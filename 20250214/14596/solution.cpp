#include <bits/stdc++.h>
#define ll long long

using namespace std;

int Map[20][20];
int n;
vector<int> level[6];
int difMap[4][20][20];
int difSum[4][5][20][20];
queue<int> beach;
int nowLevel = 0;
int s[4][5][20][20];

void init(int N, int mMap[20][20])
{
	// n = N;
	// for (int i = 0; i < n; i++) {
	// 	for (int j = 0; j < n; j++) {
	// 		Map[i][j] = mMap[i][j];
	// 		level[mMap[i][j]].push_back(i * n + j);
	// 	}
	// }
	// for(int i=0; i<n; i++) {
	// 	for(int j=0; j<n; j++) {
	// 		if(i == 0) { //c-up
	// 			difMap[0][i][j] = 20;
	// 		} else {
	// 			difMap[0][i][j] = Map[i][j] - Map[i-1][j];
	// 		}
	// 		if(j == 0) { //c-left
	// 			difMap[1][i][j] = 20;
	// 		} else {
	// 			difMap[1][i][j] = Map[i][j] - Map[i][j-1];
	// 		}
	// 		if(i == n-1) { //c-down
	// 			difMap[2][i][j] = 20;
	// 		} else {
	// 			difMap[2][i][j] = Map[i][j] - Map[i+1][j];
	// 		}
	// 		if(j == n-1) { //c-right
	// 			difMap[3][i][j] = 20;
	// 		} else {
	// 			difMap[3][i][j] = Map[i][j] - Map[i][j+1];
	// 		}
	// 	}
	// 	// for(int j=0; j<Map[0][i]; j++) beach[0].push(i);
	// 	// for(int j=0; j<Map[i][0]; j++) beach[1].push(i*n);
	// 	// beach.push(i);
	// 	// beach.push((n-1)*n+i);
	// 	// beach.push(i*n);
	// 	// beach.push(i*n+n-1);
	// }
	// for(int i=0; i<n; i++) {
	// 	for(int j=0; j<n; j++) {

	// 	}
	// }
	// // for(int i=0; i<n; i++) {
	// // 	for(int j=0; j<n; j++) cout << Map[i][j] << " ";
	// // 	cout << endl;
	// // }
	// // cout << endl;
	// // for(int i=0; i<n; i++) {
	// // 	for(int j=0; j<n; j++) cout << difMap[0][i][j] << " ";
	// // 	cout << endl;
	// // }
	// // cout << endl;
	int n = N;
	for(int i=0; i<n; i++) {
		for(int j=0; j<n; j++) {
			Map[i][j] = mMap[i][j];
		}
	}
	for(int i=0; i<n; i++) {
		for(int j=0; j<n; j++) {
			for(int l=1; l<4; l++) {
				if(i+l < n) {
					s[0][l][i][j];
				}
			}
		}
	}
}

struct Q {
	int x, y, dir, sum, m;
};

