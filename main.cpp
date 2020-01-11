#include<opencv2/opencv.hpp>
using namespace cv;
using namespace std;

int r1 = 0, r2 = 0, r3 = 0;//去浮水印變數
int maxPercent = 100, gamma = 10, angle = 0;//縮放、明暗、選轉變數

//人臉偵測
void faceIdentify(Mat &img) {
	CascadeClassifier face = CascadeClassifier("haarcascade_frontalface_default.xml");

	vector<Rect> objects;
	face.detectMultiScale(img, objects, 1.1, 7);

	for (Rect r : objects) {
		rectangle(img, Point(r.x, r.y), Point(r.x + r.width, r.y + r.height), (255, 255, 255), 2);
	}
}
//素描風
void sketch(int k, Mat &img) {
	Mat gray, bina;
	cvtColor(img, gray, COLOR_RGB2GRAY);
	GaussianBlur(gray, gray, Size(5, 5), 0);
	adaptiveThreshold(gray, bina, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, 5, k);
	imshow("Origin", img);
	imshow("After", bina);

}
void onChangeSketch(int k, void *src) {
	Mat *img = (Mat *)src;
	sketch(k, *img);
}
void adjustable(Mat &img) {
	int max = 10;

	onChangeSketch(0, &img);
	createTrackbar("size", "After", 0, max, onChangeSketch, &img);
}
//描邊
void No3() {
	Mat dst;
	Mat src = imread("dog.jpeg", IMREAD_REDUCED_GRAYSCALE_2);
	GaussianBlur(src, src, Size(3, 3), 0, 0, BORDER_DEFAULT);
	int n = 10;
	Canny(src, dst, n, n * 3, 5);
	imshow("src", src);
	imshow("side", dst);

	waitKey(0);
}
//去浮水印
void paint(Mat &img, int r1, int r2, int r3) {
	Mat mask, after;

	inRange(img, Scalar(r1, r2, r3), Scalar(225, 225, 225), mask);
	inpaint(img, mask, after, 3, INPAINT_TELEA);


	imshow("Before", img);
	imshow("Mask", mask);
	imshow("After", after);
}
void onChangePaint(int, void*src) {
	Mat *img = (Mat *)src;

	paint(*img, r1, r2, r3);
}
//特定範圍去背
void No5() {
	Mat src = imread("fruit.jpeg",IMREAD_REDUCED_COLOR_2);
	Mat mask;
	bool fromCenter = false;
	Rect2d r = selectROI(src, fromCenter);
	Mat bgModel, fgModel;
	grabCut(src, mask, r, bgModel, fgModel, 1, GC_INIT_WITH_RECT);
	compare(mask, GC_PR_FGD, mask, CMP_EQ);
	imshow("mask", mask);
	Mat foreground(src.size(), CV_8UC3, Scalar(255, 255, 255));
	src.copyTo(foreground, mask);
	imshow("提取後", foreground);

	waitKey(0);
}
//毛玻璃特效
void glass(Mat &src, int r) {
	Mat res = src.clone();
	RNG rng;

	for (int i = 0; i < res.rows - r; i++) {
		for (int j = 0; j < res.cols - r; j++) {

			int randomNum = rng.uniform(0, r);
			res.at<Vec3b>(i, j)[0] = res.at<Vec3b>(i + randomNum, j + randomNum)[0];
			res.at<Vec3b>(i, j)[1] = res.at<Vec3b>(i + randomNum, j + randomNum)[1];
			res.at<Vec3b>(i, j)[2] = res.at<Vec3b>(i + randomNum, j + randomNum)[2];
		}
	}

	imshow("Result", res);
}
void onChangeGlass(int r, void *src) {
	if (r == 0)r = 1;

	Mat *img = (Mat *)src;
	glass(*img, r);
}
//縮放、明暗、選轉
void zoom_contrast(double percent, double gamma, int angle,Mat &image) {
	//zoom
	Mat dst;
	double height = image.rows * percent;
	double width = image.cols * percent;
	resize(image, dst, Size(width, height));

	//gamma
	dst.convertTo(dst, CV_32F, 1.0 / 255.0, 0);
	pow(dst, gamma, dst);

	//Rotation
	Mat mask = getRotationMatrix2D(Point2f(dst.cols / 2, dst.rows / 2), angle, 1);
	warpAffine(dst, dst, mask, dst.size());

	namedWindow("dst", 0);
	imshow("dst", dst);
}
void onChangeZoom(int, void *src) {
	Mat *image = (Mat *)src;
	//zoom
	double percent = 0.0;
	if (maxPercent == 0)percent = 0.01;
	else percent = maxPercent / 100.0;
	//gamma
	double ga = 0.0;
	if (gamma == 0)ga = 0.1;
	else ga = gamma / 10.0;

	zoom_contrast(percent, ga, angle,*image);
}
//消除紅眼
void redEyeRemove(Mat &image) {
	if (!image.empty()) {
		CascadeClassifier eyeCascade = CascadeClassifier("haarcascade_eye.xml");
		Mat dst = image.clone();
		Mat gray;
		vector<Rect> eyes;
		cvtColor(image, gray, COLOR_BGR2GRAY);//轉灰階
		equalizeHist(gray, gray);//直方圖等化
		eyeCascade.detectMultiScale(gray, eyes, 1.1, 3, 0, Size(70, 70));//偵測人眼
		for (int i = 0; i < eyes.size(); i++) {
			//分離色彩
			Mat eye = image(eyes[i]);
			vector<Mat>BGR(3);
			split(eye, BGR);

			//提取眼球範圍
			Mat mask = (BGR[2] > 50) & (BGR[2] > (BGR[0] + BGR[1]));

			//修復
			Mat mean = (BGR[0] + BGR[1]) / 2;
			mean.copyTo(BGR[0], mask);
			mean.copyTo(BGR[1], mask);
			mean.copyTo(BGR[2], mask);

			imshow("mask", mask);

			//回填
			Mat eyeOut;
			merge(BGR, eyeOut);
			eyeOut.copyTo(dst(eyes[i]));
			rectangle(image, eyes[i], Scalar(0, 0, 255), 2, 8, 0);
		}
		imshow("Before", image);
		imshow("After", dst);
		waitKey(0);
	}
}
//浮雕&雕刻
void No9() {
	Mat src = imread("cat.jpeg",IMREAD_REDUCED_COLOR_2);
	Mat img0(src.size(), IMREAD_REDUCED_GRAYSCALE_2);
	Mat img1(src.size(), IMREAD_REDUCED_GRAYSCALE_2);
	for (int y = 1; y < src.rows - 1; y++) {
		uchar* p0 = src.ptr<uchar>(y);
		uchar* p1 = src.ptr<uchar>(y + 1);
		uchar* q0 = img0.ptr<uchar>(y);
		uchar* q1 = img1.ptr<uchar>(y);
		for (int x = 1; x < src.cols - 1; x++) {
			for (int y = 1; y < src.rows - 1; y++) {
				for (int i = 0; i < 3; i++) {

					int tmp0 = p1[3 * (x + 1) + i] - p0[3 * (x - 1) + i] + 128;//浮雕
					if (tmp0 < 0)
						q0[3 * x + i] = 0;
					else if (tmp0 > 255)
						q0[3 * x + i] = 255;
					else
						q0[3 * x + i] = tmp0;

					int tmp1 = p0[3 * (x - 1) + i] - p1[3 * (x + 1) + i] + 128;//雕刻
					if (tmp1 < 0)
						q1[3 * x + i] = 0;
					else if (tmp1 > 255)
						q1[3 * x + i] = 255;
					else
						q1[3 * x + i] = tmp1;
				}
			}
		}
	}
	imshow("src", src);
	imshow("浮雕", img0);
	imshow("雕刻", img1);

	waitKey(0);
}
//AsciiArt
void AsciiArt(Mat &image) {
	if (!image.empty()) {
		system("cls");
		for (int i = 0; i < image.rows; i++) {
			for (int j = 0; j < image.cols; j++) {
				if (0 <= image.at<uchar>(i, j) && image.at<uchar>(i, j) <= 25)cout << " ";
				else if (26 <= image.at<uchar>(i, j) && image.at<uchar>(i, j) <= 50)cout << ".";
				else if (51 <= image.at<uchar>(i, j) && image.at<uchar>(i, j) <= 75)cout << ":";
				else if (76 <= image.at<uchar>(i, j) && image.at<uchar>(i, j) <= 100)cout << "-";
				else if (101 <= image.at<uchar>(i, j) && image.at<uchar>(i, j) <= 125)cout << "=";
				else if (126 <= image.at<uchar>(i, j) && image.at<uchar>(i, j) <= 150)cout << "+";
				else if (151 <= image.at<uchar>(i, j) && image.at<uchar>(i, j) <= 175)cout << "*";
				else if (176 <= image.at<uchar>(i, j) && image.at<uchar>(i, j) <= 200)cout << "#";
				else if (201 <= image.at<uchar>(i, j) && image.at<uchar>(i, j) <= 225)cout << "%";
				else if (226 <= image.at<uchar>(i, j) && image.at<uchar>(i, j) <= 255)cout << "@";
			}
			cout << endl;
		}

		imshow("image", image);
		waitKey(0);
	}
}
int main() {
	int n;
	while (true) {
		system("cls");

		cout << "1.人臉偵測\n2.素描風\n3.描邊\n4.去浮水印\n5.特定範圍去背\n"
			<< "6.毛玻璃特效\n7.縮放、明暗、選轉\n8.消除紅眼\n9.浮雕&雕刻\n10.Ascii Art\n" << endl;

		cout << "請選擇功能(-1離開):";

		cin >> n;
		if (n == -1)break;
		else if (1 > n || n > 10) {
			continue;
		}
		else {
			switch (n) {
				case 1:
				{
					Mat img = imread("face.jpeg",IMREAD_REDUCED_COLOR_2);
					if (!img.empty()) {
						faceIdentify(img);
						imshow("img", img);
						waitKey(0);
					}
					
					break; 
				}
				case 2: 
				{
					Mat img = imread("people.jpeg", IMREAD_REDUCED_COLOR_2);
					if (!img.empty()) {
						adjustable(img);
					}

					waitKey(0);
					break;
				}
				case 3:
					No3();
					break;
				case 4:
				{
					Mat img = imread("watermark.jpg", IMREAD_REDUCED_COLOR_4);
					if (!img.empty()) {
						onChangePaint(r1, &img);
						createTrackbar("r", "Before", &r1, 255, onChangePaint, &img);
						createTrackbar("g", "Before", &r2, 255, onChangePaint, &img);
						createTrackbar("b", "Before", &r3, 255, onChangePaint, &img);
					}
					waitKey(0);
					break;
				}
				case 5:
					No5();
					break;
				case 6:
				{
					Mat src = imread("landscape.jpeg", IMREAD_REDUCED_COLOR_2);
					if (!src.empty()) {
						int r = 0;
						int max = 10;

						onChangeGlass(r, &src);
						createTrackbar("Range", "Result", &r, max, onChangeGlass, &src);

						waitKey(0);
					}
					break;
				}
				case 7:
				{
					Mat image = imread("store.jpeg", IMREAD_REDUCED_COLOR_2);
					if (!image.empty()) {
						onChangeZoom(maxPercent, &image);
						createTrackbar("Zoom", "dst", &maxPercent, maxPercent, onChangeZoom, &image);
						createTrackbar("Brightness", "dst", &gamma, 20, onChangeZoom, &image);
						createTrackbar("Angle", "dst", &angle, 360, onChangeZoom, &image);
						waitKey(0);
					}
					break;
				}
				case 8:
				{
					Mat image = imread("redEye.jfif", IMREAD_REDUCED_COLOR_2);
					redEyeRemove(image);
					break;
				}
				case 9:
					No9();
					break;
				case 10:
				{
					Mat image = imread("ascii.jpeg", IMREAD_REDUCED_GRAYSCALE_8);
					AsciiArt(image);
					break;
				}
			}
		}
	}
	
	cin.get();
	return 0;
}