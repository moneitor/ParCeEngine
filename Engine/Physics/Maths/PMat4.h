// #pragma once

// #include "Core.h"
// #include "PVec4.h"
// #include "PVec4.h"
// #include "PMat3.h"
// #include <vector>



// class pMat4
// {
// public:   
//     float *operator[] (int value);    

//     pMat4();
//     pMat4(const pMat4 &other);
//     pMat4(float a11, float a12, float a13, float a14,
//           float a21, float a22, float a23, float a24,
//           float a31, float a32, float a33, float a34,
//           float a41, float a42, float a43, float a44
//           );
//     pMat4(const pVec4 &row0, const pVec4 &row1, const pVec4 &row2, const pVec4 &row3);      

//     ~pMat4() = default;

//     pVec4 GetRow0() const;
//     pVec4 GetRow1() const;
//     pVec4 GetRow2() const;
//     pVec4 GetRow3() const;

//     pMat3 Minor(const int i, const int j) const;
//     float Determinant() const;
//     pMat4 Transpose() const;
//     inline pMat4 Invert() const;

//     pMat4 & operator = (const pMat4 &other);  
//     inline const pMat4 operator * (const float value);
//     inline const pMat4 operator * (const pVec4 &vec);
//     inline const pMat4 operator * (const pMat4 &other);
//     inline const pMat4 & operator += (const pMat4 &other);  
//     inline const pMat4 & operator -= (const pMat4 &other);  
//     inline const pMat4 & operator *= (const float value);  
//     inline const pMat4 & operator *= (const pMat4 &other);  
//     inline const pMat4 & operator /= (const float value);  

//     friend pVec4 operator * (const pMat4 &mat, const pVec4 &vec);
//     friend pVec4 operator * (const pVec4 &vec, const pMat4 &mat);


// private:
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