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


#include <opencv2/slam/charucoslamsystem.hpp>
#include <opencv2/slam/utilities/logger.hpp>

namespace cv {
  namespace slam {
    using namespace std;

    CharucoSlamSystem::CharucoSlamSystem(string config):SlamSystem(config){

    }

    //Configure from the config file what mapper, tracker, etc do you want to set.
    bool CharucoSlamSystem::setup(string config){

    //      Factories To Be Integrated Later
    //      String mapperType, trackerType, representerType, visualiserType, inputType;
    //      FileStorage fs(configs, FileStorage::READ);
    //      if(!fs.isOpened())
    //          return false;
    //      fs["input_module"] >> inputType;
    //      fs["mapping_module"] >> mapperType;
    //      fs["tracking_module"] >> trackerType;
    //      fs["visualisation_module"] >> visualiserType;
    //      fs["representation_module"] >> representerType;

    //      MappingModule mappingModule;
    //      TrackingModule trackingModule;
    //      VisualisationModule visualationModule;
    //      RepresentationModule representationModule;
    //      InputModule inputModule;

    //      mapper = mappingModule.createMapper(mapperType);
    //      tracker = trackingModule.createTracker(trackerType);
    //      camera = inputModule.createCamera(inputType);
    //      representer = representationModule.createRepresenter(representerType);
    //      visualiser = visualationModule.createVisualiser(visualiserType);

      int N;
      string configPath_camera;
      string configPath_dataset;
      string configPath_tracker;
      FileStorage fs(config, FileStorage::READ);
      if(!fs.isOpened())
        return false;
      fs["N"] >> N;
      fs["camera_path"] >> configPath_camera;
      fs["dataset_path"] >> configPath_dataset;

      configPath_tracker=config+"/aruco";


      charucoMapper = new CharucoMapper(N);
      monoCamera = new MonoCamera(configPath_camera);
      monoDataset = new MonoDataset(configPath_dataset);
      charucoTracker = new CharucoTracker(N, configPath_tracker, monoCamera);
      keyFrameGraph = new KeyFrameGraph();
      vizVisualiser = new VizVisualiser();

      return true;
    }

    //Pre-Setup
    //Start your tracking, mapping, visualisation, etc threads
    bool CharucoSlamSystem::startLiveSetup(){
      //No Threads at the moment
      return true;
    }

    //Loop Call for capturing image
    bool CharucoSlamSystem::runLiveLoop(){
      //Get Image
      CharucoFrame* charucoFrame= new CharucoFrame(monoCamera->getFrame());

      charucoTracker->trackFrame(charucoFrame, &keyFrameGraph);

      //If Tracking is Good, add to KeyFrameGraph with appropriate constraints.
      if(charucoFrame->isTracked()){
          //Perform Mapping on Newly added Mappoints
          charucoMapper->mapFrame(charucoFrame, keyFrameGraph);

          //Refine Tracking #BLANK FUNCTIONS
          charucoTracker->refinePoses(keyFrameGraph);

          //Refine Mapping #BLANK FUNCTIONS
          charucoMapper->refineMapPoints(keyFrameGraph);

          //Update our Visualiser
          vizVisualiser->plotTrajectory(keyFrameGraph,false);
        }
      else{
          return true;
        }

      return true;
    }

    //Stop capturing images. Stop threads. Release memory. Log results. Whatever you want to do.
    void CharucoSlamSystem::stopLiveLoop(){
      //To be added when threads inserted
    }

    //Pre-Setup
    //Start your tracking, mapping, visualisation, etc threads
    bool CharucoSlamSystem::startDatasetSetup(){
       //No threads at the moment
      return true;
    }

    //Loop Call for iterating through the database
    bool CharucoSlamSystem::runDatasetLoop(){
      //Get Image
      CharucoFrame* charucoFrame=new CharucoFrame(monoDataset.getFrame());

      //Track Pose
      charucoTracker->trackFrame(charucoFrame, keyFrameGraph);

      //If Tracking is Good, add to KeyFrameGraph with appropriate constraints.
      if(charucoFrame->isTracked()){
          //Perform Mapping on Newly added Mappoints
          charucoMapper->mapFrame(charucoFrame, keyFrameGraph);

          //Refine Tracking
          charucoTracker->refinePoses(keyFrameGraph);

          //Refine Mapping
          charucoMapper->refineMapPoints(keyFrameGraph);

          //Update our Visualiser
          vizVisualiser->plotTrajectory(keyFrameGraph,false);
        }
      else{
          return true;
        }

      return true;
    }

    //Stop capturing images. Stop threads. Release memory. Log results. Whatever you want to do.
    void CharucoSlamSystem::stopDatasetLoop(){
      //To be added when threads inserted
    }

  }
}
