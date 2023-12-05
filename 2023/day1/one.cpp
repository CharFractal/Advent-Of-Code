#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<stdlib.h>

int extractInt(std::string str);


int main(int argc , char** argv){

	int final = 0;
	std::ifstream myfile(argv[1]);
	std::string test;
	if(myfile.is_open()){
		while(std::getline(myfile , test)){
			final += extractInt(test);
		}
		myfile.close();
		std::cout << "final : "<< final <<std::endl;
	}else{
		std::cout<<"Unable to open the file"<<std::endl;
	}

	return 0;
};

int extractInt(std::string str) {
	int first = 0 ;
	int last = 0 ;
	int count = -1;
	for (char c : str) {
		if (isdigit(c)) {
			std::cout << c <<std::endl;
			if(count){
				first = (c - '0');
				count++;
			}else{
				last = (c - '0');
			}
		}
	}
	if(last){
		first = first*10 ;
	}else{
		first = first*10 + first;
	}
	first += last;
	std::cout<<"total : "<<first<<std::endl<<std::endl;
	return first;
}
