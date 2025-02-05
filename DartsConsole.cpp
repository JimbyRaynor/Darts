// DartsConsole.cpp : This file contains the 'main' function. Program execution begins and ends there.
//



int r; // round number
int t; // choice of type of throw ... 1 , 2 or 3
int b; // score awarded for shot
int s; // total score
long long seed=0, seed1, seed2; // seed for random numbers
double p1, p2, p3, p4; // probability waitings for successful shots
double u; // 0 <= u <= 1,  random number to compare with probability waitings

#include <iostream>
#include <ctime>
#include <chrono>

using namespace std;



int main()
{
    seed = chrono::high_resolution_clock::now().time_since_epoch().count();  // better seed for random numbers since it uses nanoseconds
    srand(seed); // set random seed
    s = 0;  // total score
    cout << "This program was originally written (in BASIC) by \n"
        << "David Ahl of Creative Computing (approx. 1970). \n"
        << "It appears in the book BASIC Computer Games by David Ahl (1978). \n\n"
        << "* BASIC was created by John G. Kemeny and Thomas E. Kurtz at Dartmouth College (1963). \n"
        << "* C was created by Dennis Ritchie at Bell Labs (1972-73). \n"
        << "* C++ was created by Bjarne Stroustrup at Bell Labs (1979-1985).\n"
        << "* Python was created by Guido van Rossum in the Netherlands (1989).\n"
        << "* The oldest high-level language is FORTRAN (1956). "
        << "  It was developed by a team led by John Backus at IBM. \n"
        << "******************************************************* \n\n";

    cout << "Bullseye ... by David Ahl of Creative Computing \n";
    cout << "Throw darts at a target with 10, 20, 30 and 40 point zones \n\n";
    cout << "Throw           Description          Probable Score \n";
    cout << " 1              Fast Overarm         Bullseye or Complete Miss  \n";
    cout << " 2              Controlled Overarm   10, 20, or 30 points \n";
    cout << " 3              Underarm             Anything \n\n\n";
    r = 0;
    while (s < 200)
    {
        r = r + 1;
        cout << "Round " << r << "\n";
        cout << "--------\n";
        cout << "Input your choice of type of throw (1,2,3): ";
        cin >> t;
        switch (t)
        {
        case 1:
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
            p1 = 0.95;
            p2 = 0.75;
            p3 = 0.45;
            p4 = 0.05;
        }
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
