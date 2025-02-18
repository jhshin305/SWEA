#include <bits/stdc++.h>
#define endl '\n'
#define mod % 1000000007

typedef long long ll;

using namespace std;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);
	
	freopen("sample_input.txt", "r", stdin);
	
	int T;
	cin >> T;
	for (int test_case=1; test_case<=T; test_case++) {
		int n, m;
		cin >> n >> m;
		set<string> a;
		for(int i=0; i<n; i++) {
			string tmp;
			cin >> tmp;
			a.insert(tmp);
		}
		int cnt = 0;
		for(int i=0; i<m; i++) {
			string tmp;
			cin >> tmp;
			if(a.find(tmp) != a.end()) cnt++;
		}

		cout << "#" << test_case << " " << cnt << endl;
	}
	
	return 0;
}