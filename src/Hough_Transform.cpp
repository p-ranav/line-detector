/*
 * Hough Transform Class Definition
 * 
 * Author: Pranav Srinivas Kumar
 * Date: 2014.11.25
 */

#include "Image_Processor.h"

extern int hough_transform_threshold;
extern int probabilistic_hough_min_line_length;
extern int probabilistic_hough_max_line_gap;

// Hough Transform Constructor
Hough_Transform::Hough_Transform(){
	// Max values for hough transform variables
	hough_transform_threshold_max = 500;
	probabilistic_hough_transform_line_length_max = 500;
	probabilistic_hough_transform_line_gap_max = 500;

	// Set type to STANDARD by default
	type = STANDARD;
}

void Hough_Transform::set_hough_transform_type(Hough_Transform::Type this_type){
	type = this_type;
}

IplImage * Hough_Transform::detect_lines(IplImage * input_frame){
	// Create Hough Transform Frame
	hough_transform_frame = cvCreateImage(cvSize(input_frame->width, input_frame->height), IPL_DEPTH_32F, 3);

	// STANDARD HOUGH TRANSFORM
	if (type == Hough_Transform::STANDARD){
	    	hough_transform_frame = cvCreateImage(cvSize(input_frame->width, input_frame->height), IPL_DEPTH_32F, 3);
		CvMemStorage* storage = cvCreateMemStorage(0);
		CvSeq* lines = 0; 
		int i, c, d; 

		// Invoke Standard Hough Transform
		lines = cvHoughLines2 (input_frame, storage, CV_HOUGH_STANDARD, 1, CV_PI/180, hough_transform_threshold, 0, 0);

		for(i = 0; i < MIN(lines->total,100); i++) {
			d=0;
			c=0;
			float* line = (float*)cvGetSeqElem(lines,i);
			float rho = line[0];
			float theta = line[1];
			CvPoint pt1, pt2;
			double a = cos(theta), b = sin(theta);
			double x0 = a*rho, y0 = b*rho;
			pt1.x = cvRound(x0 + 1000*(-b));
			pt1.y = cvRound(y0 + 1000*(a));
			pt2.x = cvRound(x0 - 1000*(-b));
			pt2.y = cvRound(y0 - 1000*(a));
			cvLine(hough_transform_frame, pt1, pt2, CV_RGB(255, 0, 0), 1, 8 );
		} 
		cvShowImage("Standard Hough Transform Line Detection", hough_transform_frame);
	}

	// PROBABILISTIC HOUGH TRANSFORM
	else if (type == Hough_Transform::PROBABILISTIC) {
		hough_transform_frame = cvCreateImage(cvSize(input_frame->width, input_frame->height), IPL_DEPTH_32F, 3);
		CvMemStorage* storage = cvCreateMemStorage(0);
		CvSeq* lines = 0; 
		int i;

		// Invoke Probabilistic Hough Transform
		lines = cvHoughLines2(input_frame, storage, CV_HOUGH_PROBABILISTIC, 1, CV_PI/180, hough_transform_threshold, probabilistic_hough_min_line_length, probabilistic_hough_max_line_gap);

		for (i=0; i<lines->total; i++){
			CvPoint * line = (CvPoint*)cvGetSeqElem(lines, i);
			cvLine(hough_transform_frame, line[0], line[1], CV_RGB(0, 255, 0), 1, 8);
		}

		cvShowImage("Probabilistic Hough Transform Line Detection", hough_transform_frame);
	}

	// Returned Processed Frame
	return hough_transform_frame;
}
