#include <iostream>
#include <vector>
using namespace std;

char* our_strcat(char* strDestination, const char* strSource) {
    // our version of strcat function
    int i = -1, j = -1;
    do ++i; while(*(strDestination + i) != 0); // moving to the end of strDestination
    do {
        ++j;
        *(strDestination + i) = *(strSource + j);
        ++i;
    } while(*(strSource + j) != 0); // adding symbols from strSource to strDestination
    return strDestination;
}

int main() {
    cout << "\nPart A or Part B? Input A for part A, B for part B: ";
    char c;
    cin >> c;
    while(c != 65 && c != 66) {
        cout << "Incorrect input. Try again: ";
        cin >> c;
    }

    if(c == 'A') {           // Part A
    constexpr short MAX_SIZE = 1024;
    char* str = new char[2 * MAX_SIZE + 4];
    char* str2 = new char[MAX_SIZE + 2];
    // str and str2 are our main strings
    cout << "\nNow we will show you how our_strcat works.\nWe need 2 strings. We will add the 2nd to the 1st.\n";
    cin.get(); // prepares us for using cin.get() later
    // input:
    cout << "Give us the 1st string of only ASCII characters, please. It's really shouldn't exceed " << MAX_SIZE << " symbols.\n";
    int i = -1;
    do {
        c = cin.get();
        str[++i] = c;
    } while(c != '\n');
    str[i] = 0;
    i = -1;
    cout << "Give us the 2nd string of only ASCII characters, please. It's really shouldn't exceed " << MAX_SIZE << " symbols.\n";
    do {
        c = cin.get();
        str2[++i] = c;
    } while(c != '\n');
    str2[i] = 0;
    // output:
    str = our_strcat(str, str2);
    cout << "\nWe have used our_strcat and now the 1st string is \"" << str
    << "\"; and the 2nd string is \"" << str2 << "\".\n\n";
    delete[] str; delete[] str2;
    }


    else {                   // Part B
    // input:
    char* str = new char[303];
    cout << "\nPlease, write a string with no more than 300 characters:\n";
    int i = -1;
    cin.get(); // prepares us for using cin.get() later
    do{
        c = cin.get();
        str[++i] = c;
    } while(c != '\n');
    str[i] = '\x20'; str[i + 1] = 0;
    // the last space is useful for word finding

    vector<bool> chars(128, 0); // chars[i] == 1 iff there is i-th ASCII symbol in the word we consider
    int sum{}; // number of different symbols
    char* winner = new char[302]; // string with minimal number of different symbols available now
    int winnerSum = 129; // sum for winner
    int spaceBefore = -1; // place where there is a space in str and this space was before the word we consider now;
                          // -1 in beginning is because the 1st word should start with the 0th symbol
    bool isWordExist{}; // 1 iff there is a word in str

    for(i = 0; *(str + i) != 0; ++i) {
        chars[*(str + i)]=1;
        if(*(str + i) == 32 && i != spaceBefore + 1) { // we found a non-empty word between spaceBefore-th and i-th symbols of str
            isWordExist = 1;
            for(int j = 0; j < 128; ++j) {sum += chars[j]; chars[j] = 0;} // computing the sum
            if(sum < winnerSum){
                for(int ii = spaceBefore + 1; ii < i; ++ii) { // winner --> our found word
                    winner[ii - spaceBefore - 1] = *(str + ii);
                }
                winner[i - spaceBefore - 1] = 0;
                winnerSum = sum;
            }
            spaceBefore = i;
            sum = 0;
        }
        if(*(str + i) == 32 && i == spaceBefore + 1) ++spaceBefore; // if 2 spaces near each other
    }
    if(!isWordExist) {
        cout << "\nThere aren't any words in the string.\n\n";
        return 0;
    }
    cout << "\nA word with minimal amount of different types of symbols is: \"";
    for(i = 0; *(winner + i) != 0; i++) cout << *(winner + i);
    cout << "\".\n\n";
    delete[] str; delete[] winner;
    }
    return 0;
}