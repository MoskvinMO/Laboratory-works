#include <iostream>
#include <iomanip>

using namespace std;

void TestExpx();

int main() {
    cout << '\n';
    long double x;
    cout << "Write x: ";
    cin >> x;
    int k;
    cout << "Write k: ";
    cin >> k;
    long double c = 1, epsilon = 1, expx = 0;
    // c is a term of the series which we sum;
    // expx is e^x which we compute
    long long m = 1;
    // m is used for computing c;
    for(int i = 0; i < k; i++) epsilon /= 10;
    // epsilon == 10^{-k}
    while(max(c, -c) > epsilon) {
        expx += c;
        c *= x; c /= m; m++;
        // c == (x^m)/(m!)
    }
    cout << setprecision(k+1);
/*  We don't make given number of digits after decimal point/comma because 
    for big x we will not see a fraction part of expx         */
    cout << "\ne^x = " << expx << "; (approximately)\n\n";
    cout << setprecision(32);
    // 32 is a precision of error |expx - e^x|
    cout << "It is different from standart exp with error of: " << max(expx - exp(x), exp(x) - expx) << ".\n\n";
    cout << "This is about " << 100 * max(expx - exp(x), exp(x) - expx) / exp(x) << "% of standart e^x.\n\n";
    return 0;
}

void TestExpx() {
/*
    This function used for testing if we compute e^x correctly.
    It computes a lot of values of expx and compare with standart e^x.
    Finally, it output a maximal relative error when x is in given interval and a corresponding x.
    Here -7 <= x < 100, x is with step 0.0001; and k = 10.
*/
    int k = 10;
    long double d = -1, mx = NAN;
    // d is maximal relative error;
    // mx is a value of x in which relative error is maximal
    cout << setprecision(100);
    for(long double x=-7; x<100; x += 0.0001) {
        long double c = 1, epsilon = 1, expx = 0;
        long long m = 1;
        for(int i = 0; i < k; i++) epsilon /= 10;
        while(max(c, -c) > epsilon) {
            expx += c;
            c *= x; c /= m; m++;
        }
        if(d<max(expx - exp(x), exp(x) - expx) / exp(x)) {
            d = max(expx - exp(x), exp(x) - expx) / exp(x);
            mx = x;
        };
    }
    cout << d << ' ' << mx;
    return;
}