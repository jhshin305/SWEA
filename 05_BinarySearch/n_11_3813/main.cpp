#include <bits/stdc++.h>
#define endl '\n'
#define mod % 1000000007
#define MAX_N 200000
#define MAX_K 200000

typedef long long ll;

using namespace std;

vector<int> w(MAX_N);
vector<int> s(MAX_K);
int n, k;

bool checking(const int& mid) {
	int wIdx = 0;
	int sIdx = 0;
	int cnt = 0;
	while(true) {
		if(w[wIdx] <= mid) {
			cnt++;
			if(cnt == s[sIdx]) {
				sIdx++;
				cnt = 0;
				if(sIdx == k) return true;
			}
		}
		else {
			cnt = 0;
		}
		wIdx++;
		if(wIdx == n) return false;
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);
	
	freopen("sample_input.txt", "r", stdin);
	
	int T;
	cin >> T;
	for (int test_case=1; test_case<=T; test_case++) {
		cin >> n >> k;

		for(int i=0; i<n; i++) cin >> w[i];
		for(int i=0; i<k; i++) cin >> s[i];
		

		int left = 1, right = 200000;
		int ans;
		while(left <= right) {
			int mid = (left + right) / 2;
			if(checking(mid)) {
				ans = mid;
				right = mid - 1;
			} else {
				left = mid + 1;
			}
		}


		cout << "Case #" << test_case << " " << ans << endl;
	}
	
	return 0;
}