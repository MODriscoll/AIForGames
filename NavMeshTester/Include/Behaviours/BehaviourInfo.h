#pragma once

#ifndef Michaels_Behaviour_Info
#define Michaels_Behaviour_Info

#include <cassert>
#include <memory>
#include <string>

class Agent;

namespace Behaviour
{
	class IBehaviour;

	using behaviour_ptr = std::shared_ptr<IBehaviour>;

	enum class eBehaviourResult : unsigned char
	{
		Success = 1 << 0,
		Failure = 1 << 1,
		Pending = 1 << 2,

		Invalid = 0
	};

	inline bool ValidateResult(const Behaviour::eBehaviourResult& a_Result)
	{
		#ifdef _DEBUG
			// Assert if result is invalid
			assert(a_Result != eBehaviourResult::Invalid && "Behaviour returned invalid result");
			// Return valid result
			return true;
		#else
			// Return valid result
			return true;
		#endif
	}

	#define VALIDATERESULT ValidateResult
}


#endif // Michaels_Behaviour_Info