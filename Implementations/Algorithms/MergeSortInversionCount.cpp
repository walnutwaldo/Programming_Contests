int msInversion(int *a, int lo, int hi) {
    if(hi <= lo + 1) return 0;
    int mid = (lo + hi) >> 1;
    int res = msInversion(a, lo, mid) + msInversion(a, mid, hi);
    int *L = new int[mid - lo], *R = new int[hi - mid];
    copy(a + lo, a + mid, L), copy(a + mid, a + hi, R);
    int i = 0, j = 0;
    while(i < mid - lo || j < hi - mid) {
        if(j == hi - mid || i < mid - lo && L[i] <= R[j]) {
            res += j;
            a[lo + i + j] = L[i++];
        } else a[lo + i + j] = R[j++];
    }
    return res;
}

int countInversions(int *a, int sz) {
    int *b = new int[sz];
    copy(a, a + sz, b);
    return msInversion(b, 0, sz);
}
