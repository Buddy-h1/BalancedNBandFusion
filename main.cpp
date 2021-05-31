#include <iostream>
#include <vector>
#include <iomanip>
#include <locale>

using namespace std;

struct numbers {
	int a;
	char b;
};

//Поиск максимума
int max(const vector<numbers>& arr) {
	int id_max = 0;
	for (int j = 0; j < arr.size() - 1; ++j) {
		while (arr[id_max].a == -1) {
			id_max++;
		}
		if (arr[id_max].a == arr[j + 1].a && arr[j + 1].a != -1) {
			if (arr[id_max].b > arr[j + 1].b) {
				id_max = j + 1;
			}
		}
		if (arr[id_max].a > arr[j + 1].a && arr[j + 1].a != -1) {
			id_max = j + 1;
		}
	}
	return id_max;
}

//Сортировка методом обмена
void Sorting(vector<numbers>& arr) {
	for (int i = 0; i < arr.size(); ++i) {
		int a = 0;
		for (int j = 0; j < arr.size() - i - 1; ++j) {
			if (arr[j].a == arr[j + 1].a) {
				if (arr[j].b > arr[j + 1].b) {
					struct numbers temp = arr[j];
					arr[j] = arr[j + 1];
					arr[j + 1] = temp;
					a = 1;
				}
			}
			else if (arr[j].a > arr[j + 1].a) {
				struct numbers temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
				a = 1;
			}
		}
		if (a == 0) { break; }
	}
}

int main() {
	setlocale(LC_CTYPE, "Russian");
	// Создание и вывод начальных данных
	char char_array[] =
	{ 'A','B','C','D','E','F',
		'G','H','I','J','K',
		'L','M','N','O','P',
		'Q','R','S','T','U',
		'V','W','X','Y','Z',
		'a','b','c','d','e',
		'f','g','h','i','j',
		'k','l','m','n','o',
		'p','q','r','s','t',
		'u','v','w','x','y','z' };
	vector<numbers> all(50);
	for (int i = 0; i < all.size(); ++i) {
		all[i].a = rand() % 40 + 10;
		int index_random_char = rand() % 51;
		char random_char = char_array[index_random_char];
		all[i].b = random_char;
	}
	cout << "Неупорядоченный массив данных" << endl;
	for (const auto& i : all) {
		cout << i.a << '>' << i.b << " ";
	}
	cout << endl << endl;

	// Распределение данных на цепочки и их сортировка и вывод
	int line = sqrt(all.size());
	double columns_temp = ceil((double)all.size() / (double)line);
	const int columns = columns_temp;
	vector<vector<numbers>> data(line);
	int k = 0;
	for (auto& i : data) {
		for (int j = 0; j < columns; ++j) {
			if (k != all.size()) {
				i.push_back(all[k]);
				++k;
			}
			else {
				break;
			}
		}
	}
	for (auto& i : data) {
		Sorting(i);
	}
	cout << "Неупорядоченный массив, разбитый на sqrt(n) цепочек" << endl;
	for (const auto& i : data) {
		for (const auto& j : i) {
			cout << setw(5) << j.a << '>' << j.b;
		}
		cout << endl;
	}

	// n-ленточное сбалансированное слияние
	vector<int> counter(line, 0);
	cout << endl;
	for (int i = 0; i < all.size(); ++i) {
		vector<numbers> temp;
		int id_max = 0;
		for (int k = 0; k < data.size(); ++k) {
			if (counter[k] < data[k].size()) {
				temp.push_back(data[k][counter[k]]);
			}
			else {
				temp.push_back({ -1, 'a' });
			}
		}
		id_max = max(temp);
		all[i] = data[id_max][counter[id_max]];
		counter[id_max]++;
	}

	cout << "Упорядоченный массив данных" << endl;
	for (const auto& i : all) {
		cout << i.a << '>' << i.b << " ";
	}
	cout << endl;
	return 0;
}