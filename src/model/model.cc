#include "model.h"

std::vector<int> s21::model::get_facet() const noexcept { return facets_; }
std::vector<double> s21::model::get_vertex() const noexcept { return vertexes_; }

void s21::model::Parser(std::string filename) noexcept {
  std::string line_;
  std::ifstream file_(filename);
  if (file_.is_open()) {
    while (std::getline(file_, line_)) {
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
    vertex_count_ = vertexes_.size();
  }
  file_.close();
}

void s21::model::ParseVertex(std::string &line_) noexcept {
  DelSpace(line_);
  while (!line_.empty()) {
    vertexes_.push_back(atof(line_.c_str()));
    DelNum(line_);
    DelSpace(line_);
  }
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
  par_.Parser("shuttle.obj");
  std::vector<int> res_ = par_.get_facet();
  for (size_t i = 0; i < res_.size(); i++) {
    std::cout << res_[i] << " ";
  }
  std::cout << std::endl << res_.size() << std::endl;
  return 0;
}
