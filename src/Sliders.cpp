/*
 * Callback definitions to handle output window sliders
 * 
 * Author: Pranav Srinivas Kumar
 * Date: 2014.11.25
 */

#include "Sliders.h"
#include "Image_Processor.h"

extern int low_slider_position;
extern int high_slider_position;
extern int hough_transform_threshold;
extern int probabilistic_hough_min_line_length;
extern int probabilistic_hough_max_line_gap;

// Callback to update low_slider_position when slider is moved
void low_slider_update(int slider_value){
    low_slider_position = slider_value;
}

// Callback to update high_slider_position when slider is moved
void high_slider_update(int slider_value){
    high_slider_position = slider_value;
}

// Callback to update hough_transform_threshold when slider is moved
void hough_slider_update(int slider_value){
    if (slider_value > 1)
    	hough_transform_threshold = slider_value;
    else
	hough_transform_threshold = 1;
}

// Callback to update probabilistic hough transform - min line length
void hough_line_length_slider_update(int slider_value){
    probabilistic_hough_min_line_length = slider_value;
}

// Callback to update probabilistic hough transform - max line gap
void hough_line_gap_slider_update(int slider_value){
    probabilistic_hough_max_line_gap = slider_value;
}

