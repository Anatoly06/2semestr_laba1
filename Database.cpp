#include "Database.h"
#include <iostream>
#include <fstream>

using namespace std;

Database::Database() {
    students = nullptr;
    size = 0;
    capacity = 0;
}

Database::Database(const Database& other) {
    size = other.size;
    capacity = other.capacity;
    students = new Student[capacity];
    for (int i = 0; i < size; i++) {
        students[i] = other.students[i];
    }
}

Database::~Database() {
    if (students != nullptr) {
        delete[] students;
    }
}

Database& Database::operator=(const Database& other) {
    if (this != &other) {
        delete[] students;

        size = other.size;
        capacity = other.capacity;
        students = new Student[capacity];
        for (int i = 0; i < size; i++) {
            students[i] = other.students[i];
        }
    }
    return *this;
}

void Database::resize() {
    int newCapacity;
    if (capacity == 0) {
        newCapacity = 10;
    }
    else {
        newCapacity = capacity * 2;
    }

    Student* newStudents = new Student[newCapacity];
    for (int i = 0; i < size; i++) {
        newStudents[i] = students[i];
    }

    if (students != nullptr) {
        delete[] students;
    }
    students = newStudents;
    capacity = newCapacity;
}

int Database::findById(int id) const {
    for (int i = 0; i < size; i++) {
        if (students[i].getId() == id) {
            return i;
        }
    }
    return -1;
}

void Database::loadFromFile(string filename) {
    ifstream file(filename.c_str());
    if (!file.is_open()) {
        cout << "Файл " << filename << " не найден, создаем новую базу" << endl;
        return;
    }

    Student temp;
    while (file >> temp) {
        if (size >= capacity) {
            resize();
        }
        students[size] = temp;
        size++;
    }

    file.close();
    cout << "Загружено " << size << " студентов из файла " << filename << endl;
}

void Database::saveToFile(string filename) {
    ofstream file(filename.c_str());
    if (!file.is_open()) {
        cout << "Ошибка сохранения в файл " << filename << "!" << endl;
        return;
    }

    for (int i = 0; i < size; i++) {
        file << students[i] << endl;
    }

    file.close();
    cout << "Сохранено " << size << " записей в файл " << filename << endl;
}

void Database::printAll() const {
    if (size == 0) {
        cout << "всех отчислили" << endl;
        return;
    }

    for (int i = 0; i < size; i++) {
        cout << "Студент #" << i + 1 << endl;
        cout << "ФИО: " << students[i].getName() << endl;
        cout << "Группа: " << students[i].getGroup() << endl;
        cout << "ID: " << students[i].getId() << endl;
        cout << "Ср. балл: " << students[i].getAvgGrade() << endl;
    }
}

void Database::searchByName(string search) const {
    bool found = false;
    cout << "\nРезультаты поиска по имени \"" << search << "\":" << endl;

    for (int i = 0; i < size; i++) {
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

void Database::searchByGroup(string search) const {
    bool found = false;
    cout << "\nРезультаты поиска по группе \"" << search << "\":" << endl;

    for (int i = 0; i < size; i++) {
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

void Database::searchById(int id) const {
    int index = findById(id);
    if (index != -1) {
        cout << "\nНайден студент:" << endl;
        cout << "ФИО: " << students[index].getName() << endl;
        cout << "Группа: " << students[index].getGroup() << endl;
        cout << "Ср. балл: " << students[index].getAvgGrade() << endl;
    }
    else {
        cout << "Студент с ID " << id << " не найден" << endl;
    }
}

void Database::searchByGrade(double minGrade) const {
    bool found = false;
    cout << "\nСтуденты со средним баллом >= " << minGrade << ":" << endl;

    for (int i = 0; i < size; i++) {
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

void Database::searchByGroupAndName(string group, string name) const {
    bool found = false;
    cout << "\nПоиск по группе \"" << group << "\" и имени \"" << name << "\":" << endl;

    for (int i = 0; i < size; i++) {
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

void Database::addStudent() {
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

    if (findById(id) != -1) {
        cout << "Такой ID уже существует!" << endl;
        return;
    }

    cout << "Средний балл: ";
    cin >> grade;

    if (size >= capacity) {
        resize();
    }

    students[size] = Student(name, group, id, grade);
    size++;
    cout << "Добавлено!" << endl;
}

void Database::removeStudent() {
    int id;
    cout << "\nВведите ID для удаления: ";
    cin >> id;

    int index = findById(id);
    if (index == -1) {
        cout << "Студент не найден" << endl;
        return;
    }

    for (int i = index; i < size - 1; i++) {
        students[i] = students[i + 1];
    }
    size--;

    cout << "студент отчислен" << endl;
}

void Database::editStudent() {
    int id;
    cout << "\nВведите ID для редактирования: ";
    cin >> id;

    int index = findById(id);
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

int Database::getSize() const {
    return size;
}

bool Database::isEmpty() const {
    return size == 0;
}
