Simultaneous Location and Mapping
=================================

This is a library that allows implementation and use of various slam algorithms in a modular fashion. All components of a
 SLAM system are available independently. There are two complete SLAM systems available for use:

**ChAruCo Marker Based SLAM**

This is a markerbased SLAM based on ChAruCo Diamonds, essentially meant as a sample SLAM to help in the structuring of this module.

**Feature Point Based SLAM**

// To be Added

**Contributing**

To add new SLAM algorithms please follow the convention being used in the existing systems. The SLAM system being integrated must be divided into the following modules:

- **Input Module**: This is the factory class that provides two options:
  - *run live slam from a camera*: **Camera** is an abstract class which has implementations such as monocamera. Other implementations such as stereo, rgbd, etc are invited. 
  - *run data slam from a folder*: This requires you to arrange the data and calibration file in the format shown under **data**.
- **Tracking Module**: This is the factory class to create a tracker - module that identifies poses between frames.
- **Mapping Module**: This is the factory class to create a mapper - module that creates MapPoints. This includes depth estimation.
- **Visualisation Module**: This is the factory class to create a visualiser - module that visualizes the SLAM. 
- **Representation Module**: This is the factory class to create a representer - a structure for storing the map and frames. Example a KeyFrameGraph. The optimisations for the structure chosen are a part of this module. Example g2o, etc.
- **Relocalisation Module**: This is the factory class to create a relocaliser - a module which has implementation for tackling the situation when tracking is lost. This includes techniques such as using BoW model to retirieve closest frame in the graph.
- **Optimisation Module**: This is the factory class to create optimiser - a routine to optimise local frames such as a local bundle adjustment.
- **SLAMSystem File**: This is the final class which includes all of the above in an algorithmic fashion. 

Make use of available modules such as Input and Visualisation whenever possible and create reusable plug-and-play structures as suggested in the examples, before submitting a PR. 
