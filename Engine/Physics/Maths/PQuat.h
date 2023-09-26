#include "Core.h"
#include "PVec3.h"

class pQuat
{
public:
    pQuat();

    ~pQuat();


private:
    pVec3 vec;
    float n;
};