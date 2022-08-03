#include <iostream>
#include <string>
#include <vector>
#include "Stack.h"
#include "randgen.h"

using namespace std;

struct stackNode {

	int x_coordinate;
	int y_coordinate;
	bool visited;
	bool has_pawn;
	bool available;
	stackNode* next;

	stackNode (){}

	stackNode(int x_coor,  int y_coor, bool visit, bool has_p, bool avail, stackNode* nextp){
		x_coordinate = x_coor;
		y_coordinate = y_coor;
		visited = visit;
		has_pawn = has_p;
		available = avail;
		next = nextp;
	}
};

void generate_board(vector<vector<stackNode> >& board){
	for(int i = 0; i < board.size(); i++) {

		for (int k = 0; k < board[0].size(); k++) {

			stackNode node = stackNode(k+1, board.size()-i, false, false, true, nullptr);
			board[i][k] = node;
		}
	}
}



bool checkX(vector<vector<stackNode>> board, int x_coor){
	int counter = 0;
	for(int i=0; i < board.size(); i++){
		if(board[i][x_coor - 1].has_pawn == true) {
			counter++;
		}
	}

	if (counter > 3) {
		return false;
	}

	return true;
}

bool checkY(vector<vector<stackNode>> board, int y_coor){
	int counter = 0;
	for(int i = 0; i < board[0].size(); i++){
		if(board[y_coor - 1][i].has_pawn == true ){
			counter++;
		}
	}
	
	if(counter > 3){
		return false;
	}
	
	return true;
}

bool checkDiag(vector<vector<stackNode>> board, int y_coor, int x_coor){
	int counter = 0;
	int size = board.size();
	int index_x = x_coor - 1;
	int index_y = y_coor - 1;

	while (index_y >= 0 && index_x >= 0 && index_y <= size - 1 && index_x <= size - 1) {
		if(board[index_y][index_x].has_pawn == true) {
			counter++;
		}
		index_y++;
		index_x--;
	}

	index_x = x_coor - 1;
	index_y = y_coor - 1;

	while(index_y >= 0 && index_x >= 0 && index_y <= size - 1 && index_x <= size - 1) {
		if(board[index_y][index_x].has_pawn == true){
			counter++;
		}
		index_x++;
		index_y--;
	}

	index_x = x_coor - 1;
	index_y = y_coor - 1;

	if(board[index_y][index_x].has_pawn == true){
		counter--; // substracting since this location is looked twice
	}

	if(counter > 3){
		return false;
	}

	return true;

}


bool max3_checker(vector<vector<stackNode> > board ,int x_coor, int y_coor) { 

	if(checkX(board, x_coor) && checkY(board, y_coor) && checkDiag(board, y_coor, x_coor)){
		return true;
	}
	return false;
}

