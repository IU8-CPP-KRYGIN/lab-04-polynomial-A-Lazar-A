// Copyright 2020 Your Name <your_email>

#include <gtest/gtest.h>

#include <polynomial.hpp>

TEST(Polynom, create) {
  std::vector<int> a1{1, 2, 3}, a2{4, 5};
  Polynomial<int> a(a1);
  Polynomial<int> b(a2);
  a[2] = 6;
  b[0] = -5;
  EXPECT_EQ(a, Polynomial<int>(std::vector<int>{6, 2, 3}));
  EXPECT_EQ(b, Polynomial<int>(std::vector<int>{4, -5}));
}

TEST(Polynom, sum) {
  std::vector<int> a1{1, 2, 3}, a2{4, 5};
  Polynomial<int> a(a1);
  Polynomial<int> b(a2);
  EXPECT_EQ(a + b, Polynomial<int>(std::vector<int>{1, 6, 8}));
  EXPECT_EQ(b + a, Polynomial<int>(std::vector<int>{1, 6, 8}));
  Polynomial<int> k(a1);
  a += b;
  EXPECT_EQ(a, Polynomial<int>(std::vector<int>{1, 6, 8}));
  b+=k;
  EXPECT_EQ(b, Polynomial<int>(std::vector<int>{1, 6, 8}));
}

TEST(Polynom, multy) {
  std::vector<int> a1{1, 2, 3}, a2{4, 5};
  Polynomial<int> a(a1);
  Polynomial<int> b(a2);
  EXPECT_EQ(a * b, Polynomial<int>(std::vector<int>{4, 13, 22, 15}));
  a *= b;
  EXPECT_EQ(a, Polynomial<int>(std::vector<int>{4, 13, 22, 15}));
  a *= 5;
  EXPECT_EQ(a, Polynomial<int>(std::vector<int>{20, 65, 110, 75}));
}

TEST(Polynom, sub) {
  std::vector<int> a1{1, 2, 3}, a2{4, 5};
  Polynomial<int> a(a1);
  Polynomial<int> b(a2);
  EXPECT_EQ(a - b, Polynomial<int>(std::vector<int>{1, -2, -2}));
  a -= b;
  EXPECT_EQ(a, Polynomial<int>(std::vector<int>{1, -2, -2}));
}

TEST(Polynom, div) {
  std::vector<int> k1{1, -12, 0, -42}, k2{1, -3};
  Polynomial<int> k(k1);
  Polynomial<int> l(k2);
  EXPECT_EQ(k / l, Polynomial<int>(std::vector<int>{1, -9, -27}));
  k /= l;
  EXPECT_EQ(k, Polynomial<int>(std::vector<int>{1, -9, -27}));
}

TEST(Polynom, mod) {
  std::vector<int> k1{1, -12, 0, -42}, k2{1, -3};
  Polynomial<int> k(k1);
  Polynomial<int> l(k2);
  EXPECT_EQ(k % l, Polynomial<int>(std::vector<int>{-123}));
  k %= l;
  EXPECT_EQ(k, Polynomial<int>(std::vector<int>{-123}));
}

TEST(Polynom, degree) {
  std::vector<int> k1{1, -12, 0, -42}, k2{1, -3};
  Polynomial<int> k(k1);
  Polynomial<int> l(k2);
  EXPECT_EQ(k.degree(), 3);
  EXPECT_EQ(l.degree(), 1);
}

TEST(Polynom, res) {
  std::vector<int> k1{1, -12, 0, -42}, k2{1, -3};
  Polynomial<int> k(k1);
  Polynomial<int> l(k2);
  EXPECT_EQ(k.count(3), -123);
  EXPECT_EQ(l.count(3), 0);
}