#pragma once

#include <cmath>
#include <iostream>
#include <limits>
#include <array>

#include "glm/vec3.hpp"

namespace geometrycentral {

// Note: this class avoids any constructors so that it is a POD type
struct Vector3 {
  // Components
  double x, y, z;

  // Access-by-index
  double& operator[](int index) { return (&x)[index]; }
  double operator[](int index) const { return (&x)[index]; };

  // Overloaded operators
  Vector3 operator+(const Vector3& v) const;
  Vector3 operator-(const Vector3& v) const;
  Vector3 operator*(double s) const;
  Vector3 operator/(double s) const;
  Vector3& operator+=(const Vector3& v);
  Vector3& operator-=(const Vector3& v);
  Vector3& operator*=(const double& s);
  Vector3& operator/=(const double& s);
  bool operator==(const Vector3& v) const;
  bool operator!=(const Vector3& v) const;
  const Vector3 operator-() const;

  // Other functions
  Vector3 rotate_around(Vector3 axis, double theta) const;
  void normalize();

  static Vector3 constant(double c) { return Vector3{c, c, c}; }

  static Vector3 zero() { return Vector3{0., 0., 0.}; }

  static Vector3 infinity() {
    const double inf = ::std::numeric_limits<double>::infinity();
    return Vector3{inf, inf, inf};
  }

  static Vector3 undefined() {
    const double nan = ::std::numeric_limits<double>::quiet_NaN();
    return Vector3{nan, nan, nan};
  }

  inline std::array<float, 3> toFloatArray() const {
    return {{static_cast<float>(x),
             static_cast<float>(y),
             static_cast<float>(z)}};
  }

  bool isFinite() const;
  bool isDefined() const;
};

Vector3 operator*(const double s, const Vector3& v);

::std::ostream& operator<<(::std::ostream& output, const Vector3& v);

double norm(const Vector3& v);
double norm2(const Vector3& v);
Vector3 unit(const Vector3& v);
Vector3 cross(const Vector3& u, const Vector3& v);
double angle(const Vector3& u, const Vector3& v);
double angleInPlane(const Vector3& u, const Vector3& v, const Vector3& normal);
double dot(const Vector3& u, const Vector3& v);
bool isFinite(const Vector3& u);
Vector3 componentwiseMin(const Vector3& u, const Vector3& v);
Vector3 componentwiseMax(const Vector3& u, const Vector3& v);

Vector3 fromGLM(const glm::vec3& v);


}  // namespace geometrycentral

namespace std {
template <>
struct hash<geometrycentral::Vector3> {
  std::size_t operator()(const geometrycentral::Vector3& v) const;
};
}  // namespace std

#include "vector3.ipp"
