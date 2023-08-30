#include "parser.h"

namespace s21 {
Parser::Parser(Data &data) : data_(data) {
  data_.far = 0.0;
  data_.near = 0.0;
  data_.v_count = 0;
  data_.e_count = 0;
  data_.max_coord = 0.0;
}

void Parser::Clear() noexcept {
  data_.far = 0.0;
  data_.near = 0.0;
  data_.v_count = 0;
  data_.e_count = 0;
  data_.max_coord = 0.0;
  data_.facets.clear();
  data_.vertexes.clear();
}

void Parser::Parse(const std::string &path) {
  Clear();
  FILE *file = fopen(path.c_str(), "rb");
  if (file) {
    fseek(file, 0, SEEK_END);
    const long size = ftell(file);
    fseek(file, 0, SEEK_SET);
    char *buffer = new char[size + 1]{};
    fread(buffer, 1, size, file);
    fclose(file);
    buffer[size] = '\n';
    size_t line_start = 0;
    for (long i = 0; i < size + 1; i++) {
      if (buffer[i] == '\n') {
        ProcessLine(std::string(buffer + line_start, buffer + i));
        line_start = i + 1;
      }
    }
    SetPerspectiveData();
    data_.e_count /= 2;
    delete[] buffer;
    buffer = nullptr;
  }
}

void Parser::ProcessLine(std::string line) {
  if (!line.empty()) {
    if (line[0] == 'v' && line[1] == ' ') {
      line.erase(line.begin());
      ParseVertex(line);
    } else if (line[0] == 'f' && line[1] == ' ') {
      line.erase(line.begin());
      ParseFacet(line);
    }
  }
}

void Parser::ParseVertex(std::string &line) {
  DelSpace(line);
  double num = 0.0;
  data_.vertexes.reserve(3);
  char *end = nullptr;
  for (int i = 0; i < 3; i++) {
    num = strtod(line.c_str(), &end);
    data_.vertexes.emplace_back(num);
    line = end;
    DelSpace(line);
  }
  if (std::fabs(num) > data_.max_coord)
    data_.max_coord = std::fabs(num);
  data_.v_count++;
}

void Parser::ParseFacet(std::string &line) {
  DelSpace(line);
  std::vector<int> buffer;
  buffer.reserve(3);
  char *end = nullptr;
  while (!line.empty()) {
    buffer.emplace_back(std::fabs(strtol(line.c_str(), &end, 10) - 1));
    line = end;
    DelNum(line);
    DelSpace(line);
  }
  size_t buffer_size = buffer.size();
  for (size_t i = 0; i < buffer_size; i++) {
    data_.facets.emplace_back(buffer[i]);
    if (i != buffer_size - 1)
      data_.facets.emplace_back(buffer[i + 1]);
    else
      data_.facets.emplace_back(buffer[0]);
  }
  data_.e_count += buffer_size == 2 ? 1 : buffer_size;
}

void Parser::DelSpace(std::string &line) const {
  while (!line.empty() && isspace(line[0]))
    line.erase(line.begin());
}

void Parser::DelNum(std::string &line) const {
  while (!line.empty() && !isspace(line[0]))
    line.erase(line.begin());
}

void Parser::SetPerspectiveData() noexcept {
  data_.max_coord *= 1.5;
  data_.far = (data_.max_coord + 10) * 10;
  data_.near = data_.max_coord / (2 * tan(60.0 * M_PI / 180 / 2));
}
}  // namespace s21