void pawn_empty_finder(vector<stackNode> &empties, int curr_x, int curr_y, vector<vector<stackNode> > board) { // check if the near locations are empty and restricted
	int size = board.size();
	if(curr_y-1 >= 0 && board[curr_y-1][curr_x].has_pawn == false) { // top

		
		int x_coor = curr_x + 1;
		int y_coor = size - curr_y; 
		y_coor = y_coor + 1;

		if(max3_checker(board, x_coor,y_coor)){
			stackNode s;
			s.x_coordinate = x_coor;
			s.y_coordinate = y_coor;

			empties.push_back(s);

		}

	
	}

	if(curr_y - 1 >= 0 && curr_x + 1 < size && board[curr_y-1][curr_x+1].has_pawn == false) { // top right diag
		
		int x_coor = curr_x + 1; // values are now coordinates 
		int y_coor = size - curr_y;
		x_coor = x_coor + 1;
		y_coor = y_coor + 1;

		if(max3_checker(board, x_coor,y_coor)) {
			stackNode s;
			s.x_coordinate = x_coor;
			s.y_coordinate = y_coor;
			empties.push_back(s);
		}



		

	}

	if(curr_x + 1 < size && board[curr_y][curr_x + 1].has_pawn == false) { // right
		
		int x_coor = curr_x + 1;
		int y_coor = size - curr_y; 
		x_coor = x_coor + 1;

		if(max3_checker(board, x_coor,y_coor)){
			stackNode s;
			s.x_coordinate = x_coor;
			s.y_coordinate = y_coor;

			empties.push_back(s);
		}



	}

	if(curr_y + 1 < size && curr_x + 1 < size && board[curr_y + 1][curr_x + 1].has_pawn == false) { // bottom right diag
		
		int x_coor = curr_x + 1;
		int y_coor = size - curr_y; 
		x_coor = x_coor + 1;
		y_coor = y_coor - 1;

		if(max3_checker(board, x_coor,y_coor)){
			stackNode s;
			s.x_coordinate = x_coor;
			s.y_coordinate = y_coor;

			empties.push_back(s);
		}


	}

	if(curr_y + 1 < size && board[curr_y + 1][curr_x].has_pawn == false) { // bottom
		
		int x_coor = curr_x + 1;
		int y_coor = size - curr_y; 
		y_coor = y_coor - 1;

		if(max3_checker(board, x_coor,y_coor)){
			stackNode s;
			s.x_coordinate = x_coor;
			s.y_coordinate = y_coor;

			empties.push_back(s);
		}

	
	
	}

	if(curr_y + 1 < size && curr_x - 1 >= 0 && board[curr_y + 1][curr_x - 1].has_pawn == false) { // bottom left diag
		
		int x_coor = curr_x + 1;
		int y_coor = size - curr_y; 
		x_coor = x_coor -1;
		y_coor = y_coor -1;

		if(max3_checker(board, x_coor,y_coor)){
			stackNode s;
			s.x_coordinate = x_coor;
			s.y_coordinate = y_coor;

			empties.push_back(s);
		}


	}

	if(curr_x - 1 >= 0 && board[curr_y][curr_x - 1].has_pawn == false) { // left
		
		int x_coor = curr_x + 1;
		int y_coor = size - curr_y; 
		x_coor = x_coor - 1;

		if(max3_checker(board, x_coor,y_coor)) {
			stackNode s;
			s.x_coordinate = x_coor;
			s.y_coordinate = y_coor;

			empties.push_back(s);		
		}


	}

	if(curr_y - 1 >= 0 && curr_x - 1 >= 0 && board[curr_y - 1][curr_x - 1].has_pawn == false) { // top left diag
		
		int x_coor = curr_x + 1;
		int y_coor = size - curr_y; 
		x_coor = x_coor -1;
		y_coor = y_coor +1;

		if(max3_checker(board, x_coor,y_coor)){
			stackNode s;
			s.x_coordinate = x_coor;
			s.y_coordinate = y_coor;

			empties.push_back(s);
		
		}


	}

	

}

void pawnPlacer(vector<vector<stackNode> > & board, int pawn_num) {
	int size = board.size();
	int counter = 1;
	
	int empty_num, curr_x = 0, curr_y = size-1;

	Stack<stackNode> pawn_stack;

	pawn_stack.push(board[curr_x][curr_y]);
	board[curr_y][curr_x].has_pawn = true;

	pawn_stack.push(board[curr_y][curr_x]);

	while(counter < pawn_num){

		vector<stackNode> empties; 
		pawn_empty_finder(empties, curr_x, curr_y, board);

		
		RandGen r;

		int random_index = r.RandInt(0 , empties.size() - 1);

		stackNode possible = empties[random_index];

		int x_coor = possible.x_coordinate;
		int y_coor = possible.y_coordinate;

		curr_x = x_coor -1;
		curr_y = size - y_coor;

		stackNode pawnLoc = board[curr_y][curr_x];
		pawnLoc.has_pawn = true;

		pawn_stack.push(pawnLoc);

		counter++;

		cout << empties.size() << endl;
	
	}
	

	


	



}


int main(){

	
	int board_size, pawn_num;

	cout <<	"Please enter the size of the board (n): ";
	cin >> board_size;

	while(11 <= board_size || board_size <= 4) {
		cout << "Board size should be in the range 4 < n < 11" << endl;
		cout << "Please enter the size of the board again (n): ";
		cin >> board_size;
	}

	vector<vector<stackNode> > board(board_size, vector<stackNode>(board_size));
	generate_board(board);

	cout << "Please enter the number of pawns (p): ";
	cin >> pawn_num;

	while (pawn_num > 3 * board_size) {
		cout << "Number of pawns are limited by 3n " << endl;
		cout << "Please enter the number of pawns again (p): ";
		cin >> pawn_num;
	}

	

	pawnPlacer(board, pawn_num);


	
	return 0;
}