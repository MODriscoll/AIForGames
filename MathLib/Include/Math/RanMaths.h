#pragma once

#include <chrono>
#include <functional>
#include <random>

// Like BitMath.h, I plan on
// improving this and add much
// more functions to help with
// rng for games

// The random engine to be used
// to generate random numbers
static std::default_random_engine prng;

// So we don't have to write
// std::chrono every 'time' 
using namespace std::chrono;

// Pre-set distributors
// types for easy use
using IntGenerator = std::uniform_int_distribution<int>;
using FloatGenerator = std::uniform_real_distribution<float>;

// Plant a time seed
inline void PlantTimeSeed()
{
	// Get the time as of now
	time_point<system_clock> cTime = system_clock::now();

	// Get the duration since
	// the timer has started
	system_clock::duration dTime = cTime.time_since_epoch();

	// Set the seed to be the
	// count of the duration
	unsigned int Seed = static_cast<unsigned int>(dTime.count());

	// Plant the new seed
	// into the gen engine
	prng.seed(Seed);
}

// Creates a new int generator
// using the min and max value
inline std::function<int()> CreateIntGenerator(int min, int max)
{
	// Create the function to return
	std::function<int()> Func;

	// Set the function to be the
	// binding of a distributor and
	// a reference to the PRNG
	Func = std::bind(IntGenerator(min, max), std::ref(prng));

	// Return the function
	return Func;
}

// Creates a new integral generator
// using the min and max value
template <typename Type>
inline std::function<Type()> CreateIntegralGenerator(Type min, Type max)
{
	// Assert if the requested general is not an integral type
	static_assert(std::is_integral<Type>::value, "Type is not integral, did you mean to use real?");

	// Create the function to return
	std::function<Type()> Func;

	// Set the function to be the
	// binding of a distributor and
	// a reference to the PRNG
	Func = std::bind(std::uniform_int_distribution<Type>(min, max), std::ref(prng));

	// Return the function
	return Func;
}

// Creates a new float generator
// using the min and max value
inline std::function<float()> CreateFloatGenerator(float min, float max)
{
	// Create the function to return
	std::function<float()> Func;

	// Set the function to be the
	// binding of a distributor and
	// a reference to the PRNG
	Func = std::bind(FloatGenerator(min, max), std::ref(prng));

	// Return the function
	return Func;
}

// Creates a new real generator
// using the min and max value
template <typename Type>
inline std::function<Type()> CreateRealGenerator(Type min, Type max)
{
	// Assert if the requested general is not a real type
	static_assert(std::_Is_RealType<Type>::value, "Type is not real, did you mean to use integral?");

	// Create the function to return
	std::function<Type()> Func;

	// Set the function to be the
	// binding of a distributor and
	// a reference to the PRNG
	Func = std::bind(std::uniform_real_distribution<Type>(min, max), std::ref(prng));

	// Return the function
	return Func;
}