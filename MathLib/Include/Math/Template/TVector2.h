#pragma once

// First draft

#include <type_traits>

// Template Vector2 class, only accepts numerical types
template <typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
class TVector2
{
public:

	// ----- VARIABLES ----- \\

	T x, y;


	// ----- INITIALISER ----- \\

	TVector2()
		: x(static_cast<T>(0)), y(static_cast<T>(0)) { }
	TVector2(T a_X, T a_Y)
		: x(a_X), y(a_Y) { }
	TVector2(const TVector2& a_Copy)
		: x(a_Copy.x), y(a_Copy.y) { }
	TVector2(TVector2&& a_Move) = default;

	~TVector2() = default;


	// ----- FUNCTIONS ----- \\

	void Negate()		 { *this *= static_cast<T>(-1); }	//Negate this vector
	void Normalise()	 { *this /= Magnitude(); }			//Normalise this vector
	void Perpendicular() { *this = TVector2(y, -x); }		//Convert this vector into a perpendicular of itself


	// ----- CALCULATIONS ----- \\

	//Get the dot product between this vector and another
	T Dot(const TVector2& a_v) const
	{
		//Return the dot product of these vectors
		return (x * a_v.x) + (y * a_v.y);
	}

	//Gets a negated version of this vector
	TVector2 GetNegate() const
	{
		// Create the vector to return and set it as this vector
		TVector2 rvec = *this;

		//Negate this vector
		rvec.Negate();

		//Return the negated vector
		return rvec;
	}

	//Gets a normalised version of this vector
	TVector2 GetNormalise() const
	{
		//Create the vector to return and set it as this vector
		TVector2 rvec = *this;

		//Normalise the vector
		rvec.Normalise();

		//Return the normalised vector
		return rvec;
	}

	//Generates a vector perpendicular to this vector
	TVector2 GetPerpendicular() const
	{
		// Create the vector to return and set it as this vector
		TVector2 rvec = *this;

		//Get the perpendicular version of this vector
		rvec.Perpendicular();

		//Return the perpendicular vector
		return rvec;
	}

	//Get the magnitude of this vector
	T Magnitude() const { return sqrt(pow(x, 2) + pow(y, 2)); }

	//Set this vector to the given values
	void Set(T a_X, T a_Y) { x = a_X; y = a_Y; }


	// ----- STATIC FUNCTIONS ----- \\

	//Create a direction vector using radians given
	static TVector2 Direction(T rad)
	{
		//Cos the radians for X and sin for Y
		return TVector2(cos(rad), sin(rad));
	}

	//Calculate the triple product between three vectors
	static TVector2 TripleProduct(const TVector2& a_v1, const TVector2& a_v2, const TVector2& a_v3)
	{
		//Calculated the triple product of these vectors
		return a_v2 * a_v3.Dot(a_v1) - a_v1 * a_v3.Dot(a_v2);
	}


	// ----- OPERATORS ----- \\

	bool operator == (const TVector2& rhs) const { return x == rhs.x && y == rhs.y }
	bool operator != (const TVector2& rhs) const { return !(*this == rhs); }

	TVector2& operator = (const TVector2& rhs) { x = rhs.x, y = rhs.y; return *this; }
	TVector2& operator = (TVector2&& rhs) = default;

	TVector2 operator + (const TVector2& rhs) { return TVector2(x + rhs.x, y + rhs.y); }
	TVector2 operator - (const TVector2& rhs) { return TVector2(x - rhs.x, y - rhs.y); }

	TVector2 operator * (const TVector2& rhs) { return TVector2(x * rhs.x, y * rhs.y); }
	TVector2 operator * (const T rhs)		  { return TVector2(x * rhs, y * rhs); }
	TVector2 operator / (const TVector2& rhs) { return TVector2(x / rhs.x, y / rhs.y); }
	TVector2 operator / (const T rhs)		  { return TVector2(x / rhs, y / rhs); }

	// These consts are for the static functions \\

	const TVector2 operator + (const TVector2& rhs) const { return TVector2(x + rhs.x, y + rhs.y); }
	const TVector2 operator - (const TVector2& rhs) const { return TVector2(x - rhs.x, y - rhs.y); }

	const TVector2 operator * (const TVector2& rhs) const { return TVector2(x * rhs.x, y * rhs.y); }
	const TVector2 operator * (const T rhs) const		  { return TVector2(x * rhs, y * rhs); }
	const TVector2 operator / (const TVector2& rhs) const { return TVector2(x / rhs.x, y / rhs.y); }
	const TVector2 operator / (const T rhs) const		  { return TVector2(x / rhs, y / rhs); }

	// ----------------------------------------- \\

	TVector2& operator += (const TVector2& rhs) { return *this = *this + rhs; }
	TVector2& operator -= (const TVector2& rhs) { return *this = *this - rhs; }

	TVector2& operator *= (const TVector2& rhs) { return *this = *this * rhs; }
	TVector2& operator *= (const T rhs)			{ return *this = *this * rhs; }
	TVector2& operator /= (const TVector2& rhs) { return *this = *this / rhs; }
	TVector2& operator /= (const T rhs)			{ return *this = *this / rhs; }

	TVector2& operator ++ ()	{ ++x; ++y; return *this; }
	TVector2& operator -- ()	{ --x; --y; return *this; }
	TVector2 operator ++ (int)	{ return TVector2(x++, y++); }
	TVector2 operator -- (int)	{ return TVector2(x--, y--); }

	void operator() (T a_X, T a_Y)		  { x = a_X; y = a_Y; }
	void operator() (const TVector2& rhs) { x = rhs.x; y = rhs.y; }

	// Cast to T* has to
	// explicitly called
	explicit operator T*() { return &x; }

	T& operator[] (int idx)				{ return ((T*)this)[idx]; }
	const T& operator[] (int idx) const { return ((T*)this)[idx]; }
};

template <typename T>
static TVector2<T> operator * (const T lhs, const TVector2<T>& rhs) { return TVector2<T>(lhs * rhs.x, lhs * rhs.y); }
template <typename T>
static TVector2<T> operator / (const T lhs, const TVector2<T>& rhs) { return TVector2<T>(lhs / rhs.x, lhs / rhs.y); }

template <typename T>
static TVector2<T>& operator *= (const T lhs, const TVector2<T>& rhs) { return rhs = lhs * rhs; }
template <typename T>
static TVector2<T>& operator /= (const T lhs, const TVector2<T>& rhs) { return rhs = lhs * rhs; }