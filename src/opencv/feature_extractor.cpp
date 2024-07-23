#include <opencv2/opencv.hpp>
#include <iostream>

int main(int argc, char** argv) {
    // 从命令行输入图像路径
    std::string image_path = "../images/1.png";
    if (argc > 1) {
        image_path = argv[1];
    }
    // 读取图像
    cv::Mat src = cv::imread(image_path, cv::IMREAD_GRAYSCALE);
    if (src.empty()) {
        std::cerr << "Could not open the image!" << std::endl;
        return -1;
    }
    std::cout << "Image path: " << image_path << std::endl;
    cv::imshow("Original Image", src);
    cv::waitKey(0);

    // 检测Harris角点
    cv::Mat dst, dst_norm, dst_norm_scaled;
    dst = cv::Mat::zeros(src.size(), CV_32FC1);

    int blockSize = 2;
    int apertureSize = 3;
    double k = 0.04;
    cv::cornerHarris(src, dst, blockSize, apertureSize, k);

    cv::imshow("Harris Corners", dst);
    cv::waitKey(0);
    // 归一化和转换
    cv::normalize(dst, dst_norm, 0, 255, cv::NORM_MINMAX, CV_32FC1, cv::Mat());
    cv::convertScaleAbs(dst_norm, dst_norm_scaled);

    // 绘制角点
    for (int i = 0; i < dst_norm.rows; i++) {
        for (int j = 0; j < dst_norm.cols; j++) {
            if ((int)dst_norm.at<float>(i, j) > 200) {
                cv::circle(dst, cv::Point(j, i), 5, cv::Scalar(0), 2, 8, 0);
            }
        }
    }

    // 显示结果
    cv::imshow("Harris Corners", dst);
    cv::waitKey(0);

    return 0;
}
