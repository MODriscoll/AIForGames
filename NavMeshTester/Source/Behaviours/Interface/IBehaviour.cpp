#include "Behaviours\Interface\IBehaviour.h"

namespace Behaviour
{
	IBehaviour::IBehaviour(const std::string& a_Tag)
		: m_Tag(a_Tag)
	{

	}

	const std::string& IBehaviour::Tag() const
	{
		// Return this behaviours tag
		return m_Tag;
	}

	behaviour_ptr IBehaviour::Clone() const
	{
		// Return a clone with the same tag
		return Clone(m_Tag);
	}

	behaviour_ptr IBehaviour::Clone(const std::string& a_Tag) const
	{
		// Return nullptr by default
		return nullptr;
	}

	behaviour_ptr IBehaviour::Find(const std::string& a_Tag)
	{
		// Return nullptr by default
		return nullptr;
	}
}