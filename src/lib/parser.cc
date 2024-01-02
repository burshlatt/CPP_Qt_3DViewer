#include "parser.h"

namespace s21 {
Parser::Parser(Data& data) : data_(data) {
  std::ios::sync_with_stdio(false);
  data_ = NewData{};
}

void Parser::Parse(std::string_view path) {
  data_ = NewData{};
  std::ifstream file(path.data());
  if (file.is_open()) {
    std::filesystem::path cut_path(path.data());
    cut_path.remove_filename();
    data_.file_dir = cut_path.generic_string();

    std::string line;
    while (std::getline(file, line)) {
      tokens_ = GetTokens(line);
      if (line.find(".mtl") != std::string::npos) {
        ParseMtl();
      } else if (line.find("usemtl") != std::string::npos) {
        ParseOffset();
      } else if (line[0] == 'v' && line[1] == ' ') {
        ParseVertex(data_.vertexes_v, 4);
      } else if (line[0] == 'v' && line[1] == 't' && line[2] == ' ') {
        ParseVertex(data_.vertexes_t, 3);
        data_.is_texture = true;
      } else if (line[0] == 'v' && line[1] == 'n' && line[2] == ' ') {
        ParseVertex(data_.vertexes_n, 4);
        data_.is_normals = true;
      } else if (line[0] == 'f' && line[1] == ' ') {
        ParseFacet();
      }
    }

    if (data_.mtl.empty()) data_.mtl.emplace_back(Mtl{});
    if (data_.usemtl.empty()) data_.usemtl.emplace_back(UseMtl{});

    data_.usemtl.back().offset_fv = data_.indices.size();
    data_.usemtl.back().offset_uv = data_.uv_map.size();
    NormalizeVertexes();

    file.close();
  }
}

std::vector<std::string> Parser::GetTokens(std::string_view line) {
  std::string token;
  std::istringstream stream(line.data());
  std::vector<std::string> words;

  while (stream >> token) words.push_back(token);

  return words;
}

void Parser::ParseOffset() {
  for (unsigned int i = 0; i < data_.mtl.size(); ++i) {
    if (data_.mtl[i].name == tokens_[1]) {
      data_.usemtl.push_back({i, 0, 0});
      if (!data_.indices.empty()) {
        data_.usemtl[data_.usemtl.size() - 2].offset_fv = data_.indices.size();
        data_.usemtl[data_.usemtl.size() - 2].offset_uv = data_.uv_map.size();
      }
      break;
    }
  }
}

std::string Parser::GetMtlFileName() {
  std::string mtl_file_name;
  for (size_t i = 0; i < tokens_.size(); i++)
    if (tokens_[i].find(".mtl") != std::string::npos)
      mtl_file_name = tokens_[i];
  return mtl_file_name;
}

void Parser::ParseMtl() {
  std::ifstream file(data_.file_dir + GetMtlFileName());
  if (file.is_open()) {
    Mtl new_mtl;
    std::string read_line;
    while (std::getline(file, read_line)) {
      std::istringstream iss(read_line);
      std::string type;
      iss >> type;
      if (type == "newmtl") {
        if (!new_mtl.name.empty()) {
          data_.mtl.push_back(new_mtl);
          new_mtl = {};
        }
        iss >> new_mtl.name;
      } else if (type == "Ns") {
        iss >> new_mtl.Ns;
      } else if (type == "Ka") {
        iss >> new_mtl.Ka[0] >> new_mtl.Ka[1] >> new_mtl.Ka[2];
      } else if (type == "Kd") {
        iss >> new_mtl.Kd[0] >> new_mtl.Kd[1] >> new_mtl.Kd[2];
      } else if (type == "Ks") {
        iss >> new_mtl.Ks[0] >> new_mtl.Ks[1] >> new_mtl.Ks[2];
      } else if (type == "Ke") {
        iss >> new_mtl.Ke[0] >> new_mtl.Ke[1] >> new_mtl.Ke[2];
      } else if (type == "Ni") {
        iss >> new_mtl.Ni;
      } else if (type == "d") {
        iss >> new_mtl.d;
      } else if (type == "illum") {
        iss >> new_mtl.illum;
      } else if (type == "map_Ka") {
        iss >> new_mtl.map_ka;
        new_mtl.map_ka = data_.file_dir + new_mtl.map_ka;
      } else if (type == "map_Kd") {
        iss >> new_mtl.map_kd;
        new_mtl.map_kd = data_.file_dir + new_mtl.map_kd;
      } else if (type == "map_Ks") {
        iss >> new_mtl.map_ks;
        new_mtl.map_ks = data_.file_dir + new_mtl.map_ks;
      }
    }
    if (!new_mtl.name.empty()) data_.mtl.push_back(new_mtl);
    file.close();
  }
}

void Parser::NormalizeVertexes() {
  unsigned int combined_idx = 0;
  unsigned int next_combined_idx = 0;
  std::map<Index, unsigned int, compare> index_map;
  auto future = std::async(std::launch::async,
                           std::bind(&s21::Parser::SetUniqueEdges, this));
  if (data_.indices.size() != 2 * data_.f_count) {
    for (auto& idx : data_.indices) {
      if (index_map.count(idx)) {
        combined_idx = index_map.at(idx);
      } else {
        combined_idx = next_combined_idx;
        index_map.insert(std::make_pair(idx, combined_idx));
        data_.vertexes.push_back(data_.vertexes_v[idx.fv * 3]);
        data_.vertexes.push_back(data_.vertexes_v[idx.fv * 3 + 1]);
        data_.vertexes.push_back(data_.vertexes_v[idx.fv * 3 + 2]);
        if (data_.is_texture) {
          data_.vertexes.push_back(data_.vertexes_t[idx.ft * 2]);
          data_.vertexes.push_back(data_.vertexes_t[idx.ft * 2 + 1]);
        }
        if (data_.is_normals) {
          data_.vertexes.push_back(data_.vertexes_n[idx.fn * 3]);
          data_.vertexes.push_back(data_.vertexes_n[idx.fn * 3 + 1]);
          data_.vertexes.push_back(data_.vertexes_n[idx.fn * 3 + 2]);
        }
        ++next_combined_idx;
      }
      data_.facets.push_back(combined_idx);
    }
  }
}

void Parser::ParseVertex(std::vector<float>& vert, int size) {
  float num = 0.0;
  char* end = nullptr;
  for (int i = 1; i < size; i++) {
    num = std::strtof(tokens_[i].c_str(), &end);
    vert.push_back(num);
    if (tokens_[0] == "v") {
      if (num < data_.min_coord[i - 1]) data_.min_coord[i - 1] = num;
      if (num > data_.max_coord[i - 1]) data_.max_coord[i - 1] = num;
    }
  }
}

void Parser::NormalizeWithEarcut(std::vector<Index>& ind_buff) {
  float off_01 = data_.vertexes_v[ind_buff[2].fv * 3 + 0] -
                 data_.vertexes_v[ind_buff[0].fv * 3 + 0];
  float off_02 = data_.vertexes_v[ind_buff[2].fv * 3 + 1] -
                 data_.vertexes_v[ind_buff[0].fv * 3 + 1];
  float off_03 = data_.vertexes_v[ind_buff[2].fv * 3 + 2] -
                 data_.vertexes_v[ind_buff[0].fv * 3 + 2];
  float off_04 = data_.vertexes_v[ind_buff[3].fv * 3 + 0] -
                 data_.vertexes_v[ind_buff[1].fv * 3 + 0];
  float off_05 = data_.vertexes_v[ind_buff[3].fv * 3 + 1] -
                 data_.vertexes_v[ind_buff[1].fv * 3 + 1];
  float off_06 = data_.vertexes_v[ind_buff[3].fv * 3 + 2] -
                 data_.vertexes_v[ind_buff[1].fv * 3 + 2];
  float sum_01 = off_01 * off_01 + off_02 * off_02 + off_03 * off_03;
  float sum_02 = off_04 * off_04 + off_05 * off_05 + off_06 * off_06;
  if (sum_01 < sum_02) {
    data_.indices.push_back(ind_buff[0]);
    data_.indices.push_back(ind_buff[1]);
    data_.indices.push_back(ind_buff[2]);
    data_.indices.push_back(ind_buff[0]);
    data_.indices.push_back(ind_buff[2]);
    data_.indices.push_back(ind_buff[3]);
  } else {
    data_.indices.push_back(ind_buff[0]);
    data_.indices.push_back(ind_buff[1]);
    data_.indices.push_back(ind_buff[3]);
    data_.indices.push_back(ind_buff[1]);
    data_.indices.push_back(ind_buff[2]);
    data_.indices.push_back(ind_buff[3]);
  }
}

Point3D Parser::Cross(const Point3D& v1, const Point3D& v2) noexcept {
  return {v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z,
          v1.x * v2.y - v1.y * v2.x};
}

Point3D Parser::Normalize(const Point3D& e) {
  float inv_length = 1.0f / std::sqrt(e.x * e.x + e.y * e.y + e.z * e.z);
  return {e.x * inv_length, e.y * inv_length, e.z * inv_length};
}

float Parser::Dot(const Point3D& v1, const Point3D& v2) noexcept {
  return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

Point3D Parser::WorldToLocal(const Point3D& a, const Point3D& u,
                             const Point3D& v, const Point3D& w) noexcept {
  return {Dot(a, u), Dot(a, v), Dot(a, w)};
}

void Parser::NewellsAlgorithm(std::vector<Index>& ind_buff,
                              unsigned int p_count) {
  Index i0{}, i0_2{};
  Point3D n1{};
  for (size_t k = 0; k < p_count; ++k) {
    i0 = ind_buff[k % p_count];
    auto vi0 = size_t(i0.fv);
    size_t j = (k + 1) % p_count;
    i0_2 = ind_buff[j];
    auto vi0_2 = size_t(i0_2.fv);

    float v0x = data_.vertexes_v[vi0 * 3 + 0];
    float v0y = data_.vertexes_v[vi0 * 3 + 1];
    float v0z = data_.vertexes_v[vi0 * 3 + 2];
    float v0x_2 = data_.vertexes_v[vi0_2 * 3 + 0];
    float v0y_2 = data_.vertexes_v[vi0_2 * 3 + 1];
    float v0z_2 = data_.vertexes_v[vi0_2 * 3 + 2];

    const Point3D point1 = {v0x, v0y, v0z};
    const Point3D point2 = {v0x_2, v0y_2, v0z_2};

    Point3D a = {point1.x - point2.x, point1.y - point2.y, point1.z - point2.z};
    Point3D b = {point1.x + point2.x, point1.y + point2.y, point1.z + point2.z};

    n1.x += (a.y * b.z);
    n1.y += (a.z * b.x);
    n1.z += (a.x * b.y);
  }
  float length_n = std::sqrt(n1.x * n1.x + n1.y * n1.y + n1.z * n1.z);
  if (length_n > 0) {
    float inv_length = -1.0f / length_n;
    n1.x *= inv_length;
    n1.y *= inv_length;
    n1.z *= inv_length;

    Point3D axis_w, axis_v, axis_u;
    axis_w = n1;
    Point3D a;
    if (std::abs(axis_w.x) > 0.9999999f) {
      a = {0.0f, 1.0f, 0.0f};
    } else {
      a = {1.0f, 0.0f, 0.0f};
    }
    axis_v = Normalize(Cross(axis_w, a));
    axis_u = Cross(axis_w, axis_v);
    using Point2D = std::pair<float, float>;

    std::vector<std::vector<Point2D>> polygon;
    std::vector<Point2D> polyline;

    bool is_err = false;
    for (size_t k = 0; k < p_count; ++k) {
      i0 = ind_buff[k];
      auto vi0 = size_t(i0.fv);
      if (3 * vi0 + 2 >= data_.vertexes_v.size()) {
        is_err = true;
        break;
      }

      float v0x = data_.vertexes_v[vi0 * 3 + 0];
      float v0y = data_.vertexes_v[vi0 * 3 + 1];
      float v0z = data_.vertexes_v[vi0 * 3 + 2];

      Point3D polypoint = {v0x, v0y, v0z};
      Point3D loc = WorldToLocal(polypoint, axis_u, axis_v, axis_w);

      polyline.emplace_back(std::pair(loc.x, loc.y));
    }
    if (!is_err) {
      polygon.push_back(polyline);
      std::vector<unsigned int> order = mapbox::earcut(polygon);
      if (order.size() % 3 == 0) {
        for (auto& i : order) {
          data_.indices.push_back(ind_buff[i]);
        }
      }
    }
  }
}

void Parser::NormalizeIndices(std::vector<Index>& ind_buff,
                              unsigned int p_count) {
  if (p_count == 4)
    NormalizeWithEarcut(ind_buff);
  else if (p_count > 4)
    NewellsAlgorithm(ind_buff, p_count);
  else
    std::move(ind_buff.begin(), ind_buff.end(),
              std::back_inserter(data_.indices));
}

void Parser::ParseFacet() {
  data_.f_count++;
  Index ind;
  int p_count = 0;
  long int num = 0;
  char* end = nullptr;
  std::vector<Index> ind_buff;
  std::vector<unsigned int> buffer_;
  buffer_.reserve(tokens_.size());
  unsigned int begin_index = data_.facets_v.size();
  for (auto& it : tokens_) {
    if (!it.empty() && it != "f") {
      num = std::strtol(it.c_str(), &end, 10);
      if (num < 0) {
        ind.fv = data_.vertexes_v.size() / 3 - static_cast<unsigned int>(-num);
      } else if (num > 0) {
        ind.fv = static_cast<unsigned int>(num) - 1;
      }
      it = end;
      buffer_.push_back(ind.fv);
      if (it[0] == '/') {
        it.erase(it.begin());
        if (it[0] != '/') {
          num = std::strtol(it.c_str(), &end, 10);
          if (num < 0) {
            ind.ft =
                data_.vertexes_t.size() / 2 - static_cast<unsigned int>(-num);
          } else if (num > 0) {
            ind.ft = static_cast<unsigned int>(num) - 1;
          }
          it = end;
        }
      }
      if (it[0] == '/') {
        it.erase(it.begin());
        num = std::strtol(it.c_str(), &end, 10);
        if (num < 0) {
          ind.fn =
              data_.vertexes_n.size() / 3 - static_cast<unsigned int>(-num);
        } else if (num > 0) {
          ind.fn = static_cast<unsigned int>(num) - 1;
        }
        it = end;
      }

      if (data_.facets_v.size() != begin_index) {
        data_.facets_v.push_back(ind.fv);
        data_.uv_map.push_back(ind.ft);
      }
      data_.facets_v.push_back(ind.fv);
      data_.uv_map.push_back(ind.ft);

      ind_buff.push_back(ind);
      ++p_count;
    }
  }
  data_.facets_v.push_back(data_.facets_v[begin_index]);
  data_.uv_map.push_back(data_.uv_map[begin_index]);
  NormalizeIndices(ind_buff, p_count);
}

void Parser::SetUniqueEdges() {
  std::set<std::pair<unsigned int, unsigned int>> edges_set;
  for (size_t i = 0; i < data_.facets_v.size(); i += 2) {
    std::pair<unsigned int, unsigned int> edge;
    if (data_.facets_v[i] > data_.facets_v[i + 1])
      edge = {data_.facets_v[i], data_.facets_v[i + 1]};
    else
      edge = {data_.facets_v[i + 1], data_.facets_v[i]};
    edges_set.insert(std::move(edge));
  }
  data_.edges.reserve(edges_set.size());
  for (auto& [start, finish] : edges_set) {
    data_.edges.emplace_back(start);
    data_.edges.emplace_back(finish);
  }
}
}  // namespace s21
