#pragma once

#include "Core.h"
#include "PVec3.h"
#include "PMat3.h"

#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/quaternion.hpp>

class pQuat
{
public:
    pQuat();
    pQuat(const pQuat &other);
    pQuat(float w_, float x_, float y_, float z_);
    pQuat(const float angle, const pVec3 &vec);
    pQuat(float value);
    pQuat(const pVec3 &vec);
    pQuat(glm::quat quat);
    pQuat(float x, float y, float z);

    ~pQuat();

    pQuat operator*(float value);
    pQuat operator*(const pQuat &other);
    pQuat operator*(const pVec3 &v1);

    pQuat &operator*=(const pQuat &other);
    pQuat operator+(const pQuat &other);
    pQuat operator-(const pQuat &other);

    pQuat operator/(float value);

    float operator[](const int i);

    float Magnitude() const;
    float MagnitudeSq() const;

    pQuat Normalize() const;
    pMat3 ToMatrix() const;
    pVec3 ToEuler() const;

    void SetW(float value);
    void SetX(float value);
    void SetY(float value);
    void SetZ(float value);

    float GetW() const;
    float GetX() const;
    float GetY() const;
    float GetZ() const;

    float GetAngle() const;
    pVec3 GetAxis() const;
    pVec3 GetVector() const;

    std::string ToString() const;

    pQuat Invert() const;

    friend pVec3 RotateVector(const pQuat &q, const pVec3 &vec);
    friend pQuat RotateByVector(const pQuat &q, const pVec3 &vec);
    friend pQuat RotateByVector(const pQuat &q, const pVec3 &vec, float dt);

    friend pQuat operator * (const pQuat &q1, const pQuat &q2);
    friend pQuat operator * (const pVec3 &v, const pQuat &q);
    friend pQuat operator * (const pQuat &q, const pVec3 &v);

    friend pQuat operator * (float value, const pQuat &q);
    friend pQuat operator * (const pQuat &q, float value);

    friend pQuat QRotate(const pQuat &q1, const pQuat &q2);
    friend pVec3 QVRotate(const pQuat &q1, const pVec3 &v);
    
    friend pQuat EulerToQuat(float x, float y, float z);


private:
    public:
    union
    {
        struct
        {
            float w, x, y, z;
        };
        float data[4];
    };
};

pQuat operator * (const pQuat &q1, const pQuat &q2);

pQuat operator * (const pVec3 &v, const pQuat &q);
pQuat operator * (const pQuat &q, const pVec3 &v);

pQuat operator * (float value, const pQuat &q);
pQuat operator * (const pQuat &q, float value);

pVec3 RotateVector(const pQuat &q, const pVec3 &vec);
pQuat RotateByVector(const pQuat &q, const pVec3 &vec);
pQuat RotateByVector(const pQuat &q, const pVec3 &vec, float dt);

pQuat QRotate(const pQuat &q1, const pQuat &q2);
pVec3 QVRotate(const pQuat &q1, const pVec3 &v);

pQuat EulerToQuat(float x, float y, float z);
