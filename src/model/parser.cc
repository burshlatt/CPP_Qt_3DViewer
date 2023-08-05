#include "parser.h"

namespace s21 {
Parser::Parser() {
    data_.v_count_ = 0;
    data_.f_count_ = 0;
    data_.max_coord_ = 0.0;
}

Parser::~Parser() { Clear(); }

const Data& Parser::get_data() const noexcept { return data_; }

void Parser::Clear() noexcept {
    data_.facets_.clear();
    data_.vertexes_.clear();
    data_.f_count_ = 0;
    data_.v_count_ = 0;
    data_.max_coord_ = 0.0;
}

void Parser::Parse(const std::string &path) noexcept {
    Clear();
    FILE* file_ = fopen(path.c_str(), "rb");
    if (file_) {
        const size_t size_ = GetSize(file_);
        char *buffer_ = new char[size_]{};
        size_t line_start_ = 0;
        size_t read_ = fread(buffer_, 1, size_, file_);
        for (size_t i = 0; i < read_; i++) {
            if (buffer_[i] == '\n' || i == read_ - 1) {
                ProcessLine(std::string(buffer_ + line_start_, buffer_ + i));
                line_start_ = i + 1;
            }
        }
        delete[] buffer_;
        buffer_ = nullptr;
        fclose(file_);
    }
}

const long& Parser::GetSize(FILE *file) const noexcept {
    long start_ = ftell(file);
    fseek(file, 0, SEEK_END);
    long end_ = ftell(file);
    fseek(file, start_, SEEK_SET);
    if (end_ > 0) return end_;
    else return 0;
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

void Parser::ParseVertex(std::string& line) noexcept {
    DelSpace(line);
    double num_ = 0.0;
    std::vector<double> buffer_;
    buffer_.reserve(3);
    char *end = nullptr;
    while (!line.empty()) {
        num_ = strtod(line.c_str(), &end);
        buffer_.push_back(num_);
        line = end;
        DelSpace(line);
    }
    data_.vertexes_.insert(data_.vertexes_.end(), buffer_.begin(), buffer_.begin() + 3);
    if (std::fabs(num_) > data_.max_coord_)
        data_.max_coord_ = std::fabs(num_);
    data_.v_count_++;
}

void Parser::ParseFacet(std::string& line) noexcept {
    DelSpace(line);
    std::vector<int> buffer_;
    buffer_.reserve(3);
    char* end = nullptr;
    while (!line.empty()) {
        buffer_.push_back(strtol(line.c_str(), &end, 10) - 1);
        line = end;
        DelNum(line);
        DelSpace(line);
    }
    for (size_t i = 0; i < buffer_.size(); i++) {
        data_.facets_.push_back(buffer_[i]);
        if (i != buffer_.size() - 1)
            data_.facets_.push_back(buffer_[i + 1]);
        else
            data_.facets_.push_back(buffer_[0]);
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
}
