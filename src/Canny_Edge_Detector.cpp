/*
 * Canny Edge Detector Class Definition
 * 
 * Author: Pranav Srinivas Kumar
 * Date: 2014.11.25
 */

#include "Image_Processor.h"

extern int low_slider_position;
extern int high_slider_position;

// Canny Edge Detector Constructor
Canny_Edge_Detector::Canny_Edge_Detector(){
	// Max values for Edge Detector variables
	low_threshold_max = 500;
	high_threshold_max = 500;
}

// Main Edge Detection Function
IplImage * Canny_Edge_Detector::detect_edges(IplImage * input_frame){
	// Create Edge Detector Frame
	canny_edge_detecion_frame = cvCreateImage(cvSize(input_frame->width, input_frame->height), IPL_DEPTH_8U, 1);

	// Convert source frame to greyscale version
	cvCvtColor(input_frame, canny_edge_detecion_frame, CV_RGB2GRAY);

	// Perform canny edge detection & write to same frame
	cvCanny(canny_edge_detecion_frame, canny_edge_detecion_frame, low_slider_position, high_slider_position, 3);

	// Pass back our now processed frame!
	return canny_edge_detecion_frame;	
}



