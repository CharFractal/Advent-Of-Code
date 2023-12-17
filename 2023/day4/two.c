#include<stdio.h>
#include<assert.h>
#include<unistd.h>
#include<stdlib.h>
#include<ctype.h>

int scratchcards(FILE* file);
int getmatches(char* line);
int main(){

	FILE* file = fopen("input.txt" , "r");
	assert(file != NULL && "failed to open the file");

	printf("scratchcards : %d", scratchcards(file));
	fclose(file);
	return 0;
}

int scratchcards(FILE* file){

	char c ;
	int rows = 0;
	while((c = getc(file)) != EOF){
		if( c == '\n') rows++;
	}
	fseek(file, 0, SEEK_SET);

	//get cards
	int* cards = malloc(sizeof(int) * rows);
	assert(cards != NULL && "failed to make cards array !");

	//fill 1
	for(int i = 0 ;i < rows ; i++){	
		cards[i] = 1;
	}

	//get copies
	int matches = 0;
	int index = 0;
	char* card = NULL;
	size_t linelen = 0;

	while(getline(&card , &linelen , file) != -1){
		matches = getmatches(card);

		int i = 1;
		while((i <= matches) && (index + i  < rows)){

			cards[index + i] += cards[index];
			i++;
		}
		index++;
	}

	int total = 0;
	for (int i = 0; i < rows; ++i) {
		total += cards[i];

		printf("%d : %d\n",i , cards[i]);
	}

	free(card);
	free(cards);
	return total;
}

int getmatches(char* line){

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

	return count;
}
