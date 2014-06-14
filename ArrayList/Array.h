#ifndef _ARRAY_H_
#define _ARRAY_H_

//#define NDEBUG

#include <iostream>
using namespace std;


// Масив елементів типу Elem
// Визначення класу
template <typename Elem>
class Array
{
private:
// Розмір масиву
   size_t _size;
// Указник на розміщення масиву
   Elem *_allocator;
// Операції та функції, не визначені для масивів
   bool operator==(const Array &) const;
   Array(const Array &);
   Array &operator=(const Array &);

public:
//обробка виходу за межі індексу масива
	class BadIndex;
// Конструктор масиву
	explicit Array(size_t);
	~Array();
// Модифікатор елемента масиву
   Elem &operator[](size_t index);
// Селектор елемента масиву
   const Elem &operator[](size_t index) const;
// Розмір масиву (селектор)
   size_t size() const;

  
};

//конструктор
template <typename Elem>
Array<Elem>::Array(size_t n)
	:_size(n), _allocator(new Elem[n])
{
#ifndef NDEBUG
	cout<<"*In constructor of Array"<<endl;
#endif
//	вирішення проблеми зі значеннями за замовчуванням,
//	але бібліотека <type_traits> включається в версіях з 2011
//	http://www.cplusplus.com/reference/type_traits/ тому в 2008 студії
//	наступна перевірка неможлива
	
/*	for(size_t i = 0; i<n ;++i)
	{
		int a;
		if(is_pod<_allocator[i]>)
			_allocator[i] = 0;
	}
	*/
};

//деструктор
template <typename Elem>
Array<Elem>::~Array()
{
#ifndef NDEBUG
	cout<<"*In destructor of Array"<<endl;
#endif
	delete [] _allocator;
	_allocator = 0;
};

// Модифікатор елемента масиву
template <typename Elem>
Elem& Array<Elem>::operator[](size_t index)
{
	if(index<0 || index>=_size) 
		throw BadIndex("out of border", index);
	else
		return _allocator[index];
};

// Селектор елемента масиву
template <typename Elem>
const Elem& Array<Elem>::operator[](size_t index) const
{
	if(index<0 || index>=_size) 
		throw BadIndex("out of border", index);
	else
		return _allocator[index];
};

// Розмір масиву (селектор)
template <typename Elem>
size_t Array<Elem>:: size() const
{
	return _size;
};


//Виведення масиву
template <typename Elem>
ostream& operator<<(ostream & os,const  Array<Elem>& a)
{
	os<<"Size of array: "<<a.size()<<endl;
	for(size_t i = 0;i<a.size()-1;++i)
		os<<i<<" ("<<a[i]<<"), ";
	os<<a.size()-1<<" ("<<a[a.size()-1]<<")";
	return os;
};
// Клас для обробки помилкових ситуацій
template <typename Elem>
class Array<Elem>::BadIndex
{
private:
// Причина аварійної ситуації
    string _reason;
// Місце її виявлення
    size_t _index;
public:
// Конструктор обробника
	BadIndex
		(string reason="unknown", size_t index=0):
	_reason(reason), _index(index)
	{
#ifndef NDEBUG
	cout<<"Constructor of BadIndex"<<endl;
#endif
	return;
	};

//селектори
	const string getReason()const{return _reason;}
	const size_t getIndex()const{return _index;}
// Деструктор обробника
	~BadIndex() {};

//вивід інформації
	void diagnose() const 
	{
		cerr<<"****"<<endl;
		cerr<<"Size of array: "<<getIndex()<<endl;
		cerr<<"Reason: ";
		for(size_t i = 0;i<_reason.length();++i)
			cerr<<getReason()[i];
		cerr<<endl;
		cerr<<"Index: "<<getIndex()<<endl;
		cerr<<"****"<<endl;
		return;
	}
};

#endif