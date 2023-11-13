#pragma once

#include "Maths/PQuat.h"
#include "Maths/PMat3.h"
#include "Maths/PMat4.h"
#include "./PRBDShape.h"
#include "../Graphics/Entity/AssModel.h"


#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/quaternion.hpp>


class pRBDBody
{
public:
    pRBDBody(pRBDShape *shape, float mass);
    pRBDBody(pRBDShape *shape, const pVec3 &pos, const pQuat &orient, float mass);
    ~pRBDBody();

    pRBDShape *GetShape();

    pVec3 Pos();
    void SetPosition(const pVec3 &pos);
    void SetPosition(float x, float y, float z);

    void SetOrientation(const glm::quat orient);
    glm::quat Orient();

    pVec3 Vel();
    void SetVelocity(const pVec3 &vel);
    void SetVelocity(float x, float y, float z);

    pVec3 Accel();
    void SetAcceleration(const pVec3 &accel);
    void SetAcceleration(float x, float y, float z);

    float Elasticity();
    void SetElasticity(float elasticity);

    float Mass();

    void AddForce(const pVec3 &force);
    void AddTorque(const pVec3 &torque);
    void CleanForces();
    void CleanTorques();

    void SetActive(bool value);    

    pVec3 WorldToLocal( pVec3 &vec) ;
    pVec3 LocalToWorld( pVec3 &vec) ;

    pVec3 GetCenterOfMassWorldSpace();
    pVec3 GetCenterOfMassLocalSpace();

    pMat3 GetInertiaTensorWorldSpace();
    pMat3 GetInertiaTensorLocalSpace();

    void IntegrateLinear(float dt);
    void IntegrateAngular(float dt);

private:
    pRBDShape *rbdShape;

    pVec3 position;
    pVec3 velocity;
    pVec3 acceleration;
    pVec3 netForce;

    glm::quat orientation;
    pVec3 angVelocity;
    pVec3 angAcceleration;
    pVec3 netTorque;

    // pMat4 transform;

    float elasticity;
    float mass;
    float invMass;

    bool active;
};