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

Student::Student(const Student& other) {
    name = other.name;
    group = other.group;
    id = other.id;
    avgGrade = other.avgGrade;
}

Student::~Student() {
}

std::string Student::getName() const { return name; }
std::string Student::getGroup() const { return group; }
int Student::getId() const { return id; }
double Student::getAvgGrade() const { return avgGrade; }

void Student::setName(std::string n) { name = n; }
void Student::setGroup(std::string g) { group = g; }
void Student::setId(int i) { id = i; }
void Student::setAvgGrade(double ag) { avgGrade = ag; }

Student& Student::operator=(const Student& other) {
    if (this != &other) {
        name = other.name;
        group = other.group;
        id = other.id;
        avgGrade = other.avgGrade;
    }
    return *this;
}

std::ostream& operator<<(std::ostream& os, const Student& s) {
    os << s.name << "|" << s.group << "|" << s.id << "|" << s.avgGrade;
    return os;
}

std::istream& operator>>(std::istream& is, Student& s) {
    std::string line;
    if (getline(is, line)) {
        size_t p1 = line.find('|');
        size_t p2 = line.find('|', p1 + 1);
        size_t p3 = line.find('|', p2 + 1);

        if (p1 != std::string::npos && p2 != std::string::npos && p3 != std::string::npos) {
            s.name = line.substr(0, p1);
            s.group = line.substr(p1 + 1, p2 - p1 - 1);
            s.id = std::stoi(line.substr(p2 + 1, p3 - p2 - 1));
            s.avgGrade = std::stod(line.substr(p3 + 1));
        }
    }
    return is;
}
