#pragma once

#ifndef _IOSTORAGE_H_
#define _IOSTORAGE_H_

// Libary includes
#include <cstddef>

namespace LightBulb
{
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

		static T* get()
		{
			return storage;
		}

		static void clear()
		{
			storage = NULL;
		}
	};

	template<typename T>
	T* IOStorage<T>::storage = NULL;
}

#endif
