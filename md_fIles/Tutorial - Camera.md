## Hardware - Camera

##### PointGrey - Black fly 3

###### Specification

- 1288 x 964 해상도
- 30fps
- USB 연결
- ROS Library 지원 - https://github.com/ros-drivers/pointgrey_camera_driver (src에 있는 pointgrey_camera_driver.zip)
- 카메라 렌즈 장착 필요

###### 연결 - 컴퓨터

1. 카메라에 렌즈를 장착한 후, USB를 연결합니다.

2. 카메라 드라이버를 설치하는 명령어 입니다.

   `sudo apt-get install ros-melodic-pointgrey-camera-driver`

   그후 한번 업데이트 해줍니다.

   `sudo apt-get update`

   아래의 코드는 카메라가 잘 인식이 되면 시리얼 넘버가 뜨게 해주는 코드입니다.

   `rosrun pointgrey_camera_driver list_cameras`

   인식이 되지 않으면 ubuntu를 재부팅하면 됩니다.

3. 터미널 창을 열어 아래의 명령어를 실행하면 카메라가 작동하며 영상 데이터를 취득합니다. ROS의 공용 Library인sensor_msgs/Image에 영상데이터들이 저장됩니다.

   `roslaunch pointgrey_camera_driver camera.launch camera:=/15384429`

4. 다른 터미널 창을 열어 아래의 명령어를 실행합니다.

   `rosrun indy_driver video`

   **영상 데이터를 src에 있는 [video.cpp](https://github.com/chaochao77/ROS_neuromeka_tutorial/blob/main/software/src/indy-ros/indy_driver/src/video.cpp) 로 불러와 영상처리를 해주는 파일을 실행**하는 작업입니다. 굳이 해당 파일뿐만 아니라, 본인이 영상처리하고자 하는 코드파일에 sensor_msgs/Image.h를 헤더파일로 포함시키면 현재 카메라 센서로 부터 저장되는 영상 데이터를 가져와 자유로이 하고자하는 영상 처리를 할 수 있습니다.

   이 프로젝트에서는 간단하게 물체를 명암으로 구분한 뒤, 컨투어 함수를 이용하여 물체를 구분했습니다.

5. 종료는 명령어를 실행 시킨 터미널 창에서 ctrl+c를 누르면 됩니다.

###### ROS - 카메라 Image 데이터

- ROS Library를 지원하는 카메라를 ros로 실행시킬 경우, 카메라 센서로 인식되어 받고 있는 이미지들은 ROS의 센서 메세지 공간 Sensor_msg - image에 저장됩니다. 따라서 **sensor_msgs/Image 를 헤더**로 불러와 코드 파일내에서 **Subcribe**를 하면 영상 데이터 취득 및 영상 처리를 할 수 있습니다.
- 노트북의 웹캠도 관련 ROS library를 설치하면 이번 프로젝트의 video.cpp을 참고하면 응용하여 사용 할 수 있습니다.

## 