#include "native_add.h"
#include <opencv2/opencv.hpp>
#include <unistd.h>
using namespace std;
using namespace cv;

extern "C" {

    // A very short-lived native function.
    FFI_PLUGIN_EXPORT intptr_t sum(intptr_t a, intptr_t b) {
        return a + b;
    }

    // Multiply function implementation
    FFI_PLUGIN_EXPORT intptr_t multiply(intptr_t a, intptr_t b) {
        return a * b;
    }

    // Factorial function implementation
    FFI_PLUGIN_EXPORT uint64_t factorial(uint64_t n) {
        if (n == 0 || n == 1)
            return 1;
        else
            return n * factorial(n - 1);
    }

    // Manipulate matrix function implementation
    FFI_PLUGIN_EXPORT intptr_t manipulate_matrix() {
        // Creating a matrix
        cv::Mat matrix = cv::Mat::zeros(5, 5, CV_8UC1);

        // Setting values of all elements in the row with index 0
        matrix.row(0).setTo(Scalar(1));

        // Setting values of all elements in the column with index 3
        matrix.col(3).setTo(Scalar(3));

        int a = matrix.at<uchar>(0, 4);
        return a;
    }

    // A longer-lived native function, which occupies the thread calling it.
    FFI_PLUGIN_EXPORT intptr_t sum_long_running(intptr_t a, intptr_t b) {
    #if _WIN32
        Sleep(5000);
    #else
        usleep(5000 * 1000);
    #endif
        return a + b;
    }

    FFI_PLUGIN_EXPORT const char* version() {
        return CV_VERSION;
    }

    FFI_PLUGIN_EXPORT intptr_t process_image(char* inputImagePath, char* outputImagePath) {
        
        Mat input = imread(inputImagePath, IMREAD_GRAYSCALE);
        Mat input_rgb = imread(inputImagePath, IMREAD_UNCHANGED);
        Mat edges_img, blur_img, erode_img;
        float perimeter, area, circularity;
        Rect rect;
        vector<vector<Point>> filtered_contours;

        vector<vector<Point>> contours;
        vector<Vec4i> hierarchy;

        GaussianBlur(input, blur_img, Size(5, 5), 0);
        threshold(blur_img, edges_img, 120, 255, THRESH_BINARY);
        erode(edges_img, erode_img, Mat(), Point(-1, -1), 3);
        findContours(erode_img, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);


        for(int i = 0; i< contours.size() ;i++){
            perimeter = arcLength(contours[i], true);
            area = contourArea(contours[i]);
            rect = boundingRect(contours[i]);
            try
            {
                circularity = 4 * 3.1428 * (area / (perimeter * perimeter));
            }
            catch(const std::exception& e)
            {
                continue;
            }
            if(area > 100 && circularity > 0.5){
                filtered_contours.push_back(contours[i]);
            };
        }
        int i = 1;
        for (const auto& contour : filtered_contours) {
            rect = boundingRect(contour);
            int r = ((rect.width + rect.height) / 2) / 2 + 3;
            circle(input_rgb, Point(rect.x + (rect.width / 2), rect.y + (rect.height / 2)), r, Scalar(0, 255, 0), 2);
            putText(input_rgb, to_string(i), Point(rect.x + (rect.width / 2), rect.y + (rect.height / 2)), 1, 2, Scalar(0, 0, 255), 2);
            i++;
        }
        
        imwrite(outputImagePath, input_rgb);
        return i;
    }
    
    

} // extern "C"
