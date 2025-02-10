#include <bits/stdc++.h>
#define endl '\n'
#define mod % 1000000007

typedef long long ll;

using namespace std;

class UnionFind {
	public:
		vector<int> parent, rank;
		UnionFind(int n) : parent(n), rank(n, 1) {
			for (int i = 0; i < n; i++) {
				parent[i] = i;
			}
		}
		int Find(int x) {
			if (x == parent[x]) return x;
			return parent[x] = Find(parent[x]);
		}
		void Union(int a, int b) {
			a = Find(a);
			b = Find(b);
			if (a == b) return;
			else if (rank[a] < rank[b]) {
				parent[a] = b;	
			}
			else if (rank[a] > rank[b]) {
				parent[b] = a;
			}
			else {
				parent[b] = a;
				rank[a]++;
			}
		}
};

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);
	
	freopen("C:/Users/jhshin/Desktop/secret/swea/20250205/n_5_7465/sample_input.txt", "r", stdin);
	
	int T;
	cin >> T;
	for (int test_case=1; test_case<=T; test_case++) {
	
		int n, m;
		cin >> n >> m;

		int cnt = n;

		UnionFind uf(n+1);

		for(int i=0; i<m; i++) {
			int a, b;
			cin >> a >> b;
			if(uf.Find(a) != uf.Find(b)) {
				uf.Union(a, b);
				cnt--;
			}
		}

		cout << "#" << test_case << " " << cnt << endl;
	}
	
	return 0;
}