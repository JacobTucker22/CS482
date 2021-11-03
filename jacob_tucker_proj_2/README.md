CS482 Artificial Intelligence  
Project 1  
Jacob Tucker  
10/3/2021  

Task:  
Implement an AI for tic tac toe using minimax algorithm  

Compiling:  
From Proj_1/Code  
Make a build directory 

	mkdir build  
	
Move to that directory  

	cd build  
	
Copy test.board (or originalTest.board which was included in the example) to build  

	cp ../test.board ./test.board  
	
Run cmake and then make  

	cmake ..  
	make  
	
This will create the program tictactoe  

Running:  
Run this with two arguments, a source board file path and an out file path  
Use the same file path to update the same board, or a new one if you want to keep them separate  

	./tictactoe ./test.board ./test.board  
	
The program loads the source board, determines which player's turn it is, checks the board for playable game states, checks for any immediate winning moves, then runs the minimax to find the optimal move for that player.  
Once it determines the optimal move, it will make that move and save the board to the out file path.  
