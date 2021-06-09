#include<iostream>
#include<math.h>
#include<conio.h>
#include<windows.h>
#include<time.h>
#include<fstream>
#include<string>
#include <ctime>
//#define WINVER 0x0500

#define SCREEN_WIDTH 90
#define SCREEN_HEIGHT 25
#define WIN_WIDTH 60

using namespace std;

//HWND wh = GetConsoleWindow(); //Fixed the size of screen
//MoveWindow(wh, 100, 30, 150, 50, TRUE); // It is for Fixed the size of screen by using coordinates



HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;


int enemY[3];
int enemX[3];
int enemyFlag[3];
char car[4][4]= {' ','+','+',' ',
                 '+','+','+','+',
                 ' ','+','+',' ',
                 '+','+','+','+',};
int carPos=WIN_WIDTH/2;
int score=0;
    fstream fin;
    fstream fout;

//now below this it is use for  File handling.
using std::cout; using std::cerr;
using std::endl; using std::string;
using std::ifstream; using std::ostringstream;

void gotoxy(int x,int y)
{
    CursorPosition.X=x;
    CursorPosition.Y=y;
    SetConsoleCursorPosition(console, CursorPosition);
}

void SetCursor(bool visible, DWORD size)
{

    if(size==0)
    {
        size=20;
    }
    CONSOLE_CURSOR_INFO lpCursor;
    lpCursor.bVisible=visible;
    lpCursor.dwSize=size;
    SetConsoleCursorInfo(console,&lpCursor);
}

void drawBorder()
{
    for(int i=0;i<SCREEN_HEIGHT;i++)
    {
        for(int j=0;j<17;j++)
        {
          //  system("Color E2");
            gotoxy(0+j,i); cout<<"-";
            gotoxy(WIN_WIDTH+j,i); cout<<"-";
        }
    }
    for(int i=0; i<SCREEN_HEIGHT; i++)
    {
        gotoxy(SCREEN_WIDTH,i); cout<<"";
    }
}

void genEnemy(int ind)
{
    enemX[ind]=17+rand()%(33);
}

void drawEnemy(int ind)
{
    if(enemyFlag[ind]==true)
    {
        //system("Color E2");
        gotoxy(enemX[ind],enemY[ind]);   cout<<"****";
        gotoxy(enemX[ind],enemY[ind]+1); cout<<"****";
        gotoxy(enemX[ind],enemY[ind]+2); cout<<"****";
        gotoxy(enemX[ind],enemY[ind]+3); cout<<" ** ";
    }
}

void eraseEnemy(int ind)
{
    if(enemyFlag[ind]==true)
    {
        gotoxy(enemX[ind],enemY[ind]);   cout<<"    ";
        gotoxy(enemX[ind],enemY[ind]+1); cout<<"    ";
        gotoxy(enemX[ind],enemY[ind]+2); cout<<"    ";
        gotoxy(enemX[ind],enemY[ind]+3); cout<<"    ";
    }
}

void resetEnemy(int ind)
{
    eraseEnemy(ind);
    enemY[ind]=1;
    genEnemy(ind);
}

void drawCar()
{
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
        //    system("Color E2");
            gotoxy(j+carPos, i+22); cout<<car[i][j];
        }
    }
}

void eraseCar()
{
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            gotoxy(j+carPos, i+22); cout<<" ";
        }
    }
}

int collision()
{
    if(enemY[0]+4 >=23)
    {
        if(enemX[0]+4-carPos>=0 && enemX[0]+4 - carPos<9)
            {
                return 1;
            }
    }
    return 0;
}

void mycompare()
{


    system("cls");
    //system("Color E4");
    //fstream fin;
    //fstream fout;
    int result=0,sizeofile,current;
    fin.open("File.txt",ios::in);
    string atr;
    fin>>atr;
    result=(int)atr[0]-48;
    cout<<"Highest Score is :- "<<atr<<endl;
    cout<<"\nCurrent Score is :- "<<score;
    if(((int)atr[0]-48)<score)
    {
    fin.close();
    fout.open("File.txt",ios::out);////it is use to write the file
    fout << score;
    fout.close();
    }
    else{fin.close();}

    getch();
    system("cls");
}

void gameover()
{

    do{
       system("cls");
       //system("Color E4");
       cout<<endl;
       cout<<"\t\t*******************\n";
       cout<<"\t\t**** GAME OVER ****\n";
       cout<<"\t\t*******************\n";
       mycompare();
       cout<<"\t\tPress escape to exit";
       char ch=getch();

       if(ch==27)
       {

         return;
       }
      }while(1);
}

void updateScore()
{
    gotoxy(WIN_WIDTH+7,5); cout<<"Score: "<<score<<endl;
}

