namespace FFT {

    const int LG_MAXN = 20;
    bool built;
    cld rt[LG_MAXN + 1], invrt[LG_MAXN + 1];

    void buildRT() {
        if(built) return;
        built = 1;
        R0F(i, LG_MAXN + 1) rt[i] = cld(cos(2 * PI / (1 << i)), sin(2 * PI / (1 << i)));
        F0R(i, LG_MAXN + 1) invrt[i] = cld(1, 0) / rt[i];
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

    vector<cld> bitReverseCopy(vector<cld> val) {
        vector<cld> res(val.size());
        F0R(i, val.size()) res[i] = val[rev(i, val.size())];
        return res;
    }

    vector<cld> fft(vector<cld> val) {
        buildRT();
        vector<cld> res = bitReverseCopy(val);
        int n = res.size();
        FOR(i, 1, 32 - __builtin_clz(n)) {
            int m = 1 << i;
            cld wm = rt[i];
            for(int k = 0; k < n; k += m) {
                cld w = 1;
                F0R(j, m >> 1) {
                    cld t = w * res[k + j + (m >> 1)];
                    cld u = res[k + j];
                    res[k + j] = u + t;
                    res[k + j + (m >> 1)] = u - t;
                    w *= wm;
                }
            }
        }
        return res;
    }

    vector<cld> invfft(vector<cld> val) {
        swap(rt, invrt);
        vector<cld> res = fft(val);
        swap(rt, invrt);
        ld u = 1.0 / val.size();
        F0R(i, res.size()) res[i] *= u;
        return res;
    }

    vector<cld> conv(vector<cld> a, vector<cld> b) {
        int finalSZ = a.size() + b.size() - 1;
        int neededSZ = 1 << (32 - __builtin_clz(finalSZ - 1));
        a.resize(neededSZ), b.resize(neededSZ);
        a = fft(a), b = fft(b);
        F0R(i, neededSZ) a[i] *= b[i];
        a = invfft(a);
        a.resize(finalSZ);
        return a;
    }

};
