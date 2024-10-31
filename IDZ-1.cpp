#include <iostream>
using namespace std;

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
    Node* root;

    void delete_next_element(Node * prev){
        if (root == nullptr) throw std::logic_error("delete element from empty list");

        if (prev -> next == root){
            if (root -> next == root)
            {
                delete root;
                root = nullptr;
                return;
            }

            prev->next = root -> next;
            delete root;
            root = prev -> next;
        }

        else 
        {
            Node* to_delete = prev -> next;
            prev -> next = prev -> next -> next;
            delete to_delete;
        }
    }

public:
    // Конструктор для инициализации списка
    List() {
        root = nullptr;
    }

    // Деструктор для освобождения памяти
    ~List() {
        clear();
    }

    // Метод для освобождения памяти
    void clear() {
        if (root == nullptr) return;

        Node* current = root->next;
        Node* next_node;

        while (current != root) {
            next_node = current -> next;
            delete current;
            current = next_node;
        }
        delete root;
        root = nullptr;
    }

    // Метод для добавления элемента в упорядоченный список по убыванию
    void add(int value) {
        Node* new_node = new Node(value, nullptr);
        
        if (root == nullptr) {
            root = new_node;
            root->next = root; 
            return;
        }

        Node* current = root;
        Node* prev = nullptr;

        do {
            if (current -> data < value) {
                break; 
            }
            prev = current;
            current = current -> next;
        } while (current != root);

        if (prev == nullptr) { 
            new_node -> next = root;
            Node* last = root;

            while (last -> next != root) {
                last = last->next;
            }
            last->next = new_node; 
            root = new_node; 
        } else { 
            new_node -> next = current;
            prev -> next = new_node;
        }
    }

    // Метод для удаления всех вхождений заданного элемента
    void deleteByValue(int value) {
    if (root == nullptr) return;
        Node* current = root;
        while (current -> next != root){
            if (current -> next -> data == value){
                delete_next_element(current);
            }
            else current = current -> next;
        }
        if (root -> data == value){
            delete_next_element(current);
        }
    }

    //метод для удаления элементов после каждого вхождения заданного 
        void deleteAfterValue(int value) {
        if (root == nullptr) return;

        Node* current = root;
        do{
            if (current -> data == value){
                Node* to_delete = current -> next;
                if (to_delete != root){
                    current -> next = to_delete -> next;
                    delete to_delete;
                }
            }
            current = current -> next;
        } while (current != root);
    }

    // Метод для поиска элемента по значению
    int SearchByValue(int value) const{
        if (root == nullptr) {
            cout << "\nnot a single occurrence "<< value << " was found";
            return 0;
        }

        Node* current = root;
        int count = 0;

        do {
            if (current -> data == value)
                count++;
            current = current -> next;
        } while (current != root);
        cout << "\n" << count << " occurrences with a value of " << value << " were found";
        return count;
    }

    // Метод для печати элементов списка
    void print() const {
        if (root == nullptr) {
            cout << "list empty\n";
            return;
        }

        Node* current = root;

        do{
            cout << current -> data << " ";
            current = current -> next;
        } while (current != root);
        
        cout << endl;
    }

    // Метод для симметрической разности двух списков
    List symmetric_difference(const List& other) const
    {
        List result;
        Node* curr1 = this -> root;
        Node* curr2 = other.root;
        
        if (curr1 == nullptr && curr2 == nullptr)
        {
            return result;
        } 
        
        else if (curr1 == nullptr)
        {
            do {
                result.add(curr2 -> data);
                curr2 = curr2 -> next;
            } while (curr2 != other.root);
            return result;
        }
        
        else if (curr2 == nullptr)
        {
            do {
                result.add(curr1 -> data);
                curr1 = curr1 -> next;
            } while (curr1 != this -> root);
            return result;
        }

        else 
        {    
            do {
                if (curr1 -> data > curr2 -> data)
                {
                    result.add(curr1 -> data);
                    curr1 = curr1 -> next;
                    if (curr1 == this -> root)
                    {
                        break;
                    }
                }
                else if (curr1 -> data < curr2 -> data)
                {
                    result.add(curr2 -> data);
                    curr2 = curr2 -> next;
                    if (curr2 == other.root)
                    {
                        break;
                    }
                }
                else 
                {
                    int value = curr1 -> data;
                    do {
                        curr1 = curr1 -> next;
                    } while (curr1 -> data == value);

                    do {
                        curr2 = curr2 -> next;
                    } while (curr2 -> data == value);

                    if (curr1 == this -> root || curr2 == other.root)
                    {
                        break;
                    }
                }

            } while (curr1 != this -> root || curr2 != other.root);
            
            if ((curr1 != this -> root && curr2 == other.root) || 
            (curr1 == this -> root && curr1 -> next == this -> root && curr2 == other.root))
            {
                do {
                    result.add(curr1 -> data);
                    curr1 = curr1 -> next;
                } while (curr1 != this -> root);
            }
            
            if ((curr1 == this -> root && curr2 != other.root) || 
            (curr2 == other.root && curr2 -> next == other.root && curr1 == this -> root))
            {
                do {
                    result.add(curr2 -> data);
                    curr2 = curr2 -> next;
                } while (curr2 != other.root);
            }
            return result;
        }
    }   
};


