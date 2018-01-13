namespace FFT {

const int MAX_DEG = 20;
cld FFTBuild[1 << MAX_DEG][2], rt[(1 << MAX_DEG) + 1];

void buildRT() {
    if(rt[0] == cld(1, 0)) return;
    F0R(i, (1 << MAX_DEG) + 1) rt[i] = cld(cos(2 * i * PI / (1 << MAX_DEG)), sin(2 * i * PI / (1 << MAX_DEG)));
}

void fft(int neededDeg, cld* vals, int len) {
    R0F(i, neededDeg + 1) {
        int arr = i & 1, narr = arr ^ 1, lli = 1 << i, llil = lli << 1, llndi = 1 << (neededDeg - i), llndim1 = llndi >> 1, rtp = lli << (MAX_DEG - neededDeg);
        if(i == neededDeg) F0R(j, lli) FFTBuild[j][arr] = (j < len) ? vals[j] : 0;
        else F0R(j, lli) F0R(k, llndi) FFTBuild[j + lli * k][arr] = FFTBuild[j + llil * (k % llndim1)][narr] + FFTBuild[j + lli + llil * (k % llndim1)][narr] * rt[rtp * k];
    }
}

void invfft(int neededDeg, cld* vals, int len) {
    reverse(rt, rt + (1 << MAX_DEG) + 1);
    fft(neededDeg, vals, len);
    reverse(rt, rt + (1 << MAX_DEG) + 1);
    F0R(i, len) FFTBuild[i][0] /= len;
}

};
