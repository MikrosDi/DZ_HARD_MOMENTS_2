
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <chrono>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <iterator>

using namespace std;


/*Task 1
* 
Реализуйте шаблонную функцию Swap, которая принимает два указателя и обменивает местами значения,
на которые указывают эти указатели (нужно обменивать именно сами указатели,
переменные должны оставаться в тех же адресах памяти).
*/

    template <typename T>

	void Swap(T** one, T** two)
	{
		T* pSwap = *one;
		*one = *two;
		*two = pSwap;
	}



/*Task 2
* 
Реализуйте шаблонную функцию SortPointers, которая принимает вектор указателей
и сортирует указатели по значениям, на которые они указывают.
*/

template <typename T>
void SortPointers(vector<T*>& v)
{
	sort(v.begin(), v.end(), [](const T* a, const T* b) {return *a < *b; });
}

template <typename T>
void PrintVector(const vector<T*>& v)
{
	auto iter = v.begin();
	while (iter != v.end())
	{
		cout << **iter << " ";
		++iter;
	}
	cout << endl;
}

template <typename T>
void RandomFillVector(std::vector<T*>& v, int size)
{
	v.resize(size);
	auto iter = v.begin();
	while (iter != v.end())
	{
		*iter = new T;
		++iter;
	}
}

template <>
void RandomFillVector(std::vector<int*>& v, int size)
{
	srand(static_cast<uint16_t>(time(0)));
	v.resize(size);
	auto iter = v.begin();
	while (iter != v.end())
	{
		int* ptr = new int();
		*ptr = rand() % 100;
		*iter = ptr;
		++iter;
	}
}


/*Task 3
* 
Подсчитайте количество гласных букв в книге “Война и мир”. Для подсчета используйте 4 способа:
○      count_if и find
○      count_if и цикл for
○      цикл for и find
○      2 цикла for
Замерьте время каждого способа подсчета и сделайте выводы.
Справка:
count_if - это алгоритмическая функция из STL, которая принимает 3 параметра: итератор на начало, итератор на конец и унарный предикат (функцию, принимающую один параметр и возвращающую тип bool).
find - это метод класса string, который возвращает позицию символа (строки), переданного в качестве параметра, в исходной строке. Если символ не найден, то метод возвращает string::npos.
*/
void count_If_Find()
{
	setlocale(LC_ALL, "rus");
	auto start = chrono::high_resolution_clock::now();

	ifstream file("voina-i-mir.txt");
	if (!file.is_open())
	{
		cout << "Не удалось прочитать файл!" << endl;
		return;
	}

    string vowels = "AEIOUaeiou";

	size_t count = count_if(std::istreambuf_iterator<char>(file), istreambuf_iterator<char>(), [=](char x) {return vowels.find(x) != string::npos; });
	file.close();

	auto finish = chrono::high_resolution_clock::now();
	auto result = chrono::duration_cast<chrono::milliseconds>(finish - start);
	cout << "(Count_if + find) занял " << result.count() << " миллисекунд.\n";
	cout << "Количество гласных: " << count << endl;
}


void count_If_For()
{
	auto start = chrono::high_resolution_clock::now();

	ifstream file("voina-i-mir.txt");
	if (!file.is_open())
	{
		cout << "Не удалось прочитать файл!" << endl;
		return;
	}

	string vowels = "AEIOUaeiou";

	size_t count = count_if(std::istreambuf_iterator<char>(file), istreambuf_iterator<char>(), [=](char x) -> bool {for (auto chr : vowels) { if (chr == x) return true; } return false; });
	file.close();

	auto finish = chrono::high_resolution_clock::now();
	auto result = chrono::duration_cast<chrono::milliseconds>(finish - start);
	cout << "(Count_if + for) занял " << result.count() << " миллисекунд.\n";
	cout << "Количество гласных: " << count << endl;
}

void count_For_Find()
{
	auto start = chrono::high_resolution_clock::now();

	ifstream file("voina-i-mir.txt");
	if (!file.is_open())
	{
		cout << "Не удалось прочитать файл!" << endl;
		return;
	}

	string vowels = "AEIOUaeiou";
	size_t count = 0;

	for (auto it = istreambuf_iterator<char>(file); it != istreambuf_iterator<char>(); ++it)
	{
		if (vowels.find(*it) != string::npos) ++count;
	}

	file.close();

	auto finish = chrono::high_resolution_clock::now();
	auto result = chrono::duration_cast<chrono::milliseconds>(finish - start);
	cout << "(For + find) занял " << result.count() << " миллисекунд.\n";
	cout << "Количество гласных: " << count << endl;
}

void count_For_For()
{
	auto start = chrono::high_resolution_clock::now();

	ifstream file("voina-i-mir.txt");
	if (!file.is_open())
	{
		cout << "Не удалось прочитать файл!" << endl;
		return;
	}

	string vowels = "AEIOUYaeiouy";
	size_t count = 0;

	for (auto it = istreambuf_iterator<char>(file); it != istreambuf_iterator<char>(); ++it)
	{
		for (char chr : vowels)
		{
			if (*it == chr && *it != std::string::npos) ++count;
		}
	}

	file.close();

	auto finish = chrono::high_resolution_clock::now();
	auto result = chrono::duration_cast<chrono::milliseconds>(finish - start);
	cout << "(For + for) занял " << result.count() << " миллисекунд.\n";
	cout << "Считаем что Y глассная(так как иногда она ей может быть) Количество гласных: " << count << endl;
}


int main()
{
	setlocale(LC_ALL, "rus");
	{
		cout << "Задание 1" << endl;
		int first = 19;
	    int* one = &first;
		int second = 25;
	    int* two = &second;
		cout << " Значение " << first << " <-> Указатель на значение " << *one << endl;
		cout << " Значение " << second << " <-> Указатель на значение " << *two << endl;
		Swap(&one, &two);
		cout << " Сработала функция Swap! " << endl;
		cout << " Значение " << first << " <-> Указатель на значение " << *one << endl;
		cout << " Значение " << second << " <-> Указатель на значение " << *two << endl;
	}

	{
		cout << "\nЗадание 2" << endl;
		cout << "Начальный вектор:" << endl;
		vector<int*> ptrVector;
		RandomFillVector(ptrVector, 10);
		PrintVector(ptrVector);
		cout << "Отсортированный вектор:" << endl;
		SortPointers(ptrVector);
		PrintVector(ptrVector);
		
	}

	{
		cout << "\nЗадание 3" << endl;
		
		count_If_Find();
		
		count_If_For();
		
		count_For_Find();
		
		count_For_For();
		
	}
}