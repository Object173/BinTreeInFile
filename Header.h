#ifndef _HEADER_H
#define _HEADER_H

#include<stdlib.h>
#include<iostream>
#include<cstdlib>
#include<time.h>
#include <fstream>

using namespace std;

class MyClass
{
	int size;
	int *mas;

public:
	MyClass() { size = 0; mas = NULL; };
	MyClass(int);//конструктор
	//~MyClass();//деструктор
	int GetEl(int n);//значение элемента
	void PrintMas();//вывести массив
	void PrintEl(int);//вывести элемент
	void Add(int, int);//добавить элемент
	void Del(int);//удалить элемент
	void Set(int, int);//изменить элемент
	void Sort(int);//сортировка элементов
	int GetSize();//размер массива
	void Resize(int);//изменить размер массива
	void Sum(MyClass &obj);//сумма объектов
	friend void Raz(MyClass *obj1, MyClass *obj2);//разность объектов

	//оператор присвоения
	MyClass& operator=(MyClass &obj);

	//оператор сложения
	MyClass operator+(MyClass &obj);
	void operator+=(MyClass &obj);
	void operator ++();

	//операторы сравнения
	bool operator>(MyClass &obj);
	bool operator<(MyClass &obj);
	bool operator==(MyClass &obj);
	bool operator!=(MyClass &obj);

	//оператор разности
	friend MyClass operator-(MyClass &obj1, MyClass &obj2);
	void operator-=(MyClass &obj);
	void operator--();

	//операторы вывода
	friend ostream& operator<< (ostream& os, MyClass &obj);
	friend ostream& operator<< (ostream& os, MyClass *obj);
	friend fstream& operator<< (fstream& os, MyClass &obj);

	//операторы ввода
	friend istream& operator>> (istream& is, MyClass &obj);
	friend fstream& operator>> (fstream& is, MyClass &obj);
};

class Fail 
{
public:
	Fail(void) {};
};

#endif