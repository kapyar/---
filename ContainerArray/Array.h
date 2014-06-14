#ifndef _ARRAY_H_
#define _ARRAY_H_

//#define NDEBUG

#include <iostream>
using namespace std;

/*
typedef int my_int ;
typedef double my_double ;
typedef char my_char ;
*/
// ����� �������� ���� Elem
// ���������� �����
template <size_t n, typename Elem>
class Array
{
private:
// ����� ������
   size_t _size;
// ������� �� ��������� ������
   Elem *_allocator;
// �������� �� �������, �� �������� ��� ������
   bool operator==(const Array &) const;
   Array(const Array &);
   Array &operator=(const Array &);

public:
//������� ������ �� ��� ������� ������
	class BadIndex;
// ����������� ������
	explicit Array();
	~Array();

// ����������� �������� ������
   Elem &operator[](size_t index);
// �������� �������� ������
   const Elem &operator[](size_t index) const;
// ����� ������ (��������)
   size_t size() const;
  
};

//�����������
template <size_t n, typename Elem>
Array<n,  Elem>::Array()
	:_size(n), _allocator(new Elem[n])
{
#ifndef NDEBUG
	cout<<"*In constructor of Array"<<endl;
#endif
//	�������� �������� � ���������� �� �������������,
//	��� �������� <type_traits> ���������� � ������ � 2011
//	http://www.cplusplus.com/reference/type_traits/ ���� � 2008 ���䳿
//	�������� �������� ���������
	/*
	for(size_t i = 0;i<n;++i)
	{
		if(is_pod<_allocator[i]>)
			_allocator = 0;
	}
	*/
};

//����������
template <size_t n, typename Elem>
Array<n,  Elem>::~Array()
{
#ifndef NDEBUG
	cout<<"*In destructor of Array"<<endl;
#endif
	delete [] _allocator;
	_allocator = 0;
};

// ����������� �������� ������
template <size_t n, typename Elem>
Elem& Array<n,  Elem>::operator[](size_t index)
{
	if(index<0 || index>=n) 
		throw BadIndex("out of border", index);
	else
		return _allocator[index];
};

// �������� �������� ������
template <size_t n, typename Elem>
const Elem& Array<n,  Elem>::operator[](size_t index) const
{
	if(index<0 || index>=n) 
		throw BadIndex("out of border", index);
	else
		return _allocator[index];
};

// ����� ������ (��������)
template <size_t n, typename Elem>
size_t Array<n,  Elem>:: size() const
{
	return _size;
};


//��������� ������
template <size_t n, typename Elem>
ostream& operator<<(ostream & os,const  Array<n, Elem>& a)
{
	os<<"Size of array: "<<a.size()<<endl;
	for(size_t i = 0;i<a.size()-1;++i)
		os<<i<<" ("<<a[i]<<"), ";
	os<<a.size()-1<<" ("<<a[a.size()-1]<<")";
	return os;
};
// ���� ��� ������� ���������� ��������
template <size_t n, typename Elem>
class Array<n, Elem>::BadIndex
{
private:
// ������� ������� ��������
    string _reason;
// ̳��� �� ���������
    size_t _index;
public:
// ����������� ���������
	BadIndex
		(string reason="unknown", size_t index=0):
	_reason(reason), _index(index)
	{
#ifndef NDEBUG
	cout<<"Constructor of BadIndex"<<endl;
#endif
	return;
	};

//���������
	const string getReason()const{return _reason;}
	const size_t getIndex()const{return _index;}
// ���������� ���������
	~BadIndex() {};

//���� ����������
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