In this project I have created a C++ program that is able to read a CFG(Control Flow Graph) from a file, and gives as output:

    - A set of paths, IC, from the initial to the final node of the CFG associated with the program taken as input
    
    - The coverage reached by IC calculated on the edges in terms of percentage
    
The algorithm implemented to construct the paths is based on the "random walk" concept, which is a formalization of the idea of carrying out successive steps/actions/and random directions.

At the beginning of the execution, the C ++ program will ask the user for the number of paths to be performed on the graph which will be called budget, and then it generates random paths. 

The algoritm terminates when the budget is exhausted.
