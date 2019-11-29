#include <iostream>
#include <vector>
#include <mpi.h>
#include <fstream>
#include "Matrix.hpp"

using std::vector;
using std::cin;
using std::cout;
using std::endl;

void printMatrix(const my::matrix<double> &myMatrixScratch, int numProcs, int myRank)
{
	for (int i = 0; i < numProcs; ++i) 
	{
		if (myRank == i)
		{
			myMatrixScratch.print(cout);
		}
		MPI_Barrier(MPI_COMM_WORLD);
	}
}

void matrixCopyer(my::matrix<double> &copyTo, const my::matrix<double> &copyFrom)
{
	for (int i = 0; i < copyTo.num_rows(); i++)
	{
		for (int j = 0; j < copyTo.num_cols(); j++)
		{
			copyTo[i][j] = copyFrom[i][j];
		}
	}
}

void setupHeatSource(my::matrix<double> &mtx, int numHeats)
{
	for (int i = 0; i < numHeats; i++)
	{
		int heatStartRow, heatStartCol, heatEndRow, heatEndCol, heatTemp;
		cin >> heatStartRow >> heatStartCol >> heatEndRow >> heatEndCol >> heatTemp;

		if (heatStartRow == heatEndRow)
		{
			for (int i = heatStartCol; i < heatEndCol; i++)
			{
				mtx[heatStartRow][i] = heatTemp;
			}	
		}
		else
		{
			for (int i = heatStartRow; i < heatEndRow; i++)
			{
				mtx[i][heatStartCol] = heatTemp;
			}
		}
	}

	mtx.print(cout);
}
void setupLeftAndRightBorder(const my::matrix<double> &mtx, vector<double> &leftBorder, vector<double> &rightBorder)
{
	leftBorder.resize(mtx.num_rows() - 2);
	rightBorder.resize(mtx.num_rows() - 2);
	for (int i = 0; i < mtx.num_rows() - 2; i++)
	{
		leftBorder[i] = mtx[i + 1][0];
		rightBorder[i] = mtx[i + 1][mtx.num_cols() - 1];
	}
}

void calculateMyProcMatrix(my::matrix<double> &myMatrixScratch, const my::matrix<double> &myMatrix, const vector<double> &leftBorder, const vector<double> &rightBorder, vector<double> &rowAbove, const vector<double> &rowBelow, int rowPerProcs, int myRank)
{
	for (int i = 0; i < rowPerProcs; i++)
	{
		for (int j = 0; j < myMatrixScratch.num_cols(); j++)
		{
			double top(0), bottom(0), left(0), right(0);

			if (j == 0) { left = leftBorder[myRank * rowPerProcs + i]; }
			else { left = myMatrix[i][j - 1]; }
			
			if (j == myMatrixScratch.num_cols() - 1) { right = rightBorder[myRank * rowPerProcs + i]; }
			else { right = myMatrix[i][j + 1]; }

			if (i == 0) { top = rowAbove[j]; }
			else { top = myMatrix[i - 1][j]; }

			if (i == rowPerProcs - 1) { bottom = rowBelow[j]; }
			else { bottom = myMatrix[i + 1][j]; }

			myMatrixScratch[i][j] = (left + right + top + bottom) / 4.0;
		}
	}
}


