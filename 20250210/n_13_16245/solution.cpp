#include <bits/stdc++.h>
#define ll long long
#define INF INT_MAX
#define MAX_CITY 600
#define MAX_N 1400
#define MAX_ADR 1000000001

using namespace std;

int n;
int city_cnt;
// vector<int> indexing(MAX_ADR, -1);
map<int, int> indexing;
vector<vector<int>> dist(MAX_CITY, vector<int>(MAX_CITY, INF));

void FloydWarshall() {
	for(int mid = 0; mid < city_cnt; mid++) {
		dist[mid][mid] = 0;
		for(int s = 0; s < city_cnt; s++)
			for(int e = 0; e < city_cnt; e++) {
				if(s==e || s==mid || e==mid) continue;
				if(dist[s][mid] != INF && dist[mid][e] != INF)
					dist[s][e] = min(dist[s][e], dist[s][mid] + dist[mid][e]);
			}
	}
}

int init(int N, int sCity[], int eCity[], int mCost[]) {
	n = N;
	city_cnt = 0;
	// indexing = vector<int>(MAX_ADR, -1);
	indexing.clear();
	dist = vector<vector<int>>(MAX_CITY, vector<int>(MAX_CITY, INF));
	for(int i = 0; i < N; i++) {
		// if(indexing[sCity[i]]) {
		if(indexing.find(sCity[i]) == indexing.end()) {
			indexing[sCity[i]] = city_cnt++;
		}
		// if(indexing[eCity[i]] == -1) {
		if(indexing.find(eCity[i]) == indexing.end()) {
			indexing[eCity[i]] = city_cnt++;
		}
		dist[indexing[sCity[i]]][indexing[eCity[i]]] = mCost[i];
	}
	FloydWarshall();

	return city_cnt;
}

void add(int sCity, int eCity, int mCost) {
	if(dist[indexing[sCity]][indexing[eCity]] > mCost) {
		dist[indexing[sCity]][indexing[eCity]] = mCost;
		// FloydWarshall();
		for(int s=0; s<city_cnt; s++) {
			for(int e=0; e<city_cnt; e++) {
				dist[s][e] = min(dist[s][e], dist[s][indexing[sCity]] + mCost + dist[indexing[eCity]][e]);
			}
		}
	}
	return;
}

int cost(int mHub) {
	ll ans = 0;
	for(int i=0; i<city_cnt; i++) {
		ans += dist[indexing[mHub]][i] + dist[i][indexing[mHub]];
		// cout << "i: " << i << " mHub: " << indexing[mHub] << endl;
		// cout << dist[indexing[mHub]][i] << " " << dist[i][indexing[mHub]] << " " << dist[indexing[mHub]][i] + dist[i][indexing[mHub]] << endl;
		// cout << endl;
	}
	return ans;
}