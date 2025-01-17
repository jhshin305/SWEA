#include <bits/stdc++.h>

using namespace std;

int MoveAndDelete(int mPlayer);
void MoveToBottom();
vector<int> deleteBlocks(int mPlayer);
vector<int> setZero(int mPlayer);
int deleteVertical(int mh, int mw);
int deleteHorizontal(int mh, int mw);
int deleteDownwardRightDiagonal(int mh, int mw);
int deleteDownwardLeftDiagonal(int mh, int mw);

int w, h;
vector<vector<int>> board;
vector<int> scores;

struct Point {
	int x, y;
};

void printBoard() {
	for(const auto& row : board) {
		for(const auto& block : row) {
			cout << block << " ";
		}
		cout << endl;
	}
	cout << endl;
}

void init(int W, int H)
{
	w = W;
	h = H;
	board = vector<vector<int>>(h, vector<int>(w, 0));
	scores = {0, 0, 0};
}

int dropBlocks(int mPlayer, int mCol)
{
	for(int i=0; i<3; i++) {
		board[0][mCol+i] = mPlayer;
	}

	return MoveAndDelete(mPlayer);
}

int changeBlocks(int mPlayer, int mCol)
{
	int Opponent = mPlayer == 1 ? 2 : 1;
	queue<Point> q;
	if(board[h-1][mCol] == Opponent) q.push({h-1, mCol});
	while(!q.empty()) {
		Point curr = q.front();
		board[curr.x][curr.y] = mPlayer;
		q.pop();
		if(curr.x-1 >= 0 && board[curr.x-1][curr.y] == Opponent) {
			q.push({curr.x-1, curr.y});
		}
		if(curr.y-1 >= 0 && board[curr.x][curr.y-1] == Opponent) {
			q.push({curr.x, curr.y-1});
		}
		if(curr.y+1 < w && board[curr.x][curr.y+1] == Opponent) {
			q.push({curr.x, curr.y+1});
		}
		if(curr.x+1 < h && board[curr.x+1][curr.y] == Opponent) {
			q.push({curr.x+1, curr.y});
		}
	}

	return MoveAndDelete(mPlayer);
}

int getResult(int mBlockCnt[2])
{
	mBlockCnt[0] = 0;
	mBlockCnt[1] = 0;
	for(const auto& row : board) {
		for(const auto& block : row) {
			mBlockCnt[abs(block)-1]++;
		}
	}
	return scores[1]>scores[2] ? 1 : scores[1]<scores[2] ? 2 : 0;
}

int MoveAndDelete(int mPlayer) {
	int score = 0;

	while(true) {
		MoveToBottom();
		vector<int> cnt = deleteBlocks(mPlayer);
		if(cnt == vector<int> {0, 0, 0}) break;
		else score += cnt[mPlayer];
	}
	scores[mPlayer] += score;
	
	// printBoard();//////////////////////////////////////////////////////
	
	return score;
}

void MoveToBottom() {
	for(int c=0; c<w; c++) {
		int bottom = h-1;
		int top = h-1;
		while(top >= 0) {
			if(board[top][c] == 0) {
				top--;
			} else {
				board[bottom][c] = board[top][c];
				if(top != bottom) {
					board[top][c] = 0;
				}
				bottom--;
				top--;
			}
		}
	}
}

vector<int> deleteBlocks(int mPlayer) {
	vector<int> cnt = {0, 0, 0};
	for(int i=0; i<h; i++) {
		for(int j=0; j<w; j++) {
			if(board[i][j] != 0) {
				if(i==0 || abs(board[i-1][j]) != abs(board[i][j])) deleteVertical(i, j);
				if(j==0 || abs(board[i][j-1]) != abs(board[i][j])) deleteHorizontal(i, j);
				if(i==0 || j==0 || abs(board[i-1][j-1]) != abs(board[i][j])) deleteDownwardRightDiagonal(i, j);
				if(i==0 || j==w-1 || abs(board[i-1][j+1]) != abs(board[i][j])) deleteDownwardLeftDiagonal(i, j);
			}
		}
	}
	cnt = setZero(mPlayer);

	return cnt;
}

vector<int> setZero(int mPlayer) {
	vector<int> cnt = {0, 0, 0};
	for(int i=0; i<h; i++) {
		for(int j=0; j<w; j++) {
			if(board[i][j] < 0) {
				cnt[abs(board[i][j])]++;
				board[i][j] = 0;
			}
		}
	}
	return cnt;
}

int deleteVertical(int mh, int mw) {
	int cnt = 1;
	int ni = mh;
	int nj = mw;
	while(ni+1 < h && abs(board[mh][mw]) == abs(board[ni+1][mw])) {
		cnt++;
		ni++;
	}
	if(cnt >= 5) {
		for(int i=0; i<cnt; i++) {
			board[mh][mw] = -abs(board[mh][mw]);
			mh++;
		}
		return cnt;
	}
	return 0;
}

int deleteHorizontal(int mh, int mw) {
	int cnt = 1;
	int ni = mh;
	int nj = mw;
	while(nj+1 < w && abs(board[mh][mw]) == abs(board[mh][nj+1])) {
		cnt++;
		nj++;
	}
	if(cnt >= 5) {
		for(int i=0; i<cnt; i++) {
			board[mh][mw] = -abs(board[mh][mw]);
			mw++;
		}
		return cnt;
	}
	return 0;
}

int deleteDownwardRightDiagonal(int mh, int mw) {
	int cnt = 1;
	int ni = mh;
	int nj = mw;
	while(ni+1 < h && nj+1 < w && abs(board[mh][mw]) == abs(board[ni+1][nj+1])) {
		cnt++;
		ni++;
		nj++;
	}
	if(cnt >= 5) {
		for(int i=0; i<cnt; i++) {
			board[mh][mw] = -abs(board[mh][mw]);
			mh++;
			mw++;
		}
		return cnt;
	}
	return 0;
}

int deleteDownwardLeftDiagonal(int mh, int mw) {
	int cnt = 1;
	int ni = mh;
	int nj = mw;
	while(ni+1 < h && nj-1 >= 0 && abs(board[mh][mw]) == abs(board[ni+1][nj-1])) {
		cnt++;
		ni++;
		nj--;
	}
	if(cnt >= 5) {
		for(int i=0; i<cnt; i++) {
			board[mh][mw] = -abs(board[mh][mw]);
			mh++;
			mw--;
		}
		return cnt;
	}
	return 0;
}