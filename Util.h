#pragma once
class Util
{
public:
	static void createMatrixFile(char* name, int rows, int columns);
	int** readMatrix(char* name);
	void writeMatrixInFile(char* name, int** result, int rows, int columns);
	int** createEmptyMatrix(int rows, int columns);
	int* readApproximation(char* name);
	void writeResult(char* name,int result);
	Util() {}
};

