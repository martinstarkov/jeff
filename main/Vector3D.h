#pragma once

#define VECTOR_SPLIT_CHARACTER ","

struct Vector3D {
  float x, y, z;
  
  Vector3D(float x, float y, float z) : x(x), y(y), z(z) {}
  Vector3D() : x(0), y(0), z(0) {}
  Vector3D(auto a) { // json array -> vector object conversion
    JsonArray array = a;
    x = array[0].as<float>();
    y = array[1].as<float>();
    z = array[2].as<float>();
  }
  
  operator String() const {
    return "(" + String(x) + VECTOR_SPLIT_CHARACTER + String(y) + VECTOR_SPLIT_CHARACTER + String(z) + ")";
  }
  Vector3D operator/ (const float num) const {
    return Vector3D(x / num, y / num, z / num);
  }
  Vector3D operator+ (const Vector3D &v) const {
    return Vector3D(x + v.x, y + v.y, z + v.z);
  }
  bool operator== (const Vector3D &v) const {
    return x == v.x && y == v.y && z == v.z;
  }
};
