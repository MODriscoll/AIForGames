#pragma once

#ifndef Michaels_Behaviour_Decorator
#define Michaels_Behaviour_Decorator

#include "IBehaviour.h"

namespace Behaviour
{
	class IDecorator : public IBehaviour
	{
	public:

		// Public destructor
		// Deletes child
		virtual ~IDecorator();

		// Update function, executes derived behaviour on given game object
		virtual eBehaviourResult Execute(Agent* a_Agent, float deltaTime) = 0;

	public:

		// Creates clone of self by cloning derived behaviour
		virtual behaviour_ptr Clone(const std::string& a_Tag) const;

		// Get child as base behaviour
		behaviour_ptr Get() const;

		// Get child as given type
		template <typename Type>
		Type* const Get();

		// Find behaviour in this decorator, returns nullptr if behaviour is not found
		virtual behaviour_ptr Find(const std::string& a_Tag) override;

	protected:

		// Protected since decorator must be inherited from
		// Decorator must be initialised with a child behaviour ( asserts if nullptr )
		IDecorator(const std::string& a_Tag, const behaviour_ptr& a_Child);

		// Clone function must be derived from
		// This will be called by decorators clone function
		// only if the childs clone did not return nullptr
		virtual behaviour_ptr Clone(const std::string& a_Tag, const behaviour_ptr& a_Child) const = 0;

		// Child of this decorator
		behaviour_ptr m_Child;
	};

	template<typename Type>
	inline Type* const IDecorator::Get()
	{
		// Assert if type is not a behaviour
		static_assert(std::is_base_of<IBehaviour, Type>::value, "Invalid search type");

		// Return the result of the cast
		return dynamic_cast<Type*>(m_Child.get());
	}
}

#endif // Michaels_Behaviour_Decorator