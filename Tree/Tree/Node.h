#ifndef _NODE_H_
#define _NODE_H_

template<typename T>
class  Node
{
public:
  T Key;
  int Count;//кількість ключів у дереві
  Node *Left;
  Node *Right;
};

#endif