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

#ifndef __OPENCV_CHARUCOSLAMSYSTEM_HPP__
#define __OPENCV_CHARUCOSLAMSYSTEM_HPP__

//General
#include <opencv2/core.hpp>
#include <opencv2/calib3d.hpp>
#include <opencv2/highgui.hpp>
#include <vector>
#include <iostream>
#include <fstream>

//Slam Related
#include "opencv2/slam/slamsystem.hpp"

//Data Structures
#include "opencv2/slam/datastructures/affinepose.hpp"
#include "opencv2/slam/datastructures/charucoframe.hpp"
#include "opencv2/slam/datastructures/charucomappoint.hpp"
#include <opencv2/slam/utilities/logger.hpp>
#include <opencv2/slam/trackingmodule/charucotracker.hpp>


namespace cv {
  namespace slam {
    /**
     * @brief CharucoSlamSystem
     * This is an abstract class to create various implementations of cameras this SLAM system may support
     */
    class KeyFrameGraph;
    class CharucoMapper;
    class CharucoTracker;
    class VizVisualiser;
    class MonoCamera;
    class MonoDataset;

    class CharucoSlamSystem: public SlamSystem{
      private:
        KeyFrameGraph* keyFrameGraph;
        CharucoMapper* charucoMapper;
        CharucoTracker* charucoTracker;
        VizVisualiser* vizVisualiser;
        MonoCamera* monoCamera;
        MonoDataset* monoDataset;

        //Threading Needs to be added

        //Mapping Thread
        //boost::thread thread_mapping;

        //Tracking Thread
        //boost::thread thread_tracking;

      public:
        CharucoSlamSystem(std::string config):SlamSystem(config){
          //setup the type of mapper, tracker, etc your code will need.
          logger.setTAG("CHARUCOSLAMSYSTEM");
        }

        bool setup(std::string config);

        //Pre-Setup
        //Start your tracking, mapping, visualisation, etc threads
        bool startLiveSetup();

        //Loop Call for capturing image
        bool runLiveLoop();

        //Stop capturing images. Stop threads. Release memory. Log results. Whatever you want to do. 
        void stopLiveLoop();

        //Pre-Setup
        //Start your tracking, mapping, visualisation, etc threads
        bool startDatasetSetup();

        //Loop Call for iterating through the database
        bool runDatasetLoop();

        //Stop capturing images. Stop threads. Release memory. Log results. Whatever you want to do.
        void stopDatasetLoop();
    };
  }
}

#endif


