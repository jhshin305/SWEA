#include <bits/stdc++.h>

using namespace std;

int h, w, cursor, cnt;
string mstr;
int idx;

void init(int H, int W, char mStr[])
{
	h = H;
	w = W;
	mstr.clear();
	cursor = 0;
	idx = 0;
	while(mStr[idx] != '\0')
	{
		mstr.push_back(mStr[idx++]);
	}
}

void insert(char mChar)
{
	mstr.insert(mstr.begin() + cursor, mChar);
	cursor++;
}

char moveCursor(int mRow, int mCol)
{
	cursor = (mRow-1) * w + (mCol-1);
	cursor = min(cursor, (int)mstr.size());
	if(cursor == (int)mstr.size()) {
		return '$';
	}
	else return mstr[cursor];
}

int countCharacter(char mChar)
{
	cnt = 0;
	idx = cursor;
	while(mstr.find(mChar, idx) != string::npos) {
		idx = mstr.find(mChar, idx);
		cnt++;
		idx++;
	}
	return cnt;
}
