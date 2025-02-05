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
		cout << "#" << test_case << " ";
	
		int n;
		cin >> n;

		priority_queue<int> pq;

		for(int i=0; i<n; i++) {
			int cmd;
			cin >> cmd;
			if(cmd == 1) {
				int num;
				cin >> num;
				pq.push(num);
			}
			else {
				if(pq.empty()) {
					cout << -1 << " ";
				}
				else {
					cout << pq.top() << " ";
					pq.pop();
				}
			}
		}

		cout << endl;
	}
	
	return 0;
}