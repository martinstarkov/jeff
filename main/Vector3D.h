#pragma once

#define VECTOR_LEFT "("
#define VECTOR_RIGHT ")"
#define VECTOR_BETWEEN ","

struct Vector3D {
  float x, y, z;
  Vector3D(float x, float y, float z) : x(x), y(y), z(z) {}
  Vector3D() : x(0.0f), y(0.0f), z(0.0f) {}
  int maxAxis() { // axis of maximum value
    float v = maxValue();
    if (v == x) {
      return 0;
    } else if (v == y) {
      return 1;
    } else if (v == z) {
      return 2;
    }
    return -1;
  }
  int minAxis() { // axis of minimum value
    float v = minValue();
    if (v == x) {
      return 0;
    } else if (v == y) {
      return 1;
    } else if (v == z) {
      return 2;
    }
    return -1;
  }
  float minValue() {
    return min(min(x, y), z);
  }
  float maxValue() {
    return max(max(x, y), z);
  }
  float operator[] (int i) {
    switch (i) {
      case 0:
        return x;
      case 1:
        return y;
      case 2:
        return z;
      default:
        return 0;
    }
  }
  operator String() const {
    return VECTOR_LEFT + String(x, 1) + VECTOR_BETWEEN + String(y, 1) + VECTOR_BETWEEN + String(z, 1) + VECTOR_RIGHT;
  }
  Vector3D operator* (const float num) const {
    return Vector3D(x * num, y * num, z * num);
  }
  Vector3D operator/ (const float num) const {
    return Vector3D(x / num, y / num, z / num);
  }
  Vector3D operator+ (const Vector3D &v) const {
    return Vector3D(x + v.x, y + v.y, z + v.z);
  }
  Vector3D operator- (const Vector3D &v) const {
    return Vector3D(x - v.x, y - v.y, z - v.z);
  }
  Vector3D operator- () const {
    return Vector3D(-x, -y, -z);
  }
  bool operator== (const Vector3D &v) const {
    return x == v.x && y == v.y && z == v.z;
  }
};
