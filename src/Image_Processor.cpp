/*
 * Image Processor Class Definition
 * 
 * Author: Pranav Srinivas Kumar
 * Date: 2014.11.25
 */

#include "Image_Processor.h"
#include "Sliders.h"

// Canny Edge Detection Global Variables
int low_slider_position = 0;
int high_slider_position = 200;

// Hough Transform Global Variables
int hough_transform_threshold = 200;
int probabilistic_hough_min_line_length = 50;
int probabilistic_hough_max_line_gap = 10;

// Setup Webcam Feed Variable
void Image_Processor::setup_webcam_feed(int cam_id){
	webcam_feed = cvCaptureFromCAM(cam_id);
}

// Create the Webcam Output Window
void Image_Processor::create_webcam_window(){
	cvNamedWindow("Webcam", CV_WINDOW_AUTOSIZE);
}

// Create the Canny Edge Detection Output Window
void Image_Processor::create_canny_edge_detector_window(){
	cvNamedWindow("Canny Edge Detection", CV_WINDOW_AUTOSIZE);
	// Create slider on edge detector window to obtain real-time user input
	cvCreateTrackbar("Low Threshold", 
			 "Canny Edge Detection", 
                         &low_slider_position, 
			 canny_edge_detector.low_threshold_max, 
			 low_slider_update);
	cvCreateTrackbar("High Threshold", 
			 "Canny Edge Detection", 
			 &high_slider_position, 
			 canny_edge_detector.high_threshold_max, 
			 high_slider_update);
}

// Create the Hough Transform Output Window
void Image_Processor::create_hough_transform_window(){
	if (hough_transform.type == Hough_Transform::STANDARD){
		// Hough Transform Output Window
		cvNamedWindow("Standard Hough Transform Line Detection", 
			      CV_WINDOW_AUTOSIZE);
		// Hough Transform Threshold Slider	
		cvCreateTrackbar("Threshold", 
				 "Standard Hough Transform Line Detection", 
                                 &hough_transform_threshold, 
                                 hough_transform.hough_transform_threshold_max, 
                                 hough_slider_update);
	}

	else if (hough_transform.type == Hough_Transform::PROBABILISTIC){
		// Hough Transform Output Window
		cvNamedWindow("Probabilistic Hough Transform Line Detection", 
			      CV_WINDOW_AUTOSIZE);
		// Hough Transform Threshold Slider	
		cvCreateTrackbar("Threshold", 
				 "Probabilistic Hough Transform Line Detection", 
                                 &hough_transform_threshold, 
                                 hough_transform.hough_transform_threshold_max, 
                                 hough_slider_update);
		// Hough Transform Min Line Length Slider
		cvCreateTrackbar("Min Line Length", 
				 "Probabilistic Hough Transform Line Detection", 
				 &probabilistic_hough_min_line_length, 
				 hough_transform.probabilistic_hough_transform_line_length_max, 
				 hough_line_length_slider_update);
		cvCreateTrackbar("Max Line Gap", 
				 "Probabilistic Hough Transform Line Detection", 
				 &probabilistic_hough_max_line_gap, 
                                 hough_transform.probabilistic_hough_transform_line_gap_max, 
                                 hough_line_gap_slider_update);
	}
}


// Setup Image Processor Frames
void Image_Processor::setup_frames(){
	// Create an image from frame capture
	input_frame = cvQueryFrame(webcam_feed);

	// Create a greyscale image which is the size of our captured image
	edge_detector_output_frame = cvCreateImage(cvSize(input_frame->width, input_frame->height), IPL_DEPTH_8U, 1);

	// Create frame that holds output of Hough Transform
	hough_transform_output_frame = cvCreateImage(cvSize(input_frame->width, input_frame->height), IPL_DEPTH_32F, 3);

	// Create a frame to use as our temporary copy of the current frame but in grayscale mode
	temp_frame = cvCreateImage(cvSize(input_frame->width, input_frame->height), IPL_DEPTH_8U, 1);
}

// Main Initialize Function
void Image_Processor::init(Hough_Transform::Type this_type){
	setup_webcam_feed(0);
	create_webcam_window();
	create_canny_edge_detector_window();
	hough_transform.set_hough_transform_type(this_type);
	create_hough_transform_window();
	setup_frames();
}

// Show Output Windows
void Image_Processor::show_windows(){

	// Show Webcam Feed
	cvShowImage("Webcam", input_frame);

	// Show Edge Detector Output
	cvShowImage("Canny Edge Detection", edge_detector_output_frame);

	if (hough_transform.type == Hough_Transform::STANDARD){
		cvShowImage("Standard Hough Transform Line Detection", hough_transform_output_frame);
	}

	else if (hough_transform.type == Hough_Transform::PROBABILISTIC){
		cvShowImage("Probabilistic Hough Transform Line Detection", hough_transform_output_frame);
	}
}

// Check for User Input
void Image_Processor::handle_user_input(){
	// Briefly wait for key press
	key_press = cvWaitKey(20);

	// If user presses ESC, quit loop
	if (key_press == 27)
		quit = true;
}


// Main Real-Time Loop
void Image_Processor::run(){
	quit = false;
	while(quit == false){

		// WEBCAM FEED
		input_frame = cvQueryFrame(webcam_feed);
        
		// CANNY EDGE DETECTION
		edge_detector_output_frame = canny_edge_detector.detect_edges(input_frame);

		// HOUGH TRANSFORM
		hough_transform_output_frame = hough_transform.detect_lines(edge_detector_output_frame);

		// Show all output windows
		show_windows();

		// Handle user input
		handle_user_input();
	}
}


// Clean up image frames, webcam feed and output windows
void Image_Processor::cleanup(){
	cvReleaseImage(&input_frame);
	cvReleaseImage(&edge_detector_output_frame);
	cvReleaseImage(&hough_transform_output_frame);
	temp_frame = NULL;
	cvReleaseImage(&temp_frame);
	cvReleaseCapture(&webcam_feed);
	cvDestroyAllWindows();
}








