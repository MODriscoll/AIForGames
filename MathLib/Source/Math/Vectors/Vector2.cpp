#include "Math\Vectors\Vector2.h"

#include "Math\Vectors\Vector3.h"
#include "Math\Vectors\Vector4.h"

#include "Math\Maths.h"

//Default constructor
Vector2::Vector2(float a_X, float a_Y)
	: x(a_X), y(a_Y) { }

//Get the magnitude of this vector
float Vector2::Magnitude() const
{
	//Combine then square root all axes
	return sqrtf(Squared());
}

//Get the radian value of this vector
float Vector2::Radians() const
{
	//Calculate and return the angle
	return atan2f(y, x);
}

//Get the distance squared of this vector
float Vector2::Squared() const
{
	//Get the sum of each axes squared
	return fpowf(x, 2) + fpowf(y, 2);
}

//Negate this vector
void Vector2::Negate()
{
	// Negate both axis
	x = -x; y = -y;
}

//Normalise this vector
void Vector2::Normalise()
{
	// Get the magnitude
	float Mag = Magnitude();

	//Scale this vector by its magnitude
	*this /= !Mag ? float_limits::epsilon() : Mag;
}

//Convert this vector to a perpendicular version of itself
void Vector2::Perpendicular()
{
	//Switch the x and y value and negate the 'y' axis
	*this = Vector2(y, -x);
}

//Convert the values of each axes to positive
void Vector2::Positivize()
{
	//Convert each axis to positive
	x = +x; y = +y;
}

//Get the projection of this vector onto the other
Vector2 Vector2::Projection(const Vector2& rhs) const
{
	//Calculate the projection vector then return
	return Vector2((Dot(*this, rhs) / (rhs.x * rhs.x + rhs.y * rhs.y)) * rhs.x,
				   (Dot(*this, rhs) / (rhs.x * rhs.x + rhs.y * rhs.y)) * rhs.y);
}

//Get the scaler projection of this vector onto the other
float Vector2::ScalarProjection(const Vector2& rhs) const
{
	// Calculate the scalar projection then return
	return (Dot(*this, rhs) / Magnitude());
}

//Get a negated version of this vector
Vector2 Vector2::GetNegate() const
{
	//Create the vector to return and set it as this vector
	Vector2 rvec = *this;

	//Negate the vector
	rvec.Negate();

	//Return the negated vector
	return rvec;
}

//Get a normalised version of this vector
Vector2 Vector2::GetNormalise() const
{
	//Create the vector to return and set it as this vector
	Vector2 rvec = *this;

	//Normalise the vector
	rvec.Normalise();

	//Return the normalised vector
	return rvec;
}

//Get a vector perpendicular to this vector
Vector2 Vector2::GetPerpendicular() const
{
	// Create the vector to return and set it as this vector
	Vector2 rvec = *this;

	//Get the perpendicular version of this vector
	rvec.Perpendicular();

	//Return the perpendicular vector
	return rvec;
}

//Get a positivized version of this vector
Vector2 Vector2::GetPositivize() const
{
	// Create the vector to return and set it as this vector
	Vector2 rvec = *this;

	//Get the positivized version of this vector
	rvec.Positivize();

	//Return the perpendicular vector
	return rvec;
}

//Clamp this vector within the given range
void Vector2::Clamp(const Vector2& a_min, const Vector2& a_max)
{
	// Clamp both axes
	x = clampf(a_min.x, a_max.x, x);
	y = clampf(a_min.y, a_max.y, y);
}

//Set this vectors values
void Vector2::Set(float a_X, float a_Y)
{
	// Set the values
	x = a_X; y = a_Y;
}

//Truncate this vector using given magnitude
void Vector2::Truncate(float a_magnitude)
{
	//Get value of given magnitude divided by this magnitude
	float ratio = a_magnitude / Magnitude();

	// Scale this vector by lower value
	*this *= ratio > 1.f ? 1.f : ratio;
}

//Find point along quadratic bezier curve at given time
Vector2 Vector2::Bezier(const Vector2& a_p1, const Vector2& a_p2, const Vector2& a_p3, float time)
{
	//Get time squared
	float ts = time * time;

	//Get the polynomial values
	float lp = 1.f - time;
	float sp = lp * lp;

	// Calculate and return the point along the curve
	return (a_p1 * sp) + (a_p2 * 2.f * lp * time) + (a_p3 * ts);
}

