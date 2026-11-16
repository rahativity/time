#include <iostream>
#include <vector>

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

// Function to find the optimal page to replace
int find_optimal(const vector<int>& frames, int frame_count, const vector<int>& pages, int n, int index) {
    int farthest = index;
    int pos = -1;

    for (int i = 0; i < frame_count; i++) {
        int j;
        for (j = index; j < n; j++) {
            if (frames[i] == pages[j]) {
                if (j > farthest) {
                    farthest = j;
                    pos = i;
                }
                break;
            }
        }

        // If the page in frame[i] is never used again in the future
        if (j == n) {
            return i;
        }
    }

    // If all pages are used in future, replace the one used farthest away
    if (pos == -1) {
        return 0;
    }
    return pos;
}

int main() {
    int n, frame;
    int pagefault = 0;

    cout << "Enter the total number of pages: ";
    cin >> n;

    cout << "Enter the number of frames: ";
    cin >> frame;

    vector<int> page(n);
    cout << "Enter the page numbers (separated by space): ";
    for (int i = 0; i < n; i++) {
        cin >> page[i];
    }

    // Initialize all frames to -1 (empty)
    vector<int> frames(frame, -1);

    cout << "\nOptimal Page Replacement Process:\n";

    for (int i = 0; i < n; i++) {
        int pos = is_exist(frames, frame, page[i]);

        if (pos != -1) {
            // Page hit: do nothing
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
            } else {
                int optimal_pos = find_optimal(frames, frame, page, n, i + 1);
                frames[optimal_pos] = page[i];
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

