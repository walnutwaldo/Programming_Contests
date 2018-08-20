#include "grader.h"
#include <bits/stdc++.h>

#define SQ(a) (a)*(a)

#define F0R(i, a) for(int i = 0; i < (a); i++)
#define FOR(i, a, b) for(int i = (a); i < (b); i++)
#define R0F(i, a) for(int i = (a) - 1; i >= 0; i--)
#define ROF(i, a, b) for(int i = (b) - 1; i >= (a); i--)

#define ran() (rand() & 0x7FFF)
#define rand31() ((ran() << 16) | (ran() << 1) | (ran() & 1))
#define rand32() ((ran() << 17) | (ran() << 2) | (ran() & 3))
#define rand63() (((ll)ran() << 48) | ((ll)ran() << 33) | ((ll)ran() << 18) | ((ll)ran() << 3) | ((ll)ran() & 7))
#define rand64() (((ll)ran() << 49) | ((ll)ran() << 34) | ((ll)ran() << 19) | ((ll)ran() << 4) | ((ll)ran() & 15))

#define F first
#define S second
#define PB push_back
#define MP std::make_pair
#define MT make_tuple
#define UB upper_bound
#define LB lower_bound
#define X real()
#define Y imag()
#define BLOCK 1000
#define BLOCKED_WINDOW (BLOCK * (K / BLOCK))
#define BLOCK_NUM 5497
#define NUM_SHOUTS 5496
#define NUM_SOLVED 5495
#define LO 5498
#define HI 5499
#define NUM_BLOCKS 1 + ((N - 1) / BLOCK)

#define N (getTrainLength())
#define K (getWindowLength())
#define idx (getCurrentCarIndex())
#define pass (getCurrentPassIndex())

typedef std::pair<int, int> pii;

void tryMin(int entry, int val, int corrIdx) {
	int valSpot = 2 * entry;
	int idxSpot = valSpot + 1;
	int valAt = get(valSpot);
	if(valAt == -1 || valAt > val) {
		set(valSpot, val);
		set(idxSpot, corrIdx);
	}
}

void wipe(int lo, int hi) { FOR(i, lo, hi) set(i, -1); }

void morning(int val) {
	if(idx == 0) wipe(0, 5000);
	if(idx >= BLOCKED_WINDOW && idx % BLOCK < K % BLOCK)
		tryMin((idx - BLOCKED_WINDOW) / BLOCK, val, idx);
	tryMin(1000 + idx / BLOCK, val, idx);
	if(idx == N - 1){
		pii blockMins[1000];
		F0R(i, NUM_BLOCKS) blockMins[i] = MP(get(2000 + 2 * i), get(2001 + 2 * i));
		F0R(j, NUM_BLOCKS) {
			pii minPair = MP(get(2 * j), get(2 * j + 1));
			F0R(i, NUM_BLOCKS)
				if(i >= j && BLOCK * i + BLOCK <= BLOCK * j + K)
					if(blockMins[i] < minPair || minPair.F == -1) minPair = blockMins[i];
			tryMin(j, minPair.F, minPair.S);
		}
	}
}

void shout(int x) {
	int numShouts = get(NUM_SHOUTS);
	if(numShouts < N - K + 1) {
		shoutMinimum(x);
		set(NUM_SHOUTS, numShouts + 1);
	}
}

void updateQueue(int val) {
	int lo = get(LO), hi = get(HI);
	while(hi > lo && get(hi - 2) >= val) hi -= 2;
	if(hi < 4500) {
		set(hi, val);
		set(hi + 1, idx);
		hi += 2;
	}
	set(HI, hi);
}

int getMin(int startIdx) {
	int lo = get(LO);
	while(get(lo + 1) < startIdx) lo += 2;
	int res = get(lo);
	set(LO, lo);
	return res;
}

void afternoon(int val) {
	if(idx < get(1)) return;
	if(idx == get(1)) {
		set(BLOCK_NUM, 0);
		set(LO, 2000);
		set(HI, 2000);
		set(NUM_SOLVED, 0);
	}
	int blockNum = get(BLOCK_NUM);
	int numSolved = get(NUM_SOLVED);
	while(1) {
		updateQueue(val);
		if(numSolved + K - 1 == idx) shout(getMin(numSolved++));
		if(blockNum == NUM_BLOCKS - 1 || idx < get(3 + 2 * blockNum)) break;
		blockNum++;
		while(numSolved < BLOCK * blockNum) shout(getMin(numSolved++));
		set(LO, 2000);
		set(HI, 2000);

	}
	if(idx == N - 1) FOR(i, numSolved, N - K + 1) shout(getMin(i));
	set(NUM_SOLVED, numSolved);
	set(BLOCK_NUM, blockNum);
}

void helpBessie(int val) {
	if(pass == 0)
		morning(val);
	else
		afternoon(val);
}
