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
	ofstream books;
	char x{};
	char menu_action, edit_action; //вариации действий при выборе
	bool end_edit; //флаг, что редактирование окончательно
	bool sort_flag;
	books.open("books.bin", ios::binary | ios::ate | ios::in);
	if (!books.is_open()) {
		cerr << BOOKS_FILE_NAME << " не найден.";
		return 2;
	}
	int size_bin; //размер бинарного файла в байтах
	int tmp_id; //пользовательский айди при редактировании
	int curr_id; //
	books.seekp(0, ios::end);
	char tmp[20];
	size_bin = books.tellp();
	cout << size_bin << sizeof(Book);
	books.close();
	Book* book_list = new Book[size_bin / sizeof(Book)];
	ifstream bookr;
	bookr.open("books.bin", ios::binary);
	bookr.read(reinterpret_cast<char*>(book_list), size_bin);
	bookr.close();
	for (int i = 0; i < size_bin / sizeof(Book); i++) {
		cout << book_list[i].Author << ' ' << book_list[i].Title << ' ' << book_list[i].Id << ' ' << book_list[i].Price << ' ' << book_list[i].Quantity << endl;
	}
	Sleep(1000);
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
			Book tmp;
			cin >> tmp.Title;
			cout << "Введите автора книги: ";
			cin >> tmp.Author;
			cout << "Введите цену книги: ";
			cin >> tmp.Price;
			cout << "Введите ID книги: ";
			cin >> tmp.Id;
			cout << "Введите количество книг в библиотеке: ";
			cin >> tmp.Quantity;
			books.open("books.bin", ios::binary | ios::ate | ios::in);
			books.seekp(0, ios::end);
			books.write(reinterpret_cast<char*>(&tmp), sizeof(Book));
			size_bin += sizeof(Book);
			books.close();
			Book* book_list = new Book[size_bin / sizeof(Book)];
			bookr.open("books.bin", ios::binary);
			bookr.read(reinterpret_cast<char*>(book_list), size_bin);
			bookr.close();
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
							end_edit == 1;
							break; 
						}
						default: { 
							cout << "Некорректная команда. Повторите попытку.";
							break;
						}
						}
						break;
					}
				}
			}
			if (curr_id == 0) {
				cout << "Книга с таким ID не найдена. Повторите попытку позже.";
				Sleep(3000);
				break;
			}
			else {
				books.open("books.bin", ios::binary | ios::ate | ios::in);
				books.seekp(curr_id * sizeof(Book), ios::beg);
				books.write(reinterpret_cast<char*>(&book_list[curr_id]), sizeof(Book));
				books.close();
			}
			break;
		}
		/*case '3':
			system("cls");
			cout << "----------------Поиск книги----------------" << endl;
			break; */
		case '4': {
			system("cls");
			cout << "----------------Сортированный список книг----------------" << endl;
			Book tmpp; //для обмена между ячейками основного массива			
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
			break;
		}
		}
	}
		
	}
