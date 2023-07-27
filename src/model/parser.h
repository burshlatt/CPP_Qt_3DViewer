#ifndef SRC_MODEL_PARSER_H_
#define SRC_MODEL_PARSER_H_

#include <cmath>
#include <vector>
#include <string>
#include <cstring>
#include <fstream>
#include <iostream>

typedef struct View {
  int v_count_ = 0;
  double max_coord_ = 0.0;
  std::vector<int> facets_;
  std::vector<double> vertexes_;
} Data;

namespace s21 {
  class Parser {
    public:
      Parser();
      ~Parser();
      
      View* get_view() const noexcept;

      void Clear() noexcept;
      void Parse(std::string path) noexcept;
      void ParseFacet(std::string &line_) noexcept;
      void ParseVertex(std::string &line_) noexcept;
      void DelNum(std::string &line_) const noexcept;
      void DelSpace(std::string &line_) const noexcept;

    private:
      Data *data_;
  };
}

#endif // SRC_MODEL_PARSER_H_