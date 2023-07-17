#include "model.h"

int s21::model::get_count_f() const noexcept { return facet_count_; }
int s21::model::get_count_v() const noexcept { return vertex_count_; }
std::vector<int> s21::model::get_facet() const noexcept { return facets_; }
std::vector<double> s21::model::get_vertex() const noexcept { return vertexes_; }

// void s21::model::Parser(std::string filename) noexcept {
//   std::string line_;
//   std::ifstream file_(filename);
//   if (file_.is_open()) {
//     while (std::getline(file_, line_)) {
//       if (!line_.empty() && isspace(line_[0]))
//         DelSpace(line_);
//       if (line_[0] == 'v') {
//         line_.erase(line_.begin());
//         ParseVertex(line_);
//       } else if (line_[0] == 'f') {
//         line_.erase(line_.begin());
//         ParseFacet(line_);
//       }
//     }
//   }
//   file_.close();
// }

// void s21::model::Parser(std::string filename) noexcept {
//   FILE* file_ = fopen(filename.c_str(), "r");
//   if (file_ != NULL) {
//     char buffer_[1000];
//     while (fgets(buffer_, sizeof(buffer_), file_) != NULL) {
//       std::string line_ = std::string(buffer_);
//       if (!line_.empty() && isspace(line_[0]))
//         DelSpace(line_);
//       if (line_[0] == 'v') {
//         line_.erase(line_.begin());
//         ParseVertex(line_);
//       } else if (line_[0] == 'f') {
//         line_.erase(line_.begin());
//         ParseFacet(line_);
//       }
//     }
//   }
//   fclose(file_);
// }

void s21::model::Parser(std::string filename) noexcept {
  FILE* file_ = fopen(filename.c_str(), "r");
  if (file_ != NULL) {
    fseek(file_, 0, SEEK_END);
    long int size_ = ftell(file_);
    char *buffer_ = new char[size_ * 2]{};
    char line_buffer_[1000]{};
    int j = 0;
    fread(buffer_, sizeof(char), size_, file_);
    for (long int i = 0; i < size_; i++) {
      if (buffer_[i] != '\n') {
        line_buffer_[j] = buffer_[i];
        j++;
      } else {
        j = 0;
        std::string line_ = std::string(line_buffer_);
        memset(line_buffer_, 0, sizeof(line_buffer_));
        if (!line_.empty() && isspace(line_[0]))
          DelSpace(line_);
        if (line_[0] == 'v') {
          line_.erase(line_.begin());
          ParseVertex(line_);
        } else if (line_[0] == 'f') {
          line_.erase(line_.begin());
          ParseFacet(line_);
        }
      }
    }
    delete[] buffer_;
  }
  fclose(file_);
}

void s21::model::ParseVertex(std::string &line_) noexcept {
  DelSpace(line_);
  while (!line_.empty()) {
    vertexes_.push_back(atof(line_.c_str()));
    DelNum(line_);
    DelSpace(line_);
  }
  vertex_count_++;
}

void s21::model::ParseFacet(std::string &line_) noexcept {
  std::vector<int> buffer_;
  DelSpace(line_);
  while (!line_.empty()) {
    buffer_.push_back(atoi(line_.c_str()));
    DelNum(line_);
    DelSpace(line_);
  }
  for (size_t i = 0; i < buffer_.size(); i++) {
    if(i != buffer_.size() - 1) {
      facets_.push_back(buffer_[i]);
      facets_.push_back(buffer_[i + 1]);
    } else {
      facets_.push_back(buffer_[i]);
      facets_.push_back(buffer_[0]);
    }
  }
  facet_count_++;
}

void s21::model::DelSpace(std::string &line_) const noexcept {
  while(!line_.empty() && isspace(line_[0])) {
    line_.erase(line_.begin());
  }
}

void s21::model::DelNum(std::string &line_) const noexcept {
  while(!line_.empty() && !isspace(line_[0])) {
    line_.erase(line_.begin());
  }
}

int main() {
  s21::model par_;
  par_.Parser("car.obj");
  std::vector<double> res_1 = par_.get_vertex();
  for (size_t i = 0; i < res_1.size(); i++) {
    std::cout << res_1[i] << " ";
  }
  std::vector<int> res_2 = par_.get_facet();
  for (size_t i = 0; i < res_2.size(); i++) {
    std::cout << res_2[i] << " ";
  }
  std::cout << std::endl << "\nVertexes: " << par_.get_count_v();
  std::cout << std::endl << "Facets: " << par_.get_count_f() << std::endl;
  return 0;
}
