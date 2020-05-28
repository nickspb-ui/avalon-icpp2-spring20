#include <iostream>
#include <fstream>
#include <windows.h>

using namespace std;

struct Book {
	static const int BUFFER_SIZE = 20;
	int Id;
	char Title[BUFFER_SIZE];
	char Author[BUFFER_SIZE];
	float Price;
	int Quantity;
};

const string BOOKS_FILE_NAME = "books.bin";

int main()
{
	/*books - для записи в файл, bookr - для чтения из него*/
	setlocale(LC_ALL, "Rus");
	Book tmpp; //для обмена между ячейками основного массива
	ofstream books;
	Book tmp;
	char x{};
	char menu_action, edit_action; //вариации действий при выборе
	bool end_edit; //флаг, что редактирование окончательно
	bool sort_flag; //флаг об окончании сортировки
	bool id_correct; //флаг об оригинальности введённого ID
	books.open("books.bin", ios::binary | ios::ate | ios::in);
	if (!books.is_open()) {
		cerr << BOOKS_FILE_NAME << " не найден.";
		return 2;
	}
	int size_bin; //размер бинарного файла в байтах
	int tmp_id; //пользовательский айди при редактировании
	int curr_id;
	books.seekp(0, ios::end);
	size_bin = books.tellp();
	books.close();
	Book* book_list = new Book[size_bin / sizeof(Book)];
	ifstream bookr;
	bookr.open("books.bin", ios::binary);
	bookr.read(reinterpret_cast<char*>(book_list), size_bin);
	bookr.close();
	int* ids = new int[size_bin / sizeof(Book)]; //массив для хранения всех айди книг
	for (int i = 0; i < size_bin / sizeof(Book); i++) {
		ids[i] = book_list[i].Id;
	}
	while (1) {
		system("cls");
		cout << "----------------Главное меню----------------" << endl << "Введите цифру для выполнения действия (1 - добавление книги, 2 - редактирование книги, 3 - поиск книги, 4 - сортированный список книг, 5 - статистика библиотеки, 6 - выход из программы): ";
		cin >> menu_action;
		switch (menu_action) {
		case '1': {
			system("cls");
			delete[] book_list;
			cout << "----------------Добавление книги----------------" << endl;
			cout << "Введите название книги: ";
			cin >> tmp.Title;
			cout << "Введите автора книги: ";
			cin >> tmp.Author;
			cout << "Введите цену книги: ";
			cin >> tmp.Price;
			cout << "Введите ID книги: ";
			cin >> tmp.Id;
			id_correct = 0;
			while (id_correct == 0) {
				id_correct = 1;
				for (int i = 0; i < size_bin / sizeof(Book); i++) {
					if (tmp.Id == ids[i]) {
						cout << "Книга с таким ID уже существует. Повторите попытку." << endl;
						cin >> tmp.Id;
						id_correct = 0;
						break;
					}
				}
			}
			cout << "Введите количество книг в библиотеке: ";
			cin >> tmp.Quantity;
			books.open("books.bin", ios::binary | ios::ate | ios::in);
			books.seekp(0, ios::end);
			books.write(reinterpret_cast<char*>(&tmp), sizeof(Book));
			books.seekp(0, ios::end);
			size_bin = books.tellp();
			books.seekp(0);
			books.close();
			book_list = new Book[size_bin / sizeof(Book)];
			bookr.open("books.bin", ios::binary);
			if (!bookr.is_open()) {
				cerr << BOOKS_FILE_NAME << " не найден.";
				return 2;
			}
			bookr.read(reinterpret_cast<char*>(book_list), size_bin);
			bookr.close();
			delete[] ids;
			ids = new int[size_bin / sizeof(Book)];
			for (int i = 0; i < size_bin / sizeof(Book); i++) {
				ids[i] = book_list[i].Id;
			}
			break;
		}
		case '2': {
			system("cls");
			cout << "----------------Редактирование книги----------------" << endl;
			cout << "Введите ID редактируемой книги: ";
			cin >> tmp_id;
			end_edit = 0;
			curr_id = 0;
			for (int i = 0; i < size_bin / sizeof(Book); i++) {
				if (book_list[i].Id == tmp_id) {
					curr_id = i;
					while (end_edit == 0) {
						cout << "Данные, которые Вы хотите изменить (1 - название, 2 - автор, 3 - количество, 4 - цена, 5 - закончить редактирование): ";
						cin >> edit_action;
						switch (edit_action) {
						case '1': {
							cout << "Введите новое название: ";
							cin >> book_list[i].Title;
							break;
						}
						case '2': {
							cout << "Введите новую фамилию автора: ";
							cin >> book_list[i].Author;
							break;
						}
						case '3': {
							cout << "Введите новое количество: ";
							cin >> book_list[i].Quantity;
							break;
						}
						case '4': { cout << "Введите новую цену: ";
							cin >> book_list[i].Price;
							break;
						}
						case '5': { 
							end_edit = 1;
							break; 
						}
						default: { 
							cout << "Некорректная команда. Повторите попытку.";
							break;
						}
						}
						if (end_edit == 1) {
							break;
						}
						cout << "Данные успешно изменены." << endl;
						x = 0;
						system("pause");
						cin.get(x);
						books.open("books.bin", ios::binary | ios::ate | ios::in);
						books.seekp(0);
						books.write(reinterpret_cast<char*>(book_list), size_bin);
						books.close();
						}
					break;
				}
			}
			if (curr_id == 0) {
				cout << "Книга с таким ID не найдена. Повторите попытку позже.";
				Sleep(3000);
				break;
			}
			break;
		}
		case '3': {
			system("cls");
			cout << "----------------Поиск книги----------------" << endl << "Введите ID искомой книги: ";
			int id_search;
			cin >> id_search;
			bool u = 0;
			int l = 0, r = size_bin / sizeof(Book);
			int mid;
			do {
				sort_flag = 0;
				for (int i = 0; i < size_bin / sizeof(Book) - 1; i++) {
						if (book_list[i].Id == book_list[i + 1].Id) {
							continue;
						}
						if (book_list[i].Id > book_list[i + 1].Id) {
							tmpp = book_list[i];
							book_list[i] = book_list[i + 1];
							book_list[i + 1] = tmpp;
							sort_flag = 1;
						}
						break;
				}
			} while (sort_flag == 1);
			int found_id;
			while ((l <= r) && (u == 0)) {
				mid = (l + r) / 2;
				if (book_list[mid].Id == id_search) {
					u = 1;
					found_id = mid;
				}
				if (book_list[mid].Id > id_search) {
					r = mid - 1;
				}
				else {
					l = mid + 1;
				}
			}
			if (u == 1) {
				cout << "Найдена книга с заданным ID. " << "Автор: " << book_list[mid].Author << ", название: " << book_list[mid].Title << ", цена: " << book_list[mid].Price << ", количество: " << book_list[mid].Quantity << endl;
			}
			else {
				cout << "Книга с заданным ID не найдена. Повторите попытку позже." << endl;
			}
			Sleep(2000);
			x = 0;
			system("pause");
			cin.get(x);
			break; 
		}

		case '4': {
			system("cls");
			cout << "----------------Сортированный список книг----------------" << endl;						
			do {
				sort_flag = 0;
				for (int i = 0; i < size_bin / sizeof(Book) - 1; i++) {
					for (int j = 0; j < book_list[0].BUFFER_SIZE; j++) {
						if (book_list[i].Author[j] == book_list[i + 1].Author[j]) {
							continue;
						}
						if (book_list[i].Author[j] > book_list[i + 1].Author[j]) {
							tmpp = book_list[i];
							book_list[i] = book_list[i + 1];
							book_list[i + 1] = tmpp;
							sort_flag = 1;
						}
						break;
					}
				}
			} while (sort_flag == 1);
			for (int i = 0; i < size_bin / sizeof(Book); i++) {
				cout << "Автор: " << book_list[i].Author << ", название: " << book_list[i].Title << ", ID: " << book_list[i].Id << ", цена: " << book_list[i].Price << ", количество: " << book_list[i].Quantity << endl;
			}
			Sleep(5000);
			x = 0;
			system("pause");
			cin.get(x);
			break;
		}
		case '5': {
			system("cls");
			cout << "----------------Статистика библиотеки----------------" << endl << "Всего книг в библиотеке: ";
			int summ{}, cost{};
			for (int i = 0; i < size_bin / sizeof(Book); i++) {
				summ += book_list[i].Quantity;
				cost += book_list[i].Quantity * book_list[i].Price;
			}
			cout << summ << '.' << endl << "Общая стоимость всех книг: " << cost << '.' << endl;
			Sleep(3000);
			x = 0;
			system("pause");
			cin.get(x);
			break;
		}

		case '6': { return 0; }
		default: {
			cout << "Введена некорректная команда. Повторите попытку.";
			Sleep(1000);
			break;
		}
		}
	}		
	}
