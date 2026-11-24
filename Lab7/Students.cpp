/*
    This is realisation of classes Student, StudentAfterTheFirstSession and StudentAfterTheSecondSession.
    Warning: overloading of operator << is not here. It is in Lab7.cpp.
*/

#include <iostream>
#include <string>
#include "Students.h"

using namespace std;

using ll = long long;

    // Class Student.

//  Constructors:
Student::Student(char* name, int course, int group, string zachetkaNumber){
    m_id = m_latestId;
    ++m_latestId;

    m_name = new char[strlen(name)+1];
    strcpy(m_name, name); // strcpy copies \0 too
    m_course = course;
    m_group = group;
    m_zachetkaNumber = zachetkaNumber;
}
// Copy constructor:
Student::Student(Student& smb):m_course{smb.m_course},m_group(smb.m_group),m_zachetkaNumber{smb.m_zachetkaNumber}{
    m_id = m_latestId;
    ++m_latestId; // We change an id even thought we just create a copy.

    m_name = new char[strlen(smb.m_name)+1];
    strcpy(m_name, smb.m_name); // strcpy copies \0 too
}

// Destructor:
Student::~Student(){
    // cout<<"\nDELETED: "<<m_name<<".\n";
    if(m_name != nullptr) delete[] m_name;
}

// Getters:
ll Student::getId() const
{
    return m_id;
}
char* Student::getName() const
{
    char* name = new char[strlen(m_name) + 1];
    strcpy(name, m_name);
    return name;
}
int Student::getCourse() const
{
    return m_course;
}
int Student::getGroup() const
{
    return m_group;
}
string Student::getZachetkaNumber() const
{
    return m_zachetkaNumber;
}

// Setters:
// We aren't allowed to change an id or zachetkaNumber
void Student::setName(char* name)
{
    if(m_name) delete[] m_name;
    m_name = new char[strlen(name)+1];
    strcpy(m_name, name);
}
void Student::setCourse(int course)
{
    m_course = course;
}
void Student::setGroup(int group)
{
    m_group = group;
}


    // Class StudentAfterTheFirstSession.

// Constructors:
StudentAfterTheFirstSession::StudentAfterTheFirstSession(char* name, int course, int group, string zachetkaNumber, short marks1[4])
:Student(name, course, group, zachetkaNumber) {
    for(int i = 0; i < 4; ++i) m_marks1[i] = marks1[i];
}
// Copy constructor:
StudentAfterTheFirstSession::StudentAfterTheFirstSession(StudentAfterTheFirstSession& smb):Student(smb) {
    for(int i = 0; i < 4; ++i) m_marks1[i] = smb.m_marks1[i];
}
// Constructor "Student --> StudentAfterTheFirstSession":
StudentAfterTheFirstSession::StudentAfterTheFirstSession(Student& smb, short marks1[4]):Student(smb) {
    for(int i = 0; i < 4; ++i) m_marks1[i] = marks1[i];
}

// Getter:
// Numeration starts from 1 here.
short StudentAfterTheFirstSession::getMark1(short number) const {
    if(number < 1 || number > 4) return -1;
    return m_marks1[number - 1];
}

// Setter:
void StudentAfterTheFirstSession::setMark1(short value, signed char number) {
    if(number < 1 || number > 4) return; // may be throw will be better here
    m_marks1[number - 1] = value;
}


    // Class StudentAfterTheSecondSession.

// Constructors:
StudentAfterTheSecondSession::StudentAfterTheSecondSession(char* name, int course, int group, string zachetkaNumber, short marks1[4], short marks2[5])
:StudentAfterTheFirstSession(name, course, group, zachetkaNumber, marks1){
    for(int i = 0; i < 5; ++i) m_marks2[i] = marks2[i];
}
// Copy constructor:
StudentAfterTheSecondSession::StudentAfterTheSecondSession(StudentAfterTheSecondSession& smb):StudentAfterTheFirstSession(smb) {
    for(int i = 0; i < 5; ++i) m_marks2[i] = smb.m_marks2[i];
}
// Constructor "StudentAfterTheFirstSession --> StudentAfterTheSecondSession":
StudentAfterTheSecondSession::StudentAfterTheSecondSession(StudentAfterTheFirstSession& smb, short marks2[5]):StudentAfterTheFirstSession(smb) {
    for(int i = 0; i < 5; ++i) m_marks2[i] = marks2[i];
}

// Getter:
// Numeration starts from 1 here.
short StudentAfterTheSecondSession::getMark2(short number) const {
    if(number < 1 || number > 5) return -1; // may be throw will be better here
    return m_marks2[number - 1];
}

// Setter:
void StudentAfterTheSecondSession::setMark2(short value, signed char number) {
    if(number < 1 || number > 5) return; // may be throw will be better here
    m_marks2[number - 1] = value;
}