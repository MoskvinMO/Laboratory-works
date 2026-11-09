#ifndef FRACTION_HPP
#define FRACTION_HPP

/*
    This is regular fraction class "Fraction".
*/

class Fraction { // regular fraction
public:
    void out(); // output

    void reduce(Fraction &frac);
    void reduce(int &a, unsigned &b);
    void reduce(long long &a, unsigned long long &b); // helps in sum, mult, divide

    Fraction(int fNumerator, unsigned fDenominator); // constructor
    Fraction(const Fraction &frac); // copy constructor
    Fraction() = delete; // default constructor will be inaccesable

    void sum(const Fraction &a, const Fraction &b); // a.sum(b, c) makes a be the sum of b and c
    void mult(const Fraction &a, const Fraction &b); // a.mult(b, c) makes a be the product of b and c
    void divide(const Fraction &a, const Fraction &b); // a.divide(b, c) makes a=b/c
    // get-methods:
    int getNumerator();
    int getDenominator();

private:
    int numerator{};
    unsigned denominator{};

    int gcd(int a, int b); // gcd function
    long long gcd(long long a, long long b); // gcd function for long long
};

#endif