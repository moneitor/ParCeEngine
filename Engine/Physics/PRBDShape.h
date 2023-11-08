#pragma once
#pragma once

#include "Maths/PMat3.h"
#include "Maths/PMat4.h"
#include "../Graphics/Entity/AssModel.h"

enum pShapeType
{
    SPHERE,
    CUBE,
    CONVEX,
    CYLINDER
};

class pRBDShape
{
public:
    pRBDShape();
    virtual ~pRBDShape();
    virtual pShapeType GetShapeType() const = 0;
    virtual assModel *GetModel() = 0;
    virtual void GetMeshVertices() = 0;
    virtual pMat3 GetInertiaTensor() const = 0;
    virtual pVec3 GetCenterOfMass() const = 0;
};

class pRBDSphere : public pRBDShape
{
public:
    pRBDSphere(assModel *model, float radius);
    virtual ~pRBDSphere();
    virtual pShapeType GetShapeType() const override;
    virtual assModel *GetModel() override;
    virtual void GetMeshVertices() override;
    virtual pMat3 GetInertiaTensor() const override;
    virtual pVec3 GetCenterOfMass() const override;

    float GetRadius() const;

private:
    assModel *m_model;

    float m_radius;
    pShapeType m_shapeType;
    pVec3 centerOfMass;
};


class pRBDCube : public pRBDShape
{
public:
    pRBDCube(assModel *model);
    virtual ~pRBDCube();
    virtual pShapeType GetShapeType() const override;
    virtual assModel *GetModel() override;
    virtual void GetMeshVertices() override;
    virtual pMat3 GetInertiaTensor() const override;
    virtual pVec3 GetCenterOfMass() const override;

private:

    assModel *m_model;
    std::vector<pVec3> m_vertices;

    pShapeType m_shapeType;
    pVec3 centerOfMass;
};



class pRBDConvex : public pRBDShape
{
public:
    pRBDConvex(assModel *model);
    virtual ~pRBDConvex();
    virtual pShapeType GetShapeType() const override;
    virtual assModel *GetModel() override;
    virtual void GetMeshVertices() override;
    virtual pMat3 GetInertiaTensor() const override;
    virtual pVec3 GetCenterOfMass() const override;

private:
    assModel *m_model;
    std::vector<pVec3> m_vertices;

    pShapeType m_shapeType;
    pVec3 centerOfMass;
};