#include "postfix_form.h"
#include <map>


//#define USE_ARRAY

#ifndef USE_ARRAY

string getPost(const string& simpleForm) {

	TStackList<char> a1;											//объ€вление элемента стека
	TStackList<char> a2;
	char stakItem;													//переменна€ дл€ запоминани€ элементов
	for (int i = 0; i < strlen(simpleForm.c_str()); i++) {			//по каждому символу строки
		if (simpleForm[i] == '+' || simpleForm[i] == '-') {			//если эл-т + или -, то вызываем трай/кетч
			try {
				if (a2.Top() == '/' || a2.Top() == '*') {			//если верхний эл-т в стеке а2 делить ли умножить
					while (a2.Top() == '/' || a2.Top() == '*') {	//пока верхний эл-т в стеке а2 делить ли умножить
						a1.push(a2.Top());							//наверх стека а1 закидывает эл-т из верха а2
						a2.pop();									//удал€ет сверху поэлементно
					}
					a2.push(simpleForm[i]);							//добавл€ем наверх стека а2 читаемую букву
				}

				else {
					a2.push(simpleForm[i]);							//иначе добавл€ем наверх стека а2 читаемую букву
				}
			}
			catch (const char* error) {	
				a2.push(simpleForm[i]);

			}
		}
		else if (simpleForm[i] == '*' || simpleForm[i] == '/') {
			a2.push(simpleForm[i]);									//закидывает читаемый эл-к в верх стека а2

		}
		else if (simpleForm[i] == '(') a2.push(simpleForm[i]);		//если эл-т (, то закидывает читаемый эл-к в верх стека а2
		else if (simpleForm[i] == ')') {							//если эл-т ), то 
			stakItem = a2.Top();									//временной переменной присваиваем верхний эл-т а2
			a2.pop();												//удал€ем его
			while (a2.Top() != '(') {								//пока верхний эл-т стека а2 не (, то
				a1.push(stakItem);									//закидываем в верх стека а1 переменную, которую ранее запомнили

				stakItem = a2.Top();								//временной переменной присваиваем следующий верхний эл-т а2
				a2.pop();											//избавл€емс€ от него
			}
			a1.push(stakItem);										//добавл€ем в верх а1 запомнивший ранее эл-т
			a2.pop();												//удал€ем верхний эл-т из а2
		}
		else {
			a1.push(simpleForm[i]);									//закидываем искомый эл-т в верх а1
		}
	}
	while (!a2.isEmpty()) {											//пока стек а2 непустой
		a1.push(a2.Top());											//добавл€€ем в стек а1 верхний эл-т стека а2
		a2.pop();													//удал€ем его
	}
	string newForm = "";											//объ€вление пустой строки 
	while (!a1.isEmpty()) {											
		newForm = a1.Top() + newForm;								//добавл€ем в начало строки эл-т а1
		a1.pop();													//удал€ем за ненадобнастью
	}
	return newForm;													//возвращаем ее

}
vector<char> getOper(const string& simpleForm) {
	vector<char> v;													//создаем вектор, чтобы записывать операнды
	for (int i = 0; i < strlen(simpleForm.c_str()); i++) {			//c_str приводит строку к формату си
		if (simpleForm[i] != '+' && simpleForm[i] != '*' && simpleForm[i] != '/' && simpleForm[i] != '-') {	
			int j = 0;												
			bool f = false;											//флаг отслеживани€
			for (int j = 0; j < v.size(); j++) {					//проверка, что j меньше размера вектора
				if (v[j] == simpleForm[i]) {						//если вектор индекса j равен отслеживаемому эл-ту
					f = true;										//флаг в тру
					break;											//выход из цикла
				}
			}
			if (f == false) {										//если не нашли в векторе этот эл-т
				v.push_back(simpleForm[i]);							//добавл€ем его в вектор
			}
		}
		///
	}
	return v;														//возвращаем вектор

}
int Calc(const string& postForm, map<char, int>& values) {

	TStackList<char> a1;

	for (int i = 0; i < strlen(postForm.c_str()); i++) {
		if (postForm[i] == '+') {
			char num2 = a1.Top();
			a1.pop();
			char num1 = a1.Top();
			a1.pop();
			int k = (values[num1] + values[num2]);
			a1.push(k);
			values.insert({ k, k });
		}
		else if (postForm[i] == '*') {
			char num2 = a1.Top();
			a1.pop();
			char num1 = a1.Top();
			a1.pop();
			int k = (values[num1] * values[num2]);
			a1.push(k);
			values.insert({ k, k });
		}
		else if (postForm[i] == '/') {
			char num2 = a1.Top();
			a1.pop();
			char num1 = a1.Top();
			a1.pop();
			int k = (values[num1] / values[num2]);
			a1.push(k);
			values.insert({ k, k });
		}
		else if (postForm[i] == '-') {
			char num2 = a1.Top();
			a1.pop();
			char num1 = a1.Top();
			a1.pop();
			int k = (values[num1] - values[num2]);
			a1.push(k);
			values.insert({ k, k });
		}
		else {
			a1.push(postForm[i]);
		}
	}
	return (int)a1.Top();
}



