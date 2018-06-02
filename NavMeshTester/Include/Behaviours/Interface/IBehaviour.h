#pragma once

#ifndef Michaels_Behaviour_Base
#define Michaels_Behaviour_Base

#include "Behaviours\BehaviourInfo.h"

namespace Behaviour
{
	class IBehaviour
	{
	public:

		// Public destructor
		virtual ~IBehaviour() = default;

		// Update function, executes derived behaviour on given agent
		virtual eBehaviourResult Execute(Agent* a_Agent, float deltaTime) = 0;

	public:

		// Get this behaviours tag
		const std::string& Tag() const;

		// Clone function, calls overload clone by default
		virtual behaviour_ptr Clone() const;

		// Clone function with new tag, returns nullptr by default
		virtual behaviour_ptr Clone(const std::string& a_Tag) const;

		// Public clone function, can be defaulted by derived types
		template <typename Type>
		std::shared_ptr<Type> Clone() const;

		// Public clone function with new tag, can be defaulted by by derived types
		template <typename Type>
		std::shared_ptr<Type> Clone(const std::string& a_Tag) const;

		// Function for behaviours to override to search hierarchy
		virtual behaviour_ptr Find(const std::string& a_Tag);

	protected:

		// Default constructor for leaf types
		// Protected since behaviour must be inherited from
		IBehaviour(const std::string& a_Tag);

		// Indentification tag
		const std::string m_Tag;
	};

	template<typename Type>
	inline std::shared_ptr<Type> IBehaviour::Clone() const
	{
		// Assert if type is not a behaviour
		static_assert(std::is_base_of<IBehaviour, Type>::value, "Invalid clone type");

		// Clone the behaviour, catch it in a behaviour pointer
		behaviour_ptr CL = Clone();

		// Cast the cloned behaviour to the requested type
		auto Cast = std::dynamic_pointer_cast<Type>(CL);

		// Return the result of the cast
		return Cast;
	}

	template<typename Type>
	inline std::shared_ptr<Type> IBehaviour::Clone(const std::string& a_Tag) const
	{
		// Assert if type is not a behaviour
		static_assert(std::is_base_of<IBehaviour, Type>::value, "Invalid clone type");

		// Clone the behaviour, catch it in a behaviour pointer
		behaviour_ptr CL = Clone(a_Tag);

		// Cast the cloned behaviour to the requested type
		auto Cast = std::dynamic_pointer_cast<Type>(CL);

		// Return the result of the cast
		return Cast;
	}
}

#endif // Michaels_Behaviour_Base