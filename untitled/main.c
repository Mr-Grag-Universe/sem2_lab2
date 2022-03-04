#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Stack.h"
#include "KGetLine.h"
#include "MyString.h"

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

void reverse(char ** arr, size_t size, size_t n) {
    if (arr == NULL) {
        return;
    }
    for (size_t i = 0; i < n; ++i) {
        /*void * temp = malloc(size);
        memmove(temp, (void*) ((size_t)arr+size*i), size);
        memmove((void*) ((size_t)arr + size*i), (void*) ((size_t)arr + size*(n-1-i)), size);
        memmove((void*) ((size_t)arr + size*(n-1-i)), temp, size);
        free(temp);*/

        char * temp = ((char*) arr)[i];
        ((char*) arr)[i] = ((char*) arr)[n-1-i];
        ((char*) arr)[n-1-i] = temp;
    }
}

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
    //sprintf(res, "%d", x);

    char buff[100];
    sprintf(buff, "%d", x);
    memcpy(res, buff, len+1);

    return res;
}

void free_words(char ** words) {
    int i = 0;
    while (words[i]) {
        if (words[i][0] != '(')
            free(words[i]);
        i++;
    }
    free(words);
}

char * new_line(Stack * digits, Stack * operators) {
    char * line = calloc(1, sizeof(char));
    // int len = 0;
    if (number_of_elements(*digits) == 0)
        return NULL;
    
    /*line = malloc(sizeof(char));
    line[0] = '\0';
    char s[100];
    int number = stack_get(digits);
    sprintf (s, "%d", number);
    int x = strlen(s);
    line = realloc(line, sizeof(char) * (x+1));
    //itoa(stack_get(digits), s, 10);
    strcat(line, s);
    // free(s);
    while (number_of_elements(*digits)) {
        // char * new_line = malloc(sizeof(char));
        // new_line[0] = '\0';
        x = strlen(line);
        line = realloc(line, sizeof(char) * (x+2));
        strcat(line, ")");
        strcat(line, (char) stack_get(operators));

        number = stack_get(digits);
        sprintf (s, "%d", number);
        // itoa(stack_get(digits), s, 10);
        x = strlen(s);
        line = realloc(line, sizeof(char) * (strlen(line) + x+1));
        strcat(line, s);
        line = malloc(sizeof(char) * (strlen(line) + 2));
        memmove(line+1, line, strlen(line)+1);
        line[0] = '(';
        // free(s);
    }
    */

    int n_o_w = 1;
    char ** words = malloc(sizeof(char *) * 2);
    words[0] = str_from_int(stack_get(digits));
    words[1] = NULL;

    while (number_of_elements(*digits)) {
        words = realloc(words, sizeof(char*) * (n_o_w + 5));
        
        words[n_o_w] = malloc(sizeof(char)*2);
        words[n_o_w][0] = (char) stack_get(operators);
        words[n_o_w][1] = '\0';

        words[n_o_w + 1] = str_from_int(stack_get(digits));

        words[n_o_w + 2] = malloc(sizeof(char)*2);
        words[n_o_w + 2][0] = ')';
        words[n_o_w + 2][1] = '\0';
        // printf("\n%s\n", words[3]);

        // printf("\n%s %s %s %s\n", words[n_o_w], words[n_o_w+1], words[n_o_w+2], words[0]);
        // print_words(words);

        //memmove(words + 1, words, sizeof(char*) * (n_o_w + 4));
        for (int i = n_o_w+3; i >= 0; --i) {
            words[i+1] = words[i];
        }

        // printf("\n%s, %s %s %s %s\n", words[0], words[n_o_w], words[n_o_w+1], words[n_o_w+2], words[n_o_w + 3]);
        // +++
        words[0] = "("; //realloc(words[0], sizeof(char)*2);
        //words[0][0] = '(';
        //words[0][1] = '\0';
        //getchar();

        /*free(words[0]);
        getchar();
        words[0] = calloc(2, sizeof(char));
        char scope[2] = {'(', '\0'}; 
        memcpy(words[0], scope, sizeof(char) * 2);*/

        words[n_o_w + 4] = NULL;

        n_o_w += 4;
    }

    // print_words(words);
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

        Stack * digits = malloc(sizeof(Stack));
        *digits = stack_init(100);
        Stack * operators = malloc(sizeof(Stack));
        *operators = stack_init(100);

        int i = 0;
        while (words[i] && is_digit(words[i])) {
            stack_put(digits, atoi(words[i]));
            i++;
        }

        // reverse(words, sizeof(char*), number_of_words(words));
        // print_words(words);

        i = number_of_words(words)-1;
        while (words[i] && is_digit(words[i])==0) {
            stack_put(operators, words[i][0]);
            i--;
        }

        // stack_print(*digits);
        // stack_print(*operators);

        char * inf_vertion = new_line(digits, operators);

        // printf("YUHUUU\n");

        printf("%s\n", inf_vertion);

        // free every memory
        free(line);
        i = 0;
        free_words(words);
        stack_free(digits);
        stack_free(operators);
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