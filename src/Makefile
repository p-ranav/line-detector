# Include OpenCV library and build main.cpp
all: main.cpp
	g++ -o rt_line_detection main.cpp Sliders.cpp Image_Processor.cpp Canny_Edge_Detector.cpp Hough_Transform.cpp `pkg-config --cflags --libs opencv`

clean: 
	$(RM) rt_line_detection

