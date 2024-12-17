#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

using namespace std;

//Вспомогательные для проверок 
bool isString(const string& inputString)
{
    if (!(isupper(inputString[0]) && isalpha(inputString[0])))
    {
        return false;
    }
    if (inputString.length() <= 1)
    {
        return false;
    }
    for (int i = 1; i < inputString.length(); i++)
    {
        if (!isalpha(inputString[i]))
        {
            return false;
        }
        if (!islower(inputString[i]))
        {
            return false;
        }
    }

    return true;
}

bool isGosNumber(const string& inputString)
{
    if (inputString.length() != 10)
    {
        return false;
    }
    
    for (char ch : inputString)
    {
        if (!isdigit(ch))
        {
            return false;
        }

    }

    return true;
}

void cinError()
{
    if (cin.fail())
    {
        cin.clear();
        cin.ignore(100, '\n');
    }
}

//Односвязный кольцевой список повторов

struct Node {
    int data;
    Node* next;

    Node(int value, Node* next_node)
    {
        data = value;
        next = next_node;
    }
};

class List {
private:
    Node* head = nullptr;

    void DeleteNextElement(Node* prev){
        if (head == nullptr) throw logic_error("delete element from empty list");

        if (prev -> next == head){
            if (head -> next == head)
            {
                delete head;
                head = nullptr;
                return;
            }

            prev -> next = head -> next;
            delete head;
            head = prev -> next;
        }

        else 
        {
            Node* to_delete = prev -> next;
            prev  ->  next = prev -> next -> next;
            delete to_delete;
        }
    }


public:

    //Добавление элемента (по убыванию)
    void add(int value) {
        Node* new_node = new Node(value, nullptr);
        
        if (head == nullptr) {
            head = new_node;
            head -> next = head; 
            return;
        }

        Node* current = head;
        Node* prev = nullptr;

        do {
            if (current  ->  data < value) 
            {
                break; 
            }
            prev = current;
            current = current  ->  next;
        } while (current != head);

        if (prev == nullptr) { 
            new_node  ->  next = head;
            Node* last = head;

            while (last  ->  next != head) 
            {
                last = last -> next;
            }
            last -> next = new_node; 
            head = new_node; 
        } else { 
            new_node  ->  next = current;
            prev  ->  next = new_node;
        }
    }


    // Удаление по значению
    void deleteByValue(int value) 
    {
        if (head == nullptr) return;
            Node* current = head;
            while (current  ->  next != head){
                if (current  ->  next  ->  data == value){
                    DeleteNextElement(current);
                }
                else current = current  ->  next;
            }
            if (head  ->  data == value){
                DeleteNextElement(current);
            }
    }

    // Подсчет элементов в списке
    int countList() const
    {
        if (head == nullptr)
        {
            return 0;
        }

        int count = 1;

        Node* temp = head;
        while (temp -> next != head) {
            temp = temp -> next;
            count++;
        }
        return count;
    }

    // Метод для печати элементов списка
    void Print() const {
        if (head == nullptr) {
            cout << "list empty\n";
            return;
        }

        Node* current = head;

        do
        {
            cout << current -> data << " ";
            current = current -> next;
        } while (current != head);
        
        cout << endl;
    }

    // Функция возвращающая голову списка
    Node* getHead()
    {
        return head;
    }

    // Функция возвращающая дату из списка
    int getData()
    {
        return head -> data;
    }
};

//АВЛ дерево

// Структура ключа дерева
struct treeData
{
    string gosNumber;
    string surname;
    string name;
    string patronymic;

    bool operator < (const treeData& key) const
    {
        if (gosNumber != key.gosNumber)
        {
            return gosNumber < key.gosNumber;
        }
        if (name != key.name)
        {
            return name < key.name;
        }
        if (surname != key.surname)
        {
            return surname < key.surname;
        }
        if (patronymic != key.patronymic)
        {
            return patronymic < key.patronymic;
        }

        return false;
    }

    bool operator == (const treeData& key) const
    {
        return ((gosNumber == key.gosNumber) && (surname == key.surname) &&
            (name == key.name) && (gosNumber == key.gosNumber));
    }
};

