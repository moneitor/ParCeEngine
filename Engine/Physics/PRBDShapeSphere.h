#pragma once

#include "PRBDShape.h"



class pRBDSphere : public pRBDShape
{
public:
    pRBDSphere(assModel *model, float radius);
    virtual ~pRBDSphere();
    virtual pShapeType GetShapeType() const override;
    virtual assModel *GetModel() override;
    virtual void SetMeshVertices() override;
    virtual std::vector<pVec3> GetMeshVerticesLocal() const override;
    virtual std::vector<pVec3> GetMeshVerticesWorld() const override;
    virtual void SetMeshFaces() override;
    virtual std::vector< std::vector<pVec3> > GetMeshFaces() const override;
    virtual pMat3 GetInertiaTensor() const override;
    virtual pVec3 GetCenterOfMass() const override;

    float GetRadius() const;

    virtual void UpdateVertices(const pQuat &orient, const pVec3 &pos) override;
    virtual void UpdateFaces(const pQuat &orient, const pVec3 &pos) override;

    virtual pBounds GetBounds(const pVec3 &pos, const pQuat &orient) const override;
    virtual pBounds GetBounds() const override;

    virtual pVec3 Support(const pVec3 &dir, const pVec3 &pos, const pQuat &orient, float bias) const override;
    

private:
    assModel *m_model;

    float m_radius;
    pShapeType m_shapeType;
    pVec3 m_centerOfMass;

    pMat3 m_inertiaTensorInv;

    std::vector<pVec3> m_vertices_local;
    std::vector<pVec3> m_vertices_world;
    std::vector< std::vector<pVec3> > m_faces;
};



