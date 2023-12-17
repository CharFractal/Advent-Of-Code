#include<stdio.h>
#include<assert.h>
#include<unistd.h>
#include<stdlib.h>
#include<ctype.h>

int totalPoints(FILE* file);
int cardPoints(char* line);

int main(){

	FILE* file = fopen("input.txt" , "r");
	assert(file != NULL && "failed to open the file");

	printf("total points : %d" , totalPoints(file));
	fclose(file);
	return 0;
}

int totalPoints(FILE* file){

	char* line = NULL;
	size_t linelen = 0;
	int total = 0;
	while(getline(&line , &linelen , file) != -1){

		total += cardPoints(line);
	}

	free(line);
	return total;
}

int cardPoints(char* line){

	int* digits = malloc(sizeof(int) * 36);

	printf("%s" , line);
	int i = 0;
	int j = 0;

	while(line[i] != '\n'){

		if(isdigit(line[i])){

			digits[j] = 0;
			int o = 0;
			while(isdigit(line[i+o])){

				digits[j] *= 10;
				digits[j] += (line[i+o] - '0');
				o++;
			}
			j++;
			i+=o;
		}else{

			i++;
		}
	}

	int count = 0;
	for(int i = 11 ; i < 36 ; i++){

		for(int j = 1 ; j < 11 ; j++){
			if(digits[i] == digits[j]){
			
				printf("%d : %d\n" , digits[i] , digits[j]);
				count++;
			}
		}	
	}

	if(count == 0) return 0;

	int total = 1;
	while(--count){
		total *= 2;
		
	}
	printf("cardtotal : %d\n" , total);
	free(digits);
	return total;
}


