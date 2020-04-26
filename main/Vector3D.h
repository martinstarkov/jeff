#pragma once
#include <Wire.h>

#define LEFT_WRAP "("
#define RIGHT_WRAP ")"
#define SPLIT_CHARACTER ","

struct Vector3D {
  float x, y, z;
  
  Vector3D(float x, float y, float z) : x(x), y(y), z(z) {}
  Vector3D() : x(0.0), y(0.0), z(0.0) {}
  Vector3D(String v) {
    v = v.substring(1, v.length() - 1); // remove first and last character, i.e. wrapping chars
    int firstSplit = v.indexOf(SPLIT_CHARACTER); // index of first split character
    int secondSplit = v.indexOf(SPLIT_CHARACTER, firstSplit + 1); // index of second split character
    x = v.substring(0, firstSplit).toFloat(); // everything before first comma
    y = v.substring(firstSplit + 1, secondSplit).toFloat(); // everything between first and second comma
    z = v.substring(secondSplit + 1, v.length()).toFloat(); // everything after second comma
  }
  float minValue() {
    float m = min(x, y);
    return min(m, z);
  }
  float maxValue() {
    float m = max(x, y);
    return max(m, z);
  }
  operator String() const {
    return LEFT_WRAP + String(x, 1) + SPLIT_CHARACTER + String(y, 1) + SPLIT_CHARACTER + String(z, 1) + RIGHT_WRAP;
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
  bool operator== (const Vector3D &v) const {
    return x == v.x && y == v.y && z == v.z;
  }
};
