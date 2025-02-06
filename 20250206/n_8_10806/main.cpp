#include <bits/stdc++.h>
#define endl '\n'
#define mod % 1000000007

typedef long long ll;

using namespace std;

struct cmp {
	bool operator()(pair<ll, int>& a, pair<ll, int>& b) {
		if(a.second == b.second) return a.first > b.first;
		return a.second > b.second;
	}
};

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	freopen("sample_input.txt", "r", stdin);
	
	int T;
	cin >> T;
	for (int test_case=1; test_case<=T; test_case++) {
	
		int n;
		cin >> n;
		vector<ll> a(n);
		for(auto &i : a) cin >> i;
		sort(a.begin(), a.end(), greater<>());
		int k;
		cin >> k;
		int d=1, ans=0;
		priority_queue<pair<ll, int>, vector<pair<ll, int>>, cmp> pq;
		vector<int> lo(k+1, INT_MAX);
		pq.push({k, 0});

		while(!pq.empty()) {
			pair<ll, int> p = pq.top(); // {k, cnt}
			lo[p.first] = min(lo[p.first], p.second);
			if(p.first == 0) {
				ans = p.second;
				break;
			}
			pq.pop();
			for(auto i : a) {
				if(p.first%i == 0) {
					if(lo[p.first/i] > p.second) {
						pq.push({p.first/i, p.second});
						lo[p.first/i] = p.second;
					}
				}
			}
			if(lo[p.first-1] > p.second+1)
			{
				pq.push({p.first-1, p.second+1});
				lo[p.first-1] = p.second+1;
			}
		}
		cout << "#" << test_case << " " << ans << endl;
	}
	
	return 0;
}