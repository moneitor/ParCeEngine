#pragma once
#pragma once

#include "Maths/PMat3.h"
#include "Maths/PMat4.h"
#include "Maths/PQuat.h"
#include "../Graphics/Entity/AssModel.h"
#include "Primitives/PBounds.h"

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
    virtual std::vector<pVec3> GetMeshVerticesWorld() const = 0;
    virtual void SetMeshFaces() = 0;
    virtual std::vector< std::vector<pVec3> > GetMeshFaces() const = 0;
    virtual pMat3 GetInertiaTensor() const = 0;
    virtual pVec3 GetCenterOfMass() const = 0;
    virtual void UpdateVertices(const pQuat &orient, const pVec3 &pos) = 0;
    virtual void UpdateFaces(const pQuat &orient, const pVec3 &pos) = 0;
    virtual pBounds GetBounds(const pVec3 &pos, const pQuat &orient) const = 0;
    virtual pBounds GetBounds() const = 0;
    virtual pVec3 Support(const pVec3 &dir, const pVec3 &pos, const pQuat &orient, float bias) const = 0;
};
