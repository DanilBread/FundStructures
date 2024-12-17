#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

// Структура для хранения данных
struct treeData {
    string gosNumber;
    string surname;
    string name;
    string patronymic;
};

// Функция для проверки строки на соответствие формату
bool isString(const string& inString) {
    for (int i = 0; i < inString.length(); i++) {
        if (!isalpha(inString[i])) {
            return false;
        }
        if (!isupper(inString[0])) {
            return false;
        }
        if ((i != 0) && !islower(inString[i])) {
            return false;
        }
    }
    if (inString.length() <= 1) {
        return false;
    }
    return !inString.empty();
}

// Функция для проверки госномера
bool isGosNumber(const string& inString) {
    if (inString.length() != 10) {
        return false;
    }
    for (char ch : inString) {
        if (!isdigit(ch)) {
            return false;
        }
    }
    return !inString.empty();
}

// Функция для проверки данных
bool stringCheck(const treeData& data) {
    if (data.name.length() <= 1 || data.surname.length() <= 1 || data.patronymic.length() <= 1 || data.gosNumber.length() != 10) {
        return false;
    }
    if (!isString(data.name)) {
        return false;
    }
    if (!isString(data.surname)) {
        return false;
    }
    if (!isString(data.patronymic)) {
        return false;
    }
    if (!isGosNumber(data.gosNumber)) {
        return false;
    }
    return true;
}

// Функция для чтения данных из файла и вывода на экран
void readAndPrintData(const string& filename) {
    ifstream input(filename);
    if (!input.is_open()) {
        cout << "*** ERROR::File " << filename << " can't be opened ***" << endl;
        return;
    }

    string line;
    int lineNumber = 0;

    while (getline(input, line)) {
        lineNumber++;
        istringstream currLine(line);
        treeData data;
        currLine >> data.surname >> data.name >> data.patronymic >> data.gosNumber;

        if (stringCheck(data)) {
            cout << "Line " << lineNumber << ": Valid data - "
                 << data.surname << " " << data.name << " " << data.patronymic << " " << data.gosNumber << endl;
        } else {
            cout << "Line " << lineNumber << ": Invalid data - " << line << endl;
        }
    }

    input.close();
}

int main() {
    string filename = "C:\\Users\\godzi\\projects\\FundStructures\\input.txt";
    cout << "Reading data from file: " << filename << endl;
    readAndPrintData(filename);
    return 0;
}