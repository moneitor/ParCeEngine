#pragma once

#include "../Maths/PVec3.h"


class pBounds
{
public:
    pBounds();
    pBounds( const pBounds &other );
    
    ~pBounds();

    const pBounds &operator=( const pBounds &other );

    bool CheckIntersection(const pBounds &other) const;

    void Extend( const pVec3 *pts, const int num );
	void Extend( const pVec3 &other );
	void Extend( const pBounds &other );

	float WidthX() const;
	float WidthY() const;
	float WidthZ() const;

public:
	pVec3 minsize;
	pVec3 maxsize;
};