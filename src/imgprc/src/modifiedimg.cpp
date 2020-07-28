#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>
#include <cv.h>
	
    image_transport::Subscriber sub ;
    image_transport::Publisher pub ;

    void imageCallback(const sensor_msgs::ImageConstPtr& msg)
    {
      try
      {
      cv::imshow("view" , cv_bridge::toCvShare(msg, "bgr8")->image);
      cv::waitKey(0);
      cv::Mat converted_image;
   	cv::cvtColor(cv_bridge::toCvShare(msg, "bgr8")->image , converted_image , CV_BGR2GRAY);
	imwrite("/home/divyanshu/Motu/newimg.jpg" , converted_image);
	sensor_msgs::ImagePtr msg = cv_bridge::CvImage(std_msgs::Header(), "mono8", converted_image).toImageMsg();
	
       
       pub.publish(msg);
      
     }
     catch (cv_bridge::Exception& e)
     {
       ROS_ERROR("Could not convert from '%s' to 'bgr8'.", msg->encoding.c_str());
     }
   }
   
   int main(int argc, char **argv)
   {
     ros::init(argc, argv, "image_listener");
     ros::NodeHandle nh;
    
     cv::namedWindow("view",cv::WINDOW_AUTOSIZE);
     cv::startWindowThread();
     image_transport::ImageTransport it(nh);
      sub = it.subscribe("camera/image", 1, imageCallback);
      pub = it.advertise("final/image" , 1);
	
     ros::spin();
     cv::destroyWindow("view");
   }
