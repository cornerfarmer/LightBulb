#pragma once

#ifndef _IOSTORAGE_H_
#define _IOSTORAGE_H_

// Libary includes
#include <cstddef>

namespace LightBulb
{
	/**
	 * \brief A helper class which temporary stores objects between serialization functions.
	 * \tparam T The type which should be stored.
	 */
	template<class T>
	class IOStorage
	{
	private:
		/**
		 * \brief The current storage.
		 */
		static T* storage;
	public:
		/**
		 * \brief Fills the storage.
		 * \param newStorage The new object which should be stored.
		 * \note This will remove the previous stored object.
		 */
		static void push(T* newStorage)
		{
			storage = newStorage;
		}

		/**
		 * \brief Returns and removes the current stored object.
		 * \return The current stored object.
		 */
		static T* pop()
		{
			T* temp = storage;
			storage = NULL;
			return temp;
		}

		/**
		 * \brief Returns the current stored object.
		 * \return The current stored object.
		 */
		static T* get()
		{
			return storage;
		}

		/**
		 * \brief Clears the current storage.
		 */
		static void clear()
		{
			storage = NULL;
		}
	};

	template<typename T>
	T* IOStorage<T>::storage = NULL;
}

#endif
