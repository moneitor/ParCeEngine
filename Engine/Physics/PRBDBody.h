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
    pQuat Orient();

    pVec3 Vel();
    void SetVelocity(const pVec3 &vel);
    void SetVelocity(float x, float y, float z);

    pVec3 Accel();
    void SetAcceleration(const pVec3 &accel);
    void SetAcceleration(float x, float y, float z);

    pVec3 AngularVelocity();
    pVec3 AngularAcceleration();

    float Elasticity();
    void SetElasticity(float elasticity);

    float Friction();
    void SetFriction(float friction);

    float Mass();
    void SetMass(float value);
    float InvMass();

    void AddForce(const pVec3 &force);
    void AddTorque(const pVec3 &torque);
    void CleanForces();
    void CleanTorques();

    void SetActive(bool value);    
    bool IsActive() const;

    pVec3 WorldToLocal( pVec3 &vec) ;
    pVec3 LocalToWorld( pVec3 &vec) ;

    pVec3 GetCenterOfMassWorldSpace();
    pVec3 GetCenterOfMassLocalSpace();

    pMat3 GetInertiaTensorWorldSpace();
    pMat3 GetInertiaTensorLocalSpace();

    void IntegrateLinear(float dt);
    void IntegrateAngular(float dt);

    void IntegrateBody(float dt);

    void SetIsColliding(bool val);
    bool IsColliding() const;

    void ApplyImpulseLinear(const pVec3 &impulse);
    void ApplyImpulseAngular(const pVec3 &impulse);
    void ApplyImpulse(const pVec3 &r, const pVec3 &impulse);

    pMat4 GetTransform();

private:
    pRBDShape *rbdShape;

    pVec3 position;
    pVec3 velocity;
    pVec3 acceleration;
    pVec3 netForce;

    pVec3 orig_position;
    pVec3 orig_velocity;
    pVec3 orig_acceleration;
    pVec3 orig_netForce;

    pMat4 transform;

    pQuat orientation;
    pVec3 angVelocity;
    pVec3 angAcceleration;
    pVec3 netTorque;

    pQuat orig_orientation;
    pVec3 orig_angVelocity;
    pVec3 orig_angAcceleration;
    pVec3 orig_netTorque;

    // pMat4 transform;

    float elasticity;
    float mass;
    float invMass;
    float friction;

    bool active;
    bool isColliding;
};