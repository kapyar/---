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
	//����������� inline
	Point (double x=0, double y=0):
	  _x(x),_y(y),_pointID(++_freeID)
	  {
		#ifndef NDEBUG
		  cout<<"Point � "<<_pointID<<": (x="<<_x<<" y="<<_y<<") was created"<<endl;
		#endif
		  //������� ��'���� ����������� ����� � ������������� 
		  //�� �������� _amount ���� �������� ������� 
		  //��������� ����� �� ��� ��������� ��������
		};

//����������� ���������
	Point (const Point & a);
	~Point();
	Point& operator=(const Point &);

//������������
	double& x(){return _x;};
	double& y(){return _y;};
	void setX(double x){_x=x;};
	void setY(double y){_y=y;};

//���������
	const double& x() const {return _x;};
	const double& y() const {return _y;};
	const double& getX() const {return _x;};
	const double& getY() const {return _y;};

//������
	const int getID() const {return _pointID;};
	static int amount()
	{
		#ifndef NDEBUG
			cout<<"The amount numbers of objects: ";
		#endif
		return (_freeID);
	};//������� ����� �� ���� �������

};

//�� ����� �����
ostream& operator<<(ostream&, const Point&);
const Point operator+ (const Point & u, const Point & v);
Point& operator+=(Point &, const Point&);
bool operator==(const Point & u, const Point &v);
bool operator!=(const Point & u, const Point &v);