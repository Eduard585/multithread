#include "Util.h"
#include <iostream>
#include <fstream>

void Util::createMatrixFile(char* name, int rows, int columns) {
	std::ofstream f1(name, std::ios::out | std::ios::app);
	f1 << rows << " " << columns << std::endl;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			f1 << (double)(rand()) / rand() << " ";
		}
		f1 << std::endl;
	}
	f1.close();
}

double** Util::readMatrix(char* name) {
	std::ifstream file(name);
	int rows, columns;
	double** matrix;
	file >> rows >> columns;
	matrix = new double* [rows];
	for (int row = 0; row < rows; row++) {
		matrix[row] = new double[columns];
		for (int column = 0; column < columns; column++) {
			file >> matrix[row][column];
		}
	}
	file.close();
	return matrix;
}
void Util::writeMatrixInFile(char* name, double** result, int rows, int columns) {
	std::ofstream f1(name, std::ios::out | std::ios::app);
	f1 << rows << " " << columns << std::endl;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			f1 << result[i][j] << " ";
		}
		f1 << std::endl;
	}
	f1.close();
}

double** Util::createEmptyMatrix(int rows, int columns) {
	double** result;
	result = new double* [rows];
	for (int row = 0; row < rows; row++) {
		result[row] = new double[columns];
	}
	return result;
}

double* Util::readApproximation(char* fileName) {
	std::ifstream file(fileName);
	int length;
	double* result;
	file >> length;
	result = new double[length];
	for (int i = 0; i < length; i++) {
		file >> result[i];
	}
	file.close();
	return result;
}