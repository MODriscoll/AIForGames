#pragma once

#ifndef Michaels_Containers_ObjectPool
#define Michaels_Containers_ObjectPool

#include <array>

namespace Containers
{
	// Forward declerations
	template <typename Type>
	class Node;
	template <typename Type, size_t Size>
	class ObjectPool;

	// Second draft, now uses std::array
	template <typename Type, size_t Size>
	class ObjectPool
	{
	public:

		// Type define for object pool
		using Pool = std::array<Node, Size>;

		// Easy access to underlying arrays iterators
		using Iterator = Pool::iterator;
		using Reverse_Iterator = Pool::reverse_iterator;

	public:

		class Node
		{
		public:

			Node() = delete;

			Node(const Type& a_Node)
				: m_Node(a_Node), m_bActive(false) { }

			Node(Type&& a_Node)
				: m_Node(std::forward<Type>(a_Node)), m_bActive(false) { }

			Node(const Node& copy) = default;
			Node(Node&& move) = default;

			~Node() = default;

			bool operator == (const Node& rhs) const
			{
				return (m_Node == rhs.m_Node && m_bActive == rhs.m_bActive);
			}

			bool operator != (const Node& rhs) const
			{
				return !(*this == rhs);
			}

			bool operator < (const Node& rhs) const
			{
				return m_bActive > rhs.m_bActive;
			}

			bool operator > (const Node& rhs) const
			{
				return m_bActive < rhs.m_bActive;
			}

			Node& operator = (const Node& rhs) = default;
			Node& operator = (Node&& rhs) = default;

			Type& Node()
			{
				return m_Node;
			}

			const Type& Node() const
			{
				return m_Node;
			}

			bool Active() const
			{
				return m_bActive;
			}

		private:

			friend ObjectPool<Type, Size>;

			Type m_Node;

			bool m_bActive;
		};

	public:

		ObjectPool()
		{
			static_assert(Size != 0u, "Pool must at least have one object");
		}

		ObjectPool(const Type& a_Default)
		{
			static_assert(Size != 0u, "Pool must at least have one object");

			// Fill the pool using default object given
			m_Pool.fill(Node(a_Default));
		}

		ObjectPool(const std::array<Type, Size>& a_Array)
		{
			static_assert(Size != 0u, "Pool must at least have one object");

			// Cycle through each object in the given array
			for (size_t idx = 0; idx < Size; ++idx)
			{
				// Create a new node using this object
				m_Pool[idx] = Node(a_Array[idx]);
			}
		}

		ObjectPool(const ObjectPool& copy) = default;
		ObjectPool(ObjectPool&& move) = default;

		~ObjectPool() = default;

		// Purposely left out
		// operator = (const Type& rhs)
		// operator = (const std::array<Type, Size>& rhs)
		// due to active issues ( not technical issues but design issues )

		ObjectPool& operator = (const ObjectPool& rhs) = default;
		ObjectPool& operator = (ObjectPool&& rhs) = default;

		void Activate()
		{
			// Are all objects already active?
			if (m_Active == Size)
				return;	// End this function

			// Set the first unactive object to active
			m_Pool[m_Active].m_bActive = true;

			// Increase the active count
			++m_Active;
		}

		void Activate(Iterator a_Iterator)
		{
			// Get the index of this iterator
			size_t Index = std::distance(m_Pool.begin(), a_Iterator);

			// Set the first unactive object to active
			m_Pool[Index].m_bActive = true;

			// Was this iterator not the
			// first unactive object?
			if (Index > m_Active)
			{
				// Swap these the first unactivate
				// object with the new active object
				m_Pool.swap(a_Iterator, Split());
			}

			// Increase the active count
			++m_Active;
		}

		void ActivateAll()
		{
			// Cycle through all the objects that are unactive
			for (auto it = Split(); it != End(); ++it)
			{
				// Set this object to active
				(*it).m_bActive = true;
			}

			// Set the active to max
			m_Active = Size;
		}

		void Deactivate()
		{
			// Are no objects active?
			if (m_Active == 0)
				return;	// End this function

			// Decrease the active count
			--m_Active;

			// Set the last active object to unactive
			m_Pool[m_Active].m_bActive = false;
		}

		void Deactivate(Iterator a_Iterator)
		{
			// Get the index of this iterator
			size_t Index = std::distance(m_Pool.begin(), a_Iterator);

			// Set the last active object to unactive
			m_Pool[Index].m_bActive = false;

			// Decrease the active count
			--m_Active;

			// Was this iterator not
			// the last active object?
			if (Index < m_Active)
			{
				// Swap these the last activate
				// object with the unactive object
				m_Pool.swap(a_Iterator, Split());
			}
		}

		void DeactivateAll()
		{
			// Cycle through all the objects that are active
			for (auto it = Begin(); it != End(); ++it)
			{
				// Set this object to unactive
				(*it).m_bActive = false;
			}

			// Set the active count to 0
			m_Active = 0;
		}

		Iterator Begin()
		{
			return m_Pool.begin();
		}

		Iterator End()
		{
			return m_Pool.end();
		}

		Iterator Split()
		{
			return m_Pool.begin() + m_Active;
		}

		Reverse_Iterator RBegin()
		{
			return m_Pool.rbegin();
		}

		Reverse_Iterator REnd()
		{
			return m_Pool.rend();
		}

		Reverse_Iterator RSplit()
		{
			return m_Pool.rbegin() + (Size - m_Active);
		}

		Node& operator [] (size_t idx)
		{
			return m_Pool[idx];
		}

		const Node& operator [] (size_t idx) const
		{
			return m_Pool[idx];
		}

		size_t Nodes() const
		{
			return Size;
		}

		size_t Active() const
		{
			return m_Active;
		}

	protected:

		Pool m_Pool;

		size_t m_Active;
	};
}

#endif // Michaels_Containers_ObjectPool