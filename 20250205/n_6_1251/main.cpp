#include <bits/stdc++.h>
#define endl '\n'
#define mod % 1000000007

typedef long long ll;

using namespace std;

struct Point {
	ll x, y;
	double dist;
};

bool compare(const Point &a, const Point &b) {
	return a.dist < b.dist;
}

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
	
	freopen("C:/Users/jhshin/Desktop/secret/swea/20250205/n_6_1251/sample_input.txt", "r", stdin);
	
	int T;
	cin >> T;
	for (int test_case=1; test_case<=T; test_case++) {
	
		int n;
		cin >> n;

		vector<Point> points(n);
		for(auto &p : points) {
			cin >> p.x;
		}
		for(auto &p : points) {
			cin >> p.y;
		}

		double e;
		cin >> e;

		vector<Point> dist;

		for(int i=0; i<n; i++) {
			for(int j=i+1; j<n; j++) {
				dist.push_back({i, j, pow(points[i].x-points[j].x, 2) + pow(points[i].y-points[j].y, 2)});
			}
		}

		sort(dist.begin(), dist.end(), compare);

		UnionFind uf(n);
		int cnt = 0;
		double result = 0;
		for(const auto& d : dist) {
			if(uf.Find(d.x) != uf.Find(d.y)) {
				uf.Union(d.x, d.y);
				result += d.dist * e;
				cnt++;
			}
			if(cnt == n) break;
		}

		cout << "#" << test_case << " " << (ll)round(result) << endl;
	}
	
	return 0;
}