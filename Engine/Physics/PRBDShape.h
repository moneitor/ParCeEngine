#pragma once
#pragma once

#include "Maths/PMat3.h"
#include "Maths/PMat4.h"
#include "Maths/PQuat.h"
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
    virtual void SetMeshVertices() = 0;
    virtual std::vector<pVec3> GetMeshVerticesLocal() const = 0;
    virtual void SetMeshFaces() = 0;
    virtual std::vector< std::vector<pVec3> > GetMeshFaces() const = 0;
    virtual pMat3 GetInertiaTensor() const = 0;
    virtual pVec3 GetCenterOfMass() const = 0;
    virtual void UpdateVertices(const pQuat &orient, const pVec3 &pos) = 0;
    virtual void UpdateFaces(const pQuat &orient, const pVec3 &pos) = 0;
};

class pRBDSphere : public pRBDShape
{
public:
    pRBDSphere(assModel *model, float radius);
    virtual ~pRBDSphere();
    virtual pShapeType GetShapeType() const override;
    virtual assModel *GetModel() override;
    virtual void SetMeshVertices() override;
    virtual std::vector<pVec3> GetMeshVerticesLocal() const override;
    virtual void SetMeshFaces() override;
    virtual std::vector< std::vector<pVec3> > GetMeshFaces() const override;
    virtual pMat3 GetInertiaTensor() const override;
    virtual pVec3 GetCenterOfMass() const override;

    float GetRadius() const;

    virtual void UpdateVertices(const pQuat &orient, const pVec3 &pos) override;
    virtual void UpdateFaces(const pQuat &orient, const pVec3 &pos) override;

private:
    assModel *m_model;

    float m_radius;
    pShapeType m_shapeType;
    pVec3 centerOfMass;

    pMat3 m_inertiaTensorInv;

    std::vector<pVec3> m_vertices_local;
    std::vector<pVec3> m_vertices_world;
    std::vector< std::vector<pVec3> > m_faces;
};


class pRBDCube : public pRBDShape
{
public:
    pRBDCube(assModel *model);
    virtual ~pRBDCube();
    virtual pShapeType GetShapeType() const override;
    virtual assModel *GetModel() override;
    virtual void SetMeshVertices() override;
    virtual std::vector<pVec3> GetMeshVerticesLocal() const override;
    virtual void SetMeshFaces() override;
    virtual std::vector< std::vector<pVec3> > GetMeshFaces() const override;
    virtual pMat3 GetInertiaTensor() const override;
    virtual pVec3 GetCenterOfMass() const override;

    virtual void UpdateVertices(const pQuat &orient, const pVec3 &pos) override;
    virtual void UpdateFaces(const pQuat &orient, const pVec3 &pos) override;

private:

    assModel *m_model;
    std::vector<pVec3> m_vertices_local;
    std::vector<pVec3> m_vertices_world;
    std::vector< std::vector<pVec3> > m_faces;

    pShapeType m_shapeType;
    pVec3 centerOfMass;

    pMat3 m_inertiaTensorInv;
};



class pRBDConvex : public pRBDShape
{
public:
    pRBDConvex(assModel *model);
    virtual ~pRBDConvex();
    virtual pShapeType GetShapeType() const override;
    virtual assModel *GetModel() override;
    virtual void SetMeshVertices() override;
    virtual std::vector<pVec3> GetMeshVerticesLocal() const override;
    virtual void SetMeshFaces() override;
    virtual std::vector< std::vector<pVec3> > GetMeshFaces() const override;
    virtual pMat3 GetInertiaTensor() const override;
    virtual pVec3 GetCenterOfMass() const override;

    virtual void UpdateVertices(const pQuat &orient, const pVec3 &pos) override;
    virtual void UpdateFaces(const pQuat &orient, const pVec3 &pos) override;

private:
    assModel *m_model;
    std::vector<pVec3> m_vertices_local;
    std::vector<pVec3> m_vertices_world;
    std::vector< std::vector<pVec3> > m_faces;

    pShapeType m_shapeType;
    pVec3 centerOfMass;

    pMat3 m_inertiaTensorInv;
};