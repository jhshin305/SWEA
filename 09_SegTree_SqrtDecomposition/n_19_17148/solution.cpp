#include <vector>
#include <array>
#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <cmath>
#define ll long long
#define MAX_N 100000
#define MAX_M 1000

using namespace std;

int n, m;
vector< vector<int>> type(MAX_M);

struct ST {
	vector<ll> tree;
	int tree_size;
	ST(const int* mTime = nullptr) {
		tree_size = 1 << int(ceil(log2(n) + 1));
		tree = vector<ll>(tree_size, 0);
		for (int i = 0; i < n; i++) tree[tree_size / 2 + i] = mTime[i];
		for (int i = tree_size / 2 - 1; i > 0; i--) tree[i] = tree[i * 2] + tree[i * 2 + 1];
	}
	void update(int idx) {
		tree[idx] = tree[idx * 2] + tree[idx * 2 + 1];
		if(idx/2) update(idx / 2);
	}
	ll getSum(int l, int r) {
		ll sum = 0;
		l += tree_size / 2; r += tree_size / 2;
		while (l <= r) {
			if (l % 2 == 1) {
				sum += tree[l];
				l++;
			}
			if (r % 2 == 0) {
				sum += tree[r];
				r--;
			}
			l /= 2;
			r /= 2;
		}
		return sum;
	}
};

ST bridge;

void init(int N, int M, int mType[], int mTime[])
{
	n = N - 1;
	m = M;
	type = vector< vector<int>>(MAX_M);
	for (int i = 0; i < n; i++) type[mType[i]].push_back(i);
	bridge = ST(mTime);
}

void destroy()
{

}

void update(int mID, int mNewTime)
{
	int idx = bridge.tree_size / 2 + mID;
	bridge.tree[idx] = mNewTime;
	bridge.update(idx / 2);
}

int updateByType(int mTypeID, int mRatio256)
{
	ll ret = 0;
	for (auto& i : type[mTypeID]) {
		int idx = bridge.tree_size / 2 + i;
		bridge.tree[idx] = bridge.tree[idx]  * mRatio256 / 256;
		bridge.update(idx / 2);
		ret += bridge.tree[bridge.tree_size / 2 + i];
	}
	return ret;
}

int calculate(int mA, int mB)
{
	if (mA > mB) swap(mA, mB);
	ll ans = bridge.getSum(mA, mB - 1);

	return ans;
}