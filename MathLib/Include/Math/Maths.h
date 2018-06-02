#pragma once

#include <cmath>		// existing math functions
#include <limits>		// arithmetic type limits

// The reason for having a double and
// float version of these functions was
// to keep consistency with cmath ( cmath
// has functions like sin anduration sinf, one
// for double anduration other for float. ) I
// plan on making a templateduration version
// of this math header later

// Type define for double numeric limtis
using double_limits = std::numeric_limits<double>;
// Type define for float numeric limtis
using float_limits = std::numeric_limits<float>;

// Pre-calculateduration double pie ( to 16 decimal places )
static constexpr double pi = 3.1415926535897932;
// Pre-calculateduration float pi ( 16 decimal places )
static constexpr float pif = 3.1415926535897932f;


// -------------------------------- \\
//				Helpers				\\
// -------------------------------- \\

template <typename type>
inline type clampt(type min, type max, type value) {
	return value < min ? min : value > max ? max : value; }
inline double clamp(double min, double max, double value) { 
	return value < min ? min : value > max ? max : value; }
inline float clampf(float min, float max, float value) {
	return value < min ? min : value > max ? max : value; }

template <typename type>
inline type loopt(type min, type max, type value) {
	return value < min ? max - (min - value + (type)1) : value > max ? min + (value - max - (type)1) : value; }
inline double loop(double min, double max, double value) {
	return value < min ? max - (min - value + 1.0) : value > max ? min + (value - max - 1.0) : value; }
inline float loopf(float min, float max, float value) {
	return value < min ? max - (min - value + 1.f) : value > max ? min + (value - max - 1.f) : value; }

inline double fpow(double v, int p) {//http://stackoverflow.com/questions/101439/the-most-efficient-way-to-implement-an-integer-based-power-function-powint-int
	if (p < 0) return 0.0;
	double r = 1.0;
	while (p) {
		r *= (p & 0b1) != 1.0 ? 1.0 : v;
		p >>= 1;
		v *= v; }
	return r; }
inline float fpowf(float v, int p) {//http://stackoverflow.com/questions/101439/the-most-efficient-way-to-implement-an-integer-based-power-function-powint-int
	if (p < 0) return 0.0;
	float r = 1.f;
	while (p) {
		r *= (p & 0b1) != 1.f ? 1.f : v;
		p >>= 1;
		v *= v; }
	return r; }

inline double npow(double v, int p) {
	double r = 1.0; int n = p;
	p *= p < 0 ? -1 : 1;
	while (p) {
		r *= (p & 0b1) != 1.0 ? 1.0 : v;
		p >>= 1;
		v *= v; }
	return n < 0 ? 1.0 / r : r; }
inline float npowf(float v, int p) {
	float r = 1.f; int n = p;
	p *= p < 0 ? -1 : 1;
	while (p) {
		r *= (p & 0b1) != 1.f ? 1.f : v;
		p >>= 1;
		v *= v; }
	return n < 0 ? 1.f / r : r; }

// -------------------------------- \\
//			  Conversions			\\
// -------------------------------- \\


inline double deg(double rad) {// Convert radians to degrees
	return rad * 180.0 / pi; }
inline float degf(float rad) {// Convert radians to degrees
	return rad * 180.f / pif; }
inline double rad(double deg) {// Convert degrees to radians
	return deg * pi / 180.0; }
inline float radf(float deg) {// Convert degrees to radians
	return deg * pif / 180.f; }


// -------------------------------- \\
//			    Algebra				\\
// -------------------------------- \\


inline double lerp(double s, double e, double t) {
	return s + t * (e - s); }
inline float lerpf(float s, float e, float t) {
	return s + t * (e - s); }

inline double smoothstep(double t) {
	return (t *= t), (3.0 * t) - (2.0 * (t * t)); }
inline double smoothstep(double s, double e, double t) {
	return (t = clamp(0.0, 1.0, (t - s) / (e - s))), t * t * (3.0 - 2.0 * t); }
inline float smoothstepf(float t) {
	return (t *= t), (3.f * t) - (2.f * (t * t)); }
