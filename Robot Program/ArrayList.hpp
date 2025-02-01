#pragma once
template<typename T>
class ArrayList {
private:
	T* array;
	int capacity;
	int size;

	void resize(int newCapacity) {
		T* newArray = new T[newCapacity];
		for (int i = 0; i < size; i++) {
			newArray[i] = array[i];
		}
		delete[] array;
		array = newArray;
		capacity = newCapacity;
	}

public:
	ArrayList(int initialCapacity = 10) {
		capacity = initialCapacity;
		size = 0;
		array = new T[capacity];
	}

	~ArrayList() {
		delete[] array;
	}

	void add(T element) {
		if (size == capacity) {
			resize(capacity * 2);
		}
		array[size++] = element;
	}

	T get(int index) {
		if (index < 0 || index >= size) {
			Serial.println("Index out of bounds");
			return T();
		}
		return array[index];
	}

	void set(int index, T element) {
		if (index < 0 || index >= size) {
			Serial.println("Index out of bounds");
			return;
		}
		array[index] = element;
	}

	int getSize() {
		return size;
	}

	bool isEmpty() {
		return size == 0;
	}

	void clear() {
		delete[] array;
		array = new T[capacity];
		size = 0;
	}
	
	T operator[](int index) {
		return this->get(index);
	}
};