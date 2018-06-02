#pragma once

#ifndef Michaels_BehaviourTree
#define Michaels_BehaviourTree

#include "Behaviours\Interface\IBehaviour.h"

#include "Blackboards\Blackboard.h"

namespace Behaviour
{
	class BehaviourTree final
	{
	public:

		// Default constructor, create empty tree
		BehaviourTree();

		// Default constructor, initialises root
		BehaviourTree(const behaviour_ptr& a_Root);

		// Copy constructor, clones existing tree
		BehaviourTree(const BehaviourTree& copy);

		// Move constructor, moves existing tree
		BehaviourTree(BehaviourTree&& move);

		// Destructor deletes behaviours
		~BehaviourTree();

		// Copy assignment, clones right hand tree
		BehaviourTree& operator = (const BehaviourTree& rhs);

		// Move assignment, moves right hand tree
		BehaviourTree& operator = (BehaviourTree&& rhs);

		// Set a new root for this tree
		void SetRoot(const behaviour_ptr& a_Behaviour);

		// Set a new blackboard for this tree
		void SetBlackboard(Blackboard* a_Blackboard);

		// Update function, executes entire tree using given agent
		eBehaviourResult Execute(Agent* a_Agent, float deltaTime);

		// Inserts new behaviour into first composite with matching tag
		// If behaviour is not inserted, the behaviour is not deleted
		// Returns true if behaviour is inserted, false if not
		bool InsertIntoComposite(const behaviour_ptr& a_Behaviour, const std::string& a_CompositeTag);
		// Inserts existing tree's root into first composite with matching tag
		// If tree is inserted, the tree's root is set to nullptr
		// Returns true if behaviour is inserted, false if not
		bool InsertIntoComposite(BehaviourTree& a_Tree, const std::string& a_CompositeTag);

		// Clones existing behaviour into first composite with matching tag
		// If clone returns nullptr, the behaviour is not inserted
		// Returns true if behaviour is inserted, false if not
		bool CloneIntoComposite(const behaviour_ptr& a_Behaviour, const std::string& a_CompositeTag);
		// Clones existing tree's root into first composite with matching tag
		// If clone returns nullptr, the behaviour is not inserted
		// Returns true if behaviour is inserted, false if not
		bool CloneIntoComposite(BehaviourTree& a_Tree, const std::string& a_CompositeTag);

		// Returns first behaviour in tree with matching tag
		// Returns nullptr if no behaviour is found
		behaviour_ptr GetBehaviour(const std::string& a_Tag);

		// Gets first behaviour in tree with matching tag then returns result of cast
		// Returns nullptr if no behaviour is found
		template <typename Type> 
		Type* const GetBehaviour(const std::string& a_Tag);

		// Return the root of this tree
		behaviour_ptr GetRoot() const;

		// Return the blackboard of this tree
		Blackboard* GetBlackboard() const;

		// Return if there is a tree
		bool Empty() const;

		// Clear the tree
		void Clear();

	private:

		// Root of the tree
		behaviour_ptr m_Root;

		// Blackboard of the tree
		Blackboard* m_Blackboard;
	};

	template <typename Type> 
	Type* const BehaviourTree::GetBehaviour(const std::string& a_Tag)
	{
		// Assert if type is not a behaviour
		static_assert(std::is_base_of<IBehaviour, Type>::value, "Invalid search type");

		// Find this behaviour, capture the result
		behaviour_ptr Res = GetBehaviour(a_Tag);

		// Was the behaviour found?
		if (Res)
		{
			// Cast the behaviour to queried type, return the result
			return dynamic_cast<Type*>(Res.get());
		}

		// Return behaviour not found
		return nullptr;
	}
}

#endif // Michaels_BehaviourTree