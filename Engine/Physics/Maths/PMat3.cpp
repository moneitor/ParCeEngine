#include "PMat3.h"

pMat3::pMat3()
    :e11{1}, e12{0}, e13{0},
     e21{0}, e22{1}, e23{0},
     e31{0}, e32{0}, e33{1}
{
}

pMat3::pMat3(const pMat3 &other)
    :e11{other.e11}, e12{other.e12}, e13{other.e13}, 
     e21{other.e21}, e22{other.e22}, e23{other.e23}, 
     e31{other.e31}, e32{other.e32}, e33{other.e33}
{
}

pMat3::pMat3(const pVec3 &row0_, const pVec3 &row1_, const pVec3 &row2_)
    :e11{row0_.GetX()}, e12{row0_.GetY()}, e13{row0_.GetZ()}, 
     e21{row1_.GetX()}, e22{row1_.GetY()}, e23{row1_.GetZ()}, 
     e31{row2_.GetX()}, e32{row2_.GetY()}, e33{row2_.GetZ()}
{
}

pMat3::pMat3(float a11_, float a12_, float a13_, 
             float a21_, float a22_, float a23_, 
             float a31_, float a32_, float a33_)
    :e11{a11_}, e12{a12_}, e13{a13_}, 
     e21{a21_}, e22{a22_}, e23{a23_}, 
     e31{a31_}, e32{a32_}, e33{a33_}
{
}

pVec3 pMat3::GetRow0() const
{
    return pVec3(e11, e12, e13);
}

pVec3 pMat3::GetRow1() const
{
    return pVec3(e21, e22, e23);
}

pVec3 pMat3::GetRow2() const
{
    return pVec3(e31, e32, e33);
}

pMat3 pMat3::Transpose() const
{
    pMat3 transposed;
    TransposeGeneric(this->data, transposed.data, 3, 3);
    return transposed;
}

pMat3 pMat3::Invert() const
{
    return pMat3();
}



pMat3 &pMat3::operator=(const pMat3 &other)
{
    this->e11 = other.e11;
    this->e12 = other.e12;
    this->e13 = other.e13;

    this->e21 = other.e21;
    this->e22 = other.e22;
    this->e23 = other.e23;

    this->e31 = other.e31;
    this->e32 = other.e32;
    this->e33 = other.e33;

    return *this;
}

const pMat3 pMat3::operator*(const float value)
{
    pMat3 result;
    for (int i=0; i < 9; i++)
    {
        result.data[i] = this->data[i] * value; 
    }
    return result;
}

const pMat3 pMat3::operator*(const pVec3 &vec)
{
    return pMat3();
}

const pMat3 pMat3::operator*(const pMat3 &other)
{
    pMat3 result;
    MatrixMultiplyGeneric(result.data, this->data, 3, 3, other.data, 3, 3);
    return result;
}

void pMat3::ToEulerAngles(float &yaw, float &pitch, float &roll)
{
    yaw = std::atan2f(e32, e33);
    pitch = std::asin(-e31);
    roll = std::atan2f(e21, e11);
}

float *pMat3::operator[](int value)
{
    return &(data[value * 3]);
}

pMat3 operator*(const pMat3 &A, const pMat3 &B)
{
    pMat3 result;
    MatrixMultiplyGeneric(result.data, A.data, 3, 3, B.data, 3, 3);
    return result;
}

pVec3 operator*(const pVec3 &vec, const pMat3 &mat)
{
    pVec3 result;
    result.SetX( Dot(vec, pVec3(mat.e11, mat.e21, mat.e31)) );
    result.SetY( Dot(vec, pVec3(mat.e12, mat.e22, mat.e32)) );
    result.SetZ( Dot(vec, pVec3(mat.e13, mat.e23, mat.e33)) );
    return result;
}

pMat3 Transpose(const pMat3 &mat)
{    
    pMat3 transposed;
    TransposeGeneric(mat.data, transposed.data, 3, 3);
    return transposed;
}

pMat2 Cut(const pMat3 &mat, int row, int col)
{
	pMat2 result;
	int index = 0;

	for (int i = 0; i < 3; ++i) 
    {
		for (int j = 0; j < 3; ++j) 
        {
			if (i == row || j == col) 
            {
				continue;
			}
			result.data[index++] = mat.data[3 * i + j];
		}
	}

	return result;
}

