// Name: Maroof Mohammed Farooq// HW P2// Image Processing#include <stdio.h>#include <iostream>#include <stdlib.h>#include <vector>#include <fstream>#include <iterator>#include <math.h>#include <map>#include "opencv2/imgproc/imgproc.hpp"#include "opencv2/highgui/highgui.hpp"#include "imageData.h"#include "imageAlgorithms.h"#include "matrix.h"using namespace std;using namespace cv;Mat src, src_gray;Mat dst;int main(int argc, char *argv[]) {	// Define file pointer and variables	int BytesPerPixel;	int imageWidth;	int imageHeight;	int problemNumber;//----------------------------------------------------------------------------------------------------------------//	// Check for proper syntax	if (argc < 3) {		cout << "Syntax Error - Incorrect Parameter Usage:" << endl;		cout <<		"program_name input_image.raw output_image.raw [BytesPerPixel = 1] [imageWidth = 256] [imageHeight = 256]" <<		endl;		return 0;	}	// Check if image is grayscale or color	if (argc < 4) {		BytesPerPixel = 1;// default is grey image		imageHeight = 256;		imageWidth = 256;	}	else {		BytesPerPixel = atoi(argv[3]);		// Check if size is specified		if (argc >= 5) {			imageWidth = atoi(argv[4]);			imageHeight = atoi(argv[5]);		}		else {			imageHeight = 256;			imageWidth = 256;		}	}	problemNumber = atoi(argv[6]);//----------------------------------------------------------------------------------------------------------------//// input and output file names	string inputFileName = argv[1];	string outputFileName = argv[2];//----------------------------------------------------------------------------------------------------------------//// 1(a) Texture Classification	if (problemNumber == 1) {		// Reading additional arguments:		if(argc!=8){			cout<< "Incorrect number of arguments for problem 1!" <<endl;			exit(0);		}		int trainingSize = atoi(argv[7]);		// Read 12 training images		vector<imageData*> trainingImages;		vector<Mat> matFiles;		for(int i = 1; i<=trainingSize; i++){			imageData* trainImage = new imageData(BytesPerPixel,imageWidth,imageHeight);			trainImage->imageRead(("HW3 Images/P1/Texture"+to_string(i)+".raw").c_str());			Mat tempImage = trainImage->convertToMat();			trainingImages.push_back(trainImage);			matFiles.push_back((tempImage));			delete(trainImage);			tempImage.release();		}		// Create Law's filter		imageAlgorithms filterCreater(trainingImages[0]);		map<int,matrix<int,double> > filterBank = filterCreater.getLawsFilter();		// Print Filters//		for(int i = 0; i< 25;i++){//			filterBank[i].printMatrix();//		}//		namedWindow( "Display window", WINDOW_AUTOSIZE );// Create a window for display.//		imshow( "Display window", (matFiles[1]));                   // Show our image inside it.//		waitKey(0);                                          // Wait for a keystroke in the	}	return 0;}