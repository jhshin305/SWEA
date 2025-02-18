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
	
		int n;
		cin >> n;

		vector<string> m(n);
		for(auto &i : m) {
			cin >> i;
		}

		vector<vector<int>> dp(n, vector<int>(n, INT_MAX));
		queue<array<int,2>> q;
		q.push({0,0});
		dp[0][0] = 0;
		while(!q.empty()) {
			auto [x, y] = q.front();
			q.pop();
			if(x+1 < n && dp[x+1][y] > dp[x][y] + m[x+1][y] - '0') {
				dp[x+1][y] = dp[x][y] + m[x+1][y] - '0';
				q.push({x+1, y});
			}
			if(x-1 >= 0 && dp[x-1][y] > dp[x][y] + m[x-1][y] - '0') {
				dp[x-1][y] = dp[x][y] + m[x-1][y] - '0';
				q.push({x-1, y});
			}
			if(y+1 < n && dp[x][y+1] > dp[x][y] + m[x][y+1] - '0') {
				dp[x][y+1] = dp[x][y] + m[x][y+1] - '0';
				q.push({x, y+1});
			}
			if(y-1 >= 0 && dp[x][y-1] > dp[x][y] + m[x][y-1] - '0') {
				dp[x][y-1] = dp[x][y] + m[x][y-1] - '0';
				q.push({x, y-1});
			}
		}
		cout << "#" << test_case << " " << dp[n-1][n-1] << endl;
	}
	
	return 0;
}