package org.opencv.sample.containers;

import android.content.Context;
import android.content.SharedPreferences;

import org.opencv.sample.utilities.CONSTANTS;

/**
 * Created by Sarthak on 04/06/16.
 */

public class Parameters {
    SharedPreferences sharedpreferences;
    SharedPreferences.Editor editor;

    public static int NMARKERS;
    public static int ADAPTIVE_THRESH_WIN_SIZE_MIN;
    public static int ADAPTIVE_THRESH_WIN_SIZE_MAX;
    public static int ADAPTIVE_THRESH_WIN_SIZE_STEP;
    public static int ADAPTIVE_THRESH_WIN_SIZE;
    public static int ADAPTIVE_THRESH_CONSTANT;
    public static double MIN_MARKER_PERIMETER_RATE;
    public static double MAX_MARKER_PERIMETER_RATE;
    public static double POLYGONAL_APPROX_ACCURACY_RATE;
    public static double MIN_CORNER_DISTANCE;
    public static int MIN_DISTANCE_TO_BORDER;
    public static double MIN_MARKER_DISTANCE;
    public static double MIN_MARKER_DISTANCE_RATE;
    public static boolean DO_CORNER_REFINEMENT;
    public static int CORNER_REFINEMENT_WINDOW_SIZE;
    public static int CORNER_REFINEMENT_MAX_ITERATIONS;
    public static double CORNER_REFINEMENT_MIN_ACCURACY;
    public static int MARKER_BORDER_BITS;
    public static int  PERSPECTIVE_REMOVE_PIXEL_PER_CELL;
    public static double PERSEPCTIVE_REMOVE_IGNORE_MARGIN_PER_CELL;
    public static double MAX_ERRONEOUS_BITS_IN_BORDER_RATE;
    public static double MIN_OTSU_STD_DEV;
    public static double ERROR_CORRECTION_RATE;

    //ARUCO MARKER
    public static int ARUCO_MARKER_D= 10;

    //ARUCO BOARD
    public static int ARUCO_BOARD_D= 10;
    public static int ARUCO_BOARD_W= 5;
    public static int ARUCO_BOARD_H= 7;
    public static int ARUCO_BOARD_S= 10;
    public static int ARUCO_BOARD_L= 100;

    //CHARUCO BOARD
    public static int CHARUCO_BOARD_D= 10;
    public static int CHARUCO_BOARD_W= 5;
    public static int CHARUCO_BOARD_H= 7;
    public static double CHARUCO_BOARD_SL= 0.04;
    public static double CHARUCO_BOARD_ML= 0.02;

    //CHARUCO CHARUCO DIAMOND
    public static int CHARUCO_DIAMOND_D= 10;
    public static double CHARUCO_DIAMOND_SL= 0.04;
    public static double CHARUCO_DIAMOND_ML= 0.02;

    Parameters(Context c){
        sharedpreferences = c.getSharedPreferences(CONSTANTS.Params, Context.MODE_PRIVATE);
        editor = sharedpreferences.edit();
        loadParameters();
    }

    public void loadParameters(){
        //loads parameters if they exist, or adds default parameters
    }

    public void resetParameters(){

    }
}