int main() {
    int input_choice, input_list, input_value;
    List list1, list2;

    while (input_choice != 7)
    {
        cout << "\nMENU:\n";
        cout << "Select a list (1/2) "; cin >> input_list; cout << "\n";
        cout << "1: Adding an element in descending order\n";
        cout << "2: Deleting all occurrences of a given\n";
        cout << "3: Deleting after each occurrence of a given\n";
        cout << "4: Searching for an element by value\n";
        cout << "5: Print\n";
        cout << "6: Symmetric difference\n";
        cout << "7: Shutdown\n";
        cout << "Your choice: "; cin >> input_choice; cout << "\n";
        switch(input_choice)
        {
            case 1:
            {
                cout << "You have selected Additions in descending order to the list_" << input_list << "\n";
                if (input_list == 1) 
                {
                    cout << "\nbefore - list_" << input_list << ": "; list1.print();
                    int quantity;
                    cout << "Enter the number of items to add: "; cin >> quantity;
                    for (int i = 0; i < quantity; i++){
                        cout << "\nEnter value: (" << i+1 << "): "; cin >> input_value;
                        list1.add(input_value);
                    }
                    cout << "\nafter - list_" << input_list << ": "; list1.print();
                } 
                else 
                {
                    cout << "\nbefore - list_" << input_list << ": "; list2.print();
                    int quantity;
                    cout << "Enter the number of items to add: "; cin >> quantity;
                    for (int i = 0; i < quantity; i++){
                        cout << "\nEneter value (" << i+1 << "): "; cin >> input_value;
                        list2.add(input_value);
                    }
                    cout << "\nafter - list_" << input_list << ": "; list2.print();
                }
                break;
            } 
            
            case 2: 
            {
                cout << "You have selected Deleting all occurrences of a given in the list_" << input_list;
                cout << "\nEneter value: "; cin >> input_value; cout << "\n";
                if (input_list == 1) 
                {
                    cout << "\nbefore - list_" << input_list << ": "; list1.print();
                    list1.deleteByValue(input_value);
                    cout << "\nafter - list_" << input_list << ": "; list1.print();
                } 
                else 
                {
                    cout << "\nbefore - list_" << input_list << ": "; list2.print();
                    list2.deleteByValue(input_value);
                    cout << "\nafter - list_" << input_list << ": "; list2.print();
                }
                break;
            } 
            
            case 3: 
            {
                cout << "You have selected Deleting after each occurrence of a given in the list_" << input_list;
                cout << "\nEneter value: "; cin >> input_value; cout << "\n";
                if (input_list == 1) 
                {
                    cout << "\nbefore - list_" << input_list << ": "; list1.print();
                    list1.deleteAfterValue(input_value);
                    cout << "\nafter - list_" << input_list << ": "; list1.print();
                } 
                else 
                {
                    cout << "\nbefore - list_" << input_list << ": "; list2.print();
                    list2.deleteAfterValue(input_value);
                    cout << "\nafter - list_" << input_list << ": "; list2.print();
                }
                break;  
            } 
            
            case 4: 
            {
                cout << "You have selected Searching for an element by value in the list_" << input_list;
                cout << "\nEneter value: "; cin >> input_value;
                if (input_list == 1) 
                {
                    cout << "\nlist_" << input_list << ": "; list1.print();
                    list1.SearchByValue(input_value);
                } 
                else 
                {
                    cout << "\nlist_" << input_list << ": "; list2.print();
                    list2.SearchByValue(input_value);
                }
                break;
            } 
            
            case 5: 
            {
                cout << "You have selected Print the list_" << input_list;
                if (input_list == 1) 
                {
                    cout << "\nlist_1: ";
                    list1.print();
                } 
                else 
                {
                    cout << "\nlist_2: ";
                    list2.print();
                } 
                break;
            } 
            
            case 6: 
            {
                cout << "You have selected the symmetric difference between lists 1 and 2\n";
                cout << "\nlist_" << input_list << ": "; list1.print();
                cout << "\nlist_" << input_list << ": "; list2.print();
                List difference_list = list1.symmetric_difference(list2);
                cout << "\ndifference_list: "; difference_list.print();
                break;
            }
            
            case 7: 
            {
                cout << "turning off the program\n";
                break;
            } 
            
            default:
            {
                cout << "Error";
                break;
            } 
        }
    }  
    return 0;
} 