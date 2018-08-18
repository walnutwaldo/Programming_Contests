namespace NTT {

    const int EXP = 23;
    const ull EXP_MULT = 119, NTT_MOD = (EXP_MULT << EXP) + 1;
    bool built;
    ull rt[EXP + 1], invrt[EXP + 1];

    ull modPow(ull a, ull p) { return p ? modPow(SQ(a) % NTT_MOD, p >> 1) * (p & 1 ? a : 1) % NTT_MOD : 1; }

    ull invMod(ull a) { return modPow(a, NTT_MOD - 2); }

    ull findCyclic() {
        vul multFactors;
        ull temp = EXP_MULT;
        for(ll i = 2; i * i <= temp; i += 2) {
            if(temp % i == 0) multFactors.PB(i);
            while(temp % i == 0) temp /= i;
            if(i == 2) i--;
        }
        if(temp > 1) multFactors.PB(temp);
        for(ll i = 2; i < NTT_MOD; i++) {
            bool works = 1;
            if(modPow(i, NTT_MOD >> 1) == 1) works = 0;
            for(const int factor : multFactors) if(modPow(i, NTT_MOD / factor) == 1) works = 0;
            if(works) return i;
        }
    }

    void buildRT() {
        if(built) return;
        built = 1;
        rt[EXP] = modPow(findCyclic(), EXP_MULT);
        R0F(i, EXP) rt[i] = SQ(rt[i + 1]) % NTT_MOD;
        F0R(i, EXP + 1) invrt[i] = invMod(rt[i]);
    }

    int rev(int idx, int sz) {
        int tmp = 1, res = 0;
        sz >>= 1;
        while(sz) {
            if(sz & idx) res |= tmp;
            sz >>= 1;
            tmp <<= 1;
        }
        return res;
    }

    vul bitReverseCopy(vul val) {
        vul res(val.size());
        F0R(i, val.size()) res[i] = val[rev(i, val.size())];
        return res;
    }

    vul ntt(vul val) {
        buildRT();
        vul res = bitReverseCopy(val);
        int n = res.size();
        FOR(i, 1, 32 - __builtin_clz(n)) {
            int m = 1 << i;
            ull wm = rt[i];
            for(int k = 0; k < n; k += m) {
                ull w = 1;
                F0R(j, m >> 1) {
                    ull t = w * res[k + j + (m >> 1)] % NTT_MOD;
                    ull u = res[k + j];
                    res[k + j] = (u + t) % NTT_MOD;
                    res[k + j + (m >> 1)] = (u + NTT_MOD - t) % NTT_MOD;
                    w = (w * wm) % NTT_MOD;
                }
            }
        }
        return res;
    }

    vul invntt(vul val) {
        swap(rt, invrt);
        vul res = ntt(val);
        swap(rt, invrt);
        ull u = invMod(val.size());
        F0R(i, res.size()) res[i] = (res[i] * u) % NTT_MOD;
        return res;
    }

    vul conv(vul a, vul b) {
        int finalSZ = a.size() + b.size() - 1;
        int neededSZ = 1 << (32 - __builtin_clz(finalSZ - 1));
        a.resize(neededSZ), b.resize(neededSZ);
        a = ntt(a), b = ntt(b);
        F0R(i, neededSZ) a[i] = a[i] * b[i] % NTT_MOD;
        a = invntt(a);
        a.resize(finalSZ);
        return a;
    }

};
