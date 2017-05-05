'''
http://quiz.geeksforgeeks.org/count-1s-sorted-binary-array/

Given a binary array sorted in non-increasing order, count the number of 1’s in it.
Examples:
Input: arr[] = {1, 1, 0, 0, 0, 0, 0}
Output: 2

Input: arr[] = {1, 1, 1, 1, 1, 1, 1}
Output: 7

Input: arr[] = {0, 0, 0, 0, 0, 0, 0}
Output: 0
'''

def count_simple(arr):
    ' walks through array linearly and counts 1s in it. O(n)'
    i = 0
    while (i < len(arr) and arr[i] == 1):
        i += 1

    return i

def count_optimized(arr):#[1, 1, 1, 1, 1, 1]
    ' will perform a binary search to find the boundary of [1, 0] in the array. O(logn)'

    begin, end = 0, len(arr)#4, 6
    while True:

        if begin == end:
            return end

        mid_index = (begin + end) // 2#5
        r = arr[mid_index]#1
        # 1 by definition as 1s are always on the left
        l = arr[mid_index - 1] if mid_index > 0 else 1#1

        if [l, r] == [1, 1]:
            begin = mid_index + 1
            continue
        if [l, r] == [0, 0]:
            end = mid_index
            continue

        return mid_index


def test_count():
    assert count_simple([1, 1, 0, 0, 0, 0]) == 2
    assert count_simple([1, 1, 1, 1, 1, 1]) == 6
    assert count_simple([0, 0, 0]) == 0

def test_count_count_optimized():
    assert count_optimized([1, 1, 0, 0, 0, 0, 0]) == 2
    assert count_optimized([1, 1, 0, 0, 0, 0]) == 2
    assert count_optimized([1, 1, 1, 1, 1, 1]) == 6
    assert count_optimized([1, 1, 1, 1, 1, 0]) == 5
    assert count_optimized([0, 0, 0]) == 0
    assert count_optimized([0]) == 0
    assert count_optimized([1]) == 1
