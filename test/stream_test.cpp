#include "gtest/gtest.h"
#include "stream/stream.hpp"

TEST(MakeStream, MakeStream0) {
  std::vector<int> vec{1,2,3,4,5};
  EXPECT_EQ(MakeStream(vec) | to_vector(), vec);
}

TEST(MakeStream, MakeStream1) {
  std::vector<int> vec{1,2,3,4,5};
  EXPECT_EQ(MakeStream(1,2,3,4,5) | to_vector(), vec);
}

TEST(MakeStream, MakeStream2) {
  std::vector<int> vec{1,2,3,4,5};
  EXPECT_EQ(MakeStream(vec.begin(), vec.end()) | to_vector(), vec);
}

TEST(MakeStream, MakeStream3) {
  std::vector<int> vec{1,2,3,4,5};
  EXPECT_EQ(MakeStream({1,2,3,4,5}) | to_vector(), vec);
}

TEST(MakeStream, MakeStream4) {
  std::vector<int> vec{1,2,3,4,5};
  EXPECT_EQ(MakeStream(std::move(vec)) | to_vector(), vec);
}

TEST(FUNCTIONAL, MAP){
  auto s = MakeStream(1,2,3,4,5);
  auto S = s | map([](int a){return std::to_string(a);}) | to_vector();
  EXPECT_EQ(std::move(S), std::vector<std::string>({"1","2","3","4","5"}));
}

TEST(FUNCTIONAL, LAMBDA){
  auto s = MakeStream(1,2,3,4,5);
  auto S = s | ([](int a){return std::to_string(a);}) | to_vector();
  EXPECT_EQ(S, std::vector<std::string>({"1","2","3","4","5"}));
}

TEST(FUNCTIONAL, FILTER){
  auto s = MakeStream(1,2,3,4,5);
  auto S = s | filter([](int a){return a%2;}) | to_vector();
  EXPECT_EQ(S, std::vector<int>({1,3,5}));
}

TEST(FUNCTIONAL, REDUCE){
  auto s = MakeStream(1,2,3,4,5);
  auto S1 = s | reduce([](int a,int b){return a+b;});
  auto S2 = s | reduce([](int a){return 0;},[](int a,int b){return a+b;});
  EXPECT_EQ(S1, 15);
  EXPECT_EQ(S2, 14);
}

TEST(FUNCTIONAL, GROUP){
  auto s = MakeStream(1,2,3,4);
  auto S1= s | group(2) | to_vector();
  std::vector<std::vector<int>> res(2);
  res[0] = std::vector<int>{1,2};
  res[1] = std::vector<int>{3,4};
  EXPECT_EQ(S1, res);
}

TEST(FUNCTIONAL, COMPLEX){
  auto s = MakeStream(1,2,3,4);
  auto res = s | ([](int a){return a * 2;}) | filter([](int a){return a>2;}) | filter([](int a){return a>4;}) | nth(1);
  EXPECT_EQ(res, 8);
}

