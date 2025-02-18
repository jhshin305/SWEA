#include <bits/stdc++.h>
#define endl '\n'
#define mod % 1000000007

typedef long long ll;

using namespace std;

// struct ST {
	// int n;
	// vector<int> tree;
	// ST(vector<int> &arr) {
	// 	n = arr.size();
	// 	int tree_size = 1 << (int)ceil(log2(n)+1);
	// 	tree = vector<int>(tree_size,-1);
	// 	init(arr, 0, n-1, 1);
	// }
	// update(const int&)
// };

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);
	
	// freopen("sample_input.txt", "r", stdin);
	
	// int T;
	// cin >> T;
	// for (int test_case=1; test_case<=T; test_case++) {
	// 	cout << "#" << test_case << " ";
	
	// 	int n, q;
	// 	cin >> n >> q;

	// 	vector<int> arr(n);
	// 	for(auto &i: arr) cin >> i;

	// 	ST st(arr);

	// 	for(int i=0; i<q; i++) {
	// 		int a, b, c;
	// 		cin >> a >> b >> c;
	// 		if(a == 0) st.update(b, c);
	// 		else cout << st.query(b, c) << " ";
	// 	}

	// }
	
	int a;
	cin >> a;
	cout << (1 << (int)ceil(log2(a)+1));

	return 0;
}