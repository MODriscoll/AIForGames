#include "Behaviours\Interface\IComposite.h"

namespace Behaviour
{
	IComposite::IComposite(const std::string& a_Tag)
		: IBehaviour(a_Tag)
	{
		// Set pending to end of array
		m_Pending = m_Behaviours.end();
	}

	IComposite::~IComposite()
	{

	}

	void IComposite::Insert(const behaviour_ptr& a_Behaviour)
	{
		// Insert this behaviour
		m_Behaviours.push_back(a_Behaviour);

		// Reset pending behaviour
		m_Pending = m_Behaviours.end();
	}

	size_t IComposite::Count() const
	{
		// Return the size of the container
		return m_Behaviours.size();
	}

	behaviour_ptr IComposite::Get(const std::string& a_Tag)
	{
		// Cycle through all behaviours
		for (auto& b : m_Behaviours)
		{
			// Is this the requested behaviour
			if (b->Tag() == a_Tag)
			{
				// Return this behaviour
				return b;
			}
		}

		// If behaviour wasn't found, return nullptr
		return nullptr;
	}
	
	behaviour_ptr IComposite::Find(const std::string& a_Tag)
	{
		// Cycle through all behaviours
		for (auto& b : m_Behaviours)
		{
			// Is this the queried behaviour?
			if (b->Tag() == a_Tag)
			{
				// Return this behaviour
				return b;
			}

			// Search this behaviour, capture result
			behaviour_ptr Cap = b->Find(a_Tag);

			// Was the behaviour found?
			if (Cap)
			{
				// Return this behaviour
				return Cap;
			}
		}

		// If behaviour wasn't found, return nullptr
		return nullptr;
	}
}