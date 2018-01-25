// Uses RUSQ.cpp
// https://github.com/walnutwaldo/Programming_Contests/blob/master/Implementations/Data%20Structures/Range%20Queries/Binary%20Indexed%20Trees/RUSQ.cpp

struct MergeSortTree {

    int s, e, *arr, *lPos, *rPos;
    RUSQ *val;
    MergeSortTree *lChild = NULL, *rChild = NULL;

    MergeSortTree(int sz, int* a) {
        s = 0, e = sz;
        buildTree(a);
    }

    MergeSortTree(int ss, int ee, int* a) {
        s = ss, e = ee;
        buildTree(a);
    }

    void buildTree(int* a) {
        val = new RUSQ(e - s);
        if(e == s + 1) arr = new int[1] {a[s]};
        else {
            int mid = (s + e) >> 1;
            lChild = new MergeSortTree(s, mid, a);
            rChild = new MergeSortTree(mid, e, a);
            arr = new int[e - s], lPos = new int[mid - s], rPos = new int[e - mid];
            int i = 0, j = 0;
            while(i < mid - s || j < e - mid) {
                if(i == mid - s || j < e - mid && rChild->arr[j] < lChild->arr[i]) {
                    rPos[j] = i + j;
                    arr[i + j] = rChild->arr[j++];
                } else {
                    lPos[i] = i + j;
                    arr[i + j] = lChild->arr[i++];
                }
            }
        }
    }

    void update(int lo, int hi, int cap, int inc) {
        if(hi <= s || lo >= e) return;
        if(s >= lo && e <= hi) {
            int pos = UB(arr, arr + e - s, cap) - arr;
            if(pos > 0) val->updateRange(0, pos - 1, inc);
        } else {
            lChild->update(lo, hi, cap, inc);
            rChild->update(lo, hi, cap, inc);
        }
    }

    int query(int i) {
        return valAndPos(i).F;
    }

    pii valAndPos(int i) {
        if(s == i && e == i + 1) return MP(val->query(0), 0);
        else {
            int mid = (s + e) >> 1;
            pii res;
            if(i < mid) {
                res = lChild->valAndPos(i);
                res.S = lPos[res.S];
            } else {
                res = rChild->valAndPos(i);
                res.S = rPos[res.S];
            }
            res.F += val->query(res.S);
            return res;
        }
    }

};
