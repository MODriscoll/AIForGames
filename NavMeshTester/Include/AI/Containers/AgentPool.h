#pragma once

#include "Containers\ObjectPool.h"

#include "Objects\Agent.h"

template <typename Type, size_t Size>
class AgentPool : public Containers::ObjectPool<Type, Size>
{
public:

	AgentPool()
	{
		static_assert(std::is_base_of<Agent, Type>::value, "Agent pool requires Agent type")
	}
};