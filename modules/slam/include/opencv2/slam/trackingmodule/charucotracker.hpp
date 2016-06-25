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

#ifndef __OPENCV_MAPPER_HPP__
#define __OPENCV_MAPPER_HPP__

//General
#include <opencv2/core.hpp>
#include <opencv2/calib3d.hpp>
#include <opencv2/highgui.hpp>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>

#include <opencv2/aruco.hpp>
#include <opencv2/aruco/charuco.hpp>

// Data Structures
#include <opencv2/slam/trackingmodule/tracker.hpp>
#include <opencv2/slam/datastructures/charucoframe.hpp>
#include <opencv2/slam/inputmodule/monocamera.hpp>
#include <opencv2/slam/datastructures/affinepose.hpp>
#include <opencv2/slam/datastructures/charucomappoint.hpp>
#include <opencv2/slam/utilities/logger.hpp>
#include <opencv2/slam/representationmodule/keyframegraphrepresenter.hpp>


namespace cv {
  namespace slam {
    class MonoCamera;
    /**
     * @brief CharucoTracker
     * This is an abstract class to create various implementations of mappers this SLAM system may support
     */
    class CharucoTracker: public Tracker{
    public:
      CharucoTracker(int lastN, std::string configPath, MonoCamera *monoCamera);

      // Aruco Related Funtions
      bool readDetectorParameters(std::string filename, Ptr<aruco::DetectorParameters> &params);

      bool trackFrame(CharucoFrame* charucoFrame, KeyFrameGraph* KeyFrameGraph);
      void refinePoses(KeyFrameGraph* KeyFrameGraph);

      bool configAruco(std::string filename);

     private:

      // Aruco Related Variables

      float squareLength;
      float markerLength;
      int dictionaryId;

      // Camera Pointer For Tracker
      MonoCamera* monoCamera;

      //Detector Parameters
      Ptr<aruco::DetectorParameters> detectorParams;

    };
  }
}

#endif