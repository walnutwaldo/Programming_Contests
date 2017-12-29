struct SuffixArray {

    vi sa;
    vector<vi> *ss;

    bool is1At(int i, int lps, int bit, bool second) {
        return ss[second][lps][sa[i]] & (1 << bit);
    }

    void radixSort(int lps, int bit, bool second, int lo, int hi) {
        if(hi <= lo + 1) return;
        if(bit == -1) {
            if(!second) radixSort(lps, 30, 1, lo, hi);
            return;
        }
        int split = lo;
        while(split < hi && !is1At(split, lps, bit, second)) split++;
        ROF(i, split + 1, hi) {
            if(!is1At(i, lps, bit, second)) swap(sa[i], sa[split]);
            while(split < hi && !is1At(split, lps, bit, second)) split++;
        }
        radixSort(lps, bit - 1, second, lo, split);
        radixSort(lps, bit - 1, second, split, hi);
    }

    SuffixArray(string s) {
        F0R(i, s.size()) sa.PB(i);
        ss = new vector<vi>[2];
        ss[0] = vector<vi>(), ss[1] = vector<vi>();
        ss[0].PB(vi()), ss[1].PB(vi());
        F0R(i, s.size()) {
            ss[0][0].PB(0);
            ss[1][0].PB(s[i] + 1);
        }
        radixSort(0, 30, 0, 0, sa.size());
        int lps = 1;
        while((1 << lps) < s.size()) {
            int lf = -1, ls = -1, curr = -1;
            ss[0].PB(vi(s.size())), ss[1].PB(vi(s.size()));
            F0R(i, s.size()) {
                if(ss[0][lps - 1][sa[i]] == lf && ss[1][lps - 1][sa[i]] == ls) ss[0][lps][sa[i]] = curr;
                else {
                    ss[0][lps][sa[i]] = ++curr;
                    lf = ss[0][lps - 1][sa[i]], ls = ss[1][lps - 1][sa[i]];
                }
            }
            F0R(i, s.size()) {
                if(i + (1 << (lps - 1)) < s.size()) ss[1][lps][i] = ss[0][lps][i + (1 << (lps - 1))];
                else ss[1][lps][i] = 0;
            }
            radixSort(lps, 30, 0, 0, sa.size());
            lps++;
        }
    }

    int lcp(int i, int j) {
        if(i < 0 || i >= sa.size() || j < 0 || j >= sa.size()) return 0;
        i = sa[i], j = sa[j];
        int cap = sa.size() - max(i, j), res = 0;
        while(cap > 0) {
            int mid = FL2(cap - 1);
            if(ss[0][mid][i + res] == ss[0][mid][j + res] && ss[1][mid][i + res] == ss[1][mid][j + res]) {
                res += (1 << mid);
                cap -= (1 << mid);
            } else cap = (1 << mid) - 1;
        }
        return res;
    }
};
