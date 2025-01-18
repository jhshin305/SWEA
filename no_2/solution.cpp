#include <bits/stdc++.h>

using namespace std;

const int MAX_W = 200;
const int MAX_H = 200;

int MoveAndDelete(int mPlayer);
void MoveToBottom();
void deleteBlocks(int mPlayer, int blocks[3]);
int deleteVertical(int mh, int mw);
int deleteHorizontal(int mh, int mw);
int deleteDownwardRightDiagonal(int mh, int mw);
int deleteUpwardRightDiagonal(int mh, int mw);

struct Point {
	int x, y;
};

int w, h;
int board[MAX_H][MAX_W];
int scores[3];
int target;
int Opponent;
Point curr;
int ni;
int nj;
int cnt;

void init(int W, int H)
{
	w = W;
	h = H;
	memset(board, 0, sizeof(board));
	scores[0] = 0;
	scores[1] = 0;
	scores[2] = 0;
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
	Opponent = mPlayer == 1 ? 2 : 1;
	stack<Point> s;
	if(board[h-1][mCol] == Opponent) s.push({h-1, mCol});
	while(!s.empty()) {
		curr = s.top();
		board[curr.x][curr.y] = mPlayer;
		s.pop();
		if(curr.x-1 >= 0 && board[curr.x-1][curr.y] == Opponent) {
			s.push({curr.x-1, curr.y});
		}
		if(curr.y-1 >= 0 && board[curr.x][curr.y-1] == Opponent) {
			s.push({curr.x, curr.y-1});
		}
		if(curr.y+1 < w && board[curr.x][curr.y+1] == Opponent) {
			s.push({curr.x, curr.y+1});
		}
		if(curr.x+1 < h && board[curr.x+1][curr.y] == Opponent) {
			s.push({curr.x+1, curr.y});
		}
	}

	return MoveAndDelete(mPlayer);
}

int getResult(int mBlockCnt[2])
{
	mBlockCnt[0] = 0;
	mBlockCnt[1] = 0;
	for(int j=0; j<w; j++) {
		for(int i=h-1; i>=0; i--) {
			if(board[i][j] != 0) {
				mBlockCnt[abs(board[i][j])-1]++;
			} else break;
		}
	}
	return scores[1]>scores[2] ? 1 : scores[1]<scores[2] ? 2 : 0;
}

int MoveAndDelete(int mPlayer) {
	int score = 0;

	while(true) {
		MoveToBottom();
		int blocks[3] = {0, 0, 0};
		deleteBlocks(mPlayer, blocks);
		if(blocks[0] == 0 && blocks[1] == 0 && blocks[2] == 0) break;
		else score += blocks[mPlayer];
	}
	scores[mPlayer] += score;
	
	return score;
}

void MoveToBottom() {
	for(int c=0; c<w; c++) {
		int bottom = h-1;
		for (int top = h - 1; top >= 0; top--) {
			if(board[top][c] != 0) {
				board[bottom][c] = board[top][c];
				if(top != bottom) {
					board[top][c] = 0;
				}
				bottom--;
			}
		}
	}
}

void deleteBlocks(int mPlayer, int blocks[3]) {
	for(int j=0; j<w; j++) {
		for(int i=h-1; i>=0; i--) {
			if(board[i][j] != 0) {
				if(i==h-1 || abs(board[i+1][j]) != abs(board[i][j])) deleteVertical(i, j);
				if(j==0 || abs(board[i][j-1]) != abs(board[i][j])) deleteHorizontal(i, j);
				if(i==0 || j==0 || abs(board[i-1][j-1]) != abs(board[i][j])) deleteDownwardRightDiagonal(i, j);
				if(i==h-1 || j==0 || abs(board[i+1][j-1]) != abs(board[i][j])) deleteUpwardRightDiagonal(i, j);
				if(board[i][j] < 0) {
					blocks[abs(board[i][j])]++;
					board[i][j] = 0;
				}
			}
			else break;
		}
	}
}

int deleteVertical(int mh, int mw) {
	cnt = 1;
	ni = mh;
	nj = mw;
	target = abs(board[mh][mw]);
	while(ni-1 >= 0 && target == abs(board[ni-1][mw])) {
		cnt++;
		ni--;
	}
	if(cnt >= 5) {
		for(int i=0; i<cnt; i++) {
			board[mh][mw] = -abs(board[mh][mw]);
			mh--;
		}
		return cnt;
	}
	return 0;
}

int deleteHorizontal(int mh, int mw) {
	cnt = 1;
	ni = mh;
	nj = mw;
	target = abs(board[mh][mw]);
	while(nj+1 < w && target == abs(board[mh][nj+1])) {
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
	cnt = 1;
	ni = mh;
	nj = mw;
	target = abs(board[mh][mw]);
	while(ni+1 < h && nj+1 < w && target == abs(board[ni+1][nj+1])) {
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

int deleteUpwardRightDiagonal(int mh, int mw) {
	cnt = 1;
	ni = mh;
	nj = mw;
	target = abs(board[mh][mw]);
	while(ni-1 >= 0 && nj+1 < w && target == abs(board[ni-1][nj+1])) {
		cnt++;
		ni--;
		nj++;
	}
	if(cnt >= 5) {
		for(int i=0; i<cnt; i++) {
			board[mh][mw] = -abs(board[mh][mw]);
			mh--;
			mw++;
		}
		return cnt;
	}
	return 0;
}