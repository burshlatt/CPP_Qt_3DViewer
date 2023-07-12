#ifndef SRC_MODEL_MODEL_H_
#define SRC_MODEL_MODEL_H_

#include <iostream>

#include <cmath>
#include <vector>
#include <string>
#include <fstream>

namespace s21 {
  class model {
    public:
      model() {}
      ~model() {}
      
      std::vector<int> get_facet() const noexcept;
      std::vector<double> get_vertex() const noexcept;

      void Parser(std::string filename) noexcept;
      void ParseFacet(std::string &line_) noexcept;
      void ParseVertex(std::string &line_) noexcept;
      void DelNum(std::string &line_) const noexcept;
      void DelSpace(std::string &line_) const noexcept;

    private:
      std::vector<int> facets_;
      std::vector<double> vertexes_;

      // int facet_count_ = 0;
      int vertex_count_ = 0;
  };
}

#endif // SRC_MODEL_MODEL_H_