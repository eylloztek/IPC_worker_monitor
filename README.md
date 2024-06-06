# Worker Monitor with IPC

This project involves the implementation of a multi-threaded system in C programming language, focusing on worker programs (adder, subtractor, multiplier, and divider) and a worker monitor program. The worker programs continuously request two numbers from the user, perform the specified operation, and communicate the results to the worker monitor program through named pipes. The worker monitor displays the operations performed by the workers on its screen in a synchronized manner.

a) Adder Program (adder.c): Developed the adder program that continuously prompts the user for two integer inputs, performs addition, and communicates the result to the worker monitor through a named pipe (adder_pipe). The program uses a while loop to ensure continuous execution, and the result is sent in a formatted manner to the named 
pipe. 

b) Subtractor Program (subtractor.c): Similar to the adder program, implemented the subtractor program that requests two integer inputs from the user, performs subtraction, and communicates the result to the worker monitor through the named pipe (subtractor_pipe). 

c) Multiplier Program (multiplier.c): Implemented the multiplier program, which continuously prompts the user for two integer inputs, performs multiplication, and communicates the result to the worker monitor through the named pipe (multiplier_pipe). 

d) Divider Program (divider.c): Developed the divider program, which continuously requests two integer inputs from the user, performs division (with a check for division by zero), and communicates the result to the worker monitor through the named pipe (divider_pipe).