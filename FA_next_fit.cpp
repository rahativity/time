#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n;
    cout << "Enter number of memory blocks: ";
    cin >> n;

    vector<int> memory(n);
    for (int i = 0; i < n; i++) {
        cout << "Enter size of block " << (i + 1) << ": ";
        cin >> memory[i];
    }

    
    while (true) {
        int size;
        cout << "\nEnter size needed (0 to exit): ";
        cin >> size;
        
        if (size == 0) {
            break;
        }
        
        int lastIndex = 0;
        bool allocated = false;
        // Start scanning from the last allocated block
        for (int count = 0; count < n; count++) {
            int i = (lastIndex + count) % n;
            if (memory[i] >= size) {
                memory[i] -= size;
                cout << "Allocated in block " << (i + 1) << "\n";
                lastIndex = i;
                allocated = true;
                break;
            }
        }

        if (!allocated) {
            cout << "No suitable block found\n";
        }
    }

    return 0;
}