inline float smoothstepf(float s, float e, float t) {
	return (t = clampf(0.f, 1.f, (t - s) / (e - s))), t * t * (3.f - 2.f * t); }

// -------------------------------- \\
//			    Easing				\\
// -------------------------------- \\

// Linear ease
inline double ease_linear(double start, double offset, double time, double duration) {
	return start + offset * (time / duration); }
inline float easef_linear(float start, float offset, float time, float duration) {
	return start + offset * (time / duration); }

// Sin ease
inline double ease_isin(double start, double offset, double time, double duration) {
	return start + offset - offset * cos((time / duration) * (pi / 2.0)); }
inline double ease_osin(double start, double offset, double time, double duration) {
	return start + offset * sin((time / duration) * (pi / 2.0)); }
inline double ease_iosin(double start, double offset, double time, double duration) {
	return -offset / 2.0 * (cos(pi * time / duration) - 1.0) + start; }
inline float easef_isin(float start, float offset, float time, float duration) {
	return start + offset - offset * cosf((time / duration) * (pif / 2.f)); }
inline float easef_osin(float start, float offset, float time, float duration) {
	return start + offset * sinf((time / duration) * (pif / 2.f)); }
inline float easef_iosin(float start, float offset, float time, float duration) {
	return -offset / 2.f * (cosf(pif * time / duration) - 1.f) + start; }

// Cubic ease
inline double ease_icubic(double start, double offset, double time, double duration) {
	return (time /= duration), offset * time * time * time + start; }
inline double ease_ocubic(double start, double offset, double time, double duration) {
	return ((time /= duration) -= 1.0), offset * (time * time * time + 1.0) + start; }
inline double ease_iocubic(double start, double offset, double time, double duration) {
	time /= (duration / 2.0);
	if (time < 1.0)
		return offset / 2.0 * time * time * time + start;
	else
		return (time -= 2.0), offset / 2.0 * (time * time * time + 2.0) + start; }
inline float easef_icubic(float start, float offset, float time, float duration) {
	return (time /= duration), offset * time * time * time + start; }
inline float easef_ocubic(float start, float offset, float time, float duration) {
	return ((time /= duration) -= 1.f), offset * (time * time * time + 1.f) + start; }
inline float easef_iocubic(float start, float offset, float time, float duration) {
	time /= (duration / 2.f);
	if (time < 1.f)
		return offset / 2.f * time * time * time + start;
	else
		return (time -= 2.f), offset / 2.f * (time * time * time + 2.f) + start; }

// Quint ease
inline double ease_iquint(double start, double offset, double time, double duration) {
	return (time /= duration), offset * time * time * time * time * time + start; }
inline double ease_oquint(double start, double offset, double time, double duration) {
	return ((time /= duration) -= 1.0), offset * (time * time * time * time * time + 1.0) + start; }
inline double ease_ioquint(double start, double offset, double time, double duration) {
	time /= (duration / 2.0);
	if (time < 1.0)
		return offset / 2.0 * time * time * time * time * time + offset;
	else
		return (time -= 2.0), offset / 2.0 * (time * time * time * time * time + 2.0) + start; }
inline float easef_iquint(float start, float offset, float time, float duration) {
	return (time /= duration), offset * time * time * time * time * time + start; }
inline float easef_oquint(float start, float offset, float time, float duration) {
	return ((time /= duration) -= 1.f), offset * (time * time * time * time * time + 1.f) + start; }
inline float easef_ioquint(float start, float offset, float time, float duration) {
	time /= (duration / 2.f);
	if (time < 1.f)
		return offset / 2.f * time * time * time * time * time + start;
	else
		return (time -= 2.f), offset / 2.f * (time * time * time * time * time + 2.f) + start; }

// Circ ease
inline double ease_icirc(double start, double offset, double time, double duration) {
	return (time /= duration), -offset * (sqrt(1.0 - time * time) - 1.0) + start; }
inline double ease_ocirc(double start, double offset, double time, double duration) {
	return ((time /= duration) -= 1.0), offset * sqrt(1.0 - time * time) + start; }
