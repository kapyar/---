#ifndef _NODE_H_
#define _NODE_H_

template<typename T>
class  Node
{
public:
  T Key;
  int Count;//������� ������ � �����
  Node *Left;
  Node *Right;
};

#endif