#ifndef _SEQUENCE_H
#define _SEQUENCE_H

#include <iostream>
#include<cassert>
using namespace std;
#include"Array.h"

// ���������� ��������� �������� ���� Elem
//�������� ������� �����������
//
//��������� ������� �� ���� �����������
//
//��������� ������� � ������� �����������
//
//����������� ��������� �������� �� �����������
template <typename Elem>
class Sequence
{
public:
// �������� ���������� ��������
   class BadSeq;
// �����������, �������� �� ������������� ����
   explicit Sequence(size_t capacity = _default);
// ����������
   ~Sequence();

// ������ ������ ����������
   size_t capacity() const;
// ������ �������� �����
   size_t size() const;
// �� ������� �����������?
   bool empty() const;

// �������� �����������
   Sequence &clear();

// �������� �������� �����������
   const Elem &operator[](size_t index) const;
// ��������-����������� �������� �����������
   Elem &operator[](size_t index);

//��������� ������� �� ���� �����������
   Sequence &add(const Elem &elem);
//��������� ������� � ������� �����������
   Sequence &cut();
//����������� ��������� �������� �� �����������
   bool isIndepend(const Elem & elem);

   size_t getBlock()const{return _default;}
private:
// ����� �����������
   size_t _size;
// ����������� ����� ����� ����������
   static const size_t _default;
// ����� ��� ��������� �����������
   Array<Elem>  *_allocator;
// �������� ������
   void enlarge(size_t times=1);
//�������� � ������� ����
  void reduce(size_t times=2);
// �������� ������� � ��������
   Sequence(const Sequence &);
   Sequence &operator=(const Sequence &);
};
//�����������
template<typename Elem>
const size_t Sequence<Elem>::_default(4);


template<typename Elem>
ostream &operator<<(ostream&os, const Sequence<Elem> &seq)
{
	os<<"Size of sequence: "<<seq.size()<<'('<<seq.capacity()<<')'<<"size of block: "<<seq.getBlock()<<endl;
	if(!seq.empty())
	{
	
	for(size_t i = 0;i<seq.size()-1;++i)
		os<<seq[i]<<", ";
	os<<seq[seq.size() - 1];
	}
	return os;
}

//�����������
template<typename Elem>
Sequence<Elem>::Sequence(size_t size):
// ����������� ������� �������� �����������
      _size(0), 
// �������� ���'�� ��� �����������
      _allocator(new Array<Elem>(size))
{
#ifndef NDEBUG
	cout<<"In constructor of Sequence"<<endl;
#endif
   return;
};

//����������
template<typename Elem>
Sequence<Elem>::~Sequence()
{
#ifndef NDEBUG
	cout<<"In destructor of Sequence"<<endl;
#endif
	delete _allocator;
}

// ������ ������ ����������
template<typename Elem>
size_t Sequence<Elem>::capacity() const
{
// �����������
   return _allocator->size();
}

template<typename Elem>
size_t Sequence<Elem>::size() const
{
	return _size;
}
// �� ������� �����������?
template<typename Elem>
   bool Sequence<Elem>::empty() const
   {
	   return _size == 0;
   }

// �������� �����������
   template<typename Elem>
   Sequence<Elem> &Sequence<Elem>::clear()
   {
	   while(!empty())
	   {
		   cut();
	   }
	   return *this;
   }

// �������� �������� ����������� 
template<typename Elem>
const Elem &Sequence<Elem>::operator[](size_t index) const
{
// �������� ��������� �����������
   if(empty())
      throw BadSeq
          ("Try to manipulate the empty sequence");
// �������� ������ �� ��� �����������
   if(index>_size)
      throw BadSeq
      ("Try to access a non existing element of the sequence");
// ����������� ������������ �����
// ����� ���� �������
   return (*_allocator)[index];
}

// �����������
template<typename Elem>
Elem &Sequence<Elem>::operator[](size_t index)
{
// �������� ��������� �����������
   if(empty())
      throw BadSeq
          ("Try to manipulate the empty sequence");
// �������� ������ �� ��� �����������
   if(index>_size)
      throw BadSeq
      ("Try to access a non existing element of the sequence");
// ����������� ������������ �����
// ����� ���� �������
   return (*_allocator)[index];
}

// �������� ������
template<typename Elem>
void Sequence<Elem>::enlarge(size_t times=1)
{
// ���� ����� �� ����� �����
   Array<Elem> *newArray=
      new Array<Elem>(times*_default+capacity());
// ���������� �� ����� ���� ������� ������
   for (size_t i=0; i<_size; i++)
      (*newArray)[i]=(*_allocator)[i];
// �������� ������ �����
   delete _allocator;
// �������������� ����������� ����� �� ����� �����
   _allocator=newArray;
   return;
}

//�������� � ������� ����
template<typename Elem>
  void Sequence<Elem>::reduce(size_t times = 2)
  {
	size_t newLenght = capacity()/times + 1;
	if(newLenght<getBlock()) newLenght = getBlock();//����������� ����� �����
	// ���� ����� �� ����� �����
  Array<Elem> *newArray = 
	  new Array<Elem>(newLenght);
// ���������� �� ����� ���� ������� ������
  for(size_t i = 0; i< newLenght;++i)
	  (*newArray)[i]=(*_allocator)[i];
// �������� ������ �����
   delete _allocator;
// �������������� ����������� ����� �� ����� �����
   _allocator=newArray;
   return;
  }
//��������� ������� �� ���� �����������
template<typename Elem>
Sequence<Elem> & Sequence<Elem>::add(const Elem &elem)
{ 
// ���� ��������� �����������
   if(_size+1>capacity())
     enlarge();
// �������� ����� �����������
   (*_allocator)[_size] = elem;
   ++_size;
   return *this;
}
//��������� ������� � ������� �����������
template<typename Elem>
Sequence<Elem> & Sequence<Elem>::cut() 
   {
	   if(empty())
		   throw BadSeq("Can't delete nothing");
	   else
	   {
		   //check to cut containers
		   if(capacity()>size()*2 + 1)
			   reduce();
		   for(size_t i = 0;i<_size-1;++i)
			   (*_allocator)[i] = (*_allocator)[i+1];
		   --_size;
	   }
	   return *this;
   }
//����������� ��������� �������� �� �����������
template<typename Elem>
bool Sequence<Elem>::isIndepend(const Elem& elem)
   {
	   for(size_t i = 0;i<_size;++i)
			if((*_allocator)[i] == elem) return false;
	
	   return true;  
   }

//�������� �������� ��������
template<typename Elem>
class Sequence<Elem>::BadSeq
{
public:
	BadSeq(string reason="unknown", size_t index = 0)
		:_reason(reason), _index(index)
	{
		return;
	}
	~BadSeq()
	{
		return;
	}
	void showInfo() const
	{
		for(size_t i = 0;i<_reason.length();++i)
			cout<<_reason[i];
		cout<<", index: "<<_index<<endl;
	}
private:
	string _reason;
	size_t _index;
};

#endif