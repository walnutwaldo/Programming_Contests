// Naive Algorithm
struct SuffixArray {

    string s;
    vi suffixArray;

    bool lessThan(int i, int j) const {
        F0R(p, s.size() + 1 - max(i, j)) {
            if(s[i + p] < s[j + p]) return 1;
            else if(s[i + p] > s[j + p]) return 0;
        }
        return i > j;
    }

    void merge_sort(int lo, int hi, vi temp) {
        if(hi == lo + 1) return;
        int mid = (lo + hi) >> 1;
        merge_sort(lo, mid, temp);
        merge_sort(mid, hi, temp);
        int i = lo, j = mid;
        while(i < mid || j < hi) {
            if(i == mid || j < hi && lessThan(suffixArray[j], suffixArray[i])) temp[i + j - mid] = suffixArray[j++];
            else temp[i + j - mid] = suffixArray[i++];
        }
        FOR(i, lo, hi) suffixArray[i] = temp[i];
    }

    SuffixArray(string _s) {
        s = _s;
        F0R(i, s.size()) suffixArray.PB(i);
        merge_sort(0, suffixArray.size(), vi(suffixArray.size()));
    }

    int lcp(int i, int j) {
        if(i < 0 || i >= suffixArray.size() || j < 0 || j >= suffixArray.size()) return 0;
        int res = 0;
        F0R(p, s.size() + 1 - max(suffixArray[i], suffixArray[j])) {
            if(s[suffixArray[i] + p] == s[suffixArray[j] + p]) res++;
            else break;
        }
        return res;
    }
};
