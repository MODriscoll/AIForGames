#pragma once

#ifndef Michaels_Behaviour_Steerer
#define Michaels_Behaviour_Steerer

#include "ISteer.h"

#include <vector>

namespace Behaviour
{
	using steer_ptr = std::shared_ptr<ISteer>;

	class Steerer final : public IBehaviour
	{
	public:

		using svector = std::vector<steer_ptr>;

	public:

		// Public constructor with default tag
		Steerer();
		// Public constructor with optional tag
		Steerer(const std::string& a_Tag);

		// Public destructor
		// Deletes all steering behaviours
		virtual ~Steerer();

		// Calculates steering force using stored behaviours to apply to given agent
		// Returns successfull result every update
		virtual eBehaviourResult Execute(Agent* a_Agent, float deltaTime) override;

	public:

		// Insert new steering behaviour
		void Insert(const steer_ptr& a_Behaviour);

		// Number of steering behaviours stored
		size_t Count() const;

		// Set the max force of this steerer
		void MaxForce(float a_MaxForce);

		// Get the max force of this steerer
		float MaxForce() const;

		// Get base steering behaviour using identification type
		ISteer* const Get(const std::string& a_Tag);

		// Get steering behaviour that matches type
		template <typename Type>
		Type* const GetType();

		// Get steering behaviour that matches both type and tag
		template <typename Type>
		Type* const GetType(const std::string& a_Tag);

		// Find behaviour in this steerer, returns nullptr if behaviour is not found
		virtual behaviour_ptr Find(const std::string& a_Tag) override;

	private:

		// Creates clone of self by cloning all stored behaviours
		virtual behaviour_ptr Clone(const std::string& a_Tag) const;

		// Steering behaviours in this steerer
		svector m_Behaviours;

		// The maximum force of this steerer
		float m_MaxForce;
	};

	template<typename Type>
	inline Type* const Steerer::GetType()
	{
		// Assure the type is a steering behaviour
		static_assert(std::is_base_of<ISteer, Type>::value, "Invalid search type");

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
	inline Type* const Steerer::GetType(const std::string & a_Tag)
	{
		// Assure the type is a steering behaviour
		static_assert(std::is_base_of<ISteer, Type>::value, "Invalid search type");

		// Cycle through all behaviours
		for (auto& b : m_Behaviours)
		{
			// Does behaviour not match the given tag?
			if (b->Tag() != a_Tag)
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

#endif // Michaels_Behaviour_Steerer