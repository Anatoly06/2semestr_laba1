#include "Student.h"

Student::Student() {
    name = "";
    group = "";
    id = 0;
    avgGrade = 0.0;
}

Student::Student(std::string n, std::string g, int i, double ag) {
    name = n;
    group = g;
    id = i;
    avgGrade = ag;
}

std::string Student::getName() const { return name; }
std::string Student::getGroup() const { return group; }
int Student::getId() const { return id; }
double Student::getAvgGrade() const { return avgGrade; }

void Student::setName(std::string n) { name = n; }
void Student::setGroup(std::string g) { group = g; }
void Student::setId(int i) { id = i; }
void Student::setAvgGrade(double ag) { avgGrade = ag; }