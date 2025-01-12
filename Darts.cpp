// DartsConsole.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

// Add 3 AI players: first one to 200 wins 

#include <iostream>
#include <ctime>
#include <chrono> // need for time (and so random) function

using namespace std;

int r; // round number
int t; // choice of type of throw ... 1 , 2 or 3
int b; // score awarded for shot
int s; // total score
long long seed=0, seed1, seed2; // seed for random numbers
double p1, p2, p3, p4; // probability waitings for successful shots
double u; // 0 <= u <= 1,  random number to compare with probability waitings

void clearscreen()
{
 cout << "\033[2J";  
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
    clearscreen();
    drawrect(1,1,70,11);
    seed = chrono::high_resolution_clock::now().time_since_epoch().count();  // better seed for random numbers since it uses nanoseconds
    srand(seed); // set random seed
    s = 0;  // total score
    gotoxy(3,2 ); cout << "Bullseye ... by David Ahl of Creative Computing";
    gotoxy(3,3 ); cout << "Throw darts at a target with 10, 20, 30 and 40 point zones";
    gotoxy(3,4 ); cout << "First player to reach 200 points wins";
    drawh(1,5,70);
    gotoxy(3,6 ); cout << "Throw           Description             Probable Score";
    drawh(1,7,70);
    gotoxy(3,8 ); cout << "  1             Fast Overarm            Bullseye or Complete Miss";
    gotoxy(3,9 ); cout << "  2             Controlled Overarm      10, 20, or 30 points";
    gotoxy(3,10); cout << "  3             Underarm                Anything";
    drawv(11,6,11); drawv(40,6,11);
    r = 0;
    while (s < 200)
    {
        r = r + 1;
        gotoxy(3,16);cout << "Round " << r;
        gotoxy(3,17);cout << "Input your choice of type of throw (1,2,3) followed by <Enter>: ";
        cin >> t;
        switch (t)
        {
        case 1:
            gotoxy(3,18);cout << "Fast Overarm";
            p1 = 0.65;
            p2 = 0.55;
            p3 = 0.5;
            p4 = 0.5;
            break;
        case 2:
            p1 = 0.99;
            p2 = 0.77;
            p3 = 0.43;
            p4 = 0.01;
            break;
        default:
            gotoxy(3,18);cout << "default";
            p1 = 0.95;
            p2 = 0.75;
            p3 = 0.45;
            p4 = 0.05;
        }
        gotoxy(3,22);
        u = 1.0 * rand() / RAND_MAX;
        if (u >= p1)
        {
            cout << "Bullseye!! 40 points!";
            b = 40;
        }
        else if (u >= p2)
        {
            cout << "30 points!";
            b = 30;
        }
        else if (u >= p3)
        {
            cout << "20 points!";
            b = 20;
        }
        else if (u >= p4)
        {
            cout << "10 points!";
            b = 10;
        }
        else
        {
            cout << "Whoops! You missed the target!";
            b = 0;
        }
        s = s + b;
        cout << "\n\n Total Score = " << s << "\n";
    }
    cout << "You finished on Round " << r << "\n";

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
