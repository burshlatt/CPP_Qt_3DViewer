#include <gtest/gtest.h>

#include "../model/parser/parser.h"

namespace s21 {
class Test {
 public:
  Data data_;
  std::unique_ptr<Parser> pars_;

  Test(Data& data) { pars_ = std::make_unique<Parser>(data); }
};
}  // namespace s21

TEST(Parser, parser_1) {
  s21::Test test_(test_.data_);
  test_.pars_->Parse("cube.obj");
  EXPECT_EQ(test_.data_.v_count_, 8);
  EXPECT_EQ(test_.data_.f_count_, 12);
  EXPECT_EQ(test_.data_.far_, (0.5 * 1.5 + 10) * 10);
  EXPECT_EQ(test_.data_.near_, 0.5 * 1.5 / (2 * tan(60.0 * M_PI / 180 / 2)));
  EXPECT_EQ(test_.data_.max_coord_, 0.5 * 1.5);
}

TEST(Parser, parser_2) {
  s21::Test test_(test_.data_);
  test_.pars_->Parse("cube.obj");
  std::vector<int> facets_ = {
      0, 6, 6, 4, 4, 0, 0, 2, 2, 6, 6, 0, 0, 3, 3, 2, 2, 0, 0, 1, 1, 3, 3, 0,
      2, 7, 7, 6, 6, 2, 2, 3, 3, 7, 7, 2, 4, 6, 6, 7, 7, 4, 4, 7, 7, 5, 5, 4,
      0, 4, 4, 5, 5, 0, 0, 5, 5, 1, 1, 0, 1, 3, 3, 7, 7, 1, 1, 7, 7, 1};
  std::vector<double> vertexes_ = {
      -0.5, -0.5, -0.5, -0.5, -0.5, 0.5, -0.5, 0.5, -0.5, -0.5, 0.5, 0.5,
      0.5,  -0.5, -0.5, 0.5,  -0.5, 0.5, 0.5,  0.5, -0.5, 0.5,  0.5, 0.5};
  EXPECT_EQ(test_.data_.facets_, facets_);
  EXPECT_EQ(test_.data_.vertexes_, vertexes_);
}

int main(int argc, char* argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
