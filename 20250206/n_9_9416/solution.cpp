#include <bits/stdc++.h>
#define MAX_N 1000

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
priority_queue<Post, vector<Post>, cmpOld> oldPosts;
int curTime;
vector<vector<int>> follow_status(MAX_N+1, vector<int>(MAX_N+1, 0));
vector<vector<int>> follow_status_init(MAX_N+1, vector<int>(MAX_N+1, 0));


void printPosts() {
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
	// cout << "oldPosts" << endl;
	// if(!oldPosts.empty()) {
	// 	tmp.clear();
	// 	while(!oldPosts.empty()) {
	// 		Post post = oldPosts.top();
	// 		oldPosts.pop();
	// 		tmp.push_back(post);
	// 		cout << post.uID << " " << post.pID << " " << post.timestamp << " " << post.like << endl;
	// 	}
	// 	for(const auto& post : tmp) oldPosts.push(post);
	// }
	// cout << endl;
}

void init(int N)
{
	n = N;
	while(!youngPosts.empty()) youngPosts.pop();
	while(!oldPosts.empty()) oldPosts.pop();
	curTime = 0;
	follow_status = follow_status_init;
}

void follow(int uID1, int uID2, int timestamp)
{
	follow_status[uID1][uID2] = 1;
	curTime = timestamp;
}

void makePost(int uID, int pID, int timestamp)
{	
	youngPosts.push({uID, pID, timestamp, 0});
	curTime = timestamp;
	printPosts();
}

void like(int pID, int timestamp)
{
	curTime = timestamp;
	vector<Post> tmp;
	bool flag = false;
	while(!youngPosts.empty()) {
		Post post = youngPosts.top();
		youngPosts.pop();
		if(timestamp - post.timestamp <= 1000) {
			tmp.push_back(post);
			if(post.pID == pID) {
				tmp.back().like++;
				flag = true;
				break;
			}
		}			
		else oldPosts.push(post);
	}
	for(const auto& post : tmp) youngPosts.push(post);
	printPosts();
}

void getFeed(int uID, int timestamp, int pIDList[])
{
	int cnt = 0;
	curTime = timestamp;
	vector<Post> tmp;
	while(!youngPosts.empty()) {
		Post post = youngPosts.top();
		youngPosts.pop();
		if(curTime - post.timestamp <= 1000) {
			tmp.push_back(post);
			if(follow_status[uID][post.uID] == 1 || uID == post.uID) {
				pIDList[cnt++] = post.pID;
				if(cnt == 10) break;
			}
		}
		else oldPosts.push(post);
	}
	for(const auto& post : tmp) youngPosts.push(post);
	if(cnt < 10) {
		tmp.clear();
		while(!oldPosts.empty()) {
			Post post = oldPosts.top();
			oldPosts.pop();
			tmp.push_back(post);
			if(follow_status[uID][post.uID] == 1 || uID == post.uID) {
				pIDList[cnt++] = post.pID;
				if(cnt == 10) break;
			}
		}
		for(const auto& post : tmp) oldPosts.push(post);
	}
	printPosts();
}