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

#include <opencv2/slam/inputmodule/monocamera.hpp>


namespace cv {
    namespace slam {
        using namespace std;
        MonoCamera::MonoCamera(string configPath){
          string initialize_path=configPath+"/config.txt";
          this->initialize(initialize_path);
        }

	bool MonoCamera::initialize(string configPath){
		string camerasourcePath;
		string calibPath;
		FileStorage fs(configPath, FileStorage::READ);
	    if(!fs.isOpened())
		return false;
	    fs["camerasource_path"] >> camerasourcePath;
	    fs["calib_path"] >> calibPath;
		if(readCameraParameters(calibPath) && readCameraSource(camerasourcePath)){
			start();
			return true;
		}
		return false;
	}

	bool MonoCamera::readCameraParameters(string calibPath){
		FileStorage fs(calibPath, FileStorage::READ);
	    if(!fs.isOpened())
		return false;
	    fs["camera_matrix"] >> camMatrix;
	    fs["distortion_coefficients"] >> distCoeffs;
	    return true;
	}

	bool MonoCamera::readCameraSource(string camerasourcePath){
		FileStorage fs(camerasourcePath, FileStorage::READ);
	    if(!fs.isOpened())
		return false;
	    fs["video"] >> video;
	    fs["cam_id"] >> camId;
	    return true;
	}

	void MonoCamera::start(){
	    if(!video.empty()) {
		inputVideo.open(video);
		waitTime = 0;
	    } else {
		inputVideo.open(camId);
		waitTime = 10;
	    }
	}

	Mat MonoCamera::getFrame(){
	    while(inputVideo.grab()) {
	    Mat image;
	    inputVideo.retrieve(image);
	    return image;
	  }
	}
}
}
