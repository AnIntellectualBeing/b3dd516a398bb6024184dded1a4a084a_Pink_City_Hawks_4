#include <opencv2/opencv.hpp>

int main() {
    cv::CascadeClassifier face_cascade;
    if (!face_cascade.load("haarcascade_frontalface_default.xml")) {
        std::cerr << "Error loading face cascade classifier. Make sure the XML file is in the current directory." << std::endl;
        return -1;
    }

    cv::VideoCapture cap(0); // Open the default camera (camera index 0)
    if (!cap.isOpened()) {
        std::cerr << "Error opening the camera." << std::endl;
        return -1;
    }

    cv::Mat frame;
    while (true) {
        cap >> frame; // Capture frame from the camera
        if (frame.empty()) {
            std::cerr << "Error capturing frame." << std::endl;
            break;
        }

        cv::Mat gray;
        cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);

        std::vector<cv::Rect> faces;
        face_cascade.detectMultiScale(gray, faces, 1.1, 4);

        // Draw rectangles around detected faces
        for (const auto& face : faces) {
            cv::rectangle(frame, face, cv::Scalar(255, 0, 0), 2);
        }

        // Display the frame with detected faces
        cv::imshow("Face Detection", frame);

        // Break the loop if 'q' key is pressed
        if (cv::waitKey(1) == 'q') {
            break;
        }
    }

    // Release the camera and close windows
    cap.release();
    cv::destroyAllWindows();

    return 0;
}
