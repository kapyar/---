#include <iostream>
using namespace std;

class B {

public:
	B()
	{
		//throw 1;
		cout << "B" << endl;
	};


	 ~B()
	{
		//throw 1;
		cout << "~B" << endl;
	}
};

class A : public B
{
public:
	char* _str;
	B* _b;

	A():
		_str(new char[100]),
		_b(new B)
	{
		//_b = new B();
		cout << "A" << endl;
	}
	~A()
	{
		delete[] _str;
		delete _b;
		cout << "~A" << endl;
	}
};


class C :public A
{
public:
	C()
	{
		cout << "C" << endl;
	}
	~C(){
		cout << "~C" << endl;
	};

private:

};


int main() {

	C a;


	return 0;
}