pMat3 Minor(const pMat3 &mat)
{
    pMat3 result;

    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            result[i][j] = Determinant(Cut(mat, i, j));
        }
    }

    return result;
}

pMat3 Cofactor(const pMat3 &mat)
{
    pMat3 out;
    CofactorGeneric(out.data, Minor(mat).data, 3, 3);
    return out;
}


float Determinant(const pMat3 &mat)
{
    float out = 0.0f;
    pMat3 cofactor = Cofactor(mat);
    for (int j = 0; j < 3; ++j)
    {
        int index = 3 * (0 + j);
        out += mat.data[index] * cofactor[0][j];
    }
    return out;

//     return mat.e11 * mat.e22 - mat.e33 -
//            mat.e11 * mat.e32 * mat.e23 +
//            mat.e21 * mat.e32 * mat.e13 -
//            mat.e21 * mat.e12 * mat.e33 +
//            mat.e31 * mat.e12 * mat.e23 -
//            mat.e31 * mat.e22 * mat.e13;
}

pMat3 Adjugate(const pMat3 &mat)
{
    return Transpose(Cofactor(mat));
}

pMat3 Inverse(const pMat3 &mat)
{
    // float determinant = Determinant(mat);
    // if(compareDouble(determinant, 0.0f)) return pMat3();
    // return Adjugate(mat) * (1.0f / determinant);

    float determinant = mat.e11 * mat.e22 - mat.e33 -
                        mat.e11 * mat.e32 * mat.e23 +
                        mat.e21 * mat.e32 * mat.e13 -
                        mat.e21 * mat.e12 * mat.e33 +
                        mat.e31 * mat.e12 * mat.e23 -
                        mat.e31 * mat.e22 * mat.e13;

    if (compareDouble(determinant, 0.0f))
    {
        return pMat3();
    }

    pMat2 result;
    float i_det = 1.0f / determinant;

    return pMat3((mat.e22 * mat.e33 - mat.e23 * mat.e32) * i_det,
                -(mat.e12 * mat.e33 - mat.e13 * mat.e32) * i_det,
                 (mat.e12 * mat.e23 - mat.e13 * mat.e22) * i_det,
                -(mat.e21 * mat.e33 - mat.e23 * mat.e31) * i_det,
                 (mat.e11 * mat.e33 - mat.e13 * mat.e31) * i_det,
                -(mat.e11 * mat.e23 - mat.e13 * mat.e21) * i_det,
                 (mat.e21 * mat.e32 - mat.e22 * mat.e31) * i_det,
                -(mat.e11 * mat.e32 - mat.e12 * mat.e31) * i_det,
                 (mat.e11 * mat.e22 - mat.e12 * mat.e21) * i_det);

    
}

pMat3 XRotation3(float angle)
{
    angle = DEG2RAD(angle);
    return pMat3(1.0f,   0.0f,        0.0f,
                 0.0f,   cosf(angle), sinf(angle),
                 0.0f,   -sinf(angle), cos(angle));
}

pMat3 YRotation3(float angle)
{
    angle = DEG2RAD(angle);
    return pMat3(cosf(angle), 0.0f,    -sinf(angle),
                 0.0f,        1.0f,    0.0f,
                 sinf(angle), 0.0f,    cosf(angle));
}

pMat3 ZRotation3(float angle)
{
    angle = DEG2RAD(angle);
    return pMat3(cosf(angle), sinf(angle), 0.0f,
                -sinf(angle), cosf(angle), 0.0f,
                 0.0f,        0.0f,        1.0f);
}

pMat3 Rotation3(float pitch, float yaw, float roll)
{
    return ZRotation3(roll) * XRotation3(pitch) * YRotation3(yaw);

}

pMat3 RotationAxis3(const pVec3 &axis, float angle)
{
    angle = DEG2RAD(angle);
    float c = cosf(angle);
    float s = sinf(angle);
    float t = 1.0f - cosf(angle);

    float x = axis.Normalize().GetX();
    float y = axis.Normalize().GetY();
    float z = axis.Normalize().GetZ();

    return pMat3(
		t * (x * x) + c, t * x * y + s * z, t * x * z - s * y, 
		t * x * y - s * z, t * (y * y) + c, t * y * z + s * x, 
		t * x * z + s * y, t * y * z - s * x, t * (z * z) + c    
        );
}
