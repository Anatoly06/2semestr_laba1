#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
#include <string>

class Student {
private:
    std::string name;
    std::string group;
    int id;
    double avgGrade;

public:
    Student();
    Student(std::string n, std::string g, int i, double ag);
    Student(const Student& other);
    ~Student();

    std::string getName() const;
    std::string getGroup() const;
    int getId() const;
    double getAvgGrade() const;

    void setName(std::string n);
    void setGroup(std::string g);
    void setId(int i);
    void setAvgGrade(double ag);

    Student& operator=(const Student& other);

    friend std::ostream& operator<<(std::ostream& os, const Student& s);
    friend std::istream& operator>>(std::istream& is, Student& s);
};

#endif
