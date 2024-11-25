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

    void DeleteNextElement(Node* prev){
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

    bool is_prime(int num) {
        if (num == 1 || num == 0) return false; 
        
        for (int i = 2; i * i <= num; i++) 
        {
            if (num % i == 0) return false; 
        }
        return true; 
    }

public:
    // Конструктор для инициализации списка
    List() {
        root = nullptr;
    }

    // Деструктор для освобождения памяти
    ~List() {
        Clear();
    }

    // Метод для освобождения памяти
    void Clear() {
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
    void Add(int value) {
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
    void DeleteByValue(int value) {
    if (root == nullptr) return;
        Node* current = root;
        while (current -> next != root){
            if (current -> next -> data == value){
                DeleteNextElement(current);
            }
            else current = current -> next;
        }
        if (root -> data == value){
            DeleteNextElement(current);
        }
    }

    //метод для удаления элементов после каждого вхождения заданного 
        void DeleteAfterValue(int value) {
        if (root == nullptr) return;

        Node* current = root;
        do{
            if (current -> data == value){
                DeleteNextElement(current);
            }
            current = current -> next;
        } while (current != root);
    }

    // Метод для поиска элемента по значению
    int SearchByValue(int value) const{
        if (root == nullptr) {
            cout << "\nEmpty list!";
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
    void Print() const {
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
    List SymmetricDifference(const List& other) const
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
                result.Add(curr2 -> data);
                curr2 = curr2 -> next;
            } while (curr2 != other.root);
            return result;
        }
        
        else if (curr2 == nullptr)
        {
            do {
                result.Add(curr1 -> data);
                curr1 = curr1 -> next;
            } while (curr1 != this -> root);
            return result;
        }

        else 
        {    
            do {
                if (curr1 -> data > curr2 -> data)
                {
                    result.Add(curr1 -> data);
                    int value = curr1 -> data;
                    do {
                        curr1 = curr1 -> next;
                    } while(curr1 -> data == value);
                    if (curr1 == this -> root)
                    {
                        break;
                    }
                }
                else if (curr1 -> data < curr2 -> data)
                {
                    result.Add(curr2 -> data);
                    int value = curr2 -> data;
                    do {
                        curr2 = curr2 -> next;
                    } while (curr2 -> data == value);
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
                    result.Add(curr1 -> data);
                    curr1 = curr1 -> next;
                } while (curr1 != this -> root);
            }
            
            if ((curr1 == this -> root && curr2 != other.root) || 
            (curr2 == other.root && curr2 -> next == other.root && curr1 == this -> root))
            {
                do {
                    result.Add(curr2 -> data);
                    curr2 = curr2 -> next;
                } while (curr2 != other.root);
            }
            return result;
        }
    }  

   
    List CreatePrimeList() {
        List prime_list; 
        Node* current = root;

        if (root == nullptr) return prime_list;

        do {
            int value = current->data; 
            int prime_value = -1; 

            for (int i = value - 1; i > 1; i--) { 
                if (is_prime(i)) {
                    prime_value = i; 
                    break; 
                }
            }

            prime_list.Add(prime_value); 
            current = current->next; 
        } while (current != root);

        return prime_list; 
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
        cout << "7: Prime list\n";
        cout << "8: Shutdown\n";
        cout << "Your choice: "; cin >> input_choice; cout << "\n";
        switch(input_choice)
        {
            case 1:
            {
                cout << "You have selected Additions in descending order to the list_" << input_list << "\n";
                if (input_list == 1) 
                {
                    cout << "\nbefore - list_" << input_list << ": "; list1.Print();
                    int quantity;
                    cout << "Enter the number of items to Add: "; cin >> quantity;
                    for (int i = 0; i < quantity; i++){
                        cout << "\nEnter value: (" << i+1 << "): "; cin >> input_value;
                        list1.Add(input_value);
                    }
                    cout << "\nafter - list_" << input_list << ": "; list1.Print();
                } 
                else 
                {
                    cout << "\nbefore - list_" << input_list << ": "; list2.Print();
                    int quantity;
                    cout << "Enter the number of items to Add: "; cin >> quantity;
                    for (int i = 0; i < quantity; i++){
                        cout << "\nEneter value (" << i+1 << "): "; cin >> input_value;
                        list2.Add(input_value);
                    }
                    cout << "\nafter - list_" << input_list << ": "; list2.Print();
                }
                break;
            } 
            
            case 2: 
            {
                cout << "You have selected Deleting all occurrences of a given in the list_" << input_list;
                cout << "\nEneter value: "; cin >> input_value; cout << "\n";
                if (input_list == 1) 
                {
                    cout << "\nbefore - list_" << input_list << ": "; list1.Print();
                    list1.DeleteByValue(input_value);
                    cout << "\nafter - list_" << input_list << ": "; list1.Print();
                } 
                else 
                {
                    cout << "\nbefore - list_" << input_list << ": "; list2.Print();
                    list2.DeleteByValue(input_value);
                    cout << "\nafter - list_" << input_list << ": "; list2.Print();
                }
                break;
            } 
            
            case 3: 
            {
                cout << "You have selected Deleting after each occurrence of a given in the list_" << input_list;
                cout << "\nEneter value: "; cin >> input_value; cout << "\n";
                if (input_list == 1) 
                {
                    cout << "\nbefore - list_" << input_list << ": "; list1.Print();
                    list1.DeleteAfterValue(input_value);
                    cout << "\nafter - list_" << input_list << ": "; list1.Print();
                } 
                else 
                {
                    cout << "\nbefore - list_" << input_list << ": "; list2.Print();
                    list2.DeleteAfterValue(input_value);
                    cout << "\nafter - list_" << input_list << ": "; list2.Print();
                }
                break;  
            } 
            
            case 4: 
            {
                cout << "You have selected Searching for an element by value in the list_" << input_list;
                cout << "\nEneter value: "; cin >> input_value;
                if (input_list == 1) 
                {
                    cout << "\nlist_" << input_list << ": "; list1.Print();
                    list1.SearchByValue(input_value);
                } 
                else 
                {
                    cout << "\nlist_" << input_list << ": "; list2.Print();
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
                    list1.Print();
                } 
                else 
                {
                    cout << "\nlist_2: ";
                    list2.Print();
                } 
                break;
            } 
            
            case 6: 
            {
                cout << "You have selected the symmetric difference between lists 1 and 2\n";
                cout << "\nlist_1: "; list1.Print();
                cout << "\nlist_2: "; list2.Print();
                List difference_list = list1.SymmetricDifference(list2);
                cout << "\ndifference_list: "; difference_list.Print();
                break;
            }
            
            case 7:
            {
                cout << "You have selected create the Prime_list from list_" << input_list;
                if (input_list == 1) 
                {
                    cout << "\nlist_1: "; list1.Print();
                    List prime_list = list1.CreatePrimeList();
                    cout << "\prime_list: "; prime_list.Print();
                } 
                else 
                {
                    cout << "\nlist_2: "; list2.Print();
                    List prime_list = list2.CreatePrimeList();
                    cout << "\prime_list: "; prime_list.Print();
                } 
                break;
            }

            case 8: 
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