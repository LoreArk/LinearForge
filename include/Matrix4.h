#ifndef MATRIX4_H
#define MATRIX4_H

#include "Vector3.h"
#include <cmath>

struct Matrix4 {
    // I dati della matrice: m[riga][colonna]
    float m[4][4];

    Matrix4(); 

    static Matrix4 Identity();
    static Matrix4 Translation(const Vector3& translation);
    static Matrix4 RotationZ(float angleRadiant);
    static Matrix4 Scale(const Vector3& scale);

    Matrix4 operator*(const Matrix4& other) const; 
    Vector3 multiplyPoint(const Vector3& p) const;  
    Vector3 multiplyVec(const Vector3& v) const;    
};

#endif