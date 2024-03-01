#pragma once
#include <iostream>

class Vector_2D
{
public:
	float x;
	float y;

	Vector_2D();
	Vector_2D(float x, float y);

	Vector_2D& add(const Vector_2D& vec);
	Vector_2D& subtract(const Vector_2D& vec);
	Vector_2D& multiply(const Vector_2D& vec);
	Vector_2D& divide(const Vector_2D& vec);

	friend Vector_2D& operator+(Vector_2D& v1, const Vector_2D& v2);
	friend Vector_2D& operator-(Vector_2D& v1, const Vector_2D& v2);
	friend Vector_2D& operator*(Vector_2D& v1, const Vector_2D& v2);
	friend Vector_2D& operator/(Vector_2D& v1, const Vector_2D& v2);

	Vector_2D& operator+=(const Vector_2D& vec);
	Vector_2D& operator-=(const Vector_2D& vec);
	Vector_2D& operator*=(const Vector_2D& vec);
	Vector_2D& operator/=(const Vector_2D& vec);

	friend bool& operator==(Vector_2D& v1, const Vector_2D& v2);
	friend bool& operator!=(Vector_2D& v1, const Vector_2D& v2);

	Vector_2D& operator*(const int& i);
	Vector_2D& zero();

	friend std::ostream& operator<<(std::ostream& stream, const Vector_2D& vec);

};