//Find point along cubic bezier curve at given time
Vector2 Vector2::Bezier(const Vector2& a_p1, const Vector2& a_p2, const Vector2& a_p3, const Vector2& a_p4, float time)
{
	//Get time squared and cubed
	float ts = time * time;
	float tc = ts * time;

	//Get the polynomial values
	float lp = 1.f - time;
	float sp = lp * lp;
	float cp = sp * lp;

	//Calculate and return the point along the curve
	return (a_p1 * cp) + (3.f * a_p2 * sp * time) + (3.f * a_p3 * lp * ts) + (a_p4 * tc);
}

//Calculate the cardinal spline of the three given points
Vector2 Vector2::Cardinal(const Vector2& a_p1, const Vector2& a_p2, const Vector2& a_p3, float alpha, float time)
{
	// Calculate the tangents
	Vector2 t1 = (a_p2 - a_p1) * alpha;
	Vector2 t2 = (a_p3 - a_p2) * alpha;

	// Calculate the rest using hermite
	return Hermite(a_p1, a_p2, t1, t2, time);
}

//Return the cross product ( Z axis ) between two vectors
float Vector2::CrossZ(const Vector2& a_v1, const Vector2& a_v2)
{
	// Calculate the cross product and return it
	return (a_v1.x * a_v2.y) - (a_v2.x * a_v1.y);
}

//Return a vector facing the given direction
Vector2 Vector2::Direction(float rad)
{
	//Cos the radians for X and sin for Y
	return Vector2(cosf(rad), sinf(rad));
}

//Find the displacement between two vectors
Vector2 Vector2::Displacement(const Vector2& a_v1, const Vector2& a_v2)
{
	//Return the first vector minused by the second vector
	return a_v1 - a_v2;
}

//Find distance between two vectors
float Vector2::Distance(const Vector2& a_p1, const Vector2& a_p2)
{
	// Calculate and return the distance between these vectors
	return sqrtf(fpowf(a_p2.x - a_p1.x, 2) + fpowf(a_p2.y - a_p1.y, 2));
}

//Find the dot product between two vectors
float Vector2::Dot(const Vector2& a_v1, const Vector2& a_v2)
{
	//Return the dot product of these vectors
	return (a_v1.x * a_v2.x) + (a_v1.y * a_v2.y);
}

//Calculate the hermite curve using points and tangents
Vector2 Vector2::Hermite(const Vector2& a_p1, const Vector2& a_p2, const Vector2& a_t1, const Vector2& a_t2, float time)
{
	//Get time squared and cubed
	float ts = time * time;
	float tc = ts * time;

	//Use the four basis functions to help calculate positions
	float h00 = 2.f * tc - 3.f * ts + 1;
	float h01 = -2.f * tc + 3.f * ts;
	float h10 = tc - 2.f * ts + time;
	float h11 = tc - ts;

	//Calculate and return hermite curve
	return h00 * a_p1 + h10 * a_t1 + h01 * a_p2 + h11 * a_t2;
}

//Find the point between two vectors using linear interpolation
Vector2 Vector2::Lerp(const Vector2& a_start, const Vector2& a_end, float time)
{
	//Lerp each axis and return them as a vector
	return a_start + (time * (a_end - a_start));
}

//Find the point between range of vectors using linear interpolation
Vector2 Vector2::RLerp(const Vector2* const a_points, size_t a_size, float time) 
{
	// Return if array is empty
	if (a_size == 0) { return Vector2(); }

	// Create buffer vector array, set it to size given
	Vector2* buffer = new Vector2[a_size];

	// Copy the given array into the buffer
	memcpy(buffer, a_points, sizeof(Vector2) * a_size);

	// Repeat until only one point remains
	while (a_size > 1)
	{
		// Repeat based on how many points are left
		for (size_t i = 0; i < a_size - 1; ++i)
		{
			// Set this index of the buffer to new lerped value
			buffer[i] = Lerp(buffer[i], buffer[i + 1], time);
		}

		// Decrease the size
		--a_size;
	}

	// After every lerp, the front value
	// should be the final lerped value
	Vector2 RVec = buffer[0];

	// Delete the buffer
	delete[] buffer;

	// Return the lerped value
	return RVec;
}

