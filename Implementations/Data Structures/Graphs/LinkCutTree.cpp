struct SplayTree {

	int val, sz;
	SplayTree *left = nullptr, *right = nullptr, *par = nullptr;

	SplayTree(int val = 0) {
		this->val = val;
		sz = 1;
	}

	void upd() {
		sz = 1;
		if(left != nullptr) {
			left->par = this;
			sz += left->sz;
		}
		if(right != nullptr) {
			right->par = this;
			sz += right->sz;
		}
	}

	void rot() {
		if(par == nullptr) return;
		SplayTree* gpar = par->par;
		if (gpar != nullptr && gpar->left == par) gpar->left = this;
		else if(gpar != nullptr) gpar->right = this;
		if(par->left == this) {
			par->left = this->right;
			this->right = par;
		} else {
			par->right = this->left;
			this->left = par;
		}
		par->upd();
		upd();
		par = gpar;
	}

	void splay() {
		while(par != nullptr) {
			SplayTree* gpar = par->par;
			if(gpar != nullptr) {
				if ((gpar->left == par) == (par->left == this)) par->rot();
				else rot();
			}
			rot();
		}
	}

	SplayTree* getOrder(int k) {
		int lsize = (left == nullptr)?0:left->sz;
		if(k == lsize) {
			splay();
			return this;
		} else if(k < lsize + 1) return left->getOrder(k);
		else return right->getOrder(k - lsize - 1);
	}

	void mergeRight(SplayTree* st) {
		splay();
		st->splay();
		this->right = st;
		upd();
	}

};

struct LinkCutTree {

	int *par;
	SplayTree *st;

	LinkCutTree(int sz) {
		par = new int[sz];
		F0R(i, sz) par[i] = -1;
		st = new SplayTree[sz];
		F0R(i, sz) st[i] = SplayTree(i);
	}

	void cutout(int v) {
		st[v].splay();
		if(st[v].right != nullptr) par[st[v].right->getOrder(0)->val] = v;
		st[v].splay();
		if(st[v].right != nullptr) st[v].right->par = nullptr;
		st[v].right = nullptr;
		st[v].upd();
	}

	int getVal(SplayTree* st) {
		if(st == nullptr) return -1;
		return st->val;
	}

	void expose(int v) {
		cutout(v);
		v = st[v].getOrder(0)->val;
		while(par[v] != -1) {
			cutout(par[v]);
			st[par[v]].mergeRight(&st[v]);
			par[v] = -1;
			st[v].splay();
			v = st[v].getOrder(0)->val;
		}
	}

	int depth(int v) {
		expose(v);
		st[v].splay();
		return st[v].sz - 1;
	}

	int find_root(int v) {
		expose(v);
		st[v].splay();
		return st[v].getOrder(0)->val;
	}

	void link(int u, int v) {
		if (u == v || depth(u) != 0 || find_root(v) == u) return;
		par[u] = v;
		expose(u);
	}

	void cut(int u, int v) {
		expose(v);
		par[u] = -1;
		expose(u);
	}
	
	int rise(int v, int amt) {
		expose(v);
		st[v].splay();
		return st[v].getOrder(st[v].sz - 1 - amt)->val;
	}

};
