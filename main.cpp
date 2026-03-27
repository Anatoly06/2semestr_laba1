#include "Database.h"
#include <iostream>
#include <cstdlib>

using namespace std;

string filename = "students.txt";

void showMenu() {
    cout << "\n         МЕНЮ" << endl;
    cout << "1. Показать всех студентов" << endl;
    cout << "2. Поиск по имени" << endl;
    cout << "3. Поиск по группе" << endl;
    cout << "4. Поиск по ID" << endl;
    cout << "5. Поиск по среднему баллу" << endl;
    cout << "6. Поиск по группе+имени" << endl;
    cout << "7. Добавить студента" << endl;
    cout << "8. Удалить студента" << endl;
    cout << "9. Редактировать студента" << endl;
    cout << "10. Сохранить и выйти" << endl;
    cout << "Выберите: ";
}

int main() {
    system("chcp 1251 > nul");

    vector<Student> students;
    MyDB::load(students, filename);

    int choice;

    do {
        showMenu();
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Ошибка! Введите число" << endl;
            continue;
        }

        switch (choice) {
        case 1:
            MyDB::showAll(students);
            break;

        case 2: {
            string s;
            cout << "Введите имя: ";
            cin.ignore();
            getline(cin, s);
            MyDB::findByName(students, s);
            break;
        }

        case 3: {
            string s;
            cout << "Введите группу: ";
            cin.ignore();
            getline(cin, s);
            MyDB::findByGroup(students, s);
            break;
        }

        case 4: {
            int id;
            cout << "Введите ID: ";
            cin >> id;
            MyDB::findById(students, id);
            break;
        }

        case 5: {
            double g;
            cout << "Введите минимальный балл: ";
            cin >> g;
            MyDB::findByGrade(students, g);
            break;
        }

        case 6: {
            string g, n;
            cout << "Введите группу: ";
            cin.ignore();
            getline(cin, g);
            cout << "Введите имя: ";
            getline(cin, n);
            MyDB::findByGroupAndName(students, g, n);
            break;
        }

        case 7:
            MyDB::add(students);
            break;

        case 8:
            MyDB::remove(students);
            break;

        case 9:
            MyDB::edit(students);
            break;

        case 10:
            MyDB::save(students, filename);
            cout << "Выход..." << endl;
            break;

        default:
            cout << "Неверный пункт меню" << endl;
        }

    } while (choice != 10);

    return 0;
}