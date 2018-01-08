ull NTTMod = (33ULL << 25) + 1, NTTBuild[1 << 19][2], tempPVPoly[1 << 19], rt[(1 << 19) + 1];

struct Polynomial {

    int deg;
    ull *coefficients;

    static ull modPow(ull a, ull p) {
        if(!p) return 1;
        if(p & 1) return a * modPow(a, p ^ 1) % NTTMod;
        ull sqrt = modPow(a, p >> 1);
        return SQ(sqrt) % NTTMod;
    }

    static void buildRT() {
        if(rt[0] == 1) return;
        rt[0] = 1;
        rt[1] = modPow(5, 33ULL << 6);
        FOR(i, 2, (1 << 19) + 1) rt[i] = rt[i - 1] * rt[1] % NTTMod;
    }

    Polynomial(int d) {
        deg = d;
        coefficients = new ull[deg + 1];
        memset(coefficients, 0, (deg + 1) * sizeof(ull));
        buildRT();
    }

    void NTT(int neededDeg) {
        R0F(i, neededDeg + 1) {
            int arr = i & 1, narr = arr ^ 1, lli = 1 << i, llil = lli << 1, llndim1 = 1 << (neededDeg - i - 1), rtp = lli << (19 - neededDeg);
            if(i == neededDeg) {
                F0R(j, deg + 1) NTTBuild[j][arr] = coefficients[j];
                FOR(j, deg + 1, lli) NTTBuild[j][arr] = 0;
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

    static void invNTT(ull *p, int pdeg) {
        int mp = 1 << 19;
        ull u = modPow(1 << pdeg, NTTMod - 2);
        R0F(i, pdeg + 1) {
            int arr = i & 1, narr = arr ^ 1, lli = 1 << i, llil = lli << 1, llpdim1 = 1 << (pdeg - i - 1), rtp = lli << (19 - pdeg);
            R0F(j, lli) {
                if(i == pdeg) NTTBuild[j][arr] = p[j] * u % NTTMod;
                else {
                    int x = j, y = mp, z = j, w = lli + j;
                    F0R(k, llpdim1) {
                        NTTBuild[x][arr] = (NTTBuild[z][narr] + NTTBuild[w][narr] * rt[y]) % NTTMod;
                        x += lli, y -= rtp, z += llil, w += llil;
                    }
                    z = j, w = lli + j;
                    F0R(k, llpdim1) {
                        NTTBuild[x][arr] = (NTTBuild[z][narr] + NTTBuild[w][narr] * rt[y]) % NTTMod;
                        x += lli, y -= rtp, z += llil, w += llil;
                    }
                }
            }
        }
    }

    Polynomial operator +(Polynomial b) {
        Polynomial res(max(deg, b.deg));
        FOR(i, min(deg, b.deg) + 1, max(deg, b.deg) + 1) res.coefficients[i] = ((i <= deg) ? coefficients[i] : b.coefficients[i]);
        F0R(i, min(deg, b.deg) + 1) res.coefficients[i] = coefficients[i] + b.coefficients[i];
        return res;
    }

    Polynomial operator *(Polynomial b) {
        int neededDeg = 32 - __builtin_clz(deg + b.deg);
        NTT(neededDeg);
        F0R(i, (1 << neededDeg)) tempPVPoly[i] = NTTBuild[i][0];
        b.NTT(neededDeg);
        F0R(i, (1 << neededDeg)) tempPVPoly[i] = tempPVPoly[i] * NTTBuild[i][0] % NTTMod;
        invNTT(tempPVPoly, neededDeg);
        Polynomial res(deg + b.deg);
        F0R(i, res.deg + 1) res.coefficients[i] = NTTBuild[i][0];
        return res;
    }

    void operator +=(Polynomial b) {
        *this = *this + b;
    }

    void operator *=(Polynomial b) {
        *this = *this * b;
    }

};
