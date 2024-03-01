#include "Vector_2D.h"

Vector_2D::Vector_2D()
{
	x = 0;
	y = 0;
}
Vector_2D::Vector_2D(float x, float y)
{
	this->x = x;
	this->y = y;
}
Vector_2D& Vector_2D::add(const Vector_2D& vec)
{
	this->x += vec.x;
	this->y += vec.y;

	return *this;
}

Vector_2D& Vector_2D::subtract(const Vector_2D& vec)
{
	this->x -= vec.x;
	this->y -= vec.y;

	return *this;
}

Vector_2D& Vector_2D::multiply(const Vector_2D& vec)
{
	this->x *= vec.x;
	this->y *= vec.y;

	return *this;
}

Vector_2D& Vector_2D::divide(const Vector_2D& vec)
{
	this->x /= vec.x;
	this->y /= vec.y;

	return *this;
}

Vector_2D& operator+(Vector_2D& v1, const Vector_2D& v2)
{
	return v1.add(v2);
}

Vector_2D& operator-(Vector_2D& v1, const Vector_2D& v2)
{
	return v1.subtract(v2);
}

Vector_2D& operator*(Vector_2D& v1, const Vector_2D& v2)
{
	return v1.multiply(v2);
}

Vector_2D& operator/(Vector_2D& v1, const Vector_2D& v2)
{
	return v1.divide(v2);
}

Vector_2D& Vector_2D::operator+=(const Vector_2D& vec)
{
	return this->add(vec);
}

Vector_2D& Vector_2D::operator-=(const Vector_2D& vec)
{
	return this->subtract(vec);
}

Vector_2D& Vector_2D::operator*=(const Vector_2D& vec)
{
	return this->multiply(vec);
}

Vector_2D& Vector_2D::operator/=(const Vector_2D& vec)
{
	return this->divide(vec);
}

Vector_2D& Vector_2D::operator*(const int& i)
{
	this->x *= i;
	this->y *= i;
	return *this;
}

Vector_2D& Vector_2D::zero()
{
	this->x = 0;
	this->y = 0;
	return *this;
}

bool& operator==(Vector_2D& v1, const Vector_2D& v2)
{
	bool equal = true;
	if (v1.x == v2.x && v1.y == v2.y)
	{
		equal= true;
	}
	else
	{
		equal = false;
	}
	return equal;
}

bool& operator!=(Vector_2D& v1, const Vector_2D& v2)
{
	bool equal = true;
	if (v1.x == v2.x && v1.y == v2.y)
	{
		equal = false;
	}
	else
	{
		equal = true;
	}
	return equal;
}

std::ostream& operator<<(std::ostream& stream, const Vector_2D& vec)
{
	stream << "(" << vec.x << "," << vec.y << ")";
	return stream;
}