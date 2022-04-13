# ubuntu installation

https://yerinpy73.tistory.com/5

# Manipulator (INDY-10) Simulation Environment

## Introduction

이 Repository는 한동대학교 2021년 2학기에 진행된 기전융합프로젝트, **스마트 팩토리의 분류 자동화를 위한 산업로봇 시뮬레이터 환경 구축** (Developing Simulation Environment of Industrial robot (Indy) for Defect Inspection) 에 대한 **설치 파일 및 튜토리얼**이 포함되어 있습니다.

스마트팩토리의 한 공정에 대한 **산업로봇의 제어 코드를 작성**하고, 작성된 코드를 **Gazebo에서 안정성 테스트**를 거친 후 실제 로봇에 적용하는 **시뮬레이션 환경을 구축**하는 것이 목적이었습니다. **시뮬레이션 테스트 및 실제 구현해본 공정은 자동 분류 공정**입니다.

매니퓰레이터 모델은 **INDY-10 (Neuromeka)**로 로봇 제어를 위한 **Linux - ROS**를 사용했으며, ROS의 **Rviz와 Gazebo** 프로그램으로 프로젝트를 진행했습니다.

**Rviz**는 **로봇의 상태를 시각화**해주거나, **움직임을 제어**하는데 도움을 주는 **Move-it** 등을 제공해주는 툴입니다.

**Gazebo**는 로봇의 물리 정보 및 외형 모델파일로 로봇을 **가상의 공간에 만들어 움직임 및 제어 등을 테스트** 할 수 있는 시뮬레이터입니다.

로봇뿐만 아니라, 사용한 **그리퍼 EGP-64** 및 **Point Grey 카메라**에 대한 연결 및 사용법 또한 Repository에 포함되어 있습니다.

**이 프로젝트는 한동대학교 김 영 근 교수님의 지도아래 진행되었습니다.**

## Requirements

ROS를 사용하기 위해 **Linux- ubuntu 18.04 버전**이 필요합니다.

또한 **WIFI 연결**이 가능한 노트북 or 데스크탑이여야 하며, 이 프로젝트에서 사용한 노트북의 사양은 CPU - Intel i5-1135G7, RAM - 16GB, Graphic card - MX450 입니다. 참고로 윈도우와 리눅스 듀얼 부팅 환경에서 프로젝트를 진행했는데 문제는 없었습니다.

**INDY-10 전용 태블릿**은 로봇 연결 및 상태 확인과 간단한 제어에 유용함으로 실험할 때 같이 사용하시면 좋습니다.

ROS에서 사용된 코드들은 대부분 **C++**로 작성되었음으로, C++을 잘 다룰수록 수월해집니다.

ROS는 Linux에서 **Python 2 버전**으로 작동됩니다. Linux의 기본 프로그램이 Python 3버전일 경우 작동되지 않습니다.

## Tutorial - Manipulator INDY-10

##### 로봇 연결

1. 컨트롤박스를 콘센트에 연결한뒤, 전원 버튼을 누릅니다. 2~5분이면 로봇이 완전히 작동하게 됩니다.
2. 컨트롤 박스 뒷면에 **랜선을 공유기에 연결**합니다. (**컴퓨터와 같은 wifi로 연결**되어야지만 ROS 코드를 사용한 제어가 가능합니다.)
3. 태블릿을 컨트롤 박스 뒷면 USB포트로 연결합니다.
4. 태블릿의 **Conty 앱**에 들어가 **USB연결**을 눌러 로봇이 잘 연결되는지 확인합니다.

4-1. 만약 연결이 되지 않을 경우 **Emergency 버튼**을 확인해보세요. 눌러져 Lock되어 있을 경우, **돌려서 빼면 됩니다. **