// Структура Авл дерева
struct AVLTree
{
    treeData key;
    int balanceFactor;
    AVLTree* right;
    AVLTree* left;
    List currList;

    AVLTree(treeData data, int value)
    {
        key = data;
        balanceFactor = 0;
        right = nullptr;
        left = nullptr;
        currList.add(value);
    }
};

// Добавление элемента по Вирту
void add(AVLTree*& root,const treeData& key, bool& height, int& value) 
{
    AVLTree *p1, *p2;

    // Вставка
    if (root == nullptr)
    {
        root = new AVLTree(key,value);
        height = true;
    }
    else if (key < root -> key) 
    {
        add(root -> left, key, height, value);
        if (height) // Выросла левая ветвь
        { 
            if (root -> balanceFactor == 1) 
            {
                root -> balanceFactor = 0;
                height = false;
            }
            else if (root -> balanceFactor == 0) 
            {
                root -> balanceFactor = -1;
            }
            else // Восстановление баланса
            {
                p1 = root -> left;
                if (p1 -> balanceFactor == -1) // Одинарная LL-ротация
                { 
                    root -> left = p1 -> right;
                    p1 -> right = root;
                    root -> balanceFactor = 0;
                    root = p1;
                }
                else // Двойная LR-ротация
                { 
                    p2 = p1 -> right;
                    p1 -> right = p2 -> left;
                    p2 -> left = p1;
                    root -> left = p2 -> right;
                    p2 -> right = root;
                    if (p2 -> balanceFactor == -1)
                    {
                        root -> balanceFactor = 1;
                    }
                    else
                    {
                        root -> balanceFactor = 0;
                    }
                    if (p2 -> balanceFactor == 1)
                    {
                        p1 -> balanceFactor = -1;
                    }
                    else
                    {
                        p1 -> balanceFactor = 0;
                    }
                    root = p2;
                }
                root -> balanceFactor = 0;
                height = false;
            }
        }
    }
    else if (root -> key < key) 
    {
        add(root -> right,key, height, value);

        if (height) // Выросла правая ветвь
        { 
            if (root -> balanceFactor == -1) 
            {
                root -> balanceFactor = 0;
                height = false;
            }
            else if (root -> balanceFactor == 0) 
            {
                root -> balanceFactor = 1;
            }
            else // Восстановление баланса
            { 
                p1 = root -> right;
                if (p1 -> balanceFactor == 1) // Одинарная RR-ротация
                {
                    root -> right = p1 -> left;
                    p1 -> left = root;
                    root -> balanceFactor = 0;
                    root = p1;
                }
                else // Двойная RL-ротация
                { 
                    p2 = p1 -> left;
                    p1 -> left = p2 -> right;
                    p2 -> right = p1;
                    root  -> right = p2 -> left;
                    p2 -> left = root;
                    if (p2 -> balanceFactor == 1)
                    {
                        root -> balanceFactor = -1;
                    }
                    else
                    {
                        root -> balanceFactor = 0;
                    }
                    if (p2 -> balanceFactor == -1)
                    {
                        p1 -> balanceFactor = 1;
                    }
                    else
                    {
                        p1 -> balanceFactor = 0;
                    }
                    root = p2;
                }
                root -> balanceFactor = 0;
                height = false;
            }
        }
    }
    else if (root -> key == key) // Ключ уже существует
    {
        root -> currList.add(value);
        height = false;
    }
}

