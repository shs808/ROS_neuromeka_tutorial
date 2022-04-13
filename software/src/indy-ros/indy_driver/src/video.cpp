   #include <ros/ros.h>
   #include <image_transport/image_transport.h>
   #include <opencv2/highgui/highgui.hpp>
   #include <cv_bridge/cv_bridge.h>
   #include <opencv2/imgproc/imgproc.hpp>
   #include <sensor_msgs/image_encodings.h>
   #include <sensor_msgs/Image.h>
   #include <indy_driver/CameraDetect.h>
   #include <indy_driver/Cameratrg.h>
   #include <iostream>
   using namespace std;
   using namespace cv;

   double cr = 0;
         double obX =0;
      double obY =0;
      double trX =0;
      double trY =0;

void msgcallback(const indy_driver::Cameratrg::ConstPtr& msg){
	cr=msg->on ;
}
  void imageCallback(const sensor_msgs::ImageConstPtr& msg)
 {
    try
    {
    // cv::imshow("view", cv_bridge::toCvShare(msg, "bgr8")->image);
    // cv::waitKey(30);
    cv::Mat frame = cv_bridge::toCvShare(msg, sensor_msgs::image_encodings::BGR8)->image;
    //cv::imwrite("/home/hwj/Documents/testcam/img.jpg",frame);
    float cmdata[] = {1190.596624173294, 0, 613.8264982857706, 0, 1197.481389143005, 496.568669564977, 0, 0, 1};
    cv::Mat cmtrx(3,3,CV_32F,cmdata);
    float dsdata[] ={-0.3169705527285323, 0.157151705099085, -0.003364806857495433, 0.008141312356792239, 0};
    cv::Mat dstrx(1,5,CV_32F,dsdata);
    cv::Mat calframe ;
    cv::undistort(frame,calframe,cmtrx,dstrx);
    Point2f src_p[4], dst_p[4];
    src_p[0] = Point2f(244,143);
    src_p[1] = Point2f(1038,132);
    src_p[2] = Point2f(91,909);
    src_p[3] = Point2f(1212,896);

    dst_p[0] = Point2f(244,132);
    dst_p[1] = Point2f(1038,132);
    dst_p[2] = Point2f(244,896);
    dst_p[3] = Point2f(1038,896);
    

    cv::Mat perspect_mat = cv::getPerspectiveTransform(src_p,dst_p);
    cv::Mat src_ipm;

    cv::warpPerspective(calframe,src_ipm,perspect_mat,Size(1288,964));
    cv::Mat src_gray;
    cv::Mat src_binary;
    //cv::namedWindow("view2", cv::WINDOW_AUTOSIZE);
    cv::cvtColor(src_ipm, src_gray, cv::COLOR_RGB2GRAY);
    cv::GaussianBlur(src_gray, src_gray, cv::Size(3, 3), 0, 0, cv::BORDER_DEFAULT);
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    Rect rect(244,132,794,764);
    src_gray = src_gray(rect);

    cv::threshold(src_gray,src_binary,150,255,0);
    cv::findContours(src_binary,contours,hierarchy,CV_RETR_EXTERNAL,CV_CHAIN_APPROX_SIMPLE);
    //cv::drawContours(frame,contours,-1,(100,15,0),1,8,hierarchy,0,Point2i());
    //cout << "contour size : "<<contours.size() << endl;
    vector<vector<Point>> conPoly(contours.size());
    vector<Rect> boundRect(contours.size());

    vector<Point> biggest;
    Mat imgshow = src_ipm(rect);
    int maxArea = 0;
    double obarea = 0;
    double trgcordx = 0;
    double trgcordy = 0;
    for (unsigned int i = 0;  i < contours.size();  i++)
{
    // std::cout << " Area: " << i<< " 번째 " << contourArea(contours[i]) << std::endl;
   obarea = contourArea(contours[0]);
}
if(obarea > 0 && obarea <6000){
   trgcordx = 0.40;
   trgcordy = 0.55;
  // printf("세모\n");
}
else if (obarea > 8000 && obarea <11000){
   trgcordx = 0.40;
   trgcordy = 0.45;
    //printf("기어\n");
}
else if (obarea > 11300){
   trgcordx = 0.42;
   trgcordy = 0.55;
    //printf("네모\n");
}
else if (obarea == 0){
   trgcordx = 0.4;
   trgcordy = 0.4;
}

  vector<Moments> mu(contours.size() );
  for( int i = 0; i < contours.size(); i++ )
     { mu[i] = moments( contours[i], false ); }

  ///  Get the mass centers:
  vector<Point2f> mc( contours.size() );
    for( int i = 0; i < contours.size(); i++ )
     { mc[i] = Point2f( mu[i].m10/mu[i].m00 , mu[i].m01/mu[i].m00 ); }
        
        
      double xpx = 0.00047;
      double ypx = 0.00046;
       /* for (unsigned int i = 0;  i < contours.size();  i++)
{
     std::cout << " 좌표 " << i<< " 번째 " << mc[i] << std::endl;
}*/
    for( int i = 0; i< contours.size(); i++ )
     {
       circle( imgshow, mc[i], 4, Scalar(255,255,0), -1, 8, 0 );
     }
     /*for(int i = 0; i< 11; i++)
         for(int j = 0; j< 10; j++)
      circle( imgshow,Point2f(80+i*63,58+j*65), 4, Scalar(255,0,0), -1, 8, 0 );*/
      //circle( imgshow,Point2f(143,70), 4, Scalar(255,0,0), -1, 8, 0 );
      if(contours.size()!=0){
         obX = (mu[0].m10/mu[0].m00)*xpx;
         obY = (mu[0].m01/mu[0].m00)*ypx;
         trX = trgcordx;
         trY = trgcordy;
      }
      else if(contours.size()==0){
         obX = 0;
         obY = 0;
         trX = 0;
         trY = 0;
      }
     //std::cout << " 좌표 " << obX<< " && " << obY << std::endl;
    for (int i = 0; i < contours.size(); i++)
    {
      cv::drawContours(imgshow,contours,i,Scalar(255,0,255),2);
    }
    //cv::imshow("view2", src_binary);
    cv::namedWindow("view5", cv::WINDOW_NORMAL);
    /* cv::imshow("view1", frame);
      cv::imshow("view2", src_ipm);
       cv::imshow("view3", src_binary);
        cv::imshow("view4", src_gray);*/
    cv::imshow("view5", imgshow);
    cv::waitKey(30);
    }
    catch (cv_bridge::Exception& e)
    {
    ROS_ERROR("Could not convert from '%s' to 'bgr8'.", msg->encoding.c_str());
    }
  }
  
  int main(int argc, char **argv)
 {
    ros::init(argc, argv, "video");
    ros::NodeHandle nh,n1,n2;

    image_transport::ImageTransport it(nh);
    image_transport::Subscriber sub = it.subscribe("camera/image_raw", 1, imageCallback);
   ros::Publisher pub = n1.advertise<indy_driver::CameraDetect>("CameraDetect", 10);



   ros::Subscriber sub2 = n2.subscribe<indy_driver::Cameratrg>("Cameratrg", 10, msgcallback);
    ros::Publisher pub2 = n2.advertise<indy_driver::Cameratrg>("Cameratrg", 10);
      ros::AsyncSpinner spinner(1);
    spinner.start();
   ros::Rate loop_rate(5);
   indy_driver::CameraDetect msg;
   indy_driver::Cameratrg msg2;
 while (ros::ok()){
      if(cr==1){
            msg.on = 1;
            msg.obX = -(obX-0.19);
            msg.obY = (obY+0.41);
            msg.trX = trX;
            msg.trY = trY;
            ROS_INFO_NAMED("COOORDINATE", "coordinate : ObX = %f,obY = %f,trX= %f,trY= %f",msg.obX,msg.obY,msg.trX,msg.trY);
            msg2.on = 0; 
         pub2.publish(msg2);
        	pub.publish(msg);
   }
        loop_rate.sleep();
        //ros::spin();
    }
       // ros::spin();
    
    cv::destroyWindow("view");
 }