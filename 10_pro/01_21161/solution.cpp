#include <bits/stdc++.h>
#define ll long long
#define INF 1e7

using namespace std;

vector<array<int,2>> sline[301][31];
vector<array<int,2>> lline[301][4];
vector<int> sremoved[301][31];
vector<int> lremoved[301][4];
int dist[301][4][4];

int n, k;
int groupA, groupB;
int cityA, cityB;

void sdijkstra(const int& group) {
	int d[31];
	for(int s=1; s<4; s++) {
		for(int i=1; i<31; i++) {
			d[i] = INF;
		}
		d[s] = 0;
		priority_queue<array<int,2>, vector<array<int,2>>, greater<array<int,2>>> pq;
		pq.push({0, s});
		while(!pq.empty()) {
			auto [cost, curr] = pq.top();
			pq.pop();
			if(d[curr] != cost) continue;
			for(auto [ncost, next] : sline[group][curr]) {
				if(d[next] > cost + ncost) {
					d[next] = cost + ncost;
					pq.push({d[next], next});
				}
			}
		}
		for(int i=1; i<4; i++) {
			dist[group][s][i] = d[i];
		}
	}
}

int ldijkstra(int start,  int end) {
	int d[301][4];
	for(int i=0; i<=n; i++) {
		for(int j=1; j<4; j++) {
			d[i][j] = INF;
		}
	}

	d[0][start] = 0;
	priority_queue<array<int,2>, vector<array<int,2>>, greater<array<int,2>>> pq;
	pq.push({0, start});
	while(!pq.empty()) {
		auto [cost, curr] = pq.top();
		if(curr==end) return cost;
		pq.pop();
		if(d[curr/100][curr%100] != cost) continue;
		for(auto [ncost, next] : lline[curr/100][curr%100]) {
			if(d[next/100][next%100] > cost + ncost) {
				d[next/100][next%100] = cost + ncost;
				pq.push({d[next/100][next%100], next});
			}
		}
		for(int next=1; next<=3; next++) {
			if(d[curr/100][next] > cost + dist[curr/100][curr%100][next]) {
				d[curr/100][next] = cost + dist[curr/100][curr%100][next];
				pq.push({d[curr/100][next], curr/100*100+next});
			}
		}
	}
	return d[0][end];
}


void init(int N, int K, int mNodeA[], int mNodeB[], int mTime[])
{
	n = N, k = K;
	for(int i = 0; i < 301; i++) {
		for(int j = 1; j < 31; j++) {
			sline[i][j].clear();
			sremoved[i][j].clear();
		}
		for(int j=0; j<4; j++) {
			lline[i][j].clear();
			lremoved[i][j].clear();
			for(int k=0; k<4; k++) {
				dist[i][j][k] = INF;
			}
		}
	}
	for(int i = 0; i < K; i++) {
		groupA = mNodeA[i]/100; groupB = mNodeB[i]/100;
		cityA = mNodeA[i]%100; cityB = mNodeB[i]%100;
		if(groupA == groupB) {
			sline[groupA][cityA].push_back({mTime[i], cityB});
			sline[groupB][cityB].push_back({mTime[i], cityA});
		} else {
			lline[groupA][cityA].push_back({mTime[i], mNodeB[i]});
			lline[groupB][cityB].push_back({mTime[i], mNodeA[i]});
		}
	}
	for(int i=1; i<=N; i++) sdijkstra(i);
}

void addLine(int mNodeA, int mNodeB, int mTime)
{
	groupA = mNodeA/100; groupB = mNodeB/100;
	cityA = mNodeA%100; cityB = mNodeB%100;
	if(groupA == groupB) {
		sline[groupA][cityA].push_back({mTime, cityB});
		sline[groupB][cityB].push_back({mTime, cityA});
		sdijkstra(groupA);
	}
	else {
		lline[groupA][cityA].push_back({mTime, mNodeB});
		lline[groupB][cityB].push_back({mTime, mNodeA});
	}
}

void removeLine(int mNodeA, int mNodeB)
{
	groupA = mNodeA/100; groupB = mNodeB/100;
	cityA = mNodeA%100; cityB = mNodeB%100;
	if(groupA == groupB) {
		sline[groupA][cityA].erase(remove_if(sline[groupA][cityA].begin(), sline[groupA][cityA].end(), [&](array<int,2> a) { return a[1] == cityB; }), sline[groupA][cityA].end());
		sline[groupB][cityB].erase(remove_if(sline[groupB][cityB].begin(), sline[groupB][cityB].end(), [&](array<int,2> a) { return a[1] == cityA; }), sline[groupB][cityB].end());
		sdijkstra(groupA);
	} else {
		lline[groupA][cityA].erase(remove_if(lline[groupA][cityA].begin(), lline[groupA][cityA].end(), [&](array<int,2> a) { return a[1] == mNodeB; }), lline[groupA][cityA].end());
		lline[groupB][cityB].erase(remove_if(lline[groupB][cityB].begin(), lline[groupB][cityB].end(), [&](array<int,2> a) { return a[1] == mNodeA; }), lline[groupB][cityB].end());
	}
}

int checkTime(int mNodeA, int mNodeB)
{
	return ldijkstra(mNodeA, mNodeB);
}