int main(int argc, char* argv[]) {
	MPI_Init(&argc, &argv);

	int numProcs;
	MPI_Comm_size(MPI_COMM_WORLD, &numProcs);

	int myRank;
	MPI_Comm_rank(MPI_COMM_WORLD, &myRank);
	const int MPI_TAG = 0;

	int numRows(0);
	int numCols(0);
	int numHeats(0);
	int matrixSize(0);
	my::matrix<double> mtx;
	vector<double> leftBorder;
	vector<double> rightBorder;
	std::ofstream fout;

	if (myRank == 0)
	{
		fout.open("1.txt");
		// Geting info from user and setting up original matrix
		cin >> numRows >> numCols >> numHeats;
		// numRows = 8;
		// numCols = 4;
		// numHeats = 1;
		matrixSize = (numRows + 2) * (numCols + 2);
		mtx.resize(numRows + 2, numCols + 2);
		setupHeatSource(mtx, numHeats);
		setupLeftAndRightBorder(mtx, leftBorder, rightBorder);
	}
	
	cout << "Setup finished" << endl;

	MPI_Bcast(&numRows, 1, MPI_INT, 0, MPI_COMM_WORLD);
	MPI_Bcast(&numCols, 1, MPI_INT, 0, MPI_COMM_WORLD);
	MPI_Bcast(&matrixSize, 1, MPI_INT, 0, MPI_COMM_WORLD);
	leftBorder.resize(numRows);
	rightBorder.resize(numRows);
	MPI_Bcast(leftBorder.data(), leftBorder.size(), MPI_DOUBLE, 0, MPI_COMM_WORLD);
	MPI_Bcast(rightBorder.data(), rightBorder.size(), MPI_DOUBLE, 0, MPI_COMM_WORLD);

	int rowPerProcs = numRows / numProcs;
	my::matrix<double> myMatrix(rowPerProcs, numCols);
	my::matrix<double> myMatrixScratch(rowPerProcs, numCols);
	vector<double> rowAbove(numCols);
	vector<double> rowBelow(numCols);
	if (myRank == 0)
	{
		// The first row will take the first row in the mtx as row above.
		for (int i = 0; i < numCols; i++) { rowAbove[i] = mtx[0][i + 1]; }

		// Send the last row to last processor
		vector<double> temp(numCols);
		for (int i = 0; i < numCols; i++) { temp[i] = mtx[numCols + 1][i + 1]; }
		MPI_Send(temp.data(), numCols, MPI_DOUBLE, numProcs - 1, MPI_TAG, MPI_COMM_WORLD);
	}
	else if (myRank == numProcs - 1)
	{
		MPI_Recv(rowBelow.data(), numCols, MPI_DOUBLE, 0, MPI_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
	}

	int iteration(0);
	int numOfChangedSlots(0);
	int totalOfChangeSlots(0);

	MPI_Barrier(MPI_COMM_WORLD);

	calculateMyProcMatrix(myMatrixScratch, myMatrix, leftBorder, rightBorder, rowAbove, rowBelow, rowPerProcs, myRank);
	numOfChangedSlots = calculateChanged(myMatrix, myMatrixScratch);
	matrixCopyer(myMatrix, myMatrixScratch);
	MPI_Allreduce(&numOfChangedSlots, &totalOfChangeSlots, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);
	printMatrix(myMatrixScratch, numProcs, myRank);

	// Loop until total slots no change
	while (totalOfChangeSlots != 0)
	{
		if (myRank % 2 == 0)	//	If rank 0, 2, 4...2n
		{
			if (myRank == 0)	// First Processor, rank == 0
			{
				vector<double> temp(numCols);
				for (int i = 0; i < numCols; i++) { temp[i] = myMatrixScratch[rowPerProcs - 1][i]; }
				MPI_Send(temp.data(), numCols, MPI_DOUBLE, 1, MPI_TAG, MPI_COMM_WORLD);

				MPI_Recv(rowBelow.data(), numCols, MPI_DOUBLE, 1, MPI_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			}
			else				// rank = 2, 4, 6...
			{
				vector<double> up(numCols);
				for (int i = 0; i < numCols; i++) { up[i] = myMatrixScratch[rowPerProcs - 1][i]; }
				MPI_Send(up.data(), numCols, MPI_DOUBLE, myRank + 1, MPI_TAG, MPI_COMM_WORLD);

				vector<double> down(numCols);
				for (int i = 0; i < numCols; i++) { down[i] = myMatrixScratch[0][i]; }
				MPI_Send(down.data(), numCols, MPI_DOUBLE, myRank - 1, MPI_TAG, MPI_COMM_WORLD);

				MPI_Recv(rowBelow.data(), numCols, MPI_DOUBLE, myRank + 1, MPI_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
				MPI_Recv(rowAbove.data(), numCols, MPI_DOUBLE, myRank - 1, MPI_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			}
		}
		else							// else if rank 1, 3, 5...2n-1
		{
			if (myRank == numProcs - 1)	// Last processor 2n-1
			{
				MPI_Recv(rowAbove.data(), numCols, MPI_DOUBLE, myRank - 1, MPI_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

				vector<double> up(numCols);
				for (int i = 0; i < numCols; i++) { up[i] = myMatrixScratch[rowPerProcs - 1][i]; }
				MPI_Send(up.data(), numCols, MPI_DOUBLE, myRank - 1, MPI_TAG, MPI_COMM_WORLD);
			}
			else						// rank == 1, 3, 5...2n-3
			{
				MPI_Recv(rowBelow.data(), numCols, MPI_DOUBLE, myRank + 1, MPI_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
				MPI_Recv(rowAbove.data(), numCols, MPI_DOUBLE, myRank - 1, MPI_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

				vector<double> down(numCols);
				for (int i = 0; i < numCols; i++) { down[i] = myMatrixScratch[rowPerProcs - 1][i]; }
				MPI_Send(down.data(), numCols, MPI_DOUBLE, myRank + 1, MPI_TAG, MPI_COMM_WORLD);

				vector<double> up(numCols);
				for (int i = 0; i < numCols; i++) { up[i] = myMatrixScratch[0][i]; }
				MPI_Send(up.data(), numCols, MPI_DOUBLE, myRank - 1, MPI_TAG, MPI_COMM_WORLD);
			}
		}

		calculateMyProcMatrix(myMatrixScratch, myMatrix, leftBorder, rightBorder, rowAbove, rowBelow, rowPerProcs, myRank);
		numOfChangedSlots = calculateChanged(myMatrix, myMatrixScratch);
		matrixCopyer(myMatrix, myMatrixScratch);
		MPI_Allreduce(&numOfChangedSlots, &totalOfChangeSlots, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);

		if (myRank == 0)
		{
			iteration++;
			fout << totalOfChangeSlots << endl;
		}
		
		printMatrix(myMatrixScratch, numProcs, myRank);
		
	}

	my::matrix<double> finalMatrix(numRows, numCols);
	MPI_Gather(myMatrixScratch.data(), myMatrixScratch.num_elements(), MPI_DOUBLE, finalMatrix.data(), myMatrixScratch.num_elements(), MPI_DOUBLE, 0, MPI_COMM_WORLD);

	if (myRank == 0)
	{
		cout << iteration << " iterations" << endl;
		finalMatrix.print(cout);
	}

	MPI_Finalize();
}