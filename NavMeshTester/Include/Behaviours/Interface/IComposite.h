#pragma once

#ifndef Michaels_Behaviour_Composite
#define Michaels_Behaviour_Composite

#include "IBehaviour.h"

#include <vector>

namespace Behaviour
{
	class IComposite : public IBehaviour
	{
	protected:

		using bvector = std::vector<behaviour_ptr>;
		using biterator = typename bvector::iterator;

	public:

		// Public destructor
		// Deletes all behaviours
		virtual ~IComposite();

		// Update function, executes derived behaviour on given game object
		virtual eBehaviourResult Execute(Agent* a_Agent, float deltaTime) = 0;

	public:

		// Insert new behaviour
		void Insert(const behaviour_ptr& a_Behaviour);

		// Number of behaviours stored
		size_t Count() const;

		// Get base behaviour using identification tag
		behaviour_ptr Get(const std::string& a_Tag);

		// Get behaviour that matches type
		template <typename Type>
		Type* const GetType();

		// Get behaviour that matches both type and tag
		template <typename Type>
		Type* const GetType(const std::string& a_Tag);

		// Find behaviour in this composite, returns nullptr if behaviour is not found
		virtual behaviour_ptr Find(const std::string& a_Tag) override;

	protected:

		// Protected since composite must be inherited from
		IComposite(const std::string& a_Tag);

		// Behaviours in this composite
		bvector m_Behaviours;

		// Pending behaviour from last executed update
		biterator m_Pending;
	};

	template<typename Type>
	inline Type* const IComposite::GetType()
	{
		// Assert if type is not a behaviour
		static_assert(std::is_base_of<IBehaviour, Type>::value, "Invalid search type");

		// Cycle through all behaviours
		for (auto& b : m_Behaviours)
		{
			// Cast this behaviour to requested type
			Type* Cast = dynamic_cast<Type*>(b.get());

			// Was the cast successfull?
			if (Cast != nullptr)
			{
				// Return this behaviour
				return Cast;
			}
		}

		// If behaviour wasn't found, return nullptr
		return nullptr;
	}

	template<typename Type>
	inline Type* const IComposite::GetType(const std::string& a_Tag)
	{
		// Assert if type is not a behaviour
		static_assert(std::is_base_of<IBehaviour, Type>::value, "Invalid search type");

		// Cycle through all behaviours
		for (auto& b : m_Behaviours)
		{
			// Does behaviour not match the given tag?
			if (b->m_Tag != a_Tag)
			{
				// Skip the rest
				continue;
			}

			// Cast this behaviour to requested type
			Type* Cast = dynamic_cast<Type*>(b.get());

			// Was the cast successfull?
			if (Cast != nullptr)
			{
				// Return this behaviour
				return Cast;
			}
		}

		// If behaviour wasn't found, return nullptr
		return nullptr;
	}
}

#endif // Michaels_Behaviour_Composite