// Балансировка левого поддерева по Вирту
void balanceLeft(AVLTree*& root, bool& height)
{
    AVLTree *p1, *p2;

    if (root -> balanceFactor == -1)
    {
        root -> balanceFactor = 0;
    }
    else if (root -> balanceFactor == 0)
    {
        root -> balanceFactor = 1; 
        height = false;
    }
    else // Восстановление баланса
    {
        p1 = root -> right;
        if (p1 -> balanceFactor >= 0) // Одиночная RR-ротация
        {
            root -> right = p1 -> left;
            p1 -> left = root;
            if (p1 -> balanceFactor == 0)
            {
                root -> balanceFactor = 1;
                p1 -> balanceFactor = -1;
                height = false;
            }
            else
            {
                root -> balanceFactor = 0;
                p1 -> balanceFactor = 0;
            }
            root = p1;
        }
        else // Двойная RL-ротация
        {
            p2 = p1 -> left;
            p1 -> left = p2 -> right;
            p2 -> right = p1;
            root -> right = p2 -> left;
            p2 -> left = root;
            if (p2 -> balanceFactor == 1)
            {
                root -> balanceFactor = -1;
            }
            else
            {
                root -> balanceFactor = 0;
            }
            if (p2 -> balanceFactor == -1)
            {
                p1 -> balanceFactor = 1;
            }
            else
            {
                p1 -> balanceFactor = 0;
            }
            root = p2;
            p2 -> balanceFactor = 0;
        }
    }
}

// Балансировка правого поддерева по Вирту
void balanceRight(AVLTree*& root, bool& height)
{
    AVLTree* p1, * p2;

    if (root -> balanceFactor == 1)
    {
        root -> balanceFactor = 0;
    }
    else if (root -> balanceFactor == 0)
    {
        root -> balanceFactor = -1;
        height = false;
    }
    else // Восстановление баланса
    {
        p1 = root -> left;
        if (p1 -> balanceFactor <= 0) // Одиночная LL-ротация
        {
            root -> left = p1 -> right;
            p1 -> right = root;
            if (p1 -> balanceFactor == 0)
            {
                root -> balanceFactor = -1;
                p1 -> balanceFactor = 1;
                height = false;
            }
            else
            {
                root -> balanceFactor = 0;
                p1 -> balanceFactor = 0;
            }
            root = p1;
        }
        else // Двойная LR-ротация
        {
            p2 = p1 -> right;
            p1 -> right = p2 -> left;
            p2 -> left = p1;
            root -> left = p2 -> right;
            p2 -> right = root;
            if (p2 -> balanceFactor == -1)
            {
                root -> balanceFactor = 1;
            }
            else
            {
                root -> balanceFactor = 0;
            }
            if (p2 -> balanceFactor == 1)
            {
                p1 -> balanceFactor = - 1;
            }
            else
            {
                p1 -> balanceFactor = 0;
            }
            root = p2;
            p2 -> balanceFactor = 0;
        }
    }
}

// Функция поиска наибольшего слева элемента по Вирту
AVLTree* findMax(AVLTree*& root, bool& height)
{

    if (root -> right != nullptr) 
    {
        AVLTree* r = findMax(root -> right, height);
        if (height) 
        {
            balanceRight(root, height);
        }
        return r;
    }
    else 
    {
        AVLTree* q;
        q = root;
        root = root -> left;
        height = true;
        return q;
    }
}

// Функция удаления узла по Вирту
void deleteNode(AVLTree*& root,const treeData& key, bool& height)
{
    if (root == nullptr)
    {
        return;
    }

    int stringNumber = root -> currList.getData();

    if (key < root -> key)
    {
        deleteNode(root -> left, key, height);
        {
            if (height)
            {
                balanceLeft(root, height);
            }
        }
    }
    else if (root -> key < key)
    {
        deleteNode(root -> right, key, height);
        if (height)
        {
            balanceRight(root, height);
        }
    }
    else
    {
        if (root -> currList.countList() > 1)
        {
            root -> currList.deleteByValue(stringNumber);
            return;
        }
        AVLTree* q = root;
        if (root -> right == nullptr)
        {
            root = root -> left;
            height = true;
        }
        else if (root -> left == nullptr)
        {
            root = root -> right;
            height = true;
        }
        else
        {   
            q = findMax(root -> left, height);
            root -> key = q -> key;
            root -> currList = q -> currList;
            if (height)
            {
                balanceLeft(root, height);
            }
        }
    }
}

