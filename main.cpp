#include "Database.h"
#include <iostream>
#include <clocale>
#include <fstream>

using namespace std;

void showMenu() {
    cout << "\n           МЕНЮ" << endl;
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

bool fileExists(string filename) {
    ifstream file(filename.c_str());
    return file.is_open();
}

int main() {
    system("chcp 1251 > nul");
    setlocale(LC_ALL, "Russian");

    string filename;
    int choice;

    do {
        cout << "\nВведите имя файла для загрузки данных: ";
        getline(cin, filename);

        if (fileExists(filename)) {
            cout << "Файл " << filename << " найден" << endl;
            break;
        }
        else {
            cout << "Файл " << filename << " не существует" << endl;
            cout << "1. Создать новый файл с таким именем" << endl;
            cout << "2. Ввести другое имя файла" << endl;
            cout << "Выберите: ";
            cin >> choice;
            cin.ignore();

            if (choice == 1) {
                cout << "Будет создан новый файл " << filename << endl;
                break;
            }
        }
    } while (true);

    Database db;
    db.loadFromFile(filename);

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
            db.printAll();
            break;

        case 2: {
            string s;
            cout << "Введите имя: ";
            cin.ignore();
            getline(cin, s);
            db.searchByName(s);
            break;
        }

        case 3: {
            string s;
            cout << "Введите группу: ";
            cin.ignore();
            getline(cin, s);
            db.searchByGroup(s);
            break;
        }

        case 4: {
            int id;
            cout << "Введите ID: ";
            cin >> id;
            db.searchById(id);
            break;
        }

        case 5: {
            double g;
            cout << "Введите минимальный балл: ";
            cin >> g;
            db.searchByGrade(g);
            break;
        }

        case 6: {
            string g, n;
            cout << "Введите группу: ";
            cin.ignore();
            getline(cin, g);
            cout << "Введите имя: ";
            getline(cin, n);
            db.searchByGroupAndName(g, n);
            break;
        }

        case 7:
            db.addStudent();
            break;

        case 8:
            db.removeStudent();
            break;

        case 9:
            db.editStudent();
            break;

        case 10:
            db.saveToFile(filename);
            cout << "Выход..." << endl;
            break;

        default:
            cout << "Неверный пункт меню" << endl;
        }

    } while (choice != 10);

    return 0;
}
