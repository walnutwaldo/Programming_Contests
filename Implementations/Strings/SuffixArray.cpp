// Naive Algorithm
struct SuffixArray {

    vector<pair<string, int>> suffixArray;

    SuffixArray(string s) {
        string temp = "";
        R0F(i, s.size()) {
            temp = s[i] + temp;
            suffixArray.PB(MP(temp, i));
        }
        sort(suffixArray.begin(), suffixArray.end());
    }

    int lcp(int i, int j) {
        if(i < 0 || i >= suffixArray.size() || j < 0 || j >= suffixArray.size()) return 0;
        string a = suffixArray[i].F;
        string b = suffixArray[j].F;
        int res = 0;
        F0R(p, min(a.size(), b.size())) {
            if(a[p] == b[p]) res++;
            else break;
        }
        return res;
    }
};
