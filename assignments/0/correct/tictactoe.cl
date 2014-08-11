(*
 * This program implements a simple 2-player tic tac toe game.
 *)
class TTTBoard {	--class to simulate Tic Tac Toe board using a string of length 9
	board:String;
	init():SELF_TYPE {{	--initializes the TTT board with all blanks
		board<-"         ";
		self;
	}};
	get(r:Int, c:Int):String {
		--checking if valid row and column number
		if r<0 then "-" else
		if 2<r then "-" else
		if c<0 then "-" else
		if 2<c then "-" else
		board.substr(r*3+c, 1)	--if no error in row and col number
		fi fi fi fi
	};
	set(r:Int, c:Int, s:String):String {	--returns '-' if invalid row or column, '+' if already occupied, the given symbol otherwise
		--checking if valid symbol
		if not s.length()=1 then "-" else
		--checking if valid row and column number
		if r<0 then "-" else
		if 2<r then "-" else
		if c<0 then "-" else
		if 2<c then "-" else
		--checking if not pre-occupied
		if not board.substr(r*3+c, 1)=" " then "+" else
		board<-board.substr(0, r*3+c).concat(s).concat(board.substr(r*3+c+1, 8-r*3-c))	--updating symbol
		fi fi fi fi fi fi
	};
	display(io:IO):Object {
		let i:Int<-0, j:Int, separator:String<-"||\n" in	--separator's last character is \n to print different rows in different lines
			while i<3 loop {
				j<-0;
				while j<3 loop {
					io.out_string(board.substr(i*3+j, 1).concat(separator.substr(j, 1)));
					j<-j+1;
				} pool;
				i<-i+1;
			} pool
	};
};
class Game {	--class to use a TTTBoard object and simulate a Tic Tac Toe
	io:IO<-new IO;
	board:TTTBoard<-new TTTBoard;
	playing:Bool<-true;
	turn:Int;	--turn=1 means player X moves first, -1 means player O moves first
	first_turn:Int<-1;
	current_player:String;	--to store the symbol of the current player
	player_symbol(code:Int):String {
		if code=1 then "X" else "O" fi
	};
	new_game():Object {{
		board.init();	--initialize the board
		turn<-first_turn;
		let current_game_finished:Bool<-false, moves_count:Int<-0, r:Int, c:Int, draw:Bool<-false in {
			while not current_game_finished loop {
				board.display(io);	--print the current board configuration
				current_player<-player_symbol(turn);	--get the symbol of the current player
				let valid_move:Bool<-false, move:String in	--valid_move is to check if the current move is valid, move is to store the result of the current move
					while not valid_move loop {
						io.out_string("Player ".concat(current_player).concat(" enter the row and column number for the move(1-3):\n"));
						r<-io.in_int()-1;	--subtract 1 to convert into string index (which begin at 0, thanks to the convention started by the great pioneers of computer science :P )
						c<-io.in_int()-1;	--same as above
						move<-board.set(r, c, current_player);	--make the move and get the result
						if move="-" then
							io.out_string("Invalid row or column number. ")
						else
							if move="+" then
								io.out_string("Already occupied. ")
							else
								valid_move<-true
							fi
						fi;
					} pool;
				moves_count<-moves_count+1;	--update count of moves
				current_game_finished<-check(r, c, current_player);	--call function to check if the current player has won
				if not current_game_finished then
					if moves_count=9 then	--if board is filled up
						current_game_finished<-(draw<-true)
					else 0 fi
				else 0 fi;
				turn<-turn*~1;	--swap turn
			} pool;
			board.display(io);
			--print reponse based on how the game ended
			io.out_string(if draw then "Game ended in a draw\n" else "Player ".concat(current_player).concat(" won the game.\n") fi);
		};
	}};
	check_row(r:Int, symbol:String):Bool {	--check if the given row has only 'symbol'
		if not board.get(r, 0)=symbol then false else
		if not board.get(r, 1)=symbol then false else
		if not board.get(r, 2)=symbol then false else
		true fi fi fi
	};
	check_column(c:Int, symbol:String):Bool {	--check if the given column has only 'symbol'
		if not board.get(0, c)=symbol then false else
		if not board.get(1, c)=symbol then false else
		if not board.get(2, c)=symbol then false else
		true fi fi fi
	};
	check_first_diagonal(symbol:String):Bool {	--check if the first diagonal has only 'symbol'
		if not board.get(0, 0)=symbol then false else
		if not board.get(1, 1)=symbol then false else
		if not board.get(2, 2)=symbol then false else
		true fi fi fi
	};
	check_second_diagonal(symbol:String):Bool {	--check if the second diagonal has only 'symbol'
		if not board.get(0, 2)=symbol then false else
		if not board.get(1, 1)=symbol then false else
		if not board.get(2, 0)=symbol then false else
		true fi fi fi
	};
	check(r:Int, c:Int, symbol:String):Bool {
		let win:Bool<-false, i:Int in {
			--checking current row
			win<-check_row(r, symbol);
			
			--checking current column
			if not win then win<-check_column(c, symbol) else 0 fi;
			
			--checking first diagonal, if applicable
			if not win then
				if r=c then win<-check_first_diagonal(symbol) else 0 fi
			else 0 fi;
			
			--checking second diagonal, if applicable
			if not win then
				if r+c=2 then win<-check_second_diagonal(symbol) else 0 fi
			else 0 fi;
			
			win;
		}
	};
	start():Object {
		while playing loop {
			new_game();
			io.out_string("Do you want to play another game? (y for yes, any other input to exit): ");
			playing<-(io.in_string())="y";	--play more if input is "y"
			first_turn<-first_turn*~1;	--swap first turn
		} pool
	};
};
class Main {
	game:Game<-new Game;
	main():Object {
		game.start()	--start the game
	};
};