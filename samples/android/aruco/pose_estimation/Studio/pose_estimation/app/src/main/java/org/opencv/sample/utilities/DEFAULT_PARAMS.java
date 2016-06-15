package org.opencv.sample.utilities;

/**
 * Created by Sarthak on 29/05/16.
 */

public class DEFAULT_PARAMS {
    //GENERAL
    public static final int DEFAULT_NMARKERS= 1024;
    public static final int DEFAULT_ADAPTIVE_THRESH_WIN_SIZE_MIN= 3;
    public static final int DEFAULT_ADAPTIVE_THRESH_WIN_SIZE_MAX= 23;
    public static final int DEFAULT_ADAPTIVE_THRESH_WIN_SIZE_STEP= 10;
    public static final int DEFAULT_ADAPTIVE_THRESH_WIN_SIZE= 21;
    public static final int DEFAULT_ADAPTIVE_THRESH_CONSTANT= 7;
    public static final double DEFAULT_MIN_MARKER_PERIMETER_RATE= 0.03;
    public static final double DEFAULT_MAX_MARKER_PERIMETER_RATE= 4.0;
    public static final double DEFAULT_POLYGONAL_APPROX_ACCURACY_RATE= 0.05;
    public static final double DEFAULT_MIN_CORNER_DISTANCE= 10.0;
    public static final int DEFAULT_MIN_DISTANCE_TO_BORDER= 3;
    public static final double DEFAULT_MIN_MARKER_DISTANCE= 10.0;
    public static final double DEFAULT_MIN_MARKER_DISTANCE_RATE= 0.05;
    public static final boolean DEFAULT_DO_CORNER_REFINEMENT= false;
    public static final int DEFAULT_CORNER_REFINEMENT_WINDOW_SIZE= 5;
    public static final int DEFAULT_CORNER_REFINEMENT_MAX_ITERATIONS= 30;
    public static final double DEFAULT_CORNER_REFINEMENT_MIN_ACCURACY= 0.1;
    public static final int DEFAULT_MARKER_BORDER_BITS= 1;
    public static final int  DEFAULT_PERSPECTIVE_REMOVE_PIXEL_PER_CELL= 8;
    public static final double DEFAULT_PERSEPCTIVE_REMOVE_IGNORE_MARGIN_PER_CELL= 0.13;
    public static final double DEFAULT_MAX_ERRONEOUS_BITS_IN_BORDER_RATE= 0.04;
    public static final double DEFAULT_MIN_OTSU_STD_DEV= 5.0;
    public static final double DEFAULT_ERROR_CORRECTION_RATE= 0.6;


    //ARUCO MARKER
    public static final int DEFAULT_ARUCO_MARKER_D= 10;

    //ARUCO BOARD
    public static final int DEFAULT_ARUCO_BOARD_D= 10;
    public static final int DEFAULT_ARUCO_BOARD_W= 5;
    public static final int DEFAULT_ARUCO_BOARD_H= 7;
    public static final int DEFAULT_ARUCO_BOARD_S= 10;
    public static final int DEFAULT_ARUCO_BOARD_L= 100;

    //CHARUCO BOARD
    public static final int DEFAULT_CHARUCO_BOARD_D= 10;
    public static final int DEFAULT_CHARUCO_BOARD_W= 5;
    public static final int DEFAULT_CHARUCO_BOARD_H= 7;
    public static final double DEFAULT_CHARUCO_BOARD_SL= 0.04;
    public static final double DEFAULT_CHARUCO_BOARD_ML= 0.02;

    //CHARUCO CHARUCO DIAMOND
    public static final int DEFAULT_CHARUCO_DIAMOND_D= 10;
    public static final double DEFAULT_CHARUCO_DIAMOND_SL= 0.04;
    public static final double DEFAULT_CHARUCO_DIAMOND_ML= 0.02;
}
