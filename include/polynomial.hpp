// Copyright 2018 Your Name <your_email>

#ifndef INCLUDE_POLYNOMIAL_HPP_
#define INCLUDE_POLYNOMIAL_HPP_
#include <array>
#include <cmath>
#include <cstddef>
#include <vector>

template <class T>
class Polynomial {
 private:
  std::vector<T> Data;
  void zero(Polynomial& rhs) {
    int i = rhs.Data.size() - 1;
    while (rhs.Data[i] == 0) {
      rhs.Data.pop_back();
      i -= 1;
    }
  }

 public:
  Polynomial() : Data{} {}
  ~Polynomial() {}
  size_t size() { return Data.size(); }
  explicit Polynomial(const std::vector<T> koef) {
    Data = koef;
    for (int i = static_cast<int>(koef.size()) - 1; i >= 0; i--) {
      Data[static_cast<int>(koef.size()) - 1 - i] = koef[i];
    }
  }
  T& operator[](size_t index) { return Data[index]; }
  T operator[](size_t index) const { return Data[index]; }

  Polynomial operator+(const Polynomial& rhs) {
    Polynomial buf;
    if (Data.size() >= rhs.Data.size()) {
      buf.Data = this->Data;
      for (int i = 0; i < static_cast<int>(rhs.Data.size()); i++) {
        buf.Data[i] += rhs.Data[i];
      }
    } else {
      buf.Data = this->Data;
      for (int i = 0; i < static_cast<int>(Data.size()); i++) {
        buf.Data[i] += rhs.Data[i];
      }
      for (int i = static_cast<int>(Data.size());
           i < static_cast<int>(rhs.Data.size()); i++) {
        buf.Data.push_back(rhs.Data[i]);
      }
    }
    zero(buf);
    return buf;
  }

  Polynomial& operator+=(const Polynomial& rhs) {
    if (Data.size() >= rhs.Data.size()) {
      for (int i = 0; i < static_cast<int>(rhs.Data.size()); i++) {
        Data[i] += rhs.Data[i];
      }
    } else {
      for (int i = 0; i < static_cast<int>(Data.size()); i++) {
        Data[i] += rhs.Data[i];
      }
      for (int i = static_cast<int>(Data.size());
           i < static_cast<int>(rhs.Data.size()); i++) {
        Data.push_back(rhs.Data[i]);
      }
    }
    zero(*this);
    return *this;
  }

  Polynomial operator-(const Polynomial& rhs) {
    Polynomial buf;
    if (Data.size() >= rhs.Data.size()) {
      buf.Data = this->Data;
      for (int i = 0; i < static_cast<int>(rhs.Data.size()); i++) {
        buf.Data[i] -= rhs.Data[i];
      }
    } else {
      buf.Data = this->Data;
      for (int i = 0; i < static_cast<int>(Data.size()); i++) {
        buf.Data[i] -= rhs.Data[i];
      }
      for (int i = static_cast<int>(Data.size());
           i < static_cast<int>(rhs.Data.size()); i++) {
        buf.Data.push_back(-rhs.Data[i]);
      }
    }
    zero(buf);
    return buf;
  }

  Polynomial& operator-=(const Polynomial& rhs) {
    if (Data.size() >= rhs.Data.size()) {
      for (int i = 0; i < static_cast<int>(rhs.Data.size()); i++) {
        Data[i] -= rhs.Data[i];
      }
    } else {
      for (int i = 0; i < static_cast<int>(Data.size()); i++) {
        Data[i] -= rhs.Data[i];
      }
      for (int i = static_cast<int>(Data.size());
           i < static_cast<int>(rhs.Data.size()); i++) {
        Data.push_back(rhs.Data[i]);
      }
    }
    zero(*this);
    return *this;
  }

  Polynomial operator*(const Polynomial& rhs) const {
    std::vector<T> kek(Data.size() + rhs.Data.size() - 1);
    Polynomial buf(kek);
    for (int i = 0; i < static_cast<int>(Data.size()); i++) {
      for (int j = 0; j < static_cast<int>(rhs.Data.size()); j++) {
        buf.Data[i + j] += Data[i] * rhs.Data[j];
      }
    }
    return buf;
  }

