#include"Screen.h"

 // Застосувати до екрана s сталий метод act n разів
void doActionConst
   (const Screen &s, ConstAction act, int n)
{
   for(int i=0; i<n; i++)
      (s.*act)();
}

// Застосувати до екрана s метод act n разів
void doActionNonConst
   (Screen &s, NonConstAction act, int n)
{
   for(int i=0; i<n; i++)
      (s.*act)();
}


int main()
{
   const int size=10;
   Screen demo(size, size);
   cout<<"Empty screen created"<<endl<<endl;
   demo.show();
   for(int i=0; i<=size; i++)
      demo.set('*').move(i, i);
   cout<<"The screen filled"<<endl<<endl;
   for(int i=0; i<=size; i++)
      demo.move(size-i-1, i).set('*');
   demo.show();
   demo.clear();
   demo.show();
   cout<<"operator<<"<<endl;
   cout<<demo<<endl;
   

  Screen v(4, 4, "1111222233334444");
  const Screen cv(5, 5, "aaaaabbbbbcccccdddddeeeee");

  cout<<"v: "<<endl;
  v.show();
  cout<<"cv: "<<endl;
  cv.show();
  cout<<"-=CONST SHOW=-"<<endl;
  cv.show();
  //cv.clear();
  cout<<cv<<endl;



cout<<endl<<"1. Transitivity"<<endl;
//Screen v(4, 4, "1111222233334444");
v.show().set('*').move(1, 1).set('*').
      move(2, 2).set('*').
      move(3, 3).set('*').show();

cout<<endl<<"2. Const transitivity"<<endl;
//const Screen cv(5, 5, "aaaaabbbbbcccccdddddeeeee");
cv.show().move(1, 1).showCurrent().
      move(2, 2).showCurrent().
      move(3, 3).showCurrent().show();

const NonConstAction menuNonConst[]=
{
   &Screen::home, 
   &Screen::move, 
   &Screen::back, 
   &Screen::clear,
   &Screen::show,
   &Screen::showCurrent
};

cout<<endl<<"******User menu********"<<endl;
int k, n;
char ch;
cout<<"3. Menu Non Const"<<endl;
v.show();
do
{
   cout<<"your action?(0-home:1-move:2-back:3-clear:4-show:5-showCurrent)";
   cin>>k;
   cout<<"multiplicity? ";
   cin>>n;
   doActionNonConst(v, menuNonConst[k], n);
   cout<<"Repeat(y/n)?";
   cin>>ch;
}
while(ch=='y');
cout<<"Non const Screen after changes: "<<endl;
v.show();

const ConstAction menuConst[]=
{
   &Screen::home, 
   &Screen::move, 
   &Screen::back, 
   &Screen::show,
   &Screen::showCurrent
};
cout<<"4. Menu Const"<<endl;
cv.show();
do
{
   cout<<"your action?(0-home:1-move:2-back:3-show:4-showCurrent)";
   cin>>k;
   cout<<"multiplicity? ";
   cin>>n;
   doActionConst(cv, menuConst[k], n);
   cout<<"Repeat(y/n)?";
   cin>>ch;
}
while(ch=='y');
cv.show();


return 0;
}