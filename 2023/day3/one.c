#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>

typedef struct {
	int rows;
	int cols;
	int count;
	char* ptr;
} Buffer;

int getsize(FILE* file);
Buffer* getbuff(FILE* file); 
int partnumber(Buffer* buffer);
int adjacentdigits(Buffer* buffer , int i , int j);
int getdigits(Buffer* buffer , int i , int j);

int main() {
	FILE* file = fopen("input.txt", "r");
	assert(file != NULL && "Failed to open file!");

	Buffer* buffer = getbuff(file);

	printf("Buffer contents:\n%s\n", buffer->ptr);
	printf("symbols : %d",partnumber(buffer));
	free(buffer->ptr); 
	free(buffer);      
	fclose(file);      
	return 0;
}

int partnumber(Buffer* buffer) {
	int total = 0; 

	for (int i = 0; i < buffer->rows; i++) {
		for (int j = 0; j < buffer->cols; j++) {
			char c = buffer->ptr[i * buffer->cols + j]; 

			if (c == '.') continue;

			if (isdigit(c)) continue;

			if (c == '\n') continue;

			printf("current : %d \n" , total);
			total += adjacentdigits(buffer, i, j); 
		}
	}
	return total; 
}

int adjacentdigits(Buffer* buffer, int i, int j) {

	int total = 0;

	for (int x = -1; x <= 1; ++x) {

		int rowValue = getdigits(buffer, i + x, j);
		if (rowValue == 0) {
			for (int y = -1; y <= 1; ++y) {
				if (y == 0) continue;

				total += getdigits(buffer, i + x, j + y);
			}
		} else {
			total += rowValue; 
		}
	}

	return total;
}

int getdigits(Buffer* buffer, int i, int j) {

	char c = buffer->ptr[j + (i * buffer->cols)];
	char l = buffer->ptr[j - 1 + (i * buffer->cols)];
	char r = buffer->ptr[j + 1 + (i * buffer->cols)];

	int digits[3] = {0, 0, 0};

	if (isdigit(c)) {
		if (isdigit(l) && isdigit(r)) {
			digits[2] = l - '0';
			digits[1] = c - '0';
			digits[0] = r - '0';
		} else if (isdigit(l)) {
			int o = 0;
			while (o < 3 && isdigit(buffer->ptr[j - o + (i * buffer->cols)])) {
				digits[o] = buffer->ptr[j - o + (i * buffer->cols)] - '0';
				int t = o;
				while(t--){
					digits[o] = digits[o] * 10;
				}
				o++;
			}
			return digits[2] + digits[1] + digits[0];
		} else if (isdigit(r)) {
			int o = 0;
			while (o < 3 && isdigit(buffer->ptr[j + o + (i * buffer->cols)])) {
				digits[o] = buffer->ptr[j + o + (i * buffer->cols)] - '0';
				int t = o;
				while(t){
					digits[t - 1] = digits[t - 1] * 10;
					t--;
				}
				o++;
			}
			return digits[0] + digits[1] + digits[2];
		} else {
			digits[0] = c - '0';
		}
	} else {
		return 0;
	}
	return (digits[2] * 100) + (digits[1] * 10) + digits[0];
}




Buffer* getbuff(FILE* file) {
	char c;

	Buffer* temp = malloc(sizeof(Buffer));
	assert(temp != NULL && "Failed to create buffer!");

	temp->rows = 0;
	temp->cols = 0; 
	temp->count = getsize(file);

	while ((c = getc(file)) != EOF) {
		temp->cols++; 
		if (c == '\n') break; 
	}
	temp->rows = temp->count / temp->cols;

	fseek(file, 0, SEEK_SET); 

	temp->ptr = malloc(sizeof(char) * temp->count);
	assert(temp->ptr != NULL && "Failed to make char array!");
	fread(temp->ptr, sizeof(char), temp->count, file);

	return temp;
}

int getsize(FILE* file) {
	fseek(file, 0, SEEK_END);
	int size = ftell(file);
	fseek(file, 0, SEEK_SET);
	return size;
}

