#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void computeLPSArray(char *pattern, int M, int *lps);
void KMPSearch(char *pattern, FILE *fp);

int main() {
    char filename[10];
    printf("Enter the input file name: ");
    scanf("%s", filename);

    FILE *fp = fopen(filename, "r");
    if (!fp) {
        printf("Failed to open the file.\n");
        return 0;
    }
    
    char pattern[30];
    printf("\nEnter the pattern to match: ");
    scanf("%s", pattern);

    KMPSearch(pattern, fp);

    fclose(fp);

    return 0;
}

void computeLPSArray(char *pattern, int M, int *lps) {
    int len = 0;
    lps[0] = 0;

    for(int i = 1; i < M; i++) {
        if (pattern[i] == pattern[len]) {
            len++;
            lps[i] = len;
        }
        else {
            if (len != 0)
                len = lps[len - 1];
            else {
                lps[i] = 0;
            }
        }
    }
}

void KMPSearch(char *pattern, FILE *fp) {
    int M = strlen(pattern);
    int N = 0;

    int *lps = (int *)malloc(sizeof(int) * M);
    int j = 0;

    computeLPSArray(pattern, M, lps);
    printf("\nLPS: ");
    for (int i = 0; i < M; i++) {
        printf("%d ", lps[i]);
    }
    printf("\n");

    int flag = 0;
    char ch;
    while ((ch = fgetc(fp)) != EOF) {
        N++;
        if (pattern[j] == ch) {
            j++;
        }
        else {
            while (j > 0 && pattern[j] != ch) {
                j = lps[j - 1];
            }
            if (pattern[j] == ch) {
                j++;
            }
        }

        if (j == M) {
            printf("\nPattern found at index %d\n", N - j);
            j = lps[j - 1];
            flag = 1;
        }
    }
    if (0 == flag) {
        printf("\nPattern not found in the text.\n");
    }
    free(lps);
}
