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

static bool compareDouble(double x, double y)
{
    return fabs(x - y) < TOLERANCE;
}