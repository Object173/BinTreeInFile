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
	MyClass(int);//�����������
	//~MyClass();//����������
	int GetEl(int n);//�������� ��������
	void PrintMas();//������� ������
	void PrintEl(int);//������� �������
	void Add(int, int);//�������� �������
	void Del(int);//������� �������
	void Set(int, int);//�������� �������
	void Sort(int);//���������� ���������
	int GetSize();//������ �������
	void Resize(int);//�������� ������ �������
	void Sum(MyClass &obj);//����� ��������
	friend void Raz(MyClass *obj1, MyClass *obj2);//�������� ��������

	//�������� ����������
	MyClass& operator=(MyClass &obj);

	//�������� ��������
	MyClass operator+(MyClass &obj);
	void operator+=(MyClass &obj);
	void operator ++();

	//��������� ���������
	bool operator>(MyClass &obj);
	bool operator<(MyClass &obj);
	bool operator==(MyClass &obj);
	bool operator!=(MyClass &obj);

	//�������� ��������
	friend MyClass operator-(MyClass &obj1, MyClass &obj2);
	void operator-=(MyClass &obj);
	void operator--();

	//��������� ������
	friend ostream& operator<< (ostream& os, MyClass &obj);
	friend ostream& operator<< (ostream& os, MyClass *obj);
	friend fstream& operator<< (fstream& os, MyClass &obj);

	//��������� �����
	friend istream& operator>> (istream& is, MyClass &obj);
	friend fstream& operator>> (fstream& is, MyClass &obj);
};

class Fail 
{
public:
	Fail(void) {};
};

#endif