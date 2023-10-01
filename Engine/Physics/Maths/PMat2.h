// #pragma once

// #include "Core.h"
// #include "PVec2.h"
// #include <vector>



// class pMat2
// {
// public:   
//     float *operator[] (int value);    

//     pMat2();
//     pMat2(const pMat2 &other);
//     pMat2(float a11, float a12, float a21, float a22);
//     pMat2(const pVec2 &row0, const pVec2 &row1);      

//     ~pMat2() = default;

//     pVec2 GetRow0() const;
//     pVec2 GetRow1() const;

//     float Determinant() const;
//     pMat2 Transpose() const;
//     inline pMat2 Invert() const;

//     pMat2 & operator = (const pMat2 &other);  
//     inline const pMat2 operator * (const float value);
//     inline const pMat2 operator * (const pVec2 &vec);
//     inline const pMat2 operator * (const pMat2 &other);
//     inline const pMat2 & operator += (const pMat2 &other);  
//     inline const pMat2 & operator -= (const pMat2 &other);  
//     inline const pMat2 & operator *= (const float value);  
//     inline const pMat2 & operator *= (const pMat2 &other);  
//     inline const pMat2 & operator /= (const float value);  

//     friend pVec2 operator * (const pMat2 &mat, const pVec2 &vec);
//     friend pVec2 operator * (const pVec2 &vec, const pMat2 &mat);
//     friend float Determinant(const pMat2& mat);


// public:
//     union
//     {
//         struct
//         {
//             float e11, e12, 
//                   e21, e22;
//         };
//         float data[4];
//     };
// };

// float Determinant(const pMat2& mat);