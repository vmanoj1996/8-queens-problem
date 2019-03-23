#ifndef N
#define N 9
#endif
// Solver for 8 queens problem c++ based.
// I am doing a recursive search of where to place queens row by row.
//If nothing is possible I would move the previously placed queen to next allowed column and proceed to the next row
#include<iostream>
#include<stack>
#include<iomanip>
#include<chrono>
#include<fstream>

#define success true
#define failed false
#define searchover true

using namespace std;
using namespace std::chrono;

bool chessBoard[N][N] = {0}; 			//current chess board
bool conflict[N][N]   = {0}; 			//1 means  conflict. 0 means no conflict
int workingRow        = 0;				//0 to N-1
stack<int> lastColumnPlaced; //holds the last location of sucessful queen placement. for each successful placement

int runSearch();
bool nextRow(bool repopul_flag = true);
void clearRow(int row,bool mat[N][N]);
void populateConflicts(int workingRow);
void disp(bool mat[N][N]);
void disp2();

int main(){
	ofstream file;
	file.open("log.txt", ios::app);
    	cout<<"\nChess board size "<<N<<endl<<endl;
	auto start=high_resolution_clock::now();
	runSearch();
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop-start);
	disp(chessBoard);
	cout<<endl;
	//disp(conflict);
	file<<endl<<N<<" "<<duration.count();
	file.close();
return 0;
}

void disp(bool mat[N][N]){
	cout<<"     ";
	for(int lin = 0; lin<N; lin++) cout<<setw(2)<<lin<<" ";
	cout<<endl;
	for(int i=0;i<3*N;i++)cout<<"-";
	cout<<endl;
	int lin = 0;
	for(int i=0;i<N;i++){
		cout<<setw(2)<<lin<<" | ";lin++;
		for(int j=0;j<N;j++){
			cout<<setw(2)<<mat[i][j]<<" ";
		}
		cout<<endl;
	}
}

void disp2(){
	for(int i=0;i<3*N;i++)cout<<"-";
	cout<<endl;
	int lin = 0;
	for(int i=0;i<N;i++){
		for(int j=0;j<N;j++){
			cout<<chessBoard[i][j]<<" ";
		}
		cout<<"\t";
		for(int j=0;j<N;j++){
			cout<<conflict[i][j]<<" ";
		}
		cout<<endl;
	}
}

int runSearch(){
// Based on goto statements
//Logic is simple
//We are going from top to bottom row.
//If we exceed N then the search is over. Incase it comes back to negative side then the code has failed
//Place first row element
//populate the conflicts for second row
//place second row element
//populate 3rd conflicts
//place third row element
//Incase we cannot place an element. update the previous row conflict and jump to the previous statement after population of conflicts
//Incase  we reached the end finish
//Incase we came to -1 th row, return error
	bool conflict_flag;
	workingRow = 0;
beforeConflictCalc:
	populateConflicts(workingRow);
AfterConfictCalc:
	conflict_flag = true;
	clearRow(workingRow, chessBoard);//Start clean
	for(int i=0; i<N; i++){
		if(conflict[workingRow][i] == false){
			conflict_flag = false;
			chessBoard[workingRow][i] = 1; // placing queen where
			lastColumnPlaced.push(i);
			break;
		}
	}
	if(conflict_flag == true){
		clearRow(workingRow, conflict);//clear the current populateConflicts
		workingRow--;
		if(workingRow<0){
			return 0;//failed
		}
		conflict[workingRow][lastColumnPlaced.top()] = 1;//avoid this point in the next step
		lastColumnPlaced.pop();//delete the previous queen
		goto AfterConfictCalc;
	}
	else{
		workingRow++;
		if(workingRow==N)	return 1;//success
		goto beforeConflictCalc;
	}
cout<<"error";
}

void clearRow(int row, bool mat[N][N]){
	for(int i= 0 ; i<N; i++) mat[row][i] = 0;
}
void populateConflicts(int workingRow){
	if(workingRow == 0) {
		for(int i=0; i<N; i++) conflict[workingRow][i]= false;
	}
	for(int j=0; j<N; j++){
			for(int i = workingRow-1; i>=0; i--){ // up
				if(chessBoard[i][j]==1){
					conflict[workingRow][j] = true;
					break;
				}
			}
			//right diag
			for(int i=workingRow-1, k=j+1; i>=0 && k<N; i--, k++){
				if(chessBoard[i][k] == 1){
					conflict[workingRow][j] = true;
					break;
				}
			}
			for(int i = workingRow-1, k=j-1; i>=0 && k>=0; i--,k--){ //left diag
				if(chessBoard[i][k] == 1){
					conflict[workingRow][j] = true;
					break;
				}
			}
	}
}

