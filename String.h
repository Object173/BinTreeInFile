#ifndef _STRING_H
#define _STRING_H

#include<string>
#include<stdio.h>
#include<iostream>
#include<fstream>

using namespace std;

class  String {
public:
char * str; 	// указатель на буфер
int len; 	//длина строки

String(){str = NULL; len = 0; }
String(char * s){ len = strlen(s); str = new char[len+1]; strcpy(str,s);}
~String(){ if (!str) {delete str;} } 
char* GetStroke() {return str;}
int GetLen() {return len;}
friend fstream& operator<<(fstream &os, const String &s);
friend fstream& operator>>(fstream &os, String &s);
friend ostream& operator<<(ostream &os, const String &s);
friend istream& operator>>(istream &os, String &s);
bool operator>(String &s) {return strcmp(str,s.GetStroke())==1;}
bool operator<(String &s) {return strcmp(str,s.GetStroke())==-1;}
bool operator==(String &s) {return strcmp(str,s.GetStroke())==0;}
bool operator!=(String &s) {return strcmp(str,s.GetStroke())!=0;}
};
fstream& operator<<(fstream &os, const String &s){
	os.write((char*)&s.len, sizeof(int));
	os.write(s.str, s.len);
	return os;
}
fstream& operator>>(fstream &os, String &s){
	os.read((char*)&s.len, sizeof(int));
	if(NULL!=s.str) 
		delete[] s.str;
	s.str=new char[s.len+1];
	os.read(s.str, s.len);
	s.str[s.len]=0;
	return os;
}
ostream& operator<<(ostream &os, const String &s){
	os<<s.str<<endl;
	return os;
}
istream& operator>>(istream &os, String &s){
	if(s.str!=NULL) delete[] s.str;
	char c[100];
	os.getline(c,100);
	//os>>c;
	s.len=strlen(c);
	s.str=strdup(c);
	return os;
}

#endif