#include <iostream>
#include"vector.h"
using namespace std;

int main(){
    Vector<double> v1 = {2.0, 3.0};
    Vector<double> v2 = {3.0, 2.0};
    cout << "Base: " << v1 << endl;
    cout << "Plus: " << v1 + v2 << endl;
    v1 += v2;
    cout << "Plus: " << v1 << endl;
    cout << "Minus: " << v1 - v2 << endl;
    v1 -= v2;
    cout << "Minus: " << v1 << endl;
    cout << "Multiply: " << v1 * 2.0 << endl;
    cout << "Multiply: " << 2.0 * v1 << endl;
    v1 *= 2.0;
    cout << "Multiply: " << v1 << endl;
    cout << "Divide: " << v1 / 2.0 << endl;
    v1 /= 2.0;
    cout << "Divide: " << v1 << endl;

    cout << "Dot: " << dot(v1, v2) << endl;
    cout << "Length: " << length(v1) << endl;
    cout << "SQlength: " << sqlength(v1) << endl;
    cout << "Norm: " << normalize(v1) << endl;
    return 0;
}