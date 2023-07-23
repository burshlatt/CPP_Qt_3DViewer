#ifndef SRC_MODEL_PARSER_H_
#define SRC_MODEL_PARSER_H_

#include <cmath>
#include <vector>
#include <string>
#include <cstring>
#include <fstream>
#include <iostream>

namespace s21 {
  class Parser {
    public:
      Parser() {}
      ~Parser() {}
      
      int get_count_f() const noexcept;
      int get_count_v() const noexcept;
      double get_max_coord() const noexcept;
      std::vector<double> get_vertex() const noexcept;
      std::vector<unsigned int> get_facet() const noexcept;

      void Parse(std::string filename) noexcept;
      void ParseFacet(std::string &line_) noexcept;
      void ParseVertex(std::string &line_) noexcept;
      void DelNum(std::string &line_) const noexcept;
      void DelSpace(std::string &line_) const noexcept;

    private:
      int facet_count_ = 0;
      int vertex_count_ = 0;
      double max_coord_ = 0.0;
      std::vector<double> vertexes_;
      std::vector<unsigned int> facets_;
  };
}

#endif // SRC_MODEL_PARSER_H_