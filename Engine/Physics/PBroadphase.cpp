#include "PBroadphase.h"


struct PseudoBody
{
    int id;
    float value;
    bool ismin;
};

int CompareSAP(const void *a, const void *b)
{
    const PseudoBody *ea = (const PseudoBody *)a;
    const PseudoBody *eb = (const PseudoBody *)b;

    if (ea->value < eb->value)
    {
        return -1;
    }
    return 1;
}

void SortBodiesBounds(std::vector<pRBDBody*> rbds, const int num, PseudoBody *sortedArray, const float dt)
{
    pVec3 axis = pVec3(1,1,1).Normalize();

    for (int i = 0; i < num; i++ )
    {
        pRBDBody *body = rbds[i];
        pBounds bounds = body->GetShape()->GetBounds(body->Pos(), body->Orient());

        // Expand bounds with linear velocity
        bounds.Extend(bounds.minsize + body->Vel() * dt);
        bounds.Extend(bounds.maxsize + body->Vel() * dt);

        const float epsilon = 0.01f;
        bounds.Extend(bounds.minsize + pVec3(1,1,1) * epsilon);
        bounds.Extend(bounds.maxsize + pVec3(1,1,1) * epsilon);

        sortedArray[i * 2 + 0].id = i; 
        sortedArray[i * 2 + 0].value = Dot(axis, bounds.minsize); 
        sortedArray[i * 2 + 0].ismin = true; 

        sortedArray[i * 2 + 1].id = i; 
        sortedArray[i * 2 + 1].value = Dot(axis, bounds.maxsize); 
        sortedArray[i * 2 + 1].ismin = false; 
    }
    qsort(sortedArray, num*2, sizeof(PseudoBody), CompareSAP);
}


void BuildCollisionPairs(std::vector<CollisionPair> &collisionPairs, const PseudoBody *sortedBodies, int num)
{
    collisionPairs.clear();

    for ( int i = 0; i < num * 2; i++ ) {
		const PseudoBody &a = sortedBodies[ i ];
		if ( !a.ismin ) {
			continue;
		}

		CollisionPair pair;
		pair.a = a.id;		

		for ( int j = i + 1; j < num * 2; j++ ) {
			const PseudoBody &b = sortedBodies[ j ];
			// if we've hit the end of the a element, then we're done creating pairs with a
			if ( b.id == a.id ) {
				break;
			}

			if ( !b.ismin ) {
				continue;
			}

			pair.b = b.id;
			collisionPairs.push_back( pair );
		}
	}
}

void SweepAndPrune1D( std::vector<pRBDBody*> rbds, int num, std::vector< CollisionPair > &finalPairs, float dt_sec ) {
	PseudoBody *sortedBodies = (PseudoBody *)alloca( sizeof( PseudoBody ) * num * 2 );

	SortBodiesBounds( rbds, num, sortedBodies, dt_sec );
	BuildCollisionPairs( finalPairs, sortedBodies, num );
}

void BroadPhase(std::vector<pRBDBody*> rbds, int num, std::vector< CollisionPair > &finalPairs, float dt_sec ) {
	finalPairs.clear();

	SweepAndPrune1D( rbds, num, finalPairs, dt_sec );
}