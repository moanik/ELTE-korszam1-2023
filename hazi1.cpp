#include <iostream>
#include <cmath>
using namespace std;

// 2 függvény és 1 változó típus
template<typename F1, typename F2, typename T>
T Newton(F1 f1, F2 f2, T x0){
    T x1 = x0;
    // 100 iteráción keresztül futtatni
    for(int i = 0; i < 100; i++){
        //cout << "ELEJE xa: " << x0 << " xb: " << x1 << "\n";
        T xs = x1;
        // következő x kiszámolása
        x1 = x1 - f1(x1) / f2(x1);
        x0 = xs;
        //cout << "VEGE xa: " << x0 << " xb: " << x1 << "\n";
    }
    return x1;
}

// A szorgalmihoz a bool függvény
template<typename T> 
bool felt(T x0, T x1){
    if(fabs(x1-x0) < 0.01){
        return false;
    }
    return true;
}

// szorgalmi függvény 3 átvett függvénnyel
template<typename F1, typename F2, typename F3, typename T>
T Newton_sz(F1 f1, F2 f2, F3 f3, T x0){
    T x1 = x0;
    // Do-While, legalább egszer lefut és az f3 visszatérési értéke dönti el tovább fut-e
    do{
        T xs = x1;
        x1 = x1 - f1(x1) / f2(x1);
        x0 = xs;
        //cout << "xa: " << x0 << " xb: " << x1 << "\n";
    }while(f3(x0, x1));

    return x1;
}

int main(){
    // Teszt a házira
    double a = Newton([](double x){ return x*x-612.0;   },[](double x){ return 2.0*x; }, 10.0);
    // Teszt a szorgalmira
    double b = Newton_sz([](double x){ return x*x-612.0;   },[](double x){ return 2.0*x; }, felt<double>, 10.0);
    cout << "a: " << a << ", b: " << b ;
    return 0;
    }