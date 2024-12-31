#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

// Function to simulate FIFO page replacement algorithm
pair<int, vector<int>> fifoPageReplacement(const vector<int>& pages, int frameSize) {
    vector<int> frame;
    int pageFaults = 0;

    for (int page : pages) {
        if (find(frame.begin(), frame.end(), page) == frame.end()) {
            if (frame.size() < frameSize) {
                frame.push_back(page);
            } else {
                frame.erase(frame.begin());
                frame.push_back(page);
            }
            pageFaults++;
        }
    }
    return {pageFaults, frame};
}

// Function to simulate LRU page replacement algorithm
pair<int, vector<int>> lruPageReplacement(const vector<int>& pages, int frameSize) {
    vector<int> frame;
    unordered_map<int, int> recentUsage;
    int pageFaults = 0;
    int time = 0;

    for (int page : pages) {
        time++;
        if (find(frame.begin(), frame.end(), page) == frame.end()) {
            if (frame.size() < frameSize) {
                frame.push_back(page);
            } else {
                int lruPage = frame[0];
                for (int f : frame) {
                    if (recentUsage[f] < recentUsage[lruPage]) {
                        lruPage = f;
                    }
                }
                auto it = find(frame.begin(), frame.end(), lruPage);
                frame.erase(it);
                frame.push_back(page);
            }
            pageFaults++;
        }
        recentUsage[page] = time;
    }
    return {pageFaults, frame};
}

// Function to simulate Optimal page replacement algorithm
pair<int, vector<int>> optimalPageReplacement(const vector<int>& pages, int frameSize) {
    vector<int> frame;
    int pageFaults = 0;

    for (size_t i = 0; i < pages.size(); ++i) {
        int page = pages[i];
        if (find(frame.begin(), frame.end(), page) == frame.end()) {
            if (frame.size() < frameSize) {
                frame.push_back(page);
            } else {
                vector<int> futureUse(frame.size(), pages.size());
                for (size_t j = 0; j < frame.size(); ++j) {
                    for (size_t k = i + 1; k < pages.size(); ++k) {
                        if (frame[j] == pages[k]) {
                            futureUse[j] = k;
                            break;
                        }
                    }
                }
                int replaceIndex = distance(futureUse.begin(), max_element(futureUse.begin(), futureUse.end()));
                frame[replaceIndex] = page;
            }
            pageFaults++;
        }
    }
    return {pageFaults, frame};
}

int main() {
    vector<int> pages = {1, 2, 3, 4, 2, 1, 5, 2, 3, 4, 5};
    int frameSize = 3;

    // FIFO
    auto fifoResult = fifoPageReplacement(pages, frameSize);
    cout << "FIFO - Page Faults: " << fifoResult.first << " Final Frame: ";
    for (int page : fifoResult.second) cout << page << " ";
    cout << endl;

    // LRU
    auto lruResult = lruPageReplacement(pages, frameSize);
    cout << "LRU - Page Faults: " << lruResult.first << " Final Frame: ";
    for (int page : lruResult.second) cout << page << " ";
    cout << endl;

    // Optimal
    auto optimalResult = optimalPageReplacement(pages, frameSize);
    cout << "Optimal - Page Faults: " << optimalResult.first << " Final Frame: ";
    for (int page : optimalResult.second) cout << page << " ";
    cout << endl;

    return 0;
}
