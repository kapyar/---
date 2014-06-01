#ifndef _TEST_H_
#define _TEST_H_
#include <iostream>
using namespace std;
#include <cmath>


struct TestFunctor
{
	void operator()(int i)
	{
		cout<<"test functor got int: "<<i<<endl;
	}
};

struct TestFunctor1
{
	void operator()()
	{
		cout<<"test Functor got nothing"<<endl;
	}
};

struct TestFunctor2
{
	int operator()(int i,int j)
	{
		cout<<"test functor got two ints: "<<i<<", "<<j<<endl;
		cout<<"and return their sum"<<endl;
		return (i+j);
	}
};

struct TestFunctor3
{
	void operator()(string s,int j)
	{
		cout<<"test functor got  string: ";
		for(size_t i = 0; i<s.length();++i)
			cout<<s[i];
		cout<<",and int : "<<j<<endl;
	}
};

class Elliptic
{
private:
	double _a, _b;
public:
	Elliptic (double a=1, double b=2):_a(a),_b(b){};
	~Elliptic(){};

	double operator()(double x) const
	{
		return 1.0/sqrt(_a*_a*cos(x)*cos(x)+(_b*_b)*(sin(x)*sin(x)));
	}
};

#endif

