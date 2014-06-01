
#include"Functor.h"
#include"Test.h"
using namespace std;
#include<iostream>


int main()

{
	{
	TestFunctor f;
	Functor<void, TYPELIST_1(int)> cmd(f);
}
	cmd(3);

	TestFunctor1 ff;
	Functor<void,NullType> cmd1(ff);
	cmd1();

	TestFunctor2 f2;
	Functor<int,TYPELIST_2(int,int)> cmd2(f2);
	int sum = cmd2(3,7);
	cout<<"sum = "<<sum<<endl;
	
	TestFunctor3 f3;
	Functor<void,TYPELIST_2(string,int)> cmd3(f3);
	cmd3("string as parametr",3);

	Elliptic eliptic(1,6);
	Functor<double,TYPELIST_1(double)> cmdEliptic(eliptic);
	double x(4);
	cout<<"Eliptic(1,6) in x = 4: "<<cmdEliptic(x)<<endl;

	return 0;
};