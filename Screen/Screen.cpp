#include"Screen.h"

/*
	���������� ������������ clear set ��� ������ �����

*/

const int Screen::maxHeight=24;
const int Screen::maxWidth=80;
const char Screen::_filler='.';


// �����������:
// ����� ���� ��������� ������ pc, ���� �� �������,
// ������ � ������������ _filler
Screen::Screen(int m, int n, char *s):
// ����������� ������� � ������ ������ � ���������� 
// ��������� ������ �� ���� ���������� ��� � 
// � ������ ��� ���� ����� ��
      _width(m>maxWidth? maxWidth :m), 
      _height(n>maxHeight? maxHeight :n), 
// ������ �������������� ����� ������ ��������
      _cursor(0)
{
// ������� ���� ���� ������������, ��� ������� 
// ����� �������, ������ ������ ���� �������
// if (s==0) lens=0; else lens = strlen(s);
   int lens= s==0? 0 :strlen(s);
// ���� ������� ����� ���������� ����� ������,
// ������ ����
   int len=lens>_height*_width? _height*_width :lens;
// ��������� ����� ������ � �����
   _wContent=new char [_height*_width+1];
// ���������� ���� �������� � ���� 
// �������� ��������� �����
   _wContent[_height*_width]='\0';
   int k=0;
   if(s!=0)
// ������� �� ������� ������ �����, 
// ��������� �� ��������
      for(; k<len; k++)
         *(_wContent+k)=*s++;
// ���������� ����� �� ���� ������������
   for(; k<_height*_width; k++)
      *(_wContent+k)=_filler;
};
// ����������
Screen::~Screen()
{
   delete [] _wContent;
}

// �������� ������ �� ������� ������
const Screen &Screen::home() const
{
   _cursor=0;
   return *this;
};
Screen &Screen::home()
{
   _cursor=0;
   return *this;
};

// ���������� ������ �� ���� ������ ������
const Screen &Screen::move() const
{
   if((++_cursor)>=_width*_height)_cursor=0;
   return *this;
};
 Screen &Screen::move() 
{
   if((++_cursor)>=_width*_height)_cursor=0;
   return *this;
};

// ��������� ������ �� ������ �������
const Screen &Screen::move(int i, int j) const
{
// ���� ������� ����������, ���������� ������ 
// �� ������� ������
   if((i>=_height)||(j>=_width))
      _cursor=0;
   else
      _cursor=_width*i+j;
   return *this;
};
Screen &Screen::move(int i, int j) 
{
// ���� ������� ����������, ���������� ������ 
// �� ������� ������
   if((i>=_height)||(j>=_width))
      _cursor=0;
   else
      _cursor=_width*i+j;
   return *this;
};

 Screen &Screen::set(char a) 
{
   *(_wContent+_cursor)=a;
   return *this;
}

// ���������� ������ �� ���� ������ ����
const Screen &Screen::back() const
{
   if(--_cursor<0)_cursor=0;
   return *this;
};
 Screen &Screen::back() 
{
   if(--_cursor<0)_cursor=0;
   return *this;
};

// �������� ���� ������
const Screen &Screen::show() const
{
// ���������� �������� �������
   int cursor=_cursor;
   cout<<"cursor="<<_cursor<<endl;
   home();
// ���� �� ������� ������
   for(int i=0; i<_height; i++)
   {
// ���������� ������ �����
      for(int j=0; j<_width; j++)
      {
      cout<<get();
      move();
      }
      cout<<endl;
   }
// ³��������� �������� �������
   _cursor=_cursor;
   return *this;
};
Screen &Screen::show() 
{
// ���������� �������� �������
   int cursor=_cursor;
   cout<<"cursor="<<_cursor<<endl;
   home();
// ���� �� ������� ������
   for(int i=0; i<_height; i++)
   {
// ���������� ������ �����
      for(int j=0; j<_width; j++)
      {
      cout<<get();
      move();
      }
      cout<<endl;
   }
// ³��������� �������� �������
   _cursor=_cursor;
   return *this;
};

Screen &Screen::clear()
{
   for(int i=0; i<_height*_width; i++)
      *(_wContent+i)=_filler;
   _cursor=0;
   return *this;
}

// �������� ������, ����� ���� ������������ ������
char Screen::get() const
{
   return *(_wContent+_cursor);
};
 char Screen::get() 
{
   return *(_wContent+_cursor);
};

 // �������� ������, ����� ���� ������������ ������
 const Screen & Screen::showCurrent() const
 {
	 cout<<"showCurrent "<< get()<<endl;
	 return *this;
 };
 Screen & Screen::showCurrent()
 {
	cout<<"showCurrent "<<get()<<endl;
	 return *this;
 };

//������������ �����
 ostream& operator<<(ostream& os, const Screen& s)
 {
	
   os<<"cursor="<<s.getCursor()<<endl;
   s.home();
// ���� �� ������� ������
   for(int i=0; i<s.getHeight(); i++)
   {
// ���������� ������ �����
      for(int j=0; j<s.getWidth(); j++)
      {
      os<<s.get();
      s.move();
      }
      cout<<endl;
   }
	 return os;
 }
