#include<iostream>
using namespace std;
#include<cassert>
#define NDEBUG
// ���� ����������� ��������
template<class Pointee>
class ArrayHandler
{
private:
//   ����� ������
     size_t _size;
//   ������� �� �����
     Pointee *_pointee;
//   ������� �� �������
     Pointee *_end;
//   ������� ��������� �������� ������
     mutable Pointee *_current; 
//	�������� ������ ������ ��� ����������
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
//   �������� ���������� ��������
     class MisUse;
//   �����������, �������� �� ������������� ����
     explicit ArrayHandler(size_t size=0);
//   ����������
     ~ArrayHandler();
//   (��)���������� ���������
     ArrayHandler& operator=(ArrayHandler&);
//   �������� ����������� �����������
     bool defined() const;
//   �������� ������ ������
     size_t size() const 
	 {
		 check();
		 return _size;
	 }
//   ��������� �������� ��� ����������
//   �������� ������������ �����������
	 Pointee& operator*() const;
//   �������� ������� �� ���������
	 Pointee* operator->() const;
//   ������ ������� ������
     void start() const 
	 {
		 check();
		 _current =_pointee;
	 }
//   ��������� ���������� ������
     bool stop() const 
	 {
		 check();
		 return _current==_end;
	 } 
//   �������� ������������
     Pointee& operator[](size_t i);
	 const Pointee& operator[](size_t i) const;
//   �������� ������� ����������
//   �������� ������� ��������� �������� ������
//   �� ������ �����
     ArrayHandler& operator+(size_t);
//   �������� ����������� ����������
     ArrayHandler& operator++();
//   �������� ����������� ����������
     ArrayHandler& operator--();
}; 

//����������� 
template<class T>
ArrayHandler<T>::ArrayHandler(size_t size = 0)
	:_pointee(size == 0 ? 0:new T[size]),
	_size(size), 
	_current(_pointee),
	_end(_pointee + size - 1)

{
	//����������� 
	for(size_t i = 0;i<size;++i)
	{
		_pointee[i] = T();
	}

#ifndef NDEBUG
	innerTest();
#endif
	return;
}

//����������
template<class T>
ArrayHandler<T>::~ArrayHandler()
{

#ifndef NDEBUG
	cout<<"Destructing this"<<endl;
#endif
	delete [] _pointee;
	//�� � �� ��������� �� ��� � �� �������� ��� �������� �����
	_pointee = 0;
	_current = 0;
	_end = 0;
	return;
}

//   (��)���������� ��������� �������
template<class T>
ArrayHandler<T>& ArrayHandler<T>::operator= (ArrayHandler& source)
{
	check();

	if(&source != this)
	{
		//��������� ������ ����
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

//   �������� ����������� �����������
template<class T>
bool ArrayHandler<T>::defined() const
{
	return _pointee != 0;
}

//   ��������� �������� ��� ����������
//   �������� ������������ �����������
template<class T>
T& ArrayHandler<T>:: operator*() const
{
	check();
	return *_current;
}
//   �������� ������� �� ���������
template<class T>
T* ArrayHandler<T>:: operator->() const
{
	check();
	return _current;
}

//   �������� ������������
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

//   �������� ������� ����������
//   �������� ������� ��������� �������� ������
//   �� ������ �����
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
//   �������� ����������� ����������
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
//   �������� ����������� ����������
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
