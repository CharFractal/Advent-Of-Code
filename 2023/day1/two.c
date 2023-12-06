#include<stdio.h>
#include<stdbool.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

typedef struct {
	int count;
	int* ptr;
} Buffer;

static char* digits[] = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};

bool compstr(char* line, char* value);
void getdigits(char* line, Buffer* buffer);
int decode(char* line);

int main(int argc , char** argv) {
	if (argc != 2) {
		printf("Usage: %s <filename>\n", argv[0]);
		return 1;
	}

	FILE* fileptr = fopen(argv[1] , "r");
	if (fileptr == NULL) {
		printf("Error opening file.\n");
		return 1;
	}

	char* line = NULL;
	size_t linelen = 0; 
	int result = 0;

	clock_t start_time = clock();
	
	while(getline(&line , &linelen , fileptr) != -1){
		result += decode(line);
	}
	
	clock_t end_time = clock();

	double exec_time = ((double)(end_time - start_time))/ CLOCKS_PER_SEC;

	printf("%d" , result);
	printf("exectime: %f" , exec_time);
	free(line);
	fclose(fileptr);
	return 0;
}

int decode(char* line) {
	Buffer buffer;
	buffer.ptr = malloc(sizeof(int));
	if (buffer.ptr == NULL) {
		printf("Memory allocation failed.\n");
		exit(1);
	}
	buffer.count = 0;

	getdigits(line, &buffer);

	int value;
	if(buffer.count == 1){

		value = buffer.ptr[0]*10 + buffer.ptr[buffer.count-1];
	}else{
		value = buffer.ptr[0]*10 + buffer.ptr[buffer.count-1];

	}
	//printf("%s -> %d\n" , line , value);
	free(buffer.ptr);
	return value;
}

void getdigits(char* line, Buffer* buffer) {
	if (*line == '\0') {
		return;
	}

	for (int i = 0; i < 10; i++) {
		if (*line == *digits[i]) {
			if (compstr(line, digits[i])) {
				buffer->count++;
				buffer->ptr = realloc(buffer->ptr, sizeof(int) * buffer->count);
				if (buffer->ptr == NULL) {
					printf("Memory allocation failed.\n");
					exit(1);
				}
				buffer->ptr[buffer->count - 1] = i;
			}
		}
	}

	if (isdigit(*line)) {
		buffer->count++;
		buffer->ptr = realloc(buffer->ptr, sizeof(int) * buffer->count);
		if (buffer->ptr == NULL) {
			printf("Memory allocation failed.\n");
			exit(1);
		}
		buffer->ptr[buffer->count - 1] = *line - '0';
	}

	getdigits(line + 1, buffer);
}

bool compstr(char* line, char* digit) {
	if (*line == '\0' && *digit != '\0') {
		return false;
	}
	if (*digit == '\0') {
		return true;
	}

	if (*line == *digit) {
		return compstr(line + 1, digit + 1);
	}

	return false;
}

