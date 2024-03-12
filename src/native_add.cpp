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

    FFI_PLUGIN_EXPORT void process_image(char* inputImagePath, char* outputImagePath) {
        
        Mat input = imread(inputImagePath, IMREAD_GRAYSCALE);
        Mat threshed, withContours;

        vector<vector<Point>> contours;
        vector<Vec4i> hierarchy;
        
        adaptiveThreshold(input, threshed, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY_INV, 77, 6);
        findContours(threshed, contours, hierarchy, RETR_TREE, CHAIN_APPROX_TC89_L1);
        
        cvtColor(threshed, withContours, COLOR_GRAY2BGR);
        drawContours(withContours, contours, -1, Scalar(0, 255, 0), 4);
        
        imwrite(outputImagePath, withContours);
        
    }
    
    

} // extern "C"
