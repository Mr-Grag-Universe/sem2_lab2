#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
            number_of_dig++;
        }
        else if (is_operator(words[i])) {
            number_of_ops++;
        }
        else if (is_letter(words[i])) {
            number_of_dig++;
        }
        else {
            free_words(words);
            return 0;
        }
    }

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

        Stack_size_t * stack = malloc(sizeof(Stack_size_t));
        *stack = stack_init_size_t(100);//, INT);

        // print_words(words);
        // getchar();

        //char * inf_vertion = malloc(sizeof(char)*(strlen(words[0])+1));
        //memcpy(inf_vertion, words[0], sizeof(char)*(strlen(words[0])+1));
        int i = 0;
        while (i < number_of_words(words)) {
            // printf("%s\n", inf_vertion);
            if (is_operator(words[i]) == 0) {
                stack_put_size_t(stack, (size_t) words[i]);
                i++;
                continue;
            }

            char * n2 = (char*) stack_get_size_t(stack);
            char * n1 = (char*) stack_get_size_t(stack);

            //int old_len = strlen(inf_vertion);
            int len1 = strlen(n1);
            int len2 = strlen(n2);

            //int len = strlen(n);

            if (is_letter(n1))
                len1 = 1;
            if (is_letter(n2))
                len2 = 1;
            
            n1 = realloc(n1, sizeof(char) * (len2 + len1 + 4));

            memcpy(n1 + 1, n1, len1);
            n1[0] = '(';

            n1[len1 + 1] = words[i][0];
            
            memcpy(n1 + len1 + 2, n2, len2);
            n1[len2 + len1 + 2] = ')';
            n1[len2 + len1 + 3] = '\0';
            stack_put_size_t(stack, (size_t) n1);

            free(n2);
            free(words[i]);
            i++;
        }
        char * answer = (char*) stack_get_size_t(stack);
        printf("%s\n", answer);

        // free every memory
        free(line);
        i = 0;
        // free_words(words);
        free(words);
        stack_free_size_t(stack);
        free(stack);
        free(answer);
    }

    printf("Enter any line to finish!\n");
    char * answer = get_line();
    if (answer)
        free(answer);

    return 0;
}