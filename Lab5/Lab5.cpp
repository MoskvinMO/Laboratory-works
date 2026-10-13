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

    // Viewing:
    cout << "Do you want to view files? Input 1 for viewing the 1st, 2 for viewing the 2nd, something else for continuation: ";
    string view;
    getline(cin, view);
    cout << '\n';
    string fileString{};
    while(1) {
        // view shows which file we want to open.
        if(view == "1") {
            ifstream in(file1, ios::app);
            while(getline(in, fileString)) {
                cout << fileString << '\n';
            }
            in.close();
        }
        else if(view == "2") {
            ifstream in(file2, ios::app);
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
    ofstream out(file3); // out is opened file3
    string row; // we will move file1 and file2 to file3 by rows
    ifstream in1(file1, ios::app); // in2 is opened file1
    while(getline(in1, row)) out << row << '\n'; // moving file1 to file3
    in1.close();
    ifstream in2(file2, ios::app); // in2 is opened file1
    while(getline(in2, row)) out << row << '\n'; // moving file2 to file3
    in2.close();
    out.close();
    FileSort(file3); // sorting the file3
    // Output of file3:
    cout << "We have done the task. The third file's strings are:\n\n";
    ifstream in3(file3, ios::app); // in3 is opened file3
    while(getline(in3, row)) cout << row << '\n';
    in3.close();
    cout << '\n';
    return 0;
}

void FileSort(string fileName) { // sorting rows in file named fileName
    // We move file rows to the vector fileRows, sort this vector and move back.
    vector<string> fileRows{};
    ifstream file(fileName, ios::app);
    string row;
    while(getline(file, row)) { // moving rows to vector
        fileRows.push_back(row);
    }
    sort(fileRows.begin(), fileRows.end()); // sorting a vector
    file.close();
    ofstream fileAgain(fileName);
    for(auto sortedRow : fileRows) fileAgain << sortedRow << '\n'; // moving back
    file.close();
}