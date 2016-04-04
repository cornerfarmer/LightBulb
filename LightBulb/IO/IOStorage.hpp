#pragma once

#ifndef _IOSTORAGE_H_
#define _IOSTORAGE_H_

// Libary includes
#include <cstddef>

template<class T>
class IOStorage
{
private:
	static T* storage;
public:
	static void push(T* newStorage)
	{
		storage = newStorage;
	}

	static T* pop()
	{
		T* temp = storage;
		storage = NULL;
		return temp;
	}
};

template<typename T>
T* IOStorage<T>::storage = NULL;

#endif
