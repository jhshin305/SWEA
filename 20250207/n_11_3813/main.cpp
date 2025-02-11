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
	
		int n, k;
		cin >> n >> k;

		vector<int> w(n);
		vector<int> s(k);
		for(auto &i : w) cin >> i;
		for(auto &i : s) cin >> i;

		


		cout << "Case #" << test_case << endl;
	}
	
	return 0;
}