  Polynomial& operator*=(const Polynomial& rhs) {
    std::vector<T> kek(Data.size() + rhs.Data.size() - 1);
    Polynomial buf(kek);
    for (int i = 0; i < static_cast<int>(Data.size()); i++) {
      for (int j = 0; j < static_cast<int>(rhs.Data.size()); j++) {
        buf.Data[i + j] += Data[i] * rhs.Data[j];
      }
    }
    Data = buf.Data;
    return *this;
  }

  Polynomial operator*(const T rhs) {
    Polynomial buf(*this);
    for (int i = 0; i < static_cast<int>(Data.size()); i++) {
      buf.Data[i] *= rhs;
    }
    zero(buf);
    return buf;
  }

  Polynomial& operator*=(const T rhs) {
    for (int i = 0; i < static_cast<int>(Data.size()); i++) {
      Data[i] *= rhs;
    }
    zero(*this);
    return *this;
  }

  Polynomial operator/(const Polynomial rhs) {
    std::vector<T> kek(Data.size() - rhs.Data.size() + 1);
    Polynomial buf(kek);
    Polynomial temp = *this;
    if (Data.size() < rhs.Data.size()) {
      zero(buf);
      return buf;
    } else {
      for (int i = 0; i < static_cast<int>(buf.Data.size()); i++) {
        buf.Data[buf.Data.size() - i - 1] =
            temp[temp.Data.size() - 1 - i] / rhs.Data[rhs.Data.size() - 1];
        for (int j = 0; j < static_cast<int>(rhs.Data.size()); j++) {
          temp.Data[temp.Data.size() - j - i - 1] -=
              rhs.Data[rhs.Data.size() - j - 1] *
              buf.Data[buf.Data.size() - i - 1];
        }
      }
      return buf;
    }
  }

  Polynomial& operator/=(const Polynomial rhs) {
    std::vector<T> kek(Data.size() - rhs.Data.size() + 1);
    Polynomial buf(kek);
    Polynomial temp = *this;
    if (Data.size() < rhs.Data.size()) {
      zero(buf);
      *this = buf;
      return *this;
    } else {
      for (int i = 0; i < static_cast<int>(buf.Data.size()); i++) {
        buf.Data[buf.Data.size() - i - 1] =
            temp[temp.Data.size() - 1 - i] / rhs.Data[rhs.Data.size() - 1];
        for (int j = 0; j < static_cast<int>(rhs.Data.size()); j++) {
          temp.Data[temp.Data.size() - j - i - 1] -=
              rhs.Data[rhs.Data.size() - j - 1] *
              buf.Data[buf.Data.size() - i - 1];
        }
      }
      *this = buf;
      return *this;
    }
  }

  Polynomial operator%(const Polynomial rhs) {
    if (Data.size() < rhs.Data.size()) {
      return *this;
    }
    Polynomial temp = *this;
    temp /= rhs;
    temp *= rhs;
    temp = *this - temp;
    return temp;
  }

  Polynomial& operator%=(const Polynomial rhs) {
    if (Data.size() < rhs.Data.size()) {
      return *this;
    }
    Polynomial temp = *this;
    temp /= rhs;
    temp *= rhs;
    temp = *this - temp;
    *this = temp;
    return *this;
  }

  int degree() { return static_cast<int>(Data.size() - 1); }

  T count(T x) {
    T sum = 0;
    for (int i = 0; i < static_cast<int>(Data.size()); i++) {
      sum += pow(x, i) * Data[i];
    }
    return sum;
  }

  bool operator==(const Polynomial rhs) const {
    if (Data.size() != rhs.Data.size()) {
      return false;
    }
    for (size_t i = 0; i < Data.size(); ++i) {
      if (Data[i] != rhs[i]) {
        return false;
      }
    }
    return true;
  }
};

#endif  // INCLUDE_POLYNOMIAL_HPP_
