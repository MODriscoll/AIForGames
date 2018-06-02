#include "Math\Vectors\Vector4.h"

#include "Math\Vectors\Vector2.h"
#include "Math\Vectors\Vector3.h"

#include "Math\Maths.h"

//Default constructor
Vector4::Vector4(float a_X, float a_Y, float a_Z, float a_W)
	: x(a_X), y(a_Y), z(a_Z), w(a_W) { }

//Copy constructor
Vector4::Vector4(const Vector4& a_Copy)
	: x(a_Copy.x), y(a_Copy.y), z(a_Copy.z), w(a_Copy.w) { }

//Get the magnitude of this vector
float Vector4::Magnitude() const
{
	//Combine then square root all axes
	return sqrtf(fpowf(x, 2) + fpowf(y, 2) + fpowf(z, 2) + fpowf(w, 2));
}

//Normalise this vector
void Vector4::Normalise()
{
	//Scale this vector by its magnitude
	*this /= Magnitude();
}

//Get a normalised version of this vector
Vector4 Vector4::GetNormalise() const
{
	//Create the vector to return and set it as this vector
	Vector4 rvec = *this;

	//Normalise the vector
	rvec.Normalise();

	//Return the normalised vector
	return rvec;
}

//Set this vectors values
void Vector4::Set(float a_X, float a_Y, float a_Z, float a_W)
{
	x = a_X; y = a_Y; z = a_Z; w = a_W;
}

//Find the cross product between two vectors
Vector4 Vector4::Cross(const Vector4& a_v1, const Vector4& a_v2)
{
	//Return the cross product vector of these vectors
	return Vector4((a_v1.y * a_v2.z - a_v1.z * a_v2.y),
				   (a_v1.z * a_v2.x - a_v1.x * a_v2.z),
				   (a_v1.x * a_v2.y - a_v1.y * a_v2.x),
				   (a_v1.w * a_v2.w - a_v1.w * a_v2.w));
}

//Find the dot product between two vectors
float Vector4::Dot(const Vector4& a_v1, const Vector4& a_v2)
{
	//Return the dot product of these vectors
	return (a_v1.x * a_v2.x) + (a_v1.y * a_v2.y) + (a_v1.z * a_v2.z) + (a_v1.w *a_v2.w);
}

//Does equal operator
bool Vector4::operator==(const Vector4& rhs) const
{
	return x == rhs.x && y == rhs.y && z == rhs.z && w == rhs.w;
}

//Does not equal operator
bool Vector4::operator!=(const Vector4& rhs) const
{
	return !(*this == rhs);
}

//Equal operator
Vector4& Vector4::operator=(const Vector4& rhs)
{
	x = rhs.x, y = rhs.y, z = rhs.z, w = rhs.w; return *this;
}

//Addition operator
Vector4 Vector4::operator+(const Vector4& rhs)
{
	return Vector4(x + rhs.x, y + rhs.y, z + rhs.z, w + rhs.w);
}

//Compound addition operator
Vector4& Vector4::operator+=(const Vector4& rhs)
{
	return *this = *this + rhs;
}

//Subtraction operator
Vector4 Vector4::operator-(const Vector4& rhs)
{
	return Vector4(x - rhs.x, y - rhs.y, z - rhs.z, w - rhs.w);
}

//Compound subtraction operator
Vector4& Vector4::operator-=(const Vector4& rhs)
{
	return *this = *this - rhs;
}

//Multiplication operator
Vector4 Vector4::operator*(const Vector4& rhs)
{
	return Vector4(x * rhs.x, y * rhs.y, z * rhs.z, w * rhs.w);
}

//Float multiplication operator
Vector4 Vector4::operator*(const float rhs)
{
	return Vector4(x * rhs, y * rhs, z * rhs, w * rhs);
}

//Compound multiplication operator
Vector4& Vector4::operator*=(const Vector4& rhs)
{
	return *this = *this * rhs;
}

//Float compound multiplication operator
Vector4& Vector4::operator*=(const float rhs)
{
	return *this = *this * rhs;
}

//Division operator
Vector4 Vector4::operator/(const Vector4& rhs)
{
	return Vector4(x / rhs.x, y / rhs.y, z / rhs.z, w / rhs.w);
}

//Float division operator
Vector4 Vector4::operator/(const float rhs)
{
	return Vector4(x / rhs, y / rhs, z / rhs, w / rhs);
}

//Compound division operator
Vector4& Vector4::operator/=(const Vector4& rhs)
{
	return *this = *this / rhs;
}

//Float compound division operator
Vector4& Vector4::operator/=(const float rhs)
{
	return *this = *this / rhs;
}

//Post-Increment
Vector4& Vector4::operator++()
{
	++x, ++y, ++z, ++w; return *this;
}

//Post-Decrement
Vector4& Vector4::operator--()
{
	--x, --y, --z, --w; return *this;
}

//Pre-Increment
Vector4 Vector4::operator++(int)
{
	Vector4 r = *this; ++*this; return r;
}

//Pre-Decrement
Vector4 Vector4::operator--(int)
{
	Vector4 r = *this; --*this; return r;
}

//Float operator ( Set )
void Vector4::operator()(float a_X, float a_Y, float a_Z, float a_W)
{
	x = a_X; y = a_Y; z = a_Z; w = a_W;
}

//Vector4 operator
void Vector4::operator()(const Vector4& rhs)
{
	*this = rhs;
}

//Float pointer conversion operator
Vector4::operator float*()
{
	return &x;
}

//Vector2 conversion operator
Vector4::operator Vector2()
{
	return Vector2(x, y);
}

//Vector3 conversion operator
Vector4::operator Vector3()
{
	return Vector3(x, y, z);
}

//Array operator
float& Vector4::operator[](int idx)
{
	return ((float*)this)[idx];
}

//Const array operator
const float& Vector4::operator[](int idx) const
{
	return ((float*)this)[idx];
}