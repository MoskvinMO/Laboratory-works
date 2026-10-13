/*
We assume that we should sort strings-rows.
For example, sorting a file {
a
n ab
klm
}
will give us file {
a
klm
n ab
}
*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

void FileSort(string fileName); // function for sorting the rows in a file named fileName

int main() {
    // Input files names:
    cout<<"\nWhen writing file names, write full names. For example, \"foo.txt\".\n";
    cout << "\nWhat is the first file? Please, write it's name: ";
    string file1;
    getline(cin, file1);
    FileSort(file1);
    cout << "What is the second file? Please, write it's name: ";
    string file2;
    getline(cin, file2);
    FileSort(file2);

    // Mode of opening choosing:
    cout << "Do you want to destroy all data in files or keep them?\nPress 0+Enter for destoying the 1st, 1+Enter for keeping the 1st: ";
    bool file1Fate;
    cin >> file1Fate;
    cout << "Press 0+Enter for destoying the 2nd, 1+Enter for keeping the 2nd: ";
    bool file2Fate;
    cin >> file2Fate;

    // Viewing:
    cout << "Do you want to view files? Input 1 for viewing the 1st, 2 for viewing the 2nd, something else for continuation: ";
    string view;
    getline(cin, view); // getline that make everything OK after "cin >> file2Fate"
    getline(cin, view); // getline that really get a string view
    cout << '\n';
    string fileString{};
    while(1) {
        // view show which file we want to open;
        // format of opening depends on file's fate.
        // 4 options that lead to viewing.
        if(view == "1" && file1Fate) {
            ifstream in(file1, ios::app);
            while(getline(in, fileString)) {
                cout << fileString << '\n';
            }
            in.close();
        }
        else if(view == "1" && !file1Fate) {
            ifstream in(file1);
            while(getline(in, fileString)) {
                cout << fileString << '\n';
            }
            in.close();
        }
        else if(view == "2" && file2Fate) {
            ifstream in(file2, ios::app);
            while(getline(in, fileString)) {
                cout << fileString << '\n';
            }
            in.close();
        }
        else if(view == "2" && !file2Fate) {
            ifstream in(file2);
            while(getline(in, fileString)) {
                cout << fileString << '\n';
            }
            in.close();
        }
        else break;
        cout << "\n   What is your next choice? "; // choice whether we will view again
        getline(cin, view);
        cout << '\n';
    }

    // Creating the 3rd file (file3):
    cout << "Now we will merge these 2 files into the 3rd.\nHow the third file should be named?\n";
    string file3;
    cin >> file3;
    ofstream out(file3);
    string row;
    if(file1Fate) {
        ifstream in(file1, ios::app);
        while(getline(in, row)) out << row << '\n';
    }
    else {
        ifstream in(file1);
        while(getline(in, row)) out << row << '\n';
    }
    if(file2Fate) {
        ifstream in(file2, ios::app);
        while(getline(in, row)) out << row << '\n';
    }
    else {
        ifstream in(file2);
        while(getline(in, row)) out << row << '\n';
    }
    out.close();
    FileSort(file3);
    cout << "We have done the task. The third file's strings are:\n\n";
    ifstream in(file3, ios::app);
    while(getline(in, row)) cout << row << '\n';
    in.close();
    cout << '\n';
    return 0;
}

void FileSort(string fileName) {
    vector<string> fileRows{};
    ifstream file(fileName, ios::app);
    string row;
    while(getline(file, row)) {
        fileRows.push_back(row);
    }
    sort(fileRows.begin(), fileRows.end());
    file.close();
    ofstream fileAgain(fileName);
    for(auto sortedRow : fileRows) fileAgain << sortedRow << '\n';
    file.close();
}