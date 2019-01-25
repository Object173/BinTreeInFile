#include<ctime>

#include "String.h"
#include "Header.h"
#include "Shablon.h"

using namespace std;

/*
class MyClass
{
public:
	int n;
	int *mas;

	MyClass(){n=0;mas=NULL;}
	MyClass(int x) 
	{
		n=x;
		mas=new int[n];
		for(int i=0;i<n;i++)
			mas[i]=i;
	}
	
	//��������� ������
	friend ostream& operator<< (ostream& os, MyClass &obj)
	{
		os << obj.n << endl;
		for(int i=0;i<obj.n;i++)
			os << obj.mas[i] << " ";
		return os;
	}

	friend istream& operator>> (istream& is, MyClass &obj)
	{
		is >> obj.n;
		if(obj.mas!=NULL) delete obj.mas;
		obj.mas=new int[obj.n];
		for(int i=0;i<obj.n;i++)
			obj.mas[i]=i;
		return is;
	}

	friend fstream& operator<< (fstream& f, MyClass &obj)
	{
		f.write((char*)&obj.n,sizeof(int));
		for(int i=0;i<obj.n;i++)
			f.write((char*)&obj.mas[i],sizeof(int));
		return f;
	}

	friend fstream& operator>> (fstream& f, MyClass &obj)
	{
		if(obj.mas!=NULL) delete obj.mas;
		f.read((char*)&obj.n,sizeof(int));
		obj.mas=new int[obj.n];
		for(int i=0;i<obj.n;i++)
			f.read((char*)&obj.mas[i],sizeof(int));
		return f;
	}

	bool operator>(MyClass &obj) {return n>obj.n;}
	bool operator<(MyClass &obj) {return n<obj.n;}
	bool operator==(MyClass &obj) {return n==obj.n;}
	bool operator!=(MyClass &obj) {return n!=obj.n;}
};
*/


void menu()
{
	cout<<"����"<<endl;
	cout<<"1 - �������� �������"<<endl;
	cout<<"2 - ������� ������� �� ��������"<<endl;
	cout<<"3 - ������� ������"<<endl;
	cout<<"4 - ������������ ������"<<endl;
	cout<<"5 - ������� ����"<<endl;
	cout << "6 - ������� ������� �� ������" << endl;
	cout<<"0 - �����"<<endl;
}

void TestInt()
{
	cout << "������� ��� ����� ";
	char fname[100];
	cin >> fname;

	Shablon<int> Sh(fname);

	int k;
	do
	{
		system("cls");
		menu();
		cin >> k;
		int x;
		switch(k)
		{
		case 1:
			cout << "������� ����: ";
			cin>>x;
			Sh.AddObj(x);
			break;
		case 2:
			cout << "������� ��������: ";
			cin >> x;
			if(Sh.Find(x).el.pos!=0)
			{
				Sh.Del(Sh.Find(x));
				cout << "������ ������" << endl;
			}
			else cout << "������ �� ������" << endl;
			system("pause");
			break;
		case 3:
			cout << "������" << endl;
			Sh.Print();
			system("pause");
			break;
		case 4:
			Sh.Update();
			cout << "������ ���������������"<<endl;
			system("pause");
			break;
		case 5:
			Sh.Remove();
			break;
		case 6:
			cout << "������� ����� ��������: ";
			cin >> x;
			if (Sh.Del(x) == 0) cout << "������� �� ������" << endl;
			else cout << "������� ������" << endl;
			system("pause");
			break;
		}

	} while(k>0);
}

void TestString()
{
	cout << "������� ��� ����� ";
	char fname[100];
	cin >> fname;

	Shablon<String> Sh(fname);

	int k;
	String s(fname);

	do
	{
		system("cls");
		menu();
		int x;
		cin >> k;
	
		switch(k)
		{
		case 1:
			cout << "������� ������: ";
			getchar();
			cin>>s;
			Sh.AddObj(s);
			break;
		case 2:
			cout << "������� ��������: ";
			cin >> s;
			if(Sh.Find(s).el.pos!=0)
			{
				Sh.Del(Sh.Find(s));
				cout << "������ ������" << endl;
			}
			else cout << "������ �� ������" << endl;
			system("pause");
			break;
		case 3:
			cout << "������" << endl;
			Sh.Print();
			system("pause");
			break;
		case 4:
			Sh.Update();
			cout << "������ ���������������"<<endl;
			system("pause");
			break;
		case 5:
			Sh.Remove();
			break;
		case 6:
			cout << "������� ����� ��������: ";
			cin >> x;
			if (Sh.Del(x) == 0) cout << "������� �� ������" << endl;
			else cout << "������� ������" << endl;
			system("pause");
			break;
		}

	} while(k>0);
}


void TestMy()
{
	cout << "������� ��� ����� ";
	char fname[100];
	cin >> fname;

	Shablon<MyClass> Sh(fname);
	MyClass my;

	int k;
	do
	{
		system("cls");
		menu();
		int x;
		cin >> k;
		
		switch(k)
		{
		case 1:
			cout << "������� ������ ������� � ��������: ";
			cin>>my;
			cout << my;
			Sh.AddObj(my);
			break;
		case 2:
			cout << "������� ��������: ";
			cin >> my;
			if(Sh.Find(my).el.pos!=0)
			{
				Sh.Del(Sh.Find(my));
				cout << "������ ������" << endl;
			}
			else cout << "������ �� ������" << endl;
			system("pause");
			break;
		case 3:
			cout << "������" << endl;
			Sh.Print();
			system("pause");
			break;
		case 4:
			Sh.Update();
			cout << "������ ���������������"<<endl;
			system("pause");
			break;
		case 5:
			Sh.Remove();
			break;
		case 6:
			cout << "������� ����� ��������: ";
			cin >> x;
			if (Sh.Del(x) == 0) cout << "������� �� ������" << endl;
			else cout << "������� ������" << endl;
			system("pause");
			break;
		}

	} while(k>0);
}

void main()
{
	system("cls");
	setlocale(LC_ALL, ".ACP");

	cout<<"������� ��� ������"<<endl;
	cout<<"1 - int"<<endl;
	cout<<"2 - string"<<endl;
	cout<<"3 - MyClass"<<endl;

	int type;
	cin>>type;

	if(type==1) TestInt();
	else
	if(type==2) TestString();
	else
	if(type==3) TestMy();

	system("pause");
}