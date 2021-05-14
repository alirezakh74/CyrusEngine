#pragma once

class Vector2D
{

public:

	Vector2D(float x = 0, float y = 0);
	~Vector2D();

	void setX(float x);
	float getX() const;
	void setY(float y);
	float getY() const;

	float length();
	void normalize();

	Vector2D operator+(const Vector2D& v2) const;
	friend Vector2D& operator+=(Vector2D& v1, const Vector2D& v2);

	Vector2D operator-(const Vector2D& v2) const;
	friend Vector2D& operator-=(Vector2D& v1, const Vector2D& v2);

	Vector2D operator*(float scalar);
	Vector2D& operator*=(float scalar);

	Vector2D operator/(float scalar);
	Vector2D& operator/=(float scalar);

private:

	float m_x;
	float m_y;
};

