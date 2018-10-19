#include "Vec2.h"
#include <math.h>

Vec2::Vec2(float _x, float _y)
	:
	x(_x),
	y(_y)
{
}

Vec2 Vec2::operator+(const Vec2 & rhs) const
{
	return Vec2(x+rhs.x, y+rhs.y);
}

Vec2 & Vec2::operator+=(const Vec2 & rhs)
{
	return *this = *this + rhs;
}

Vec2 Vec2::operator-(const Vec2 & rhs) const
{
	return Vec2(x-rhs.x, y-rhs.y);
}

Vec2 & Vec2::operator-=(const Vec2 & rhs)
{
	return *this = *this - rhs;
}

Vec2 Vec2::operator*(float rhs) const
{
	return Vec2(x*rhs, y*rhs);
}

Vec2 & Vec2::operator*=(float rhs)
{
	return *this = *this*rhs;
}

Vec2 Vec2::operator/(float rhs) const
{
	return Vec2(x/rhs, y/rhs);
}

Vec2 & Vec2::operator/=(float rhs)
{
	return *this = *this / rhs;
}

float Vec2::GetLengthSq() const
{
	return x * x + y * y;
}

float Vec2::GetLength() const
{
	return sqrt(GetLengthSq());
}

Vec2 Vec2::GetNormalized() const
{
	const float len = GetLength();
	if (len > 0)
	{
		return *this * (1 / GetLength());
	}
	return *this;
}

Vec2 & Vec2::Normalize()
{
	return *this = this->GetNormalized();
}
