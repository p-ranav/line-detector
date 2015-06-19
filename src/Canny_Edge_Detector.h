/*
 * Canny Edge Detector Class Declaration
 * 
 * Author: Pranav Srinivas Kumar
 * Date: 2014.11.25
 */

class Canny_Edge_Detector {

public:
	// Constructor
	Canny_Edge_Detector();

	// Edge Detection function
        IplImage * detect_edges(IplImage * input_frame);

	// Max Values for Edge Detection Variables
	int low_threshold_max;
	int high_threshold_max;
	
private:
	// Output Frame after Canny Edge Detection
	IplImage * canny_edge_detecion_frame;
};
