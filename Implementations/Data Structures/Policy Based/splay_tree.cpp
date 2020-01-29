struct splay_tree {
    
    struct node {
        
        int v;
        int subsize;
        node *l, *r, *p;
        
        node(int v) : v(v), subsize(1), l(nullptr), r(nullptr), p(nullptr) {}
        
    };
    
    node *root = nullptr;
    
    void upd(node *st) {
        st->subsize = 1;
        if (st->l) { st->l->p = st; st->subsize += st->l->subsize; }
        if (st->r) { st->r->p = st; st->subsize += st->r->subsize; }
    }
    
    void rotate(node *st) {
        node *par = st->p;
        node *gpar = par->p;
        if (gpar) {
            if (gpar->l == par) { gpar->l = st; } else { gpar->r = st; }
        }
        if (par->l == st) { par->l = st->r; st->r = par; } else{ par->r = st->l; st->l = par; }
        upd(par);
        upd(st);
        st->p = gpar;
    }
    
    node *splay(node *st) {
        while (st->p) {
            node *par = st->p;
            node *gpar = par->p;
            if (gpar) {
                if ((gpar->l == par) == (par->l == st)) { rotate(par); } else { rotate(st);  }
            }
            rotate(st);
        }
        return root = st;
    }
    
    node *insert(node *st, int v) {
        if (!st) { return root = new node(v); }
        if (v < st->v) {
            if (st->l == nullptr) {
                st->l = new node(v);
                upd(st);
                return splay(st->l);
            } else {
                return insert(st->l, v);
            }
        } else if (v > st->v) {
            if (st->r == nullptr) {
                st->r = new node(v);
                upd(st);
                return splay(st->r);
            } else {
                return insert(st->r, v);
            }
        } else{ return splay(st); }
    }
    
    node *insert(int v) { return insert(root, v); }
    
    node *find_by_value(node *st, int v) {
        if (st == nullptr) { return nullptr; }
        if (v < st->v) { return find_by_value(st->l, v); } else if (v == st->v) { return splay(st); } else{ return find_by_value(st->r, v); }
    }
    
    node *find_by_value(int v) { return find_by_value(root, v); }
    
    node *find_by_order(node *st, int o) {
        if (st == nullptr) { return nullptr; }
        int inLeft = (st->l) ? st->l->subsize : 0;
        if (o < inLeft) {
            return find_by_order(st->l, o);
        } else if (o == inLeft) {
            return splay(st);
        } else {
            return find_by_order(st->r, o - inLeft - 1);
        }
    }
    
    node *find_by_order(int o) { return find_by_order(root, o); }
    
    node *erase(int v, node *st) {
        st = find_by_value(st, v);
        if (st == nullptr) { return nullptr; }
        node *l = st->l, *r = st->r;
        delete st;
        if (l) { l->p = nullptr; }
        if (r) { r->p = nullptr; }
        if (!r) { return root = l; } else {
            r = find_by_order(r, 0);
            r->l = l;
            return root = r;
        }
    }
    
    node *erase(int v) { return erase(v, root); }
    
}
