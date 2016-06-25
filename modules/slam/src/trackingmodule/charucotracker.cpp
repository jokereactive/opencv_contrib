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

#include <opencv2/slam/trackingmodule/charucotracker.hpp>

namespace cv {
  namespace slam {
    using namespace std;

    CharucoTracker::CharucoTracker(int lastN, string configPath, MonoCamera* monoCamera):Tracker(lastN){
        this->monoCamera=monoCamera;
        string detectorParamsPath = configPath + "/detector_params.yml";
        string configArucoPath = configPath + "/config.txt";
        detectorParams = aruco::DetectorParameters::create();
        bool readOk1 =readDetectorParameters(detectorParamsPath, detectorParams);
        bool readOk2 =configAruco(configArucoPath);
        if(!readOk1 || !readOk2){
            //Log Error in Reading
        }
        else{
            //Log Success
        }
    }

    bool CharucoTracker::trackFrame(CharucoFrame* charucoFrame, KeyFrameGraph* keyFrameGraph){
      //Find Matching Frames with atleast one common Mappoint
      Mat image = charucoFrame->getImage();

      //Variables needed for tracking
      vector< int > markerIds;
      vector< Vec4i > diamondIds;
      vector< vector< Point2f > > markerCorners, rejectedMarkers, diamondCorners;
      vector< Vec3d > rvecs, tvecs;

      Ptr<aruco::Dictionary> dictionary =
              cv::aruco::getPredefinedDictionary(aruco::PREDEFINED_DICTIONARY_NAME(dictionaryId));

      // detect markers
      aruco::detectMarkers(image, dictionary, markerCorners, markerIds, detectorParams,
                           rejectedMarkers);

      // detect diamonds
      if(markerIds.size() > 0){
          aruco::detectCharucoDiamond(image, markerCorners, markerIds,
                                      squareLength / markerLength, diamondCorners, diamondIds,
                                      monoCamera->getCamMatrix(), monoCamera->getDistCoeffs());
        }
      else{
          return false;
        }

      // estimate diamond pose
      if(diamondIds.size() > 0) {
        aruco::estimatePoseSingleMarkers(diamondCorners, squareLength, monoCamera->getCamMatrix(),
                                         monoCamera->getDistCoeffs(), rvecs, tvecs);
        }
        else{
          return false;
        }


      // register MapPoints based on Diamonds detected
      std::vector<CharucoMapPoint*> mapPointsIdentified;
      for(unsigned int i = 0; i < diamondIds.size(); i++){
        aruco::drawAxis(image, monoCamera->getCamMatrix(), monoCamera->getDistCoeffs(), rvecs[i], tvecs[i],
                        squareLength * 0.5f);
        Affine3f pose_temp(rvecs[i],tvecs[i]);
        mapPointsIdentified.push_back(new CharucoMapPoint(diamondIds[i],AffinePose(pose_temp),charucoFrame));
        }
      charucoFrame->addMapPoints(mapPointsIdentified);

      Affine3f* pose;
      if(keyFrameGraph->getNodes().size()==0){
          //First Frame
          pose= new Affine3f(Vec3d(0,0,0),Vec3d(0,0,0));
          charucoFrame->addTracking(*pose);
          Node* node = new Node(charucoFrame);
          keyFrameGraph->insert(node);
        }
      else{
          // Find matches in KeyFrameGraph
          vector<CharucoFrame*> candidates = keyFrameGraph->getFrameMatches(charucoFrame);
          vector<Node*> candidates_nodes = keyFrameGraph->getNodeMatches(charucoFrame);
          if(candidates.size()==0){
              return false;
            }

          // Estimate Pose based on first match tracked frame
          CharucoFrame* reference = candidates[candidates.size()-1];
          Affine3f referenceInverse = reference->getPose().getPose().inv();
          *pose= referenceInverse*charucoFrame->getPose().getPose();
          charucoFrame->addTracking(*pose);

          // Add Constraint to Graph. This will be used Later.
          Node* reference_node = candidates_nodes[candidates_nodes.size()-1];
          Node* node = new Node(charucoFrame);
          reference_node->addConstraint(node,*pose);

        }
      return true;
    }

    void CharucoTracker::refinePoses(KeyFrameGraph* keyFrameGraph){
        //Do Rotational Averaging and All.
    }

    bool CharucoTracker::readDetectorParameters(string filename, Ptr<aruco::DetectorParameters> &params){
        FileStorage fs(filename, FileStorage::READ);
        if(!fs.isOpened()){
           return false;
        }
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

    bool CharucoTracker::configAruco(string filename){
        FileStorage fs(filename, FileStorage::READ);
        if(!fs.isOpened()){
            return false;
        }
        fs["squareLength"] >> squareLength;
        fs["markerLength"] >> markerLength;
        fs["dictionaryId"] >> dictionaryId;
        return true;
    }
  }
}
