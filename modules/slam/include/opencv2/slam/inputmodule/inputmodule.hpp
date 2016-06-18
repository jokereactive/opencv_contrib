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

#ifndef __OPENCV_INPUTMODULE_HPP__
#define __OPENCV_INPUTMODULE_HPP__

//General
#include <opencv2/core.hpp>
#include <opencv2/calib3d.hpp>
#include <opencv2/highgui.hpp>
#include <vector>
#include <iostream>
#include <fstream>
#include <cstddef>

//Slam Related
#include <opencv2/slam/inputmodule/camera.hpp>
#include <opencv2/slam/inputmodule/dataset.hpp>
#include <opencv2/slam/inputmodule/monocamera.hpp>
#include <opencv2/slam/inputmodule/monocameradataset.hpp>
#include <opencv2/slam/utilities/logger.hpp>


namespace cv {
  namespace slam {
    /**
     * @brief Input Module
     * Specific class for Input Segment of the SLAM System. 
     * This class is a factory class and can be used to generate cameras and datasets
     * It can also be used to run dataset slam.
     */
    class Camera;
    class Dataset;
    class MonoCamera;
    class MonoCameraDataset;

    class CV_EXPORTS_W InputModule {
      public:
        /**
         * @brief Create a Camera object
         *
         * @param cameraConfigPath path of the config file containing the camera parameters
         * @return the output camera object
         *
         * This functions creates a Camera Object given the Camera Type obtained from the cameraConfigPath. Example - Mono Camera, RGBD Camera, etc.
         */
        Camera* createCamera(std::string cameraConfigPath);

        /**
         * @brief Create a Dataset object
         *
         * @param dataSetPath path of the dataset folder
         *
         * This functions creates a Dataset Object given the Camera Type obtained from the cameraConfigPath. Example - Mono Camera, RGBD Camera, etc.
         */
        Dataset* createDataset(std::string datasetConfigPath);
    };
  }
}


#endif
