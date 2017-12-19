#pragma once

template <class T>
class SharedPtr
{
	T* ptr;
	int *count;

	SharedPtr() {};
	SharedPtr(nullptr);
	SharedPtr(*T ptr);


};