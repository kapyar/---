#include<iostream>
using namespace std;
#include<cassert>
#define NDEBUG
// Клас маніпуляторів масивами
template<class Pointee>
class ArrayHandler
{
private:
//   Розмір масиву
     size_t _size;
//   Указник на масив
     Pointee *_pointee;
//   Указник за масивом
     Pointee *_end;
//   Указник поточного елемента масиву
     mutable Pointee *_current; 
//	виводить адреси змінних для тестування
	 void innerTest()const
	 {
		cout<<"********************"<<endl;
		cout<<"constructing this"<<endl;
		cout<<"_pointee "<<_pointee<<endl;
		cout<<"_current "<<_current<<endl;
		cout<<"_end "<<_end<<endl;
		cout<<"********************"<<endl;
	 }

	 void check()const
	 {
		 if(!defined())
			throw MisUse("Try to use not defined pointer");
	 }

	// ArrayHandler& (const ArrayHandler &);

public:
//   Обробник помилкових ситуацій
     class MisUse;
//   Конструктор, закритий від конвертування типів
     explicit ArrayHandler(size_t size=0);
//   Деструктор
     ~ArrayHandler();
//   (Не)копіювальне присвоєння
     ArrayHandler& operator=(ArrayHandler&);
//   Перевірка визначеності маніпулятора
     bool defined() const;
//   Селектор розміру масиву
     size_t size() const 
	 {
		 check();
		 return _size;
	 }
//   Специфічні операції над указниками
//   Операція розіменування маніпулятора
	 Pointee& operator*() const;
//   Операція доступу за указником
	 Pointee* operator->() const;
//   Почати обробку масиву
     void start() const 
	 {
		 check();
		 _current =_pointee;
	 }
//   Перевірити вичерпання масиву
     bool stop() const 
	 {
		 check();
		 return _current==_end;
	 } 
//   Операція індексування
     Pointee& operator[](size_t i);
	 const Pointee& operator[](size_t i) const;
//   Операції адресної арифметики
//   Збільшити указник поточного елемента масиву
//   на задане число
     ArrayHandler& operator+(size_t);
//   Операція префіксного інкременту
     ArrayHandler& operator++();
//   Операція префіксного декременту
     ArrayHandler& operator--();
}; 

//конструктор 
template<class T>
ArrayHandler<T>::ArrayHandler(size_t size = 0)
	:_pointee(size == 0 ? 0:new T[size]),
	_size(size), 
	_current(_pointee),
	_end(_pointee + size - 1)

{
	//ініціалізація 
	for(size_t i = 0;i<size;++i)
	{
		_pointee[i] = T();
	}

#ifndef NDEBUG
	innerTest();
#endif
	return;
}

//деструктор
template<class T>
ArrayHandler<T>::~ArrayHandler()
{

#ifndef NDEBUG
	cout<<"Destructing this"<<endl;
#endif
	delete [] _pointee;
	//не я їх створював не мені і їх видаляти але обнулити можна
	_pointee = 0;
	_current = 0;
	_end = 0;
	return;
}

//   (Не)копіювальне присвоєння руйнівне
template<class T>
ArrayHandler<T>& ArrayHandler<T>::operator= (ArrayHandler& source)
{
	check();

	if(&source != this)
	{
		//видаляємо старий обєкт
		delete [] _pointee;
		_pointee = source._pointee;
		source._pointee = 0;

		_current = _pointee;
		source._current = 0;

		_size = source._size;
		source._size = 0;

		_end = _pointee+_size;
		source._end = 0;

	}

	return *this;
}

//   Перевірка визначеності маніпулятора
template<class T>
bool ArrayHandler<T>::defined() const
{
	return _pointee != 0;
}

//   Специфічні операції над указниками
//   Операція розіменування маніпулятора
template<class T>
T& ArrayHandler<T>:: operator*() const
{
	check();
	return *_current;
}
//   Операція доступу за указником
template<class T>
T* ArrayHandler<T>:: operator->() const
{
	check();
	return _current;
}

//   Операція індексування
template<class T>
T& ArrayHandler<T>:: operator[](size_t i)
{
#ifndef NDEBUG
	cout<<"_current[i]: "<<&_current[i]<<endl;
	cout<<"_end "<<_end<<endl;
#endif
	check();

	if(&_current[i]>_end)
		throw  MisUse("Index is out of boarder");
	return _current[i];
}

template<class T>
const T& ArrayHandler<T>:: operator[](size_t i) const
{
#ifndef NDEBUG
	cout<<"_current[i]: "<<&_current[i]<<endl;
	cout<<"_end "<<_end<<endl;
#endif
	check();

	if(&_current[i]>_end)
		throw  MisUse("Index is out of boarder");
	return _current[i];
}

//   Операції адресної арифметики
//   Збільшити указник поточного елемента масиву
//   на задане число
template<class T>
ArrayHandler<T>& ArrayHandler<T>::operator+(size_t i)
{
	check();
	if(_pointee+i>_end)
	{
		throw MisUse("Cant increment : out of boarder");
	}
	else
	{
		_current = _pointee+i;
	}
	return *this;
}
//   Операція префіксного інкременту
template<class T>
ArrayHandler<T>& ArrayHandler<T>:: operator++()
{
	check();
	if (_current == _end)
		throw MisUse("Cant increment : out of boarder operator++");
	else
	{
#ifndef NDEBUG
		innerTest();
#endif
		++_current;
	}
	return *this;
}
//   Операція префіксного декременту
template<class T>
ArrayHandler<T>& ArrayHandler<T>:: operator--()
{
	check();
	if(_current == _pointee)
	{
		throw MisUse("Cant decrement index is out of boarder");
	}
	else
	{
#ifndef NDEBUG
		innerTest();
#endif
		--_current;
	}
	return *this;
}

template<class T>
ostream& operator<<(ostream& os, const ArrayHandler<T>& a)
{
	for(size_t i = 0;i<a.size();++i)
	{
		os<<i<<' '<<':'<<a[i]<<endl;
	}
	return os;
}

template<class T>
class ArrayHandler<T>::MisUse
{
private :
		string _reason;
public:
	MisUse(string reason = "Unknown Reason")
		:_reason(reason)
	{
#ifndef NDEBUG
		cout<<"Iside of MisUse: "<<endl;
#endif
	}

	string getReason()const
	{
		return _reason;
	}

	void diagnos() const
	{
		cout<<"reason: "<<endl;
		for(size_t i = 0;i<_reason.length();++i)
		{
			cout<<_reason[i];
		}
		cout<<endl;
	}
};
