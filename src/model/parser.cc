#include "parser.h"

namespace s21 {
const Data& Parser::get_data() const noexcept {
  return data_;
}

void Parser::Parse(std::string path) noexcept {
  Clear();
  std::string line_;
  std::ifstream file_(path);
  if (file_.is_open()) {
    while (std::getline(file_, line_)) {
      if (!line_.empty() && isspace(line_[0]))
        DelSpace(line_);
      if (line_[0] == 'v' && isspace(line_[1])) {
        line_.erase(line_.begin());
        ParseVertex(line_);
      } else if (line_[0] == 'f' && isspace(line_[1])) {
        line_.erase(line_.begin());
        ParseFacet(line_);
      }
    }
  }
  file_.close();
}

void Parser::Clear() noexcept {
  data_.facets_.clear();
  data_.vertexes_.clear();
  data_.v_count_ = 0;
  data_.max_coord_ = 0.0;
}

void Parser::DelSpace(std::string &line_) const noexcept {
  while(!line_.empty() && isspace(line_[0]))
    line_.erase(line_.begin());
}

void Parser::DelNum(std::string &line_) const noexcept {
  while(!line_.empty() && !isspace(line_[0]))
    line_.erase(line_.begin());
}

void Parser::ParseVertex(std::string &line_) noexcept {
  DelSpace(line_);
  double num_ = 0.0;
  while (!line_.empty()) {
    num_ = atof(line_.c_str());
    data_.vertexes_.push_back(num_);
    DelNum(line_);
    DelSpace(line_);
    if (fabs(num_) > data_.max_coord_)
      data_.max_coord_ = num_;
  }
  data_.v_count_++;
}

void Parser::ParseFacet(std::string &line_) noexcept {
  std::vector<int> buffer_;
  DelSpace(line_);
  while (!line_.empty()) {
    buffer_.push_back(atoi(line_.c_str()) - 1);
    DelNum(line_);
    DelSpace(line_);
  }
  for (size_t i = 0; i < buffer_.size(); i++) {
    data_.facets_.push_back(buffer_[i]);
    if(i != buffer_.size() - 1)
      data_.facets_.push_back(buffer_[i + 1]);
    else
      data_.facets_.push_back(buffer_[0]);
  }
  data_.f_count_++;
}

// void Parser::Parser(std::string path) noexcept {
//   FILE* file_ = fopen(path.c_str(), "r");
//   if (file_ != NULL) {
//     fseek(file_, 0, SEEK_END);
//     long int size_ = ftell(file_);
//     char *buffer_ = new char[size_ * 2]{};
//     char line_buffer_[1000]{};
//     int j = 0;
//     fread(buffer_, sizeof(char), size_, file_);
//     for (long int i = 0; i < size_; i++) {
//       if (buffer_[i] != '\n') {
//         line_buffer_[j] = buffer_[i];
//         j++;
//       } else {
//         j = 0;
//         std::string line_ = std::string(line_buffer_);
//         memset(line_buffer_, 0, sizeof(line_buffer_));
//         if (!line_.empty() && isspace(line_[0]))
//           DelSpace(line_);
//         if (line_[0] == 'v') {
//           line_.erase(line_.begin());
//           ParseVertex(line_);
//         } else if (line_[0] == 'f') {
//           line_.erase(line_.begin());
//           ParseFacet(line_);
//         }
//       }
//     }
//     delete[] buffer_;
//   }
//   fclose(file_);
// }
}