int numberOfCandidate(int M, int mStructure[5])
{
	int cnt = 0;
	int dif[M-1];
	for(int m=0; m<M-1; m++) {
		dif[m] = mStructure[m+1] - mStructure[m];
	}
	bool isSym = true;
	for(int m=0; m<M-1; m++) {
		if(dif[m] != -dif[M-2-m]) {
			isSym = false;
			break;
		}
	}
	for(int i=0; i<n; i++) {
		for(int j=0; j<n; j++) {
			bool flag[4] = {true, true, true, true};
			for(int m=0; m<M-1; m++) {
				if(i-m<0 || difMap[0][i-m][j] != dif[m]) flag[0] = false;
				if(j-m<0 || difMap[1][i][j-m] != dif[m]) flag[1] = false;
				if(i+M-m>n || difMap[2][i+m][j] != dif[m]) flag[2] = false;
				if(j+M-m>n || difMap[3][i][j+m] != dif[m]) flag[3] = false;
			}
			for(int k=0; k<4; k++) {
				if(flag[k]) {
					cnt++;
					// cout << k << " " << i << " " << j << endl;
				}
			}
		}
	}
	// cout << endl;
	if(isSym) {
		cnt /= 2;
	}
	if(M == 1) {
		cnt /= 2;
	}



	// int cnt = 0;
	// queue<Q> q;
	// for(int i=0; i<n; i++) {
	// 	for(int j=0; j<n; j++) {
	// 		q.push({i, j, 0, Map[i][j]+mStructure[0], 1});
	// 		q.push({i, j, 1, Map[i][j]+mStructure[0], 1});
	// 		q.push({i, j, 2, Map[i][j]+mStructure[0], 1});
	// 		q.push({i, j, 3, Map[i][j]+mStructure[0], 1});
	// 	}
	// }
	// while(!q.empty()) {
	// 	Q curr = q.front();
	// 	q.pop();
	// 	if(curr.m == M) {
	// 		cnt++;
	// 		continue;
	// 	}
	// 	switch (curr.dir)
	// 	{
	// 		case 0:
	// 			if(curr.x-1 >= 0 && Map[curr.x-1][curr.y] == curr.sum-mStructure[curr.m]) {
	// 				q.push({curr.x-1, curr.y, 0, curr.sum, curr.m+1});
	// 			}
	// 			break;
	// 		case 1:
	// 			if(curr.y-1 >= 0 && Map[curr.x][curr.y-1] == curr.sum-mStructure[curr.m]) {
	// 				q.push({curr.x, curr.y-1, 1, curr.sum, curr.m+1});
	// 			}
	// 			break;
	// 		case 2:
	// 			if(curr.x+1 < n && Map[curr.x+1][curr.y] == curr.sum-mStructure[curr.m]) {
	// 				q.push({curr.x+1, curr.y, 2, curr.sum, curr.m+1});
	// 			}
	// 			break;
	// 		case 3:
	// 			if(curr.y+1 < n && Map[curr.x][curr.y+1] == curr.sum-mStructure[curr.m]) {
	// 				q.push({curr.x, curr.y+1, 3, curr.sum, curr.m+1});
	// 			}
	// 			break;
	// 	}
	// }
	// bool isSym = true;
	// for(int m=0; m<M; m++) {
	// 	if(mStructure[m] != mStructure[M-1-m]) {
	// 		isSym = false;
	// 		break;
	// 	}
	// }
	
	// if(isSym) {
	// 	cnt /= 2;
	// }
	// if(M == 1) {
	// 	cnt /= 2;
	// }
	
	return cnt;
}
	
int maxArea(int M, int mStructure[5], int mSeaLevel)
{
	int cnt = 0;
	// int dif[M-1];
	// for(int m=0; m<M-1; m++) {
	// 	dif[m] = mStructure[m+1] - mStructure[m];
	// }
	// int candi[5000];
	int candiSize = 0;
	// for(int i=0; i<n; i++) {
	// 	for(int j=0; j<n; j++) {
	// 		bool flag = true;
	// 		for(int m=0; m<M-1; m++) {
	// 			if(i+m >= n || j+m >= n) {
	// 				flag = false;
	// 				break;
	// 			}
	// 			if(difMap[0][i+m][j] != dif[m] || difMap[1][i][j+m] != dif[m] || difMap[2][i][j+m] != -dif[m] || difMap[3][i+m][j] != -dif[m]) {
	// 				flag = false;
	// 				break;
	// 			}
	// 		}
	// 		if(flag) {
	// 			candi[candiSize++] = i*n+j;
	// 		}
	// 	}
	// }
	// for(int i=0; i<candiSize; i++) {
	// 	int x = candi[i] / n;
	// 	int y = candi[i] % n;
	// 	if(Map[x][y] > mSeaLevel) {
	// 		cnt++;
	// 	}
	// }
	return candiSize ? cnt : -1;
}