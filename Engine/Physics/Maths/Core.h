#pragma once

#include <math.h>
#include <algorithm>
#include <vector>

#include <glm/mat2x2.hpp>
#include <glm/mat3x3.hpp>
#include <glm/mat4x4.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/matrix_decompose.hpp>

#define TOLERANCE 0.0000001

typedef glm::vec2 pVec2;
typedef glm::vec3 pVec3;
typedef glm::vec4 pVec4;

typedef glm::mat2 pMat2;
typedef glm::mat3 pMat3;
typedef glm::mat4 pMat4;

static bool compareDouble(double x, double y)
{
    return fabs(x - y) < TOLERANCE;
}

static void TransposeGeneric(const float *src, float *dst, int rows, int columns)
{
    for (int i = 0; i < rows * columns; i++)
    {
        int row_ = i/rows;
        int columns_ = i % rows;
        dst[i] = src[columns * columns_ + row_];
    }
}

static bool MatrixMultiplyGeneric(float *result, const float *A, int ARows, int ACols, const float *B, int BRows, int BCols)
{
    // check if multiplication can be done
    if(ACols != BRows) return false;

    for (int i = 0; i < ARows; ++i)
    {
        for (int j = 0; i < BCols; ++j)
        {
            result[BCols * i + j] = 0.0f;
            for (int k = 0; k < BRows; ++k)
            {
                int a = ACols * i * k;
                int b = BCols * k + j;
                result[BCols * i + j] += A[a] * B[b];
            }
        }
    }
    return true;
}

