## Tutorial - ROS

##### ROS 설치 - Rviz, Gazebo

1. **Linux에서 ctrl+alt+t 로 터미널(cmd)창**을 열고 아래의 코드를 순서대로 입력합니다. **ROS key 설정**하는 코드입니다.

- ROS 홈페이지에 접속하여 ROS key관련 최신 리스트를 받아오는 코드입니다.

  `sudo sh -c 'echo "deb http://packages.ros.org/ros/ubuntu $(lsb_release -sc) main" > /etc/apt/sources.list.d/ros-latest.list'`

  `sudo apt-key adv --keyserver 'hkp://keyserver.ubuntu.com:80' --recv-key C1CF6E31E6BADE8868B172B4F42ED6FBAB17C654`

- 최신 정보 업데이트를 진행합니다.

  `sudo apt-get update`

1. **ROS 설치 코드**입니다. 터미널(cmd)에 아래와 같이 입력하시면 됩니다.

   본 튜토리얼에서는 ROS1 melodic 버전을 사용합니다.

   `sudo apt-get install ros-melodic-desktop-full`

   주의 : WIFI나 인터넷 연결 상태가 안좋거나, 랜선 자체에 Block 기능이 활성화 되어 있을 경우 완전히 다운로드 되지 않습니다.

2. ROS 초기화 명령어 입니다. **처음 설치시**에만 사용됩니다.

- ROS 의존성 파일 설치 코드입니다.

  `sudo apt-get install python-rosdep`

  `sudo rosdep init`

  `sudo rosdep update`

1. **로봇의 역기구학 계산 및 제어**를 위한 **Moveit 패키지 및 필요 파일 설치**입니다 .

   `sudo apt-get install ros-melodic-moveit`

   `sudo apt-get install ros-melodic-industrial-core`

   `sudo apt-get install ros-melodic-joint-state-publisher`

   `sudo apt-get install ros-melodic-trac-ik`

   `sudo apt-get install ros-melodic-moveit-visual-tools`

2. 시뮬레이션을 위한 **Gazebo 설치** 입니다.

   `sudo apt-get install ros-melodic-effort-controllers`

   `sudo apt-get install ros-melodic-joint-trajectory-controller`

3. **터미널(cmd)이 실행될 때**마다 bashrc에 **ROS관련 환경구성을 추가**해 ROS를 실행 할 때 마다 **자동적으로 환경구성을 로드**해 진행을 수월하게 합니다. 이 명령어는 한번만 해주면 됩니다.

   `echo "source /opt/ros/melodic/setup.bash" >> ~/.bashrc`

   `source ~/.bashrc`

4. **ROS 파일 공간 (workspace)** 만들기

   앞으로 사용하면서 추가 또는 설치할 로봇 기본 소스 코드를 저장할 공간(workspace)을 만듭니다.

- 작업 디렉토리 생성 `mkdir -p ~/catkin_ws/src`

  

##### 프로젝트 source 파일 설치

1. 링크로 들어가 src 안에 있는 파일들을 다운로드 받습니다.

   [Download files in src](https://github.com/chaochao77/ROS_neuromeka_tutorial/blob/main/software/src)

   - indy-ros.zip:
   - Neuromeka INDY-10 관련 ros 소스파일들 입니다.
   - pointgrey_camera_driver.zip
   - 이번 프로젝트에서 사용된 카메라의 ros 소스파일입니다.
   - track-ik.zip:
   - 로봇의 역기구학을 계산해주는 플러그-인인데, 기존의 Rviz의 Move-it이 사용하는 플러그인보다 더 빠르고 정확합니다.

2. 다운로드 받은 파일을 압축 해제 후 Home의 catkin_ws의 src 폴더에 넣습니다. 폴더명을 아래 그림과 같이 지정한 후 압축해제 파일들을 넣습니다.

[![스크린샷, 2022-04-13 12-05-58](https://user-images.githubusercontent.com/79825525/163092084-657b5fcd-6452-4983-9330-721b6be992b0.png)](https://user-images.githubusercontent.com/79825525/163092084-657b5fcd-6452-4983-9330-721b6be992b0.png)

1. 이제 터미널 (cmd) 창을 열어 앞서 사용해본 catkin_make 명령어로 파일들을 빌드 합니다.

   `cd ~/catkin_ws/`

   `catkin_make`

   만들어진 공간을 cd 명령어를 통해 간 후, catkin_make 명령어를 통해 src에 있는 모든 파일에 대한 빌드파일을 만듭니다.

   src 내부의 로봇에 관련된 **C++코드**들은 바꿀 때마다 **catkin_make로 빌드**해줘야지 바뀐 내용들이 저장됩니다.

2. (초기 설정시 1회 수행) ROS 환경구성한 것처럼 터미널에서 실행할 때 마다 자동적으로 catkin_ws에 빌드된 파일들이 불러와지도록 해주는 명령어입니다. 이 명령어 또한 한번만 해주면 .bashrc 파일을 삭제 하지 않는 이상 계속 저장되어 있습니다.

   `echo "source ~/catkin_ws/devel/setup.bash" >> ~/.bashrc`

   `source ~/.bashrc`

   `sudo chown -R $USER ~/.ros`

3. 빌드가 무사히 완료되었다면 아래의 코드들로 테스트 해봅니다

   - Rviz 실행: Indy10 로봇 시각화

     `roslaunch indy10_moveit_config demo.launch`

   [![img](https://github.com/chaochao77/ROS_neuromeka_tutorial/raw/main/image/20.jpg)](https://github.com/chaochao77/ROS_neuromeka_tutorial/raw/main/image/20.jpg)

   - Gazebo 실행: Indy10 로봇 모션 시뮬레이션
   - 별도의 cmd창을 실행 후 아래의 명령어 입력 `roslaunch indy10_gazebo indy10_moveit_gazebo.launch`

   [![img](https://github.com/chaochao77/ROS_neuromeka_tutorial/raw/main/image/21.jpg)](https://github.com/chaochao77/ROS_neuromeka_tutorial/raw/main/image/21.jpg)

   - Rviz에서 Display>Motionplanning 박스를 체크합니다. 그러면 로봇의 엔드툴 기준으로 움직일 수 있는 간단한 원형 가이드 바가 보입니다

   [![img](https://github.com/chaochao77/ROS_neuromeka_tutorial/raw/main/image/22.jpg)](https://github.com/chaochao77/ROS_neuromeka_tutorial/raw/main/image/22.jpg)

   [![img](https://github.com/chaochao77/ROS_neuromeka_tutorial/raw/main/image/24.jpg)](https://github.com/chaochao77/ROS_neuromeka_tutorial/raw/main/image/24.jpg)

   - 원하는 Manipulator 포즈를 마우스로 원형 바를 조정

- MotionPlanning>Planning> Commands: `Plan & excute` 클릭

- Rviz와 Gazebo에서 로봇 매니퓰레이터 둘 다 움직이는 것을 확인 할 수 있습니다.

  [![img](https://github.com/chaochao77/ROS_neuromeka_tutorial/raw/main/image/25.jpg)](https://github.com/chaochao77/ROS_neuromeka_tutorial/raw/main/image/25.jpg)

  [![img](https://github.com/chaochao77/ROS_neuromeka_tutorial/raw/main/image/26.jpg)](https://github.com/chaochao77/ROS_neuromeka_tutorial/raw/main/image/26.jpg)

4. 종료하시고 싶으시다면 명령을 실행한 터미널로 가서 `ctrl+c` 를 누르면 `roslaunch`나 `rosrun`한 파일들이 종료됩니다.

##### 