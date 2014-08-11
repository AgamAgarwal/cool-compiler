/*
 * This program implements a simple 2-player tic tac toe game.
 */
#include<iostream>
using namespace std;
class TTTBoard {	//class to simulate Tic Tac Toe board using a string of length 9
	private:
	string board;
	public:
	void init() {	//initializes the TTT board with all blanks
		board="         ";
	}
	char get(int r, int c) {
		//checking if(valid row and column number
		if(r<0 || 2<r || c<0 || 2<c)
			return '-';
		return board[r*3+c];	//if(no error in row and col number
	}
	char set(int r, int c, char s) {	//returns '-' if(invalid row or column, '+' if(already occupied, the given symbol otherwise
		//checking if(valid row and column number
		if(r<0 || 2<r || c<0 || 2<c)
			return '-';
		//checking if(not pre-occupied
		if(board[r*3+c]!=' ')
			return '+';
		return board[r*3+c]=s;	//updating symbol
	}
	void display() {
		int i=0, j;
		char separator[3]={'|', '|', '\n'};	//separator's last character is \n to print different rows in different lines
		while(i<3) {
			j=0;
			while(j<3) {
				cout<<board[i*3+j]<<separator[j];
				j++;
			}
			i++;
		}
	}
};
class Game {	//class to use a TTTBoard object and simulate a Tic Tac Toe
	private:
	TTTBoard board;
	bool playing;
	int turn, first_turn;	//turn=1 means player X moves first, -1 means player O moves first
	char current_player;	//to store the symbol of the current player
	public:
	Game() {
		board=TTTBoard();
		playing=true;
		first_turn=1;
	}
	char player_symbol(int code) {
		return code==1?'X':'O';
	}
	void new_game() {
		board.init();	//initialize the board
		turn=first_turn;
		bool current_game_finished=false, draw=false;
		int moves_count=0, r, c;
		while(!current_game_finished) {
			board.display();	//print the current board configuration
			current_player=player_symbol(turn);	//get the symbol of the current player
			bool valid_move=false;	//to check if(the current move is valid
			char move;	//to store the result of the current move
			while(!valid_move) {
				cout<<"Player "<<current_player<<" enter the row and column number for the move(1-3):\n";
				cin>>r>>c;
				r--;	//subtract 1 to convert into string index (which begin at 0, thanks to the convention started by the great pioneers of computer science :P )
				c--;	//same as above
				move=board.set(r, c, current_player);	//make the move and get the result
				if(move=='-') 
					cout<<"Invalid row or column number. ";
				else if(move=='+') 
					cout<<"Already occupied. ";
				else
					valid_move=true;
			}
			moves_count++;	//update count of moves
			current_game_finished=check(r, c, current_player);	//call function to check if the current player has won
			if(!current_game_finished && moves_count==9) 	//if board is filled up
					current_game_finished=(draw=true);
			turn*=-1;	//swap turn
		}
		board.display();
		//print reponse based on how the game ended
		if(draw)
			cout<<"Game ended in a draw\n";
		else
			cout<<"Player "<<current_player<<" won the game.\n";
	}
	bool check_row(int r, char symbol) {	//check if the given row has only 'symbol'
		return board.get(r, 0)==symbol && board.get(r, 1)==symbol && board.get(r, 2)==symbol;
	}
	bool check_column(int c, char symbol) {	//check if the given column has only 'symbol'
		return board.get(0, c)==symbol && board.get(1, c)==symbol && board.get(2, c)==symbol;
	}
	bool check_first_diagonal(char symbol) {	//check if the first diagonal has only 'symbol'
		return board.get(0, 0)==symbol && board.get(1, 1)==symbol && board.get(2, 2)==symbol;
	}
	bool check_second_diagonal(char symbol) {	//check if the second diagonal has only 'symbol'
		return board.get(0, 2)==symbol && board.get(1, 1)==symbol && board.get(2, 0)==symbol;
	}
	bool check(int r, int c, char symbol) {
		return
			check_row(r, symbol)	//checking current row
			|| check_column(c, symbol) //checking current column
			|| (r==c && check_first_diagonal(symbol))	//checking first diagonal, if applicable
			|| (r+c==2 && check_second_diagonal(symbol));	//checking second diagonal, if applicable
	}
	void start() {
		while(playing) {
			new_game();
			cout<<"Do you want to play another game? (y for yes, any other input to exit): ";
			char choice;
			cin>>choice;
			playing=choice=='y';	//play more if input is "y"
			first_turn*=-1;	//swap first turn
		}
	}
};
int main() {
	Game game;
	game=Game();
	game.start();	//start the game
}