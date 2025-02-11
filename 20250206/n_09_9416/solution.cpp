#include <bits/stdc++.h>
#define MAX_N 1000
#define MAX_POST 100000

using namespace std;

struct Post {
	int uID, pID, timestamp, like;
};

struct cmpYoung {
	bool operator()(const Post& a, const Post& b) {
		if(a.like != b.like) return a.like < b.like;
		else return a.timestamp < b.timestamp;
	}
};

struct cmpOld {
	bool operator()(const Post& a, const Post& b) {
		return a.timestamp < b.timestamp;
	}
};

int n;
priority_queue<Post, vector<Post>, cmpYoung> youngPosts;
vector<Post> posts(MAX_POST);
int postsCnt;
int curTime;
vector<vector<int>> follow_status(MAX_N+1, vector<int>(MAX_N+1, 0));
int oldIdx;
vector<vector<int>> myPosts(MAX_N+1);
vector<vector<int>> myFoloows(MAX_N+1);

int t;

bool comp(const Post& a, const int & b) {
	return a.timestamp < b;
}

void printPosts() {
	// if(t <= 5) return;
	// cout << "curTime: " << curTime << endl;
	// vector<Post> tmp;
	// cout << "youngPosts" << endl;
	// while(!youngPosts.empty()) {
	// 	Post post = youngPosts.top();
	// 	youngPosts.pop();
	// 	tmp.push_back(post);
	// 	cout << post.uID << " " << post.pID << " " << post.timestamp << " " << post.like << endl;
	// }
	// for(const auto& post : tmp) youngPosts.push(post);
	// // cout << "oldPosts" << endl;
	// // if(!oldPosts.empty()) {
	// // 	tmp.clear();
	// // 	while(!oldPosts.empty()) {
	// // 		Post post = oldPosts.top();
	// // 		oldPosts.pop();
	// // 		tmp.push_back(post);
	// // 		cout << post.uID << " " << post.pID << " " << post.timestamp << " " << post.like << endl;
	// // 	}
	// // 	for(const auto& post : tmp) oldPosts.push(post);
	// // }
	// cout << "posts" << endl;
	// for(int i = 1; i <= postsCnt; i++) {
	// 	cout << posts[i].uID << " " << posts[i].pID << " " << posts[i].timestamp << " " << posts[i].like << endl;
	// }
	// cout << endl;
}

void init(int N)
{
	n = N;
	while(!youngPosts.empty()) youngPosts.pop();
	postsCnt = 0;
	curTime = 0;
	follow_status[0][0]++;
	t = follow_status[0][0];
	oldIdx = 1;
	myPosts = vector<vector<int>>(MAX_N+1);
	myFoloows = vector<vector<int>>(MAX_N+1);
}

void follow(int uID1, int uID2, int timestamp)
{
	follow_status[uID1][uID2] = t;
	myFoloows[uID1].push_back(uID2);
	// curTime = timestamp;
}

void makePost(int uID, int pID, int timestamp)
{	
	// cout << "makePost: " << uID << " " << pID << " " << timestamp << endl;
	youngPosts.push({uID, pID, timestamp, 0});
	posts[pID] = {uID, pID, timestamp, 0};
	postsCnt++;
	myPosts[uID].push_back(pID);
	// curTime = timestamp;
	printPosts();
}

void like(int pID, int timestamp)
{
	// cout << "like: " << pID << " " << timestamp << endl;
	// curTime = timestamp;
	vector<Post> tmp;
	if(timestamp - posts[pID].timestamp <= 1000) {
		posts[pID].like++;
		youngPosts.push(posts[pID]);
	}
	printPosts();
}

void getFeed(int uID, int timestamp, int pIDList[])
{
	// cout << "getFeed: " << uID << " " << timestamp << endl;
	int cnt = 0;
	curTime = timestamp;
	// vector<bool> visited(postsCnt+1, false);
	// vector<Post> tmp;
	// while(!youngPosts.empty()) {
	// 	Post post = youngPosts.top();
	// 	youngPosts.pop();
	// 	if(visited[post.pID]) continue;
	// 	visited[post.pID] = true;
	// 	if(curTime - post.timestamp <= 1000) {
	// 		tmp.push_back(post);
	// 		if(follow_status[uID][post.uID] == t || uID == post.uID) {
	// 			pIDList[cnt++] = post.pID;
	// 			if(cnt == 10) break;
	// 		}
	// 	}
	// }
	// for(const auto& post : tmp) youngPosts.push(post);
	priority_queue<Post, vector<Post>, cmpYoung> tYoungPosts;
	for(auto myPID : myPosts[uID]) {
		if(curTime - posts[myPID].timestamp <= 1000) {
			tYoungPosts.push(posts[myPID]);
		}
	}
	for(auto myFoloow : myFoloows[uID]) {
		for(auto myPID : myPosts[myFoloow]) {
			if(curTime - posts[myPID].timestamp <= 1000) {
				tYoungPosts.push(posts[myPID]);
			}
		}
	}
	while(cnt < 10 && !tYoungPosts.empty()) {
		Post post = tYoungPosts.top();
		tYoungPosts.pop();
		if(follow_status[uID][post.uID] == t || uID == post.uID)
			pIDList[cnt++] = post.pID;
	}
	
	if(cnt < 10) {
		// int left = 1, right = postsCnt;
		// while(left <= right) {
		// 	int mid = (left + right) / 2;
		// 	if(posts[mid].timestamp < curTime - 1000) left = mid + 1;
		// 	else right = mid - 1;
		// }
		int idx = lower_bound(posts.begin()+oldIdx, posts.begin()+postsCnt, curTime - 1000, comp) - posts.begin();
		while(idx>=1 && posts[idx].timestamp >= curTime - 1000) idx--;
		oldIdx = idx;
		while(cnt < 10 && idx >= 1) {
			if(follow_status[uID][posts[idx].uID] == t || uID == posts[idx].uID)
				pIDList[cnt++] = idx;
			idx--;
		}
		// while(cnt < 10 && right >= 1) {
		// 	if(follow_status[uID][posts[right].uID] == t || uID == posts[right].uID)
		// 		pIDList[cnt++] = right;
		// 	right--;
		// }
	}
	printPosts();
}