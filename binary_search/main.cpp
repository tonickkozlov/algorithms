// Find number of occurrences of a given number in a sorted array.
#include <vector>
#include <iostream>

using namespace std;

int lowerBound(vector<int> elements, int target) {
    size_t begin = 0, end = elements.size();
    while (end - begin != 1) {
        size_t middle = (begin + end) / 2;
        if (elements[middle] < target) {
            begin = middle;
        } else {
            end = middle;
        }
    }
    return begin == 0 ? begin : end;
}

int upperBound(vector<int> elements, int target) {
    size_t begin = 0, end = elements.size();
    while (end - begin != 1) {
        size_t middle = (begin + end) / 2;
        if (elements[middle] <= target) {
            begin = middle;
        } else {
            end = middle;
        }
    }
    return end;
}
int countOccurences(vector<int> elements, int target) {
    int lbound = lowerBound(elements, target);
    int ubound = upperBound(elements, target);
    cout << lbound << " " << ubound << endl;
    if (elements[lbound] > target || elements[ubound-1] < target) {
        return 0;
    }
    return ubound - lbound;
}

int main() {
    vector<int> elements {1, 1, 1, 1, 1, 1, 1, 4, 4, 4, 5, 6, 7, 7, 7, 7};
    cout << countOccurences(elements, 5);

}
