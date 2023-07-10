#include<stdio.h>
#include<stdlib.h>


typedef struct node {
    int num;
    int level;
    struct node *left;
    struct node *right;
    struct node *parent;
}node;

void add();
void search(void);
void delete(void);
void display(node *p, int level);
node *makeNode(node *p, int n);
int searchNode(node *p, int n);
void deleteNode(node *p, int n);
void releaseNode(node *p);
int balanceFactor(node *p);
void height(node *p);
int calc(node *p);
void judgeAdd(int n);
void judgeDelete(int n);
void rotateRight(node *p, node *parent);
void rotateLeft(node *p, node *parent);
node *root;
int level;


int main(void) {
    int res;
    root = NULL;

    while(1) {
        printf("1--追加\t2--削除\t3--探索\t4--表示\t0--終了\n");
        scanf("%d", &res);
        if(!res) {
            break;
        }
        switch(res) {
            case 1:
                add();
                break;
            case 2:
                delete();
                break;
            case 3:
                search();
                break;
            case 4:
                display(root, 0);
                break;
        }
    }

    releaseNode(root);
    return 0;
}

void add() {
    int n;
    printf("入力する値:");
    scanf("%d", &n);
    root = makeNode(root, n);
    height(root);
    judgeAdd(n);
}

void search(void) {
    int n, res;
    printf("探索する値:");
    scanf("%d", &n);
    res = searchNode(root, n);
    if(res == 1) {
        printf("見つかりませんでした\n");
    }
}

void delete(void) {
    int n;
    printf("削除する値:");
    scanf("%d", &n);
    deleteNode(root, n);
    if(root != NULL){
        height(root);
        judgeDelete(n);
    }
}

node *makeNode(node *p, int n) {
    if(p == NULL) {
        p = (node *)malloc(sizeof(node));
        if(p == NULL) {
            printf("メモリを確保できませんでした.\n");
            return p;
        }
        p->num = n;
        p->left = NULL;
        p->right = NULL;
        p->parent = NULL;  
    }

    else if(n <= p->num) {
        p->left = makeNode(p->left, n);
        p->left->parent = p;
    }
    else {
        p->right = makeNode(p->right, n);
        p->right->parent = p;
    }
    return p;
}

int searchNode(node *p, int n) {
    if(n == p->num) {
        printf("%d\n", n);
        return 0;
    }
    else if(n <= p->num) {
        if(p->left == NULL) return 1;
        printf("%d->", p->num);
        searchNode(p->left, n);
    }
    else {
        if(p->right == NULL) return 1;
        printf("%d->", p->num);
        searchNode(p->right, n);
    }
}

void deleteNode(node *p, int n) {
    if(p == NULL) return;

    while(p !=  NULL){
        if(n < p->num){
            p = p->left;
        } 
        else if(n > p->num){
            p = p->right;
        } 
        else break;
    }
    if(p == NULL) return;
    

    if(p->left == NULL && p->right == NULL) {
        if(p->parent == NULL) {
            root = NULL;
            free(p);
            return;
        }
        else if(p->parent->left == p) {
            p->parent->left = NULL;
            p = NULL;
            free(p);
        }
        else{
            p->parent->right = NULL;
            p = NULL;
            free(p);
        }
    }
    else if((p->left != NULL && p->right == NULL) || (p->left != NULL && p->right != NULL)) {
        node *tmp;
        tmp = p->left;
        int i = 0;
        while(tmp->right != NULL) {
            tmp = tmp->right;
            i++;
        }   
        p->num = tmp->num;
        if(tmp->left != NULL) {
            if(i == 0) tmp->parent->left = tmp->left;
            else tmp->parent->right = tmp->left;
            free(tmp);
        }
        else {
            if(i == 0) tmp->parent->left = NULL;
            else tmp->parent->right = NULL;
            tmp = NULL;
            free(tmp);
        }
    }
    else if(p->left == NULL && p->right != NULL) {
        node *tmp;
        tmp = p->right;
        p->num = tmp->num;
        p->right = tmp->right;
        tmp = NULL;
        free(tmp);
    }
}

void display(node *root, int level) {
    if (root == NULL)
    {
        return;
    }
    if (level == 0)
    {
        printf("木構造を降順で表示します。\n");
    }
    display(root->right, level + 1);
    for (int i = 0; i < level; i++)
        printf("|\t");
    printf("%d (%d)\n", root->num, balanceFactor(root));
    display(root->left, level + 1);
}

void releaseNode(node *p) {
    releaseNode(p -> left);
    releaseNode(p -> right);
    free(p);
}

int balanceFactor(node *p) {
    int l, r;
    if(p->left == NULL) l = 0;
    else l = p->left->level;
    if(p->right == NULL) r = 0;
    else r = p->right->level;
    return l - r;
}

void height(node *p) {
    if(p == NULL) return;
    p->level = calc(p);
    height(p->left);
    height(p->right);
}

int calc(node *p) {
    int l, r;
    if(p == NULL) return 0;
    l = calc(p->left) + 1;
    r = calc(p->right) + 1;
    if(l < r) return r;
    else return l;
}

void judgeAdd(int n) {
    int balance;
    node *current;
    current = root;

    while(1) {
        if(n == current->num) break;
        if(n < current->num) current = current->left;
        else if(n > current->num) current = current->right;
    }

    balance = balanceFactor(current);
    if(balance < -1 || balance > 1) {
        if(balance == 2 && balanceFactor(current->left) == 1) {
            rotateRight(current->left, current);
        }
        else if(balance == -2 && balanceFactor(current->right) == 1) {
            rotateRight(current->right->left, current->right);
            rotateLeft(current->right, current);
        }
        else if(balance == 2 && balanceFactor(current->left) == -1) {
            rotateLeft(current->left->right, current->left);
            rotateRight(current->left, current);
        }
        else if(balance == -2 && balanceFactor(current->right) == -1) {
            rotateLeft(current->right, current);
        }
        height(root);
    }
    
    if(current == root) return;
    judgeAdd(current->parent->num);
}

void judgeDelete(int n) {
    int i;
    node *current;
    current = root;

     while(1) {
        if(n < current->num) {
            if(current->left == NULL) break;
            else current = current->left;
        }
        else if(n > current->num) {
            if(current->right == NULL) break;
            else current = current->right;
        }
    }

    i = current->num;
    judgeAdd(i);
}

void rotateRight(node *p, node *parent) {
    parent->left = p->right;
    p->right = parent;
    p->parent = parent->parent;
    parent->parent = p;
    if(parent == root) root = p;
    else if(p->parent->right == parent) p->parent->right = p;
    else p->parent->left = p;
}

void rotateLeft(node *p, node *parent) {
    parent->right = p->left;
    p->left = parent;
    p->parent = parent->parent;
    parent->parent = p;
    if(parent == root) root = p;
    else if(p->parent->left == parent) p->parent->left = p;
    else p->parent->right = p;
}