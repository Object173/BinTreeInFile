#ifndef _SHABLON_H
#define _SHABLON_H

#include<iostream>
#include<fstream>

using namespace std;

template<class Object>
class Shablon :public fstream
{
	unsigned long head; //указатель на голову
	unsigned long end; //указатель на конец файла 
	char *fname; //имя файла
	bool dynamic; //динамичен ли Object

	struct Elem //элемент дерева
	{
		unsigned long pos;
		unsigned long left;
		unsigned long right;

		Elem() {pos=left=right=0;}

		Elem(long p,long l,long r)
		{
			pos=p;
			left=l;
			right=r;
		}
	};

public:

	class iterator //итератор
	{
	public:
		Shablon<Object> *Sh;
		Elem el;

		iterator(Shablon<Object> &s) //конструктор
		{
			Sh=&s;
			el=Sh->GetHead();
		}
		iterator(iterator &it) //конструктор
		{
			Sh=it.Sh;
			el=it.el;
		}
		iterator &operator++(int) //сдвиг вперед
		{
			if(el.pos==end().el.pos)
			{
				el=begin().el;
			}
			if(el.right!=0)
			{
				el=Sh->GetEl(el.right);
				while(el.left!=0) el=Sh->GetEl(el.left);
				return *this;
			}

			Elem e=Sh->GetEl(PosNext(Sh->HeadPos()));
			while(!(Sh->GetObj(el.pos)<Sh->GetObj(e.pos)))
			{
				el=e;
				e=Sh->GetEl(PosNext(Sh->HeadPos()));
			}
			el=e;

			return *this;
		}
		iterator &operator--(int) // сдвиг назад
		{
			if(el.pos==begin().el.pos)
			{
				el=end().el;
			}
			if(el.left!=0)
			{
				el=Sh->GetEl(el.left);
				while(el.right!=0) el=Sh->GetEl(el.right);
				return *this;
			}

			Elem e=Sh->GetEl(PosNext(Sh->HeadPos()));
			while(Sh->GetObj(el.pos)<Sh->GetObj(e.pos))
			{
				el=e;
				e=Sh->GetEl(PosNext(Sh->HeadPos()));
			}
			el=e;

			return *this;
		}
		long Pos() {return el.pos-sizeof(long)*2;} //позиция текущего объекта
		long PosNext(long pos)
		{
			if (pos!=0) 
			{
				Elem e=Sh->GetEl(pos);
				if(Sh->GetEl(e.left).pos==el.pos || Sh->GetEl(e.right).pos==el.pos)
					return pos;
				long l;
				l=PosNext(Sh->GetEl(pos).left);
				if(l>0) return l;
				l=PosNext(Sh->GetEl(pos).right);
				if(l>0) return l;
			}
			return 0;
		}
		Object operator *(){return Sh->GetObj(el.pos);} //преобразование

		iterator& operator =(long pos) //присвоение по позиции
		{
			el=Sh->GetEl(pos);
			return *this;
		}
		iterator& operator =(iterator &it) //присвоение итератора
		{
			Sh=it.Sh;
			el=it.el;
			return *this;
		}

		long left() {return el.left;} //позиция левого
		long right() {return el.right;} // позиция правого
		iterator Left() {iterator it(*this); it.el=it.Sh->GetEl(left());return it;} //итератор левый
		iterator Right() {iterator it(*this); it.el=it.Sh->GetEl(right());return it;} // итератор правый

		iterator begin() //начало
		{
			iterator it=*this;
			it.el=Sh->GetHead();
			while(it.el.left!=0) it.el=Sh->GetEl(it.el.left);
			return it;
		}
		iterator end() //конец
		{
			iterator it=*this;
			it.el=Sh->GetHead();
			while(it.el.right!=0) it.el=Sh->GetEl(it.el.right);
			return it;
		}
		iterator head() //конец
		{
			iterator it=*this;
			it.el=Sh->GetHead();
			return it;
		}

