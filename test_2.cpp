#include <iostream>
using namespace std;

    bool is_prime(int num) {
        if (num == 1 || num == 0) return false; 
        for (int i = 2; i * i <= num; i++) {
            cout << i << "\n";
            if (num % i == 0) 
            {
                cout << "FAIL " << i << "\n";
                return false; 
            }
        }
        return true; 
    }

int main(){
    cout << is_prime(997);
    return 0;
}