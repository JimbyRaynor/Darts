// DartsConsole.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

// Add 3 AI players: first one to 200 wins 

#include <iostream>
#include <ctime>
#include <chrono> // need for time (and so random) function
#include <thread> // for pausing
#include <unistd.h>  // need for getch()
#include <termios.h>  // need for getch()

using namespace std;

int r; // round number
int b; // score awarded for shot
int s = 0; // total human player score
int s1 = 0; // total computer 1 score
int s2 = 0; // total computer 2 score
int s3 = 0; // total computer 3 score

long long seed=0, seed1, seed2; // seed for random numbers
double p1, p2, p3, p4; // probability waitings for successful shots
double u; // 0 <= u <= 1,  random number to compare with probability waitings

// this linux function will read a character from the keyboard (<Enter> not required)
char rbgetchar() {    // watch out for offical getchar() function, it requires  <Enter> !!!
    char buf = 0;
    struct termios old = {0};
    if (tcgetattr(0, &old) < 0) {
        perror("tcgetattr");
    }
    old.c_lflag &= ~ICANON;
    old.c_lflag &= ~ECHO;
    old.c_cc[VMIN] = 1;
    old.c_cc[VTIME] = 0;
    if (tcsetattr(0, TCSANOW, &old) < 0) {
        perror("tcsetattr");
    }
    if (read(0, &buf, 1) < 0) {
        perror("read");
    }
    old.c_lflag |= ICANON;
    old.c_lflag |= ECHO;
    if (tcsetattr(0, TCSADRAIN, &old) < 0) {
        perror("tcsetattr");
    }
    return buf;
}


void pause(int t)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(t));
}

void resetmode()
{
   cout << "\033[0m"; 
}

void clearscreen()
{
 cout << "\033[2J";  
}

void setblue()
{
    cout << "\033[1;38;2;80;80;255m";
}

void setred()
{
    cout << "\033[1;38;2;255;0;0m";
}

void setyellow()
{
    cout << "\033[1;38;2;255;255;0m";
}

void setblack()
{
    cout << "\033[1;38;2;0;0;0m";
}

void setgreen()
{
    cout << "\033[1;38;2;0;255;0m";
}


void setwhite()
{
    cout << "\033[1;38;2;0;0;0m";
}

void setbackyellow()
{
    cout << "\033[1;48;2;255;255;0m";
}

void setbackgreen()
{
    cout << "\033[1;48;2;0;200;0m";
}

void setbackred()
{
    cout << "\033[1;48;2;255;0;0m";
}

void setbackblue()
{
    cout << "\033[1;48;2;0;0;255m";
}

void setbackgrey()
{
    cout << "\033[1;48;2;100;100;100m";
}

void setyellowongreen()
{   
    setbackgreen();
    setyellow();
}

void setblueonyellow()
{
    setbackyellow();
    setblue();
}

void setblackonred()
{
    setbackred();
    setblack();
}

void setyellowonblue()
{
    setyellow();
    setbackblue();   
}

void setwhiteongrey()
{
    setwhite();
    setbackgrey();   
}

void gotoxy(int x, int y)
{
  cout << "\033["+to_string(y)+";"+to_string(x)+"H";
}

void drawh(int x1,int y1,int x2)
{
    setbackyellow();
    for (int i = x1;i<=x2;i++)
    {
        gotoxy(i,y1);
        cout << " ";
    }
    resetmode();
}

void drawv(int x1,int y1,int y2)
{
    setbackyellow();
    for (int i = y1;i<=y2;i++)
    {
        gotoxy(x1,i);
        cout << " ";
    }
    resetmode();
}

void drawrect(int x1, int y1, int x2,int y2)
{
    
    drawh(x1,y1,x2);
    drawh(x1,y2,x2);
    drawv(x1,y1,y2);
    drawv(x2,y1,y2);

}

