namespace FFT {
	
	const int LG_MAXN = 22;
	bool builtRT;
	cld rt[LG_MAXN + 1], invrt[LG_MAXN + 1];

	void buildRT() {
		if(builtRT) return;
		builtRT = 1;
		F0R(i, LG_MAXN + 1) rt[i] = cld(cos(2 * PI / (1 << i)), sin(2 * PI / (1 << i)));
		F0R(i, LG_MAXN + 1) invrt[i] = cld(1, 0) / rt[i];
	}

	int rev(int x, int numBits) {
		int res = 0;
		F0R(i, numBits) if(x & (1 << i)) res |= (1 << (numBits - 1 - i));
		return res;
	}

	vcld bitRevCopy(vcld v) {
		vcld res(sz(v));
		F0R(i, sz(v)) res[i] = v[rev(i, 31 - __builtin_clz(sz(v)))];
		return res;
	}

	vcld fft(vcld v) {
		buildRT();
		vcld res = bitRevCopy(v);
		int n = sz(res);
		F0R(i, 32 - __builtin_clz(n)) {
			int step = 1 << i;
			cld root = rt[i];
			for(int k = 0; k < n; k += step) {
				cld currMult(1, 0);
				F0R(j, step >> 1) {
					cld t = currMult * res[k + j + (step >> 1)];
					cld u = res[k + j];
					res[k + j] = u + t;
					res[k + j + (step >> 1)] = u - t;
					currMult *= root;
				}
			}
		}
		return res;
	}

	vcld invfft(vcld v) {
		swap(rt, invrt);
		vcld res = fft(v);
		swap(rt, invrt);
		ld u = 1.0 / sz(v);
		F0R(i, sz(res)) res[i] *= u;
		return res;
	}

	vcld conv(vcld a, vcld b) {
		int finalSize = sz(a) + sz(b) - 1;
		int neededSize = (finalSize == 1)?1 : (1 << (32 - __builtin_clz(finalSize - 1)));
		a.resize(neededSize), b.resize(neededSize);
		a = fft(a), b = fft(b);
		F0R(i, neededSize) a[i] *= b[i];
		a = invfft(a);
		a.resize(finalSize);
		return a;
	}

};