inline double ease_iocirc(double start, double offset, double time, double duration) {
	time /= (duration / 2.0);
	if (time < 1.0)
		return -offset / 2.0 * (sqrt(1.0 - time * time) - 1.0) + start;
	else
		return (time -= 2.0), offset / 2.0 * (sqrt(1.0 - time * time) + 1.0) + start; }
inline float easef_icirc(float start, float offset, float time, float duration) {
	return (time /= duration), -offset * (sqrtf(1.f - time * time) - 1.f) + start; }
inline float easef_ocirc(float start, float offset, float time, float duration) {
	return ((time /= duration) -= 1.f), offset * sqrtf(1.f - time * time) + start; }
inline float easef_iocirc(float start, float offset, float time, float duration) {
	time /= (duration / 2.f);
	if (time < 1.f)
		return -offset / 2.f * (sqrtf(1.f - time * time) - 1.f) + start;
	else
		return (time -= 2.f), offset / 2.f * (sqrtf(1.f - time * time) + 1.f) + start; }

// Elastic ease
inline double ease_ielastic(double start, double offset, double time, double duration) {
	double s = 1.70158, p = 0.0, a = offset;
	if (time == 0.0)
		return start;
	else
		time /= duration;
	if (time == 1.0)
		return start + offset;
	if (p == 0.0)
		p = duration * 0.3f;
	if (a < fabs(offset))
		a = offset, s = p / 4.0;
	else
		s = p / (2.0 * pi) * asin(offset / a);
	return -(a * pow(2.0, 10.0 * --time) * sin((time * duration - s) * (2.0 * pi) / p)) + start; }
inline double ease_oelastic(double start, double offset, double time, double duration) {
	double s = 1.70158, p = 0.0, a = offset;
	if (time == 0.0)
		return start;
	else
		time /= duration;
	if (time == 1.0)
		return start + duration;
	if (p == 0.0)
		p = duration * 0.3f;
	if (a < fabs(offset))
		a = offset, s = p / 4.0;
	else
		s = p / (2.0 * pi) * asin(offset / a);
	return a * pow(2.0, -10.0 * time) * sin((time * duration - s) * (2.0 * pi) / p) + offset + start; }
inline double ease_ioelastic(double start, double offset, double time, double duration) {
	double s = 1.70158, p = 0.0, a = offset;
	if (time == 0.0)
		return start;
	else
		time /= (duration / 2.0);
	if (time == 2.0)
		return start + offset;
	if (p == 0.0)
		p = duration * (0.3f * 1.5f);
	if (a < fabs(offset))
		a = offset, s = p / 4.0;
	else
		s = p / (2.0 * pi) * asin(offset / a);
	if (time < 1.0)
		return -0.5 * (a * pow(2.0, 10.0 * --time) * sin((time * duration - s) * (2.0 * pi) / p)) + start;
	else
		return a * pow(2.0, -10.0 * --time) * sin((time * duration - s) * (2.0 * pi) / p) * 0.5f + offset + start; }
inline float easef_ielastic(float start, float offset, float time, float duration) {
	float s = 1.70158f, p = 0.f, a = offset;
	if (time == 0.f)
		return start;
	else
		time /= duration;
	if (time == 1.f)
		return start + offset;
	if (p == 0.f)
		p = duration * 0.3f;
	if (a < fabsf(offset))
		a = offset, s = p / 4.f;
	else
		s = p / (2.f * pif) * asinf(offset / a);
	return -(a * powf(2.f, 10.f * --time) * sinf((time * duration - s) * (2.f * pif) / p)) + start; }
inline float easef_oelastic(float start, float offset, float time, float duration) {
	float s = 1.70158f, p = 0.f, a = offset;
	if (time == 0.f)
		return start;
	else
		time /= duration;
	if (time == 1.f)
		return start + duration;
	if (p == 0.f)
		p = duration * 0.3f;
	if (a < fabsf(offset))
		a = offset, s = p / 4.f;
	else
		s = p / (2.f * pif) * asinf(offset / a);
	return a * powf(2.f, -10.f * time) * sinf((time * duration - s) * (2.f * pif) / p) + offset + start; }
