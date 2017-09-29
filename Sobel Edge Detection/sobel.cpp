#include "sobel.h"
#include <cmath>

void SobelEdge(const unsigned char *image, int *G, const int numOfRows, const int numOfCols)
{
	// This function convolve the image with a Sobel filter in one dimention using
	// separable convolution, see(https://blogs.mathworks.com/steve/2006/10/04/separable-convolution/)
	// and (https://en.wikipedia.org/wiki/Sobel_operator)
	// image is numOfRows*numOfCols matrix rearranged to 1D array in row-major order	
	
	int *Gx = new int[numOfRows * numOfCols]; // gradient along x
	int *Gy = new int[numOfRows * numOfCols]; // gradient along y	

	int A[3] = { 1, 0, -1 }; // filter kernel
	int B[3] = { 1, 2, 1 };

	int *g_1 = new int[numOfRows * numOfCols]; // temporary array
	int *g_2 = new int[numOfRows * numOfCols];

	int r = 0, c = 0; // row and column index
		
	int index = 0;
	for (int i = 0; i < numOfRows; i++) // first and last columns
	{		
		index = i * numOfCols + 0;
		g_1[index] = A[1] * image[index] + A[2] * image[index + 1];
		g_2[index] = B[1] * image[index] + B[2] * image[index + 1];

		index = i * numOfCols + numOfCols - 1;
		g_1[index] = A[0] * image[index - 1] + A[1] * image[index];
		g_2[index] = B[0] * image[index - 1] + B[1] * image[index];
	}
	for (int i = 0; i < numOfRows; i++) // 2 to numOfClos -1 columns
	{
		for (int j = 1; j < numOfCols - 1; j++)
		{			
			index = i * numOfCols + j;
			g_1[index] = A[0] * image[index - 1] + A[1] * image[index] + A[2] * image[index + 1];
			g_2[index] = B[0] * image[index - 1] + B[1] * image[index] + B[2] * image[index + 1];
		}
	}

	for (int j = 0; j < numOfCols; j++) // first and last rows
	{
		index = j;
		Gx[index] = B[1] * g_1[index] + B[2] * g_1[index + numOfCols];
		Gy[index] = A[1] * g_2[index] + A[2] * g_2[index + numOfCols];
		G[index] = abs(Gx[index]) + abs(Gy[index]);

		index = (numOfRows - 1) * numOfCols + j;
		Gx[index] = B[0] * g_1[index - numOfCols] + B[1] * g_1[index];
		Gy[index] = A[0] * g_2[index - numOfCols] + A[1] * g_2[index];
		G[index] = abs(Gx[index]) + abs(Gy[index]);
	}
	for (int i = 1; i < numOfRows - 1; i++) // 2 to numOfRows - 1 rows
	{
		for (int j = 0; j < numOfCols; j++)
		{
			index = i * numOfCols + j;
			Gx[index] = B[0] * g_1[index - numOfCols] + B[1] * g_1[index] + B[2] * g_1[index + numOfCols];
			Gy[index] = A[0] * g_2[index - numOfCols] + A[1] * g_2[index] + A[2] * g_2[index + numOfCols];

			G[index] = abs(Gx[index]) + abs(Gy[index]);
		}
	}
		
	delete Gx;
	delete Gy;
	delete g_1;
	delete g_2;
}