## 자동 분류 공정 (Pick & Place in this project)

이 프로젝트에서 구성한 자동 분류 공정에 대한 ROS 코드는 아래의 순서에 따라 작동하게 됩니다.

[![img](https://github.com/chaochao77/ROS_neuromeka_tutorial/raw/main/image/40.jpg)](https://github.com/chaochao77/ROS_neuromeka_tutorial/blob/main/image/40.jpg)

##### 하드웨어 세팅

[![img](https://github.com/chaochao77/ROS_neuromeka_tutorial/raw/main/image/30.jpg)](https://github.com/chaochao77/ROS_neuromeka_tutorial/blob/main/image/30.jpg)[![img](https://github.com/chaochao77/ROS_neuromeka_tutorial/raw/main/image/31.jpg)](https://github.com/chaochao77/ROS_neuromeka_tutorial/blob/main/image/31.jpg)

위의 왼쪽 이미지처럼 로봇과 카메라, 작업 테이블을 간단히 세팅하여 실험을 진행했습니다. 잡을 물체는 왼쪽 이미지처럼 기어와 다른 모양들의 물체들로 구성했습니다.

하드웨어 세팅에서 가장 중요한 부분은 물체가 놓이는 **평면의 높이**, 로봇이 **물체를 잡을 위치에 대한 카메라의 픽셀당 좌표 값계산**, 그리고 가장 중요한 **로봇의 영점좌표와 카메라의 영점좌표 조정**입니다. 아래의 예시 이미지들은 이번 프로젝트에서 사용한 세팅 구도입니다.

![image](https://user-images.githubusercontent.com/79825525/168936220-ae0d71d1-0b30-4109-93ec-00a9fdfa7d8f.png)

예를 들어 위의 이미지 처럼 로봇의 영점좌표(**엔드툴 좌표가 아닌 로봇의 0번 조인트의 중심 좌표**)에서 카메라의 ROI영역의 영점좌표가 다를 경우, **카메라 좌표 중심과 indy10 X축 영점 사이거리 Dx와 y축 사이거리 Dy를 이동 좌표에 더하거나 빼주고, 축 방향이 서로 반대 일 경우에는 좌표를 반전시키는 등, 로봇의 영점좌표 기준으로 좌표 계산**을 해야합니다. **ROS의 길이 표준 값은 미터(m) 기준 입니다. 예를 들어 Dx가 10cm미터라하면 0.1만큼을 계산식에 넣어야 합니다.**

예를 들어 이번 프로젝트에서 사용한 [video.cpp](https://github.com/chaochao77/ROS_neuromeka_tutorial/blob/main/software/src/indy-ros/indy_driver/src/video.cpp) 에서 178번째와 179번째 줄을 보면 아래와 같이 물체 좌표 계산하였습니다.

```
        robot_X = -(camera_X - ROI_center_X - Dx);   // x축 방향이 반대
        robot_Y = (camera_Y + Dy);   
```

[![img](https://github.com/chaochao77/ROS_neuromeka_tutorial/raw/main/image/36.jpg)](https://github.com/chaochao77/ROS_neuromeka_tutorial/blob/main/image/36.jpg)

또한 물체가 한 평면 위에 있을 경우, 로봇의 영점좌표와 평면의 높이차이 H와, 그리퍼의 잡는 부분에서 엔드툴까지의 높이 G.H를 고려하여 로봇의 도달 좌표의 z 값을 계산해야 합니다.

이 프로젝트에서는 한 평면만을 사용했기에 로봇의 이동 높이는 고정이 되어있습니다. 그렇기에 실제 로봇에 물체 및 목표 좌표를 보내는 코드에서 z값이 고정적으로 들어가게 됩니다. [camera_process.cpp](https://github.com/chaochao77/ROS_neuromeka_tutorial/blob/main/software/src/indy-ros/indy_driver/src/camera_process.cpp)에서 52번째 줄이 고정된 계산 값인데 계산 식은 아래식을 따릅니다.

```
obz = H + G.H
```

**H**는 물체가 놓이는 **평면(테이블)과 로봇의 영점좌표의 차이**, 그리고 **G.H는 그리퍼의 높이**입니다. 그리퍼의 높이를 더하는 이유는 Moveit의 경우 로봇이 좌표로 **이동 할 떄 기준은 로봇의 영점좌표**이고 **이동 객체의 중심은 로봇의 끝(엔드툴)**이기 때문입니다.

[camera_process.cpp](https://github.com/chaochao77/ROS_neuromeka_tutorial/blob/main/software/src/indy-ros/indy_driver/src/camera_process.cpp)에서 60번째 줄의 trz 값은 물체의 이동 목표 좌표의 높이 값입니다. 타겟 좌표 또한 위와 같이 잘 계산 하여 값을 넣으면 됩니다.

로봇과 카메라의 세팅에 따라 축기준 좌표계산 값이 달라짐으로 그에 해당하는 코드들을 로봇의 현 상황에 따라 수정하면 됩니다.

##### Gazebo test

작성한 ROS 코드들이 맞는 순서에 따라 잘 움직이는 지, 좌표로 이동이 깔끔히 잘 계산되어 가는 지등을 Gazebo로 테스트 할 수 있습니다.

먼저 home/catkin_ws/src/indy_ros/indy10_gazebo/launch에 있는 [indy10_moveit_gazebo.launch](https://github.com/chaochao77/ROS_neuromeka_tutorial/blob/main/software/src/indy-ros/indy10_gazebo/launch/indy10_moveit_gazebo.launch) 에서 include부분을 찾아 주석처리를 없앱니다. html 언어의 주석처리는 <!-- ~~~ -- > 입니다.

[![img](https://github.com/chaochao77/ROS_neuromeka_tutorial/raw/main/image/28.jpg)](https://github.com/chaochao77/ROS_neuromeka_tutorial/blob/main/image/28.jpg)[![img](https://github.com/chaochao77/ROS_neuromeka_tutorial/raw/main/image/29.jpg)](https://github.com/chaochao77/ROS_neuromeka_tutorial/blob/main/image/29.jpg)

카메라를 연결한 후, 카메라 런치파일과 video.cpp을 각기 다른 터미널 창에서 실행합니다.

```
roslaunch pointgrey_camera_driver camera.launch camera:=/15384429
rosrun indy_driver video
```

이제 또다른 터미널창을 열어 Gazebo 런치 파일을 실행합니다.

```
roslaunch indy10_gazebo indy10_moveit_gazebo.launch
```

아래의 영상은 로봇이 잡을 여러 물체를 이리 저리 옮겨보고 바꿔보며 Gazebo에서 로봇이 설계한 대로 잘 찾아서 움직이는지 테스트하는 영상입니다. 카메라가 보는 방향과 로봇의 방향이 반대로 반전되어 있습니다.

[![Gazebo_test](https://camo.githubusercontent.com/e8b60236a40c6a9851b5b7335246bf4ada824717b9767d9ee25d89d7cc3f0df8/687474703a2f2f696d672e796f75747562652e636f6d2f76692f6c557844627756785244772f302e6a7067)](https://youtu.be/lUxDbwVxRDw?t=0s)

- Gazebo에서 한칸당 1m 입니다.

테스트를 하면서 로봇의 움직임을 확인하고, [camera_process.cpp](https://github.com/chaochao77/ROS_neuromeka_tutorial/blob/main/software/src/indy-ros/indy_driver/src/camera_process.cpp)이나 [video.cpp](https://github.com/chaochao77/ROS_neuromeka_tutorial/blob/main/software/src/indy-ros/indy_driver/src/video.cpp) 에서 좌표 이동에 대한 계산 값을 수정하여 조정합니다. obx, oby 관련 코드들은 물체 좌표이며 trx, try 관련 코드들은 물체가 이동해야 할 타겟 좌표임으로 **실제 로봇 세팅에 맞게 값을 수정**하면 됩니다.

##### 실제 로봇 실행

Gazebo 테스트로 **좌표 조정 및 코드 수정이 완료**되면 실제 로봇에 적용해봅니다.

Gazebo에서 했던 것 같이 home/catkin_ws/src/indy_ros/indy_driver/launch의 [indy_interface.launch](https://github.com/chaochao77/ROS_neuromeka_tutorial/blob/main/software/src/indy-ros/indy_driver/launch/indy_interface.launch) 에서 44번째에서 47번째 까지의 주석처리를 없앱니다.

카메라를 연결한 후, Gazebo test에서 한 것 처럼

```
roslaunch pointgrey_camera_driver camera.launch camera:=/15384429
rosrun indy_driver video
```

을 각기다른 창에서 실행 시키면 됩니다.

```
roslaunch indy10_moveit_config moveit_planning_execution.launch robot_ip:=xxx.xxx.xxx.xxx
```

을 실행하면 이제 로봇이 물체를 찾고 그 물체를 옮기는 Pick & Place 를 시작합니다.
