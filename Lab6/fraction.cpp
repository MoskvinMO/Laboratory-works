#include <iostream>
#include "fraction.h"

/*
    "Fraction" class.
    Realisation of mathods.
*/

void Fraction::out() { // output
    if(denominator == 0) {
        if(numerator == 0) {std::cout << "NaN"; return;} // 0/0 is NaN
        std::cout << (numerator > 0 ? "+inf" : "-inf"); // +inf or -inf depends on sign of the numerator
        return;
    }
    std::cout << numerator << '/' << denominator;
}
void Fraction::reduce(Fraction &frac) {
    int nod = gcd(frac.numerator, frac.denominator);
    frac.numerator /= nod;
    frac.denominator /= nod;
}
void Fraction::reduce(int &a, unsigned &b) {
    int nod = gcd(a, b);
    a /= nod;
    b /= nod;
}
void Fraction::reduce(long long &a, unsigned long long &b) { // helps in sum, mult, divide
    long long nod = gcd(a, (long long)b);
    a /= nod;
    b /= nod;
}

Fraction::Fraction(int fNumerator, unsigned fDenominator) { // constructor
    numerator = fNumerator;
    denominator = fDenominator;
    reduce(numerator, denominator);
}
Fraction::Fraction(const Fraction &frac) { // copy constructor
    numerator = frac.numerator;
    denominator = frac.denominator;
    reduce(numerator, denominator);
}

void Fraction::sum(const Fraction &a, const Fraction &b) { // a.sum(b, c) makes a be the sum of b and c
    /*
    We convert numerators and denominators into long long (preNumerator, preDenominator), reduce them and go back.
    This is done because int expressions are likely to be overflowed.
    numerator = a.numerator * b.denominator + b.numerator * a.denominator;
    denominator = a.denominator * b.denominator;
    */
    long long preNumerator = (long long)(a.numerator) * b.denominator + (long long)(b.numerator) * a.denominator;
    unsigned long long preDenominator = (unsigned long long)(a.denominator) * b.denominator;
    reduce(preNumerator, preDenominator);
    numerator = preNumerator;
    denominator = preDenominator;
}
void Fraction::mult(const Fraction &a, const Fraction &b) { // a.mult(b, c) makes a be the product of b and c
    // protect from overflowing
    // numerator = a.numerator * b.numerator;
    // denominator = a.denominator * b.denominator;
    long long preNumerator = (long long)(a.numerator) * b.numerator;
    unsigned long long preDenominator = (unsigned long long)(a.denominator) * b.denominator;
    reduce(preNumerator, preDenominator);
    numerator = preNumerator;
    denominator = preDenominator;
}
void Fraction::divide(const Fraction &a, const Fraction &b) { // a.divide(b, c) makes a=b/c
    // protect from overflowing
    // numerator = a.numerator * b.denominator;
    // denominator = a.denominator * b.numerator;
    long long preNumerator = (long long)(a.numerator) * b.denominator * (2 * (b.numerator >= 0) - 1);
    unsigned long long preDenominator = (unsigned long long)(a.denominator) * abs(b.numerator);
    reduce(preNumerator, preDenominator);
    numerator = preNumerator;
    denominator = preDenominator;
    reduce(numerator, denominator);
}

// get-methods:
int Fraction::getNumerator() {
    return numerator;
}
int Fraction::getDenominator() {
    return denominator;
}

// gcd functions:
int Fraction::gcd(int a, int b) { // default gcd function
    if(a > b) std::swap(a, b);
    if(!a) return (b ? b : 1); // if(a==0) return 1 if b==0 and return b if b!=0
    while(a) {
        b %= a;
        std::swap(a, b);
    }
    return abs(b);
}
long long Fraction::gcd(long long a, long long b) { // gcd function for long long
    if(a > b) std::swap(a, b);
    if(!a) return (b ? b : 1);
    while(a) {
        b %= a;
        std::swap(a, b);
    }
    return abs(b);
}