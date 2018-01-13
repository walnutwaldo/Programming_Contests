namespace NTT {

const int MAX_DEG = 5, EXP_MULT = 119ULL, EXP = 23;
ull NTTMod = (EXP_MULT << EXP) + 1, NTTBuild[1 << MAX_DEG][2], rt[(1 << MAX_DEG) + 1];

ull modPow(ull a, ull p) {
    if(!p) return 1;
    if(p & 1) return a * modPow(a, p ^ 1) % NTTMod;
    ull sqrt = modPow(a, p >> 1);
    return SQ(sqrt) % NTTMod;
}

ull invMod(ull a) {
    return modPow(a, NTTMod - 2);
}

ull findCyclic() {
    vi multFactors;
    ull temp = EXP_MULT;
    for(int i = 2; i * i <= temp; i += 2) {
        if(temp % i == 0) multFactors.PB(i);
        while(temp % i == 0) temp /= i;
        if(i == 2) i--;
    }
    if(temp > 1) multFactors.PB(temp);
    FOR(i, 2, NTTMod) {
        bool works = 1;
        if(modPow(i, NTTMod >> 1) == 1) works = 0;
        for(const int factor : multFactors) if(modPow(i, NTTMod / factor) == 1) works = 0;
        if(works) return i;
    }
}

void buildRT() {
    if(rt[0] == 1) return;
    rt[0] = 1;
    rt[1] = modPow(findCyclic(), EXP_MULT << (EXP - MAX_DEG));
    FOR(i, 2, (1 << MAX_DEG) + 1) rt[i] = rt[i - 1] * rt[1] % NTTMod;
}

void ntt(int neededDeg, ull* vals, int len) {
    R0F(i, neededDeg + 1) {
        int arr = i & 1, narr = arr ^ 1, lli = 1 << i, llil = lli << 1, llndim1 = 1 << (neededDeg - i - 1), rtp = lli << (MAX_DEG - neededDeg);
        if(i == neededDeg) {
            F0R(j, len) NTTBuild[j][arr] = vals[j];
            FOR(j, len, lli) NTTBuild[j][arr] = 0;
        } else F0R(j, lli) {
            int x = j, y = 0, z = j, w = j + lli;
            F0R(k, llndim1) {
                NTTBuild[x][arr] = (NTTBuild[z][narr] + NTTBuild[w][narr] * rt[y]) % NTTMod;
                x += lli, y += rtp, z += llil, w += llil;
            }
            z = j, w = j + lli;
            F0R(k, llndim1) {
                NTTBuild[x][arr] = (NTTBuild[z][narr] + NTTBuild[w][narr] * rt[y]) % NTTMod;
                x += lli, y += rtp, z += llil, w += llil;
            }
        }
    }
}

void invntt(int neededDeg, ull* vals, int len) {
    reverse(rt, rt + (1 << MAX_DEG) + 1);
    ntt(neededDeg, vals, len);
    reverse(rt, rt + (1 << MAX_DEG) + 1);
    ull u = invMod(len);
    F0R(i, len) NTTBuild[i][0] *= u, NTTBuild[i][0] %= NTTMod;
}

};

using namespace NTT;