inline float easef_ioelastic(float start, float offset, float time, float duration) {
	float s = 1.70158f, p = 0.f, a = offset;
	if (time == 0.f)
		return start;
	else
		time /= (duration / 2.f);
	if (time == 2.f)
		return start + offset;
	if (p == 0.f)
		p = duration * (0.3f * 1.5f);
	if (a < fabsf(offset))
		a = offset, s = p / 4.f;
	else
		s = p / (2.f * pif) * asinf(offset / a);
	if (time < 1.f)
		return -0.5f * (a * powf(2.f, 10.f * --time) * sinf((time * duration - s) * (2.f * pif) / p)) + start;
	else
		return a * powf(2.f, -10.f * --time) * sinf((time * duration - s) * (2.f * pif) / p) * 0.5f + offset + start; }

// Quad ease
inline double ease_iquad(double start, double offset, double time, double duration) {
	return (time /= duration), offset * time * time + start; }
inline double ease_oquad(double start, double offset, double time, double duration) {
	return (time /= duration), (-offset * time * (time - 2.0) + start); }
inline double ease_ioquad(double start, double offset, double time, double duration) {
	time /= (duration / 2.0);
	if (time < 1.0)
		return offset / 2.0 * time * time + start;
	else
		return -offset / 2.0 * (--time * (time - 2.0) - 1.0) + start; }
inline float easef_iquad(float start, float offset, float time, float duration) {
	return (time /= duration), offset * time * time + start; }
inline float easef_oquad(float start, float offset, float time, float duration) {
	return (time /= duration), (-offset * time * (time - 2.f) + start); }
inline float easef_ioquad(float start, float offset, float time, float duration) {
	time /= (duration / 2.f);
	if (time < 1.f)
		return offset / 2.f * time * time + start;
	else
		return -offset / 2.f * (--time * (time - 2.f) - 1.f) + start; }

// Quart ease
inline double ease_iquart(double start, double offset, double time, double duration) {
	return (time /= duration), offset * time * time * time * time + start; }
inline double ease_oquart(double start, double offset, double time, double duration) {
	return ((time /= duration) -= 1.0), -offset * (time * time * time * time - 1.0) + start; }
inline double ease_ioquart(double start, double offset, double time, double duration) {
	time /= (duration / 2.0);
	if (time < 1.0)
		return offset / 2.0 * time * time * time * time + start;
	else
		return (time -= 2.0), -offset / 2.0 * (time * time * time * time - 2.0) + start; }
inline float easef_iquart(float start, float offset, float time, float duration) {
	return (time /= duration), offset * time * time * time * time + start; }
inline float easef_oquart(float start, float offset, float time, float duration) {
	return ((time /= duration) -= 1.f), -offset * (time * time * time * time - 1.f) + start; }
inline float easef_ioquart(float start, float offset, float time, float duration) {
	time /= (duration / 2.f);
	if (time < 1.f)
		return offset / 2.f * time * time * time * time + start;
	else
		return (time -= 2.f), -offset / 2.f * (time * time * time * time - 2.f) + start; }

// Expo ease
inline double ease_iexpo(double start, double offset, double time, double duration) {
	if (time == 0.0)
		return start;
	else
		return offset * pow(2.0, 10.0 * (time / duration - 1.0)) + start; }
inline double ease_oexpo(double start, double offset, double time, double duration) {
	if (time == duration)
		return start + offset;
	else
		return offset * (-pow(2.0, -10.0 * time / duration) + 1.0) + start; }
inline double ease_ioexpo(double start, double offset, double time, double duration) {
	if (time == 0.0)
		return start;
	if (time == duration)
		return start + offset;
	else
		time /= (duration / 2.0);
	if (time < 1.0)
		return offset / 2.0 * pow(2.0, 10.0 * (time - 1.0)) + start;
	else
		return offset / 2.0 * (-pow(2.0, -10.0 * --time) + 2.0) + start; }
inline float easef_iexpo(float start, float offset, float time, float duration) {
	if (time == 0.f)
		return start;
	else
		return offset * powf(2.f, 10.f * (time / duration - 1.f)) + start; }
inline float easef_oexpo(float start, float offset, float time, float duration) {
	if (time == duration)
		return start + offset;
	else
		return offset * (-powf(2.f, -10.f * time / duration) + 1.f) + start; }
