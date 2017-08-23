struct TreapNode {

    ll val, priority;
    int id;
    TreapNode *parent = NULL, *lChild = NULL, *rChild = NULL;

    TreapNode(int id, ll val, ll priority) {
        this->id = id;
        this->val = val;
        this->priority = priority;
    }

};

struct Treap {

    unordered_map<int, TreapNode*> idMap;
    TreapNode *root = NULL;

    void lFlip(TreapNode* parent, TreapNode* child) {
        if(parent->parent != NULL) {
            if(parent == parent->parent->lChild) parent->parent->lChild = child;
            else parent->parent->rChild = child;
        } else root = child;
        parent->lChild = child->rChild;
        child->rChild = parent;
    }

    void rFlip(TreapNode* parent, TreapNode* child) {
        if(parent->parent != NULL) {
            if(parent == parent->parent->lChild) parent->parent->lChild = child;
            else parent->parent->rChild = child;
        } else root = child;
        parent->rChild = child->lChild;
        child->lChild = parent;
    }

    void swapWithChild(TreapNode* parent) {
        if(parent->lChild == NULL || parent->rChild->priority > parent->lChild->priority) {
            TreapNode* child = parent->rChild;
            child->parent = parent->parent;
            if(child->parent == NULL) root = child;
            else if(child->parent->lChild == parent) child->parent->lChild = child;
            else child->parent->rChild = child;
            parent->rChild = child->rChild;
            if(parent->rChild != NULL) parent->rChild->parent = parent;
            child->rChild = parent;
            parent->parent = child;
            TreapNode* temp = child->lChild;
            child->lChild = parent->lChild;
            parent->lChild = temp;
            if(temp != NULL) temp->parent = parent;
            if(child->lChild != NULL) child->lChild->parent = child;
        } else {
            TreapNode* child = parent->lChild;
            child->parent = parent->parent;
            if(child->parent == NULL) root = child;
            else if(child->parent->lChild == parent) child->parent->lChild = child;
            else child->parent->rChild = child;
            parent->lChild = child->lChild;
            if(parent->lChild != NULL) parent->lChild->parent = parent;
            child->lChild = parent;
            parent->parent = child;
            TreapNode* temp = child->rChild;
            child->rChild = parent->rChild;
            parent->rChild = temp;
            if(temp != NULL) temp->parent = parent;
            if(child->rChild != NULL) child->rChild->parent = child;
        }
    }

    void add(int id, ll val, ll priority) {
        TreapNode* toAdd = new TreapNode(id, val, priority);
        if(root == NULL) root = toAdd;
        else {
            TreapNode *curr = root;
            while(true) {
                if(toAdd->val <= curr->val) {
                    if(curr->lChild == NULL) {
                        curr->lChild = toAdd;
                        toAdd->parent = curr;
                        break;
                    } else {
                        curr = curr->lChild;
                    }
                } else {
                    if(curr->rChild == NULL) {
                        curr->rChild = toAdd;
                        toAdd->parent = curr;
                        break;
                    } else {
                        curr = curr->rChild;
                    }
                }
            }
        }
        while(toAdd->parent != NULL && toAdd->parent->priority < toAdd->priority) {
            if(toAdd == toAdd->parent->lChild) lFlip(toAdd->parent, toAdd);
            else rFlip(toAdd->parent, toAdd);
        }
        idMap.insert(MP(id, toAdd));
    }

    void removeNode(int id) {
        TreapNode *toRemove = idMap[id];
        idMap.erase(id);
        while(toRemove->lChild != NULL || toRemove->rChild != NULL) swapWithChild(toRemove);
        if(toRemove == root) {
            root = NULL;
        } else {
            if(toRemove = toRemove->parent->lChild) toRemove->parent->lChild = NULL;
            else toRemove->parent->rChild = NULL;
        }
        toRemove = NULL;
    }

    int querySuffix(ll val) {
        TreapNode* curr = root;
        ll best = 0;
        int idOfBest = -1;
        while(curr != NULL) {
            if(curr->val <= val) {
                if(idOfBest == -1 || curr->priority > best) {
                    idOfBest = curr->id;
                    best = curr->priority;
                }
                curr = curr->rChild;
            } else curr = curr->lChild;
        }
        return idOfBest;
    }

};