		bool isbegin() {return el.pos==begin().el.pos;} //проверка на первый эл
		bool isend() {return el.pos==end().el.pos;} //проверка на последний эл

		bool operator==(Object &obj){return Sh->GetObj(el.pos) == obj;} //сравнение
		bool operator==(iterator &it){return Sh->GetObj(el.pos) == Sh->GetObj(it.el.pos);} 
		bool operator!=(iterator &it){return Sh->GetObj(el.pos) != Sh->GetObj(it.el.pos);} 
	};

	//конструктор без параметров
	Shablon():basic_fstream() {head=end=0;}

	Shablon(const char *name):basic_fstream(name, ios::in | ios::out | ios::binary)
	{
		fname=strdup(name);
		if(!is_open()) //если файла нет
		{
			ofstream of(name);
			of.close();
			open(name, ios::in | ios::out | ios::binary);

			head=end=2*sizeof(long);
			write((char*)&head,sizeof(long)); //голова
			write((char *)&end,sizeof(long)); //конец файла
		}
		else //если файл есть
		{
			read((char*)&head,sizeof(long)); //голова
			read((char*)&end,sizeof(long)); //конец файла
		}
		if(typeid(Object)==typeid(int) || typeid(Object)==typeid(double) || 
			typeid(Object)==typeid(char) || typeid(Object)==typeid(float) ||
			typeid(Object)==typeid(float))
			dynamic=false;
		else dynamic=true;
	}
	~Shablon()
	{
		delete[] fname;
		close();
	}
	void AddObj(Object &obj); //добавление объекта
	void Del(iterator &it); //удаление
	int Del(int n); //удаление по лог номеру
	void Print();
	void Update(); //пересборка файла
	void Remove() //удаление файла
	{
		close();
		remove(fname);
	}
	iterator Find(Object &obj) //поиск
	{
		iterator it=*this;
		while(GetObj(it)!=obj)
		{
			if(obj<GetObj(it)) 
				if (it.el.left==0) {it.el.pos=0;return it;}
				else it=it.Left();
			else
				if (it.el.right==0) {it.el.pos=0;return it;}
				else it=it.Right();
		}
		return it;
	}

private:
	Elem GetEl(long pos) //элемент дерева
	{
		long left,right;
		seekp(pos);
		read((char*)&left,sizeof(long));
		read((char*)&right,sizeof(long));
		//Elem el(tellg(),left,right);
		Elem el(pos+2*sizeof(long),left,right);
		return el;
	}
	Elem GetHead() {return GetEl(head);} //вершина дерева
	long HeadPos() {return head;}
	Object GetObj(long pos);
	Object GetObj(iterator &it) {return GetObj(it.el.pos);}
	void WriteP(Shablon<Object> &f,Elem e1, Elem e2);
};

template<class Object> int Shablon<Object>::Del(int n)
{
	iterator it(*this);
	it = it.begin();
	int i;
	for (i = 0; i < n && !it.isend(); i++, it++);
	if (i != n && it.isend()) return 0;
	Del(it);
	return 1;
}

template<class Object> void Shablon<Object>::WriteP(Shablon<Object> &f,Elem e1, Elem e2)
{
	iterator b(*this),e(*this);
	b.el=e1;e.el=e2;
	if(b==e)
	{
		Object obj=*b;
		f.AddObj(obj);
		return;
	}
	iterator it(*this);
	int size;
	for(it=b,size=1;it!=e;it++,size++);
	size=size/2+1;
	it=b;
	for(int i=1;i<size;i++,it++);
	Object obj=*it;
	f.AddObj(obj);

	it--;
	WriteP(f,b.el,it.el);
	it++;
	if(b++==e && e==it) return;
	else b--;
	it++;
	WriteP(f,it.el,e.el);
}

template<class Object> void Shablon<Object>::Update()
{
	Shablon<Object> Sh("UpdateFile.pop");
	iterator it(*this);
	WriteP(Sh,it.begin().el,it.end().el);
	Sh.close();	
	this->close();
	remove(fname);
	rename("UpdateFile.pop",fname);
	this->open(fname);
	read((char*)&head,sizeof(long)); //голова
	read((char*)&end,sizeof(long)); //конец файла
}

