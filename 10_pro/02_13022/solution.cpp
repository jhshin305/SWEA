#include <bits/stdc++.h>
#define ll long long

using namespace std;

int last;
vector<int> dif;

int kmpWhere(const vector<int>& target)
{
	// from right to left
	vector<int> pi(target.size(), 0);
	int j = 0;
	for(int i = 1; i < target.size(); i++)
	{
		while(j > 0 && target[i] != target[j]) j = pi[j - 1];
		if(target[i] == target[j]) pi[i] = ++j;
	}
	for(int i = 0; i < dif.size(); i++)
	{
		if(dif[i] == target[j])
		{
			if(j == target.size() - 1) return i - target.size() + 2;
			j++;
		}
		else
		{
			while(j > 0 && dif[i] != target[j]) j = pi[j - 1];
			if(dif[i] == target[j]) j++;
		}
	}
	return -1;
}

void init()
{
	last = -1;
	dif.clear();
}

void makeWall(int mHeights[5])
{
	for(int i = 0; i < 5; i++)
	{
		if(last != -1) dif.push_back(mHeights[i] - last);
		last = mHeights[i];
	}
}

int matchPiece(int mHeights[5])
{
	vector<int> target;
	int temp = -1;
	for(int i = 0; i < 5; i++)
	{
		if(temp != -1) target.push_back(mHeights[i] - temp);
		temp = mHeights[i];
	}
	int idx = kmpWhere(target);
	int sum = 0;
	
	return idx;
}