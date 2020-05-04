#pragma once
class Util
{
public:
	static void createMatrixFile(char* name, int rows, int columns);
	double** readMatrix(char* name);
	void writeMatrixInFile(char* name, double** result, int rows, int columns);
	double** createEmptyMatrix(int rows, int columns);
	double* readApproximation(char* name);
	Util() {}
};

