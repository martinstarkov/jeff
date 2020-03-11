#pragma once

struct Vector3D { 
  
    float x, y, z;
    
    Vector3D(float x, float y, float z) : x(x), y(y), z(z) {}
    Vector3D() : x(0), y(0), z(0) {}
    
    String toString() { 
      return "(" + String(x) + "," + String(y) + "," + String(z) + ")";
    }
    Vector3D operator/ (const float num) const {
      return Vector3D(x / num, y / num, z / num);
    }
    Vector3D operator+ (const Vector3D &v) const {
      return Vector3D(x + v.x, y + v.y, z + v.z);
    }
};