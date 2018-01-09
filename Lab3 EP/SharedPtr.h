#pragma once

template <class T>
class SharedPtr
{

	T* pointer;
	std::size_t *refs;

	void clear()
	{
		/*	if (!--*refs)
			{


				delete pointer;
				delete refs;

			}*/

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
		++*refs;
	}

	SharedPtr(SharedPtr<T>&& other)
		: pointer(other.pointer), refs(other.refs)
	{

		other.pointer = nullptr;
		other.refs = new std::size_t(1);
	}

	~SharedPtr()
	{
		clear();
	}

	void reset()
	{
		if (refs != nullptr)
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
	}

	template <typename Other>
	bool operator==(const SharedPtr<Other>& rhs)
	{
		return pointer == rhs.pointer;
	}

	template <typename Other>
	bool operator== (const Other& rhs)
	{
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
		return *refs == 1;
	}

	template <typename Other>
	SharedPtr<Other>& operator=(SharedPtr<Other>& other)
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
	SharedPtr<Other>& operator=(SharedPtr<Other>&& other)
	{


		pointer = other.pointer;
		refs = other.refs;
		other.pointer = nullptr;


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

	//template <typename Other>
	T* get() const { return pointer; }

	const T& operator*() const { return *pointer; }

	T* operator->() const { return &*pointer; }

	/*template <typename Other>
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
	}*/

};