'''
Searching for Patterns | Set 1 (Naive Pattern Searching)
Given a text txt[0..n-1] and a pattern pat[0..m-1], write a function search(char pat[], char txt[]) that prints all occurrences of pat[] in txt[]. You may assume that n > m.

Examples:

Input:  txt[] = "THIS IS A TEST TEXT"
        pat[] = "TEST"
Output: Pattern found at index 10

Input:  txt[] =  "AABAACAADAABAABA"
        pat[] =  "AABA"
Output: Pattern found at index 0
        Pattern found at index 9
        Pattern found at index 12
'''

def strcmp(str1, str2):
    if len(str1) != len(str2):
        return False

    i = 0;
    for i, c in enumerate(str1):
        if c != str2[i]:
            return False

    return True


def naive(haystack, needle):
    i = 0
    matches = []
    while i < len(haystack):
        if strcmp(haystack[i:i+len(needle)], needle):
            matches.append(i)
        i += 1

    return matches

def test_pattern_searching(algo=naive):
    assert algo("foo", "bar") == []
    assert algo("THIS IS A TEST TEXT", "TEST") == [10]
    assert algo("AABAACAADAABAABA", "AABA") == [0, 9, 12]
