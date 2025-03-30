#pragma once
#include <iostream>
#include <string>
#include "list.h"
using namespace std;

template<typename T>
class AbstractStack {
public:
    virtual void push(T value) = 0;			//правила реализации абстрактных классов, чтобы работало наследование. Два файла со стеками
    virtual void pop() = 0;
    virtual T Top() const = 0;
    virtual bool isEmpty() const = 0;
    virtual bool isFull() const = 0;
	virtual ~AbstractStack() {}
};

template<typename T>
class ArrayStack : public AbstractStack<T> {
private:
    T* data; // Указатель на массив данных типа T, который будет использоваться для хранения элементов стека
    int capacity;
    int topIndex;

public:
    ArrayStack(int capacity = 10) { // Конструктор, принимающий параметр ёмкости
        if (capacity <= 0) throw "error";
        this->capacity = capacity;
        this->data = new T[capacity];              // Выделение памяти под массив
        for (int i = 0; i < this->capacity; i++) { // Цикл для инициализации всех элементов массива
            this->data[i] = 0;
        }
        this->topIndex = -1;
    }

    ArrayStack(const ArrayStack& ts) { // Конструктор копирования
        this->capacity = ts.capacity;
        this->topIndex = ts.topIndex;
        this->data = new T[this->capacity];
        for (int i = 0; i < this->capacity; i++) { // Цикл для копирования элементов из другого стека
            this->data[i] = ts.data[i];
        }
    }

    ~ArrayStack() {
        delete[] data;
    }

    bool isFull() const {
        return (this->topIndex == this->capacity - 1);
    }

    bool isEmpty() const {
        return (this->topIndex == -1);
    }

    void push(T val) {
        if (isFull()) throw "error";
        topIndex++;
        this->data[topIndex] = val;
    }

    void pop() {
        if (isEmpty()) throw "error";
        this->topIndex--;
    }

    T Top() const {
        if (isEmpty()) throw "error";
        return data[topIndex];
    }
};
