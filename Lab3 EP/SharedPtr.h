#pragma once
#include <assert.h>


template <class T>
class SharedPtr
{

	T* pointer;
	std::size_t *refs;

	void clear()
	{

		if (refs != nullptr)
		{
			(*refs)--;
			if (*refs == 0)
			{
				delete pointer;
				delete refs;
			}
		}
	}

public:
	explicit SharedPtr(T* p = NULL)
		: pointer(p), refs(new std::size_t(1)) {}

	SharedPtr(const SharedPtr<T>& other)
		: pointer(other.pointer), refs(other.refs)
	{
		if (pointer != NULL)
		{
			++*refs;
		}
		else
		{
			--*refs;
		}
		//assert(Invariant());

	}

	SharedPtr(SharedPtr<T>&& other)
		: pointer(other.pointer), refs(other.refs)
	{

		/*other.pointer = nullptr;
		other.refs = new std::size_t(1);*/
		++*refs;
		other.reset();
	}

	~SharedPtr()
	{
		clear();
	}

	void reset()
	{
		//assert(Invariant());
		if (pointer != nullptr || refs != nullptr)
		{
			(*refs)--;

			if (*refs == 0)
			{
				delete pointer;
				delete refs;
			}

			refs = nullptr;
			pointer = nullptr;
		}
		//assert(Invariant());
	}

	template <typename Other>
	bool operator==(const SharedPtr<Other>& rhs)
	{
		if (rhs.pointer == nullptr)
		{
			return true;
		}
		return pointer == rhs.pointer;
	}

	template <typename Other>
	bool operator== (const Other& rhs)
	{
		if (rhs == nullptr)
		{
			return true;
		}
		return pointer == nullptr;
	}

	template <typename Other>
	friend bool operator< (const SharedPtr<T>& lhs, const SharedPtr<Other>& rhs)
	{
		return lhs.pointer < rhs.pointer;
	}

	operator bool() const
	{
		return pointer != nullptr;
	}

	bool unique() const
	{

		if (pointer != nullptr)
		{
			return *refs == 1;
		}
		else
		{
			return *refs == 0;
		}
	}

	template <typename Other>
	SharedPtr<Other>& operator=(SharedPtr<Other>& other)
	{
		assert(Invariant());
		if (this != &other && pointer != nullptr)
		{
			clear();
			pointer = other.pointer;
			refs = other.refs;
			++*refs;

		}
		assert(Invariant());

		return *this;
	}

	template <typename Other>
	SharedPtr<Other>& operator=(SharedPtr<Other>&& other)
	{
		assert(Invariant());
		if (pointer != nullptr)
		{
			pointer = other.pointer;
			refs = other.refs;
			other.pointer = nullptr;
			other.reset();
		}
		assert(Invariant());

		return *this;
	}

	template <typename Other>
	SharedPtr<Other> operator=(Other* p)
	{
		assert(Invariant());
		//kolla så att inte nullptr och att den gamla pekaren tas bort.
		if (pointer != p && p != nullptr)
		{

			pointer = p;
			*refs = 1;
			delete p;
			assert(Invariant());

		}

		return *this;
	}

	T* get() const { return pointer; }

	const T& operator*() const { return *pointer; }

	T* operator->() const { return &*pointer; }

	bool Invariant()
	{
		if (pointer == nullptr)
		{
			//Om pointer pekaren är nullptr så får man inte kolla på refs. Refs ska inte vara satt till något. 
			//Om inte utgår vi rån att refs är satt till något
			return false;
		}

		else if (pointer != nullptr)
		{
			return *refs>0;
		}
		//return !pointer || *refs > 0;
	}



};