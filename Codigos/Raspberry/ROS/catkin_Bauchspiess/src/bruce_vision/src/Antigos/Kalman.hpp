
#include "opencv2/opencv.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/core/core.hpp"
#include <cv.h>
#include <highgui.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include <sys/time.h>

using namespace std;
using namespace cv;

class Kalman{
	
private:	
	Mat S;
	Mat K;
	Mat I;

	Mat b;
	Mat q;

public:
	Mat H;
	Mat F;
	Mat P;
	Mat Q;
	Mat B;
	Mat R;

	Mat y;
	Mat x;
	void init(Mat, Mat, Mat, Mat, Mat, Mat, Mat);
	void init(Mat, Mat, Mat, Mat, Mat, Mat);
	void timeF(float* );
	void predict(bool);
	void predict(Mat);
	void predict();
	void update(Mat);
	void timeB(float);
	void timeQ(float);


};