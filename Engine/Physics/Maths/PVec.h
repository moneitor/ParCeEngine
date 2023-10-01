#pragma once
#include <array>
#include <iostream>

#include "Core.h"


#define D2 2
#define D3 3

#define X 0
#define Y 1
#define Z 2

template <typename coord_type, size_t dimensions = D3 >
class pVec 
{
    static_assert(std::is_arithmetic_v<coord_type>, "Vector class can only store integral or floating points values");
    static_assert(dimensions >= D2, "Vector dimension atleast should be 2D");

    std::array<coord_type, dimensions> coords = {};
    bool is_normalized = false;

public:
    pVec() {}

    pVec(std::array<coord_type, dimensions> _coords) : coords(_coords) {}

    pVec(coord_type _x, coord_type _y, coord_type _z) : coords({_x,_y,_z}) {}

    pVec(coord_type _x, coord_type _y) : coords({ _x,_y}) {}

    bool operator==(const pVec<coord_type, dimensions>&) const;
    bool operator!=(const pVec<coord_type, dimensions>&) const;
    bool operator<(const pVec<coord_type, dimensions>&) const;
    bool operator>(const pVec<coord_type, dimensions>&) const;
    pVec<coord_type, dimensions> operator*(coord_type value);
    pVec<coord_type, dimensions> operator-(const pVec<coord_type, dimensions>&) const;
    pVec<coord_type, dimensions> operator+(const pVec<coord_type, dimensions>&) const;
    coord_type operator[](const unsigned int) const;

    float Dot(const pVec<coord_type, dimensions>& v1, const pVec<coord_type, dimensions>& v2);
    pVec<coord_type, dimensions> Cross(const pVec<coord_type, dimensions>&);
    void assign(const unsigned int dim, coord_type value);
    float magnitude() const;
    void normalize();

};

typedef pVec<float, D2>		pVec2d;
typedef pVec<float, D3>		pVec3d;

template<typename coord_type, size_t dimensions>
bool pVec<coord_type, dimensions>::operator==(const pVec<coord_type, dimensions>& _other) const
{
    for (int i = 0; i < dimensions; i++)
    {
        if (!compareDouble(coords[i], _other.coords[i]))
            return false;
    }
    return true;
}


template<typename coord_type, size_t dimensions>
bool pVec<coord_type, dimensions>::operator!=(const pVec<coord_type, dimensions>& _other) const
{
    return !(*this == _other);
}


template<typename coord_type, size_t dimensions>
bool pVec<coord_type, dimensions>::operator<(const pVec<coord_type, dimensions>& _other) const
{
    for (size_t i = 0; i < dimensions; i++)
    {
        if (this->coords[i] < _other.coords[i])
            return true;
        else if (this->coords[i] > _other.coords[i])
            return false;
    }

    return false;
}


template<typename coord_type, size_t dimensions>
bool pVec<coord_type, dimensions>::operator>(const pVec<coord_type, dimensions>& _other) const
{
    if (*this == _other)
    {
        return false;
    }
    return !(*this < _other);
}

template<typename coord_type, size_t dimensions>
pVec<coord_type, dimensions> pVec<coord_type, dimensions>::operator*(coord_type value)
{
    std::array<coord_type, dimensions> temp_array;

    for (int i = 0; i < dimensions; i++)
    {
        temp_array[i] = coords[i] * value;
    }

    return pVec<coord_type, dimensions>(temp_array);
}


template<typename coord_type, size_t dimensions>
pVec<coord_type, dimensions> pVec<coord_type, dimensions>::operator-( const pVec<coord_type, dimensions>& _other) const
{
    std::array<coord_type, dimensions> temp_array;

    for (int i = 0; i < dimensions; i++)
        temp_array[i] = coords[i] - _other.coords[i];

    return pVec<coord_type, dimensions>(temp_array);
}


template<typename coord_type, size_t dimensions>
pVec<coord_type, dimensions> pVec<coord_type, dimensions>::operator+(const pVec<coord_type, dimensions>& _other) const
{
    std::array<coord_type, dimensions> temp_array;

    for (int i = 0; i < dimensions; i++)
        temp_array[i] = coords[i] + _other.coords[i];

    return pVec<coord_type, dimensions>(temp_array);
}

template <typename coord_type, size_t dimensions>
coord_type pVec<coord_type, dimensions>::operator[](const unsigned int value) const
{
    if (value >= coords.size()) {
        std::cout << "Index out of bounds";
        return coord_type();
    }

    return coords[value];
}

template <typename coord_type, size_t dimensions>
float pVec<coord_type, dimensions>::Dot(const pVec<coord_type, dimensions>& v1, const pVec<coord_type, dimensions>& v2)
{
    if (v1.coords.size() != v2.coords.size())
			return FLT_MIN;

		float product = 0;
		for (size_t i = 0; i < v1.coords.size(); i++)
			product = product + v1[i] * v2[i];
		return product;
}

template<typename coord_type, size_t dimensions>
void pVec<coord_type, dimensions>::assign(const unsigned int _index, coord_type value)
{
    if (_index >= coords.size()) {
        std::cout << "Index out of bounds";
    }

    coords[_index] = value;
}

template<typename coord_type, size_t dimensions>
float pVec<coord_type, dimensions>::magnitude() const
{
    float value = 0.0f;
    for (int i = 0; i < dimensions; i++)
        value += pow(coords[i], 2.0);

    return sqrt(value);
}


template<typename coord_type, size_t dimensions>
void pVec<coord_type, dimensions>::normalize()
{
    auto mag = magnitude();
    for (int i = 0; i < dimensions; i++)
        assign(i, coords[i] / mag);
}




