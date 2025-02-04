#include <bits/stdc++.h>
#define endl '\n'
#define mod % 1000000007

typedef long long ll;

using namespace std;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);
	
	freopen("C:/Users/jhshin/Desktop/secret/SWEA/13501/sample_input.txt", "r", stdin);
	
	int T;
	cin >> T;
	for(int test_case=1; test_case<=T; test_case++) {
		int n, m, l;
		cin >> n >> m >> l;
		vector<int> v(n);
		for(auto &i : v) cin >> i;
		for(int i=0; i<m; i++) {
			char c;
			int a, b;
			cin >> c;
			if(c == 'I') {
				cin >> a >> b;
				v.insert(v.begin()+a, b);
			}
			else if(c == 'D') {
				cin >> a;
				v.erase(v.begin()+a);
			}
			else if(c == 'C') {
				cin >> a >> b;
				v[a] = b;
			}
		}
		if(v.size() <= l) cout << "#" << test_case << " -1" << endl;
		else cout << "#" << test_case << " " << v[l] << endl;
	}
	
	return 0;
}