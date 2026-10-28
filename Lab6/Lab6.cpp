#include <iostream>

int gcd(int, int);
long long gcd(long long, long long);

class Fraction { // regular fraction
private:
    int numerator{};
    unsigned denominator{};
public:
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
    void reduce(long long &a, unsigned long long &b) { // helps in sum, mult, divide
        long long nod = gcd(a, (long long)b);
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
    void mult(const Fraction &a, const Fraction &b) { // a.mult(b, c) makes a be the product of b and c
        // protect from overflowing
        // numerator = a.numerator * b.numerator;
        // denominator = a.denominator * b.denominator;
        long long preNumerator = (long long)(a.numerator) * b.numerator;
        unsigned long long preDenominator = (unsigned long long)(a.denominator) * b.denominator;
        reduce(preNumerator, preDenominator);
        numerator = preNumerator;
        denominator = preDenominator;
    }
    void divide(const Fraction &a, const Fraction &b) { // a.divede(b, c) makes a=b/c
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
    int getNumerator(){
        return numerator;
    }
    int getDenominator(){
        return denominator;
    }
};

int main()
{
    std::cout << "\nLet's see some fractions.\nPlease, write the first numerator: ";
    int firstNumerator;
    std::cin >> firstNumerator;
    std::cout << "Please, write the first denominator: ";
    int firstDenominator;
    std::cin >> firstDenominator;
    std::cout << "Please, write the second numerator: ";
    int secondNumerator;
    std::cin >> secondNumerator;
    std::cout << "Please, write the second denominator: ";
    int secondDenominator;
    std::cin >> secondDenominator;
    Fraction frac1(firstNumerator, firstDenominator);
    Fraction frac2(secondNumerator, secondDenominator);
    std::cout << "You have written 2 fractions.\nThe first one:  "; frac1.out();
    std::cout << ";\nthe second one: "; frac2.out();
    std::cout << ".\nNumerator of the first is " << frac1.getNumerator() << ";\nnumerator of the second is " << frac2.getNumerator() <<
    ";\ndenomenator of the first is " << frac1.getDenominator() << ";\ndenomenator of the second is " << frac2.getDenominator();
    Fraction helpFrac(1, 1);
    helpFrac.sum(frac1, frac2);
    std::cout << ".\nTheir sum is ";
    helpFrac.out();
    helpFrac.mult(frac1, frac2);
    std::cout << ";\ntheir product is ";
    helpFrac.out();
    helpFrac.divide(frac1, frac2);
    std::cout << ";\nthe result of division of the first by the second is ";
    helpFrac.out();
    helpFrac.divide(frac2, frac1);
    std::cout << ";\nthe result of division of the second by the first is ";
    helpFrac.out();
    std::cout << ".\n\n";
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
long long gcd(long long a, long long b) { // gcd function for long long
    if(a>b) std::swap(a, b);
    if(!a) return (b ? b : 1);
    while(a){
        b %= a;
        std::swap(a, b);
    }
    return abs(b);
}