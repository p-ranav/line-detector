/*
 * Image Processor Class Declaration
 * 
 * Author: Pranav Srinivas Kumar
 * Date: 2014.11.25
 */

#include "opencv/cv.h"
#include "opencv/highgui.h"
#include <math.h>
#include "Canny_Edge_Detector.h"
#include "Hough_Transform.h"

class Image_Processor{

public:
	// Create Webcam Window
	void create_webcam_window();

	// Create Canny Edge Detector Window
	void create_canny_edge_detector_window();

	// Create Hough Transform Window
	void create_hough_transform_window();

	// Setup Webcam feed variable
        void setup_webcam_feed(int cam_id=0);	

	// Setup frame variables 
        void setup_frames();
	
	// Main Initialize Function
	void init(Hough_Transform::Type transform_type);

	// Show output windows
	void show_windows();

	// Handle user input
	void handle_user_input();

	// Main Real-Time Loop
	void run();

	// Clean up
	void cleanup();

private:
	// Webcam feed
	CvCapture * webcam_feed;

	// Canny Edge Detection Object
	Canny_Edge_Detector canny_edge_detector;	

	// Hough Transform Object
	Hough_Transform hough_transform;

	// Input Frame - Fetched from Webcam
	IplImage * input_frame;

	// Edge Detector Output Frame
        IplImage * edge_detector_output_frame;

        // Hough Transform Output Frame
	IplImage * hough_transform_output_frame;

	// Temp Frame used during processing	
        IplImage * temp_frame;	

	// User Input from Keyboard
	char key_press;
	bool quit;
};
