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

    int lastIndex = 0;

    while (1) {
        int size, allocated = 0;
        cout << "\nEnter size needed (0 to exit): ";
        cin >> size;

        if (size == 0) break;

        for (int count = 0; count < n; count++) {
            int i = (lastIndex + count) % n;
            if (memory[i] >= size) {
                memory[i] -= size;
                cout << "Allocated in block " << (i + 1) << "\n";
                lastIndex = i;
                allocated = 1;
                break;
            }
        }

        if (!allocated)
            cout << "No suitable block found\n";
    }

    return 0;
}
