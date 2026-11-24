#include <iostream>
#include <string>

using namespace std;

using ll = long long;


class Student{
public:
    Student(char* name, int course, int group, string zachetkaNumber){
        m_id = m_latestId;
        ++m_latestId;

        m_name = new char[strlen(name)+1];
        strcpy(m_name, name); // strcpy copies \0 too

        m_course = course;
        m_group = group;
        m_zachetkaNumber = zachetkaNumber;
    }
    Student() = delete;
    Student(Student& smb):m_course{smb.m_course},m_group(smb.m_group),m_zachetkaNumber{smb.m_zachetkaNumber}{
        m_id = m_latestId;
        ++m_latestId;

        m_name = new char[strlen(smb.m_name)+1];
        strcpy(m_name, smb.m_name); // strcpy copies \0 too
    }
    ~Student(){                                            // CHANGE THIS IN THE END
        cout<<"\nDELETED: "<<m_name<<".\n";
        if(m_name!=nullptr) delete[] m_name;
    }
    ll getId() const
    {
        return m_id;
    }
    char* getName() const
    {
        char* name = new char[strlen(m_name)+1];
        strcpy(name, m_name);
        return name;
    }
    int getCourse() const
    {
        return m_course;
    }
    int getGroup() const
    {
        return m_group;
    }
    string getZachetkaNumber() const
    {
        return m_zachetkaNumber;
    }
    void setName(char* name)
    {
        if(m_name) delete[] m_name;
        m_name = new char[strlen(name)+1];
        strcpy(m_name, name);
    }
    void setCourse(int course)
    {
        m_course = course;
    }
    void setGroup(int group)
    {
        m_group = group;
    }
public:                 // CHANGE THIS TO PRIVATE LATER
    ll m_id;
    char* m_name;
    int m_course;
    int m_group;
    // We don't know whether zachetka's number is really a number;
    // for example, see identificational number in a passport.
    string m_zachetkaNumber;            // ???
    static inline ll m_latestId{}; // it's used in id creating
};
ostream& operator<<(ostream& out, const Student& student){
    out << student.getId() << ": student " << student.getName() << ", course " << student.getCourse()
    << ", group " << student.getGroup() << ", zachetka number " << student.getZachetkaNumber();
    // we don't finish it with a point because we want to try to use static_cast when overloading << for heirs of Student
    return out;
}


class StudentAfterTheFirstSession: public Student {
public:
    StudentAfterTheFirstSession(char* name, int course, int group, string zachetkaNumber, short marks1[4]):Student(name, course, group, zachetkaNumber) {
        for(int i=0; i<4; ++i) m_marks1[i] = marks1[i];
    }
    StudentAfterTheFirstSession() = delete;
    StudentAfterTheFirstSession(StudentAfterTheFirstSession& smb):Student(smb) {
        for(int i=0; i<4; ++i) m_marks1[i] = smb.m_marks1[i];
    }
    StudentAfterTheFirstSession(Student& smb, short marks1[4]):Student(smb) {
        for(int i=0; i<4; ++i) m_marks1[i] = marks1[i];
    }
    // Numeration starts from 1 here.
    short getMark1(short number) const {
        if(number < 1 || number > 4) return -1; // may be throw will be better here
        return m_marks1[number-1];
    }
    void setMark1(short value, signed char number) {
        if(number < 1 || number > 4) return; // may be throw will be better here
        m_marks1[number-1] = value;
    }
private:
    short m_marks1[4];
};
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


class StudentAfterTheSecondSession: public StudentAfterTheFirstSession {
    public:
    StudentAfterTheSecondSession(char* name, int course, int group, string zachetkaNumber, short marks1[4], short marks2[5]):
    StudentAfterTheFirstSession(name, course, group, zachetkaNumber, marks1){
        for(int i=0; i<5; ++i) m_marks2[i] = marks2[i];
    }
    StudentAfterTheSecondSession() = delete;
    StudentAfterTheSecondSession(StudentAfterTheSecondSession& smb):StudentAfterTheFirstSession(smb) {
        for(int i=0; i<5; ++i) m_marks2[i] = smb.m_marks2[i];
    }
    StudentAfterTheSecondSession(StudentAfterTheFirstSession& smb, short marks2[5]):StudentAfterTheFirstSession(smb) {
        for(int i=0; i<5; ++i) m_marks2[i] = marks2[i];
    }
    // Numeration starts from 1 here.
    short getMark2(short number) const {
        if(number < 1 || number > 5) return -1; // may be throw will be better here
        return m_marks2[number-1];
    }
    void setMark2(short value, signed char number) {
        if(number < 1 || number > 5) return; // may be throw will be better here
        m_marks2[number-1] = value;
    }
private:
    short m_marks2[5];
};
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


int main(){
    char* aa = new char[4];
    aa[0] = 'a'; aa[1] = 'b'; aa[2] = 'c'; aa[3] = 0;
    Student a(aa, 3, 5, "9");
    aa[1] = 'd';
    Student b(aa, 5, 7, "A3B59C0P");
    short arr[4] = {1, 2, 3, 5};
    StudentAfterTheFirstSession d(aa, 11, 0, "9", arr);
    StudentAfterTheFirstSession e(d);
    Student c(a);
    StudentAfterTheFirstSession f(c, arr);
    cout<<a.m_id<<b.m_id;
    cout<<c.m_id<<c.m_name;
    cout<<d.m_id<<e.m_id<<e.m_name;
    cout<<'\x20'<<e.getMark1(1)<<'\n';
    short arrr[5] = {11,12,13,14,15};
    StudentAfterTheSecondSession g(e, arrr);
    g.setMark2(21,1);
    cout<<g.getMark2(1) << '\n';
    cout<<a<<'.'<<'\x20'<<b<<'\n'<<f<<endl;
    cout<<g;
    return 0;
}