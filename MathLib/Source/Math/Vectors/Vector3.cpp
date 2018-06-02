#include "Math\Vectors\Vector3.h"

#include "Math\Vectors\Vector2.h"
#include "Math\Vectors\Vector4.h"

#include "Math\Maths.h"

//Default constructor
Vector3::Vector3(float a_X, float a_Y, float a_Z)
	: x(a_X), y(a_Y), z(a_Z) { }

//Copy constructor
Vector3::Vector3(const Vector3& a_Copy)
	: x(a_Copy.x), y(a_Copy.y), z(a_Copy.z) { }

//Get the magnitude of this vector
float Vector3::Magnitude() const
{
	//Combine then square root all axes
	return sqrtf(fpowf(x, 2) + fpowf(y, 2) + fpowf(z, 2));
}

//Normalise this vector
void Vector3::Normalise()
{
	//Scale this vector by its magnitude
	*this /= Magnitude();
}

//Get a normalised version of this vector
Vector3 Vector3::GetNormalise() const
{
	//Create the vector to return and set it as this vector
	Vector3 rvec = *this;

	//Normalise the vector
	rvec.Normalise();

	//Return the normalised vector
	return rvec;
}

//Set this vectors values
void Vector3::Set(float a_X, float a_Y, float a_Z)
{
	x = a_X; y = a_Y; z = a_Z;
}

//Find the cross product between two vectors
Vector3 Vector3::Cross(const Vector3& a_v1, const Vector3& a_v2)
{
	//Return the cross product vector of these vectors
	return Vector3((a_v1.y * a_v2.z - a_v1.z * a_v2.y), 
				   (a_v1.z * a_v2.x - a_v1.x * a_v2.z), 
				   (a_v1.x * a_v2.y - a_v1.y * a_v2.x));
}

//Find the displacement between two vectors
Vector3 Vector3::Displacement(const Vector3& a_v1, const Vector3& a_v2)
{
	//Return the first vector minused by the second vector
	return Vector3((a_v1.x - a_v2.x),
				   (a_v1.y - a_v2.y),
				   (a_v1.z - a_v2.z));
}

//Find the dot product between two vectors
float Vector3::Dot(const Vector3& a_v1, const Vector3& a_v2)
{
	//Return the dot product of these vectors
	return (a_v1.x * a_v2.x) + (a_v1.y * a_v2.y) + (a_v1.z * a_v2.z);
}

//Find the point between two vectors based on time
Vector3 Vector3::Lerp(const Vector3& a_start, const Vector3& a_end, float time)
{
	//Lerp each axis and return them as a vector
	return Vector3(lerpf(a_start.x, a_end.x, time), lerpf(a_start.y, a_end.y, time), lerpf(a_start.z, a_end.z, time));
}

//Does equal operator
bool Vector3::operator==(const Vector3& rhs) const
{
	return x == rhs.x && y == rhs.y && z == rhs.z;
}

//Does not equal operator
bool Vector3::operator!=(const Vector3& rhs) const
{
	return !(*this == rhs);
}

//Equal operator
Vector3& Vector3::operator=(const Vector3& rhs)
{
	x = rhs.x; y = rhs.y; z = rhs.z; return *this;
}

//Addition operator
Vector3 Vector3::operator+(const Vector3& rhs)
{
	return Vector3(x + rhs.x, y + rhs.y, z + rhs.z);
}

//Compound addition operator
Vector3& Vector3::operator+=(const Vector3& rhs)
{
	return *this = *this + rhs;
}

//Subtraction operator
Vector3 Vector3::operator-(const Vector3& rhs)
{
	return Vector3(x - rhs.x, y - rhs.y, z - rhs.z);
}

//Compound subtraction operator
Vector3& Vector3::operator-=(const Vector3& rhs)
{
	return *this = *this - rhs;
}

//Multiplication operator
Vector3 Vector3::operator*(const Vector3& rhs)
{
	return Vector3(x * rhs.x, y * rhs.y, z * rhs.z);
}

//Float multiplication operator
Vector3 Vector3::operator*(const float rhs)
{
	return Vector3(x * rhs, y * rhs, z * rhs);
}

//Compound multiplication operator
Vector3& Vector3::operator*=(const Vector3& rhs)
{
	return *this = *this * rhs;
}

//Float compound multiplication operator
Vector3& Vector3::operator*=(const float rhs)
{
	return *this = *this * rhs;
}

//Division operator
Vector3 Vector3::operator/(const Vector3& rhs)
{
	return Vector3(x / rhs.x, y / rhs.y, z / rhs.z);
}

//Float division operator
Vector3 Vector3::operator/(const float rhs)
{
	return Vector3(x / rhs, y / rhs, z / rhs);
}

//Compound division operator
Vector3& Vector3::operator/=(const Vector3& rhs)
{
	return *this = *this / rhs;
}

//Float compound division operator
Vector3& Vector3::operator/=(const float rhs)
{
	return *this = *this / rhs;
}

//Post-Increment
Vector3& Vector3::operator++()
{
	++x, ++y, ++z; return *this;
}

//Post-Decrement
Vector3& Vector3::operator--()
{
	--x, --y, --z; return *this;
}

//Pre-Increment
Vector3 Vector3::operator++(int)
{
	Vector3 r = *this; ++*this; return r;
}

//Pre-Decrement
Vector3 Vector3::operator--(int)
{
	Vector3 r = *this; --*this; return r;
}

//Float operator ( Set )
void Vector3::operator()(float a_X, float a_Y, float a_Z)
{
	x = a_X; y = a_Y; z = a_Z;
}

//Vector3 operator
void Vector3::operator()(const Vector3& rhs)
{
	*this = rhs;
}

//Float pointer conversion operator
Vector3::operator float*()
{
	return &x;
}

//Vector2 conversion operator
Vector3::operator Vector2()
{
	return Vector2(x, y);
}

//Vector4 conversion operator
Vector3::operator Vector4()
{
	return Vector4(x, y, z, 0);
}

//Array operator
float& Vector3::operator[](int idx)
{
	return ((float*)this)[idx];
}

//Const array operator
const float& Vector3::operator[](int idx) const
{
	return ((float*)this)[idx];
}