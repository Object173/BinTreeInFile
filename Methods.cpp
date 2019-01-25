#include "Header.h"

MyClass::MyClass(int s)
{
	size = s;
	mas = new int[size];
	for (int i = 0; i < size; i++)
		mas[i] = i;
}

/*MyClass::~MyClass()
{
	delete[] mas;
}*/

int MyClass::GetEl(int n)
{
	if (n >= size) return INT_MIN;
	else return mas[n];
}

void MyClass::PrintEl(int n)
{
	if (mas[n]!=INT_MIN) cout << mas[n] << endl;
	else cout << "NULL" << endl;
}

void MyClass::PrintMas()
{
	for (int i = 0; mas[i] != INT_MIN && i < size; i++)
		PrintEl(i);

	cout << endl;
}

void MyClass::Add(int x, int n)
{
	int i;
	for (i = 0; mas[i] != INT_MIN && i<n && i<size; i++);
	if (i == size)
	{
		Resize(size + 1);
		Add(x, n);
		return;
	}

	if (mas[i] == INT_MIN) mas[i] = x;
	else
	{
		for (; mas[i] != INT_MIN && i<size; i++);
			if (i == size)
			{
				Resize(size + 1);
				Add(x, n);
				return;
			}

		for (i = size - 1; i>n; i--)
			mas[i] = mas[i - 1];
		mas[n] = x;
	}
}

void MyClass::Del(int n)
{
	if (n>size) return;

	mas[n] = INT_MIN;
	for (int i = n; i < size - 1; i++)
		mas[i] = mas[i + 1];
	mas[size - 1] = INT_MIN;
}

void MyClass::Set(int n, int x)
{
	if (mas[n] == INT_MIN || n >= size) return;
	mas[n] = x;
}

void MyClass::Sort(int f)
{
	if (mas[0] == INT_MIN || f>2 || f<1) return;

	if (f == 1)	//по возрастанию
	{
		int min;
		for (int i = 0; mas[i] != INT_MIN && i < size; i++)
		{
			min = i;
			for (int j = i; mas[j] != INT_MIN && j < size; j++)
				if (mas[j] < mas[min]) min = j;
			int x = mas[i];
			mas[i] = mas[min];
			mas[min] = x;
		}
		return;
	}

	if (f == 2)	//по убыванию
	{
		int max;
		for (int i = 0; mas[i] != INT_MIN && i < size; i++)
		{
			max = i;
			for (int j = i; mas[j] != INT_MIN && j < size; j++)
			if (mas[j] > mas[max]) max = j;
			int x = mas[i];
			mas[i] = mas[max];
			mas[max] = x;
		}
		return;
	}
}

void MyClass::Resize(int ns)
{
	int *m = new int[ns];

	for (int i = 0; i < ns; i++)
		if (i < size) m[i] = mas[i];
		else m[i] = INT_MIN;

	size = ns;
	delete[] mas;
	mas = m;
}

int MyClass::GetSize()
{
	return size;
}

void MyClass::Sum(MyClass &obj)
{
	for (int i = 0; obj.GetEl(i) != INT_MIN; i++)
	{
		bool f=true;
		for (int j = 0; mas[j] != INT_MIN && f && j<size;j++)
			if (obj.mas[i] == mas[j]) f = false;
			if (f) Add(obj.mas[i], INT_MAX);
	}
}

void Raz(MyClass *obj1, MyClass *obj2)
{
	for (int i = 0; obj1->GetEl(i) != INT_MIN; i++)
	{
		bool f = true;
		for (int j = 0; obj2->GetEl(j) != INT_MIN && f; j++)
			if (obj1->GetEl(i) == obj2->GetEl(j)) f = false;
		if (!f)
		{
			obj1->Del(i);
			i--;
		}
	}
}

MyClass& MyClass::operator=(MyClass &obj)
{ 
	Resize(0);

	for (int i = 0; i < obj.GetSize(); i++)
		Add(obj.GetEl(i), i);

	return *this;
}

bool MyClass::operator>(MyClass &obj)
{
	return size>obj.size;
}

bool MyClass::operator<(MyClass &obj)
{
	return size<obj.size;
}

bool MyClass::operator==(MyClass &obj)
{
	return size==obj.size;
}

bool MyClass::operator!=(MyClass &obj)
{
	return size!=obj.size;
}

MyClass MyClass::operator+(MyClass &obj)
{
	MyClass *obj3=new MyClass(size);
	for (int i = 0; i < size; i++)
		obj3->Add(mas[i], i);
	obj3->Sum(obj);
	
	return *obj3;
}

void MyClass::operator+=(MyClass &obj)
{
	Sum(obj);
}

void MyClass::operator ++()
{
	Resize(size++);
}

void MyClass::operator-=(MyClass &obj)
{
	MyClass *obj1 = &obj;
	Raz(this, obj1);
}

void MyClass::operator--()
{
	Resize(size - 1);
}

MyClass operator-(MyClass &obj1, MyClass &obj2)
{
	MyClass *obj3=new MyClass(0);
	*obj3 = obj1;
	Raz(obj3, &obj2);
	return *obj3;
}

ostream& operator<< (ostream& os, MyClass &obj)
{
	os << "Размер массива = " << obj.GetSize()<<endl;
	for (int i = 0; i < obj.GetSize(); i++)
		if (obj.GetEl(i)!=INT_MIN) os << obj.GetEl(i) << " ";
	os << endl;
	return os;
}

ostream& operator<< (ostream& os, MyClass *obj)
{
	os << "Размер массива = " << obj->GetSize()<<endl;
	for (int i = 0; i < obj->GetSize(); i++)
		if (obj->GetEl(i)!=INT_MIN) os << obj->GetEl(i) << " ";
	os << endl;
	return os;
}

fstream& operator<< (fstream& os, MyClass &obj)
{
	int i=0;
	for (i = 0; obj.GetEl(i) != INT_MIN && i < obj.GetSize(); i++);
	os.write((char*)&i,sizeof(int));
	//os << i << endl;
	int x;
	for (int i = 0; i < obj.GetSize(); i++)
	{
		//os << obj.GetEl(i) << " ";
		x=obj.GetEl(i);
		os.write((char*)&x,sizeof(int));
	}
	return os;
}

istream& operator>> (istream& is, MyClass &obj)
{
	int size, x;
	is >> size;
	obj.Resize(0);
	obj.Resize(size);
	for (int i = 0; i < size; i++)
	{
		is >> x;
		obj.Add(x, i);
	}
	return is;
}

fstream& operator>> (fstream& is, MyClass &obj)
{
	//if (!is) throw Fail();

	int size, x;
	//is >> size;
	is.read((char*)&size,sizeof(int));
	obj.Resize(0);
	obj.Resize(size);
	for (int i = 0; i < size; i++)
	{
		//is >> x;
		is.read((char*)&x,sizeof(int));
		obj.Add(x, i);
	}
	return is;
}
