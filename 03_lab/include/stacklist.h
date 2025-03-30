#pragma once

#include "list.h"
#include "stack.h"

template <typename T>
class TStackList : public AbstractStack<T> {
private:
    TList<T> pMem; // ���������� ���������� pMem ���� TList, ������� ����� �������������� ��� �������� ��������� �����
public:
    TStackList() {} //���������� �� �����, ��� ��� ��� ��������� ������ �������������� � ���������� ����������

    TStackList(const TStackList<T>& ts) { // ����������� �����������
        TNode<T>* tmp = ts.pMem.GetFirst(); // ��������� ������� ���� �� ������ ������� �����
        while (tmp != nullptr) { // ���� �� ��� ���, ���� �� ��������� ����� ������
            pMem.InsertEnd(tmp->key); // ������� ����� (��������) ���������� ���� � ����� �������� ������
            tmp = tmp->pNext; // ������� � ���������� ����
        }
    }

    ~TStackList() {} // ��� ���� ���������� �����

    bool isFull() const {
        TNode<int>* s = new TNode<int>(1); // ������� �������� ������ ��� ����� ����
        return (s == nullptr); // ���������� true, ���� ������ �� ���� ��������
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
        return pMem.GetFirst()->key; // ���������� �������� �������� �������� �����
    }
};
