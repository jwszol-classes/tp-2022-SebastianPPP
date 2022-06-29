Project 4 - Elevator

Description

Our task in this project was to create an elevator that would reproduce the real one. It had to be limited to 700 kg (assuming "one man weighs 60 kg") and a queuing mechanism. The next goal was to run the elevator down to the ground floor after 5 seconds if not in use. The last task was to create an elevator interface that shows the mass of people inside, the direction of travel and the floor on which it is located. It was all supposed to be controlled by the user with the buttons shown on the screen. 
This project was created using C++ and GDI+.

The problems we faced

We started out by creating a typical C++ file that supports WinAPI and GDI+.
The first task was to draw the startup screen. We scaled the window so that our entire elevator was visible, and we measured the floors so that there was room for walking passengers. We used double buffering to make smooth animations. Then we programmed a queue. 
After putting it all together, we got the following program.

//zdjęcie wyglądu gui