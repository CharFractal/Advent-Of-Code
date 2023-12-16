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

static char* colors[] = {"Game" , "red", "green", "blue"};
static int check[] = {0 , 12 , 13 , 14};
static int games = 1;

bool compstr(char* line, char* value);
void getdigits(char* line, Buffer* buffer);
int decode(char* line);
void updateBuffer(Buffer* buffer);

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
		//printf("%s" , line);
		result += decode(line);
	}

	clock_t end_time = clock();

	double exec_time = ((double)(end_time - start_time))/ CLOCKS_PER_SEC;

	printf("result : %d\n" , result);
	printf("exectime: %f" , exec_time);
	free(line);
	fclose(fileptr);

	return 0;
}

int decode(char* line) {

	int result = 0;
	Buffer buffer ;
	buffer.ptr = malloc(sizeof(int) * 4);
	if (buffer.ptr == NULL) {
		printf("Memory allocation failed.\n");
		exit(1);
	}
	memset(buffer.ptr, 0, sizeof(int) * 4);
	buffer.count = 4;
	buffer.ptr[0] = games;
	games++;
	getdigits(line, &buffer);

	for(int i = 1 ;  i < buffer.count ; i++){
		if(buffer.ptr[i] > check[i]){
			return 0;
		}
	}
	for(int i = 0 ; i < buffer.count ; i++){
		printf("%s -> %d\n" ,colors[i],  buffer.ptr[i]);
	}
	printf("\n\n");
	result = buffer.ptr[0];
	free(buffer.ptr);
	return result;
}

void getdigits(char* line, Buffer* buffer) {
	if (*line == '\0') {
		return;
	}

	if (isdigit(*line)) {

		if(isdigit(*(line+1))){
			for (int i = 0; i < 4; i++) {
				if (*(line+3) == *colors[i]) {
					if (compstr(line + 3, colors[i])) {
						int n =  (((*line - '0')*10) + (*(line+1) - '0'));
						if(buffer->ptr[i] < n ){

							buffer->ptr[i] = n;
						}
						//printf("%d -> %s\n" ,buffer->ptr[i],colors[i]);
						return getdigits(line + 2 , buffer);
					}
				}
			}
		}else{
			for (int i = 0; i < 4; i++) {
				if (*(line+2) == *colors[i]) {
					if (compstr(line + 2, colors[i])) {
						int n = *(line) - '0';
						if(buffer->ptr[i] < n){
							buffer->ptr[i] = n; 
						}
						//printf("%d -> %s\n" ,buffer->ptr[i],colors[i]);
						return getdigits(line + 1, buffer);
					}
				}
			}
		}
	}
	return getdigits(line+1 , buffer);
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

void updateBuffer(Buffer* buffer){
	buffer->count++;
	buffer->ptr = realloc(buffer->ptr, sizeof(int) * buffer->count);
	if (buffer->ptr == NULL) {
		printf("Memory reallocation of buffer failed.\n");
		exit(1);
	}
}
