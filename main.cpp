#include <opencv2/opencv.hpp>
#include <raspicam_cv.h>
#include <iostream>
#include <chrono>
#include <ctime>

using namespace std;
using namespace cv;
using namespace raspicam;

Mat frame;
RaspiCam_Cv Camera;

// Resolution for image
void Setup(int argc, char **argv, RaspiCam_Cv &Camera)
{
    Camera.set(CAP_PROP_FRAME_WIDTH, ("-w", argc, argv, 400));
    Camera.set(CAP_PROP_FRAME_HEIGHT, ("-h", argc, argv, 240));
    Camera.set(CAP_PROP_BRIGHTNESS, ("-br", argc, argv, 50));
    Camera.set(CAP_PROP_CONTRAST, ("-co", argc, argv, 50));
    Camera.set(CAP_PROP_SATURATION, ("-sa", argc, argv, 50));
    Camera.set(CAP_PROP_GAIN, ("-g", argc, argv, 50));
    Camera.set(CAP_PROP_FPS, ("-fps", argc, argv, 100));
}

// Capture frame
void Capture()
{
	Camera.grab();
    Camera.retrieve(frame);
    cvtColor(frame, frame, COLOR_BGR2RGB);
}

int main(int argc, char **argv)
{
    Setup(argc, argv, Camera);

    cout << "Connecting to camera" << endl;
    if (!Camera.open())
    {
        cout << "Failed to Connect" << endl;
        return -1;
    }

    while (1)
    {
        auto start = std::chrono::system_clock::now();

        Capture();
        namedWindow("orignal", WINDOW_KEEPRATIO);
        moveWindow("orignal", 50, 100);
        resizeWindow("orignal", 640, 480);
        imshow("orignal", frame);

        auto end = std::chrono::system_clock::now();
        std::chrono::duration<double> elapsedSeconds = end - start;
        float time = elapsedSeconds.count();
        int FPS = 1 / t;

        waitKey(1);
    }

    return 0;
}