int calcprobs(char choice, int playernum)
{
int b = 0;
switch (choice)
        {
        case '1':
            p1 = 0.65;
            p2 = 0.64;
            p3 = 0.63;
            p4 = 0.62;
            break;
        case '2':
            p1 = 0.99;
            p2 = 0.77;
            p3 = 0.43;
            p4 = 0.01;
            break;
        default:
            p1 = 0.95;
            p2 = 0.75;
            p3 = 0.45;
            p4 = 0.05;
        }
        u = 1.0 * rand() / RAND_MAX;
        //gotoxy(57,17+playernum);
        setred();
        if (u >= p1)
        {
            cout << "**Bullseye - 40 points**";
            b = 40;
        }
        else if (u >= p2)
        {
            cout << "**30 points**           ";
            b = 30;
        }
        else if (u >= p3)
        {
            cout << "**20 points**           ";
            b = 20;
        }
        else if (u >= p4)
        {
            cout << "**10 points**           ";
            b = 10;
        }
        else
        {
            cout << "**Miss**                ";
            b = 0;
        }
    cout << flush;
    return b;
}

void shoot(char choice, int playernum)
{
        setyellow();
        for( int i = 0; i<19;i++)
        {
         gotoxy(3+i,10+playernum);
         cout << " -" << choice << "->";
         cout << flush; // draw to screen immediately, do not buffer
         pause(30);
        }
}

int main()
{
    char choice;
    clearscreen();
    seed = chrono::high_resolution_clock::now().time_since_epoch().count();  // better seed for random numbers since it uses nanoseconds
    srand(seed); // set random seed
    setblueonyellow();
    gotoxy(3,2 ); cout << "Bullseye ... by David Ahl of Creative Computing                  ";
    gotoxy(3,3 ); cout << "Throw darts at a target with 10, 20, 30 and 40 point zones       ";
    gotoxy(3,4 ); cout << "First player to reach 200 points wins                            ";
    setyellowongreen();
    gotoxy(3,5 ); cout << "Throw           Description             Probable Score           ";
    gotoxy(3,6 ); cout << "  1             Fast Overarm            Bullseye or Complete Miss";
    gotoxy(3,7 ); cout << "  2             Controlled Overarm      10, 20, or 30 points     ";
    gotoxy(3,8 ); cout << "  3             Underarm                Anything                 ";
    setgreen();
    setwhiteongrey();
    gotoxy(50,11); cout << "Human:           ";
    gotoxy(50,12); cout << "Computer 1:      ";
    gotoxy(50,13); cout << "Computer 2:      ";
    gotoxy(50,14); cout << "Computer 3:      ";
    r = 0;
    while ( (s < 200) && (s1 < 200) && (s2 < 200) && (s3 < 200) )
    {
        r = r + 1;  
        setyellowonblue();
        gotoxy(3,10);cout << "Round "<< r << ". ";cout << "Input type of throw (1,2,3):";
        resetmode();
        setblackonred();
        cout << flush; // draw to screen immediately, do not buffer
        choice = rbgetchar();
        shoot(choice,1);
        b = calcprobs(choice,1);
        s = s + b;
        gotoxy(63,11); cout << s;         pause(1000);
        shoot('1',2);
        b = calcprobs('1',2);
        s1 = s1 + b;
        gotoxy(63,12); cout << s1;         pause(1000);
        shoot('2',3);
        b = calcprobs('2',3);
        s2 = s2 + b;
        gotoxy(63,13); cout << s2;         pause(1000);
        shoot('3',4);
        b = calcprobs('3',4);
        s3 = s3 + b;
        gotoxy(63,14); cout << s3;         pause(1000);
        resetmode();
    }
    if (s >= 200)
    {
       cout << "\nHuman player wins \n"; 
    }
    if (s1 >= 200)
    {
       cout << "\nComputer 1 wins \n"; 
    }
    if (s2 >= 200)
    {
       cout << "\nComputer 2 wins \n"; 
    }
    if (s3 >= 200)
    {
       cout << "\nComputer 3 wins \n"; 
    }
    cout << "\nFinished on Round " << r << "\n";

}
