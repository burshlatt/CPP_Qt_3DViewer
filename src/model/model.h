#ifndef SRC_MODEL_MODEL_H_
#define SRC_MODEL_MODEL_H_

#include <iostream>

#include <cmath>
#include <vector>
#include <string>
#include <cstring>
#include <fstream>

namespace s21 {
  class model {
    public:
      model() {}
      ~model() {}
      
      int get_count_f() const noexcept;
      int get_count_v() const noexcept;
      std::vector<double> get_vertex() const noexcept;
      std::vector<unsigned int> get_facet() const noexcept;

      void Parser(std::string filename) noexcept;
      void ParseFacet(std::string &line_) noexcept;
      void ParseVertex(std::string &line_) noexcept;
      void DelNum(std::string &line_) const noexcept;
      void DelSpace(std::string &line_) const noexcept;

    private:
      int facet_count_ = 0;
      int vertex_count_ = 0;
      std::vector<double> vertexes_;
      std::vector<unsigned int> facets_;
  };
}

#endif // SRC_MODEL_MODEL_H_