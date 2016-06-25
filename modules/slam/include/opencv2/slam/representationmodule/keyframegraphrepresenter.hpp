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

#ifndef _OPENCV_KEYFRAMEGRAPH_HPP_
#define _OPENCV_KEYFRAMEGRAPH_HPP_

//General
#include <opencv2/core.hpp>
#include <opencv2/calib3d.hpp>
#include <opencv2/highgui.hpp>
#include <vector>
#include <iostream>
#include <fstream>
#include <cstddef>

#include <opencv2/slam/datastructures/affinepose.hpp>
#include <opencv2/slam/representationmodule/representer.hpp>
#include <opencv2/slam/datastructures/charucoframe.hpp>
#include <opencv2/slam/utilities/logger.hpp>

namespace cv {
 namespace slam {
    class Node;
    class AffinePose;
    class CharucoFrame;

    /**
    * @brief Constraint
    * Analogous to Edge on a Graph
    */
    class Constraint
    {
    public:
     Constraint(Node *source, Node *destination, AffinePose pose)
     {
         this->source = source;
         this->destination = destination;
         this->pose=pose;
     }

     Node* getSource() {return source;}
     Node* getDestination() {return destination;}
     AffinePose getPose() {return pose;}
    private:
     Node* source;
     Node* destination;
     AffinePose pose;
    };

    /**
    * @brief Node
    * Analogous to Vertex on a Graph
    */
    class Node
    {
    public:
        Node(CharucoFrame* charucoFrame)
        {
            this->charucoFrame=charucoFrame;
            this->id = charucoFrame->getId();
        }

        void addConstraint(Node *v, AffinePose pose)
        {
            Constraint newConstraint(this, v, pose);
            constraints.push_back(newConstraint);
        }

        CharucoFrame* getFrame() {return charucoFrame;}
        std::vector<Constraint> getConstraints() {return constraints;}

        bool equals(Node* other){
          if(this->id==other->getId()){
              return true;
            }
          return false;
        }

        unsigned long int getId(){
          return id;
        }

    private:
        unsigned long int id;
        CharucoFrame* charucoFrame;
        std::vector<Constraint> constraints;
    };

    /**
    * @brief KeyFrameGraph
    * This is an abstract class to create various implementations of representer this SLAM system may support
    */
    class KeyFrameGraph: public Representer {
    public:
        void insert(Node *v)
        {
            nodes.push_back(v);
        }

        std::vector<CharucoFrame*> getFrameMatches(CharucoFrame* charucoFrame);
        std::vector<Node*> getNodeMatches(CharucoFrame* charucoFrame);
        Node* getNodeById(unsigned long int id);
        CharucoFrame* getFrameById(unsigned long int id);
        std::vector<Node*> getNodes(){
          return nodes;
        }

    private:
        std::vector<Node*> nodes;

   };
 }
}

#endif
