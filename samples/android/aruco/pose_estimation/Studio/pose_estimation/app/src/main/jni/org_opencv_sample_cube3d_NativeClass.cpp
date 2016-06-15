#include <org_opencv_sample_cube3d_NativeClass.h>
#include <opencv2/highgui.hpp>
#include <opencv2/aruco/charuco.hpp>
#include <vector>
#include <iostream>

#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
using namespace cv;
using namespace cv::aruco;

#include <fstream>
#include <iostream>
#include <cstdlib>
using namespace std;

/**
 */
static bool readCameraParameters(string filename, Mat &camMatrix, Mat &distCoeffs) {
    FileStorage fs(filename, FileStorage::READ);
    if(!fs.isOpened())
        return false;
    fs["camera_matrix"] >> camMatrix;
    fs["distortion_coefficients"] >> distCoeffs;
    return true;
}

/**
 */
static bool readDetectorParameters(string filename, Ptr<aruco::DetectorParameters> &params) {
    FileStorage fs(filename, FileStorage::READ);
    if(!fs.isOpened())
        return false;
    fs["adaptiveThreshWinSizeMin"] >> params->adaptiveThreshWinSizeMin;
    fs["adaptiveThreshWinSizeMax"] >> params->adaptiveThreshWinSizeMax;
    fs["adaptiveThreshWinSizeStep"] >> params->adaptiveThreshWinSizeStep;
    fs["adaptiveThreshConstant"] >> params->adaptiveThreshConstant;
    fs["minMarkerPerimeterRate"] >> params->minMarkerPerimeterRate;
    fs["maxMarkerPerimeterRate"] >> params->maxMarkerPerimeterRate;
    fs["polygonalApproxAccuracyRate"] >> params->polygonalApproxAccuracyRate;
    fs["minCornerDistanceRate"] >> params->minCornerDistanceRate;
    fs["minDistanceToBorder"] >> params->minDistanceToBorder;
    fs["minMarkerDistanceRate"] >> params->minMarkerDistanceRate;
    fs["doCornerRefinement"] >> params->doCornerRefinement;
    fs["cornerRefinementWinSize"] >> params->cornerRefinementWinSize;
    fs["cornerRefinementMaxIterations"] >> params->cornerRefinementMaxIterations;
    fs["cornerRefinementMinAccuracy"] >> params->cornerRefinementMinAccuracy;
    fs["markerBorderBits"] >> params->markerBorderBits;
    fs["perspectiveRemovePixelPerCell"] >> params->perspectiveRemovePixelPerCell;
    fs["perspectiveRemoveIgnoredMarginPerCell"] >> params->perspectiveRemoveIgnoredMarginPerCell;
    fs["maxErroneousBitsInBorderRate"] >> params->maxErroneousBitsInBorderRate;
    fs["minOtsuStdDev"] >> params->minOtsuStdDev;
    fs["errorCorrectionRate"] >> params->errorCorrectionRate;
    return true;
}

JNIEXPORT void JNICALL Java_org_opencv_sample_cube3d_NativeClass_EstimatePose
        (JNIEnv * env, jobject obj, jlong inputImage){

    String cameraParams = "/sdcard/opencv-cube3d/calib.txt";
    String modelParams = "/sdcard/opencv-cube3d/detector_params.yml";

    float squareLength = 0.04;
    float markerLength = 0.02;
    int dictionaryId = 10;
    bool estimatePose = true;

    Ptr<aruco::DetectorParameters> detectorParams = aruco::DetectorParameters::create();

    bool readOk = readDetectorParameters(modelParams, detectorParams);

    if(!readOk) {
        cerr << "Invalid detector parameters file" << endl;
    }

    Ptr<aruco::Dictionary> dictionary =
        aruco::getPredefinedDictionary(aruco::PREDEFINED_DICTIONARY_NAME(dictionaryId));

    Mat camMatrix, distCoeffs;
    if(estimatePose) {
        bool readOk = readCameraParameters(cameraParams, camMatrix, distCoeffs);
        if(!readOk) {
            cerr << "Invalid camera file" << endl;
        }
    }

    Mat& image = *(Mat*)inputImage;

    if (image.empty())
    {
        std::cerr << "Can't read image from the file: " << image << std::endl;
        exit(-1);
    }

    vector< int > markerIds;
    vector< Vec4i > diamondIds;
    vector< vector< Point2f > > markerCorners, rejectedMarkers, diamondCorners;
    vector< Vec3d > rvecs, tvecs;

    // detect markers
    aruco::detectMarkers(image, dictionary, markerCorners, markerIds, detectorParams,
                         rejectedMarkers);

    // detect diamonds
    if(markerIds.size() > 0)
        aruco::detectCharucoDiamond(image, markerCorners, markerIds,
                                    squareLength / markerLength, diamondCorners, diamondIds,
                                    camMatrix, distCoeffs);

    // estimate diamond pose
    if(estimatePose && diamondIds.size() > 0) {
        // if autoscale, extract square size from last diamond id
        aruco::estimatePoseSingleMarkers(diamondCorners, squareLength, camMatrix,
                                                         distCoeffs, rvecs, tvecs);
    }

    if(markerIds.size() > 0){
            aruco::drawDetectedMarkers(image, markerCorners);
    }


    if(diamondIds.size() > 0) {
        aruco::drawDetectedDiamonds(image, diamondCorners, diamondIds);
        if(estimatePose) {
            for(unsigned int i = 0; i < diamondIds.size(); i++)
                aruco::drawAxis(image, camMatrix, distCoeffs, rvecs[i], tvecs[i],
                                squareLength * 0.5f);
        }

    }

}