inline float easef_ioexpo(float start, float offset, float time, float duration) {
	if (time == 0.f)
		return start;
	if (time == duration)
		return start + offset;
	else
		time /= (duration / 2.f);
	if (time < 1.f)
		return offset / 2.f * powf(2.f, 10.f * (time - 1.f)) + start;
	else
		return offset / 2.f * (-powf(2.f, -10.f * --time) + 2.f) + start; }

// Back ease
inline double ease_iback(double start, double offset, double time, double duration, double size = 1.70158) {
	return (time /= duration), offset * time * time * ((size + 1.0) * time - size) + start; }
inline double ease_oback(double start, double offset, double time, double duration, double size = 1.70158) {
	return ((time /= duration) -= 1.0), offset * (time * time * ((size + 1.0) * time + size) + 1.0) + start; }
inline double ease_ioback(double start, double offset, double time, double duration, double size = 1.70158) {
	time /= (duration / 2.0), size *= 1.525;
	if (time < 1.0)
		return offset / 2.0 * (time * time * ((size + 1.0) * time - size)) + start;
	else
		return (time -= 2.0), offset / 2.0 * (time * time * ((size + 1.0) * time + size) + 2.0) + start; }
inline float easef_iback(float start, float offset, float time, float duration, float size = 1.70158f) {
	return (time /= duration), offset * time * time * ((size + 1.f) * time - size) + start; }
inline float easef_oback(float start, float offset, float time, float duration, float size = 1.70158f) {
	return ((time /= duration) -= 1.f), offset * (time * time * ((size + 1.f) * time + size) + 1.f) + start; }
inline float easef_ioback(float start, float offset, float time, float duration, float size = 1.70158f) {
	time /= (duration / 2.f), size *= 1.525f;
	if (time < 1.f)
		return offset / 2.f * (time * time * ((size + 1.f) * time - size)) + start;
	else
		return (time -= 2.f), offset / 2.f * (time * time * ((size + 1.f) * time + size) + 2.f) + start; }

// Bounce ease
inline double ease_obounce(double start, double offset, double time, double duration) {
	time /= duration;
	if (time < 1.0 / 2.75)
		return offset * (7.5625 * time * time) + start;
	else if (time < 2.0 / 2.75)
		return (time -= (1.5 / 2.75)), offset * (7.5625 * time * time + 0.75) + start;
	else if (time < 2.5 / 2.75)
		return (time -= (2.25 / 2.75)), offset * (7.5625 * time * time + 0.9375) + start;
	else
		return (time -= (2.625 / 2.75)), offset * (7.5625 * time * time + 0.984375) + start; }
inline double ease_ibounce(double start, double offset, double time, double duration) {
	return offset - ease_obounce(0.0, offset, duration - time, duration) + start; }
inline double ease_iobounce(double start, double offset, double time, double duration) {
	if (time < duration / 2.0)
		return ease_ibounce(0.0, offset, time * 2.0, duration) * 0.5 + start;
	else
		return ease_obounce(0.0, offset, time * 2.0 - duration, duration) * 0.5 + offset * 0.5 + start; }
inline float easef_obounce(float start, float offset, float time, float duration) {
	time /= duration;
	if (time < 1.f / 2.75f)
		return offset * (7.5625f * time * time) + start;
	else if (time < 2.f / 2.75f)
		return (time -= (1.5f / 2.75f)), offset * (7.5625f * time * time + 0.75f) + start;
	else if (time < 2.5f / 2.75f)
		return (time -= (2.25f / 2.75f)), offset * (7.5625f * time * time + 0.9375f) + start;
	else
		return (time -= (2.625f / 2.75f)), offset * (7.5625f * time * time + 0.984375f) + start; }
inline float easef_ibounce(float start, float offset, float time, float duration) {
	return offset - easef_obounce(0.f, offset, duration - time, duration) + start; }
inline float easef_iobounce(float start, float offset, float time, float duration) {
	if (time < duration / 2.f)
		return easef_ibounce(0.f, offset, time * 2.f, duration) * 0.5f + start;
	else
		return easef_obounce(0.f, offset, time * 2.f - duration, duration) * 0.5f + offset * 0.5f + start; }


