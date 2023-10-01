#include "ParCe.h"


int main(int argc, char* argv[])
{
	// Parce::Instance()->Initialize();

	// while(Parce::Instance()->IsRunning())
	// {		
	// 	Parce::Instance()->Update();
	// 	Parce::Instance()->Render();
	// }

	// Parce::Instance()->Destroy();


	// PVec<int> v1 = PVec<int>(1,2,3);

	// pVec<float, D3> v1 = pVec<float, D3>(1.8, 2.0, 0.0);
	// pVec<float, D3> v2 = pVec<float, D3>(3.5, 4.0, 5.0);
	// pVec3 pv1 = pVec3(1.0, 0.0, 0.0);
	// pVec3 pv2 = pVec3(0.0, 1.0, 0.0);	

	// pVec3 cross1 = pv1.Cross(pv2).Normalize();

	// pMat3 pmat1 = pMat3(pv1, pv2, cross1);

	pMat3 pmat3 = pMat3(0,1,2,3,4,5,6,7,8);

	
	// pMat2 minor = Cut(pmat3, 1, 1);

	std::cout << "Mat element is: " << pmat3[0][1] << std::endl;
	std::cout << "Mat Determinant is: " << glm::determinant(pmat3) << std::endl;
	// std::cout << "Mat element is: " << trans[2][0] << std::endl;
	// std::cout << "Minor element is: " << minor.data[0] << " " << minor.data[1]<< std::endl;
	// std::cout << "Minor element is: " << minor.data[2] << " " << minor.data[3]<< std::endl;



	return 0;
}