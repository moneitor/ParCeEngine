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

	pMat4 pmat = pMat4(0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15);
	pMat4 ident = pMat4();
	pMat4 invert = Inverse(ident);
	pMat3 ident3 = pMat3();
	pMat3 cofactor3 = Cofactor(ident3);
	pMat3 adjugate3 = Adjugate(ident3);
	pMat3 invert3 = Inverse(ident3);

	
	pMat3 cut = Cut(pmat, 1, 1);
	pMat4 minor = Minor(pmat);
	pMat4 cofactor = Cofactor(pmat);

	std::cout << "Mat element is: " << pmat[0][1] << std::endl;
	// std::cout << "Mat element is: " << trans[2][0] << std::endl;
	std::cout << "Cut element is: " << cut[0][0] << " " << cut[0][1] << " " << cut[0][2] <<std::endl;
	std::cout << "Cut element is: " << cut[1][0] << " " << cut[1][1] << " " << cut[1][2] <<std::endl;


	std::cout << "Minor element is: " << minor[0][0] << " " << minor[0][1]<<  " " << minor[0][2]<<std::endl;
	std::cout << "Minor element is: " << minor[1][0] << " " << minor[1][1]<<  " " << minor[1][2]<<std::endl;
	std::cout << "Minor element is: " << minor[2][0] << " " << minor[2][1]<<  " " << minor[2][2]<<std::endl;

	std::cout << "Cofactor3 element is: " << cofactor3[0][0] << " " << cofactor3[0][1]<<  " " << cofactor3[0][2]<<std::endl;
	std::cout << "Cofactor3 element is: " << cofactor3[1][0] << " " << cofactor3[1][1]<<  " " << cofactor3[1][2]<<std::endl;
	std::cout << "Cofactor3 element is: " << cofactor3[2][0] << " " << cofactor3[2][1]<<  " " << cofactor3[2][2]<<std::endl;

	std::cout << "Invert element is: " << invert3[0][0] << " " << invert3[0][1]<<  " " << invert3[0][2]<<std::endl;
	std::cout << "Invert element is: " << invert3[1][0] << " " << invert3[1][1]<<  " " << invert3[1][2]<<std::endl;
	std::cout << "Invert element is: " << invert3[2][0] << " " << invert3[2][1]<<  " " << invert3[2][2]<<std::endl;

	std::cout << "Adjugate element is: " << adjugate3[0][0] << " " << adjugate3[0][1]<<  " " << adjugate3[0][2]<<std::endl;
	std::cout << "Adjugate element is: " << adjugate3[1][0] << " " << adjugate3[1][1]<<  " " << adjugate3[1][2]<<std::endl;
	std::cout << "Adjugate element is: " << adjugate3[2][0] << " " << adjugate3[2][1]<<  " " << adjugate3[2][2]<<std::endl;

	std::cout << "Determinant3 of mat is: " << Determinant(ident3) <<  std::endl;




	return 0;
}