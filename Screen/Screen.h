// Текстовий екран максимального розміру
// maxHeigh х maxWidth
//
#include<iostream>
using namespace std;

class Screen
{
public:
// Конструктор:
// Екран буде заповнено рядком pc, якщо він заданий,
// інакше — наповнювачем _filler
   Screen(int, int, char *pc=0);
// Деструктор
   ~Screen();

// Однойменні сталі та несталі методи
// Помістити курсор на початок екрана
   const Screen &home() const;
   Screen &home();
// Перемістити курсор на один символ вправо
   const Screen &move() const;
   Screen &move();
// Перемістити курсор на один символ вліво
   const Screen &back() const;
   Screen &back();
// Показати вміст екрану
   const Screen &show() const;
   Screen &show();
// Перенести курсор на задану позицію
   const Screen &move(int, int) const;
   Screen &move(int, int);
// Очистити екран
   
   Screen &clear();
// Показати символ, перед яким розташований курсор
   const Screen &showCurrent() const;
   Screen &showCurrent();
// Селектор
   char get() const;
   char get();
// Модифікатор
   
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
// Максимальна висота екрана
   static const int maxHeight;
// Максимальна ширина екрана
   static const int maxWidth;
// Наповнювач
   static const char _filler;
// Фактична висота екрана
   int _height;
// Фактична ширина екрана
   int _width;
// Наповнення екрана
   char *_wContent;
// Місце розташування курсору
   mutable int _cursor;
// Нереалізовані, а тому закриті копіювання:
// копіювання екранів не передбачене 
//також забороняємо очищати та змінювати вміст
//сталого екрану, через те що _cursor mutable  
//розміщаємо методи clear, set в закриту частину
   Screen(const Screen &);
   Screen &operator=(const Screen &);
   //забороняємо це робити зі сталим екраном
   const Screen &clear()const;
   const Screen &set(char) const;
};

typedef const Screen&(Screen::*const ConstAction)()const;
typedef  Screen&(Screen::*const NonConstAction)();

//утиліти
ostream& operator<<(ostream& os, const Screen&);
