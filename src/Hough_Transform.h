/*
 * Hough Transform Class Declaration
 * 
 * Author: Pranav Srinivas Kumar
 * Date: 2014.11.25
 */

class Hough_Transform{

public:
	// Constructor
	Hough_Transform();

        // Hough Transform Types
	enum Type {
		STANDARD,
		PROBABILISTIC
	};

	// Hough Transform Type 
	Hough_Transform::Type type;

	// Max Values for Hough Transform Variables
	int hough_transform_threshold_max;
	int probabilistic_hough_transform_line_length_max;
	int probabilistic_hough_transform_line_gap_max;

	// Set Hough Transform Type
	void set_hough_transform_type(Hough_Transform::Type this_type);

	// Line Detection Function
	IplImage * detect_lines(IplImage * input_frame);

private:

	// Output Frame after Hough Transform
	IplImage * hough_transform_frame;
};
