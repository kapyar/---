#include<iostream>
using namespace std;

class Point
{
private:
	static int _freeID;
	const int _pointID;
	double _x;
	double _y;

public:
	//конструктор inline
	Point (double x=0, double y=0):
	  _x(x),_y(y),_pointID(++_freeID)
	  {
		#ifndef NDEBUG
		  cout<<"Point № "<<_pointID<<": (x="<<_x<<" y="<<_y<<") was created"<<endl;
		#endif
		  //оскільки об'єкти створюються тільки в конструкторах 
		  //то перемінна _amount буде рахувати кількість 
		  //створених обєктів за час існування програми
		};

//конструктор копіювання
	Point (const Point & a);
	~Point();
	Point& operator=(const Point &);

//модифікатори
	double& x(){return _x;};
	double& y(){return _y;};
	void setX(double x){_x=x;};
	void setY(double y){_y=y;};

//селектори
	const double& x() const {return _x;};
	const double& y() const {return _y;};
	const double& getX() const {return _x;};
	const double& getY() const {return _y;};

//методи
	const int getID() const {return _pointID;};
	static int amount()
	{
		#ifndef NDEBUG
			cout<<"The amount numbers of objects: ";
		#endif
		return (_freeID);
	};//кількість обєктів які були створені

};

//не члени класу
ostream& operator<<(ostream&, const Point&);
const Point operator+ (const Point & u, const Point & v);
Point& operator+=(Point &, const Point&);
bool operator==(const Point & u, const Point &v);
bool operator!=(const Point & u, const Point &v);