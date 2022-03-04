#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

char * get_line() {
	setlocale(LC_ALL, "Rus");

	char * res = NULL;
	char n = 0;
	int old_len = 0;
	char buf[101] = {0};
	
	do {
		n = scanf("%100[^\n]", buf);
		int chunck_len = strlen(buf);
		// printf("%d %d\n", n, chunck_len);
		//int old_len = strlen(res);

		

		if (n == 1) { // } || n == EOF) {
			res = (char *) realloc(res, sizeof(char) * (old_len + chunck_len + 1));
			memcpy(res+old_len, buf, chunck_len);
			old_len += chunck_len;
		}
			if (n == EOF) {
				if (chunck_len == 0) {
					if (res)
						free(res);
					printf("\n");
					return NULL;
				}
				printf("\n");
				break;
			}

		// if (n < 0) {

			// printf("hey, here i am!\n");
		// }
		else if (n == 0) scanf("%*c");

		else if (!old_len) return NULL;

	} while (n > 0);

	if (old_len > 0)
		res[old_len] = '\0';
	else
		res = (char *) calloc(1, sizeof(char));

	// printf("%s\n", res);
	return res;
}

char * get_line_from_lesson() {
    char buf[81] = {0};
    char * res = (char*) malloc(1);
    res[0] = '\0';
    int len = 0;

    //printf("%d", EOF);
    while (scanf("%80[^\n]", buf) != EOF) {
        int chunk_len = strlen(buf);
        int old_len = strlen(res);

        if (chunk_len == 80) {
            res = (char*) realloc(res, sizeof(char) * (old_len + chunk_len + 1));

            memcpy(res + old_len, buf, chunk_len);
            res[old_len + chunk_len] = '\0';
        }
        else {
            res = (char *) realloc(res, sizeof(char) * (old_len + chunk_len + 2));

            memcpy(res + old_len, buf, chunk_len);
            res[old_len + chunk_len + 1] = '\0';
            res[old_len + chunk_len] = '\n';
            scanf("%*c");
        }
        len = strlen(res);
        for (int i = 0; i < 81; ++i) buf[i] = '\0';
    }

    //printf("\n%s\n", res);

    if (len > 0) {
        char * new_res = (char*) malloc(sizeof(char) * len);
        for (int i = 0; i < len; i++) new_res[i] = res[i];
        free(res);
//        res = (char*) realloc(new_res, sizeof(char) * len);
        res = new_res;
        res[len-1] = '\0';
    }
    else res = calloc(1, sizeof(char));

    //res[]

    return res;
}