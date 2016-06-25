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

#include <opencv2/slam/visualisationmodule/vizvisualiser.hpp>

namespace cv {
  namespace slam {
    using namespace std;
    Mat VizVisualiser::cv_cloud_load(){
        Mat cloud(1, 1889, CV_32FC3);
        ifstream ifs("bunny.ply");

        string str;
        for(size_t i = 0; i < 12; ++i)
            getline(ifs, str);

        Point3f* data = cloud.ptr<cv::Point3f>();
        float dummy1, dummy2;
        for(size_t i = 0; i < 1889; ++i)
            ifs >> data[i].x >> data[i].y >> data[i].z >> dummy1 >> dummy2;

        cloud *= 5.0f;
        return cloud;
    }

    VizVisualiser::VizVisualiser(){

        // setup Viz
        myWindow= viz::Viz3d("Coordinate Frame");

        // Add coordinate axes
        myWindow.showWidget("Coordinate Widget", viz::WCoordinateSystem());

        // Setup Transform Coordinates
        Vec3f cam_pos(1.0f,0.0f,0.0f), cam_focal_point(0.0f,0.0f,0.0f), cam_y_dir(0.0f,-1.0f,0.0f);
        cam_pose = viz::makeCameraPose(cam_pos, cam_focal_point, cam_y_dir);
        transform = viz::makeTransformToGlobal(Vec3f(0.0f,-1.0f,0.0f), Vec3f(-1.0f,0.0f,0.0f), Vec3f(0.0f,0.0f,-1.0f), cam_pos);

        // Setup and Place the Bunny
        bunny_cloud = cv_cloud_load();
        viz::WCloud cloud_widget(bunny_cloud, viz::Color::green());

        // Pose of the widget in camera frame
        cloud_pose = Affine3f().translate(Vec3f(-1.0f,-1.0f,2.0f));

        // Pose of the widget in global frame
        cloud_pose_global = transform * cloud_pose;

        myWindow.showWidget("bunny", cloud_widget, cloud_pose_global);

    }


    void VizVisualiser::plotTrajectory(KeyFrameGraph* keyFrameGraph, bool VR){
        this->posesReceived.clear();
        vector<Node*> Nodes = keyFrameGraph->getNodes();

        for(int i=0;i<Nodes.size();i++){
            posesReceived.push_back(Nodes[i]->getFrame()->getPose().getPose());
          }

        myWindow.showWidget("Frustums", cv::viz::WTrajectoryFrustums(posesReceived, Vec2d(0.78, 0.78), 0.15));
        myWindow.showWidget("Trajectory", cv::viz::WTrajectory(posesReceived, cv::viz::WTrajectory::PATH, 0.2, cv::viz::Color::brown()));

        if(VR){
            myWindow.setViewerPose(*posesReceived.end());
          }

        myWindow.spinOnce(1,true);
    }
  }
}
