#pragma once

#ifndef Michaels_Behaviour_Seek
#define Michaels_Behaviour_Seek

#include "ISteer.h"

namespace Behaviour
{
	class Seek final : public ISteer
	{
	public:

		// Public constructor with default tag
		Seek();
		// Public constructor with optional tag
		Seek(const std::string& a_Tag);

		// Default destructor
		virtual ~Seek() = default;

		// Seeks given agent towards the set target
		virtual eBehaviourResult Execute(Agent* a_Agent, float deltaTime) override;

		// Calculates the force needed to move the given agent towards the set target
		virtual Vector2 Calculate(Agent* a_Agent) override;

		// Clone this seek behaviour with a new tag
		virtual behaviour_ptr Clone(const std::string& a_Tag) const;
	};
}

#endif // Michaels_Behaviour_Seek