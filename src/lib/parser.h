#ifndef CPP_QT_3DVIEWER_LIB_PARSER_H_
#define CPP_QT_3DVIEWER_LIB_PARSER_H_

#include <vector>
#include <string>
#include <string_view>

#include "src/lib/struct.h"

namespace s21 {
class Parser {
    public:
        Parser(Data& data);
        ~Parser() = default;

        void ParseMtl();
        void ParseFacet();
        void ParseOffset();
        void SetUniqueEdges();
        void NormalizeVertexes();
        void Parse(std::string_view path);
        void ParseVertex(std::vector<float>& vert, int size);
        void NormalizeWithEarcut(std::vector<Index>& ind_buff);
        void NormalizeIndices(std::vector<Index>& ind_buff, unsigned int p_count);
        void NewellsAlgorithm(std::vector<Index>& ind_buff, unsigned int p_count);

        std::string GetMtlFileName();
        std::vector<std::string> GetTokens(std::string_view line);
        float Dot(const Point3D& v1, const Point3D& v2) noexcept;

        Point3D Normalize(const Point3D& e);
        Point3D Cross(const Point3D& v1, const Point3D& v2) noexcept;
        Point3D WorldToLocal(const Point3D& a, const Point3D& u, const Point3D& v, const Point3D& w) noexcept;

    private:
        Data& data_;
        std::vector<std::string> tokens_;
};
}  // namespace s21

#endif  // CPP_QT_3DVIEWER_LIB_PARSER_H_
