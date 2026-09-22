#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

int main() {
    ios::sync_with_stdio(0); // faster input/output; helpful for big n

    constexpr long long MaxSize = 1048576;
    int* arr = new int[MaxSize];
    int n{};
    cout << "\nPlease, write n: ";
    cin >> n;

    while(n < 1 || n > MaxSize) {
        cout << "Incorrect Input. Try again or write the same n if you are ready: ";
        int k{};
        cin >> k;
        if(k == n) break;
        n = k;
        if(k > 0 && k <= MaxSize) break;
    }

    cout << "Do you want to use keyboard or random numbers? Write 1 for keyboard, 0 for random numbers.\n"
    << "There can be an error if you will choose neither 1 nor 0.\n";
    bool b{};
    cin >> b;
    if(b) {
        // Array input is from the keyboard.
        for(int i = 0; i < n; ++i) {
            cout << "Element number " << i + 1 << " is: ";
            cin >> i[arr];
        }
    }
    else {
        // Array of pseudo-random numbers.
        int Start, End;
        cout << "Write minimal possible and maximal possible pseudo-random values: ";
        cin >> Start >> End;
        if(Start > End) swap(Start, End);
        // making more random
        srand(time(0));
        rand(); rand(); rand();
        for(int i = 0; i < n; ++i) arr[i]=Start + (rand() + rand() * RAND_MAX) % (End - Start + 1);
        /*
        If End - Start is too large this might not work correctly.
        That may happen when End - Start > 1e9.
        Also, distribution is not uniform.
        */
        cout << "\nYour array is:\n";
        for(int i = 0; i < n - 1; ++i) cout << arr[i] << ' ';
        cout << arr[n - 1] << '\n';
    }

    long long Product = 1;
    // We assume that numeration of indexes starts from 1.
    for(int i = 1; i < n; i += 2) {
        Product *= *(arr + i);
    }
    // In case n == 1 there are not any even index; we write about this when n == 1.
    cout << "\nProduct of elements with even indexes is: " << Product 
    << (n - 1 ? ".\n" : "   (even indexes don't exist).\n");

    long long Sum{};
    int i1{}, i2{}, ArrElement{};
    bool IsZeroWas = 0;
    for(int i = 0; i < n; ++i) {
        ArrElement = arr[i];
        if(!ArrElement && !IsZeroWas) {i1 = i; IsZeroWas = 1;}
        if(!ArrElement) i2 = i;
    }
    for(int i = i1; i < i2; ++i) {Sum += arr[i];}
    cout << "Sum of elements between the first and the last zeroes is: " << Sum << ".\n";

    bool IsFinished = 0;
    while(!IsFinished) {
    /*
        Modifying the array.
        While it is not ordered as we want, move negative numbers to the start.
        When moving, we scan all array, and if we see positive and then negative integers, we swap them.
    */
        for(int i = 0; i < n - 1; ++i) {
            if(arr[i + 1] < 0 && arr[i] >= 0) {
                // swap arr[i] and arr[i+1]
                arr[i] ^= arr[i + 1];
                arr[i + 1] ^= arr[i];
                arr[i] ^= arr[i + 1];
            }
        }
        /*
            Checking if the array is ordered as we want.
            We scan the array from the start. We want to have all negative elements and then all non-negative.
            So, when scanning, if we get a non-negative number, we remember this (IsSmth variable);
            and then, if we find a negative number, we haven't finished yet.
        */
        bool IsSmth = 0;
        IsFinished = 1;
        for(int i = 0; i < n; ++i) {
            if(arr[i] >= 0){IsSmth = 1; continue;}
            if(arr[i] < 0 && IsSmth){IsFinished = 0; break;}
        }
    }
    cout << "\nModified array:\n";
    for(int i = 0; i < n - 1; ++i) cout << arr[i] << '\x20';
    cout << arr[n - 1] << "\n\n";

    delete[] arr;
    return 0;
}