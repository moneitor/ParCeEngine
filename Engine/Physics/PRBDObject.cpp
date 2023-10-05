#include "PRBDObject.h"

pRBDObject::pRBDObject()
{
}

pRBDObject::pRBDObject(const pVec3 & pos)
    :position{pos}
{
}

pRBDObject::pRBDObject(assModel * model, const pVec3 &pos)
    :position{pos}, object{model}
{
}

assModel * pRBDObject::GetObject()
{
    return object;
}

pVec3 pRBDObject::GetPosition()
{
    return position;
}


