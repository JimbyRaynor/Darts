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
int s; // total score
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

void setgreen()
{
    cout << "\033[1;38;2;0;255;0m";
}


void gotoxy(int x, int y)
{
  cout << "\033["+to_string(y)+";"+to_string(x)+"H";
}

void drawh(int x1,int y1,int x2)
{
    for (int i = x1;i<=x2;i++)
    {
        gotoxy(i,y1);
        cout << "*";
    }
}

void drawv(int x1,int y1,int y2)
{
    for (int i = y1;i<=y2;i++)
    {
        gotoxy(x1,i);
        cout << "*";
    }
}

void drawrect(int x1, int y1, int x2,int y2)
{
    drawh(x1,y1,x2);
    drawh(x1,y2,x2);
    drawv(x1,y1,y2);
    drawv(x2,y1,y2);
}

int main()
{
    char choice;
    clearscreen();
    seed = chrono::high_resolution_clock::now().time_since_epoch().count();  // better seed for random numbers since it uses nanoseconds
    srand(seed); // set random seed
    s = 0;  // total score
    setblue();
    gotoxy(3,2 ); cout << "Bullseye ... by David Ahl of Creative Computing";
    gotoxy(3,3 ); cout << "Throw darts at a target with 10, 20, 30 and 40 point zones";
    gotoxy(3,4 ); cout << "First player to reach 200 points wins";
    gotoxy(3,6 ); cout << "Throw           Description             Probable Score";
    gotoxy(3,8 ); cout << "  1             Fast Overarm            Bullseye or Complete Miss";
    gotoxy(3,9 ); cout << "  2             Controlled Overarm      10, 20, or 30 points";
    gotoxy(3,10); cout << "  3             Underarm                Anything";
    setgreen();
    drawrect(1,1,70,11);
    drawh(1,5,70);
    drawh(1,7,70);
    drawv(11,6,11); 
    drawv(40,6,11);
    r = 0;
    while (s < 200)
    {
        r = r + 1;
        setgreen();
        gotoxy(3,16);cout << "Round " << r;
        gotoxy(3,17);cout << "Input your choice of type of throw (1,2,3):";
        cout << flush; // draw to screen immediately, do not buffer
        choice = rbgetchar();
        setyellow();
        for( int i = 0; i<50;i++)
        {
         gotoxy(3+i,18);cout << " -" << choice << "->";
         cout << flush; // draw to screen immediately, do not buffer
         pause(30);
        }
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
        gotoxy(57,18);
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
        s = s + b;
        cout << "\n\n Total Score = " << s << "\n";
    }
    cout << "You finished on Round " << r << "\n";

}
