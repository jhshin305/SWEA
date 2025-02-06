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
		vector<int> a(n);
		for(auto &i : a) cin >> i;
		int k;
		cin >> k;
		priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int,int>>> pq;
		pq.push({0, k});
		while(pq.top().second) {
			pair<int, int> p = pq.top();
			pq.pop();
			for(const auto& i : a) {
				pq.push({p.first+p.second%i, p.second/i});
			}
			pq.push({p.first+p.second, 0});
		}
		cout << "#" << test_case << " " << pq.top().first << endl;
	}
	
	return 0;
}