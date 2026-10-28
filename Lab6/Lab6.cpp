#include <iostream>

int gcd(int, int);

class Fraction { // regular fraction
public:
    int numerator{};
    unsigned denominator{};
    void out() { // output
        if(denominator == 0) {
            if(numerator == 0) {std::cout << "NaN"; return;} // 0/0 is NaN
            std::cout << (numerator > 0 ? "+inf" : "-inf"); // +inf or -inf depends on sign of the numerator
            return;
        }
        std::cout << numerator << '/' << denominator;
    }
    void reduce(Fraction &frac) {
        int nod = gcd(frac.numerator, frac.denominator);
        frac.numerator /= nod;
        frac.denominator /= nod;
    }
    void reduce(int &a, unsigned &b) {
        int nod = gcd(a, b);
        a /= nod;
        b /= nod;
    }
    Fraction(int fNumerator, unsigned fDenominator) { // constructor
        numerator = fNumerator;
        denominator = fDenominator;
        reduce(numerator, denominator);
    }
    Fraction(const Fraction &frac){ // copy constructor
        numerator=frac.numerator;
        denominator=frac.denominator;
        reduce(numerator, denominator);
    }
    Fraction() = delete; // default constructor will be inaccesable
    void sum(const Fraction &a, const Fraction &b) { // a.sum(b, c) makes a be the sum of b and c
        // May be we should make 2 long long entities for numerator and denominator to have less often overflow?
        denominator = a.denominator * b.denominator;
        numerator = a.numerator*b.denominator+b.numerator*a.denominator;
        reduce(numerator, denominator);
    }
    void mult(const Fraction &a, const Fraction &b) { // a.mult(b, c) makes a be the product of b and c
        denominator = a.denominator * b.denominator;
        numerator = a.numerator*b.numerator;
        reduce(numerator, denominator);
    }
    void divide(const Fraction &a, const Fraction &b) { // a.divede(b, c) makes a=b/c
        denominator = a.denominator * b.numerator;
        numerator = a.numerator*b.denominator;
        reduce(numerator, denominator);
    }
};

int main()
{
    
    return 0;
}

int gcd(int a, int b) { // gcd function
    if(a>b) std::swap(a, b);
    if(!a) return (b ? b : 1); // if(a==0) return 1 if b==0 and return b if b!=0
    while(a){
        b %= a;
        std::swap(a, b);
    }
    return abs(b);
}