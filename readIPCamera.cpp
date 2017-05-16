#include <opencv2/opencv.hpp>
#include <thread>
#include <mutex>
#include <queue>

using namespace std;
using namespace cv;

bool endTracking = false;
std::deque<cv::Mat> dMats;	// 视频帧缓冲队列
std::recursive_mutex m;		// 锁
VideoCapture cap;

void getFrame(){

	cv::Mat framein;

	while (!endTracking){
		cap >> framein;
		{
			// 加锁
			std::lock_guard<std::recursive_mutex> lk(m);
			dMats.push_back(framein);
		}
	}
}

int main()
{
	cap.open("rtsp://192.168.1.168:554/sub");
	if (!cap.isOpened())
	{
		cerr << "open camera failed.";
		return -1;
	}

	namedWindow("Test");

	// 创建线程，读取网口摄像头
	std::thread t1(&getFrame);

	while (true)
	{
		Mat frameout;
		{
			// 加锁
			std::lock_guard<std::recursive_mutex> lk(m);

			while (dMats.size() > 0){
				frameout = dMats.front();
				dMats.pop_front();
			}
		}

		if (frameout.empty()) continue;

		imshow("Test", frameout);

		char ch = waitKey(30);
		if (ch == 27)
		// 按ESC退出
		{
			endTracking = true;
			break;
		}
	}
	// 线程结束返回
	t1.join();

	return 0;
}