// Поиск элементов по заданному ключу
void searchData(AVLTree*& root, const treeData& key)
{
    if (root == nullptr)
    {
        cout << "\nУзел не найден!\n";
        return;
    }
    else if (key == root -> key)
    {
        cout << "\nУзел найден!\n";
        return;
    }
    if (key < root -> key)
    {
        searchData(root -> left, key);
    }
    else if (root -> key < key)
    {
        searchData(root -> right, key);
    }
}

// Очистка дерева
void clearTree(AVLTree*& root, int& value)
{
    if (root == nullptr)
    {
        return;
    }

    clearTree(root -> right, value);
    clearTree(root -> left, value);
    delete root;
    root = nullptr;
    value = 0;
}

// Проверка входных данных
bool stringCheck(treeData& tree)
{
    if (tree.name.length() <= 1 || tree.surname.length() <= 1
        || tree.patronymic.length() <= 1 || tree.gosNumber.length() != 10)
    {
        return false;
    }
    if (!isString(tree.name))
    {
        return false;
    }
    if (!isString(tree.surname))
    {
        return false;
    }
    if (!isString(tree.patronymic))
    {
        return false;
    }

    if (!isGosNumber(tree.gosNumber))
    {
        return false;
    }
    return true;
}

// Получение данных из файла
void ImportFile(AVLTree*& root, const string& filename, int& value, bool& height)
{
    ifstream input(filename);
    if (!input.is_open())
    {
        cout << "\n !!!ОШИБКА!!! Файл не может быть открыт!\n\n";
        return;
    }

    string current;

    while (getline(input, current))
    {
        istringstream currLine(current);
        treeData data;
        currLine >> data.surname >> data.name >> data.patronymic >> data.gosNumber;
        if (stringCheck(data))
        {
            add(root, data, height, ++value);
        }
        else
        {
            value++;
        }
    }
    input.close();
}

// Вывод в файл
void ExportFile(AVLTree*& root, ofstream& file_output)
{
    if (root == nullptr)
    {
        return;
    }
    ExportFile(root -> left, file_output);

    Node* temp = root -> currList.getHead();

    do
    {
        if (temp -> next != root -> currList.getHead())
        {
            file_output << temp -> data << ", ";
        }
        else
        {
            file_output << temp -> data << " | ";
        }
        temp = temp -> next;
    } while (temp != root -> currList.getHead());

    file_output << root -> key.surname << " " << root -> key.name << " " << root -> key.patronymic << " " << root -> key.gosNumber << "\n";

    ExportFile(root -> right, file_output);
}

// Функция создания ключа
treeData createKey()
{
    treeData key;

    bool flag = true;

    while (flag)
    {
        cout << "Введите Фамилию: ";
        cin >> key.surname;
        if (isString(key.surname))
        {
            flag = false;
        }
        else
        {
            cout << "\n!!! ОШИБКА !!!  Некорректная Фамилия!\n\n";
        }
    }

    flag = true;

    while (flag)
    {
        cout << "Введите Имя: ";
        cin >> key.name;
        if (isString(key.name))
        {
            flag = false;
        }
        else
        {
            cout << "\n !!!ОШИБКА!!! Неккоректное Имя!\n\n";
        }
    }

    flag = true;

    while (flag)
    {
        cout << "Введите Отчество: ";
        cin >> key.patronymic;
        if (isString(key.patronymic))
        {
            flag = false;
        }
        else
        {
            cout << "\n !!!Ошибка!!! Некорректное Отчество!\n\n";
        }
    }

    flag = true;

    while (flag)
    {
        cout << "Введите Госномер: ";
        cin >> key.gosNumber;
        if (isGosNumber(key.gosNumber))
        {
           flag = false;
        }
        else 
        {
            cout << "\n !!!ОШИБКА!!! Некорректный Госномер!\n";
        }
    }
    return key;
}

// Обход справа - налево
void rightLeftOrder(AVLTree*& root, ofstream& file)
{
    if (root == nullptr)
    {
        return;
    }

    rightLeftOrder(root -> right, file);

    cout << root -> key.surname << " " << root -> key.name << " " << root -> key.patronymic << " #"
        << root -> key.gosNumber << endl;

    file << root -> key.surname << " " << root -> key.name << " " << root -> key.patronymic << " #"
        << root -> key.gosNumber << endl;

    rightLeftOrder(root -> left, file);
}

