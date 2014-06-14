// ��������� ����� ������������� ������
// maxHeigh � maxWidth
//
#include<iostream>
using namespace std;

class Screen
{
public:
// �����������:
// ����� ���� ��������� ������ pc, ���� �� �������,
// ������ � ������������ _filler
   Screen(int, int, char *pc=0);
// ����������
   ~Screen();

// ��������� ���� �� ������ ������
// �������� ������ �� ������� ������
   const Screen &home() const;
   Screen &home();
// ���������� ������ �� ���� ������ ������
   const Screen &move() const;
   Screen &move();
// ���������� ������ �� ���� ������ ����
   const Screen &back() const;
   Screen &back();
// �������� ���� ������
   const Screen &show() const;
   Screen &show();
// ��������� ������ �� ������ �������
   const Screen &move(int, int) const;
   Screen &move(int, int);
// �������� �����
   
   Screen &clear();
// �������� ������, ����� ���� ������������ ������
   const Screen &showCurrent() const;
   Screen &showCurrent();
// ��������
   char get() const;
   char get();
// �����������
   
   Screen &set(char);

    const int getCursor() const
	{
		return _cursor;
	}
	const int getHeight() const
	{
		return _height;
	}
	const int getWidth()const
	{
		return _width;
	}

private:
// ����������� ������ ������
   static const int maxHeight;
// ����������� ������ ������
   static const int maxWidth;
// ����������
   static const char _filler;
// �������� ������ ������
   int _height;
// �������� ������ ������
   int _width;
// ���������� ������
   char *_wContent;
// ̳��� ������������ �������
   mutable int _cursor;
// �����������, � ���� ������ ���������:
// ��������� ������ �� ����������� 
//����� ����������� ������� �� �������� ����
//������� ������, ����� �� �� _cursor mutable  
//�������� ������ clear, set � ������� �������
   Screen(const Screen &);
   Screen &operator=(const Screen &);
   //����������� �� ������ � ������ �������
   const Screen &clear()const;
   const Screen &set(char) const;
};

typedef const Screen&(Screen::*const ConstAction)()const;
typedef  Screen&(Screen::*const NonConstAction)();

//������
ostream& operator<<(ostream& os, const Screen&);
