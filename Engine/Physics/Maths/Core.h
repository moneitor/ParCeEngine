#pragma once

#include <math.h>
#include <algorithm>
#include <vector>

#include <string>

#include "PVec3.h"
#include "PVec4.h"

#include <glm/mat2x2.hpp>
#include <glm/mat3x3.hpp>
#include <glm/mat4x4.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/matrix_decompose.hpp>

#define TOLERANCE 0.0000001
#define GLOBAL_SCALE 1

// typedef glm::vec2 pVec2;
// typedef glm::vec3 pVec3;
// typedef glm::vec4 pVec4;

// typedef glm::mat2 pMat2;
// typedef glm::mat3 pMat3;
// typedef glm::mat4 pMat4;



static float DEG2RAD(float angle)
{
    return angle * ( M_PI / 180.0f) ;
}

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

static bool MatrixMultiplyGeneric(float* out, const float* matA, int aRows, int aCols, const float* matB, int bRows, int bCols)
{
    // check if multiplication can be done
    if (aCols != bRows) 
        {
		return false;
	}

	for (int i = 0; i < aRows; ++i) {
		for (int j = 0; j < bCols; ++j) {
			out[bCols * i + j] = 0.0f;
			for (int k = 0; k < bRows; ++k) {
				out[bCols * i + j] += matA[aCols * i + k] * matB[bCols * k + j];
			}
		}
	}

	return true;
}

static void CofactorGeneric(float *result, const float *minor, int rows, int columns)
{
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < columns; ++j)
        {
            int t = columns * j + i; // Index
            int s = columns * j + i;
            float sign = powf(-1.0f, i + j);
            result[t] = minor[s] * sign;
        }
    }
}




