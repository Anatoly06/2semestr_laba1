#ifndef DATABASE_H
#define DATABASE_H

#include "Student.h"
#include <string>

class Database {
private:
    Student* students;
    int size;
    int capacity;

    void resize();
    int findById(int id) const;

public:
    Database();
    Database(const Database& other);
    ~Database();

    Database& operator=(const Database& other);

    void loadFromFile(std::string filename);
    void saveToFile(std::string filename);

    void printAll() const;

    void searchByName(std::string search) const;
    void searchByGroup(std::string search) const;
    void searchById(int id) const;
    void searchByGrade(double minGrade) const;
    void searchByGroupAndName(std::string group, std::string name) const;

    void addStudent();
    void removeStudent();
    void editStudent();

    int getSize() const;
    bool isEmpty() const;
};

#endif
