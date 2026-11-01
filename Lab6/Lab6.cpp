#include <iostream>
#include "fraction.hpp"

int main()
{
    // input:
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

    Fraction frac1(firstNumerator * (firstDenominator < 0 ? -1 : 1), abs(firstDenominator));    // we avoid a situation when denominator is negative
    Fraction frac2(secondNumerator * (secondDenominator < 0 ? -1 : 1), abs(secondDenominator)); // we avoid a situation when denominator is negative

    // Showing our methods:
    // output of fractions:
    std::cout << "You have written 2 fractions.\nThe first one:  "; frac1.out();
    std::cout << ";\nthe second one: "; frac2.out();
    // output of numerators and denominators:
    std::cout << ".\nNumerator of the first is " << frac1.getNumerator() << ";\nnumerator of the second is " << frac2.getNumerator() <<
    ";\ndenomenator of the first is " << frac1.getDenominator() << ";\ndenomenator of the second is " << frac2.getDenominator();
    // output of sum, product and division with given fractions:
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