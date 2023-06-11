#include <iostream>
#include"Rational.h"
using namespace std;

int main(){
    Rational r1 = {4, 9};
    Rational r2 = {3, 2};

    cout << "r1 is " << r1 << endl;
    cout << "r2 is " << r2 << endl;
    cout << r1 << " Plus " << r2 << " is: " << r1 + r2 << endl;
    r1 += r2;
    cout << "r1 Plus r2 is: " << r1 << endl;
    cout << r1 << " Minus " << r2 << " is: " << r1 - r2 << endl;
    r1 -= r2;
    cout << "r1 Minus r2 is: " << r1 << endl;
    cout << r1 << " Times 2: " << r1 * 2 << endl;
    cout << r1 << " Times 2: " << 2 * r1 << endl;
    cout << r1 << " Times " << r2 << " is: " << r1 * r2 << endl;
    r1 *= 2.0;
    cout << "r1 Multiplied by 2: " << r1 << endl;
    cout << r1  << " Divided by 2: " << r1 / 2 << endl;
    r1 /= 2;
    cout << "r1 divided by 2: " << r1 << endl;
    cout << r1 << " Divided " << r2 << " is: " << r1 / r2 << endl;

    cout << r1 << " Squared is: " << pow(r1, 2) << endl;
    cout << "Sqrt of " << r1 << " is " << sqrt(r1) << endl;

    Rational r3 = std::move(r1);

    cout << "r3 is " << r3 << endl;
    return 0;

}