
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
Реализуйте шаблонную функцию Swap, которая принимает два указателя и обменивает местами значения,
на которые указывают эти указатели (нужно обменивать именно сами указатели,
переменные должны оставаться в тех же адресах памяти).
*/
template <typename T>
void Swap(T& ptr1, T& ptr2) noexcept
{
	assert(ptr1 != ptr2);

	T temp(move(ptr1));
	ptr1 = move(ptr2);
	ptr2 = move(temp);
}
class Item
{
private:
	int value = 0;
public:
	Item(int input)
		: value(input)
	{

	}

	void printValue();

};

void Item::printValue()
{
	cout << value << endl;
}


/*Task 2
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
void countVowels1()
{
	setlocale(LC_ALL, "rus");
	auto start = chrono::high_resolution_clock::now();

	ifstream file("voina-i-mir.txt");
	if (!file.is_open())
	{
		cout << "Не удалось прочитать файл!" << endl;
		return;
	}

    string vowels = "AEIOUYaeiouy";

	size_t count = count_if(std::istreambuf_iterator<char>(file), istreambuf_iterator<char>(), [=](char x) {return vowels.find(x) != string::npos; });
	file.close();

	auto finish = chrono::high_resolution_clock::now();
	auto result = chrono::duration_cast<chrono::milliseconds>(finish - start);
	cout << "(Count_if + find) took " << result.count() << " миллисекунд.\n";
	cout << "Количество гласных: " << count << endl;
}


void countVowels2()
{
	auto start = chrono::high_resolution_clock::now();

	ifstream file("voina-i-mir.txt");
	if (!file.is_open())
	{
		cout << "Не удалось прочитать файл!" << endl;
		return;
	}

	string vowels = "AEIOUYaeiouy";

	size_t count = count_if(std::istreambuf_iterator<char>(file), istreambuf_iterator<char>(), [=](char x) -> bool {for (auto chr : vowels) { if (chr == x) return true; } return false; });
	file.close();

	auto finish = chrono::high_resolution_clock::now();
	auto result = chrono::duration_cast<chrono::milliseconds>(finish - start);
	cout << "(Count_if + for) took " << result.count() << " миллисекунд.\n";
	cout << "Количество гласных: " << count << endl;
}

void countVowels3()
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
		if (vowels.find(*it) != string::npos) ++count;
	}

	file.close();

	auto finish = chrono::high_resolution_clock::now();
	auto result = chrono::duration_cast<chrono::milliseconds>(finish - start);
	cout << "(For + find) took " << result.count() << " миллисекунд.\n";
	cout << "Количество гласных: " << count << endl;
}

void countVowels4()
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
	cout << "(For + for) took " << result.count() << " миллисекунд.\n";
	cout << "Количество гласных: " << count << endl;
}


int main()
{
	setlocale(LC_ALL, "rus");
	{
		cout << "Задание 1" << endl;
		unique_ptr<Item> ptr1(new Item(7));
		unique_ptr<Item> ptr2(new Item(777));
		ptr1->printValue();
		ptr2->printValue();
		swap(ptr1, ptr2);
		ptr1->printValue();
		ptr2->printValue();
		
	}

	{
		cout << "\nЗадание 2" << endl;
		cout << "Начальный вектор:" << endl;
		vector<int*> ptrVector;
		RandomFillVector(ptrVector, 10);
		PrintVector(ptrVector);
		cout << "\nОтсортированный вектор:" << endl;
		SortPointers(ptrVector);
		PrintVector(ptrVector);
		
	}

	{
		cout << "\nЗадание 3" << endl;
		//Task 3
		//count_if + find
		countVowels1();
		//count_if + for
		countVowels2();
		//for+find
		countVowels3();
		//for+for
		countVowels4();
		
	}
}