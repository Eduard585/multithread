#include "Util.h"
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <ctime>

void Util::createMatrixFile(char* name, int rows, int columns) {
	std::ofstream f1(name);
	srand(time(NULL));
	f1.setf(std::ios_base::binary, std::ios_base::trunc);
	f1 << rows << " " << columns << std::endl;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			int value = rand() % 100 + 1;
			f1 << value << " ";
		}
		f1 << std::endl;
	}
	f1.close();
}

int** Util::readMatrix(char* name) {
	std::ifstream file(name);
	int rows, columns;
	int** matrix;
	file >> rows >> columns;
	matrix = new int* [rows];
	for (int row = 0; row < rows; row++) {
		matrix[row] = new int[columns];
		for (int column = 0; column < columns; column++) {
			file >> matrix[row][column];
		}
	}
	file.close();
	return matrix;
}
void Util::writeMatrixInFile(char* name, int** result, int rows, int columns) {
	std::ofstream f1(name, std::ios::out | std::ios::trunc);
	f1 << rows << " " << columns << std::endl;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			f1 << result[i][j] << " ";
		}
		f1 << std::endl;
	}
	f1.close();
}

void Util::writeResult(char* name, int result) {
	std::ofstream f1(name, std::ios::out | std::ios::app);
	f1 << result << " ";
	f1.close();
}

int** Util::createEmptyMatrix(int rows, int columns) {
	int** result;
	result = new int* [rows];
	for (int row = 0; row < rows; row++) {
		result[row] = new int[columns];
		for (int column = 0; column < columns; column++) {
			result[row][column] = 0;
		}		
	}
	return result;
}

int* Util::readApproximation(char* fileName) {
	std::ifstream file(fileName);
	int length;
	int* result;
	file >> length;
	result = new int[length];
	for (int i = 0; i < length; i++) {
		file >> result[i];
	}
	file.close();
	return result;
}