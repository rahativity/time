#include <bits/stdc++.h>

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

        // Find the largest block that is large enough
        int worstIndex = -1;
        for (int i = 0; i < n; i++) {
            if (memory[i] >= size) {
                if (worstIndex == -1 || memory[i] > memory[worstIndex]) {
                    worstIndex = i;
                }
            }
        }

        if (worstIndex != -1) {
            memory[worstIndex] -= size;
            cout << "Allocated in block " << (worstIndex + 1) << "\n";
        } else {
            cout << "No suitable block found\n";
        }
    }

    return 0;
}
