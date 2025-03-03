#include <bits/stdc++.h>
#define ll long long

using namespace std;

int last;
vector<int> dif;

void init()
{
	last = -1;
	dif.clear();
}

void makeWall(int mHeights[5])
{
	for(int i = 0; i < 5; i++)
	{
		if(last != -1) dif.push_back(0);
		else dif.push_back(mHeights[i] - last);
		last = mHeights[i];
	}
}

int matchPiece(int mHeights[5])
{
	
	return -1;
}