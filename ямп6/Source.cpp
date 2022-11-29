#include <iostream>
#include <string>
#include <algorithm>
#include <time.h>
using namespace  std;

struct Tree {
    int key;
    Tree* left, * right;

};

void push(Tree*& t, int x,int tmp=0) {
    if (t == NULL) {
        t = new Tree;                
        t->key = x;                
        t->left = t->right = NULL;       
        return;                         
    }
    tmp = rand() % 2;
    cout << tmp << endl;
    if (tmp == 0) {
        push(t->right, x);
    }
    else {
        push(t->left,x);
    }
}

void print(Tree* node, bool isLeft=0,const string& prefix="")
{
    cout << prefix;
    cout <<(isLeft ? "|--" : "L--");
    node != nullptr ? cout << node->key : cout << "NULL";
    cout << endl;
    if (node == nullptr)
    {
        return;
    }
    print(node->left, true, prefix + (isLeft ? "| " : " "));
    print(node->right, false, prefix + (isLeft ? "| " : " "));
}

int height(Tree* t) {
    if (!t) return -1;
    else return max(height(t->left), height(t->right)) + 1;
}
int maxValue(struct Tree* node)
{
    if (node == NULL) {
        return INT16_MIN;
    }
    int value = node->key;
    int leftMax = maxValue(node->left);
    int rightMax = maxValue(node->right);

    return max(value, max(leftMax, rightMax));
}

int minValue(struct Tree* node)
{
    if (node == NULL) {
        return INT16_MAX;
    }
    int value = node->key;
    int leftMax = minValue(node->left);
    int rightMax = minValue(node->right);

    return min(value, min(leftMax, rightMax));
}
/* Returns true if a binary tree is a binary search tree */
int isBST(struct Tree* node)
{
    if (node == NULL)
        return 1;

    /* false if the max of the left is > than us */
    if (node->left != NULL
        && maxValue(node->left) > node->key)
        return 0;

    /* false if the min of the right is <= than us */
    if (node->right != NULL
        && minValue(node->right) < node->key)
        return 0;

    /* false if, recursively, the left or right is not a BST
     */
    if (!isBST(node->left) || !isBST(node->right))
        return 0;

    /* passing all that, it's a BST */
    return 1;
}

int hate(Tree* root)
{
    if (!root) {
        return 0;
    }
    return 1 + hate(root->left) + hate(root->right);
}

void count(Tree* t, int n, int k,int&max,Tree*&tmp) {
    if (!t) return;
    if (k == n) {
        int tt = hate(t);
        if (!isBST(t)) {
            tt = 0;
        }
        cout << tt << endl;
        if (tt >= max) {
            max = tt;
            tmp = t;
        }
    }
    if (k < n) {
        count(t->left, n, k + 1, max, tmp);
        count(t->right, n, k + 1, max, tmp);
    }
}
Tree* maxBTS(Tree*t) {
    if (!t) return nullptr;
    int max = 0;
    Tree* tmp = new Tree;
    for (int i = 0; i <= height(t); i++) {
        count(t,height(t),i,max,tmp);
    }
    return tmp;
}

void pushBTS(Tree*& t, int x) {
    if (t == NULL) {
        t = new Tree;                //Выделяем память
        t->key = x;                 //Кладем в выделенное место аргумент a
        t->left = t->right = NULL;       //Очищаем память для следующего роста
        return;                         //Заложили семечко, выходим
    }
    //Дерево есть
    if (x > t->key) pushBTS(t->right, x); //Если аргумент а больше чем текущий элемент, кладем его вправо
    if (x < t->key) pushBTS(t->left, x);
    return;                                     //Иначе кладем его влево
}

int main()
{
    setlocale(LC_ALL, "Russian");
    int n;                              //Количество элементов
    int s;   //Число, передаваемое в дерево
    Tree* t = NULL;
    cout << "введите количество элементов  ";
    cin >> n;                           //Вводим количество элементов
    srand(time(NULL));
    for (int i = 0; i < n; ++i)
    {
        cout << "введите число  ";
        cin >> s;
        push(t, s);                 //И каждый кладем в дерево
    }
    cin >> s;
    pushBTS(t, s);
    cin >> s;
    pushBTS(t, s);
    cin >> s;
    pushBTS(t, s);
    cin >> s;
    pushBTS(t, s);
    cout << "ваше дерево\n";

    print(t);
    cout << endl;
    cout << maxBTS(t)->key<<" "<< hate(maxBTS(t));
    return 0;
}