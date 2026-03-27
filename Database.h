#ifndef DATABASE_H
#define DATABASE_H

#include "Student.h"
#include <vector>
#include <string>

namespace MyDB {

    void load(std::vector<Student>& students, std::string filename);
    void save(std::vector<Student>& students, std::string filename);

    void showAll(std::vector<Student>& students);

    void findByName(std::vector<Student>& students, std::string search);
    void findByGroup(std::vector<Student>& students, std::string search);
    void findById(std::vector<Student>& students, int id);
    void findByGrade(std::vector<Student>& students, double minGrade);
    void findByGroupAndName(std::vector<Student>& students, std::string group, std::string name);

    void add(std::vector<Student>& students);
    void remove(std::vector<Student>& students);
    void edit(std::vector<Student>& students);

    int searchByIdHelper(std::vector<Student>& students, int id);
}

#endif