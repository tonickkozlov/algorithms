#include <stdio.h>
#include <string.h>

void swap(char *lhs, char *rhs) {
    char tmp = *rhs;
    *rhs = *lhs;
    *lhs = tmp;
}

void permute(char *S, size_t start, size_t length) {
    if (length - 1 == start) {
        printf("%s\n", S);
        return;
    }

    for (size_t i = start; i < length; ++i) {
        swap(S+start, S+i);
        permute(S, start+1, length);
        swap(S+start, S+i);
    }
}


int main() {
    char mystr[] = "ABCD";

    permute(mystr, 0, strlen(mystr));

    printf("%d\n", sizeof(mystr));
}
