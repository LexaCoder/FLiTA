#include <stdio.h>
#include <ctype.h>
#include <string.h>

int decimal_to_binary(int decimal);

int main() {
    int size1, size2;
    char input[256];
    char *token;
    int valid_input;

    while (1) {
        printf("Enter the size of the set: ");
        fgets(input, sizeof(input), stdin);
        valid_input = sscanf(input, "%d", &size1);
        if (valid_input == 1 && size1 > 0 && size1 <= 20) {
            break;
        }
        if (valid_input == 0 || size1 <= 0) {
            printf("Error: invalid input, please enter a natural number.\n");
        } else {
            printf("Error: the size of the set cannot exceed 20.\n");
        }
    }

    int set[size1];
    int i, j;

    printf("\nEnter %d elements of the set (separated by spaces):\n", size1);
    while (1) {
        fgets(input, sizeof(input), stdin);
        token = strtok(input, " \n");
        for (i = 0; i < size1; i++) {
            if (token == NULL) {
                printf("Error: insufficient input\n");
                break;
            }
            valid_input = sscanf(token, "%d", &set[i]);
            if (valid_input != 1 || set[i] <= 0) {
                printf("Error: invalid input, please enter a natural number.\n");
                break;
            }

            // check for duplicate values
            for (j = 0; j < i; j++) {
                if (set[j] == set[i]) {
                    printf("Error: the set cannot contain duplicate values\n");
                    valid_input = 0;
                    break;
                }
            }
            if (j < i) {
                // duplicate value found, request input again
                break;
            }

            token = strtok(NULL, " \n");
        }
        if (i == size1) {
            break;
        }
        printf("\nEnter %d elements of the set (separated by spaces):\n", size1);
    }

    printf("\nSet:\n");
    for (i = 0; i < size1; i++) {
        printf("%d ", set[i]);
    }

    printf("\n\nBinary representation of elements in the set:\n");
    for (i = 0; i < size1; i++) {
        printf("%d -> ", set[i]);
        printf("%d\n", decimal_to_binary(set[i]));
    }

    return 0;
}

int decimal_to_binary(int decimal) {
    int binary = 0, base = 1;
    while (decimal > 0) {
        binary += (decimal % 2) * base;
        decimal /= 2;
        base *= 10;
    }
    return binary;
}
