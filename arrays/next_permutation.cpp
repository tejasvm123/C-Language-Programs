/*
Program Name: Next Permutation
Problem Statement:
Given an array of integers, rearrange the elements to form the next lexicographically greater permutation.
If such an arrangement is not possible, rearrange it to the lowest possible order (sorted in ascending order).

Example:
Input:
Enter number of elements: 3
Enter the elements:
1 2 3

Output:
Next permutation: 1 3 2

Explanation:
The next permutation of [1, 2, 3] is [1, 3, 2].
If input was [3, 2, 1], output would be [1, 2, 3] since it's the last permutation.

Approach:
1. Traverse from the end and find the first element that is smaller than its next (index = i - 1).
2. Find the element just larger than arr[i - 1] from the end (index = j).
3. Swap arr[i - 1] and arr[j].
4. Reverse the subarray from i to the end.
This will generate the next lexicographically greater permutation.

Time Complexity: O(n)
Space Complexity: O(1)

Compilation Command:
g++ next_permutation.cpp -o next_permutation
Run Command:
./next_permutation
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Function to compute the next permutation
void nextPermutation(vector<int>& arr) {
    int n = arr.size();
    int i = n - 2;

    // Step 1: Find first decreasing element from the right
    while (i >= 0 && arr[i] >= arr[i + 1]) {
        i--;
    }

    if (i >= 0) {
        // Step 2: Find element just greater than arr[i]
        int j = n - 1;
        while (arr[j] <= arr[i]) {
            j--;
        }
        swap(arr[i], arr[j]);
    }

    // Step 3: Reverse the suffix
    reverse(arr.begin() + i + 1, arr.end());
}

int main() {
    int n;
    cout << "Enter number of elements: ";
    cin >> n;

    vector<int> arr(n);
    cout << "Enter the elements:\n";
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    nextPermutation(arr);

    cout << "Next permutation: ";
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}
