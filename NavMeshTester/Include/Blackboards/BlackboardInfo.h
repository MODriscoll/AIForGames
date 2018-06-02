#pragma once

#ifndef Michaels_Blackboard_Info
#define Michaels_Blackboard_Info

#include <string>

enum class eBlackboardType : unsigned char
{
	Int			= 1 << 0,
	UInt		= 1 << 1,
	Float		= 1 << 2,
	Char		= 1 << 3,
	Bool		= 1 << 4,
	Pointer		= 1 << 5,

	Invalid		= 0
};

#endif // Michaels_Blackboard_Info