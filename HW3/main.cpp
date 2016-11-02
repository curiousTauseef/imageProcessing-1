// Name: Maroof Mohammed Farooq// HW P2// Image Processing#include "headers.h"#include "imageData.h"#include "imageAlgorithms.h"#include "matrix.h"using namespace std;using namespace cv;Mat src, src_gray;Mat dst;int main(int argc, char *argv[]) {	// Define file pointer and variables	int BytesPerPixel;	int imageWidth;	int imageHeight;	int problemNumber;//----------------------------------------------------------------------------------------------------------------//	// Check for proper syntax	if (argc < 3) {		cout << "Syntax Error - Incorrect Parameter Usage:" << endl;		cout <<		"program_name input_image.raw output_image.raw [BytesPerPixel = 1] [imageWidth = 256] [imageHeight = 256]" <<		endl;		return 0;	}	// Check if image is grayscale or color	if (argc < 4) {		BytesPerPixel = 1;// default is grey image		imageHeight = 256;		imageWidth = 256;	}	else {		BytesPerPixel = atoi(argv[3]);		// Check if size is specified		if (argc >= 5) {			imageWidth = atoi(argv[4]);			imageHeight = atoi(argv[5]);		}		else {			imageHeight = 256;			imageWidth = 256;		}	}	problemNumber = atoi(argv[6]);//----------------------------------------------------------------------------------------------------------------//// input and output file names	string inputFileName = argv[1];	string outputFileName = argv[2];//----------------------------------------------------------------------------------------------------------------//// 1(a) Texture Classification	if(problemNumber ==1000){		imageData testImg(BytesPerPixel,imageWidth,imageHeight);		testImg.imageRead("HW3 Images/P1/Texture1.raw");		imageAlgorithms algo(&testImg);		matrix<int,double> testout = algo.subtractDC(testImg);		testout.printMatrix();	}	if (problemNumber == 1) {		// Reading additional arguments:		if(argc!=8){			cout<< "Incorrect number of arguments for problem 1!" <<endl;			exit(0);		}		int trainingSize = atoi(argv[7]);		// Read 12 training images		vector<imageData*> trainingImages;		vector<Mat> matFiles;		for(int i = 1; i<=trainingSize; i++){			imageData* trainImage = new imageData(BytesPerPixel,imageWidth,imageHeight);			trainImage->imageRead(("HW3 Images/P1/Texture"+to_string(i)+".raw").c_str());			Mat tempImage = trainImage->convertToMat();			trainingImages.push_back(trainImage);			matFiles.push_back((tempImage));		}		// Create object for image algorithms		imageAlgorithms lawsAlgorithm(trainingImages[0]);		// Step 1: Remove DC Component from filter		vector<matrix<int,double> > subtractedDCImages;		for_each(trainingImages.begin(),trainingImages.end(),[&](imageData* image){			subtractedDCImages.push_back(lawsAlgorithm.subtractDC(*image));		});		// Step 2: Create Law's filter		map<int,matrix<int,double> > filterBank = lawsAlgorithm.getLawsFilter();		// Step 3: Convolve laws filter with input image		map<int, matrix<int,double> > outputImages;		unordered_map<int, vector<double> > featureVectors;		featureVectors.reserve(trainingSize);		matrix<int,double> tempMatrix(imageHeight,imageWidth,BytesPerPixel);		double energyValue = 0;		int imageNumber = 0;		// Convolve all images		for_each(subtractedDCImages.begin(), subtractedDCImages.end(), [&](matrix<int,double> inputImage){			// Apply filter and calculate energy value			for_each(filterBank.begin(),filterBank.end(),[&](pair<int,matrix<int,double> > filter){				tempMatrix = lawsAlgorithm.filterApply(&inputImage,&get<1>(filter),"convolutionWithoutAbsolute");				energyValue = lawsAlgorithm.imageEnergy(tempMatrix);				featureVectors[imageNumber].push_back(energyValue);			});			imageNumber++;		});//		for_each(featureVectors[1].begin(), featureVectors[1].end(), [](double x){cout << x << endl;});//		namedWindow( "Display window", WINDOW_AUTOSIZE );// Create a window for display.//		imshow( "Display window", (matFiles[1]));                   // Show our image inside it.//		waitKey(0);                                          // Wait for a keystroke in the	}//----------------------------------------------------------------------------------------------------------------//// 2(a) Extraction and Description of Salient Points:	if(problemNumber ==4){		// Input Mat image://		Mat inputImage = imread(inputFileName);		// Convert image to grayscale//		Mat grayImage(imageHeight,imageWidth,CV_8UC1);//		cvtColor(inputImage,grayImage,CV_RGB2GRAY);		// Get SIFT points//		xfeatures2d::SIFT::create();//		int minHessian = 400;////		SiftFeatureDetector detector;//		vector<KeyPoint> keypoints_1;//		detector.detect( inputImage, keypoints_1);//		Mat img_keypoints_1;//		drawKeypoints( inputImage, keypoints_1, img_keypoints_1, Scalar::all(-1), DrawMatchesFlags::DEFAULT );//		imshow("Keypoints 1", img_keypoints_1 );//		waitKey(0);//		namedWindow("Image", WINDOW_AUTOSIZE);//		imshow("Image", inputImage);//		waitKey(0);//		Ptr<SIFT> sift = xfeatures2d::SIFT::create();//		Ptr<Feature2D> f2d = xfeatures2d::SIFT::create();	//---------------//		Mat img_1 = imread( "HW3\ Images/P2/rav4_2.jpg", CV_LOAD_IMAGE_GRAYSCALE );		Mat img_2 = imread( "HW3\ Images/P2/rav4_1.jpg", CV_LOAD_IMAGE_GRAYSCALE );		if( !img_1.data || !img_2.data )		{ printf(" --(!) Error reading images \n"); return -1; }		//-- Step 1: Detect the keypoints using SURF Detector		int minHessian = 400;		SiftFeatureDetector detector;		std::vector<KeyPoint> keypoints_1, keypoints_2;		detector.detect( img_1, keypoints_1 );		detector.detect( img_2, keypoints_2 );		//-- Step 2: Calculate descriptors (feature vectors)		SurfDescriptorExtractor extractor;		Mat descriptors_1, descriptors_2;		extractor.compute( img_1, keypoints_1, descriptors_1 );		extractor.compute( img_2, keypoints_2, descriptors_2 );		//-- Step 3: Matching descriptor vectors using FLANN matcher		FlannBasedMatcher matcher;		std::vector< DMatch > matches;		matcher.match( descriptors_1, descriptors_2, matches );		double max_dist = 0; double min_dist = 100;		//-- Quick calculation of max and min distances between keypoints		for( int i = 0; i < descriptors_1.rows; i++ )		{ double dist = matches[i].distance;			if( dist < min_dist ) min_dist = dist;			if( dist > max_dist ) max_dist = dist;		}		printf("-- Max dist : %f \n", max_dist );		printf("-- Min dist : %f \n", min_dist );		//-- Draw only "good" matches (i.e. whose distance is less than 2*min_dist,		//-- or a small arbitary value ( 0.02 ) in the event that min_dist is very		//-- small)		//-- PS.- radiusMatch can also be used here.		std::vector< DMatch > good_matches;		for( int i = 0; i < descriptors_1.rows; i++ )		{ if( matches[i].distance <= max(2*min_dist, 0.02) )			{ good_matches.push_back( matches[i]); }		}		//-- Draw only "good" matches		Mat img_matches;		drawMatches( img_1, keypoints_1, img_2, keypoints_2,					 good_matches, img_matches, Scalar::all(-1), Scalar::all(-1),					 vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS );		//-- Show detected matches		imshow( "Good Matches", img_matches );		for( int i = 0; i < (int)good_matches.size(); i++ )		{ printf( "-- Good Match [%d] Keypoint 1: %d  -- Keypoint 2: %d  \n", i, good_matches[i].queryIdx, good_matches[i].trainIdx ); }		waitKey(0);	}//----------------------------------------------------------------------------------------------------------------//// 3. Canny Edge detector:	if(problemNumber == 5){		// Read input image and convert to Mat		imageData inputImage(BytesPerPixel,imageWidth,imageHeight);		inputImage.imageRead(inputFileName.c_str());		Mat inputMatImage = inputImage.convertToMat();		//Set parameters of canny edge detector		int smootheningRadius = 5;		Mat grayImage(imageHeight,imageWidth,CV_8UC1);		cvtColor(inputMatImage,grayImage, CV_RGB2GRAY);		Mat outputMatImage(imageHeight,imageWidth,CV_8UC1);		// Apply Canny		Canny(grayImage,outputMatImage, 240,255,3,true);		// Display image		namedWindow("Image", WINDOW_AUTOSIZE);		imshow("Image", outputMatImage);		waitKey(0);	}	return 0;}