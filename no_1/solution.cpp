#include <iostream>
#include <bits/stdc++.h>

#define MAX_N 1000
#define MAX_M 20
#define MAX_TREASURE 10000
#define MAX_P_TREASURE 20

using namespace std;

struct Result {
    int y, x;
};

int n, m;
Result treasures[MAX_TREASURE];
int treasureCount;
Result target;
Result p_treasure[MAX_P_TREASURE];
int p_treasureCount;
Result p;
Result q;
bool check_000;
bool check_090;
bool check_180;
bool check_270;

int MAP[MAX_N][MAX_N];

void init(int N, int M, int Map[MAX_N][MAX_N])
{
    n = N;
    m = M;
    treasureCount = 0;
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < N; j++)
        {
            MAP[i][j] = Map[i][j];
            if(Map[i][j] == 1) treasures[treasureCount++] = {i, j};
        }
    }
}

Result findTreasureChest(int Pieces[MAX_M][MAX_M])
{
    Result res = {0,0};
    p_treasureCount = 0;

    for(int i = 0; i < m; i++)
    {
        for(int j = 0; j < m; j++)
        {
            if(Pieces[i][j] == 9) target = {i, j};
            else if(Pieces[i][j] == 1) p_treasure[p_treasureCount++] = {i, j};
        }
    }

    for(int t=0; t<treasureCount; t++) {
        p = treasures[t];
        if(MAP[p.y][p.x] != 1) continue;
        check_000 = true;
        check_090 = true;
        check_180 = true;
        check_270 = true;
        for(int pt=0; pt<p_treasureCount; pt++) {
            q = p_treasure[pt];
            if(check_000) {
                if(p.y - target.y + q.y < 0 || p.x - target.x + q.x < 0 || p.y - target.y + q.y >= n || p.x - target.x + q.x >= n) {
                    check_000 = false;
                }
                else if(MAP[p.y - target.y + q.y][p.x - target.x + q.x] != 1) {
                    check_000 = false;
                }
            }
            if(check_090) {
                if(p.y - target.x + q.x < 0 || p.x + target.y - q.y < 0 || p.y - target.x + q.x >= n || p.x + target.y - q.y >= n) {
                    check_090 = false;
                }
                else if(MAP[p.y - target.x + q.x][p.x + target.y - q.y] != 1) {
                    check_090 = false;
                }
            }
            if(check_180) {
                if(p.y + target.y - q.y < 0 || p.x + target.x - q.x < 0 || p.y + target.y - q.y >= n || p.x + target.x - q.x >= n) {
                    check_180 = false;
                }
                else if(MAP[p.y + target.y - q.y][p.x + target.x - q.x] != 1) {
                    check_180 = false;
                }
            }
            if(check_270) {
                if(p.y + target.x - q.x < 0 || p.x - target.y + q.y < 0 || p.y + target.x - q.x >= n || p.x - target.y + q.y >= n) {
                    check_270 = false;
                }
                else if(MAP[p.y + target.x - q.x][p.x - target.y + q.y] != 1) {
                    check_270 = false;
                }
            }
            if(!check_000 && !check_090 && !check_180 && !check_270) break;
        }
        
        if(check_000) {
            for(int pt=0; pt<p_treasureCount; pt++) {
                q = p_treasure[pt];
                MAP[p.y - target.y + q.y][p.x - target.x + q.x] = 0;
            }
            MAP[p.y][p.x] = 0;
            res = p;
            break;
        }
        else if(check_090) {
            for(int pt=0; pt<p_treasureCount; pt++) {
                q = p_treasure[pt];
                MAP[p.y - target.x + q.x][p.x + target.y - q.y] = 0;
            }
            MAP[p.y][p.x] = 0;
            res = p;
            break;
        }
        else if(check_180) {
            for(int pt=0; pt<p_treasureCount; pt++) {
                q = p_treasure[pt];
                MAP[p.y + target.y - q.y][p.x + target.x - q.x] = 0;
            }
            MAP[p.y][p.x] = 0;
            res = p;
            break;
        }
        else if(check_270) {
            for(int pt=0; pt<p_treasureCount; pt++) {
                q = p_treasure[pt];
                MAP[p.y + target.x - q.x][p.x - target.y + q.y] = 0;
            }
            MAP[p.y][p.x] = 0;
            res = p;
            break;
        }
    }
	return res;
}