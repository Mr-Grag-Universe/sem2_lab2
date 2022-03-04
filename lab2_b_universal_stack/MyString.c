#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void tabs_to_spaces(char * line) {
	if (line == NULL) return;
	if (line[0] == '\0') return;
	int i = 0;
	while (line[i] != '\0') {
		if (line[i] == '\t')
			line[i] = ' ';
		i++;
	}
}

int is_letter(char * line) {
	if (line == NULL)
		return -1;
	if (line[1] != '\0')
		return 0;
	if ((line[0] < 'a' || line[0] > 'z') && (line[0] < 'A' || line[0] > 'Z'))
		return 0;
	return 1;
}

void delete_double_spaces(char ** line) {
    if (*line == NULL)
        return;
    
    int i = 0;
    char flag = 0;
    while ((*line)[i] != '\0') {
        // printf("%s\n", *line);
        if ((*line)[i] == ' ') {
            if (flag) { // delete spaces
                int ind = i;
                while ((*line)[ind] == ' ')
                    ind++;
                int len = strlen((*line));

                // 0 1 (<-flag) 2 3 4 (<-' ') 5 \0: len = 7
                // printf("here\n");
                // getchar();
                memcpy((*line) + i, (*line) + ind, sizeof(char) * (len-ind+1));
                (*line) = (char*) realloc((*line), sizeof(char) * (len+1-(ind-i)));
                // getchar();
                // printf("%s\n", (*line));
                i--;
                flag = 0;
            }
            else
                flag = 1;
        }
        else
            flag = 0;
        i++;
    }
}

unsigned char is_digit(char * s) {
	size_t i = 0;
	while (s[i]) {
		if (s[i] == '-') {
			if (i || strlen(s) == 1)
				return 0;
		}
		else if ((s[i] > '9' || s[i] < '1') && s[i] != '0')
			return 0;
		++i;
	}
	return 1;
}

unsigned char is_float(char * s) {
	size_t i = 0;
	char flag = 0;
	// char min = 0;
	while (s[i]) {
		if ((s[i] > '9' || s[i] < '1') && s[i] != '0') {
			if (s[i] == '.') {
				if (flag)
					return 0;
				flag++;
			}
			else if (s[i] == '-') {
				if (i == 0)
					continue;
				return 0;
			}
			else
				return 0;
		}
		++i;
	}
	return 1;
}

unsigned char is_operator(char * s) {
	char mult[] = "*";
	char sum[] = "+";
	char min[] = "-";
	char dev[] = "/";

	if (s == NULL)
		return 0;

	if (strcmp(s, mult) == 0) return 1;
	else if (strcmp(s, sum) == 0) return 1;
	else if (strcmp(s, min) == 0) return 1;
	else if (strcmp(s, dev) == 0) return 1;
	return 0;
}

char * str_copy(char * line) {
	int len = strlen(line);
	char * copy = (char*) malloc((len+1) * sizeof(char));
	memmove(copy, line, sizeof(char) * (len + 1));
	return copy;
}

char ** split(char * line) {
	char ** res = NULL;
	int n = 0;

	if (line == NULL)
		return NULL;
	if (line[0] == '\0')
		return NULL;

	char * copy = str_copy(line);

	// getchar();

	char * word = strtok(copy, " \t");
	while (word) {
		// printf("%ld, %ld\n", word, line);
		n++;
		res = realloc(res, sizeof(char*) * n);
		res[n-1] = malloc(sizeof(char) * (strlen(word)+1));
		memcpy(res[n-1], word, sizeof(char)*(strlen(word)+1));
		word = strtok(NULL, " \t");
	}
	free(copy);
	res = realloc(res, sizeof(char*) * (n+1));
	res[n] = NULL;

	return res;
}