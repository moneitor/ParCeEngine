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
    virtual pShapeType GetShapeType() = 0;
    virtual assModel *GetModel() = 0;
    virtual void ChunkMeshVertices() = 0;
};

class pRBDSphere : public pRBDShape
{
public:
    pRBDSphere(assModel *model, float radius);
    virtual ~pRBDSphere();
    virtual pShapeType GetShapeType() override;
    virtual assModel *GetModel() override;
    virtual void ChunkMeshVertices() override;

    float GetRadius() const;

private:
    assModel *m_model;

    float m_radius;
    pShapeType m_shapeType;
};


class pRBDCube : public pRBDShape
{
public:
    pRBDCube(assModel *model);
    virtual ~pRBDCube();
    virtual pShapeType GetShapeType() override;
    virtual assModel *GetModel() override;
    virtual void ChunkMeshVertices() override;

private:

    assModel *m_model;
    std::vector<pVec3> m_vertices;

    pShapeType m_shapeType;
};



class pRBDConvex : public pRBDShape
{
public:
    pRBDConvex(assModel *model);
    virtual ~pRBDConvex();
    virtual pShapeType GetShapeType() override;
    virtual assModel *GetModel() override;
    virtual void ChunkMeshVertices() override;

private:
    assModel *m_model;
    std::vector<pVec3> m_vertices;

    pShapeType m_shapeType;
};