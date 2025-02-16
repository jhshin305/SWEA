#include <bits/stdc++.h>
#define ll long long
#define alpha 26

using namespace std;

string s;
bool isReverse;
int cntWord[475255]; // "a" -> "zzzz"

// extern int tc;

void printWordCnt() {
	// if(tc < 4) return;
	// cout << s << ": " << endl;
	// for(int i=0; i<475254; i++) {
	// 	string tmp = "";
	// 	int t = i;
	// 	while(t) {
	// 		tmp = (char)('a' + t%alpha - 1) + tmp;
	// 		t /= alpha;
	// 	}
	// 	if(cntWord[i] > 0)
	// 		cout << tmp << " " << cntWord[i] << endl;
	// }
	// cout << endl;
}

void init(char mStr[])
{
	memset(cntWord, 0, sizeof(cntWord));
	isReverse = false;
	s = "";
	for(int i=0; mStr[i]!='\0'; i++)
		s += mStr[i];
	
	for (int i = 0; i < s.size(); i++) {
		int hash = 0;
		for(int len=1; len<=4; len++) {
			if(i+len > s.size()) break;
			hash *= alpha;
			hash += s[i+len-1] - 'a' + 1;
			
			cntWord[hash]++;
		}
	}
	printWordCnt();
}

void appendWord(char mWord[])
{
	string tmp;
	if(!isReverse) {
		for(int i=0; mWord[i]!='\0'; i++) {
			s += mWord[i];
			int hash = 0;
			int cof = 1;
			for(int len=1; len<=4; len++) {
				if(s.size() < len) break;
				hash += (s[s.size()-1-len+1] - 'a' + 1)*cof;
				cof *= alpha;
				cntWord[hash]++;
			}
		}
	}
	else {
		for(int i=0; mWord[i]!='\0'; i++) {
			s = mWord[i] + s;
			int hash = 0;
			for(int len=1; len<=4; len++) {
				if(s.size() < len) break;
				hash *= alpha;
				hash += s[len-1] - 'a' + 1;
				cntWord[hash]++;
			}
		}
	}
	printWordCnt();
}

void cut(int k)
{
	if(!isReverse) {
		for(int start=s.size()-1; start>=s.size()-k; start--) {
			int hash = 0;
			int cof = 1;
			for(int len=1; len<=4; len++) {
				if(start-len+1 < 0) break;
				hash += (s[start-len+1] - 'a' + 1)*cof;
				cof *= alpha;
				
				cntWord[hash]--;
			}
		}
		s = s.substr(0, s.size()-k);
	}
	else {
		for(int start=0; start<k; start++) {
			int hash = 0;
			for(int len=1; len<=4; len++) {
				if(start+len-1 >= s.size()) break;
				hash *= alpha;
				hash += s[start+len-1] - 'a' + 1;
				
				cntWord[hash]--;
			}
		}
		s = s.substr(k);
	}
	printWordCnt();
}

void reverse()
{
	isReverse = !isReverse;
}

int countOccurrence(char mWord[])
{
	string tmp;
	for(int i=0; mWord[i]!='\0'; i++)
		tmp += mWord[i];
	if(isReverse) reverse(tmp.begin(), tmp.end());
	int tHash = 0;
	for(int i=0; i<tmp.size(); i++) {
		tHash *= alpha;
		tHash += tmp[i] - 'a' + 1;
	}
	int cnt = cntWord[tHash];

	return cnt;
}