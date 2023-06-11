#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

// ----------------------------------------------------------
// Legnagyobb közös osztó számítás megvalósítása
// ----------------------------------------------------------
int lnko(int szamlalo, int nevezo){

    int result = std::min(szamlalo, nevezo);
    while (result > 0) {
        if (szamlalo % result == 0 && nevezo % result == 0) {
            break;
        }
        result--;
    }

    return result;
}

// ----------------------------------------------------------
// Legkisebb közös többszörös számítás megvalósítása
// ----------------------------------------------------------
int lkkt(int nevezo_1, int nevezo_2){

    return (nevezo_1 / lnko(nevezo_1, nevezo_2)) * nevezo_2;

}

// ----------------------------------------------------------
// Racionális szám osztály megvalósítása
// ----------------------------------------------------------
class Rational{


    public:
        int szamlalo, nevezo;
        Rational() = default;
        Rational( Rational const& ) = default;
        Rational( Rational && ) = default;
        // Számláló és nevező megadása
        Rational( int a, int b ) { 
            int l = lnko(a, b);

            szamlalo = (int)(a / l);
            nevezo = (int)(b / l);
        };
        // Integer konvertálása
        Rational( int szam ) { szamlalo = szam; nevezo = 1;};


    Rational& norm(){

        int l = lnko(szamlalo, nevezo);

        szamlalo = (int)(szamlalo / l);
        nevezo = (int)(nevezo / l);

        return *this;
    }

    // ----------------------------------------------------------
    // Összeadás megvalósítása
    // ----------------------------------------------------------
    // Racionális + Racionális
    Rational& operator+=( Rational const& r )
    {

        int l = lkkt(nevezo, r.nevezo);

        szamlalo = szamlalo * (l / nevezo) + r.szamlalo * (l / r.nevezo);
        nevezo = l;
        return norm();
    }
    // Racionális + Egész
    Rational& operator+=( int const& b )
    {

        Rational r = Rational( b );

        int l = lkkt(nevezo, r.nevezo);

        szamlalo = szamlalo * (l / nevezo) + r.szamlalo * (l / r.nevezo);
        nevezo = l;
        return norm();
    }

    // ----------------------------------------------------------
    // Kivonás megvalósítása
    // ----------------------------------------------------------
    // Racionális - Racionális
    Rational& operator-=( Rational const& r )
    {

        int l = lkkt(nevezo, r.nevezo);

        szamlalo = szamlalo * (l / nevezo) - r.szamlalo * (l / r.nevezo);
        nevezo = l;
        return norm();
    }
    // Racionális - Egész
    Rational& operator-=( int const& b )
    {

        Rational r = Rational( b );

        int l = lkkt(nevezo, r.nevezo);

        szamlalo = szamlalo * (l / nevezo) - r.szamlalo * (l / r.nevezo);
        nevezo = l;
        return norm();
    }

    // ----------------------------------------------------------
    // Szorzás megvalósítása
    // ----------------------------------------------------------
    // Racionális * Racionális
    Rational& operator*=( Rational const& b)
    {
        szamlalo = szamlalo * b.szamlalo;
        nevezo = nevezo * b.nevezo;

        return norm();

    }
    // Racionális * Egész
    Rational& operator*=( int const& c)
    {
        szamlalo = szamlalo * c;

        return norm();

    }

    // ----------------------------------------------------------
    // Osztás megvalósítása
    // ----------------------------------------------------------
    // Racionális / Racionális
    Rational& operator/=( Rational const& b)
    {
        szamlalo = szamlalo * b.nevezo;
        nevezo = nevezo * b.szamlalo;

        return norm();

    }
    // Racionális / Egész
    Rational& operator/=( int const& c)
    {
        nevezo = nevezo * c;

        return norm();

    }

};

