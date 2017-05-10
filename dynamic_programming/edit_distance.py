"""
Given two strings str1 and str2 and below operations that can performed on str1. Find minimum number of edits (operations) required to convert ‘str1’ into ‘str2’.

Insert
Remove
Replace

All of the above operations are of equal cost.

Examples:

Input:   str1 = "geek", str2 = "gesek"
Output:  1
We can convert str1 into str2 by inserting a 's'.

Input:   str1 = "cat", str2 = "cut"
Output:  1
We can convert str1 into str2 by replacing 'a' with 'u'.

Input:   str1 = "sunday", str2 = "saturday"
Output:  3
Last three and first characters are same.  We basically
need to convert "un" to "atur".  This can be done using
below three operations. 
Replace 'n' with 'r', insert t, insert a



1. Subproblems: edit distance beween X[i:] and Y[j:] for any i, j
    # subproblems = O(|X|*|Y|)

2. Guess: Given X[i], Y[i], turn X[i] into Y[i]:
    * replace X[i] with Y[j]
    * insert Y[j] in the beginning
    * delete X[i]

3. Recurrence: DP(i, j) = min(
        COST_REPLACE(X[i], Y[j]) + DP(i+1, j+1),
        COST_INSERT(Y[i]) + DP(i, j+1),
        COST_DELETE(X[i]) + DP(i+1, j),
    )

4. Topo order: nested loops
"""

COST_INSERT = 1
COST_DELETE = 1
COST_REPLACE = 1

def edit_distance_recursive(x, y, i=0, j=0, current=0):
    if i >= len(x) or j >= len(y):
        return current

    if x[i] == y[j]:
        return current + edit_distance_recursive(x, y, i+1, j+1)

    return current + min(
            edit_distance_recursive(x, y, i+1, j+i) + COST_REPLACE,
            edit_distance_recursive(x, y, i, j+i) + COST_INSERT,
            edit_distance_recursive(x, y, i+1, j) + COST_DELETE,
            )

def print_mat(mat):
    for row in mat:
        print(row)

def edit_distance_dp(x, y):
    mat = [[0 for i in range(len(y)+1)] for j in range(len(x)+1)] 
    for i in reversed(range(0, len(x))):
        for j in reversed(range(0, len(y))):

            print(i, j)

            if x[i] == y[j]:
                mat[i][j] = mat[i+1][j+1]
            else :
                mat[i][j] = min(
                        mat[i+1][j+1] + COST_REPLACE,
                        mat[i][j+1] + COST_INSERT,
                        mat[i+1][j] + COST_DELETE,
                        )

    return mat[0][0]

def test_edit_distance_recursive():
    assert edit_distance_recursive("cat", "cat") == 0
    assert edit_distance_recursive("geek", "gesek") == 1
    assert edit_distance_recursive("sunday", "saturday") == 3

def test_edit_distance():
    assert edit_distance_dp("cat", "cat") == 0
    assert edit_distance_dp("geek", "gesek") == 1
    assert edit_distance_dp("sunday", "saturday") == 3

