#pragma once

template <class T>
class SharedPtr
{

	T* pointer;
	std::size_t *refs;

	void clear()
	{
		if (!--*refs)
		{
			delete pointer;
			delete refs;
		}
	}

public:
	explicit SharedPtr(T* p = NULL)
		: pointer(p), refs(new std::size_t(1)) {}

	SharedPtr(const SharedPtr<T>& other)
		: pointer(other.pointer), refs(other.refs)
	{
		++*refs;
	}

	~SharedPtr()
	{
		clear();
	}

	template <typename Other>
	SharedPtr<Other> operator== (SharedPtr<Other> &rhs)
	{
		 if (rhs->pointer == nullptr)
		 {
			 return false;
		 }
		return true;
	}

	operator bool() const { return pointer != nullptr; }

	bool unique() const
	{
		return *refs == 1;
	}
	
	template <typename Other>
	SharedPtr<Other> operator=(const SharedPtr<Other>& other)
	{
		if (this != &other)
		{
			clear();
			pointer = other.pointer;
			refs = other.refs;
			++*refs;
		}

		return *this;
	}

	template <typename Other>
	SharedPtr<Other> operator=(Other* p)
	{
		if (pointer != p)
		{
			pointer = p; 
			*refs = 1;
		}

		return *this;
	}

	template <typename Other>
	Other operator *()
	{
		return *pointer;
	}

	template <typename Other>
	const Other& operator *() const
	{
		return *pointer;
	}

	template <typename Other>
	Other* operator->() const
	{
		return pointer;
	}

	std::size_t getCounts()
	{
		return *refs;
	}

};