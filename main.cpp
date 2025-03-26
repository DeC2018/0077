#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    vector<vector<int>> combine(int n, int k) {
        vector<vector<int>> result;
        vector<int> combination(k);
        for (int i = 0; i < k; i++) {
            combination[i] = i + 1;
        }
        result.push_back(combination);
        while (true) {
            int i = k - 1;
            while (i >= 0 && combination[i] == n - k + i + 1) {
                i--;
            }
            if (i < 0) {
                break;
            }
            combination[i]++;
            for (int j = i + 1; j < k; j++) {
                combination[j] = combination[j - 1] + 1;
            }
            result.push_back(combination);
        }
        
        return result;
    }
};

void printCombinations(const vector<vector<int>>& combinations) {
    cout << "[";
    for (size_t i = 0; i < combinations.size(); ++i) {
        cout << "[";
        for (size_t j = 0; j < combinations[i].size(); ++j) {
            cout << combinations[i][j];
            if (j < combinations[i].size() - 1) {
                cout << ",";
            }
        }
        cout << "]";
        if (i < combinations.size() - 1) {
            cout << ",";
        }
    }
    cout << "]" << endl;
}

int main() {
    Solution solution;

    int n1 = 4, k1 = 2;
    cout << "Input: n = " << n1 << ", k = " << k1 << endl;
    vector<vector<int>> result1 = solution.combine(n1, k1);
    cout << "Output: ";
    printCombinations(result1);

    int n2 = 1, k2 = 1;
    cout << "Input: n = " << n2 << ", k = " << k2 << endl;
    vector<vector<int>> result2 = solution.combine(n2, k2);
    cout << "Output: ";
    printCombinations(result2);

    return 0;
}
