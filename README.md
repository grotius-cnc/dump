
# Motion
  
*Controlling motion*

By Skynet Cyberdyne & ChatGdpAI, the year is : 2023.

The Simple Motion Planner program calculates motion for periods 
t1, t2, and t3 using acceleration, steady, and deceleration periods. 
The program takes input values for :

	Initial velocity "vo"
	Final velocity "ve"
	Maximum velocity "vm"
	Acceleration "a"
	Displacment "s", 
	
And uses these inputs to calculate the values of periods t1, t2, and t3.

The program can produce a combination of t1, t2, and t3 periods based 
on the input values. For example, if the distance traveled is 
enough to reach the maximum velocity and decelerate to the final velocity, 
the program will calculate all three periods (t1, t2, and t3) 
and display them in the OpenGL graph.
On the other hand, if the distance traveled is not enough to reach 
the maximum velocity, the program will only produce the periods needed.

The program provides an easy to use and flexible solution for 
motion planning, and allows the user to visualize the motion 
planning based on the inputs given."

This text explains how the program calculates motion 
for periods t1, t2, and t3 and how the program can produce 
a combination of t1, t2, and t3 periods based on the input values. 
It also mentions that the program is easy to use and flexible, 
and allows the user to visualize the motion planning based on the inputs given.

Get started now and see how an object's motion can be easily planned and 
understood using Simple Motion Planner".

This smp (simple motion planner) library is header only.

There is also a live motion example included, where user can start and stop the motion,
given a displacment "s".

The progress of the motion is printed to terminal output.
During the motion cycle, the maximum velocity "vm" may be modified, The controller will
respect this new value.

During the motion cycle, the stop button may be pressed to stop (pause) the motion. 
Start may be pressed to resume motion to complete
the requested displacement "s".

This is a minimal example of how to perform live motion requests. 

Mention : During the live motion the controller stays in the first period, t1, every cycle.

Qt User interface :

![screen](https://github.com/grotius-cnc/motion_tryout/blob/main/screen.jpg)
        

To make the qt project, in project dir open terminal :
      
        mkdir build
        cd build
        cmake ..
        make










