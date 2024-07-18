#pragma once
#include <initializer_list>
namespace vtr
{
	template <class T>
	class Vector
	{
	private:
		T* arr = NULL;
		int elements = 0;
		int cap = 0;
	public:
		Vector(void);
		explicit Vector(T);
		Vector(std::initializer_list<T>);
		Vector(Vector<T>&);
		~Vector(void);
		Vector& operator=(const Vector&);
		Vector& operator=(Vector&&);
		Vector& operator=(std::initializer_list<T>);
		T& operator[](int);
		void assign(int, const T);
		T front(void);
		T back(void);
		T* begin(void);
		T* end(void);
		bool empty(void);
		int size(void);
		void reserve(int);
		int capacity(void);
		void clear(void);
		void insert(T*, T&&);
		void erase(T*);
		void push_back(T);
		void pop_back(void);
		void resize(size_t, T);
		void swap(Vector<T>&);
	};

	template<class T>
	Vector<T>::Vector(void) {}

	template<class T>
	Vector<T>::Vector(T a)
	{
		arr = new T(a);
		elements = 1;
		cap = elements;
	}

	template<class T>
	Vector<T>::Vector(std::initializer_list<T> init)
	{
		arr = new T[init.size()];
		int i = 0;
		for (auto it = init.begin(); it != init.end(); it++)
		{
			arr[i] = *it;
			i++;
		}
		elements = init.size();
		cap = elements;
	}

	template<class T>
	Vector<T>::Vector(Vector<T>& vect)
	{
		arr = new T[vect.elements];
		std::memcpy(arr, vect.arr, vect.elements * sizeof(T));
		elements = vect.elements;
		cap = elements;
	}

	template<class T>
	Vector<T>::~Vector(void)
	{
		elements = 0;
		cap = 0;
		delete[] arr;
	}

	template<class T>
	Vector<T>& Vector<T>::operator=(const Vector<T>& other) // check this again if need to use memcpy
	{
		~Vector();
		Vector(other);
		return *this;
	}

	template<class T>
	Vector<T>& Vector<T>::operator=(Vector<T>&& other)
	{
		~Vector();
		Vector(other);
		return *this;
	}

	template<class T>
	Vector<T>& Vector<T>::operator=(std::initializer_list<T> init)
	{
		delete[] arr;
		arr = new T[init.size()];
		int i = 0;
		for (auto it = init.begin(); it != init.end(); it++)
		{
			arr[i] = *it;
			i++;
		}
		elements = init.size();
		cap = elements;
		return *this;
	}

	template<class T>
	T& Vector<T>::operator[](int index)
	{
		return arr[index];
	}

	template<class T>
	void Vector<T>::assign(int count, const T val)
	{
		if (elements < count)
		{
			this->~Vector();
			arr = new T[count];
			cap = count;
		}
		elements = count;
		for (int i = 0; i < count; i++)
		{
			arr[i] = val;
		}
	}

	template<class T>
	T Vector<T>::front(void)
	{
		return arr[0];
	}

	template<class T>
	T Vector<T>::back(void)
	{
		return arr[elements - 1];
	}

	template<class T>
	T* Vector<T>::begin(void)
	{
		return arr;
	}

	template<class T>
	T* Vector<T>::end(void)
	{
		if (elements == 0)
			return NULL;
		else
			return (arr + elements);
	}

	template<class T>
	bool Vector<T>::empty(void)
	{
		return elements == 0 ? true : false;
	}

	template<class T>
	int Vector<T>::size(void)
	{
		return elements;
	}

	template<class T>
	void Vector<T>::reserve(int new_cap)
	{
		if (new_cap > cap)
		{
			T* temp = new T[new_cap];
			std::memcpy(temp, arr, elements * sizeof(T));
			delete[] arr;
			arr = temp;
			cap = new_cap;
		}
		else
		{
			return;
		}
	}

	template<class T>
	int Vector<T>::capacity(void)
	{
		return cap;
	}

	template<class T>
	void Vector<T>::clear(void)
	{
		elements = 0;
	}

	template<class T>
	void Vector<T>::insert(T* pos, T&& value)
	{
		if (elements < cap) 
		{
			T prev_val, current_val;
			current_val = value;
			T* it;
			for (it = pos; it <= end(); it++)
			{
				prev_val = *it;
				*it = current_val;
				current_val = prev_val;
			}
			*it = current_val;
			elements++;
		}
		else
		{
			T* temp = new T[elements + 1];
			T* it;
			int i = 0;
			for (it = begin(); it < end(); it++)
			{
				if (it == pos)
				{
					temp[i] = value;
					i++;
					if (elements == 0)
					{
						break;
					}
				}
				temp[i] = *it;
				i++;
			}
			if (it == pos)
			{
				temp[i] = value;
			}
			if(arr != NULL)
				delete[] arr;
			arr = temp;
			elements++;
			cap++;
		}
	}

	template<class T>
	void Vector<T>::erase(T* pos)
	{
		if (pos == end())
		{
			elements--;
		}
		else
		{
			for (auto it = pos; it < (end() - 1); it++)
			{
				*it = *(it + 1);
			}
			elements--;
		}
	}

	template<class T>
	void Vector<T>::push_back(T val)
	{
		if (elements >= cap)
		{
			T* temp = new T[cap * 2];
			std::memcpy(temp, arr, elements * sizeof(T));
			delete[] arr;
			arr = temp;
			cap *= 2;
		}
		arr[elements] = val;
		elements++;
	}

	template<class T>
	void Vector<T>::pop_back(void)
	{
		elements--;
	}

	template<class T>
	void Vector<T>::resize(size_t count, T val)
	{
		if (count <= elements)
		{
			elements = count;
		}
		else if (elements < count && count <= cap)
		{
			for (int i = elements; i < count; i++)
			{
				arr[i] = val;
			}
			elements = count;
		}
		else
		{
			T* temp = new T[count];
			std::memcpy(temp, arr, elements * sizeof(T));
			delete[] arr;
			arr = temp;
			for (int i = elements; i < count; i++)
			{
				arr[i] = val;
			}
			elements = count;
			cap = count;
		}
	}

	template<class T>
	void Vector<T>::swap(Vector<T>& other)
	{
		T* temp_arr = other.arr;
		int temp_cap = other.cap;
		int temp_elements = other.elements;
		other.arr = this->arr;
		other.cap = this->cap;
		other.elements = this->elements;
		this->arr = temp_arr;
		this->cap = temp_cap;
		this->elements = temp_elements;
	}
}