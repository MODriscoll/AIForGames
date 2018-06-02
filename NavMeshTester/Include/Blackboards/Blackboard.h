#pragma once

#ifndef Michaels_Blackboard
#define Michaels_Blackboard

#include "BlackboardInfo.h"

#include <map>

class Blackboard final
{
private:

	struct BlackboardNode;

	using nmap = std::map<std::string, BlackboardNode>;
	using niterator = nmap::iterator;
	using nconst_iterator = nmap::const_iterator;

private:

	// Node struct ( wrapper for values )
	struct BlackboardNode
	{
		// Default constructor sets type to invalid
		BlackboardNode()
			: m_Type(eBlackboardType::Invalid) { }

		// ----- CONSTRUCTORS ----- \\

		// Overloaded constructors for each compatible type

		BlackboardNode(int a_Int)
			: m_Type(eBlackboardType::Int), m_Int(a_Int) { }
		BlackboardNode(size_t a_UInt)
			: m_Type(eBlackboardType::UInt), m_UInt(a_UInt) { }
		BlackboardNode(float a_Float)
			: m_Type(eBlackboardType::Float), m_Float(a_Float) { }
		BlackboardNode(char a_Char)
			: m_Type(eBlackboardType::Char), m_Char(a_Char) { }
		BlackboardNode(bool a_Bool)
			: m_Type(eBlackboardType::Bool), m_Bool(a_Bool) { }
		BlackboardNode(void* a_Pointer)
			: m_Type(eBlackboardType::Pointer), m_Pointer(a_Pointer) { }

		// Default destructor
		~BlackboardNode() = default;

		// ----- SETS ----- \\

		// Overloaded sets for each compatible type
		// Sets type and value to match overloaded type parameter

		void Set(int a_Int)
		{ m_Type = eBlackboardType::Int; m_Int = a_Int; }
		void Set(size_t a_UInt) 
		{ m_Type = eBlackboardType::UInt; m_UInt = a_UInt; }
		void Set(float a_Float)
		{ m_Type = eBlackboardType::Float; m_Float = a_Float; }
		void Set(char a_Char) 
		{ m_Type = eBlackboardType::Char; m_Char = a_Char; }
		void Set(bool a_Bool)
		{ m_Type = eBlackboardType::Bool; m_Bool = a_Bool; }
		void Set(void* a_Pointer) 
		{ m_Type = eBlackboardType::Pointer; m_Pointer = a_Pointer; }

		// ----- GETS ----- \\
		
		// Overloaded gets for each comptatible type
		// Returns value if type matches overloaded type parameter, otherwise default value

		int Get(int)
		{ return m_Type == eBlackboardType::Int ? m_Int : int(); }
		size_t Get(size_t)
		{ return m_Type == eBlackboardType::UInt ? m_UInt : size_t(); }
		float Get(float)
		{ return m_Type == eBlackboardType::Float ? m_Float : float(); }
		char Get(char)
		{ return m_Type == eBlackboardType::Char ? m_Char : char(); }
		bool Get(bool)
		{ return m_Type == eBlackboardType::Bool ? m_Bool : bool(); }
		void* Get(void*)
		{ return m_Type == eBlackboardType::Pointer ? m_Pointer : nullptr; }

		// Union for all compatible types
		union
		{
			int			m_Int;
			size_t		m_UInt;
			float		m_Float;
			char		m_Char;
			bool		m_Bool;
			void*		m_Pointer;
		};

		// Indentification type
		eBlackboardType m_Type;
	};

public:

	using Node = BlackboardNode;

	// Default constructor and destructor
	Blackboard() = default;
	~Blackboard() = default;

	// ----- SETS ----- \\

	// If node doesn't exist, a new node is created and set to corresponding type
	// If node does exist, the nodes type is set to corresponding type
	// Pointer types are not deleted

	void	SetAs_Int(const std::string& a_Tag, int a_Int);
	void	SetAs_UInt(const std::string& a_Tag, size_t a_UInt);
	void	SetAs_Float(const std::string& a_Tag, float a_Float);
	void	SetAs_Char(const std::string& a_Tag, char a_Char);
	void	SetAs_Bool(const std::string& a_Tag, bool a_Bool);
	void	SetAs_Pointer(const std::string& a_Tag, void* a_Pointer);

	// ----- GETS ----- \\

	// If node doesn't exist, default value of type is returned ( Type() )
	// If node exists and matches type, value is returned
	// If node exists and doesn't match type, default value of type is returned ( Type() )
	// Default value of pointer is nullptr

	int		GetAs_Int(const std::string& a_Tag);
	size_t	GetAs_UInt(const std::string& a_Tag);
	float	GetAs_Float(const std::string& a_Tag);
	char	GetAs_Char(const std::string& a_Tag);
	bool	GetAs_Bool(const std::string& a_Tag);
	void*	GetAs_Pointer(const std::string& a_Tag);

	// Removes node with matching tag
	// Pointer types are not deleted
	void Remove(const std::string& a_Tag);

	// Returns true if board has node with matching tag, false if not
	bool Has(const std::string& a_Tag) const;

	// Returns type being stored in node with matching tag
	// If node doesn't exist, invalid type is returned
	eBlackboardType Type(const std::string& a_Tag) const;

private:

	// Template set function, calls nodes overloaded set function
	template <typename Type>
	void SetAs(const std::string& a_Tag, Type& a_Type)
	{
		// To capture if node exists
		bool Exi = false;

		// Find this node, capture the iterator
		niterator it = GetNode(a_Tag, Exi);

		// Was the node found?
		if (Exi)
		{
			// Get reference to the node
			Node& Ref = it->second;

			// Reset the node
			Ref.Set(a_Type);
		}
		else
		{
			// Create the new node in this slot
			m_Nodes[a_Tag] = Node(a_Type);
		}
	}

	// Template get function, calls nodes overloaded get function
	template <typename Type>
	Type GetAs(const std::string& a_Tag)
	{
		// To capture if node exists
		bool Exi = false;

		// Find this node, capture the iterator
		niterator it = GetNode(a_Tag, Exi);

		// Was the node found?
		if (Exi)
		{
			// Get reference to the node
			Node& Ref = it->second;

			// Get this nodes value and return it
			return Ref.Get(Type());
		}
		else
		{
			// Create invalid node and return its default
			return Node().Get(Type());
		}
	}

	// Gets iterator to node with matching tag
	// If node is found, out is set true otherwise false
	niterator GetNode(const std::string& a_Tag, bool& out_Found);
	// Get const qualified iterator to node with matching tag
	// If node is found, out is set true otherwise false
	nconst_iterator GetNode(const std::string& a_Tag, bool& out_Found) const;

	// Nodes of this board
	nmap m_Nodes;
};

#endif // Michaels_Blackboard