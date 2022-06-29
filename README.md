Project 4 - Elevator

Description

Our task in this project was to create an elevator that would reproduce the real one. It had to be limited to 700 kg (assuming "one man weighs 60 kg") and a queuing mechanism. The next goal was to run the elevator down to the ground floor after 5 seconds if not in use. The last task was to create an elevator interface that shows the mass of people inside, the direction of travel and the floor on which it is located. It was all supposed to be controlled by the user with the buttons shown on the screen. <br/>
This project was created using C++ and GDI+.

The problems we faced

We started out by creating a typical C++ file that supports WinAPI and GDI+.
The first task was to draw the startup screen. We scaled the window so that our entire elevator was visible, and we measured the floors so that there was room for walking passengers. We used double buffering to make smooth animations. Then we programmed a queue. 
After putting it all together, we got the following program.

![image](https://user-images.githubusercontent.com/106469243/176541068-8c6c825f-5a4b-4ec5-9106-fb528e1c2a60.png)

Buttons send information where passenger is waiting and where he want to go, just like in real situation. <br/>
Queue is made of the people waiting. Their starting point and destination point helps to set the positions in queue. <br/>
Elevator is moving based on the queue. <br/>
Mass is being added when passenger is in the elevator and removed when he reach his destination. <br/>
Floors are just "drawLined" in the window. <br/>
Passenger is a bitmap added to the code. <br/>
If queue is empty for 5 seconds, it will guide our elevator to the lowest level. <br/>
Max. mass possible is 700 kg (8 passengers 60kg each). <br/>
