#include<iostream>
using namespace std;
#include"Tree.h"
/*
	Параметризоване бінарне дерево
	Три види обходу: лівосторонній, зворотній, та з кінця

*/

void main ()
{
	setlocale(LC_ALL, "Ukrainian");
	 Tree<double> a;

	a.buildTree ();
	cout<<"Our binary tree"<<endl;
	a.show (a.getTree(),0);
	cout<<"\nHeight of the tree: "<<a.height(a.getTree())<<endl;
	cout<<"\nBypassLeft: ";
	a.bypassLeft (a.getTree());
	cout<<"\nBypassEnd: "; a.bypassEnd (a.getTree());
	cout<<"\nBypassBack: "; a.bypassBack (a.getTree());
	a.clearTree (a.getTree());

	cout<<endl;
}