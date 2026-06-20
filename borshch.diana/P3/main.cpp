#include <iostream>
#include <fstream>
#include <cstdlib>
#include <climits>

int main(int argc, char* argv[]){
	
	if (argc != 4) {
           if (argc < 4) {
              std::cerr << "not enough arguments" << std::endl;
        } else {
           std::cerr << "too many arguments" << std::endl;
        }
        return 1;
	}

	char num = argv[1][0];
	if (num != '1' || num != '2') {
    	   std::cerr << "first parameter must be 1 or 2" << std::endl;
    	return 1;
	}
        std::ifstream inputFile(argv[2]);
        if (!inputFile.is_open()) {
	   std::cerr << "can't open file" << std::endl;
	   return 2;
	}
	
	int rows, cols;
	if (!(inputFile >> rows >> cols)) {
	   std::cerr << "NOT numbers" << std::endl;
	   inputFile.close();
	   return 2;
	}
	if (rows <= 0 || cols <= 0) {
	   std::cerr << "NOT real numbers" << std::endl;
           inputFile.close();
           return 2;
        }
	if (num == 1) {
           int totalElements = rows * cols;
           if (totalElements > 10000) {
              std::cerr << "A LOT of elements, more than 10_000" << std::endl;
              inputFile.close();
              return 2;
           }
        }

	int** matrix = nullptr;
	if (num == 1) {
	const int MAX_SIZE = 10000;
    	if (rows * cols > MAX_SIZE) {
           std::cerr << "Matrix exceeds fixed array size limit" << std::endl;
           inputFile.close();
           return 2;
    	}
    
    	matrix = new int*[rows];
    	for (int i = 0; i < rows; i++) {
           matrix[i] = new int[cols];
    	   }
	} else {
	   matrix = new int*[rows];
           for (int i = 0; i < rows; i++) {
              matrix[i] = new int[cols];
           }
        }
	for (int i = 0; i < rows; i++) {
           for (int j = 0; j < cols; j++) {
              if (!(inputFile >> matrix[i][j])) {
                 std::cerr << "сan't read element" << std::endl;
                 for (int k = 0; k < rows; k++) {
                    delete[] matrix[k];
                 }
                 delete[] matrix;
                 inputFile.close();
                 return 2;
              }
           }
        }
        inputFile.close();








return 0;
}
