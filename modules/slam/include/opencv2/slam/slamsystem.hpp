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

#ifndef __OPENCV_SLAMSYSTEM_HPP__
#define __OPENCV_SLAMSYSTEM_HPP__

#include <opencv2/core.hpp>
#include <vector>

//SLAM Modules
//Input Module
#include "opencv2/slam/inputmodule/inputmodule.hpp"
//Mapping Module
#include "opencv2/slam/mappingmodule/mappingmodule.hpp"
//Optimisation Module
#include "opencv2/slam/optimisationmodule/optimisationmodule.hpp"
//Relocalisation Module
#include "opencv2/slam/relocalisationmodule/relocalisationmodule.hpp"
//Tracking Module
#include "opencv2/slam/trackingmodule/trackingmodule.hpp"
//Visualisation Module
#include "opencv2/slam/visualisationmodule/visualisationmodule.hpp"

//Logger
#include "opencv2/slam/utilities/logger.hpp"


namespace cv {
namespace slam {
    /**
     * @brief SlamSystem
     * This is an abstract class to create various implementations of SLAM
     */
    class SlamSystem {
      protected:
///          Factories Integrated Later
//          Logger* logger;
//          Mapper* mapper;
//          Tracker* tracker;
//          Optimiser* optimiser;
//          Relocaliser* relocaliser;
//          Representer* representer;
//          Visualiser* visualiser;

        bool ready;
        bool running;

        Logger logger;

      public:
        SlamSystem(std::string config){
          //setup the type of mapper, tracker, etc your code will need.
          logger.setTAG("SLAMSYSTEM");
          setReady(setup(config));
        }

        void startLive();

        void startDataset();

        void stopLive();

        void stopDataset();

        //Configure from the config file what mapper, tracker, etc do you want to set.
        virtual bool setup(std::string config)=0;

        //Run your implementation of live slam.
        //Ideally you should use the visualiser to show the results but to facilitate porting to various platforms
        //you may use this function to capture images from your camera or implement a buffer.
        //The main thread loop must remain in this function.

        //Pre-Setup
        //Start your tracking, mapping, visualisation, etc threads
        virtual bool startLiveSetup()=0;

        //Loop Call for capturing image
        virtual bool runLiveLoop()=0;

        //Stop capturing images. Stop threads. Release memory. Log results. Whatever you want to do.
        virtual void stopLiveLoop()=0;

        //Run your implementation of live slam.
        //Ideally you should use the visualiser to show the results but to facilitate porting to various platforms
        //you may use this function to iterate through the database and access images
        //The main thread loop must remain in this function.

        //Pre-Setup
        //Start your tracking, mapping, visualisation, etc threads
        virtual bool startDatasetSetup()=0;

        //Loop Call for iterating through the database
        virtual bool runDatasetLoop()=0;

        //Stop capturing images. Stop threads. Release memory. Log results. Whatever you want to do.
        virtual void stopDatasetLoop()=0;

        void setReady(bool ready){
          this->ready=ready;
        }

        void setRunning(bool running){
          this->running=running;
        }

        bool isReady(){
          return ready;
        }

        bool isRunning(){
          return running;
        }
    };
  }
}


#endif