//Calcualte the triple product of three given vectors
Vector2 Vector2::TripleProduct(const Vector2& a_v1, const Vector2& a_v2, const Vector2& a_v3)
{
	//Calculated the triple product of these vectors
	return a_v2 * Dot(a_v3, a_v1) - a_v1 * Dot(a_v3, a_v2);
}

//Does equal operator
bool Vector2::operator==(const Vector2& rhs) const
{
	return x == rhs.x && y == rhs.y;
}

//Does not equal operator
bool Vector2::operator!=(const Vector2& rhs) const
{
	return !(*this == rhs);
}

//Const addition operator
Vector2 Vector2::operator+(const Vector2& rhs) const
{
	return Vector2(x + rhs.x, y + rhs.y);
}

//Const positivise operator
Vector2 Vector2::operator+() const
{
	return Vector2(+x, +y);
}

//Compound addition operator
Vector2& Vector2::operator+=(const Vector2& rhs)
{
	return *this = *this + rhs;
}

//Const subtraction operator
Vector2 Vector2::operator-(const Vector2& rhs) const
{
	return Vector2(x - rhs.x, y - rhs.y);
}

//Const negate operator
Vector2 Vector2::operator-() const
{
	return Vector2(-x, -y);
}

//Compound subtraction operator
Vector2& Vector2::operator-=(const Vector2& rhs)
{
	return *this = *this - rhs;
}

//Const multiplication operator
Vector2 Vector2::operator*(const Vector2& rhs) const
{
	return Vector2(x * rhs.x, y * rhs.y);
}

//Const float multiplication operator
Vector2 Vector2::operator*(const float rhs) const
{
	return Vector2(x * rhs, y * rhs);
}

//Compound multiplication operator
Vector2& Vector2::operator*=(const Vector2& rhs)
{
	return *this = *this * rhs;
}

//Float compound multiplication operator
Vector2& Vector2::operator*=(const float rhs)
{
	return *this = *this * rhs;
}

//Const division operator
Vector2 Vector2::operator/(const Vector2& rhs) const
{
	return Vector2(x / rhs.x, y / rhs.y);
}

//Const float division operator
Vector2 Vector2::operator/(const float rhs) const
{
	return Vector2(x / rhs, y / rhs);
}

//Const modulus operator
Vector2 Vector2::operator%(const Vector2& rhs) const
{
	return Vector2(fmodf(x, rhs.x), fmodf(y, rhs.y));
}

//Const float modulus operator
Vector2 Vector2::operator%(const float rhs) const
{
	return Vector2(fmodf(x, rhs), fmodf(y, rhs));
}

//Compound division operator
Vector2& Vector2::operator/=(const Vector2& rhs)
{
	return *this = *this / rhs;
}

//Float compound division operator
Vector2& Vector2::operator/=(const float rhs)
{
	return *this = *this / rhs;
}

//Compound modulus operator
Vector2& Vector2::operator%=(const Vector2& rhs)
{
	return *this = *this % rhs;
}

//Float compound modulus operator
Vector2& Vector2::operator%=(const float rhs)
{
	return *this = *this % rhs;
}

//Pre-Increment
Vector2& Vector2::operator++()
{
	++x; ++y; return *this;
}

//Pre-Decrement
Vector2& Vector2::operator--()
{
	--x, --y; return *this;
}

//Post-Increment
Vector2 Vector2::operator++(int)
{
	Vector2 r = *this; ++*this; return r;
}

//Post-Decrement
Vector2 Vector2::operator--(int)
{
	Vector2 r = *this; --*this; return r;
}

//Float operator ( Set )
void Vector2::operator()(float a_X, float a_Y)
{
	x = a_X; y = a_Y;
}

//Vector2 operator
void Vector2::operator()(const Vector2& rhs)
{
	*this = rhs;
}

//Float pointer conversion operator
Vector2::operator float*()
{
	return &x;
}

//Vector3 conversion operator
Vector2::operator Vector3()
{
	return Vector3(x, y, 0.f);
}

//Vector4 conversion operator
Vector2::operator Vector4()
{
	return Vector4(x, y, 0.f, 0.f);
}

//Array operator
float& Vector2::operator[](int idx)
{
	return ((float*)this)[idx];
}

//Const array operator
const float& Vector2::operator[](int idx) const
{
	return ((float*)this)[idx];
}