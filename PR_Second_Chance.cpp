#include <bits/stdc++.h>

using namespace std;

// Function to check if a page exists in frames
int is_exist(const vector<int>& frames, int frame_count, int page) {
    for (int i = 0; i < frame_count; i++) {
        if (frames[i] == page) {
            return i; // Return position if page found
        }
    }
    return -1; // Page not found
}

int main() {
    int n, frame;
    int pagefault = 0;
    int pointer = 0;

    cout << "Enter the total number of pages: ";
    cin >> n;

    cout << "Enter the number of frames: ";
    cin >> frame;

    vector<int> page(n);
    cout << "Enter the page numbers (separated by space): ";
    for (int i = 0; i < n; i++) {
        cin >> page[i];
    }

    // Initialize all frames and reference bits
    vector<int> frames(frame, -1);
    vector<int> reference(frame, 0);

    cout << "\nSecond Chance Page Replacement Process:\n";

    for (int i = 0; i < n; i++) {
        int pos = is_exist(frames, frame, page[i]);

        if (pos != -1) {
            // Page hit: give second chance
            reference[pos] = 1;
        } else {
            // Page fault: find a frame with reference bit 0
            while (reference[pointer] == 1) {
                reference[pointer] = 0;
                pointer = (pointer + 1) % frame;
            }

            // Replace the page
            frames[pointer] = page[i];
            reference[pointer] = 0;
            pointer = (pointer + 1) % frame;
            pagefault++;
        }

        // Display frames
        cout << "After inserting page " << page[i] << ": ";
        for (int j = 0; j < frame; j++) {
            if (frames[j] == -1) {
                cout << "[ ] ";
            } else {
                cout << "[" << frames[j] << "] ";
            }
        }
        cout << "\n";
    }

    cout << "\nTotal Page Faults = " << pagefault << "\n";

    return 0;
}
