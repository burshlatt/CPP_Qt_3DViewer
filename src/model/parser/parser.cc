#include "parser.h"

namespace s21 {
Parser::Parser(Data &data) : data_(data) {
    data_.v_count_ = 0;
    data_.f_count_ = 0;
    data_.far_ = 0.0;
    data_.near_ = 0.0;
    data_.max_coord_ = 0.0;
}

void Parser::Clear() noexcept {
    data_.facets_.clear();
    data_.vertexes_.clear();
    data_.f_count_ = 0;
    data_.v_count_ = 0;
    data_.far_ = 0.0;
    data_.near_ = 0.0;
    data_.max_coord_ = 0.0;
}

void Parser::Parse(const std::string &path) noexcept {
    Clear();
    FILE* file_ = fopen(path.c_str(), "rb");
    if (file_) {
        fseek(file_, 0, SEEK_END);
        const long size_ = ftell(file_);
        fseek(file_, 0, SEEK_SET);
        char* buffer_ = new char[size_]{};
        fread(buffer_, 1, size_, file_);
        fclose(file_);
        size_t line_start = 0;
        for (long i = 0; i < size_; i++) {
            if (buffer_[i] == '\n' || i == size_ - 1) {
                ProcessLine(std::string(buffer_ + line_start, buffer_ + i));
                line_start = i + 1;
            }
        }
        SetPerspectiveData();
        delete[] buffer_;
        buffer_ = nullptr;
    }
}

void Parser::ProcessLine(std::string line) noexcept {
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

void Parser::ParseVertex(std::string &line) noexcept {
    DelSpace(line);
    double num_ = 0.0;
    data_.vertexes_.reserve(3);
    char *end = nullptr;
    while (!line.empty()) {
        num_ = strtod(line.c_str(), &end);
        data_.vertexes_.emplace_back(num_);
        line = end;
        DelSpace(line);
    }
    if (std::fabs(num_) > data_.max_coord_)
        data_.max_coord_ = std::fabs(num_);
    data_.v_count_++;
}

void Parser::ParseFacet(std::string &line) noexcept {
    DelSpace(line);
    std::vector<int> buffer_;
    buffer_.reserve(3);
    char* end = nullptr;
    while (!line.empty()) {
        buffer_.emplace_back(strtol(line.c_str(), &end, 10) - 1);
        line = end;
        DelNum(line);
        DelSpace(line);
    }
    for (size_t i = 0; i < buffer_.size(); i++) {
        data_.facets_.emplace_back(buffer_[i]);
        if (i != buffer_.size() - 1)
            data_.facets_.emplace_back(buffer_[i + 1]);
        else
            data_.facets_.emplace_back(buffer_[0]);
    }
    data_.f_count_++;
}

void Parser::DelSpace(std::string &line) const noexcept {
    while (!line.empty() && isspace(line[0]))
        line.erase(line.begin());
}

void Parser::DelNum(std::string &line) const noexcept {
  while(!line.empty() && !isspace(line[0]))
    line.erase(line.begin());
}

void Parser::SetPerspectiveData() noexcept {
    data_.max_coord_ *= 1.5;
    data_.far_ = (data_.max_coord_ + 10) * 10;
    data_.near_ = data_.max_coord_ / (2 * tan(60.0 * M_PI / 180 / 2));
}
}
