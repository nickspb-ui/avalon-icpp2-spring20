#include <iostream>
#include <stdio.h>
#include <limits>

using namespace std;

int main() {
	setlocale(LC_ALL, "Rus");
	printf("Тип переменной%11c%11s%5c%23s%14c%12s\n", '|', "Размер,", '|', "Значение", '|', "Количество");
	printf("%25c%9s%7c%15s%5c%14s%3c%13s\n", '|', "байт", '|', "Минимальное", '|', "Максимальное", '|', "значимых бит");
	printf("----------------------------------------------------------------------------------------------\n");
	printf("bool%21c%15d%c%19d%c%16d%c%15d%c\n", '|', sizeof(bool), '|', numeric_limits<bool>::min(), '|', numeric_limits<bool>::max(), '|', numeric_limits<bool>::digits, '|');
	printf("unsigned short%11c%15d%c%19d%c%16d%c%15d%c\n", '|', sizeof(unsigned short), '|', numeric_limits<unsigned short>::min(), '|', numeric_limits<unsigned short>::max(), '|', numeric_limits<unsigned short>::digits, '|');
	printf("short%20c%15d%c%19d%c%16d%c%15d%c\n", '|', sizeof(short), '|', numeric_limits<short>::min(), '|', numeric_limits<short>::max(), '|', numeric_limits<short>::digits, '|');
	printf("unsigned int%13c%15d%c%19d%c%16u%c%15d%c\n", '|', sizeof(unsigned int), '|', numeric_limits<unsigned int>::min(), '|', numeric_limits<unsigned int>::max(), '|', numeric_limits<unsigned int>::digits, '|');
	printf("int%22c%15d%c%19d%c%16u%c%15d%c\n", '|', sizeof(int), '|', numeric_limits<int>::min(), '|', numeric_limits<int>::max(), '|', numeric_limits<int>::digits, '|');
	printf("unsigned long%12c%15d%c%19d%c%16u%c%15d%c\n", '|', sizeof(unsigned long), '|', numeric_limits<unsigned long>::min(), '|', numeric_limits<unsigned long>::max(), '|', numeric_limits<unsigned long>::digits, '|');
	printf("long%21c%15d%c%19d%c%16u%c%15d%c\n", '|', sizeof(long), '|', numeric_limits<long>::min(), '|', numeric_limits<long>::max(), '|', numeric_limits<long>::digits, '|');
	printf("unsigned long long%7c%15d%c%19lld%c%16e%c%15d%c\n", '|', sizeof(unsigned long long), '|', numeric_limits<unsigned long long>::min(), '|', static_cast<double>(numeric_limits<unsigned long long>::max()), '|', numeric_limits<unsigned long long>::digits, '|');
	printf("long long%16c%15d%c%19e%c%16e%c%15d%c\n", '|', sizeof(long long), '|', static_cast<double>(numeric_limits<long long>::min()), '|', static_cast<double>(numeric_limits<long long>::max()), '|', numeric_limits<long long>::digits, '|');
	printf("char%21c%15d%c%19d%c%16d%c%15d%c\n", '|', sizeof(char), '|', numeric_limits<char>::min(), '|', numeric_limits<char>::max(), '|', numeric_limits<char>::digits, '|');
	printf("float%20c%15d%c%19e%c%16e%c%15d%c\n", '|', sizeof(float), '|', numeric_limits<float>::min(), '|', numeric_limits<float>::max(), '|', numeric_limits<float>::digits, '|');
	printf("double%19c%15d%c%19e%c%16e%c%15d%c\n", '|', sizeof(double), '|', numeric_limits<double>::min(), '|', numeric_limits<double>::max(), '|', numeric_limits<double>::digits, '|');
}
