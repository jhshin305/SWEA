#include <bits/stdc++.h>
#define endl '\n'
#define mod % 1000000007

typedef long long ll;

using namespace std;

struct Node {
	char data;
	int left = 0;
	int right = 0;
};

string returnData(const Node& node, const vector<Node>& nodes) {
	string str = "";
	if(node.left != 0) {
		str += returnData(nodes[node.left], nodes);
	}
	str += node.data;
	if(node.right != 0) {
		str += returnData(nodes[node.right], nodes);
	}
	return str;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);
	
	freopen("C:/Users/jhshin/Desktop/secret/swea/20250204/n_3_1231/sample_input.txt", "r", stdin);
	
	int T = 10;
	for (int test_case=1; test_case<=T; test_case++) {
	
		int N;
		cin >> N;
		cin.ignore();

		vector<Node> nodes(N+1);
		for(int i=1; i<=N; i++) {
			string temp;
			getline(cin, temp);
			istringstream iss(temp);
			int idx;
			iss >> idx >> nodes[idx].data;
			if(iss >> nodes[idx].left) {
				iss >> nodes[idx].right;
			}
		}

		cout << "#" << test_case << " " << returnData(nodes[1], nodes) << endl;
	}
	
	return 0;
}