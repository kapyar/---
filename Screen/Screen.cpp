#include"Screen.h"

/*
	Заборонено використання clear set для сталих обєктів

*/

const int Screen::maxHeight=24;
const int Screen::maxWidth=80;
const char Screen::_filler='.';


// Конструктор:
// Екран буде заповнено рядком pc, якщо він заданий,
// інакше — наповнювачем _filler
Screen::Screen(int m, int n, char *s):
// Ініціалізація довжини і ширини екрана з одночасною 
// перевіркою виходу за його максимальні межі — 
// в такому разі буде взято їх
      _width(m>maxWidth? maxWidth :m), 
      _height(n>maxHeight? maxHeight :n), 
// Курсор встановлюється перед першим символом
      _cursor(0)
{
// Указник може бути невизначеним, тоді вважаємо 
// рядок порожнім, інакше беремо його довжину
// if (s==0) lens=0; else lens = strlen(s);
   int lens= s==0? 0 :strlen(s);
// Якщо довжина рядка наповнення надто велика,
// урізаємо його
   int len=lens>_height*_width? _height*_width :lens;
// Створюємо образ екрана в пам’яті
   _wContent=new char [_height*_width+1];
// Заповнення його починаємо з кінця 
// символом закінчення рядка
   _wContent[_height*_width]='\0';
   int k=0;
   if(s!=0)
// Вписуємо на початку екрану рядок, 
// переданий як параметр
      for(; k<len; k++)
         *(_wContent+k)=*s++;
// Доповнюємо екран до кінця наповнювачем
   for(; k<_height*_width; k++)
      *(_wContent+k)=_filler;
};
// Деструктор
Screen::~Screen()
{
   delete [] _wContent;
}

// Помістити курсор на початок екрана
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

// Перемістити курсор на один символ вправо
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

// Перенести курсор на задану позицію
const Screen &Screen::move(int i, int j) const
{
// Якщо позиція некоректна, переносимо курсор 
// на початок екрана
   if((i>=_height)||(j>=_width))
      _cursor=0;
   else
      _cursor=_width*i+j;
   return *this;
};
Screen &Screen::move(int i, int j) 
{
// Якщо позиція некоректна, переносимо курсор 
// на початок екрана
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

// Перемістити курсор на один символ вліво
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

// Показати вміст екрана
const Screen &Screen::show() const
{
// Збереження значення курсору
   int cursor=_cursor;
   cout<<"cursor="<<_cursor<<endl;
   home();
// Цикл за рядками екрана
   for(int i=0; i<_height; i++)
   {
// Формування одного рядка
      for(int j=0; j<_width; j++)
      {
      cout<<get();
      move();
      }
      cout<<endl;
   }
// Відновлення значення курсору
   _cursor=_cursor;
   return *this;
};
Screen &Screen::show() 
{
// Збереження значення курсору
   int cursor=_cursor;
   cout<<"cursor="<<_cursor<<endl;
   home();
// Цикл за рядками екрана
   for(int i=0; i<_height; i++)
   {
// Формування одного рядка
      for(int j=0; j<_width; j++)
      {
      cout<<get();
      move();
      }
      cout<<endl;
   }
// Відновлення значення курсору
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

// Показати символ, перед яким розташований курсор
char Screen::get() const
{
   return *(_wContent+_cursor);
};
 char Screen::get() 
{
   return *(_wContent+_cursor);
};

 // Показати символ, перед яким розташований курсор
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

//перевовнення стеку
 ostream& operator<<(ostream& os, const Screen& s)
 {
	
   os<<"cursor="<<s.getCursor()<<endl;
   s.home();
// Цикл за рядками екрана
   for(int i=0; i<s.getHeight(); i++)
   {
// Формування одного рядка
      for(int j=0; j<s.getWidth(); j++)
      {
      os<<s.get();
      s.move();
      }
      cout<<endl;
   }
	 return os;
 }
