#include "Behaviours\Tree\BehaviourTree.h"

#include "Behaviours\Interface\IComposite.h"
#include "Behaviours\Interface\IDecorator.h"

namespace Behaviour
{
	BehaviourTree::BehaviourTree()
		: m_Root(nullptr), m_Blackboard(nullptr)
	{

	}

	BehaviourTree::BehaviourTree(const behaviour_ptr& a_Root)
		: m_Root(a_Root), m_Blackboard(nullptr)
	{

	}

	BehaviourTree::BehaviourTree(const BehaviourTree& copy)
		: m_Blackboard(copy.m_Blackboard)
	{
		// Clear this tree
		Clear();

		// Is tree empty?
		if (copy.Empty())
		{
			// Set root to nullptr
			m_Root = nullptr;
		}
		else
		{
			// Set root to clone of existing tree
			m_Root = copy.m_Root->Clone();
		}
	}

	BehaviourTree::BehaviourTree(BehaviourTree&& move)
		: m_Root(std::move(move.m_Root)), m_Blackboard(move.m_Blackboard)
	{
		// Set other tree's blackboard to nullptr
		move.m_Blackboard = nullptr;
	}

	BehaviourTree::~BehaviourTree()
	{
		
	}

	BehaviourTree& BehaviourTree::operator=(const BehaviourTree& rhs)
	{
		// Clear this tree
		Clear();

		// Is other tree not empty?
		if (!rhs.Empty())
		{
			// Set root to clone of existing tree
			m_Root = rhs.m_Root->Clone();
		}

		// Set blackboard to tree's blackboard
		m_Blackboard = rhs.m_Blackboard;

		// Return this tree
		return *this;
	}

	BehaviourTree& BehaviourTree::operator=(BehaviourTree&& rhs)
	{
		// Clear this tree
		Clear();

		// Set root and blackboard to other tree's root and blackboard
		m_Root = std::move(rhs.m_Root);
		m_Blackboard = rhs.m_Blackboard;

		// Set blackboard to nullptr
		rhs.m_Blackboard = nullptr;

		// Return this tree
		return *this;
	}

	void BehaviourTree::SetRoot(const behaviour_ptr& a_Behaviour)
	{
		// Clear any potential tree that might exist
		Clear();

		// Set the new root of the tree
		m_Root = a_Behaviour;
	}

	void BehaviourTree::SetBlackboard(Blackboard* a_Blackboard)
	{
		// Set the blackboard
		m_Blackboard = a_Blackboard;
	}

	eBehaviourResult BehaviourTree::Execute(Agent* a_Agent, float deltaTime)
	{
		// Starting from the root, execute the tree. Return the result
		return m_Root->Execute(a_Agent, deltaTime);
	}

	bool BehaviourTree::InsertIntoComposite(const behaviour_ptr& a_Behaviour, const std::string& a_CompositeTag)
	{
		// Assert if tree is empty
		assert(!Empty() && "Tree is empty, use set root instead");

		// Find this composite behaviour starting from root
		behaviour_ptr Get = m_Root->Tag() == a_CompositeTag ? m_Root : m_Root->Find(a_CompositeTag);

		// Was the tag found?
		if (Get)
		{
			// Cast the behaviour to composite type
			std::shared_ptr<IComposite> Com = std::dynamic_pointer_cast<IComposite>(Get);

			// Assert if cast failed
			assert(Com && "Tagged behaviour is not of composite type");

			// Insert the behaviour
			Com->Insert(a_Behaviour);

			// Return behaviour inserted
			return true;
		}

		// Return behaviour not inserted
		return false;
	}

	bool BehaviourTree::InsertIntoComposite(BehaviourTree& a_Tree, const std::string& a_CompositeTag)
	{
		// Assert if tree is empty
		assert(!Empty() && "Tree is empty, use set root instead");

		// Find this composite behaviour starting from root
		behaviour_ptr Get = m_Root->Tag() == a_CompositeTag ? m_Root : m_Root->Find(a_CompositeTag);

		// Was the tag found?
		if (Get)
		{
			// Cast the behaviour to composite type
			std::shared_ptr<IComposite> Com = std::dynamic_pointer_cast<IComposite>(Get);

			// Assert if cast failed
			assert(Com && "Tagged behaviour is not of composite type");

			// Insert the tree's root
			Com->Insert(a_Tree.m_Root);

			// Set the tree's root to nullptr
			a_Tree.m_Root.reset();

			// Return behaviour inserted
			return true;
		}

		// Return behaviour not inserted
		return false;
	}

	bool BehaviourTree::CloneIntoComposite(const behaviour_ptr& a_Behaviour, const std::string& a_CompositeTag)
	{
		// Assert if tree is empty
		assert(!Empty() && "Tree is empty, use set root instead");

		// Find this composite behaviour starting from root
		behaviour_ptr Get = m_Root->Tag() == a_CompositeTag ? m_Root : m_Root->Find(a_CompositeTag);

		// Was the tag found?
		if (Get)
		{
			// Cast the behaviour to composite type
			std::shared_ptr<IComposite> Com = std::dynamic_pointer_cast<IComposite>(Get);

			// Assert if cast failed
			assert(Com && "Tagged behaviour is not of composite type");

			// Clone this behaviour
			behaviour_ptr Clo = a_Behaviour->Clone();

			// Was the behaviour cloned?
			if (Clo)
			{
				// Insert the clone
				Com->Insert(Clo);

				// Return clone inserted
				return true;
			}
		}

		// Return clone not inserted
		return false;
	}

	bool BehaviourTree::CloneIntoComposite(BehaviourTree& a_Tree, const std::string & a_CompositeTag)
	{
		// Assert if tree is empty
		assert(!Empty() && "Tree is empty, use set root instead");

		// Find this composite behaviour starting from root
		behaviour_ptr Get = m_Root->Tag() == a_CompositeTag ? m_Root : m_Root->Find(a_CompositeTag);

		// Was the tag found?
		if (Get)
		{
			// Cast the behaviour to composite type
			std::shared_ptr<IComposite> Com = std::dynamic_pointer_cast<IComposite>(Get);

			// Assert if cast failed
			assert(Com && "Tagged behaviour is not of composite type");

			// Clone the tree's root
			behaviour_ptr Clo = a_Tree.m_Root->Clone();

			// Was the behaviour cloned?
			if (Clo)
			{
				// Insert the clone
				Com->Insert(Clo);

				// Return clone inserted
				return true;
			}
		}

		// Return clone not inserted
		return false;
	}

	behaviour_ptr BehaviourTree::GetBehaviour(const std::string& a_Tag)
	{
		// Is the tree empty?
		if (Empty())
		{
			// Return behaviour not found
			return nullptr;
		}

		// Find this behaviour starting from the root, return the result
		return m_Root->Find(a_Tag);
	}

	behaviour_ptr BehaviourTree::GetRoot() const 
	{ 
		// Return the root of this tree
		return m_Root; 
	}

	Blackboard* BehaviourTree::GetBlackboard() const 
	{ 
		// Return the blackboard of this tree
		return m_Blackboard; 
	}

	bool BehaviourTree::Empty() const
	{
		// Return if tree is empty
		return !m_Root;
	}

	void BehaviourTree::Clear()
	{
		// Is there a tree?
		if (m_Root)
		{
			// Delete the tree
			m_Root.reset();
		}
	}
}