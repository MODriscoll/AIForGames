#pragma once

#include <type_traits>

enum class mNodeType : unsigned char
{
	Default,

	Spawn,
	Exit
};

enum class mSpawnType : unsigned char
{
	None,

	Player,
	Survivour,
	Monster
};

using mNodeTypeBase = std::underlying_type_t<mNodeType>;
using mSpawnTypeBase = std::underlying_type_t<mSpawnType>;

inline mSpawnType operator & (const mSpawnType& lhs, const mSpawnType& rhs)
{
	return static_cast<mSpawnType>((static_cast<mSpawnTypeBase>(lhs) & static_cast<mSpawnTypeBase>(rhs)));
}

inline mSpawnType operator | (const mSpawnType& lhs, const mSpawnType& rhs)
{
	return static_cast<mSpawnType>((static_cast<mSpawnTypeBase>(lhs) | static_cast<mSpawnTypeBase>(rhs)));
}

inline mNodeType GetNodeType(const int& a_Value)
{
	return static_cast<mNodeType>(a_Value);
}

inline mSpawnType GetSpawnType(const int& a_Value)
{
	return static_cast<mSpawnType>(a_Value);
}

inline int GetNodeType(const mNodeType& a_Value)
{
	return static_cast<int>(a_Value);
}

inline int GetSpawnType(const mSpawnType& a_Value)
{
	return static_cast<int>(a_Value);
}