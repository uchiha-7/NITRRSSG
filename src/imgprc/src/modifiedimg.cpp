#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>
#include <cv.h>
	
    image_transport::Subscriber sub ;
    image_transport::Publisher pub ;

    void imageCallback(const sensor_msgs::ImageConstPtr& msg)
    {
        cv::Mat converted_image;
	cv:: Mat received_image = cv_bridge::toCvShare(msg, "bgr8")->image;
   	cv::cvtColor( received_image , converted_image , CV_BGR2GRAY);
	imwrite("/home/divyanshu/Motu/newimg.jpg" , converted_image);
	sensor_msgs::ImagePtr msg2 = cv_bridge::CvImage(std_msgs::Header(), "mono8", converted_image).toImageMsg();
        pub.publish(msg2);
   }
   
   int main(int argc, char **argv)
   {
     ros::init(argc, argv, "image_listener");
     ros::NodeHandle nh;
     cv::namedWindow("view",cv::WINDOW_AUTOSIZE);
     image_transport::ImageTransport it(nh);
     pub = it.advertise("final/image" , 1);
     sub = it.subscribe("camera/image", 1, imageCallback);
     ros::spin();
     cv::destroyWindow("view");
   }
