#pragma once

#include "list.h"
#include "stack.h"

template <typename T>
class TStackList : public AbstractStack<T> {
private:
    TList<T> pMem; // Объявление переменной pMem типа TList, которая будет использоваться для хранения элементов стека
public:
    TStackList() {} //реализация не нужна, так как все возможные случаи обрабатываются в реализации односвязок

    TStackList(const TStackList<T>& ts) { // Конструктор копирования
        TNode<T>* tmp = ts.pMem.GetFirst(); // Получение первого узла из списка другого стека
        while (tmp != nullptr) { // Цикл до тех пор, пока не достигнут конец списка
            pMem.InsertEnd(tmp->key); // Вставка ключа (значения) последнего узла в конец текущего списка
            tmp = tmp->pNext; // Переход к следующему узлу
        }
    }

    ~TStackList() {} // уже есть деструктор листа

    bool isFull() const {
        TNode<int>* s = new TNode<int>(1); // Попытка выделить память под новый узел
        return (s == nullptr); // Возвращает true, если память не была выделена
    }

    bool isEmpty() const {
        return (pMem.GetFirst() == nullptr);
    }

    void push(T val) {
        if (isFull()) throw "error";

        pMem.InsertFirst(val);
    }

    void pop() {
        if (isEmpty()) throw "error";
        pMem.DeleteFirst();
    }

    T Top() const {
        if (isEmpty())  throw "error";
        return pMem.GetFirst()->key; // Возвращает значение верхнего элемента стека
    }
};