// Вспомогательная функция для печати узла
void printTreeHelper(AVLTree* root, int indent = 0)
{
    Node* temp = root -> currList.getHead();

    if (root != nullptr)
    {
        if (root -> right != nullptr) 
        {
            printTreeHelper(root -> right, indent + 4);
        }

        if (indent > 0) 
        {
            cout << setw(indent) << ' ';
        }


        cout << root -> key.surname << " " << root -> key.name
            << " " << root -> key.patronymic << " #" << root -> key.gosNumber << " | (" << root -> balanceFactor << ") | [";

        do
        {
            if (temp -> next != root -> currList.getHead())
            {
                cout << temp -> data << ", ";
            }
            else
            {
                cout << temp -> data << "]\n";
            }
            temp = temp -> next;
        } while (temp != root -> currList.getHead());

        if (root -> left != nullptr) 
        {
            printTreeHelper(root -> left, indent + 4);
        }
    }
}

// Основная функция для печати дерева
void printTree(AVLTree* root)
{
    if (root == nullptr)
    {
        cout << "Дерево пустое!\n";
        return;
    }
    printTreeHelper(root);
}


int main()
{
    ofstream output;
    output.open("output.txt");
    int answer = 0;
    bool height;
    string filename = "C:\\Users\\godzi\\projects\\FundStructures\\input.txt";
    AVLTree* root = nullptr;
    int value = 0;
    while (answer != 9)
    {
        cout << "______________________________________________\n";
        cout << "|                   |МЕНЮ|                   |\n";
        cout << "|1 - Добавить элемент                        |\n";
        cout << "|2 - Распечатка дерева                       |\n";
        cout << "|3 - Найти 1 элемент по ключу                |\n";
        cout << "|4 - Удалить 1 элемент по ключу              |\n";
        cout << "|5 - Импорт из файла                         |\n";
        cout << "|6 - Экспорт в файл                          |\n";
        cout << "|7 - Печать обхода справа-налево             |\n";
        cout << "|8 - Удаление всего дерева                   |\n";
        cout << "|9 - ВЫХОД                                   |\n";
        cout << "|____________________________________________|\n";
    
        cout << "\nВаш выбор: ";
        cin >> answer;
        treeData new_node;
        switch (answer)
        {
        case 1:
        {
            value++;
            add(root, createKey(), height, value);
            cout << endl;
            break;
        }
        case 2:
        {
            cout << "__________________________________________________________________________\n";
            cout << "| Фамилия Имя Отчество Госномер (Баланс узла) [Строки в списке повторов] |\n";
            cout << "--------------------------------------------------------------------------\n";
            cout << "                   Дерево: \n\n";
            printTree(root);
            cout << "\n";
            break;
        }
        case 3:
        {
            searchData(root, createKey());
            cout << "\n";
            break;
        }
        case 4:
        {
            deleteNode(root, createKey(), height);
            cout << "\n";
            break;
        }
        case 5:
        {
            cout << "Данные из файла успешно имортированы!\n\n";
            ImportFile(root, filename, value, height);
            cout << "\n";
            break;
        }
        case 6:
        {
            cout << "Данные в файл успешно эскпортированы!\n\n";
            ExportFile(root, output);
            cout << endl;
            break;
        }
        case 7:
        {
            cout << "Обход справа-налево\n\n ";
            rightLeftOrder(root, output);
            cout << "\nЭкспорт успешен!\n\n";

            break;
        }
        case 8:
        {
            cout << "Дерево успешно удалено!\n";
            clearTree(root, value);
            value = 0;
            cout << "\n";
            break;
        }
        case 9:
        {
            cout << "\nПрограмма завершила работу!\n";
            break;
        }
        default:
        {
            cinError();
            cout << "\n !!!ОШИБКА! Некорректный ввод!\n\n";
            break;

        }
        }
    }
    output.close();
}