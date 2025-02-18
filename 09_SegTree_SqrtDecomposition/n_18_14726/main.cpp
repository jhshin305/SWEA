#include <bits/stdc++.h>
#define endl '\n'
#define mod % 1000000007

typedef long long ll;

using namespace std;

struct ST {
	int n;
	vector<array<int,2>> tree;
	int tree_size;
	ST(vector<int> &arr) {
		n = arr.size();
		tree_size = 1 << (int)ceil(log2(n)+1);
		tree = vector<array<int,2>>(tree_size,{-1,INT_MAX});
		for(int i=tree_size/2; i<tree_size/2+n; i++) tree[i] = {arr[i-tree_size/2],arr[i-tree_size/2]};
		for(int i=tree_size/2-1; i>0; i--) {
			tree[i][0] = max(tree[i*2][0], tree[i*2+1][0]);
			tree[i][1] = min(tree[i*2][1], tree[i*2+1][1]);
		}
	}
	void update(const int& idx, const int& val) {
		int i = idx + tree_size/2;
		tree[i] = {val,val};
		while(i > 1) {
			i /= 2;
			tree[i][0] = max(tree[i*2][0], tree[i*2+1][0]);
			tree[i][1] = min(tree[i*2][1], tree[i*2+1][1]);
		}
	}
	int query(int l, int r) {
		int max_val = -1, min_val = INT_MAX;
		l += tree_size/2; r += tree_size/2;
		while(l <= r) {
			if(l % 2 == 1) {
				max_val = max(max_val, tree[l][0]);
				min_val = min(min_val, tree[l][1]);
				l++;
			}
			if(r % 2 == 0) {
				max_val = max(max_val, tree[r][0]);
				min_val = min(min_val, tree[r][1]);
				r--;
			}
			l /= 2; r /= 2;
		}
		return max_val - min_val;
	}
};

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);
	
	freopen("sample_input.txt", "r", stdin);
	
	int T;
	cin >> T;
	for (int test_case=1; test_case<=T; test_case++) {
		cout << "#" << test_case << " ";
	
		int n, q;
		cin >> n >> q;

		vector<int> arr(n);
		for(auto &i: arr) cin >> i;

		ST st(arr);


		for(int i=0; i<q; i++) {
			int a, b, c;
			cin >> a >> b >> c;
			if(a == 0) st.update(b, c);
			else cout << st.query(b, c-1) << " ";
		}
		cout << endl;
	}
	return 0;
}