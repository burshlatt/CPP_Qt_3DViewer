#ifndef CPP5_3DVIEWER_V2_1_1_MODEL_STRUCT_H_
#define CPP5_3DVIEWER_V2_1_1_MODEL_STRUCT_H_

#include <limits>
#include <string>
#include <vector>

struct Point3D {
  float x, y, z;
};

struct Index {
  unsigned int fv;
  unsigned int fn;
  unsigned int ft;
};

typedef struct {
  unsigned int index;
  unsigned int offset_fv;
  unsigned int offset_uv;
} UseMtl;

typedef struct NewMtl {
  std::string name;
  float Ns;
  float Ka[3]{};
  float Kd[3];
  float Ks[3]{};
  float Ke[3]{};
  float Ni;
  float d;
  int illum;
  std::string map_ka;
  std::string map_kd;
  std::string map_ks;
  NewMtl();
  ~NewMtl() = default;
} Mtl;

inline NewMtl::NewMtl() : Ns(32.0f), Kd{1.0f, 1.0f, 1.0f}, d(1.0f) {}

typedef struct NewData {
  size_t f_count;
  bool is_normals;
  bool is_texture;
  float min_coord[3];
  float max_coord[3];
  std::string file_dir;
  std::vector<Mtl> mtl;
  std::vector<UseMtl> usemtl;
  std::vector<Index> indices;
  std::vector<float> vertexes;
  std::vector<float> vertexes_v;
  std::vector<float> vertexes_t;
  std::vector<float> vertexes_n;
  std::vector<unsigned int> edges;
  std::vector<unsigned int> uv_map;
  std::vector<unsigned int> facets;
  std::vector<unsigned int> facets_v;

  NewData();
  ~NewData() = default;
} Data;

inline NewData::NewData() {
  f_count = 0;
  is_normals = false;
  is_texture = false;
  min_coord[0] = std::numeric_limits<float>::max();
  min_coord[1] = std::numeric_limits<float>::max();
  min_coord[2] = std::numeric_limits<float>::max();
  max_coord[0] = std::numeric_limits<float>::min();
  max_coord[1] = std::numeric_limits<float>::min();
  max_coord[2] = std::numeric_limits<float>::min();
}

struct compare {
  bool operator()(const Index& lhs, const Index& rhs) const noexcept {
    if (lhs.fv < rhs.fv) return true;
    if (rhs.fv < lhs.fv) return false;
    if (lhs.fn < rhs.fn) return true;
    if (rhs.fn < lhs.fn) return false;
    if (lhs.ft < rhs.ft) return true;
    return rhs.ft < lhs.ft;
  }
};

enum Coord { kX, kY, kZ };

enum SType { kSmooth, kFlat };

enum ScaleAct { kScaleMul, kScaleDiv };

enum VType { kNone, kCircle, kSquare };

enum Projection { kCentral, kParallel };

enum MapType { kAmbient, kDiffuse, kSpecular };

enum ModelType { kFrame, kDashed, kSolid, kTextured };

enum Action { kLeft, kRight, kUp, kDown, kClose, kFar };

enum UIndex {
  kMvpU,
  kMvU,
  kMatNormalU,
  kColorU,
  kVertexSizeU,
  kAmbientU,
  kDiffuseU,
  kSpecularU,
  kEmissionU,
  kShinessU,
  kOpacityU
};

#endif  // CPP5_3DVIEWER_V2_1_1_MODEL_STRUCT_H_
