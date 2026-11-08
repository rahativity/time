#include <iostream>
#include <vector>

using namespace std;

#define ll long long
#define vi vector<int>
#define vll vector<long long>
#define pb push_back
#define all(x) (x).begin(), (x).end()

int main() {
    int n;
    cout << "Enter number of memory blocks: ";
    cin >> n;

    vi memory(n);
    for (int i = 0; i < n; i++) {
        cout << "Enter size of block " << (i + 1) << ": ";
        cin >> memory[i];
    }

    while (1) {
        int size, worstIndex = -1;
        cout << "\nEnter size needed (0 to exit): ";
        cin >> size;

        if (size == 0) break;

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