void instructions()
{
    system("cls");
   // system("Color E4");
    cout<<"-: INSTRUCTION :-";
    cout<<"\n1. Avoid Cars by Moving left or Right by using arrow Keys.\n";
    cout<<"\n2. Press 'a' For LEFT.\n";
    cout<<"\n3. Press 'd' For RIGHT.";
    cout<<"\n   Press escape to exit";
    cout<<"\n...Press any key to go back to menu...";
    getch();
}
void Playing()
{
     //do{
     drawCar();
     drawEnemy(0);
     drawEnemy(1);
     if(collision()==1)
     {
         gameover();
         cout<<"\n\t\tThank You For Playing";
         exit(0);
     }

     Sleep(50);// game Speed(Screen speed).
     eraseCar();
     eraseEnemy(0);
     eraseEnemy(1);

     if(enemY[0]==10)
         if(enemyFlag[1]==0)
            enemyFlag[1]=1;

         if(enemyFlag[0]==1)
            enemY[0]+=1;

         if(enemyFlag[1]==1)
            enemY[1]+=1;

         if( enemY[0]>SCREEN_HEIGHT-4)
         {
             resetEnemy(0);
             score++;
             updateScore();
         }
         if( enemY[1]>SCREEN_HEIGHT-4)
         {
             resetEnemy(1);
             score++;
             updateScore();
         }
     //}while(1);
}
void play()
{
    fstream fin;
    fstream fout;
    int result=0,sizeofile,current;
    fin.open("File.txt",ios::in);//it is use to read the file
    string atr;
    fin>>atr;


    carPos= -1+WIN_WIDTH/2;
    score=0;
    enemyFlag[0]=1;
    enemyFlag[1]=0;
    enemY[0]= enemY[1]=1;

    system("cls");
    //system("Color 74");
    drawBorder();
    updateScore();
    genEnemy(0);
    genEnemy(1);

    gotoxy(WIN_WIDTH+7,2);  cout<<"Car Game";
    gotoxy(WIN_WIDTH+6,4);  cout<<"--------";
    gotoxy(WIN_WIDTH+6,6);  cout<<"--------";
    gotoxy(WIN_WIDTH+7,12); cout<<"Control";
    gotoxy(WIN_WIDTH+7,13); cout<<"--------";
    gotoxy(WIN_WIDTH+2,14); cout<<"A -> LEFT";
    gotoxy(WIN_WIDTH+2,15); cout<<"D -> RIGHT";
    gotoxy(WIN_WIDTH+2,20); cout<<" Highest Score ";
    gotoxy(WIN_WIDTH+2,21); cout<<" "<<atr<<" "<<endl;;

    gotoxy(18,5); cout<<"Press any key to start";
    getch();
    gotoxy(18,5); cout<<"                      ";
    while(1)
    {
        gotoxy(WIN_WIDTH+2,16); cout<<"Playing";
            char ch;
            if(kbhit())ch=getch();
            //if(getch()=='a'|| getch()=='A')
            if(ch=='a'|| ch=='A')
            {
                gotoxy(WIN_WIDTH+2,17); cout<<"A press";
                gotoxy(WIN_WIDTH+2,18); cout<<"       ";
                if(carPos>18)//18
                {
                    carPos-=4;
                    Playing();
                }
                else
                {
                    carPos;
                    Playing();
                }
            }
            if(ch=='d'|| ch=='D')//else if(getch()=='d'||getch()=='D')
            {
                gotoxy(WIN_WIDTH+2,17); cout<<"       ";
                gotoxy(WIN_WIDTH+2,18); cout<<"D press";
                if(carPos<50)
                {
                    carPos+=4;
                    Playing(); //goto forwarda;
                }
                 else
                {
                    carPos;
                    Playing();
                }
            }
            else if(ch==27)//else if(getch()==27)
            {
                break;
            }
            else
            {
                carPos;
                Playing();
            }
    }
    fin.close();
}
int main()
{
//HWND wh = GetConsoleWindow(); //Fixed the size of screen
//MoveWindow(console, 100, 30, 150, 50, TRUE); // It is for Fixed the size of screen by using coordinates



    SetCursor(0,0);
    srand((unsigned)time(NULL));
    do
    {
        system("cls");
        system("Color E2");
        gotoxy(5,5); cout<<"------------";
        gotoxy(5,6); cout<<"|| CAR GAME ||";
        gotoxy(5,7); cout<<"------------";
        gotoxy(5,9); cout<<"1. START GAME ";
        gotoxy(5,10); cout<<"2. INSTRUCTION";
        gotoxy(5,11); cout<<"3. QUIT";
        gotoxy(5,13); cout<<"-: Select Option :-";
        char op=getche();

        if(op=='1') play();
        else if(op=='2') instructions();
        else if(op=='3') exit(0);
    }
    while(1);

return 0;
}
