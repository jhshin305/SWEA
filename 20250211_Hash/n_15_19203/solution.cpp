#include <bits/stdc++.h>
#define ll long long

using namespace std;

string s;

void init(char mStr[])
{
	s = "";
	for(int i=0; mStr[i]!='\0'; i++)
		s += mStr[i];
}

void appendWord(char mWord[])
{
	for(int i=0; mWord[i]!='\0'; i++)
		s += mWord[i];
}

void cut(int k)
{
	s = s.substr(0, s.size()-k);
}

void reverse()
{
	reverse(s.begin(), s.end());
}

int kmp(const string &d, const string &t)
{
	vector<int> fail(t.size());
	for(int i=1, j=0; i<t.size(); i++)
	{
		while(j>0 && t[i]!=t[j])
			j = fail[j-1];
		if(t[i]==t[j])
			fail[i] = ++j;
	}
	int cnt = 0;
	for(int i=0, j=0; i<d.size(); i++)
	{
		while(j>0 && d[i]!=t[j])
			j = fail[j-1];
		if(d[i]==t[j])
		{
			if(j==t.size()-1)
			{
				cnt++;
				j = fail[j];
			}
			else
				j++;
		}
	}
	return cnt;
}

int countOccurrence(char mWord[])
{
	string t;
	for(int i=0; mWord[i]!='\0'; i++)
		t += mWord[i];


	return kmp(s, t);
}