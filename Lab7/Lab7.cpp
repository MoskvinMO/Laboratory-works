#include <iostream>
#include <string>
#include "Students.h"

using namespace std;

// Overloading of operator <<:
ostream& operator<<(ostream& out, const Student& student);
ostream& operator<<(ostream& out, StudentAfterTheFirstSession& smb);
ostream& operator<<(ostream& out, StudentAfterTheSecondSession& smb);

int main() {
    cout << "\nExample of using of our classes.\n\n";
    char* aa = new char[4];
    aa[0] = 'A'; aa[1] = 'b'; aa[2] = 'c'; aa[3] = 0; // aa is a name "Abc".
    Student a(aa, 3, 5, "9");
    Student c(a);
    aa[1] = 'd'; // aa is a name "Adc" now.
    Student b(aa, 5, 7, "A3B59C0P"); // zachetka's number can be a string with not only digits.
    short arr[4] = {1, 2, 3, 5}; // The first array of marks.
    StudentAfterTheFirstSession d(aa, 11, 0, "9", arr);
    StudentAfterTheFirstSession e(d);
    StudentAfterTheFirstSession f(c, arr);
    cout<<"a id: "<<a.getId()<<".\n"<<"b id: "<<b.getId()<<".\n";
    cout<<"c id: "<<c.getId()<<"; c name: "<<c.getName()<<".\n";
    cout<<"d course: "<<d.getCourse()<<".\n";
    cout<<"e id: "<<e.getId()<<"; e name: "<<e.getName()<<"; the first his mark is: "<<e.getMark1(1)<<'\n';
    short arrr[5] = {11,12,13,14,15}; // The second array of marks.
    StudentAfterTheSecondSession g(e, arrr);
    g.setMark2(21,1);
    cout << "The first mark of g in the 2nd session is " << g.getMark2(1) << ".\n";
    cout<<"Information about a, b, f, g:\n";
    cout<<a<<".\n"<<b<<".\n"<<f<<".\n"<<g<<".\n";
    cout<<"Average mark of f is "<<d.averageGrade()<<".\n";
    cout<<"Average mark of g is "<<g.averageGrade()<<".\n\n";
    return 0;
}


ostream& operator<<(ostream& out, const Student& student){
    out << student.getId() << ": student " << student.getName() << ", course " << student.getCourse()
    << ", group " << student.getGroup() << ", zachetka number " << student.getZachetkaNumber();
    // we don't finish it with a point because we want to try to use static_cast when overloading << for heirs of Student
    return out;
}

ostream& operator<<(ostream& out, StudentAfterTheFirstSession& smb){
    StudentAfterTheFirstSession* smbPtr = &smb;
    out << *static_cast<Student*>(smbPtr);
    out << ", marks after the first session are: ";
    for(signed char i = 1; i < 5; ++i){
        out<<smbPtr->getMark1(i);
        if(i-4) out << '\x20';
    }
    return out;
}

ostream& operator<<(ostream& out, StudentAfterTheSecondSession& smb){
    StudentAfterTheSecondSession* smbPtr = &smb;
    out << *static_cast<StudentAfterTheFirstSession*>(smbPtr);
    out << ", marks after the second session are: ";
    for(signed char i = 1; i < 6; ++i){
        out<<smbPtr->getMark2(i);
        if(i-5) out << '\x20';
    }
    return out;
}