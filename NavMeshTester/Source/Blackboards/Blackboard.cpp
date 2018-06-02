#include "Blackboards\Blackboard.h"

using nmap = std::map <std::string, Blackboard::Node>;

void Blackboard::SetAs_Int(const std::string& a_Tag, int a_Int)
{
	// Call relative set function
	SetAs(a_Tag, a_Int);
}

void Blackboard::SetAs_UInt(const std::string& a_Tag, size_t a_UInt)
{
	// Call relative set function
	SetAs(a_Tag, a_UInt);
}

void Blackboard::SetAs_Float(const std::string& a_Tag, float a_Float)
{
	// Call relative set function
	SetAs(a_Tag, a_Float);
}

void Blackboard::SetAs_Char(const std::string& a_Tag, char a_Char)
{
	// Call relative set function
	SetAs(a_Tag, a_Char);
}

void Blackboard::SetAs_Bool(const std::string& a_Tag, bool a_Bool)
{
	// Call relative set function
	SetAs(a_Tag, a_Bool);
}

void Blackboard::SetAs_Pointer(const std::string& a_Tag, void* a_Pointer)
{
	// Call relative set function
	SetAs(a_Tag, a_Pointer);
}

int Blackboard::GetAs_Int(const std::string& a_Tag)
{
	// Call relative get function
	return GetAs<int>(a_Tag);
}

size_t Blackboard::GetAs_UInt(const std::string& a_Tag)
{
	// Call relative get function
	return GetAs<size_t>(a_Tag);
}

float Blackboard::GetAs_Float(const std::string& a_Tag)
{
	// Call relative get function
	return GetAs<float>(a_Tag);
}

char Blackboard::GetAs_Char(const std::string& a_Tag)
{
	// Call relative get function
	return GetAs<char>(a_Tag);
}

bool Blackboard::GetAs_Bool(const std::string& a_Tag)
{
	// Call relative get function
	return GetAs<bool>(a_Tag);
}

void* Blackboard::GetAs_Pointer(const std::string& a_Tag)
{
	// Call relative get function
	return GetAs<void*>(a_Tag);
}

void Blackboard::Remove(const std::string& a_Tag)
{
	// Remove this node
	m_Nodes.erase(a_Tag);
}

bool Blackboard::Has(const std::string& a_Tag) const
{
	// To capture if node exists
	bool Exi = false;

	// Find this node
	GetNode(a_Tag, Exi);

	// Return the captured bool
	return Exi;
}

eBlackboardType Blackboard::Type(const std::string& a_Tag) const
{
	// To capture if node exists
	bool Exi = false;

	// Find this node, capture the iterator
	nconst_iterator it = GetNode(a_Tag, Exi);

	// Was the node found?
	if (Exi)
	{
		// Get reference to the node
		const Node& Ref = it->second;

		// Return this nodes type
		return Ref.m_Type;
	}
	else
	{
		// Return no node found
		return eBlackboardType::Invalid;
	}
}

nmap::iterator Blackboard::GetNode(const std::string& a_Tag, bool& out_Found)
{
	// Find this node, capture the iterator
	niterator it = m_Nodes.find(a_Tag);

	// Set the output bool to true if found
	out_Found = (it != m_Nodes.end());

	// Return the iterator
	return it;
}

nmap::const_iterator Blackboard::GetNode(const std::string& a_Tag, bool& out_Found) const
{
	// Find this node, capture the iterator
	nconst_iterator it = m_Nodes.find(a_Tag);

	// Set the output bool to true if found
	out_Found = (it != m_Nodes.cend());

	// Return the iterator
	return it;
}