# Solitario-C
Solitarie Windows console game using ANSI escape sequences for the "graphics" where you move the cards with command inputs, by entering the coordinates of the cards.

It is based on my final project for my 'Introduction to C' course at my college. The original project was written in a single 1K lines-of-code .c monolith and had an extra feature to log the moves inputted into a txt file. 

The original project did not require visual details, but I added them anyway. I also added user commands to make some card movements easier to perform.

## Controls
The board displays numbers and letters to represent stacks of cards and positions. As long as the movement is allowed, you can move a card from one stack to another by entering the letter of the origin stack, a hypen, and the letter of the destination stack. Ex.: "M-B" moves the card at the top of the M stack to the top of the B stack.

You can also move a card from the non-ordered stacks to the ordered stack (the foundations) by inputing the origin stack letter twice. Ex.: if the card at the top of the stack D can move onto any of the ordered stacks, then by entering "DD" will move the card to the proper foundation.

You can move a sub-stack of cards from one stack onto another as long as the movement is allowed and by entering the specific coordinate of the origin stack. Ex.: if a sub-stack starting at E3 you can move at the top of the stack G, then you can input "E3-G" to make that move.

You can flip the card from the stock by entering "M".

These commands are not case-sensitive, so it is equally valid entering "b2-c" as entering "B2-C".

## Other commands
You can enter "restart" to restart the game.

You can enter "exit" to exit the game.

## Screenshots
![Screenshot 2024-12-27 141458](https://github.com/user-attachments/assets/b5b9487f-43e9-4e79-915a-82136c12a90a)

Early version

![image](https://github.com/user-attachments/assets/7f0874e0-ae53-4341-8214-24fb163bddc8)

## Compilation
Developed on Dev-C++ 5.11 where you can compile it by pressing F9. Entry point is in `main.c`. It can be opened with the `solitario-c.dev` file.

![image](https://github.com/user-attachments/assets/d8e6fbd2-9da8-44b9-9e6b-43a7d6d49d49)

## Note
The card symbol may not be displayed properly on some systems.

## Misc
It took me around one week to complete this project; including properly learning pointers and dynamic memory, experimenting, designing, testing, fixing bugs and documenting. The null pointer dereference was by far the most common bug; so the lesson to learn while working with pointers is: **always** check if the pointer is null **before** dereferencing it.
