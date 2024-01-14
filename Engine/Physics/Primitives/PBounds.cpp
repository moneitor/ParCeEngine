#include "PBounds.h"

pBounds::pBounds()
:minsize{pVec3( 1e6 )}, maxsize{pVec3(-1e6)}
{
}

pBounds::pBounds(const pBounds &other)
:minsize{other.minsize}, maxsize{other.maxsize}
{
}

const pBounds & pBounds::operator = ( const pBounds &other ) 
{
	minsize = other.minsize;
	maxsize = other.maxsize;
	return *this;
}

bool pBounds::CheckIntersection(const pBounds &other) const
{
    if(maxsize.GetX() < other.minsize.GetX() || 
       maxsize.GetY() < other.minsize.GetY() ||
       maxsize.GetZ() < other.minsize.GetZ())
       {
            return false;
       }

    if(other.maxsize.GetX() < minsize.GetX() ||
       other.maxsize.GetY() < minsize.GetY() ||
       other.maxsize.GetZ() < minsize.GetZ())
       {
            return false;
       }

    return true;
}

void pBounds::Extend(const pVec3 *pts, const int num)
{
    for (int i = 0; i < num; i++)
    {
        Extend(pts[i]);
    }
}

void pBounds::Extend(const pVec3 &other)
{
    if (other.GetX() < minsize.GetX() ) {
		minsize.SetX(other.GetX())  ;
	}
	if (other.GetY() < minsize.GetY() ) {
		minsize.SetY( other.GetY());
	}
	if (other.GetZ() < minsize.GetZ() ) {
		minsize.SetZ(other.GetZ());
	}
	if (other.GetX() > maxsize.GetX() ) {
		maxsize.SetX(other.GetX());
	}
	if (other.GetY() > maxsize.GetY() ) {
		maxsize.SetY(other.GetY());
	}
	if (other.GetZ() > maxsize.GetZ() ) {
		maxsize.SetZ(other.GetZ());
	}
}

void pBounds::Extend(const pBounds &other)
{
    Extend( other.minsize );
	Extend( other.maxsize );
}

float pBounds::WidthX() const
{
    return maxsize.GetX() - minsize.GetX();
}

float pBounds::WidthY() const
{
    return maxsize.GetY() - minsize.GetY();
}


float pBounds::WidthZ() const
{
    return maxsize.GetZ() - minsize.GetZ();
}



pBounds::~pBounds()
{
}
