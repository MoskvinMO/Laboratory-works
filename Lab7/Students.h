#ifndef STUDENTS_H
#define STUDENTS_H

#include <iostream>
#include <string>

using namespace std;

using ll = long long;


class Student{
public:
    // Constructors:
    Student(char* name, int course, int group, string zachetkaNumber);
    Student() = delete;    // Default constructor is deleted.
    Student(Student& smb); // Copy constructor.
    // Destructor:
    ~Student();

    // Getters:
    ll getId() const;
    char* getName() const;
    int getCourse() const;
    int getGroup() const;
    string getZachetkaNumber() const;

    // Setters:
    void setName(char* name);
    void setCourse(int course);
    void setGroup(int group);
private:
    ll m_id;
    char* m_name;
    int m_course;
    int m_group;
    // We don't know whether zachetka's number is really a number;
    // for example, see identificational number in a passport.
    // We don't have methods for changing m_zachetkaNumber so it is unchangable.
    string m_zachetkaNumber;
    static inline ll m_latestId{}; // it's used in id creating
};


class StudentAfterTheFirstSession: public Student {
public:
    // Constructors:
    StudentAfterTheFirstSession(char* name, int course, int group, string zachetkaNumber, short marks1[4]);
    StudentAfterTheFirstSession() = delete; // default constructor is deleted
    StudentAfterTheFirstSession(StudentAfterTheFirstSession& smb); // Copy constructor
    // Useful constructor from Strudent to StudentAfterTheFirstSession:
    StudentAfterTheFirstSession(Student& smb, short marks1[4]);

    // Getters:
    // Numeration starts from 1 here!
    short getMark1(short number) const;
    void setMark1(short value, signed char number);
private:
    short m_marks1[4];
};


class StudentAfterTheSecondSession: public StudentAfterTheFirstSession {
    public:
    // Constructors:
    StudentAfterTheSecondSession(char* name, int course, int group, string zachetkaNumber, short marks1[4], short marks2[5]);
    StudentAfterTheSecondSession() = delete;
    StudentAfterTheSecondSession(StudentAfterTheSecondSession& smb);
    StudentAfterTheSecondSession(StudentAfterTheFirstSession& smb, short marks2[5]);

    // Getter:
    // Numeration starts from 1 here!
    short getMark2(short number) const;

    // Setter
    void setMark2(short value, signed char number);
private:
    short m_marks2[5];
};

#endif