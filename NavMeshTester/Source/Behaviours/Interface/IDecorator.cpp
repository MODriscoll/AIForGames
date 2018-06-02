#include "Behaviours\Interface\IDecorator.h"

namespace Behaviour
{
	IDecorator::IDecorator(const std::string& a_Tag, const behaviour_ptr& a_Child)
		: IBehaviour(a_Tag), m_Child(a_Child)
	{
		// Assert if child is nullptr
		assert(m_Child && "Decorator requires child");
	}

	IDecorator::~IDecorator()
	{

	}

	behaviour_ptr IDecorator::Clone(const std::string& a_Tag) const
	{
		// Clone the child behaviour
		behaviour_ptr CL = m_Child->Clone();

		// Was the clone made?
		if (CL)
		{
			// Get derived behaviour to clone and return the clone
			return Clone(a_Tag, CL);
		}
		else
		{
			// Return nullptr
			return nullptr;
		}
	}

	behaviour_ptr IDecorator::Get() const
	{
		// Return the child behaviour
		return m_Child;
	}

	behaviour_ptr IDecorator::Find(const std::string& a_Tag)
	{
		// If child is queried behaviour, return it. Otherwise continue search
		return m_Child->Tag() == a_Tag ? m_Child : m_Child->Find(a_Tag);
	}

}