#include <bits/stdc++.h>
#define ll long long
#define alpha 26

using namespace std;

struct Trie {
	Trie* next[alpha];
	int cnt=0;
	Trie() {
		fill(next, next + alpha, nullptr);
		cnt = 0;
	}
	~Trie() {
		for(int i=0; i<alpha; i++) {
			if(next[i]) {
				delete next[i];
			}
		}
	}
	int insert(const char* key) {
		if(*key == '\0') {
			return ++cnt;
		}
		else {
			int curr = *key - 'a';
			if(!next[curr]) {
				next[curr] = new Trie();
			}
			return next[curr]->insert(key + 1);
		}
	}
	int remove(const char* key) {
		if(*key == '\0') {
			if(cnt) {
				int ret = cnt;
				cnt = 0;
				return ret;
			}

			else return 0;
		}
		else if(*key == '?') {
			int ret = 0;
			for(int curr=0; curr<alpha; curr++) {
				if(next[curr]) 
					ret += next[curr]->remove(key + 1);
			}
			return ret;
		}
		else {
			int curr = *key - 'a';
			if(!next[curr]) {
				return 0;
			}
			return next[curr]->remove(key + 1);
		}
	}
	int find(const char* key) {
		if(*key == '\0') {
			return cnt;
		}
		else if(*key == '?') {
			int ret = 0;
			for(int curr=0; curr<alpha; curr++) {
				if(next[curr]) {
					ret += next[curr]->find(key + 1);
				}
			}
			return ret;
		}
		else {
			int curr = *key - 'a';
			if(!next[curr]) {
				return 0;
			}
			return next[curr]->find(key + 1);
		}
	}
};

Trie* root;

void init() {
	delete root;
	root = new Trie();
	return;
}

int add(char str[]) {
	return root->insert(str);
}

int remove(char str[]) {
	return root->remove(str);
}

int search(char str[]) {
	return root->find(str);
}