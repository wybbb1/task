#include "Detector.hpp"

int main() {

	string path = "Resources/task.png";
	Mat img = imread(path);

	Detector dter;
	dter.set_img(img);
	dter.detect();
	dter.print();

	imshow("image", img);
	waitKey(0);

	return 0;
}