#include "ParCe.h"


int main(int argc, char* argv[])
{
	Parce::Instance()->Initialize();

	while(Parce::Instance()->IsRunning())
	{		
		Parce::Instance()->Update();
		Parce::Instance()->Render();
	}

	Parce::Instance()->Destroy();

	return 0;
}