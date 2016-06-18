//General
#include <opencv2/core.hpp>
#include <opencv2/calib3d.hpp>
#include <opencv2/highgui.hpp>
#include <vector>
#include <iostream>
#include <fstream>

#include <opencv2/slam/charucoslamsystem.h>

int main(){
    CharucoSlamSystem* charucoSlamSystem = new charucoSlamSystem("/home/sarthak/GSOC/opencv_contrib/modules/slam/charuco_slam");
    charucoSlamSystem->startLive();
    return 0;
}
