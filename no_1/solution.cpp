#include <iostream>
#include <bits/stdc++.h>

#define MAX_N 1000
#define MAX_M 20
#define MAK_TREASURE 10000 

using namespace std;

struct Result {
    int y, x;
};

int n, m;
Result treasures[MAX_N * MAX_N];
int treasureCount;

void spin(int Pieces[MAX_M][MAX_M], Result& target)
{
    int tmp[MAX_M][MAX_M];
    for(int i = 0; i < m; i++)
    {
        for(int j = 0; j < m; j++)
        {
            tmp[j][m-i-1] = Pieces[i][j];
        }
    }

    for(int i = 0; i < m; i++)
    {
        for(int j = 0; j < m; j++)
        {
            Pieces[i][j] = tmp[i][j];
        }
    }

    int tmp_y = target.y;
    target.y = target.x;
    target.x = m - tmp_y - 1;
}

int MAP[MAX_N][MAX_N];

void init(int N, int M, int Map[MAX_N][MAX_N])
{
    n = N;
    m = M;
    treasureCount = 0; // Initialize treasure count
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
    Result res;
    res.y = res.x = 0;

    Result target;

    for(int i = 0; i < m; i++)
    {
        for(int j = 0; j < m; j++)
        {
            if(Pieces[i][j] == 9)
            {
                target.y = i;
                target.x = j;
                break;
            }
        }
    }

    for(int s=0; s<4; s++) {//rotate
        if(s>0) spin(Pieces, target);
        bool check = true;
        for (int t = 0; t < treasureCount; t++) {//check all possible position of the map
            check = true;
            Result p = treasures[t];
            if(MAP[p.y][p.x] != 1) continue;
            if(p.y - target.y < 0 || p.x - target.x < 0 || p.y - target.y + m > n || p.x - target.x + m > n) continue;
            for(int i = 0; i < m; i++)
            {
                for(int j = 0; j < m; j++)
                {
                    if(Pieces[i][j] == 1 && MAP[p.y - target.y + i][p.x - target.x + j] != 1)
                    {
                        check = false;
                        break;
                    }
                }
                if(!check) 
                {
                    break;
                }
            }
            if(check)
            {
                for(int i = 0; i < m; i++)
                {
                    for(int j = 0; j < m; j++)
                    {
                        if(Pieces[i][j] == 1) MAP[p.y - target.y + i][p.x - target.x + j] = 0;
                    }
                }
                res = p;
                return res;
            }
        }
    }
	return res;
}