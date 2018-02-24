#include <iostream>
#include</home/mudit/intern/cameracaliberate.hpp>





#define CAMERA_CALIBERATION_MODULE_ 1
#define CALIBERATE_COLOUR_ 1



#if (CAMERA_CALIBERATION_MODULE_)
void CaliberationTest()
{
	CameraCaliberation nexusS;
//nexusS.GetImages(0);
    //nexusS.GetImages(0);
//nexusS.Caliberate();

  //  nexusS.Caliberate();
   //nexusS.ShowUndistorted("/home/mudit/intern/build/results/cam1/intrinsic1.txt","/home/mudit/intern/build/results/cam1/distortion_coeffs1.txt");
//    nexusS.GetTransformation(2, "/home/mudit/intern/build/results/cam1/intrinsic1.txt", "/home/mudit/intern/build/results/cam1/distortion_coeffs1.txt",
//                             "/home/mudit/intern/build/results/cam1/rotation1.txt", "/home/mudit/intern/build/results/cam1/translation1.txt",
//                              "/home/mudit/intern/build/results/cam1/imagept1.txt", "/home/mudit/intern/build/results/cam1/objectpt1.txt");
     //nexusS.GetTransformation(2, "/home/mudit/pylon-calibration/build/results/cam2/intrinsic2.txt", "/home/mudit/pylon-calibration/build/results/cam2/distortion_coeffs2.txt",
     //"/home/mudit/pylon-calibration/build/results/cam2/rotation2.txt", "/home/mudit/pylon-calibration/build/results/cam2/translation2.txt",
     //"/home/mudit/pylon-calibration/build/results/cam2/imagept2.txt", "/home/mudit/pylon-calibration/build/results/cam2/objectpt2.txt");
  nexusS.StressTest(0, 2, "/home/mudit/intern/build/results/cam1/intrinsic1.txt", "/home/mudit/intern/build/results/cam2/intrinsic2.txt",
                      "/home/mudit/intern/build/results/cam1/distortion_coeffs1.txt",  "/home/mudit/intern/build/results/cam2/distortion_coeffs2.txt",
                      "/home/mudit/intern/build/results/cam1/rotation1.txt", "/home/mudit/intern/build/results/cam2/rotation2.txt",
         "/home/mudit/intern/build/results/cam1/translation1.txt", "/home/mudit/intern/build/results/cam2/translation2.txt");



	std::cout<<" [INF] End"<<std::endl;
}
#endif

#if (CALIBERATE_COLOUR_)

// C++ libraries
#include <iostream>
#include <string>
#include <vector>
// OpenCV libraries
#include <opencv2/core/core.hpp>
#include <opencv/highgui.h>
#include <opencv/cv.h>
#include<fstream>
using namespace cv;
using namespace std;


int filter0[6] = {172,34,255,54,255,143}; // Arrey for HSV filter, [Hmax, Hmin, Smax, Smin, Vmax, Vmin]
int filter1[6] = {172,34,255,54,255,143}; // Arrey for HSV filter, [Hmax, Hmin, Smax, Smin, Vmax, Vmin]

Mat imghsv[2]; // Input HSV image : Global cause of trackbar
Mat imgbin[2]; // Input Binary image : Filtered object is ball : Global cause of trackbar
cv::Mat img[2], img1[2];
// Trackbar function : Routine called when trackbar is modified
void on_trackbar( int, void* )
{
	inRange(imghsv[0], Scalar(filter0[1], filter0[3], filter0[5]), Scalar(filter0[0], filter0[2], filter0[4]), imgbin[0]); 
	inRange(imghsv[1], Scalar(filter1[1], filter1[3], filter1[5]), Scalar(filter1[0], filter1[2], filter1[4]), imgbin[1]); 

	imshow("Hs0", imghsv[0]); // Show input HSV image
	imshow("Bn0",imgbin[0]); // Show filtered image
	imshow("Tr0", img[0]); // Show centroid image

	imshow("Hs1", imghsv[1]); // Show input HSV image
	imshow("Bn1",imgbin[1]); // Show filtered image
	imshow("Tr1", img[1]); // Show centroid image
}







