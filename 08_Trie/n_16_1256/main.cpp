#include <bits/stdc++.h>
#define endl '\n'
#define mod % 1000000007
#define alpha 26

typedef long long ll;

using namespace std;

struct Trie {
	bool finish;
	Trie* next[alpha];
	int cntChild;
	Trie() {
		finish = false;
		memset(next, 0, sizeof(next));
		cntChild = 0;
	}
	void insert(const char* key) {
		if (*key == '\0') {
			finish = true;
		}
		else {
			int curr = *key - 'a';
			if (!next[curr]) {
				next[curr] = new Trie();
			}
			next[curr]->cntChild++;
			next[curr]->insert(key+1);
		}
	}
	string find(int k) {
		for (int i=0; i<alpha; i++) {
			if (next[i]) {
				if (k <= next[i]->cntChild) return string(1, i+'a') + next[i]->find(k);
				else k -= next[i]->cntChild;
			}
		}
		return "";
	}

};

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);
	
	freopen("sample_input.txt", "r", stdin);
	
	int T;
	cin >> T;
	for (int test_case=1; test_case<=T; test_case++) {
	
		int k;
		cin >> k;

		string s;
		cin >> s;

		Trie* root = new Trie();
		for (int i=0; i<s.size(); i++) {
			root->insert(s.substr(i).c_str());
		}
		string ans;
		ans = root->find(k);

		cout << "#" << test_case << " " << (ans!="" ? ans : "none")  << endl;
	}
	
	return 0;
}