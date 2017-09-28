#include <iostream>

#include "sobel.h"
#include "CImg.h"

using namespace std;
using namespace cimg_library;

int main()
{
	CImg<unsigned char> image("valve.bmp");
				
	int numOfRows = image.height();
	int numOfCols = image.width();

	unsigned char *data = image.data();

	int *edge = new int[numOfRows * numOfCols];
	SobelEdge(data, edge, numOfRows, numOfCols);

	// display results
	CImg<unsigned char> imageEdge(edge, numOfCols, numOfRows);
	CImgDisplay src_disp(image, "source");
	CImgDisplay edge_disp(imageEdge, "edge");
	while (!src_disp.is_closed() || !edge_disp.is_closed())
	{
		src_disp.wait();
	}

	delete edge;
	
	return 0;	
}