void CaliberateColor()
{
cv::VideoCapture cam[2];

	cam[0].open(0);
	cam[1].open(1);
	if(!cam[0].isOpened() || !cam[1].isOpened())
	{
		std::cout<<" [ERR] Camera not opened "<<std::endl;
		std::exit(0);
	}

	cam[0].set(CV_CAP_PROP_FRAME_WIDTH, 640);
	cam[0].set(CV_CAP_PROP_FRAME_HEIGHT, 480);
	cam[0].set(CV_CAP_PROP_FPS, 30);
	cam[1].set(CV_CAP_PROP_FRAME_WIDTH, 640);
	cam[1].set(CV_CAP_PROP_FRAME_HEIGHT, 480);
	cam[1].set(CV_CAP_PROP_FPS, 30);

	//namedWindow("T 0"); // Window to display input RGB image
	namedWindow("P 0"); // Windoe to display Parameter trackbar
	//namedWindow("H 0"); // Windoe to display Parameter trackbar
	//namedWindow("F 0"); // Window to display filtered Image

	//namedWindow("T 1"); // Window to display input RGB image
	namedWindow("P 1"); // Windoe to display Parameter trackbar
	//namedWindow("H 1"); // Windoe to display Parameter trackbar
	//namedWindow("F 1"); // Window to display filtered Image

	char key = 'r'; // Key press to stop execution

	createTrackbar( "Hmax", "P 0", &filter0[0], 255, NULL);
	createTrackbar( "Hmin", "P 0", &filter0[1], 255, NULL);
	createTrackbar( "Smax", "P 0", &filter0[2], 255, NULL);
	createTrackbar( "Smin", "P 0", &filter0[3], 255, NULL);
	createTrackbar( "Vmax", "P 0", &filter0[4], 255, NULL);
	createTrackbar( "Vmin", "P 0", &filter0[5], 255, NULL);

	createTrackbar( "Hmax", "P 1", &filter1[0], 255, NULL);
	createTrackbar( "Hmin", "P 1", &filter1[1], 255, NULL);
	createTrackbar( "Smax", "P 1", &filter1[2], 255, NULL);
	createTrackbar( "Smin", "P 1", &filter1[3], 255, NULL);
	createTrackbar( "Vmax", "P 1", &filter1[4], 255, NULL);
	createTrackbar( "Vmin", "P 1", &filter1[5], 255, NULL);

	// Waste 1000 frames : Let camera settle and adjust to brightness
	for(int i=0;i<100;i++)
	{
		cam[0] >> img[0];
		cam[1] >> img[1];	
	}

    	cv::Mat kernel = cv::getStructuringElement(cv::MORPH_CROSS,cv::Size(3,3),cv::Point(-1,-1));

	key = 'r';
	while(true)
	{
		cam[0] >> img[0];
		cam[1] >> img[1];	

		//cv::blur( img1[0], img[0], cv::Size( 5, 5 ) );
		//cv::blur( img1[1], img[1], cv::Size( 5, 5 ) );

		cvtColor(img[0], imghsv[0], CV_BGR2HSV); // Convert colour to HSV
		cvtColor(img[1], imghsv[1], CV_BGR2HSV); // Convert colour to HSV

		inRange(imghsv[0], Scalar(filter0[1], filter0[3], filter0[5]), Scalar(filter0[0], filter0[2], filter0[4]), imgbin[0]); 
		inRange(imghsv[1], Scalar(filter1[1], filter1[3], filter1[5]), Scalar(filter1[0], filter1[2], filter1[4]), imgbin[1]); 

		cv::erode(imgbin[0],imgbin[0],kernel,cv::Point(-1,-1),2);
		cv::dilate(imgbin[0],imgbin[0],kernel,cv::Point(-1,-1),2);
		cv::erode(imgbin[0],imgbin[0],kernel,cv::Point(-1,-1),2);

		cv::erode(imgbin[1],imgbin[1],kernel,cv::Point(-1,-1),2);
    		cv::dilate(imgbin[1],imgbin[1],kernel,cv::Point(-1,-1),2);
		cv::erode(imgbin[1],imgbin[1],kernel,cv::Point(-1,-1),2);

		imshow("Hs0", imghsv[0]); // Show input HSV image
		imshow("Bn0",imgbin[0]); // Show filtered image
		imshow("Tr0", img[0]); // Show centroid image

		imshow("Hs1", imghsv[1]); // Show input HSV image
		imshow("Bn1",imgbin[1]); // Show filtered image
		imshow("Tr1", img[1]); // Show centroid image


		key = waitKey(5); // Wait for 1ms for intrupt from user to exit
		if(key == 'q') // If user presses 'q'
			break; // Exit while loop
	}
    destroyAllWindows(); // Distroid all display windows
   



}
#endif







int main()
{

     CaliberationTest();
//    CaliberateColor();


}
