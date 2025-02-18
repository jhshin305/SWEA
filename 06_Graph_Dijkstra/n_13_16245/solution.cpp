#include <bits/stdc++.h>
#define ll long long
#define INF INT_MAX
#define MAX_CITY 601

using namespace std;

int city_cnt;
vector<array<int, 2>> line[MAX_CITY]; // {ecity, cost}
vector<array<int, 2>> rline[MAX_CITY]; // {scity, cost}
int dist[MAX_CITY][MAX_CITY];
priority_queue<array<int, 2>, vector<array<int,2>>, greater<>> pq;

void dijkstra(const int& s) {
	for(int i=0; i<city_cnt; i++) {
		dist[s][i] = INF;
		dist[i][s] = INF;
	}
	dist[s][s] = 0;
	pq.push({0, s});
	while(!pq.empty()) {
		auto [cost, curr] = pq.top();
		pq.pop();
		if(dist[s][curr] != cost) continue;
		for(auto [next, ncost] : line[curr]) {
			if(dist[s][next] > cost + ncost) {
				dist[s][next] = cost + ncost;
				pq.push({dist[s][next], next});
			}
		}
	}
	pq.push({0, s});
	while(!pq.empty()) {
		auto [cost, curr] = pq.top();
		pq.pop();
		if(dist[curr][s] != cost) continue;
		for(auto [next, ncost] : rline[curr]) {
			if(dist[next][s] > cost + ncost) {
				dist[next][s] = cost + ncost;
				pq.push({dist[next][s], next});
			}
		}
	}
}

vector<int> cityMap;

int findIdx(const int& x) {
	return lower_bound(cityMap.begin(), cityMap.end(), x) - cityMap.begin();
}

int init(int N, int sCity[], int eCity[], int mCost[]) {
	cityMap.clear();
	for(int i=0; i<N; i++) {
		cityMap.push_back(sCity[i]);
		cityMap.push_back(eCity[i]);
	}
	sort(cityMap.begin(), cityMap.end());
	cityMap.erase(unique(cityMap.begin(), cityMap.end()), cityMap.end());
	city_cnt = cityMap.size();
	for(int i=0; i<city_cnt; i++) {
		line[i].clear();
		rline[i].clear();
	}
	for(int i = 0; i < N; i++) {
		sCity[i] = findIdx(sCity[i]);
		eCity[i] = findIdx(eCity[i]);
		line[sCity[i]].push_back({eCity[i], mCost[i]});
		rline[eCity[i]].push_back({sCity[i], mCost[i]});
	}

	return city_cnt;
}

void add(int sCity, int eCity, int mCost) {
	sCity = findIdx(sCity);
	eCity = findIdx(eCity);
	line[sCity].push_back({eCity, mCost});
	rline[eCity].push_back({sCity, mCost});
	return;
}

int cost(int mHub) {
	ll ans = 0;
	int s = findIdx(mHub);
	dijkstra(s);
	for(int i=0; i<city_cnt; i++) {
		ans += dist[s][i] + dist[i][s];
	}
	return ans;
}