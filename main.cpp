
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Parse input format: 8 integers, each on separate lines
void parseInput(vector<int>& rootValues, int& cnt) {
    int value;
    
    // Read first 7 integers for BST nodes
    for (int i = 0; i < 7; i++) {
        if (cin >> value) {
            rootValues.push_back(value);
        }
    }
    
    // Read the last integer as cnt
    if (cin >> cnt) {
        // Successfully read cnt
    }
}

int main() {
    vector<int> rootValues;
    int cnt;
    
    parseInput(rootValues, cnt);
    
    // Sort values in descending order to get largest to smallest
    sort(rootValues.begin(), rootValues.end(), greater<int>());
    
    // The k-th largest element is at index k-1 (0-based)
    if (cnt > 0 && cnt <= rootValues.size()) {
        cout << rootValues[cnt - 1] << endl;
    }
    
    return 0;
}
