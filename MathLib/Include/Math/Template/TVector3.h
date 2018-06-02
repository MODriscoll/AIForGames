#pragma once

// First draft

#include <type_traits>

// Template Vector3 class, only accepts numerical types
template <typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
class TVector3
{
public:

	// ----- VARIABLES ----- \\

	T x, y, z;


	// ----- INITIALISER ----- \\

	TVector3()
		: x(static_cast<T>(0)), y(static_cast<T>(0)), z(static_cast<T>(0)) { }
	TVector3(T a_X, T a_Y, T a_Z)
		: x(a_X), y(a_Y), z(a_Z) { }
	TVector3(const TVector3& a_Copy)
		: x(a_Copy.x), y(a_Copy.y), z(a_Copy.z) { }
	TVector3(TVector3&& a_Move) = default;

	~TVector3() = default;


	// ----- FUNCTIONS ----- \\

	void Negate()		 { *this *= static_cast<T>(-1); }	//Negate this vector
	void Normalise()	 { *this /= Magnitude(); }			//Normalise this vector
	void Perpendicular() { *this = x > z ? TVector3(y, -x, static_cast<T>(0)) : TVector3(static_cast<T>(0), -z, y); }


	// ----- CALCULATIONS ----- \\

	//Get the cross product between this vector and another
	TVector3 Cross(const TVector3& a_v) const
	{
		//Return the cross product vector of these vectors
		return TVector3((y * a_v.z - z * a_v.y),
						(z * a_v.x - x * a_v.z),
			            (x * a_v.y - y * a_v.x));
	}

	//Get the dot product between this vector and another
	T Dot(const TVector3& a_v) const
	{
		//Return the dot product of these vectors
		return (x * a_v.x) + (y * a_v.y) + (z * a_v.z);
	}

	//Gets a negated version of this vector
	TVector3 GetNegate() const
	{
		// Create the vector to return and set it as this vector
		TVector3 rvec = *this;

		//Negate this vector
		rvec.Negate();

		//Return the negated vector
		return rvec;
	}

	//Gets a normalised version of this vector
	TVector3 GetNormalise() const
	{
		//Create the vector to return and set it as this vector
		TVector3 rvec = *this;

		//Normalise the vector
		rvec.Normalise();

		//Return the normalised vector
		return rvec;
	}

	//Generates a vector perpendicular to this vector
	TVector3 GetPerpendicular() const
	{
		// Create the vector to return and set it as this vector
		TVector3 rvec = *this;

		//Get the perpendicular version of this vector
		rvec.Perpendicular();

		//Return the perpendicular vector
		return rvec;
	}

	//Get the magnitude of this vector
	T Magnitude() const { return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2)); }

	//Set this vector to the given values
	void Set(T a_X, T a_Y, T a_Z) { x = a_X; y = a_Y; z = a_Z; }


	// ----- OPERATORS ----- \\

	bool operator == (const TVector3& rhs) const { return x == rhs.x && y == rhs.y && z == rhs.z; }
	bool operator != (const TVector3& rhs) const { return !(*this == rhs); }

	TVector3& operator = (const TVector3& rhs) { x = rhs.x, y = rhs.y; z = rhs.z; return *this; }
	TVector3& operator = (TVector3&& rhs) = default;

	TVector3 operator + (const TVector3& rhs) { return TVector3(x + rhs.x, y + rhs.y, z + rhs.z); }
	TVector3 operator - (const TVector3& rhs) { return TVector3(x - rhs.x, y - rhs.y, z - rhs.z); }

	TVector3 operator * (const TVector3& rhs) { return TVector3(x * rhs.x, y * rhs.y, z * rhs.z); }
	TVector3 operator * (const T rhs) { return TVector3(x * rhs, y * rhs, z * rhs); }
	TVector3 operator / (const TVector3& rhs) { return TVector3(x / rhs.x, y / rhs.y, z / rhs.y); }
	TVector3 operator / (const T rhs) { return TVector3(x / rhs, y / rhs, z / rhs); }

	// These consts are for the static functions \\

	const TVector3 operator + (const TVector3& rhs) const { return TVector3(x + rhs.x, y + rhs.y, z + rhs.z); }
	const TVector3 operator - (const TVector3& rhs) const { return TVector3(x - rhs.x, y - rhs.y, z - rhs.z); }

	const TVector3 operator * (const TVector3& rhs) const { return TVector3(x * rhs.x, y * rhs.y, z * rhs.z); }
	const TVector3 operator * (const T rhs) const { return TVector3(x * rhs, y * rhs, z * rhs); }
	const TVector3 operator / (const TVector3& rhs) const { return TVector3(x / rhs.x, y / rhs.y, z / rhs.z); }
	const TVector3 operator / (const T rhs) const { return TVector3(x / rhs, y / rhs, z / rhs); }

	// ----------------------------------------- \\

	TVector3& operator += (const TVector3& rhs) { return *this = *this + rhs; }
	TVector3& operator -= (const TVector3& rhs) { return *this = *this - rhs; }

	TVector3& operator *= (const TVector3& rhs) { return *this = *this * rhs; }
	TVector3& operator *= (const T rhs) { return *this = *this * rhs; }
	TVector3& operator /= (const TVector3& rhs) { return *this = *this / rhs; }
	TVector3& operator /= (const T rhs) { return *this = *this / rhs; }

	TVector3& operator ++ () { ++x; ++y; ++z; return *this; }
	TVector3& operator -- () { --x; --y; --z; return *this; }
	TVector3 operator ++ (int) { return TVector3(x++, y++, z++); }
	TVector3 operator -- (int) { return TVector3(x--, y--, z--); }

	void operator() (T a_X, T a_Y, T a_Z) { x = a_X; y = a_Y; z = a_Z; };
	void operator() (const TVector3& rhs) { x = rhs.x; y = rhs.y; z = rhs.z; }

	// Cast to T* has to
	// explicitly called
	explicit operator T*() { return &x; }

	T& operator[] (int idx) { return ((T*)this)[idx]; }
	const T& operator[] (int idx) const { return ((T*)this)[idx]; }
};

template <typename T>
static TVector3<T> operator * (const T lhs, const TVector3<T>& rhs) { return TVector3<T>(lhs * rhs.x, lhs * rhs.y, lhs * rhs.z); }
template <typename T>
static TVector3<T> operator / (const T lhs, const TVector3<T>& rhs) { return TVector3<T>(lhs / rhs.x, lhs / rhs.y, lhs / rhs.z); }

template <typename T>
static TVector3<T>& operator *= (const T lhs, const TVector3<T>& rhs) { return rhs = lhs * rhs; }
template <typename T>
static TVector3<T>& operator /= (const T lhs, const TVector3<T>& rhs) { return rhs = lhs * rhs; }
