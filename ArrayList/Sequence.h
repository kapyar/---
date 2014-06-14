#ifndef _SEQUENCE_H
#define _SEQUENCE_H

#include <iostream>
#include<cassert>
using namespace std;
#include"Array.h"

// Послідовний контейнер елементів типу Elem
//Створити порожню послідовність
//
//·Долучити елемент до кінця послідовності
//
//·Вилучити елемент з початку послідовності
//
//·Встановити належність елемента до послідовності
template <typename Elem>
class Sequence
{
public:
// Обробник помилкових ситуацій
   class BadSeq;
// Конструктор, закритий від конвертування типів
   explicit Sequence(size_t capacity = _default);
// Деструктор
   ~Sequence();

// Видати ємність контейнера
   size_t capacity() const;
// Видати поточний розмір
   size_t size() const;
// Чи порожня послідовність?
   bool empty() const;

// Очистити послідовність
   Sequence &clear();

// Селектор елемента послідовності
   const Elem &operator[](size_t index) const;
// Селектор-модифікатор елемента послідовності
   Elem &operator[](size_t index);

//·Долучити елемент до кінця послідовності
   Sequence &add(const Elem &elem);
//·Вилучити елемент з початку послідовності
   Sequence &cut();
//·Встановити належність елемента до послідовності
   bool isIndepend(const Elem & elem);

   size_t getBlock()const{return _default;}
private:
// Розмір послідовності
   size_t _size;
// Стандартний розмір блоку контейнера
   static const size_t _default;
// Масив для розміщення послідовності
   Array<Elem>  *_allocator;
// Збільшити ємність
   void enlarge(size_t times=1);
//Зменшити у кількість разів
  void reduce(size_t times=2);
// Невживані функції і операції
   Sequence(const Sequence &);
   Sequence &operator=(const Sequence &);
};
//ініціалізація
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

//Конструктор
template<typename Elem>
Sequence<Elem>::Sequence(size_t size):
// Ініціалізація довжини порожньої послідовності
      _size(0), 
// Виділення пам'яті для послідовності
      _allocator(new Array<Elem>(size))
{
#ifndef NDEBUG
	cout<<"In constructor of Sequence"<<endl;
#endif
   return;
};

//деструктор
template<typename Elem>
Sequence<Elem>::~Sequence()
{
#ifndef NDEBUG
	cout<<"In destructor of Sequence"<<endl;
#endif
	delete _allocator;
}

// Видати ємність контейнера
template<typename Elem>
size_t Sequence<Elem>::capacity() const
{
// Делегування
   return _allocator->size();
}

template<typename Elem>
size_t Sequence<Elem>::size() const
{
	return _size;
}
// Чи порожня послідовність?
template<typename Elem>
   bool Sequence<Elem>::empty() const
   {
	   return _size == 0;
   }

// Очистити послідовність
   template<typename Elem>
   Sequence<Elem> &Sequence<Elem>::clear()
   {
	   while(!empty())
	   {
		   cut();
	   }
	   return *this;
   }

// Селектор елемента послідовності 
template<typename Elem>
const Elem &Sequence<Elem>::operator[](size_t index) const
{
// Перевірка порожності послідовності
   if(empty())
      throw BadSeq
          ("Try to manipulate the empty sequence");
// Перевірка виходу за межі послідовності
   if(index>_size)
      throw BadSeq
      ("Try to access a non existing element of the sequence");
// Делегування розподілювачу пам’яті
// через його указник
   return (*_allocator)[index];
}

// Модифікатор
template<typename Elem>
Elem &Sequence<Elem>::operator[](size_t index)
{
// Перевірка порожності послідовності
   if(empty())
      throw BadSeq
          ("Try to manipulate the empty sequence");
// Перевірка виходу за межі послідовності
   if(index>_size)
      throw BadSeq
      ("Try to access a non existing element of the sequence");
// Делегування розподілювачу пам’яті
// через його указник
   return (*_allocator)[index];
}

// Збільшити ємність
template<typename Elem>
void Sequence<Elem>::enlarge(size_t times=1)
{
// Дати запит на новий масив
   Array<Elem> *newArray=
      new Array<Elem>(times*_default+capacity());
// Переписати до нього вміст старого масиву
   for (size_t i=0; i<_size; i++)
      (*newArray)[i]=(*_allocator)[i];
// Видалити старий масив
   delete _allocator;
// Переспрямувати розподілювач пам’яті на новий масив
   _allocator=newArray;
   return;
}

//Зменшити у кількість разів
template<typename Elem>
  void Sequence<Elem>::reduce(size_t times = 2)
  {
	size_t newLenght = capacity()/times + 1;
	if(newLenght<getBlock()) newLenght = getBlock();//стандартний розмір блоку
	// Дати запит на новий масив
  Array<Elem> *newArray = 
	  new Array<Elem>(newLenght);
// Переписати до нього вміст старого масиву
  for(size_t i = 0; i< newLenght;++i)
	  (*newArray)[i]=(*_allocator)[i];
// Видалити старий масив
   delete _allocator;
// Переспрямувати розподілювач пам’яті на новий масив
   _allocator=newArray;
   return;
  }
//·Долучити елемент до кінця послідовності
template<typename Elem>
Sequence<Elem> & Sequence<Elem>::add(const Elem &elem)
{ 
// Якщо контейнер переповнено
   if(_size+1>capacity())
     enlarge();
// Збільшити розмір послідовності
   (*_allocator)[_size] = elem;
   ++_size;
   return *this;
}
//·Вилучити елемент з початку послідовності
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
//·Встановити належність елемента до послідовності
template<typename Elem>
bool Sequence<Elem>::isIndepend(const Elem& elem)
   {
	   for(size_t i = 0;i<_size;++i)
			if((*_allocator)[i] == elem) return false;
	
	   return true;  
   }

//Обробник аварійних ситуацій
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