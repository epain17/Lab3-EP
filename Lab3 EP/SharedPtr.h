#pragma once
//#include <vector>
//
//template <class OBJ> 
//class ObjContainer {
//	std::vector<OBJ*> a;
//
//public:
//	void add(OBJ* obj) {
//		a.push_back(obj);  // call vector's standard method.
//	}
//	friend class SharedPtr;
//};
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

	SharedPtr(SharedPtr<T>&& other)
		: pointer(other.pointer), refs(other.refs)
	{
		other.pointer = nullptr;
	}

	~SharedPtr()
	{
		clear();
	}

	void reset()
	{
		pointer = nullptr;
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