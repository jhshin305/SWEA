#include <bits/stdc++.h>
#define ll long long
#define MAX_NODE 30040
#define MAX_GROUP 301

using namespace std;

// vector<int> sGroup[MAX_GROUP];
// vector<int> connected[MAX_GROUP][31];
// vector<int> outCon[MAX_GROUP][4];
int bridge[MAX_GROUP][31][MAX_GROUP][31];
int cost[MAX_GROUP][31][MAX_GROUP][31];
// int vst[MAX_GROUP][31];
int n, k, tc=0;
int aGroup, bGroup;
int aNode, bNode;

void sGroupTime(const int& group) {
	//dijstra
	for(int s=1; s<=3; s++) {
		priority_queue<array<int,2>, vector<array<int,2>>, greater<array<int,2>>> pq; //totalCost, endNode
		vector<int> c(31, INT_MAX);
		c[s] = 0;
		bool vst[31];
		pq.push({0,s});
		while(!pq.empty()) {
			auto q = pq.top();
			pq.pop();
			vst[q[1]] = true;
			c[q[1]] = q[0];
			for(int e=1; e<=30; e++) {
				if(vst[e] == true) continue;
				if(bridge[group][q[1]][group][e] == 0) continue;
				pq.push({q[0] + bridge[group][q[1]][group][e], e});
			}
				// for(auto& i: connected[group][q[1]]) {
				// 	if(bridge[group][q[1]][group][i%100] > 0 && vst[i%100]==false)
				// 		pq.push({q[0] + bridge[group][q[1]][group][i%100], i%100});
				// }
		}
		for(int e=1; e<=3; e++) cost[group][s][group][e] = c[e];
	}
}

void init(int N, int K, int mNodeA[], int mNodeB[], int mTime[])
{
	n = N;
	k = K;
	tc++;

	for(int i=0; i<MAX_GROUP; i++) {
		for(int j=0; j<31; j++) {
			// connected[i][j].clear();
			for(int k=0; k<MAX_GROUP; k++) {
				for(int l=0; l<31; l++) {
					bridge[i][j][k][l] = 0;
					cost[i][j][k][l] = INT_MAX;
				}
			}
			cost[i][j][i][j] = 0;
		}
	}
	
	for(int i=0; i<k; i++) {
		aGroup = mNodeA[i]/100; bGroup = mNodeB[i]/100;
		aNode = mNodeA[i]%100; bNode = mNodeB[i]%100;
		// if(aGroup == bGroup) {
		// 	connected[aGroup][aNode].push_back(mNodeB[i]);
		// 	connected[bGroup][bNode].push_back(mNodeA[i]);
		// }
		// else {
		// 	outCon[aGroup][aNode].push_back(mNodeB[i]);
		// 	outCon[bGroup][bNode].push_back(mNodeA[i]);
		// }
		bridge[aGroup][aNode][bGroup][bNode] = mTime[i];
		bridge[bGroup][bNode][aGroup][aNode] = mTime[i];
		cost[aGroup][aNode][bGroup][bNode] = mTime[i];
		cost[bGroup][bNode][aGroup][aNode] = mTime[i];
	}

	for(int g=1; g<=n; g++) sGroupTime(g);
}

void addLine(int mNodeA, int mNodeB, int mTime)
{
	aGroup = mNodeA/100; bGroup = mNodeB/100;
	aNode = mNodeA%100; bNode = mNodeB%100;
	// connected[aGroup][aNode].push_back(mNodeB);
	// connected[bGroup][bNode].push_back(mNodeA);
	bridge[aGroup][aNode][bGroup][bNode] = mTime;
	bridge[bGroup][bNode][aGroup][aNode] = mTime;

	if(cost[aGroup][aNode][bGroup][bNode] > mTime) {
		cost[aGroup][aNode][bGroup][bNode] = mTime;
		cost[bGroup][bNode][aGroup][aNode] = mTime;
		if(aGroup == bGroup) sGroupTime(aGroup);
	}
}

void removeLine(int mNodeA, int mNodeB)
{
	aGroup = mNodeA/100; bGroup = mNodeB/100;
	aNode = mNodeA%100; bNode = mNodeB%100;

	if(cost[aGroup][aNode][bGroup][bNode] < bridge[aGroup][aNode][bGroup][bNode]) {
		cost[aGroup][aNode][bGroup][bNode] = 0;
		if(aGroup == bGroup) sGroupTime(aGroup);
	}

	bridge[aGroup][aNode][bGroup][bNode] = 0;
	bridge[bGroup][bNode][aGroup][aNode] = 0;
}

int checkTime(int mNodeA, int mNodeB)
{
	priority_queue<array<int,2>, vector<array<int,2>>, greater<array<int,2>>> pq; //totalCost, endNode
	vector<int> c(MAX_GROUP*4, INT_MAX);
	c[mNodeA] = 0;
	bool vst[MAX_GROUP][4];
	pq.push({0,mNodeA});
	while(!pq.empty()) {
		auto q = pq.top();
		pq.pop();
		int g = q[1]/100, n = q[1]%100;
		vst[g][n] = true;
		c[q[1]] = q[0];
		for(int group=0; group<=300; group++) {
			for(int node=1; node<=3; node++) {
				if(vst[group][node] == true) continue;
				if(g==group && g!=0) {
					pq.push({c[q[1]]+cost[g][n][group][node], group*100+node});
				}
				else {
					if(bridge[g][n][group][node] == 0) continue;
					pq.push({c[q[1]]+bridge[g][n][group][node], group*100+node});
				}
			}
		}
	}
	return c[mNodeB];
}