// ----------------------------------------------------------
// Összeadás megvalósítása
// ----------------------------------------------------------
// Racionális + Racionális
Rational operator+( Rational const& a, Rational const& b)
{
    int l = lkkt(a.nevezo, b.nevezo);

    return Rational(a.szamlalo * (l / a.nevezo) + b.szamlalo * (l / b.nevezo) , l);


}
// Racionális + Egész
Rational operator+( Rational const& a, int const& c)
{
    Rational b = Rational(c);

    int l = lkkt(a.nevezo, b.nevezo);

    return Rational(a.szamlalo * (l / a.nevezo) + b.szamlalo * (l / b.nevezo) , l);


}
// Egész + Racionális
Rational operator+( int const& c, Rational const& a)
{
    Rational b = Rational(c);

    int l = lkkt(a.nevezo, b.nevezo);

    return Rational(a.szamlalo * (l / a.nevezo) + b.szamlalo * (l / b.nevezo) , l);


}

// ----------------------------------------------------------
// Kivonás megvalósítása
// ----------------------------------------------------------
// Racionális - Racionális
Rational operator-( Rational const& a, Rational const& b)
{
    int l = lkkt(a.nevezo, b.nevezo);

    return Rational(a.szamlalo * (l / a.nevezo) - b.szamlalo * (l / b.nevezo) , l);

}
// Racionális - Egész
Rational operator-( Rational const& a, int const& c )
{
    Rational b = Rational(c);

    int l = lkkt(a.nevezo, b.nevezo);

    return Rational(a.szamlalo * (l / a.nevezo) - b.szamlalo * (l / b.nevezo) , l);

}
// Egész - Racionális
Rational operator-( int const& c, Rational const& a )
{
    Rational b = Rational(c);

    int l = lkkt(a.nevezo, b.nevezo);

    return Rational(a.szamlalo * (l / a.nevezo) - b.szamlalo * (l / b.nevezo) , l);

}

// ----------------------------------------------------------
// Szorzás megvalósítása
// ----------------------------------------------------------
// Racionális * Racionális
Rational operator*( Rational const& a, Rational const& b)
{

    return Rational(a.szamlalo * b.szamlalo , a.nevezo * b.nevezo);

}
// Racionális * Egész
Rational operator*( Rational const& a, int const& c)
{
    Rational b = Rational(c);

    return a * b;

}
// Egész * Racionális
Rational operator*(int const& c, Rational const& a)
{
    Rational b = Rational(c);

    return a * b;

}

// ----------------------------------------------------------
// Osztás megvalósítása
// ----------------------------------------------------------
// Racionális / Racionális
Rational operator/( Rational const& a, Rational const& b)
{

    return Rational(a.szamlalo * b.nevezo , a.nevezo * b.szamlalo);

}
// Racionális / Egész
Rational operator/( Rational const& a, int const& c)
{
    Rational b = Rational(c);

    return a / b;

}
// Egész / Racionális
Rational operator/(int const& c, Rational const& a)
{
    Rational b = Rational(c);

    return b / a;

}

// ----------------------------------------------------------
// Hatványozás megvalósítása
// ----------------------------------------------------------
Rational pow(Rational const& a, int const& b)
{

    return Rational((int)pow(a.szamlalo, b), (int)pow(a.nevezo, b));

}

// ----------------------------------------------------------
// Gyökvonás megvalósítása
// ----------------------------------------------------------
template<typename F1, typename F2, typename T>
int Newton(F1 f1, F2 f2, T x0){
    T x1 = x0;

    // 100 iteráción keresztül futtatni
    for(int i = 0; i < 10000; i++){
        T xs = x1;
        x1 = x1 - f1(x1) / f2(x1);
        x0 = xs;
    }
    return (int)x1;
}
Rational sqrt(Rational const& a)
{
    
    return Rational(
    Newton([a](double x){ return x*x - (double)a.szamlalo;   },[](double x){ return 2.0*x; }, 2.0), 
    Newton([a](double x){ return x*x - (double)a.nevezo;   },[](double x){ return 2.0*x; }, 2.0)
    );

}

// ----------------------------------------------------------
// Kiírás megvalósítása
// ----------------------------------------------------------
std::ostream& operator<<( std::ostream& o, Rational const& r )
{
    o << "" << r.szamlalo << " / " << r.nevezo;
    return o;
}

// ----------------------------------------------------------
// Beolvasás megvalósítása
// ----------------------------------------------------------
std::istream& operator>>( std::istream& i, Rational& r)
{
    i >> r.szamlalo;
    i >> r.nevezo;
    return i;
}