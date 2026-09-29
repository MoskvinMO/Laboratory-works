#include <iostream>
#include <vector>
#include <iomanip>
#include <limits>

using namespace std;

int M(int a, int b, vector<vector<int>>& m) {
// M(a, b, m) is an element of matrix m written as triangle on place [a][b]
    if(a < b) swap(a,b);
    return m[a][b];
}

int IntSize(int n) { // number of digits of int n
    int u = (n == 0);
    while(n) {n /= 10; ++u;}
    return u;
}

struct diagonal {
    int number;
    long long sum;
};

int main() {
    // input size
    cout << "\nPlease, write any dimension of our square matrix: ";
    int n;
    cin >> n;
    vector<vector<int>> m;

    // if input is incorrect
    while(n < 1 || n > 10) {
        cout << "Input is incorrect. Please, try again or write the same number if you are ready to consequences.\n"
        << "Write any dimension of our square matrix again: ";
        int nTryAgain;
        cin >> nTryAgain;
        if(nTryAgain == n || (nTryAgain > 0 && nTryAgain < 11)) {n = nTryAgain; break;}
    }

    // input
    vector<int> v;       // 1 row of matrix
    int k;               // 1 element of matrix
    int maxIntSize = 1;  // maximal number of digits of elements of matrix
    for(int i = 1; i <= n; ++i) {
        for(int j = 0; j < i;) {
            cout << "Write an element in row " << i << " and column " << ++j <<": ";
            cin >> k;
            maxIntSize = max(maxIntSize, IntSize(k));
            v.push_back(k);
        }
        m.push_back(v);
        v.clear();
    }

    // output
    cout << "\nMatrix is:\n";
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < n - 1; ++j) cout << setw(maxIntSize) << M(i, j, m) << ' ';
        cout << setw(maxIntSize) << M(i, n - 1, m) << '\n';
    }

    int mxn = numeric_limits<int>::min(); // maximal element in columns without positive elements
    int tmxn{}; // maximal element in column we consider at given moment of time
    bool IsNonPositiveColumnExist{};
    for(int j = 0; j < n; ++j) {
        for(int i = 0; i < n; ++i) if(M(i, j, m) > 0) goto EXIT; // if column contain a positive element, stop scanning this column
        IsNonPositiveColumnExist = 1; // if we are here, than we have found a column without positive elements
        for(int i = 0; i < n; ++i) mxn = max(mxn, M(i, j, m));
        EXIT:;
    }
    if(IsNonPositiveColumnExist) cout << "\nMaximal element in columns without positive elements is: " << mxn << ".\n";
    else cout << "\nThere is no column without positive elements.\n";

    diagonal winner = {0, 0}; // diagonal with minimal average matching the conditions
    if(n == 1) {
        cout << "\nThere is no diagonal corresponding to the statement.\n\n";
        return 0;
    }
    for(int i = 0; i < 2 * n - 1; ++i) { // cycle on diagonals
        if(i == n - 1) continue;         // we don't consider the antidiagonal
        long long temptSum = 0;          // sum of elements of diagonal we consider now
        // there won't be overflow because of n <= 10
        for(int j = max(0, i - n + 1); j < min(i + 1, n); ++j) { // cycle on elements of diagonal number i + 1
            temptSum+=M(j, i - j, m);
        }
        if(!i || temptSum * winner.number < winner.sum * min(i + 1, 2 * n - 1 - i)) {winner.number = min(i + 1, 2 * n - 1 - i); winner.sum = temptSum;}
        // If our diagonal has average less than winner, change winner.
        // !i is here because we need to put a real diagonal as winner.
        // There won't be overflow because of n <= 10.
    }
    cout << setprecision(16) << '\n'; // precision is not too bad and not too large to contain a lot of wrong digits
    cout << "Minimal average of numbers on the diagonals parallel to antidiagonal and that aren't antidiagonal is (approximately): "
    << ((long double)winner.sum) / winner.number << ".\n\n";
    return 0;
}