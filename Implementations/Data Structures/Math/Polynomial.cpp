// Uses FFT and is correct but is kind of slow.

cld FFTBuild[1 << 19][2], tempPVPoly[1 << 19], rt[1 << 19];

struct Polynomial {

    int deg;
    ll *coefficients;

    static void buildRT() {
        if(rt[0].R == 1) return;
        F0R(i, 1 << 19) rt[i] = cld(cos(2 * i * PI / (1 << 19)), sin(2 * i * PI / (1 << 19)));
    }

    Polynomial(int d) {
        deg = d;
        coefficients = new ll[deg + 1];
        memset(coefficients, 0, (deg + 1) * sizeof(ll));
        buildRT();
    }

    void FFT(int neededDeg) {
        R0F(i, neededDeg + 1) {
            clock_t start = clock();
            int arr = i & 1;
            int narr = arr ^ 1;
            int lli = 1 << i;
            int llil = lli << 1;
            int llndim1 = 1 << (neededDeg - i - 1);
            int rtp = lli << (19 - neededDeg);
            if(i == neededDeg) {
                F0R(j, deg + 1) FFTBuild[j][arr] = coefficients[j];
                FOR(j, deg + 1, lli) FFTBuild[j][arr] = 0;
            } else F0R(j, lli) {
                int x = j, y = 0, z = j, w = j + lli;
                F0R(k, llndim1) {
                    FFTBuild[x][arr] = FFTBuild[z][narr] + FFTBuild[w][narr] * rt[y];
                    x += lli, y += rtp, z += llil, w += llil;
                }
                z = j;
                w = j + lli;
                F0R(k, llndim1) {
                    FFTBuild[x][arr] = FFTBuild[z][narr] + FFTBuild[w][narr] * rt[y];
                    x += lli, y += rtp, z += llil, w += llil;
                }
            }
            cout << "\t\t" << i << ": " << (clock() - start) << endl;
        }
    }

    static void invFFT(cld *p, int pdeg) {
        int mp = 1 << 19;
        cld u = 1 << pdeg;
        R0F(i, pdeg + 1) {
            int arr = i & 1;
            int narr = arr ^ 1;
            int lli = 1 << i;
            int llil = lli << 1;
            int llpdim1 = 1 << (pdeg - i - 1);
            int rtp = lli << (19 - pdeg);
            clock_t start = clock();
            R0F(j, lli) {
                if(i == pdeg) FFTBuild[j][arr] = p[j] / u;
                else {
                    int x = j, y = 0, z = j, w = lli + j;
                    F0R(k, llpdim1) {
                        FFTBuild[x][arr] = FFTBuild[z][narr] + FFTBuild[w][narr] * rt[y];
                        x += lli, y -= rtp, z += llil, w += llil;
                        if(y < 0) y += mp;
                    }
                    z = j;
                    w = lli + j;
                    F0R(k, llpdim1) {
                        FFTBuild[x][arr] = FFTBuild[z][narr] + FFTBuild[w][narr] * rt[y];
                        x += lli, y -= rtp, z += llil, w += llil;
                        if(y < 0) y += mp;
                    }
                }
            }
            cout << i << ": " << (clock() - start) << endl;
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
        FFT(neededDeg);
        F0R(i, (1 << neededDeg)) tempPVPoly[i] = FFTBuild[i][0];
        b.FFT(neededDeg);
        F0R(i, (1 << neededDeg)) tempPVPoly[i] *= FFTBuild[i][0];
        invFFT(tempPVPoly, neededDeg);
        Polynomial res(deg + b.deg);
        F0R(i, res.deg + 1) res.coefficients[i] = (ll)round(FFTBuild[i][0].R);
        return res;
    }

    void operator +=(Polynomial b) {
        *this = *this + b;
    }

    void operator *=(Polynomial b) {
        *this = *this * b;
    }

};