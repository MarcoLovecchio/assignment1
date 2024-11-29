The nodes have been done in both programming languages, C++ for UI_node and Python for Distance_node.
I have developed the scripts as a game, so if you hit the wall or if the turtles are too close it's GAME OVER.
Turtle1 and Turtle2 are considered two different player; if one hit the wall, the second can keep playing.
The first node will spawn the turtle2 (position 2.0-2.0 and orientation 0.0 arbitrary selected) and will ask every second to the user which turtle to control and the velocity to implement (x and y linear velocity and z angular velocity).
The second node calculate the relative distance between the turtles and publish it on the topic /distance.
If the turtles are closer than a selected threshold (1.0), it's GAME OVER for both the players.
As already sed, if one of the turtles is too close to the wall (lower bound = 0.5 and upper bound = 10.5), it's GAME OVER for that player, but the other one can keep play until he also hit the wall or get too close to the other turtle.
GAME OVER messages will be displayed on the terminal.

In order to run the code you need to do the following steps:

- Open the terminal;
- Go inside the ros workspace folder (cd assignment1);
- Run the ros master (roscore);
- Open a new tab;
- Run the turtlesim node (rosrun turtlesim turtlesim_node);
- Open a new tab;
- Run the UI_node (rosrun assignment1_rt UI_node);
- Split the tab horizontally;
- Run the Distance_node (rosrun assignment1_rt Distance.py).
(Unfortunatly sometimes the Distance_node will publish GAME OVER message; in this case restart the node)

If you loose the game you need to restart the three nodes.
