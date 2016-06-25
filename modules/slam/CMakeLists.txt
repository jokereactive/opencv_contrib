set(the_description "Simultaneous Location and Mapping")

cmake_minimum_required(VERSION 2.8)

project( OpenCV_SLAM )

find_package( OpenCV REQUIRED )

include_directories(include)

add_library(opencv_slam_modules
    include/opencv2/slam/datastructures/affinepose.hpp
    include/opencv2/slam/datastructures/charucoframe.hpp
    include/opencv2/slam/datastructures/charucomappoint.hpp
    include/opencv2/slam/datastructures/frame.hpp
    include/opencv2/slam/datastructures/mappoint.hpp
    include/opencv2/slam/datastructures/pose.hpp
    include/opencv2/slam/inputmodule/camera.hpp
    include/opencv2/slam/inputmodule/dataset.hpp
    include/opencv2/slam/inputmodule/inputmodule.hpp
    include/opencv2/slam/inputmodule/monocamera.hpp
    include/opencv2/slam/inputmodule/monocameradataset.hpp
    include/opencv2/slam/mappingmodule/charucomapper.hpp
    include/opencv2/slam/mappingmodule/mapper.hpp
    include/opencv2/slam/mappingmodule/mappingmodule.hpp
    include/opencv2/slam/optimisationmodule/optimisationmodule.hpp
    include/opencv2/slam/relocalisationmodule/relocalisationmodule.hpp
    include/opencv2/slam/representationmodule/keyframegraphrepresenter.hpp
    include/opencv2/slam/representationmodule/representationmodule.hpp
    include/opencv2/slam/representationmodule/representer.hpp
    include/opencv2/slam/trackingmodule/charucotracker.hpp
    include/opencv2/slam/trackingmodule/tracker.hpp
    include/opencv2/slam/trackingmodule/trackingmodule.hpp
    include/opencv2/slam/utilities/logger.hpp
    include/opencv2/slam/visualisationmodule/visualisationmodule.hpp
    include/opencv2/slam/visualisationmodule/visualiser.hpp
    include/opencv2/slam/visualisationmodule/vizvisualiser.hpp
    include/opencv2/slam.hpp
    src/datastructures/charucoframe.cpp
    src/datastructures/charucomappoint.cpp
    src/datastructures/frame.cpp
    src/datastructures/mappoint.cpp
    src/datastructures/pose.cpp
    src/inputmodule/inputmodule.cpp
    src/inputmodule/monocamera.cpp
    src/inputmodule/monocameradataset.cpp
    src/mappingmodule/mappingmodule.cpp
    src/optimisationmodule/optimisationmodule.cpp
    src/relocalisationmodule/relocalisationmodule.cpp
    src/representationmodule/representationmodule.cpp
    src/trackingmodule/trackingmodule.cpp
    src/utilities/logger.cpp
    src/visualisationmodule/visualisationmodule.cpp
    src/mappingmodule/charucomapper.cpp
    src/mappingmodule/mapper.cpp
    src/visualisationmodule/visualiser.cpp
    src/visualisationmodule/vizvisualiser.cpp
    src/representationmodule/keyframegraphrepresenter.cpp
    src/representationmodule/representer.cpp
    src/trackingmodule/tracker.cpp
    src/slamsystem.cpp
    include/opencv2/slam/slamsystem.hpp
    src/trackingmodule/charucotracker.cpp
    )

add_library(charuco_slam
    src/charucoslamsystem.cpp
    include/opencv2/slam/charucoslamsystem.hpp
    ${opencv_slam_modules})

add_executable(demo_charuco_slam
    samples/demo_slam.cpp
    ${charuco_slam}
)

target_link_libraries(demo_charuco_slam charuco_slam opencv_slam_modules)
