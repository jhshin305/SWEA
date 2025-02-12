#include <bits/stdc++.h>
#define ll long long
#define INF INT_MAX
#define MAX_CITY 600
#define MAX_N 1400

using namespace std;

int n;
int city_cnt;
vector<vector<array<int, 2>>> line(MAX_CITY); // {ecity, cost}
vector<vector<array<int, 2>>> rline(MAX_CITY); // {scity, cost}
map<int, int> indexing;
vector<vector<int>> dist(MAX_CITY, vector<int>(MAX_CITY, INF));

void dijkstra(const int& s) {
	for(int s=0; s<city_cnt; s++) {
		vector<int> d(MAX_CITY, INF);
		d[s] = 0;
		priority_queue<array<int, 2>> pq;
		pq.push({0, s});
		while(!pq.empty()) {
			auto [cost, curr] = pq.top();
			pq.pop();
			if(d[curr] < cost) continue;
			for(auto [next, ncost] : line[curr]) {
				if(d[next] > cost + ncost) {
					d[next] = cost + ncost;
					pq.push({d[next], next});
				}
			}
		}
		for(int e=0; e<city_cnt; e++) {
			dist[s][e] = d[e];
		}
	}
}

int scity;
int ecity;

int init(int N, int sCity[], int eCity[], int mCost[]) {
	n = N;
	city_cnt = 0;
	// indexing = vector<int>(MAX_ADR, -1);
	line = vector<vector<array<int, 2>>>(MAX_CITY);
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
		// dist[indexing[sCity[i]]][indexing[eCity[i]]] = mCost[i];
		line[indexing[sCity[i]]].push_back({indexing[eCity[i]], mCost[i]});
	}

	return city_cnt;
}

void add(int sCity, int eCity, int mCost) {
	// scity = indexing[sCity];
	// ecity = indexing[eCity];
	// if(dist[scity][ecity] > mCost) {
	// 	dist[scity][ecity] = mCost;
	// 	for(int s=0; s<city_cnt; s++) {
	// 		for(int e=0; e<city_cnt; e++) {
	// 			dist[s][e] = min(dist[s][e], dist[s][scity] + mCost + dist[ecity][e]);
	// 		}
	// 	}
	// }
	line[indexing[sCity]].push_back({indexing[eCity], mCost});
	return;
}

int cost(int mHub) {
	ll ans = 0;
	dijkstra(mHub);
	for(int i=0; i<city_cnt; i++) {
		ans += dist[indexing[mHub]][i] + dist[i][indexing[mHub]];
		// cout << "i: " << i << " mHub: " << indexing[mHub] << endl;
		// cout << dist[indexing[mHub]][i] << " " << dist[i][indexing[mHub]] << " " << dist[indexing[mHub]][i] + dist[i][indexing[mHub]] << endl;
		// cout << endl;
	}
	return ans;
}