# Arduino-Fivebar-Robot
Code for a parallel robot with a fivebar configuration.

The python code in the pc folder runs a command line interface that takes in workspace coordinates of the robot. 
IK is then computed on the pc and the resulting joint space coordinates is sent via serial to arduino.

The ino file executes the joint space coordinates, and is also responsible for startup tasks such as homing. 
