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

#include <opencv2/slam/datastructures/charucoframe.hpp>

namespace cv {
   namespace slam {
     using namespace std;

     void CharucoFrame::addTracking(AffinePose pose){
       this->pose=pose;
       this->Frame::setTracked(true);
     }

     void CharucoFrame::addMapPoints(std::vector<CharucoMapPoint*> mapPointsIdentified){
       this->mapPointsIdentified = mapPointsIdentified;
     }

     vector<CharucoMapPoint*> CharucoFrame::getCommonMapPoints(CharucoFrame* other){
        vector<CharucoMapPoint*> commonPoints;
        for(int i=0;i<this->mapPointsIdentified.size();i++){
            for(int j=0;j<other->mapPointsIdentified.size();j++){
                if(this->mapPointsIdentified[0]->compare(other->mapPointsIdentified[0])){
                    commonPoints.push_back(this->mapPointsIdentified[0]);
                  }
              }
          }
        return commonPoints;
     }

     vector<CharucoMapPoint*> CharucoFrame::getUncommonMapPoints(CharucoFrame* other){
       vector<CharucoMapPoint*> uncommonPoints;
       for(int i=0;i<this->mapPointsIdentified.size();i++){
           for(int j=0;j<other->mapPointsIdentified.size();j++){
               if(!this->mapPointsIdentified[0]->compare(other->mapPointsIdentified[0])){
                   uncommonPoints.push_back(this->mapPointsIdentified[0]);
                 }
             }
         }
       return uncommonPoints;
     }

     bool CharucoFrame::compare(CharucoFrame* other){
        if(this->getCommonMapPoints(other).size()>0){
            return true;
          }
        return false;
     }

   }
}
