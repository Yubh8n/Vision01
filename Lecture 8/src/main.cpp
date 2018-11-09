/*
RoVi1
Example application to load and display an image.

Version: 9e42db7
*/

#include <opencv2/highgui.hpp>

#include <iostream>
#include <opencv/cv.hpp>


using namespace cv;

const int Hue_max = 180;
int Hue_slider_min;
int Hue_slider_min_old;
int Hue_slider_max;
int Hue_slider_max_old;


const int Satuation_max = 255;
int Satuation_slider_min;
int Satuation_slider_min_old;
int Satuation_slider_max;
int Satuation_slider_max_old;


const int Value_max = 255;
int Value_slider_min;
int Value_slider_min_old;
int Value_slider_max;
int Value_slider_max_old;

Mat img;
Mat HSV;

void onTrackbar(int, void *)
{
    Mat imgConvert(img.rows,img.cols,CV_8UC1,CvScalar(0));

    if (Hue_slider_min_old != Hue_slider_min ||
        Hue_slider_max_old != Hue_slider_max ||
        Satuation_slider_min != Satuation_slider_min_old ||
        Satuation_slider_max != Satuation_slider_max_old ||
        Value_slider_min_old != Value_slider_min_old ||
        Value_slider_max_old != Value_slider_max)
    {
        for (int i = 0; i<imgConvert.rows; i++)
            for (int j = 0; j<imgConvert.cols;j++)
                if (HSV.at<Vec3b>(i,j).val[0] > Hue_slider_min && HSV.at<Vec3b>(i,j).val[0] < Hue_slider_max &&
                    HSV.at<Vec3b>(i,j).val[1] > Satuation_slider_min && HSV.at<Vec3b>(i,j).val[1] < Satuation_slider_max &&
                    HSV.at<Vec3b>(i,j).val[2] > Value_slider_min && HSV.at<Vec3b>(i,j).val[2] < Value_slider_max)
                    imgConvert.at<uchar>(i,j) = 255;
    }
    imshow("HSV Manipulation", imgConvert);
}

int main(int argc, char* argv[])

{    // Load image file
    img = cv::imread("lego.jpg");

    // Check that the image file was actually loaded
    if (img.empty()) {
        std::cout << "Input image not found << '\n";
        return 1;
    }
    cv::Mat b(img.rows,img.cols,CV_8UC1,CvScalar(0));
    cv::Mat r(img.rows,img.cols,CV_8UC1,CvScalar(0));
    cv::Mat g(img.rows,img.cols,CV_8UC1,CvScalar(0));


    cv::Mat HSV_segment(img.rows,img.cols,CV_8UC1,CvScalar(0));
    //Mat HSV;
    cvtColor(img,HSV,COLOR_BGR2HSV,0);

    cv::Mat Hue1(img.rows,img.cols,CV_8UC1,CvScalar(0));
    cv::Mat Satuation1(img.rows,img.cols,CV_8UC1,CvScalar(0));
    cv::Mat Value1(img.rows,img.cols,CV_8UC1,CvScalar(0));


    for (int i = 0; i<img.rows; i++)
    {
        for (int j = 0; j<img.cols; j++)
        {
            Hue1.at<uchar>(i,j) = HSV.at<Vec3b>(i,j).val[0];
            Satuation1.at<uchar>(i,j) = HSV.at<Vec3b>(i,j).val[1];
            Value1.at<uchar>(i,j) = HSV.at<Vec3b>(i,j).val[2];

            b.at<uchar>(i,j) = img.at<Vec3b>(i,j).val[0];
            g.at<uchar>(i,j) = img.at<Vec3b>(i,j).val[1];
            r.at<uchar>(i,j) = img.at<Vec3b>(i,j).val[2];
        }
    }

    namedWindow("HSV Manipulation");
    imshow("HSV Manipulation",img);

    Hue_slider_min = 0;
    Hue_slider_max = Hue_max;
    Satuation_slider_min = 0;
    Satuation_slider_max = Satuation_max;
    Value_slider_min = 0;
    Value_slider_max = Value_max;

    createTrackbar("Hue_min","HSV Manipulation",&Hue_slider_min, Hue_max,onTrackbar);
    createTrackbar("Hue_max","HSV Manipulation",&Hue_slider_max, Hue_max,onTrackbar);
    createTrackbar("Satuation_min","HSV Manipulation",&Satuation_slider_min, Satuation_max,onTrackbar);
    createTrackbar("Satuation_max","HSV Manipulation",&Satuation_slider_max, Satuation_max,onTrackbar);
    createTrackbar("Value_min","HSV Manipulation",&Value_slider_min, Value_max,onTrackbar);
    createTrackbar("Value_max","HSV Manipulation",&Value_slider_max, Value_max,onTrackbar);

    // Show the image
    //cv::imshow("org Img", img);
    //cv::imshow("Blue Img", b);
    //cv::imshow("Red Img", r);
    //cv::imshow("Green Img", g);
    //cv::imshow("Hue Img", Hue1);
    //cv::imshow("Satuation Img", Satuation1);
    //cv::imshow("Value Img", Value1);
    //cv::imshow("hsv", HSV_segment);

    // Wait for escape key press before returning
    while (cv::waitKey() != 27)
        ; // (do nothing)

    return 0;
}
