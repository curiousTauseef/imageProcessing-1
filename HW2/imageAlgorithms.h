//
// Created by Maroof Mohammed Farooq on 9/11/16.
//

#ifndef CPP_IMAGEALGORITHMS_H
#define CPP_IMAGEALGORITHMS_H

#include "matrix.h"
#include <map>

using namespace std;

class imageAlgorithms{
public:
    imageAlgorithms(imageData* imageObject1);
    ~imageAlgorithms(void);

    unsigned char bilinearInterpolation(double rowIndex, double columnIndex,double depthIndex=0.0);
    void histEqualization_tf();
    void histEqualization_cdf();
    void equalizationBasedOnReference(imageData referenceObject);
    void histEqualization_gaussian(double mean, double std);
    void psnr(imageData originalImage);
    void meanFilter(int windowSize);
    void medianFilter(int windowSize);
    void NLMFilter(int windowSize, int searchWindowSize, double decayFactor);
    void dithering(int indexMatrixSize,bool useGivenMatrix);
    void fourLevelDithering();
    void errorDiffusion(string algorithm);
    void binarize(double threshold, bool invert = false);
    void binarizeBasedOnMode(double radius,bool invert = false);
    void adaptiveBinarization(int windowSize);
    matrix<int,bool> charToBoolean();
    matrix<int,unsigned char> booleanToChar(matrix<int,bool> inputMatrix);

    matrix<int,double>  filterApply(imageData frame, matrix<int,double>  window,string algorithm);
    map<int,vector<int> > harrisCornerDetector(double RThreshold);

    matrix<int,bool> morphologicalAlgorithms(matrix<int,bool> binaryImageData, string operation);
    matrix<int,bool> holeFilling();
    matrix<int,bool> dilation_holeFilling(matrix<int,bool> seedMatrix, matrix<int,bool> inputMatrix);
    matrix<int,bool> dilation(matrix<int,bool> inputMatrix, int numberOfIter);
    matrix<int,bool> erosion(matrix<int,bool> inputMatrix, int numberOfIter);

    matrix<int,unsigned char> connectedComponentLabelling(matrix<int,bool> inputMatrix);



private:
    imageData* imageObject;
    matrix<int,int> bayerMat(int size);

    bool conditionalPatternMatching(string operation,int obtainedPattern);
    bool unconditionalPatternMatching(string operation,int obtainedPattern);
    map<int,int > hitMapDeveloper(vector<int> patternValues1,vector<int> patternValues2);
    map<int,vector<int>  > maskMapDeveloper(vector<int> maskValues, vector<int> patternValues1);
    int bound(int obtainedPattern);

};

#endif //CPP_IMAGEALGORITHMS_H
