#include <bits/stdc++.h>

using namespace std;

#define NAME_MAXLEN 6
#define PATH_MAXLEN 1999

int mstrcmp(const char *a, const char *b)
{
	int i;
	for (i = 0; a[i] != '\0'; i++)
	{
		if (a[i] != b[i])
			return a[i] - b[i];
	}
	return a[i] - b[i];
}

int mstrncmp(const char *a, const char *b, int len)
{
	for (int i = 0; i < len; i++)
	{
		if (a[i] != b[i])
			return a[i] - b[i];
	}
	return 0;
}

int mstrlen(const char *a)
{
	int len = 0;

	while (a[len] != '\0')
		len++;

	return len;
}

void mstrcpy(char *dest, const char *src)
{
	int i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = src[i];
}

void mstrncpy(char *dest, const char *src, int len)
{
	for (int i = 0; i<len; i++)
	{
		dest[i] = src[i];
	}
	dest[len] = '\0';
}

struct Node {
	map<string, Node> child;
	int t_size = 0;
};

map<string, Node> dir;


void init(int n) {
	dir.clear();
	dir["/"];
}

vector<string> getTokens(char path[PATH_MAXLEN + 1]) {
	string p = path;
	istringstream iss(p);
	string token;
	vector<string> tokens;
	while (getline(iss, token, '/')) {
		tokens.push_back(token);
	}
	return tokens;
}

void cmd_mkdir(char path[PATH_MAXLEN + 1], char name[NAME_MAXLEN + 1]) {
	vector<string> tokens = getTokens(path);
	Node* cur = &dir["/"];
	cur->t_size++;
	for (int i = 1; i < tokens.size(); i++) {
		cur = &cur->child[tokens[i]];
		cur->t_size++;
	}
	cur->child[name];
}

void cmd_rm(char path[PATH_MAXLEN + 1]) {
	vector<string> tokens = getTokens(path);
	Node* src = &dir["/"];
	for(int i = 1; i < tokens.size(); i++) {
		src = &src->child[tokens[i]];
	}
	int t_size = src->t_size+1;
	src = &dir["/"];
	src->t_size -= t_size;
	for(int i = 1; i < tokens.size()-1; i++) {
		src = &src->child[tokens[i]];
		src->t_size -= t_size;
	}
	src->child.erase(tokens.back());
}

void cmd_cp(char srcPath[PATH_MAXLEN + 1], char dstPath[PATH_MAXLEN + 1]) {
	vector<string> srcTokens = getTokens(srcPath);
	vector<string> dstTokens = getTokens(dstPath);
	Node* src = &dir["/"];
	for(int i = 1; i < srcTokens.size(); i++) {
		src = &src->child[srcTokens[i]];
	}
	int t_size = src->t_size+1;
	Node* dst = &dir["/"];
	dst->t_size += t_size;
	for(int i = 1; i < dstTokens.size(); i++) {
		dst = &dst->child[dstTokens[i]];
		dst->t_size += t_size;
	}
	dst->child[srcTokens.back()] = *src;
}

void cmd_mv(char srcPath[PATH_MAXLEN + 1], char dstPath[PATH_MAXLEN + 1]) {
	vector<string> srcTokens = getTokens(srcPath);
	vector<string> dstTokens = getTokens(dstPath);
	Node* src = &dir["/"];
	for(int i = 1; i < srcTokens.size(); i++) {
		src = &src->child[srcTokens[i]];
	}
	int t_size = src->t_size+1;
	src = &dir["/"];
	src->t_size -= t_size;
	for(int i = 1; i < srcTokens.size()-1; i++) {
		src = &src->child[srcTokens[i]];
		src->t_size -= t_size;
	}
	Node* dst = &dir["/"];
	dst->t_size += t_size;
	for(int i = 1; i < dstTokens.size(); i++) {
		dst = &dst->child[dstTokens[i]];
		dst->t_size += t_size;
	}
	
	Node temp = src->child[srcTokens.back()];
	src->child.erase(srcTokens.back());
	dst->child[srcTokens.back()] = temp;
}

int cmd_find(char path[PATH_MAXLEN + 1]) {
	vector<string> tokens = getTokens(path);
	Node* cur = &dir["/"];
	for(int i = 1; i < tokens.size(); i++) {
		cur = &cur->child[tokens[i]];
	}
	return cur->t_size;
}