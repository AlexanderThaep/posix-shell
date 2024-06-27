#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define BUFFER_SIZE 256
#define TBUFFER_SIZE 16

#define PROGRAM_NAME "shell"

int EXIT_STATUS = 0;
int BUILTINS_COUNT = 4;
char* BUILTINS[] = {"help", "exit", "cd", "ls"};

int actual_buffer_size = BUFFER_SIZE;
char* input_buffer;
char c;

int actual_tbuffer_size = TBUFFER_SIZE;
char** token_buffer;

int processTokens() {
	char* first_token = token_buffer[0];
	if (first_token == NULL) {
		return 1;
	}

	int index = 0;
	int match = -1;
	for (; index < BUILTINS_COUNT; index++) {
		char* builtin = BUILTINS[index];

		int i = 0;
		while (builtin[i] != '\0' || first_token[i] != '\0') {
			if (builtin[i] != first_token[i]) {
				match = -1;
				break;
			}
			match = index;
			i++;
		}
		if (match == -1) continue;
		break;
	}
	if (match != -1) {
		printf("Matched command [%s]\n", BUILTINS[match]);
	}
	
	return 0;
}

char** tokenizeLine() {
	int index = 0;
	int tindex = 0;
	char skip = 0;
	char in_string = 0;

	while (1) {
		c = input_buffer[index];
		
		switch (c) {
			case '\'':
			case '\"':
				in_string = 1;
				break;
			case '\0':
				token_buffer[tindex] = NULL;
				return token_buffer;
			case ' ':
			case '\r':
			case '\v':
			case '\f':
			case '\n':
			case '\t':
				input_buffer[index] = '\0';
				if (skip == 1) {
					skip = 0;
				}
				break;
			default:
				if (skip == 0) {
					token_buffer[tindex] = input_buffer + index;
					tindex++;
				}

				if (tindex >= actual_tbuffer_size) {
					actual_tbuffer_size += TBUFFER_SIZE;
					token_buffer = realloc(token_buffer, sizeof(char*) * actual_tbuffer_size);
				}

				skip = 1;
				break;
		}

		index++;
	}
	return NULL;
}

char* readLine() {
	int index = 0;
	while (input_buffer != NULL) {
		c = getchar();
		
		if (c == EOF || c == '\n') {
			input_buffer[index] = '\0';
			return input_buffer;
		}

		input_buffer[index] = c;
		index++;

		if (index >= actual_buffer_size) {
			actual_buffer_size += BUFFER_SIZE;
			input_buffer = realloc(input_buffer, actual_buffer_size);
		}
	}
	return NULL;
}

int main(int argc, char** argv) {

	input_buffer = (char*) malloc(sizeof(char) * BUFFER_SIZE);	
	token_buffer = (char**) malloc(sizeof(char*) * TBUFFER_SIZE);

	if (input_buffer == NULL || token_buffer == NULL) {
		goto error;
	}

	while (EXIT_STATUS == 0) {
		time_t seconds = time(NULL);
		printf("[%ld] Enter command: ", seconds);
		if (readLine() == NULL) {
			goto error;
		}
		if (tokenizeLine() == NULL) {
			goto error;
		}

		//
		int index = 0;
		while (token_buffer[index] != NULL) {
			printf("%s\n", token_buffer[index]);
			index++;
		}
		//

		// processTokens();

	}

	return 0;

	error:
	perror(PROGRAM_NAME);
	free(input_buffer);
	input_buffer = NULL;
	free(token_buffer);
	token_buffer = NULL;
	return 1;
}
