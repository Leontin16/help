#pragma once
template <typename T>
struct TNode {
	T key;											// значение узла
	TNode* pNext;									// указатель на следующий узел
	TNode(T k) : key(k), pNext(nullptr) {}			// конструктор инициализирует ключ и обнуляет указатель
};

template <typename T>								// объявление шаблона класса
class TList {
private:
	TNode<T>* pFirst;								// указатель на первый узел списка
public:
	TList() :pFirst(nullptr) {}						// инициализация списка
	TList(const TList& other) : pFirst(nullptr) {	// конструктор копирования, создающий новый список на основе другого.
		if (other.pFirst == nullptr) {				// проверка, пустой ли другой список.
			return;									// если пустой, выходим из конструктора.
		}
		pFirst = new TNode<T>(other.pFirst->key);	// создаем первый узел нового списка, копируя ключ из другого списка.
		TNode<T>* tmp = pFirst;						// указатель на текущий узел в новом списке.
		TNode<T>* curr = other.pFirst->pNext;		// указатель на следующий узел в другом списке.

		while (curr != nullptr) {					// проходим по всем узлам другого списка.
			tmp->pNext = new TNode<T>(curr->key);	// создаем новый узел и добавляем его в конец нового списка.
			tmp = tmp->pNext;						// переходим к новому узлу в новом списке.
			curr = curr->pNext;						// переходим к следующему узлу в другом списке.
		}
	}
	~TList() {
		while (pFirst != nullptr) {
			TNode<T>* tmp = pFirst;
			pFirst = pFirst->pNext;
			delete tmp;
		}
	}
	TNode<T>* Search(T key) {
		if (this->pFirst == nullptr) throw "error";
		TNode<T>* tmp = pFirst;						// указатель на текущий узел
		while (tmp != nullptr && tmp->key != key) { // пока не достигнут конец списка и ключ не найден.
			tmp = tmp->pNext;						// переходим к следующему узлу.
		}
		return tmp;									// возвращаем найденный узел или nullptr, если не найден.
		}

	void InsertEnd(T key) {							// метод для вставки нового узла в конец списка.
		TNode<T>* tmp1 = new TNode<T>(key);			// создаем новый узел с заданным ключом.

		if (pFirst == nullptr) {
			pFirst = tmp1;
			return;
		}

		TNode<T>* tmp = this->pFirst;				// указатель на первый узел списка.
		while (tmp->pNext != nullptr) {				// проходим до последнего узла списка.
			tmp = tmp->pNext;						// переходим к следующему узлу.
		}
		tmp->pNext = tmp1;							// добавляем новый узел в конец списка.

	}

	void InsertBefore(T searchKey, T key) {
		TNode<T>* tmp1 = new TNode<T>(key);			// создаем новый узел с заданным ключом.
		if (pFirst == nullptr) throw "error";
		TNode<T>* tmp = this->pFirst;				// указатель на первый узел списка.
		while (tmp->pNext != nullptr && tmp->pNext->key != searchKey) {		// ищем узел перед которым нужно вставить новый (текущий эл-т последний в списке, и проверка на соответствие текущего узла и искомого значения)
			tmp = tmp->pNext;
		}
		TNode<T>* findElem = tmp->pNext;			// Сохраняем указатель на следующий узел после найденного.
		tmp->pNext = tmp1;							// Вставляем новый узел в список.
		tmp1->pNext = findElem;						// Устанавливаем указатель нового узла на следующий элемент после него.
	}

	void InsertAfter(T searchKey, T key) {			
		TNode<T>* tmp1 = new TNode<T>(key);			// Создаем новый узел с заданным ключом.
		if (pFirst == nullptr) throw "error";
		TNode<T>* tmp = this->pFirst;				// Указатель на первый узел списка.
		while (tmp != nullptr && tmp->key != searchKey) {		// существует ли узел, и совпадает ли ключ текущего узла с искомым значением
			tmp = tmp->pNext;						// Вставляем новый узел после найденного
		}
		TNode<T>* findElem = tmp->pNext;			// Сохраняем указатель на следующий элемент после найденного.
		tmp->pNext = tmp1;							// Вставляем новый узел в список после найденного элемента.
		tmp1->pNext = findElem;						// Устанавливаем указатель нового узла на следующий элемент после него.
	}
	void InsertFirst(T key) {
		TNode<T>* tmp1 = new TNode<T>(key);			// Создаем новый узел с заданным ключом.
		if (pFirst == nullptr) {					// Если список пустой,
			pFirst = tmp1;							// устанавливаем новый узел как первый.
			return;									// Выходим из метода.
		}
		TNode<T>* tmp = this->pFirst;				// Указатель на текущий первый элемент списка.
		tmp1->pNext = tmp;							// Устанавливаем указатель нового узла на старый первый элемент списка.
		this->pFirst = tmp1;						// Новый узел становится первым элементом списка.

	}
	TNode<T>* GetLast() const {
		if (pFirst == nullptr) return nullptr;		// Если список пустой, возвращаем nullptr.
		TNode<T>* tmp = pFirst;						// Указатель на первый элемент списка.

		while (tmp->pNext != nullptr) {				
			tmp = tmp->pNext;						
		}
		return tmp;

	}
	TNode<T>* GetFirst() const { return this->pFirst; }

	void DeleteLast() {
		if (pFirst == nullptr) 
			throw "List is empty";

		if (pFirst->pNext == nullptr) {				// Если в списке только один элемент,
			delete pFirst;							// освобождаем память,
			pFirst = nullptr;						// и устанавливаем указатель на первый элемент в nullptr.
			return;
		}

		TNode<T>* tmp = pFirst;						// Указатель на первый элемент списка.
		while (tmp->pNext->pNext != nullptr) {		// Проходим до предпоследнего элемента списка.
			tmp = tmp->pNext;
		}

		delete tmp->pNext;
		tmp->pNext = nullptr;
	}
	void DeleteFirst() {
		if (pFirst == nullptr)
			throw "List is empty";

		if (pFirst->pNext == nullptr) {				// Если в списке только один элемент указатель
			delete pFirst;							// освобождаем память,
			pFirst = nullptr;						// и устанавливаем указатель на первый элемент в nullptr.
			return;
		}


		TNode<T>* tmp = pFirst->pNext;				// Сохраняем указатель на второй элемент списка.
		delete pFirst;								// Освобождаем память первого элемента списка.
		this->pFirst = tmp;							// Устанавливаем второй элемент как первый элемент списка.
	}

};