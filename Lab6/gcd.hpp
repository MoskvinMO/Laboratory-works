#ifndef GCD_HPP
#define GCD_HPP

/*
    There is a function for finding the greatest common divisor of 2 given integers.
    It is useful in Fraction class.
*/

#include <iostream>

int gcd(int a, int b) { // gcd function
    if(a > b) std::swap(a, b);
    if(!a) return (b ? b : 1); // if(a==0) return 1 if b==0 and return b if b!=0
    while(a) {
        b %= a;
        std::swap(a, b);
    }
    return abs(b);
}

long long gcd(long long a, long long b) { // gcd function for long long
    if(a > b) std::swap(a, b);
    if(!a) return (b ? b : 1);
    while(a) {
        b %= a;
        std::swap(a, b);
    }
    return abs(b);
}

#endif