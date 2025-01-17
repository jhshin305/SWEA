#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>

#define INIT			(100)
#define DROP_BLOCKS		(200)
#define CHANGE_BLOCKS	(300)
#define GET_RESULT		(400)

extern void init(int W, int H);
extern int dropBlocks(int mPlayer, int mCol);
extern int changeBlocks(int mPlayer, int mCol);
extern int getResult(int mBlockCnt[2]);

static bool run()
{
	int Q, W, H;
	
	int mPlayer, mCol;
	
	int ret = -1, ans;
	int mBlockCnt[2] = {};
	int r1, r2;
	
	scanf("%d", &Q);
	
    bool okay = false;
	for (int q = 0; q < Q; ++q)
	{
		// printf("q: %d\n", q);
		int cmd;
		scanf("%d", &cmd);
		switch(cmd)
		{
		case INIT:
			scanf("%d %d", &W, &H);
			init(W, H);
			okay = true;
			break;
		case DROP_BLOCKS:
			scanf("%d %d", &mPlayer, &mCol);
			if (okay)
				ret = dropBlocks(mPlayer, mCol);
			scanf("%d", &ans);
			if (ret != ans)
				okay = false;
			break;
		case CHANGE_BLOCKS:
			scanf("%d %d", &mPlayer, &mCol);
			if (okay)
				ret = changeBlocks(mPlayer, mCol);
			scanf("%d", &ans);
			if (ret != ans)
				okay = false;
			break;
		case GET_RESULT:
			if (okay)
				ret = getResult(mBlockCnt);
			scanf("%d %d %d", &ans, &r1, &r2);
			if (ans != ret || mBlockCnt[0] != r1 || mBlockCnt[1] != r2)
				okay = false;
			break;
		default:
			okay = false;
			break;
		}
	}

    return okay;
}

int main()
{
    setbuf(stdout, NULL);
    freopen("C:/Users/jhshin/Desktop/secret/SWEA/no_2/sample_input_2.txt", "r", stdin);

    int T, MARK;
    scanf("%d%d", &T, &MARK);

    for (int tc = 1; tc <= T; tc++)
    {
        int score = run() ? MARK : 0;
        printf("#%d %d\n", tc, score);
    }

    return 0;
}