template<class Object> Object Shablon<Object>::GetObj(long pos) //объект по позиции
{
	Object obj;
	seekp(pos);
	if(dynamic) *this>>obj;
	else read((char*)&obj,sizeof(Object));	
	return obj;
}

template<class Object> void Shablon<Object>::AddObj(Object &obj) //добавить объект
{
	if(end>head)
	{
		Shablon<Object>::iterator it(*this);
		it=head;
		while(true)
		{
			if(obj<*it) 
				if(it.left()>0) it=it.Left();
				else 
				{
					seekp(it.Pos());
					write((char*)&end,sizeof(long));
					break;
				}
			else
				if(it.right()>0) it=it.Right();
				else 
				{
					seekp(it.Pos()+sizeof(long));
					write((char*)&end,sizeof(long));
					break;
				}
		}
	}
	seekp(end);
	long x=0;
	write((char*)&x,sizeof(long));
	write((char*)&x,sizeof(long));

	if(dynamic) 
		*this<<obj;
	else write((char*)&obj,sizeof(obj));
	
	end=tellg();

	seekp(sizeof(long));
	write((char*)&end,sizeof(long));	
}

template<class Object> void Shablon<Object>::Del(iterator &it)
{
	iterator iter=*this;
	iterator iter1=*this;
	iter.el=GetHead();
	iter1.el=GetHead();
	if(it==iter) //удаляем голову
	{
		if (iter.right() == 0)
		{
			seekp(0);
			head = iter.left();
			write((char*)&head, sizeof(long));
			return;
		}
		iter=iter.Right();
		while(iter.el.left!=0) iter=iter.Left();
		iter1=iter1.Left();
		iter.el.left=iter1.Pos();
		seekp(iter.Pos());
		long pos=iter.el.left;
		write((char*)&pos,sizeof(long));
		head=GetHead().right;
		seekp(0);
		write((char*)&head,sizeof(long));
		return;
	}
	while(iter.Left()!=it && iter.Right()!=it) //поиск вершины над удаляемым объектом
	{
		if(*it<*iter) iter=iter.Left();
		else iter=iter.Right();
	}
	if(it.el.left==0 && it.el.right==0) //если у удаляемого нет дочерних
	{
		if(iter.Left()==it)iter.el.left=0;
		if(iter.Right()==it)iter.el.right=0;
		seekp(iter.Pos());
		write((char*)&iter.el.left,sizeof(long));
		write((char*)&iter.el.right,sizeof(long));
		return;
	}
	if(it.el.right!=0) //если есть правый элемент
	{
		iter1=it.Right();
		while(iter1.el.left!=0) iter1=iter1.Left();
		iter1.el.left=it.el.left;
		seekp(iter1.Pos());
		long l=iter1.el.left;
		write((char*)&l,sizeof(long));
	}
	else 
		{
			it.el.right=it.el.left;
			seekp(it.Pos()+sizeof(long));
			long l=it.el.right;
			write((char*)&l,sizeof(long));
		}

	if(iter.Left()==it) //если удаляемый элемент слева
	{
		iter.el.left=it.el.right;
		seekp(iter.Pos());
		long l=iter.el.left;
		write((char*)&l,sizeof(long));
		return;
	}
	if(iter.Right()==it) //если справа
	{
		iter.el.right=it.el.right;
		seekp(iter.Pos()+sizeof(long));
		long l=iter.el.right;
		write((char*)&l,sizeof(long));
		return;
	}

}

template<class Object> void Shablon<Object>::Print()
{
	iterator it(*this);
	cout << "HEAD" << endl;
	cout << *it << endl;
	cout << "TREE" << endl;
	for(it=it.begin();!it.isend();it++)
		cout << *it << endl;
	cout << *it << endl;
}

#endif