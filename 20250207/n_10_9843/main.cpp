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
		ll n;
		cin >> n;

		ll ans;
		ll tmp = 1+8*n;
		ll tmp2 = static_cast<ll>(sqrt(tmp));
		if(tmp2 * tmp2 == tmp) {
			ans = (tmp2-1)/2;
		}
		else {
			ans = -1;
		}

		cout << "#" << test_case << " " << ans << endl;
	}
	
	return 0;
}