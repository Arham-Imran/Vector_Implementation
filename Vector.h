#ifndef __vector__
#define __vector__
#include <initializer_list>
#include <cstring>
namespace vtr
{
	template <class T>
	class vector
	{
	private:
		T* arr = NULL;
		int elements = 0;
		int cap = 0;
	public:
		vector(void);
		explicit vector(T);
		vector(std::initializer_list<T>);
		vector(vector<T>&);
		vector(vector<T>&&);
		~vector(void);
		vector& operator=(const vector&);
		vector& operator=(vector&&);
		vector& operator=(std::initializer_list<T>);
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
		void swap(vector<T>&);
	};

	template<class T>
	vector<T>::vector(void) {}

	template<class T>
	vector<T>::vector(T a)
	{
		arr = new T(a);
		elements = 1;
		cap = elements;
	}

	template<class T>
	vector<T>::vector(std::initializer_list<T> init)
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
	vector<T>::vector(vector<T>& vect)
	{
		arr = new T[vect.elements];
		std::memcpy(arr, vect.arr, vect.elements * sizeof(T));
		elements = vect.elements;
		cap = vect.cap;
	}

	template<class T>
	vector<T>::vector(vector<T>&& other)
	{
		arr = other.arr;
		elements = other.elements;
		cap = other.cap;
		other.arr = nullptr;
		elements = 0;
		cap = 0;
	}

	template<class T>
	vector<T>::~vector(void)
	{
		elements = 0;
		cap = 0;
		delete[] arr;
	}

	template<class T>
	vector<T>& vector<T>::operator=(const vector<T>& other) // check this again if need to use memcpy
	{
		arr = new T[other.elements];
		std::memcpy(arr, other.arr, other.elements * sizeof(T));
		elements = other.elements;
		cap = elements;
		return *this;
	}

	template<class T>
	vector<T>& vector<T>::operator=(vector<T>&& other)
	{
		arr = new T[other.elements];
		std::memcpy(arr, other.arr, other.elements * sizeof(T));
		elements = other.elements;
		cap = elements;
		return *this;
	}

	template<class T>
	vector<T>& vector<T>::operator=(std::initializer_list<T> init)
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
	T& vector<T>::operator[](int index)
	{
		return arr[index];
	}

	template<class T>
	void vector<T>::assign(int count, const T val)
	{
		if (elements < count)
		{
			this->~vector();
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
	T vector<T>::front(void)
	{
		return arr[0];
	}

	template<class T>
	T vector<T>::back(void)
	{
		return arr[elements - 1];
	}

	template<class T>
	T* vector<T>::begin(void)
	{
		return arr;
	}

	template<class T>
	T* vector<T>::end(void)
	{
		if (elements == 0)
			return NULL;
		else
			return (arr + elements);
	}

	template<class T>
	bool vector<T>::empty(void)
	{
		return elements == 0 ? true : false;
	}

	template<class T>
	int vector<T>::size(void)
	{
		return elements;
	}

	template<class T>
	void vector<T>::reserve(int new_cap)
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
	int vector<T>::capacity(void)
	{
		return cap;
	}

	template<class T>
	void vector<T>::clear(void)
	{
		elements = 0;
	}

	template<class T>
	void vector<T>::insert(T* pos, T&& value)
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
	void vector<T>::erase(T* pos)
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
	void vector<T>::push_back(T val)
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
	void vector<T>::pop_back(void)
	{
		if(elements > 0)
			elements--;
		else
			return;
	}

	template<class T>
	void vector<T>::resize(size_t count, T val)
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
	void vector<T>::swap(vector<T>& other)
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
#endif