// -------------------------------- \\
//			   Geometry				\\
// -------------------------------- \\


inline double oppadj(double hypot, double x) {
	return sqrt(fpow(hypot, 2) - fpow(x, 2)); }


// -------------------------------- \\
//			 Trigonometry			\\
// -------------------------------- \\


inline double cot(double x) {
	return (1.0 / tan(x)); }
inline double sec(double x) {
	return (1.0 / cos(x)); }
inline double csc(double x) {
	return (1.0 / sin(x)); }

inline double coth(double x) {
	return (cosh(x) / sinh(x)); }
inline double sech(double x) {
	return (1.0 / cosh(x)); }
inline double csch(double x) {
	return (1.0 / sinh(x)); }

inline double acot(double x) {
	return atan(1.0 / x); }
inline double asec(double x) {
	return acos(1.0 / x); }
inline double acsc(double x) {
	return asin(1.0 / x); }

inline double acoth(double x) {
	return atanh(1.0 / x); }
inline double asech(double x) {
	return acosh(1.0 / x); }
inline double acsch(double x) {
	return asinh(1.0 / x); }
inline double acot2(double x, double y) {
	if (y > 0.0)
		return acot(x / y);
	else if (y < 0.0)
		if (x >= 0.0)
			return acot(x / y) + pi;
		else
			return acot(x / y) - pi;
	else
		if (x > 0.0)
			return +(pi / 2);
		else if (x < 0.0)
			return -(pi / 2);
		else
			return (double)NAN; }

// Sin rule
inline double sinrl(double a, double A, double B) {// Get length of b
	return a / sin(rad(A)) * sin(rad(B)); }
inline float sinrlf(float a, float A, float B) {// Get length of b
	return a / sinf(radf(A)) * sinf(radf(B)); }
inline double sinra(double a, double A, double b) {// Get angle of B ( in radians )
	return asin((sin(rad(A)) / a) * b); }
inline float sinraf(float a, float A, float b) {// Get angle of B ( in radians )
	return asinf((sinf(radf(A)) / a) * b); }

// Cos rule
inline double cosrl(double a, double b, double C) {// Get length of c
	return sqrt(fpow(a, 2) + fpow(b, 2) - 2.0 * a * b * cos(rad(C))); }
inline float cosrlf(float a, float b, float C) {// Get length of c
	return sqrtf(fpowf(a, 2) + fpowf(b, 2) - 2.f * a * b * cosf(radf(C))); }
inline double cosra(double a, double b, double c) {// Get angle of C ( in radians )
	return acos((fpow(a, 2) + fpow(b, 2) - fpow(c, 2)) / (2.0 * a * b)); }
inline float cosraf(float a, float b, float c) {// Get angle of C ( in radians )
	return acosf((fpowf(a, 2) + fpowf(b, 2) - fpowf(c, 2)) / (2.f * a * b)); }

// Lissajous curve
inline void lsjc(double& out_x, double& out_y, double A, double B, double s, double f, double p) {
	out_x = s * sin(A * f + p); 
	out_y = s * sin(B); }
inline void lsjcf(float& out_x, float& out_y, float A, float B, float s, float f, float p) {
	out_x = s * sinf(A * f + p);
	out_y = s * sinf(B); }

// Lissajous knot
inline double lsjk(double T, double s, double n, double p) {
	return s * cos(n * T + p); }
inline void lsjk(double& out_x, double& out_y, double& out_z, double T, double s, double nx, double ny, double nz, double px, double py, double pz) {
	out_x = lsjk(T, s, nx, px);
	out_y = lsjk(T, s, ny, py);
	out_z = lsjk(T, s, nz, pz); }
inline float lsjkf(float T, float s, float n, float p) {
	return s * cosf(n * T + p); }
inline void lsjkf(float& out_x, float& out_y, float& out_z, float T, float s, float nx, float ny, float nz, float px, float py, float pz) {
	out_x = lsjkf(T, s, nx, px);
	out_y = lsjkf(T, s, ny, py);
	out_z = lsjkf(T, s, nz, pz); }