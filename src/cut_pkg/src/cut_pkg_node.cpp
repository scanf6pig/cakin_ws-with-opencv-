#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main()
{
    //读取图像
    Mat image = imread("/home/lin/Pictures/hm2.png");

    //定义颜色的阀值（HSV颜色空间）
    Scalar lower_brown(10,50,50);
    Scalar upper_brown(30,255,255);

    Scalar lower_green(36,25,25);
    Scalar upper_green(70,255,255);

    //将图像由BGR转换为HSV
    Mat hsv_image;
    cvtColor(image,hsv_image,cv::COLOR_BGR2HSV);

    //定义掩码，将图像中颜色区域分为黑色和白色
    Mat mask_brown, mask_green;
    inRange(hsv_image,lower_brown,upper_brown,mask_brown);
    inRange(hsv_image,lower_green,upper_green,mask_green);

    //开运算，去除噪声，填充孔洞
    Mat kernel = getStructuringElement(MORPH_RECT,Size(5,5));
    morphologyEx(mask_brown,mask_brown,MORPH_OPEN,kernel);
    morphologyEx(mask_green,mask_green,MORPH_OPEN,kernel);

    //在原始图像应用掩码，提取绿色和棕色区域
    Mat brown_image, green_image;
    bitwisw_and(image, image, brown_image, mask_brown);
    bitwisw_and(image, image, green_image, mask_green);

    //显示图像
    imshow("BROWN",brown_image);
    imshow("GREEN",green_image);
    waitKey(0);
    destroyAllWindows();

    return 0;
}