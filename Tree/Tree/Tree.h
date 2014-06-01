#ifndef _TREE_H_
#define _TREE_H_

#include"Node.h"
template<typename T>
class Tree
{
  private:
    Node<T> *_root; //корінь дерева
    void search (T,Node<T>**);
  public:
    Tree() :_root(0){}
	Node<T>** getTree () {return &_root;} 
    void buildTree ();
    void clearTree (Node<T> **);
    void bypassEnd (Node<T> **);
    void bypassLeft (Node<T> **);
    void bypassBack (Node<T> **);
    void show (Node<T>**,int);
    int height (Node<T>**);
};
template<typename T>
void Tree<T>::buildTree ()
{
  T elem;
  cout<<"Input values 0 to stop"<<endl;;
  cin>>elem;
  while  (elem!=0)
  { 
	  search (elem,&_root);
	  cin>>elem; 
  }
}
template<typename T>
void Tree<T>::search (T x,Node<T> **p)
{
  if  (*p==0)
  {
    *p = new(Node<T>);
    (**p).Key = x;     (**p).Count = 1;
    (**p).Left = 0; (**p).Right = 0; }
  else
    if  (x<(**p).Key) 
		search (x,&((**p).Left));
    else
      if  (x>(**p).Key) 
		  search (x,&((**p).Right));
      else  (**p).Count = (**p).Count + 1;
}
template<typename T>
void Tree<T>::bypassLeft (Node<T> **w)
{
  if  (*w!=0)
  {
    cout<<(**w).Key<<" ";
    bypassLeft (&((**w).Left));
    bypassLeft (&((**w).Right));
  }
}
template<typename T>
void Tree<T>::bypassEnd (Node<T> **w)
{
  if  (*w!=0)
  {
	bypassEnd (&((**w).Left));
    bypassEnd (&((**w).Right));
    cout<<(**w).Key<<" "; 
  }
}
template<typename T>
void Tree<T>::bypassBack (Node<T> **w)
{
  if  (*w!=0)
  { 
	bypassBack (&((**w).Left));
	cout<<(**w).Key<<" ";
    bypassBack (&((**w).Right)); 
  }
}
template<typename T>
void Tree<T>::clearTree (Node<T> **w)
{
  if  (*w!=0)
  { 
	  clearTree (&((**w).Left));
      clearTree (&((**w).Right));
      delete *w; 
  }
}
template<typename T>
void Tree<T>::show (Node<T> **w,int len)

{
  int i;

  if  (*w!=0)
  {
	  show (&((**w).Right),len+1);
      for  (i=1; i<=len; i++) cout<<"   ";
		cout<<(**w).Key<<endl;
      show (&((**w).Left),len+1); }
}
template<typename T>
int Tree<T>::height (Node<T> **w)
{
  int h1,h2;
  if  (*w==0) return (-1);
  else
  {
    h1 = height (&((**w).Left));
    h2 = height (&((**w).Right));
    if  (h1>h2) return (1 + h1);
    else  return (1 + h2);
  }
}
#endif