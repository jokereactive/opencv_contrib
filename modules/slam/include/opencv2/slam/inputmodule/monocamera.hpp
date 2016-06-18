/*
By downloading, copying, installing or using the software you agree to this
license. If you do not agree to this license, do not download, install,
copy or use the software.

                          License Agreement
               For Open Source Computer Vision Library
                       (3-clause BSD License)

Copyright (C) 2013, OpenCV Foundation, all rights reserved.
Third party copyrights are property of their respective owners.

Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

  * Redistributions of source code must retain the above copyright notice,
    this list of conditions and the following disclaimer.

  * Redistributions in binary form must reproduce the above copyright notice,
    this list of conditions and the following disclaimer in the documentation
    and/or other materials provided with the distribution.

  * Neither the names of the copyright holders nor the names of the contributors
    may be used to endorse or promote products derived from this software
    without specific prior written permission.

This software is provided by the copyright holders and contributors "as is" and
any express or implied warranties, including, but not limited to, the implied
warranties of merchantability and fitness for a particular purpose are
disclaimed. In no event shall copyright holders or contributors be liable for
any direct, indirect, incidental, special, exemplary, or consequential damages
(including, but not limited to, procurement of substitute goods or services;
loss of use, data, or profits; or business interruption) however caused
and on any theory of liability, whether in contract, strict liability,
or tort (including negligence or otherwise) arising in any way out of
the use of this software, even if advised of the possibility of such damage.
*/

#ifndef __OPENCV_MONOCAMERA_HPP__
#define __OPENCV_MONOCAMERA_HPP__

//General
#include <opencv2/core.hpp>
#include <opencv2/calib3d.hpp>
#include <opencv2/highgui.hpp>
#include <vector>
#include <iostream>
#include <fstream>

//Slam Related
#include <opencv2/slam/inputmodule/camera.hpp>
#include <opencv2/slam/inputmodule/dataset.hpp>
#include <opencv2/slam/inputmodule/monocamera.hpp>
#include <opencv2/slam/inputmodule/monocameradataset.hpp>

//Data Structures
#include "opencv2/slam/datastructures/affinepose.hpp"
#include "opencv2/slam/datastructures/charucoframe.hpp"
#include "opencv2/slam/datastructures/charucomappoint.hpp"

#include <opencv2/slam/inputmodule/camera.hpp>
#include <opencv2/slam/utilities/logger.hpp>


namespace cv {
  namespace slam {
    /**
     * @brief Camera
     * This is an abstract class to create various implementations of cameras this SLAM system may support
     */
    class Camera;

    class MonoCamera: public Camera {
      private:
        Mat camMatrix;
        Mat distCoeffs;
        VideoCapture inputVideo;
        std::string video;
        int camId;
        int waitTime;

      public:
        MonoCamera(std::string configPath);
        bool initialize(std::string configPath);
        bool readCameraParameters(std::string filename);
        bool readCameraSource(std::string camerasourcePath);
        void start();
        Mat getFrame();
        Mat getCamMatrix(){
                return camMatrix;
        }
        Mat getDistCoeffs(){
                return distCoeffs;
        }
    };
  }
}

#endif
