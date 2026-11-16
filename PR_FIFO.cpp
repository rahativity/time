#include <iostream>
#include <vector>

using namespace std;

// Function to check if a page exists in frames
bool is_exist(const vector<int>& frames, int frame_count, int page) {
    for (int i = 0; i < frame_count; i++) {
        if (frames[i] == page) {
            return true;
        }
    }
    return false;
}

int main() {
    int n, frame_count;
    int page_faults = 0, pos = 0;

    cout << "Enter the total number of pages: ";
    cin >> n;

    cout << "Enter the number of frames: ";
    cin >> frame_count;

    vector<int> pages(n);
    cout << "Enter the page numbers (separated by space): ";
    for (int i = 0; i < n; i++) {
        cin >> pages[i];
    }

    // Initialize all frames to -1 (empty)
    vector<int> frames(frame_count, -1);

    cout << "\nPage Replacement Process:\n";

    for (int i = 0; i < n; i++) {
        if (!is_exist(frames, frame_count, pages[i])) {
            // If page is not in frames, replace using FIFO
            frames[pos] = pages[i];
            pos = (pos + 1) % frame_count;
            page_faults++;

            // Display current state of frames
            cout << "After inserting page " << pages[i] << ": ";
            for (int j = 0; j < frame_count; j++) {
                if (frames[j] == -1) {
                    cout << "[ ] ";
                } else {
                    cout << "[" << frames[j] << "] ";
                }
            }
            cout << "\n";
        }
    }

    cout << "\nTotal Page Faults = " << page_faults << "\n";

    return 0;
}