#else
string getPost(const string& simpleForm, int n) {

	TStackArray<char> a1(n);
	TStackArray<char> a2(n);
	char stakItem;
	for (int i = 0; i < strlen(simpleForm.c_str()); i++) {
		if (simpleForm[i] == '+' || simpleForm[i] == '-') {
			try {
				if (a2.Top() == '/' || a2.Top() == '*') {
					while (a2.Top() == '/' || a2.Top() == '*') {
						a1.push(a2.Top());
						a2.pop();
					}
					a2.push(simpleForm[i]);
				}

				else {
					a2.push(simpleForm[i]);
				}
			}
			catch (const char* error) {
				a2.push(simpleForm[i]);

			}
		}
		else if (simpleForm[i] == '*' || simpleForm[i] == '/') {
			a2.push(simpleForm[i]);

		}
		else if (simpleForm[i] == '(') a2.push(simpleForm[i]);
		else if (simpleForm[i] == ')') {
			stakItem = a2.Top();
			a2.pop();
			while (a2.Top() != '(') {
				a1.push(stakItem);

				stakItem = a2.Top();
				a2.pop();
			}
			a1.push(stakItem);
			a2.pop();
		}
		else {
			a1.push(simpleForm[i]);
		}
	}
	while (!a2.isEmpty()) {
		a1.push(s2.Top());
		a2.pop();
	}
	string newForm = "";
	while (!a1.isEmpty()) {
		newForm = a1.Top() + newForm;
		a1.pop();
	}
	return newForm;

}
vector<char> getOper(const string& simpleForm) {
	vector<char> v;
	for (int i = 0; i < strlen(simpleForm.c_str()); i++) {
		if (simpleForm[i] != '+' && simpleForm[i] != '*' && simpleForm[i] != '/' && simpleForm[i] != '-') {
			int j = 0;
			bool f = false;
			for (int j = 0; j < v.size(); j++) {
				if (v[j] == simpleForm[i]) {
					f = true;
					break;
				}
			}
			if (f == false) {
				v.push_back(simpleForm[i]);
			}
		}

	}
	return v;

}
int Calc(const string& postForm, int n, map<char, int>& values) {

	TStackArray<char> a1(n);

	for (int i = 0; i < n; i++) {
		if (postForm[i] == '+') {
			char num2 = a1.Top();
			a1.pop();
			char num1 = a1.Top();
			a1.pop();
			int k = (values[num1] + values[num2]);
			a1.push(k);
			values.insert({ k, k });
		}
		else if (postForm[i] == '*') {
			char num2 = a1.Top();
			a1.pop();
			char num1 = s1.Top();
			a1.pop();
			int k = (values[num1] * values[num2]);
			a1.push(k);
			values.insert({ k, k });
		}
		else if (postForm[i] == '/') {
			char num2 = a1.Top();
			a1.pop();
			char num1 = a1.Top();
			a1.pop();
			int k = (values[num1] / values[num2]);
			a1.push(k);
			values.insert({ k, k });
		}
		else if (postForm[i] == '-') {
			char num2 = a1.Top();
			a1.pop();
			char num1 = a1.Top();
			a1.pop();
			int k = (values[num1] - values[num2]);
			a1.push(k);
			values.insert({ k, k });
		}
		else {
			a1.push(postForm[i]);
		}
	}
	return (int)a1.Top();
}




#endif // !USE_LIST