4-2. 우측 상단에 붉은 메세지가 떠있을 경우, 우측 상단에 있는 **리셋을 눌러 초기화**하면 됩니다.

 [![img](https://github.com/chaochao77/ROS_neuromeka_tutorial/raw/main/image/11.jpg)](https://github.com/chaochao77/ROS_neuromeka_tutorial/blob/main/image/11.jpg)

1. 로봇의 IP를 확인하기 위해 환경설정, **애플리케이션 정보**를 들어가 **IP**를 확인합니다. (**ROS로 로봇과 연결 시 **IP를 알아야합니다.)

   [![img](https://github.com/chaochao77/ROS_neuromeka_tutorial/raw/main/image/12.jpg)](https://github.com/chaochao77/ROS_neuromeka_tutorial/blob/main/image/12.jpg)[![img](https://github.com/chaochao77/ROS_neuromeka_tutorial/raw/main/image/13.jpg)](https://github.com/chaochao77/ROS_neuromeka_tutorial/blob/main/image/13.jpg)

2. 이제 USB 연결을 해제하고 **확인한 IP로 WIFI모드로 연결**합니다. (*이때 태블릿 또한 같은 공유기 WIFI로 연결되어 있어야합니다)

3. 로봇이 작동이 잘되는지 간단히 테스트 하고싶으시다면 아래와 같이 **프로그램 > 새로만들기 > 시간기준 > 조인트이동 편집 > 직접 교시**로 들어가 직접 손으로 로봇 조인트들을 움직일 수 있습니다.

   [![img](https://github.com/chaochao77/ROS_neuromeka_tutorial/raw/main/image/17.jpg)](https://github.com/chaochao77/ROS_neuromeka_tutorial/blob/main/image/17.jpg)[![img](https://github.com/chaochao77/ROS_neuromeka_tutorial/raw/main/image/14.jpg)](https://github.com/chaochao77/ROS_neuromeka_tutorial/blob/main/image/14.jpg)

   [![img](https://github.com/chaochao77/ROS_neuromeka_tutorial/raw/main/image/15.jpg)](https://github.com/chaochao77/ROS_neuromeka_tutorial/blob/main/image/15.jpg)[![img](https://github.com/chaochao77/ROS_neuromeka_tutorial/raw/main/image/19.jpg)](https://github.com/chaochao77/ROS_neuromeka_tutorial/blob/main/image/19.jpg)

   ![img](https://github.com/chaochao77/ROS_neuromeka_tutorial/raw/main/image/16.jpg)

   또한 이동 > 홈 위치 or 영위치를 누르는 것으로 조인트 별로 이상이 없는지 간단히 체크 할 수 있습니다.

실험 도중 로봇이 멈추거나, 오류가 생길 경우 **태블릿의 Reset 버튼**을 누르면 로봇 상태가 초기화 되며 오류가 고쳐집니다.

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

  만들어진 공간을 cd 명령어를 통해 간 후, catkin_make 명령어를 통해 src에 있는 모든 파일에 대한 빌드파일을 만듭니다.

  아래의 코드들은 추후 실험을 진행하면서 src 내부의 로봇에 관련된 **C++코드**들은 바꿀 때마다 **catkin_make로 빌드**해줘야지 바뀐 내용들이 저장이 됨으로 **자주 사용**하게 될 것입니다.

  `cd ~/catkin_ws/`

  `catkin_make`

1. ROS 환경구성한 것처럼 터미널에서 실행할 때 마다 자동적으로 catkin_ws에 빌드된 파일들이 불러와지도록 해주는 명령어입니다. 이 명령어 또한 한번만 해주면 .bashrc 파일을 삭제 하지 않는 이상 계속 저장되어 있습니다.

   `echo "source ~/catkin_ws/devel/setup.bash" >> ~/.bashrc`

   `source ~/.bashrc`

   `sudo chown -R $USER ~/.ros`

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

   ![img](https://github.com/chaochao77/ROS_neuromeka_tutorial/raw/main/image/20.jpg)

   - Gazebo 실행: Indy10 로봇 모션 시뮬레이션

   - 별도의 cmd창을 실행 후 아래의 명령어 입력 `roslaunch indy10_gazebo indy10_moveit_gazebo.launch`

   ![img](https://github.com/chaochao77/ROS_neuromeka_tutorial/raw/main/image/21.jpg)

   - Rviz에서 Display>Motionplanning 박스를 체크합니다. 그러면 로봇의 엔드툴 기준으로 움직일 수 있는 간단한 원형 가이드 바가 보입니다

   ![img](https://github.com/chaochao77/ROS_neuromeka_tutorial/raw/main/image/22.jpg)

    

   ![img](https://github.com/chaochao77/ROS_neuromeka_tutorial/raw/main/image/24.jpg)

   - 원하는 Manipulator 포즈를 마우스로 원형 바를 조정

- MotionPlanning>Planning> Commands: `Plan & excute` 클릭

- Rviz와 Gazebo에서 로봇 매니퓰레이터 둘 다 움직이는 것을 확인 할 수 있습니다.

  ![img](https://github.com/chaochao77/ROS_neuromeka_tutorial/raw/main/image/25.jpg)

   

  ![img](https://github.com/chaochao77/ROS_neuromeka_tutorial/raw/main/image/26.jpg)

1. 종료하시고 싶으시다면 명령을 실행한 터미널로 가서 `ctrl+c` 를 누르면 `roslaunch`나 `rosrun`한 파일들이 종료됩니다.

##### 실제 로봇 연결

1. INDY-10을 작동시키고, **컨트롤박스에 연결된 공유기와 동일한 WIFI로 컴퓨터와 연결**합니다.

2. 태블릿으로 확인한 로봇의 IP로 터미널 창에서 아래의 명령어의 xxx부분에 **IP주소를 추가하여 실행**합니다.

   `roslaunch indy10_moveit_config moveit_planning_execution.launch robot_ip:=xxx.xxx.xxx.xxx`

3. 태블릿으로 로봇을 조작하여 움직이면 Rviz에서도 실시간으로 로봇이 움직이는 것을 확인 할 수 있습니다.

4. 종료하시고 싶으시다면 명령을 실행한 터미널로 가서 `ctrl+c` 를 눌러 실행한 `roslaunch`가 종료되면서 Rviz가 꺼지고 로봇과의 연결이 끊깁니다.

## Hardware - Gripper

##### EGP-C-64 (SCHUNK)

[![img](https://github.com/chaochao77/ROS_neuromeka_tutorial/raw/main/image/140.jpg)](https://github.com/chaochao77/ROS_neuromeka_tutorial/blob/main/image/140.jpg)

###### Specification

- 20mm의 스트로크
- 230N의 힘 (50%, 100% 조절 가능)
- **24V 전력공급** 필요
- **Open, close 두개의 입력선**으로 그리퍼 **열고, 닫기 제어**
- LED light, 스트로크 위치 감지 센서 등 출력 센서

###### 연결 - 플랜지, 그리퍼

그리퍼를 로봇에 장착 할 때, 로봇의 엔드툴과 그리퍼의 장착부를 호환시켜주는 부품을 플랜지라 합니다. 아래의 이미지 예시처럼 플랜지를 먼저 장착한 뒤, 그리퍼를 장착하면 됩니다.

[![img](https://github.com/chaochao77/ROS_neuromeka_tutorial/raw/main/image/150.jpg)](https://github.com/chaochao77/ROS_neuromeka_tutorial/blob/main/image/150.jpg)

1. 플랜지를 M4나사 6개와 로봇의 엔드툴 부분과 연결합니다.
2. 그 후 위치에 맞게 그리퍼를 끼운 후, M4 육각렌치로 4개의 나사를 돌려 장착합니다.

###### 연결 - 컨트롤 박스

1. 컨트롤 박스 후면을 보면 아래의 이미지와 같이 Digital I/O, Analog I/O가 있습니다.

   [![img](https://github.com/chaochao77/ROS_neuromeka_tutorial/raw/main/image/112.jpg)](https://github.com/chaochao77/ROS_neuromeka_tutorial/blob/main/image/112.jpg)[![img](https://github.com/chaochao77/ROS_neuromeka_tutorial/raw/main/image/111.jpg)](https://github.com/chaochao77/ROS_neuromeka_tutorial/blob/main/image/111.jpg)

   ![img](https://github.com/chaochao77/ROS_neuromeka_tutorial/raw/main/image/114.jpg)

   전선을 포트에 넣어 연결하려면은 **일자 드라이버 작은게 **필요합니다. 각 번호의 포트 **구멍 옆의 주황색 부분**을 일자 드라이버로 꾸욱 누르면 포트 구멍이 열려 쉽게 넣고 뺄 수 있습니다. **하지만 너무 깊게 넣을 시 빼기 힘들 수 있으니 잘 잡힐 정도로만 넣으면 됩니다.** 

2. 컨트롤 박스의 I/O보드들에 전력을 공급하기 위해 위의 오른쪽 이미지 처럼 **1-10포트의 9,10번째를 서로 연결**하고, **11-20포트의 9,10번째를 서로 연결**합니다

   - 1-10 의 9,10번째 포트는 **GND**, 1-20의 9,10번째 포트는 **24[V] VCC**로 **컨트롤 박스 내부에서 자체적으로 I/O보드에 24[V]전력이 공급**되게 해줍니다.

3. 이제 그리퍼 EGP-C-64에 전력 공급을 위해 **41-50의 10번 포트에 Vcc(빨강, 파랑 패턴선), 9번에 GND(회색 갈색 패턴선)을 연결**합니다.

4. 그리퍼의 **Close(파랑선)을 41-50의 2번 포트에, Open(빨강)을 1번에 연결**합니다. 아래의 이미지처럼 연결되었다면 그리퍼를 사용할 준비가 완료 된겁니다.

   ![img](https://github.com/chaochao77/ROS_neuromeka_tutorial/raw/main/image/113.jpg)

###### 제어 - 태블릿

1. Conty 앱을 실행하여 로봇과 연결합니다.

2. 로봇 설정에 들어가면 아래의 이미지 처럼 화면에 바로 6개의 조인트 및 **Smart DI/O** 들이 보입니다.

   ![img](https://github.com/chaochao77/ROS_neuromeka_tutorial/raw/main/image/141.jpg)

3. Smart D I/O에서 **8 번과 9번**의 출력에 따라 그리퍼와 연결된 **Close(blue), Open(red) 선에 0,1의 디지털 값**이 입력됩니다.

4. 태블릿에서 **8번을 눌러 On (초록색) , 9번을 off(회색)**을 하면 그리퍼 **열기**, 반대로 **8번을 다시 눌러 off, 9번을 눌러 on**하면 그리퍼 **닫기** 작용을 하게 됩니다.

5. EGP-C-64의 경우 **Open과 Close가 { 1 ,0 } 또는 {0 , 1} 으로 입력**이 되어야 지만 열고 닫는 작용을 하게 됩니다.

###### 제어 - ROS(INDY-10)

indy6d_driver.cpp은 **ROS에서 연결된 로봇의 컨트롤 박스로 명령어를 주거나, 데이터를 받게 해주는 cpp 코드파일** 입니다. 이 곳에서 컨트롤 박스 후면 디지털 포트들(Smart DI/O)에 **입력을 받거나, 출력을 주는 명령어를 보내 그리퍼를 작동** 할 수 있습니다.

[indy6d_driver.cpp](https://github.com/chaochao77/ROS_neuromeka_tutorial/blob/main/software/src/indy-ros/indy_driver/src/indy6d_driver.cpp)

위의 링크로 해당 코드파일을 보면, 태블릿에서 작동한 것과 같이 8번과 9번포트로 디지털 값 입출력을 **코드 명령어를 통해 직접 전달** 할 수 있습니다.

- 그리퍼 Open

  ```
  int idx;
  char val;
  Data gripdata;
  unsigned int len;
  idx = 9;                                        // 9번 포트 '0' 입력
  val = 0;
  memcpy(gripdata.byte, &idx, sizeof(int));
  memcpy(gripdata.byte+sizeof(int), &val, sizeof(char));
  indySocket.sendCommand(402,gripdata,5);
  indySocket.getFeedback(402, gripdata, len);
  idx = 8;										// 8번 포트 '1' 입력
  val = 1;
  memcpy(gripdata.byte, &idx, sizeof(int));
  memcpy(gripdata.byte+sizeof(int), &val, sizeof(char));
  indySocket.sendCommand(402,gripdata,5);
  indySocket.getFeedback(402, gripdata, len);
  ```

  - Data gripdata : [SocketDefine.h](https://github.com/chaochao77/ROS_neuromeka_tutorial/blob/main/software/src/indy-ros/indy_driver/src/SocketHandler/SocketDefine.h) 에 선언된 공용체 Data입니다. **unsigned char byte[SIZE_DATA_MAX] **에 포트 인덱스 (idx - 4byte )와 값(val - 1byte)을 넣어 sendCommand [ 402번 - SmartDI/O 입력 하나쓰기 ] 를 통해 원하는 포트에 1또는 0을 입력 할 수 있습니다.
  - idx : 포트 번호 , int 타입
  - val : 포트에 넣을 값 (0 또는 1) , char 타입
  - memcpy : 포트 입출력을 위한 명령어는 unsigned **char byte[]**에 입력된 값으로만 작동됩니다. 따라서 포트 번호 idx 와 val값이 char byte의 메모리로 넣어지려면 **memcpy를 통해 idx와 val 값이 각각 복사**되어 들어가게 됩니다.
  - indySocket.sendCommand(402,gripdata,5) : 402는 디지털 입력 하나쓰기 명령어 번호, gripdata는 넣고자 하는 공용체 Data 값 , 5는 명령어를 처리에 필요한 데이터크기 5byte 입니다.

- 그리퍼 Close

  ```
  int idx;
  char val;
  Data gripdata;
  unsigned int len;
  idx = 8;										// 8번포트 '0' 입력
  val = 0;
  memcpy(gripdata.byte, &idx, sizeof(int));
  memcpy(gripdata.byte+sizeof(int), &val, sizeof(char));
  indySocket.sendCommand(402,gripdata,5);
  indySocket.getFeedback(402, gripdata, len);
  idx = 9;										// 9번포트 '1' 입력
  val = 1;
  memcpy(gripdata.byte, &idx, sizeof(int));
  memcpy(gripdata.byte+sizeof(int), &val, sizeof(char));
  indySocket.sendCommand(402,gripdata,5);
  indySocket.getFeedback(402, gripdata, len);
  ```

  - Open과 반대로 8번 인덱스에 0 값을, 9번 인덱스에 1값을 넣으면 작동 됩니다.

위와 같이 작성 완료 후, ROS에서 실제 로봇을 작동하는 파일을 roslaunch로 실행하게 되면 해당 명령을 처리 할때 그리퍼가 작동하게 됩니다.

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

   인식이 되지 않으면 ubuntu를

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

## 자동 분류 공정 (Pick & Place in this project)

이 프로젝트에서 구성한 자동 분류 공정에 대한 ROS 코드는 아래의 순서에 따라 작동하게 됩니다.

[![img](https://github.com/chaochao77/ROS_neuromeka_tutorial/raw/main/image/40.jpg)](https://github.com/chaochao77/ROS_neuromeka_tutorial/blob/main/image/40.jpg)

##### 하드웨어 세팅

[![img](https://github.com/chaochao77/ROS_neuromeka_tutorial/raw/main/image/30.jpg)](https://github.com/chaochao77/ROS_neuromeka_tutorial/blob/main/image/30.jpg)[![img](https://github.com/chaochao77/ROS_neuromeka_tutorial/raw/main/image/31.jpg)](https://github.com/chaochao77/ROS_neuromeka_tutorial/blob/main/image/31.jpg)

위의 왼쪽 이미지처럼 로봇과 카메라, 작업 테이블을 간단히 세팅하여 실험을 진행했습니다. 잡을 물체는 왼쪽 이미지처럼 기어와 다른 모양들의 물체들로 구성했습니다.

하드웨어 세팅에서 가장 중요한 부분은 물체가 놓이는 **평면의 높이**, 로봇이 **물체를 잡을 위치에 대한 카메라의 픽셀당 좌표 값계산**, 그리고 가장 중요한 **로봇의 영점좌표와 카메라의 영점좌표 조정**입니다. 아래의 예시 이미지들은 이번 프로젝트에서 사용한 세팅 구도입니다.

[![img](https://github.com/chaochao77/ROS_neuromeka_tutorial/raw/main/image/35.jpg)](https://github.com/chaochao77/ROS_neuromeka_tutorial/blob/main/image/35.jpg)

예를 들어 위의 이미지 처럼 로봇의 영점좌표(**엔드툴 좌표가 아닌 로봇의 0번 조인트의 중심 좌표**)에서 카메라의 ROI영역의 영점좌표가 다를 경우, **서로의 X축 사이거리 Dy와 y축 사이거리 Dx를 이동 좌표에 더하거나 빼주고, 축 방향이 서로 반대 일 경우에는 좌표를 반전시키는 등, 로봇의 영점좌표 기준으로 좌표 계산**을 해야합니다. **ROS의 길이 표준 값은 미터(m) 기준 입니다. 예를 들어 Dx가 10cm미터라하면 0.1만큼을 계산식에 넣어야 합니다.**

예를 들어 이번 프로젝트에서 사용한 [video.cpp](https://github.com/chaochao77/ROS_neuromeka_tutorial/blob/main/software/src/indy-ros/indy_driver/src/video.cpp) 에서 178번째와 179번째 줄을 보면 아래와 같이 물체 좌표 계산하였습니다.

```
        robot_X = -(camera_X-Dx);   // x축 방향이 반대
        robot_Y = (camera_Y+Dy);   
```

[![img](https://github.com/chaochao77/ROS_neuromeka_tutorial/raw/main/image/36.jpg)](https://github.com/chaochao77/ROS_neuromeka_tutorial/blob/main/image/36.jpg)

또한 물체가 한 평면 위에 있을 경우, 로봇의 영점좌표와 평면의 높이차이 H와, 그리퍼의 잡는 부분에서 엔드툴까지의 높이 G.H를 고려하여 로봇의 도달 좌표의 z 값을 계산해야 합니다.

이 프로젝트에서는 한 평면만을 사용했기에 로봇의 이동 높이는 고정이 되어있습니다. 그렇기에 실제 로봇에 물체 및 목표 좌표를 보내는 코드에서 z값이 고정적으로 들어가게 됩니다. [camera_process.cpp](https://github.com/chaochao77/ROS_neuromeka_tutorial/blob/main/software/src/indy-ros/indy_driver/src/camera_process.cpp)에서 52번째 줄이 고정된 계산 값인데 계산 식은 아래식을 따릅니다.

 `obz = H - G.H`

**H**는 물체가 놓이는 **평면(테이블)과 로봇의 영점좌표의 차이**, 그리고 **G.H는 그리퍼의 높이**입니다. 그리퍼의 높이를 빼는 이유는 Moveit의 경우 로봇이 좌표로 **이동 할 떄 기준은 로봇의 영점좌표**이고 **이동 객체의 중심은 로봇의 끝(엔드툴)**이기 때문입니다.

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

## Info

If you have a question about the code or setting the environment, contact to me via e-mail

[21500813@handong.edu](mailto:21500813@handong.edu)