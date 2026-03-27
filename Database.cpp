#include "Database.h"
#include <iostream>
#include <fstream>

using namespace std;

namespace MyDB {

    void load(vector<Student>& students, string filename) {
        ifstream file(filename.c_str());
        if (!file.is_open()) {
            return;
        }

        string line;
        while (getline(file, line)) {
            if (line.empty()) continue;

            size_t p1 = line.find('|');
            size_t p2 = line.find('|', p1 + 1);
            size_t p3 = line.find('|', p2 + 1);

            if (p1 != string::npos && p2 != string::npos && p3 != string::npos) {
                string name = line.substr(0, p1);
                string group = line.substr(p1 + 1, p2 - p1 - 1);
                int id = stoi(line.substr(p2 + 1, p3 - p2 - 1));
                double grade = stod(line.substr(p3 + 1));

                students.push_back(Student(name, group, id, grade));
            }
        }
        file.close();
        cout << "Загружено " << students.size() << " студентов" << endl;
    }

    void save(vector<Student>& students, string filename) {
        ofstream file(filename.c_str());
        if (!file.is_open()) {
            cout << "Ошибка сохранения!" << endl;
            return;
        }

        for (int i = 0; i < students.size(); i++) {
            file << students[i].getName() << "|"
                << students[i].getGroup() << "|"
                << students[i].getId() << "|"
                << students[i].getAvgGrade() << endl;
        }
        file.close();
        cout << "Сохранено " << students.size() << " записей" << endl;
    }

    void showAll(vector<Student>& students) {
        if (students.size() == 0) {
            cout << "всех отчислили" << endl;
            return;
        }

        for (int i = 0; i < students.size(); i++) {
            cout << endl << "Студент #" << i + 1 << endl;
            cout << "ФИО: " << students[i].getName() << endl;
            cout << "Группа: " << students[i].getGroup() << endl;
            cout << "ID: " << students[i].getId() << endl;
            cout << "Ср. балл: " << students[i].getAvgGrade() << endl;
        }
    }

    void findByName(vector<Student>& students, string search) {
        bool found = false;
        cout << "\nРезультаты поиска по имени \"" << search << "\":" << endl;

        for (int i = 0; i < students.size(); i++) {
            if (students[i].getName().find(search) != string::npos) {
                cout << "ID: " << students[i].getId() << " | "
                    << students[i].getName() << " | "
                    << students[i].getGroup() << " | "
                    << students[i].getAvgGrade() << endl;
                found = true;
            }
        }

        if (!found) cout << "Ничего не найдено" << endl;
    }

    void findByGroup(vector<Student>& students, string search) {
        bool found = false;
        cout << "\nРезультаты поиска по группе \"" << search << "\":" << endl;

        for (int i = 0; i < students.size(); i++) {
            if (students[i].getGroup() == search) {
                cout << "ID: " << students[i].getId() << " | "
                    << students[i].getName() << " | "
                    << students[i].getGroup() << " | "
                    << students[i].getAvgGrade() << endl;
                found = true;
            }
        }

        if (!found) cout << "Ничего не найдено" << endl;
    }

    void findById(vector<Student>& students, int id) {
        for (int i = 0; i < students.size(); i++) {
            if (students[i].getId() == id) {
                cout << "\nНайден студент:" << endl;
                cout << "ФИО: " << students[i].getName() << endl;
                cout << "Группа: " << students[i].getGroup() << endl;
                cout << "Ср. балл: " << students[i].getAvgGrade() << endl;
                return;
            }
        }
        cout << "Студент с ID " << id << " не найден" << endl;
    }

    void findByGrade(vector<Student>& students, double minGrade) {
        bool found = false;
        cout << "\nСтуденты со средним баллом >= " << minGrade << ":" << endl;

        for (int i = 0; i < students.size(); i++) {
            if (students[i].getAvgGrade() >= minGrade) {
                cout << "ID: " << students[i].getId() << " | "
                    << students[i].getName() << " | "
                    << students[i].getGroup() << " | "
                    << students[i].getAvgGrade() << endl;
                found = true;
            }
        }

        if (!found) cout << "Ничего не найдено" << endl;
    }

    void findByGroupAndName(vector<Student>& students, string group, string name) {
        bool found = false;
        cout << "\nПоиск по группе \"" << group << "\" и имени \"" << name << "\":" << endl;

        for (int i = 0; i < students.size(); i++) {
            if (students[i].getGroup() == group &&
                students[i].getName().find(name) != string::npos) {
                cout << "ID: " << students[i].getId() << " | "
                    << students[i].getName() << " | "
                    << students[i].getAvgGrade() << endl;
                found = true;
            }
        }

        if (!found) cout << "Ничего не найдено" << endl;
    }

    int searchByIdHelper(vector<Student>& students, int id) {
        for (int i = 0; i < students.size(); i++) {
            if (students[i].getId() == id) {
                return i;
            }
        }
        return -1;
    }

    void add(vector<Student>& students) {
        string name, group;
        int id;
        double grade;

        cout << "\nДобавление студента" << endl;
        cout << "ФИО: ";
        cin.ignore();
        getline(cin, name);

        cout << "Группа: ";
        getline(cin, group);

        cout << "ID: ";
        cin >> id;

        if (searchByIdHelper(students, id) != -1) {
            cout << "Такой ID уже существует!" << endl;
            return;
        }

        cout << "Средний балл: ";
        cin >> grade;

        students.push_back(Student(name, group, id, grade));
        cout << "Добавлено!" << endl;
    }

    void remove(vector<Student>& students) {
        int id;
        cout << "\nВведите ID для удаления: ";
        cin >> id;

        int index = searchByIdHelper(students, id);
        if (index == -1) {
            cout << "Студент не найден" << endl;
            return;
        }

        students.erase(students.begin() + index);
        cout << "студент отчислен" << endl;
    }

    void edit(vector<Student>& students) {
        int id;
        cout << "\nВведите ID для редактирования: ";
        cin >> id;

        int index = searchByIdHelper(students, id);
        if (index == -1) {
            cout << "Студент не найден" << endl;
            return;
        }

        cout << "\nТекущие данные:" << endl;
        cout << "ФИО: " << students[index].getName() << endl;
        cout << "Группа: " << students[index].getGroup() << endl;
        cout << "Ср. балл: " << students[index].getAvgGrade() << endl;

        cout << "\nВведите новые данные (Enter - оставить как есть):" << endl;
        cin.ignore();

        string newName;
        cout << "Новое ФИО: ";
        getline(cin, newName);
        if (newName != "") students[index].setName(newName);

        string newGroup;
        cout << "Новая группа: ";
        getline(cin, newGroup);
        if (newGroup != "") students[index].setGroup(newGroup);

        string newGrade;
        cout << "Новый средний балл: ";
        getline(cin, newGrade);
        if (newGrade != "") {
            double g = stod(newGrade);
            students[index].setAvgGrade(g);
        }

        cout << "Обновлено!" << endl;
    }

}