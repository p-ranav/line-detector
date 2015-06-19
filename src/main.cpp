/*
 * OpenCV-based Real-time Hough Transform Line Detection:
 * -----------------------------------------------------
 * (1) Periodically fetches webcam feed
 * (2) Applies Canny Edge Detection to a queried image frame 
 * (3) Applies Hough Transform Line Detection to the detected edges
 *
 * Author: Pranav Srinivas Kumar
 * Date: 2014.11.25
 */

#include <iostream>
#include "Image_Processor.h"

using namespace std;

int main(int argc, char** argv)
{
	// Create an Image Processor Object
	Image_Processor image_processor;

	// Initialize Image Processor with Hough Transform type
	// Type can be either STANDARD or PROBABILISTIC
	image_processor.init(Hough_Transform::STANDARD);

	// Run Image Processor Real-Time Loop
	image_processor.run();

	// Clean up on exit
	image_processor.cleanup();
}
