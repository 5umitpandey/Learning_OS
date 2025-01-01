#include <iostream>
#include <thread>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

// Function to calculate the sum of elements
void calculateSum(const std::vector<int>& data, int& sum) {
    sum = 0;
    for (int num : data) {
        sum += num;
    }
}

// Function to find the maximum value
void findMax(const std::vector<int>& data, int& maxVal) {
    maxVal = INT_MIN;
    for (int num : data) {
        if (num > maxVal) {
            maxVal = num;
        }
    }
}

// Function to find the minimum value
void findMin(const std::vector<int>& data, int& minVal) {
    minVal = INT_MAX;
    for (int num : data) {
        if (num < minVal) {
            minVal = num;
        }
    }
}

int main() {
    // Shared data
    vector<int> data = {15, 22, 13, 27, 35, 19, 8, 24, 18, 30};
    int sum = 0, maxVal = 0, minVal = 0;

    // Create threads
    thread sumThread(calculateSum, std::cref(data), std::ref(sum));
    thread maxThread(findMax, std::cref(data), std::ref(maxVal));
    thread minThread(findMin, std::cref(data), std::ref(minVal));

    // Wait for all threads to finish
    sumThread.join();
    maxThread.join();
    minThread.join();

    // Print results
    cout << "Sum of elements: " << sum << std::endl;
    cout << "Maximum value: " << maxVal << std::endl;
    cout << "Minimum value: " << minVal << std::endl;

    return 0;
}
