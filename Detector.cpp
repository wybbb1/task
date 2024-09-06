#include "Detector.hpp"

using namespace std;
using namespace cv;

class Detector {
	Mat img;
	vector<Point> centerpoint;
	string objType[3];

public:

	void set_img(Mat& _img) {
		img = _img;
		centerpoint.resize(3);
	}
	void detect() {

		Mat imgtemp;
		cvtColor(img, imgtemp, COLOR_BGR2GRAY);
		GaussianBlur(imgtemp, imgtemp, Size(3, 3), 3, 0);
		Canny(imgtemp, imgtemp, 25, 75);
		Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
		dilate(imgtemp, imgtemp, kernel);

		vector<vector<Point>> contours;
		vector<Vec4i> hierarchy;

		findContours(imgtemp, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
		//drawContours(img, contours, -1, Scalar(255, 0, 255), 2);

		for (int i = 0; i < contours.size(); ++i) {
			vector<vector<Point>> conpoly(contours.size());
			vector<Rect> boundRect(contours.size());

			float peri = arcLength(contours[i], true);
			approxPolyDP(contours[i], conpoly[i], 0.02 * peri, true);
			boundRect[i] = boundingRect(conpoly[i]);

			int objCor = (int)conpoly[i].size();

			if (objCor == 3) {
				objType[i] = "Tri";
				centerpoint[i] = { boundRect[i].x + boundRect[i].width / 2, boundRect[i].y + 2 * boundRect[i].height / 3 };
				//rectangle(img, boundRect[i].tl(), boundRect[i].br(), Scalar(0, 255, 0), 5);
				circle(img, centerpoint[i], 10, Scalar(0, 69, 255), FILLED);
			}
			else if (objCor == 4) {
				objType[i] = "Rect";
				centerpoint[i] = { (2 * boundRect[i].x + boundRect[i].width) / 2, (2 * boundRect[i].y + boundRect[i].height) / 2 };
				//rectangle(img, boundRect[i].tl(), boundRect[i].br(), Scalar(0, 255, 0), 5);
				circle(img, centerpoint[i], 10, Scalar(0, 69, 255), FILLED);
			}
			else {
				objType[i] = "Circle";
				centerpoint[i] = { (2 * boundRect[i].x + boundRect[i].width) / 2, (2 * boundRect[i].y + boundRect[i].height) / 2 };
				//rectangle(img, boundRect[i].tl(), boundRect[i].br(), Scalar(0, 255, 0), 5);
				circle(img, centerpoint[i], 10, Scalar(0, 69, 255), FILLED);
			}
		}
	}
	void print() {
		for (int i = 0; i < 3; ++i) {
			cout << objType[i] << ": " << centerpoint[i] << endl;
		}
	}
};