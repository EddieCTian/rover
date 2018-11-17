# Rover Software
All the software for the rover. Started using ROS
ROS Kinetic

Package name: rover

Nodes:
Drive_server_node: drive_server
Drive_client_node: drive_client (Arduino code)
... (Add more nodes)


To clone this package:

1) Create a folder (name doesn't matter)
2) Create a src folder inside
3) git clone this repository into this src folder

To run this package:

1) Compile the package by running this command in the base folder (the folder you created):
  catkin_make
2) Run each nodes by typing in this command:
  rosrun rover "name of the node"
---
  
---To run Drive---

1) roscore 
2) Upload the Drive_receiver Arduino code on the Arduidno
3) Run the receiver node using this command (***using your port number): rosrun rosserial_python serial_node.py _port:=/dev/ttyACM# _baud:=57600
4) On the separate command window, use this command: rosrun rover drive_sender
5) Control the rover using the arrow keys

---
---To run SLAM---

1) roscore
2) on Jetson (Or any device with the stereo camera and RTABMAP setup): roslaunch rover traverse.launch
3) on the groundstation computer: rosrun rviz rviz

---
---To run ARM---
1) Install openrave. Follow instructions from https://scaron.info/teaching/installing-openrave-on-ubuntu-16.04.html
2) Go to arm control folder
3) Run script with ./filename.ext (If it's not an executable, ensure "#!/Use/bin/env python" is at the top of the file and type "chmod +x filename.ext" in the terminal)

Openrave is mainly used for visualization, whilst the main control is done in the script.
To make a visual model of the arm follow these steps:
4) Make an arm model in a urdf file format. Follow this tutorial to assist you: http://wiki.ros.org/urdf/Tutorials/Create%20your%20own%20urdf%20file
5) Convert a urdf file into a collada file. Follow this page for assistance with that: http://wiki.ros.org/collada_urdf
6) In the collada (*.dae) file, due to some bug, manually change the arm links parameters with the help of the file Arm_visualization_params_manual.odt
7) Make sure that the collada file name is the same as in environment.xml
8) Your visual model is set now, enjoy!

To run using ROS, steps (make sure you have the joystick connected beforehand):
1) Make sure that your computer is configured properly. The catkin package should be made. In  ~/.bashrc file make sure you export correct ROS_MASTER_URI and ROS_IP (Note: be careful when using ROS_IP together with ROS_HOSTNAME, as they are mostly mutually exclusive)
2) to run the Master, type "roscore" in the command line
3) to run the Arm Listener, which listenes for the angle values (usually run on the rover computer), type "rosrun rover arm_listener_ROS.py"
4) to run the control script (usually run on the ground station computer controlling the arm), in the root of the cloned from github "rover" folder type "rosrun rover arm_control_RSX_2018_ROS.py"

For using the arm camera, go through the camera manual. Its IP is 192.168.0.10 (make sure the network is 192.168.*.*)
---

