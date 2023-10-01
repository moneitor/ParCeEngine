// #pragma once

// #include "Core.h"
// #include "PVec3.h"
// #include "PMat2.h"
// #include <vector>



// class pMat3
// {
// public:   
//     float *operator[] (int value);    

//     pMat3();
//     pMat3(const pMat3 &other);
//     pMat3(float a11, float a12, float a13,
//           float a21, float a22, float a23,
//           float a31, float a32, float a33
//           );
//     pMat3(const pVec3 &row0, const pVec3 &row1, const pVec3 &row2);      

//     ~pMat3() = default;

//     pVec3 GetRow0() const;
//     pVec3 GetRow1() const;
//     pVec3 GetRow2() const;

//     // float Determinant() const;
//     pMat3 Transpose() const;
//     inline pMat3 Invert() const;

//     pMat3 & operator = (const pMat3 &other);  
//     inline const pMat3 operator * (const float value);
//     inline const pMat3 operator * (const pVec3 &vec);
//     inline const pMat3 operator * (const pMat3 &other);
//     inline const pMat3 & operator += (const pMat3 &other);  
//     inline const pMat3 & operator -= (const pMat3 &other);  
//     inline const pMat3 & operator *= (const float value);  
//     inline const pMat3 & operator *= (const pMat3 &other);  
//     inline const pMat3 & operator /= (const float value);  

//     friend pVec3 operator * (const pMat3 &mat, const pVec3 &vec);
//     friend pVec3 operator * (const pVec3 &vec, const pMat3 &mat);

//     friend pMat2 Cut(const pMat3 &mat, int row, int col);  
//     friend pMat3 Minor(const pMat3, const int i, const int j);

//     union
//     {
//         struct
//         {
//             float e11, e12, e13, e14,
//                   e21, e22, e23, e24,
//                   e31, e32, e33, e34,
//                   e41, e42, e43, e44;
//         };
//         float data[16];
//     };

      
// };

// pMat2 Cut(const pMat3 &mat, int row, int col);   
// pMat3 Minor(const pMat3 &mat);