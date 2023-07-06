/*!
* \brief Шаблонный класс динамической коллекции на основе динамического массива.

Создать шаблонный класс динамической коллекции (связный список, очередь динамический
массив).
Обязательными пунктами задания являются следующие возможности коллекции:
- размещение в себе элементов произвольного типа;
- добавление и удаление элементов;
- предоставление доступа к элементам массива;
- возможность работы с колеекцией через range based for, std::size;
- корректная передача по параметру в функции.
Дополнительные возможности:
работа независимо с хранением данных и с выделением памяти;
возможность удаления и вставки новых элементов в произвольные места коллекции.
*/
#ifndef _VECTOR_H_
#define _VECTOR_H_

template <typename T>
class Vector
{
public:
	///////////////////////////////////////////////////////////////////////////////////////
	class Iterator
	{
	public:
		Iterator() = delete;
		Iterator(T* data) : data_(data) {}
		Iterator& operator++()
		{
			data_++;
			return *this;
		}

		Iterator& operator++(int)
		{
			Iterator tmp(*this);
			data_++;
			return tmp;
		}

		Iterator& operator--()
		{
			data_--;
			return *this;
		}

		Iterator& operator--(int)
		{
			Iterator tmp(*this);
			data_++;
			return tmp;
		}

		Iterator& operator+(int num)
		{
			Iterator it(this->data_ + num);
			(*this) = it;
			return *this;
		}

		Iterator& operator-(int num)
		{
			Iterator it(this->data_ - num);
			(*this) = it;
			return *this;
		}

		bool operator==(const Iterator& obj) const
		{
			return this->data_ == obj.data_;
		}

		bool operator!=(const Iterator& obj) const
		{
			return this->data_ != obj.data_;
		}

		T& operator*()
		{
			return *data_;
		}


	private:
		T* data_;
	};
	///////////////////////////////////////////////////////////////////////////////////

	Vector() : _array(nullptr), _size(0) {}

	Vector(const Vector& v) : _array(new T[v._size]), _size(v._size)
	{
		for (size_t i = 0; i < _size; i++)
		{
			_array[i] = v._array[i];
		}
	}

	Vector(int size) : _array(new T[size]), _size(size) {}

	Vector(const std::initializer_list<T>& list) : Vector(list.size())
	{
		int i = 0;
		for (auto& el : list)
		{
			this->_array[i] = el;
			i++;
		}
	}

	~Vector()
	{
		this->clear();
	}

	Vector& operator=(const Vector& v)
	{
		if (this != &v)
		{
			if (this->_array != nullptr)
			{
				delete[] this->_array;
				this->_array = nullptr;
			}
			this->_size = v._size;
			for (size_t i = 0; i < this->_size; i++)
			{
				this->_array[i] = v._array[i];
			}
			return *this;
		}
		return *this;
	}

	void push_back(const T& data)
	{
		this->_size++;
		T* newArray = new T[this->_size]{};
		for (size_t i = 0; i < this->_size - 1; i++)
		{
			newArray[i] = this->_array[i];
		}
		newArray[this->_size - 1] = data;
		delete[] this->_array;
		this->_array = newArray;
	}

	void pop_back()
	{
		this->_size--;
		T* newArray = new T[this->_size]{};
		for (size_t i = 0; i < this->_size; i++)
		{
			newArray[i] = this->_array[i];
		}
		delete[] this->_array;
		this->_array = newArray;
	}

	void insert(const T& data, int index)
	{
		this->_size++;
		T* newArray = new T[this->_size]{};
		for (size_t i = 0; i < index; ++i)
		{
			newArray[i] = this->_array[i];
		}
		newArray[index] = data;
		for (size_t i = index; i < this->_size - 1; ++i)
		{
			newArray[i + 1] = this->_array[i];
		}
		delete[] this->_array;
		this->_array = newArray;
	}

	void erase(int index)
	{
		T* newArray = new T[this->_size - 1]{};
		for (size_t i = 0; i < index; ++i)
		{
			newArray[i] = this->_array[i];
		}
		for (size_t i = index + 1; i < this->_size; ++i)
		{
			newArray[i - 1] = this->_array[i];
		}
		this->_size--;
		delete[] this->_array;
		this->_array = newArray;
	}

	void clear()
	{
		delete[] _array;
		_array = nullptr;
	}

	T front()
	{
		return *_array;
	}

	int size() const
	{
		return _size;
	}

	T& operator[](int i)
	{
		return _array[i];
	}

	const T& operator[](int i) const
	{
		return _array[i];
	}

	T& at(int i) 
	{
		return _array[i];
	}

	const T& at(int i) const
	{
		return _array[i];
	}

	Iterator begin()
	{
		return Iterator(_array);
	}

	Iterator begin() const
	{
		return Iterator(_array);
	}

	Iterator end()
	{
		return Iterator(_array + _size);
	}

	Iterator end() const
	{
		return Iterator(_array + _size);
	}

	Iterator rbegin()
	{
		return Iterator(_array + _size - 1);
	}

	Iterator rend()
	{
		return Iterator(_array - 1);
	}

	void swap(Vector& v)
	{
		if (this->_size != v._size)
			return;
		else
		{
			for (size_t i = 0; i < this->_size; i++)
			{
				std::swap(this->_array[i], v._array[i]);
			}
		}
		return;
	}


private:
	T* _array;
	int _size;
};


#endif