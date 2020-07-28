#include <ros/ros.h>
    #include <image_transport/image_transport.h>
    #include <opencv2/highgui/highgui.hpp>
    #include <cv_bridge/cv_bridge.h>
    
    void imageCallback(const sensor_msgs::ImageConstPtr& msg)
    {
      try
      {
       cv::imshow("view", cv_bridge::toCvShare(msg, "mono8")->image);
       cv::waitKey(0);
     }
     catch (cv_bridge::Exception& e)
     {
       ROS_ERROR("Could not convert from '%s' to 'bgr8'.", msg->encoding.c_str());
     }
   }
   
   int main(int argc, char **argv)
   {
     ros::init(argc, argv, "imagex");
     ros::NodeHandle nh;
     cv::namedWindow("view2",cv::WINDOW_AUTOSIZE);
     cv::startWindowThread();
     image_transport::ImageTransport it(nh);
     image_transport::Subscriber sub = it.subscribe("final/image", 1, imageCallback);
     ros::spin();
     cv::destroyWindow("view2");
}
