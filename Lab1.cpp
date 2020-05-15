#include <iostream>
#include <fstream>
#include <windows.h>
#include <omp.h>

#include <iostream>
#include "Util.h"

//OPTIONS
ULONGLONG dwStart;
Util util;
long long rows1 = 1500;// Количество строк первой матрицы
long long columns2 = 1500;// Количество столбцов второй матрицы
long long inter21 = 1500; // Количество столбцов первой матрицы и строк для второй
int threadsNum = 8;
int chunkSize = 1;

void multiply(int** a, int** b, int** c);
void multiplyWithParallel(int** a, int** b, int** c);
void multiMatrixOneCycle(int** a, int** b, int** c);
int* createResultMatrixFillZero();
void start();


int main()
{
	/*for (int i = 500; i < 2000; i += 250) {
		rows1 = columns2 = inter21 = i;
		start();
		std::ofstream f1("timeResult.txt", std::ios::out | std::ios::app);
		f1 << std::endl;
		f1.close();
	}*/
	omp_set_num_threads(threadsNum);
	start();
}

void start() {
	int** a = nullptr, ** b = nullptr, ** c;
	int* cc;

	util.createMatrixFile((char*)("matrix1.txt"), rows1, inter21);
	util.createMatrixFile((char*)("matrix2.txt"), inter21, columns2);

	a = util.readMatrix((char*)"matrix1.txt");
	b = util.readMatrix((char*)"matrix2.txt");
	c = util.createEmptyMatrix(rows1, columns2);
	cc = createResultMatrixFillZero();

	multiply(a, b, c);
	util.writeMatrixInFile((char*)"resultOneThread.txt", c, rows1, columns2);
	multiplyWithParallel(a, b, c);
	c = util.createEmptyMatrix(rows1, columns2);
	multiMatrixOneCycle(a, b, c);
	util.writeMatrixInFile((char*)"resultOneCycle.txt", c, rows1, columns2);
	
}

void multiply(int** a, int** b, int** c) {
	dwStart = GetTickCount64();
	for (int row = 0; row < rows1; row++) {
		for (int column = 0; column < columns2; column++) {
			c[row][column] = 0;
			for (int inter = 0; inter < inter21; inter++) {
				c[row][column] += a[row][inter] * b[inter][column];
			}
		}
	}
	ULONGLONG result = GetTickCount64() - dwStart;
	printf_s("No parallel: %I64d ms\n", result);
	util.writeResult((char*)"timeResult.txt", result);
}

void multiplyWithParallel(int** a, int** b, int** c) {
	dwStart = GetTickCount64();

#pragma omp parallel shared(c)
	{
#pragma omp for schedule(static,chunkSize)
		for (int row = 0; row < rows1; row++) {
			for (int column = 0; column < columns2; column++) {
				c[row][column] = 0;
				for (int inter = 0; inter < inter21; inter++) {
					c[row][column] += a[row][inter] * b[inter][column];
				}
			}
		}
	}
	
	ULONGLONG result = GetTickCount64() - dwStart;
	printf_s("Simple parallel for: %I64d ms\n", result);
	util.writeResult((char*)"timeResult.txt", result);
}

void multiMatrixOneCycle(int** a, int** b, int** c) {
	long long count = rows1 * columns2 * inter21;
	long long temp = 0, column = 0, row = 0, i = 0;
	dwStart = GetTickCount64();

#pragma omp parallel shared(c,i) private(row,column,temp) 
	{
#pragma omp for schedule(static,chunkSize)
		for (i = 0; i < count; i++) {
			row = i / (inter21 * columns2);
			column = (i / inter21) % columns2;
			temp = i % inter21;

			c[row][column] += a[row][temp] * b[temp][column];
		}
	}		
		
	ULONGLONG result = GetTickCount64() - dwStart;
	printf_s("One cycle: %I64d ms\n", result);
	util.writeResult((char*)"timeResult.txt", result);
}

int* createResultMatrixFillZero() {
	int* result;
	result = new int[rows1 * columns2];
	for (int64_t i = 0; i < rows1 * columns2; i++) {
		result[i] = 0;
	}
	return result;
}
