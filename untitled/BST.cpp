#include <stdio.h>
#include <stdexcept>

using namespace std;


class node {
private:
    int value;
    node *left, *right, *parent;
public:
    node(int v, node *inParent) : value(v) {
        parent = inParent;
        left = right = NULL;
    }

    int val() const {
        return value;
    }

    node *getLeft() {
        return left;
    }

    node *getParent() {
        return parent;
    }

    node *getRight() {
        return right;
    }

    node *clear() {
        if (left) left = left->clear();
        if (right) right = right->clear();
        delete this;
        return NULL;
    }

public:
    node *search(int v) {
        if (v < value) {
            if (left) return left->search(v);
            else return NULL;
        } else if (value < v) {
            if (right) return right->search(v);
            else return NULL;
        } else return this;
    }

    const node *search_min() const {
        if (left) return left->search_min();
        else return this;
    }

    const node *search_max() const {
        if (right) return right->search_max();
        else return this;
    }

    const node *prev(int v) const {
        if (v < value) {
            if (left) return left->prev(v);
            else return NULL;
        } else if (value < v) {
            if (right) {
                const node *nd = right->prev(v);
                if (nd) return nd;
                else return this;
            } else return this;
        } else {
            if (left) return left->search_max();
            else return NULL;
        }
    }

    const node *next(int v) const {
        if (v < value) {
            if (left) {
                const node *nd = left->next(v);
                if (nd) return nd;
                else return this;
            } else return this;
        } else if (value < v) {
            if (right) return right->next(v);
            else return NULL;
        } else {
            if (right) return right->search_min();
            else return NULL;
        }
    }

    node *insert(int v) {
        if (v < value) {
            if (left) left = left->insert(v);
            else left = new node(v, this);
        } else if (value < v) {
            if (right) right = right->insert(v);
            else right = new node(v, this);
        } else value = v;
        return this;
    }

    node *remove_min() {
        if (left) {
            left = left->remove_min();
            return this;
        } else {
            node *nd = right;
            delete this;
            return nd;
        }
    }

    node *remove_max() {
        if (right) {
            right = right->remove_max();
            return this;
        } else {
            node *nd = left;
            delete this;
            return nd;
        }
    }

    node *remove(int v) {
        if (v < value) {
            if (left) left = left->remove(v);
            return this;
        } else if (value < v) {
            if (right) right = right->remove(v);
            return this;
        } else if (!left) {
            node *nd = right;
            delete this;
            return nd;
        } else if (!right) {
            node *nd = left;
            delete this;
            return nd;
        } else {
            value = left->search_max()->value;
            left = left->remove_max();
            return this;
        }
    }

};

void inorder(node *t) {
    if (t == NULL)
        return;
    inorder(t->getLeft());
    printf("%d\n", t->val());
    inorder(t->getRight());
}

class bst {
    node *root;
public:
    bst() {
        root = NULL;
    }

    ~bst() {
        if (root) root = root->clear();
    }

public:

    int prev(int v) const {
        if (!root) throw invalid_argument("tree is empty");
        const node *nd = root->prev(v);
        if (!nd) throw invalid_argument("absent previous");
        return nd->val();
    }

    bool search(int v) const {
        if (root) return root->search(v) != NULL;
        else return false;
    }

    void insert(int v) {
        if (root) root = root->insert(v);
        else root = new node(v, NULL);
    }

    void remove(int v) {
        if (root) root = root->remove(v);
    }

    node *getRoot() {
        return root;
    }

    void inorder(struct node *root) {
        if (root != NULL) {
            inorder(root->getLeft());
            printf("%d \n", root->val());
            inorder(root->getRight());
        }
    }

    node *myPrevious(struct node *currentNode, int b) {
        if (currentNode->getParent()->val() > currentNode->val()) {
            return currentNode->getParent();
        } else {
            return myPrevious(currentNode->getParent(), b);
        }
    }

};

void printPreviousAndNextValue(bst &t, int b) {
    if (t.search(b)) {
        int previous;
        int next;
        if (t.getRoot()->search_min()->val() == b) {
            previous = -1;
        } else {
            previous = t.prev(b);
        }
        if (t.getRoot()->search_max()->val() == b) {
            next = -1;
        } else {
            next = t.getRoot()->next(b)->val();
        }
        printf("%d %d\n", previous, next);
    } else {
        printf("NO\n");
    }
}

void removeIfExist(bst &t, int b) {
    if (t.search(b)) {
        t.remove(b);
    }
}

void printContains(const bst &t, int b) {
    printf(t.search(b)
           ? "YES\n"
           : "NO\n");
}

void printMaxValue(bst &t) {
    printf("%d\n", t.getRoot()->search_max()->val());
}

void printMinValue(bst &t) {
    printf("%d\n", t.getRoot()->search_min()->val());
}

bool startCommand(bst &t, int a, int b) {
    bool isFinish;
    switch (a) {
        case 0:
            isFinish = true;
            break;
        case 1:
            t.insert(b);
            break;
        case 2:
            printMinValue(t);
            break;
        case 3:
            printMaxValue(t);
            break;
        case 4:
            printContains(t, b);
            break;
        case 5:
            removeIfExist(t, b);
            break;
        case 6:
            printPreviousAndNextValue(t, b);
            break;
    }
    return isFinish;
}

int main() {
    bst t;
    int a, b;
    bool isFinish = false;

    while (!isFinish) {
        scanf("%d %d", &a, &b);
        isFinish = startCommand(t, a, b);
    }

    return 0;
}