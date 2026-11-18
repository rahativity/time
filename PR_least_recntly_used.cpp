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

// Function to find the least recently used page
int find_lru(const vector<int>& time, int frame_count) {
    int min_time = time[0];
    int pos = 0;
    for (int i = 1; i < frame_count; i++) {
        if (time[i] < min_time) {
            min_time = time[i];
            pos = i;
        }
    }
    return pos;
}

int main() {
    int n, frame;
    int pagefault = 0, counter = 0;

    cout << "Enter the total number of pages: ";
    cin >> n;

    cout << "Enter the number of frames: ";
    cin >> frame;

    vector<int> page(n);
    cout << "Enter the page numbers (separated by space): ";
    for (int i = 0; i < n; i++) {
        cin >> page[i];
    }

    // Initialize all frames and times
    vector<int> frames(frame, -1);
    vector<int> time(frame, 0);

    cout << "\nLeast Recently Used (LRU) Page Replacement Process:\n";

    for (int i = 0; i < n; i++) {
        int pos = is_exist(frames, frame, page[i]);

        if (pos != -1) {
            // Page hit: update access time
            counter++;
            time[pos] = counter;
        } else {
            // Page fault: check for an empty frame first
            int empty = -1;
            for (int j = 0; j < frame; j++) {
                if (frames[j] == -1) {
                    empty = j;
                    break;
                }
            }

            if (empty != -1) {
                frames[empty] = page[i];
                counter++;
                time[empty] = counter;
            } else {
                int lru_pos = find_lru(time, frame);
                frames[lru_pos] = page[i];
                counter++;
                time[lru_pos] = counter;
            }
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

