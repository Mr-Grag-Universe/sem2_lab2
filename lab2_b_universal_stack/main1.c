#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "Stack.h"
#include "KGetLine.h"
#include "MyString.h"
#include "func.h"

void delete_spaces(char ** line) {
    char * res = malloc(sizeof(char) * (strlen(*line)+1));
    int j = 0;
    for (size_t i = 0; i < strlen(*line)+1; ++i) {
        if ((*line)[i] != ' ') {
            res[j] = (*line)[i];
            j++;
        }
    }
    res = realloc(res, sizeof(char) * (j+1));
    free(*line);
    *line = res;
}

void print_words(char ** words) {
    int i = 0;
    while (words[i]) {
        printf("%s ", words[i]);
        i++;
    }
    printf("\n");
}

/*
void reverse(char ** arr, size_t size, size_t n) {
    if (arr == NULL) {
        return;
    }
    for (size_t i = 0; i < n; ++i) {
        void * temp = malloc(size);
        memmove(temp, (void*) ((size_t)arr+size*i), size);
        memmove((void*) ((size_t)arr + size*i), (void*) ((size_t)arr + size*(n-1-i)), size);
        memmove((void*) ((size_t)arr + size*(n-1-i)), temp, size);
        free(temp);

        char * temp = ((char*) arr)[i];
        ((char*) arr)[i] = ((char*) arr)[n-1-i];
        ((char*) arr)[n-1-i] = temp;
    }
}
*/

int number_of_words(char ** words) {
    if (words == NULL)
        return 0;

    int i = 0;
    while (words[i])
        i++;

    return i;
}

char * str_from_int(int x) {
    int len = 0;
    int y = x;
    while (y) {
        len++;
        y /= 10;
    }
    if (x < 0)
        len++;

    char * res = malloc(sizeof(char) * (len+1));

    char buff[100] = {0};
    sprintf(buff, "%d", x);
    memcpy(res, buff, len+1);

    return res;
}

void free_words(char ** words) {
    int i = 0;
    while (words[i]) {
        free(words[i]);
        i++;
    }
    free(words);
}

char * new_line(Stack_int * digits, Stack_int * operators) {
    char * line = calloc(1, sizeof(char));
    if (TEMPLATE(number_of_elements, int)(*digits) == 0)//number_of_elements(*digits) == 0)
        return NULL;

    int n_o_w = 1;
    char ** words = malloc(sizeof(char *) * 2);
    words[0] = str_from_int(TEMPLATE(stack_get, int)(digits));//stack_get(digits));
    words[1] = NULL;

    //print_words(words);
    //getchar();

    while (TEMPLATE(number_of_elements, int)(*digits)) {//number_of_elements(*digits)) {
        //printf("hi1\n");
        words = realloc(words, sizeof(char*) * (n_o_w + 5));

        //printf("hi2\n");

        words[n_o_w] = malloc(sizeof(char)*2);
        words[n_o_w][0] = (char) TEMPLATE(stack_get, int)(operators);//stack_get(operators);
        words[n_o_w][1] = '\0';

        //printf("hi3\n");

        words[n_o_w + 1] = str_from_int(TEMPLATE(stack_get, int)(digits));//stack_get(digits));

        //printf("hi4\n");

        words[n_o_w + 2] = malloc(sizeof(char)*2);
        words[n_o_w + 2][0] = ')';
        words[n_o_w + 2][1] = '\0';

        //printf("hi5\n");

        //memmove(words + 1, words, sizeof(char*) * (n_o_w + 4));
        for (int i = n_o_w+3; i >= 0; --i) {
            words[i+1] = words[i];
        }

        //printf("hi6\n");

        words[0] = malloc(sizeof(char) * 2);
        words[0][0] = '(';
        words[0][1] = '\0';

        //printf("hi7\n");

        words[n_o_w + 4] = NULL;

        n_o_w += 4;
    }

    //print_words(words);
    //getchar();

    for (int i = 0; i < n_o_w; ++i) {
        int len = strlen(words[i]);
        int old_len = strlen(line);

        line = realloc(line, old_len+len+1);

        memmove(line+old_len, words[i], len+1);
    }

    free_words(words);

    return line;
}

int check_line(char * line) {
    if (line == NULL)
        return -1;
    if (line[0] == '\0')
        return 0;
    
    // printf("%s\n", line);
    char ** words = split(line);
    // printf("%s\n", line);

    char flag = 0;
    int number_of_ops = 0, number_of_dig = 0;
    for (int i = 0; i < number_of_words(words); ++i) {
        if (is_digit(words[i])) {
            if (flag) {
                // printf("noo: %d\nnod: %d", number_of_ops, number_of_dig);
                free_words(words);
                return 0;
            }
            number_of_dig++;
        }
        else if (is_operator(words[i])) {
            number_of_ops++;
            flag = 1;
        }
        else {
            // printf("noo: %d\nnod: %d", number_of_ops, number_of_dig);
            free_words(words);
            return 0;
        }
    }

    // printf("noo: %d\nnod: %d", number_of_ops, number_of_dig);
    free_words(words);
    return (number_of_dig == number_of_ops+1);
}

int main() {
    printf("Hello!\nHere you can write your lines:\n");

    while (1) {
        printf("-> ");
        char * line = get_line();

        if (line == NULL)
            break;
        
        // delete_spaces(&line);

        if (line[0] == '\0') {
            free(line);
            continue;
        }

        if (strcmp(line, "finish") == 0) {
            free(line);
            break;
        }

        if (check_line(line) == 0) {
            free(line);
            printf("Your line is wrong. Please check it and try agane.\n");
            continue;
        }

        char ** words = split(line);
        // print_words(words); // ###

        Stack_int * digits = malloc(sizeof(Stack_int));
        *digits = TEMPLATE(stack_init, int)(100, INT);//stack_init(100);
        Stack_int * operators = malloc(sizeof(Stack_int));
        *operators = TEMPLATE(stack_init, int)(100, INT);//stack_init(100);

        int i = 0;
        while (words[i] && is_digit(words[i])) {
            TEMPLATE(stack_put, int)(digits, atoi(words[i]));//stack_put(digits, atoi(words[i]));
            i++;
        }

        // reverse(words, sizeof(char*), number_of_words(words));
        // print_words(words);

        i = number_of_words(words)-1;
        while (words[i] && is_digit(words[i])==0) {
            TEMPLATE(stack_put, int)(operators, words[i][0]);//stack_put(operators, words[i][0]);
            i--;
        }

        // stack_print(*digits);
        // stack_print(*operators);

        //printf("%d, %c\n", digits->head->item, (char) operators->head->item);
        //getchar();

        char * inf_vertion = new_line(digits, operators);

        // printf("YUHUUU\n");

        printf("%s\n", inf_vertion);

        // free every memory
        free(line);
        i = 0;
        free_words(words);
        TEMPLATE(stack_free, int)(digits);//stack_free(digits);
        TEMPLATE(stack_free, int)(operators);//stack_free(operators);
        free(operators);
        free(digits);
        free(inf_vertion);
    }

    printf("Enter any line to finish!\n");
    char * answer = get_line();
    if (answer)
        free(answer);

    return 0;
}