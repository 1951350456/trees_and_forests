#include <bits/stdc++.h>
using namespace std;
struct TreeNode {
    char val; // 节点的值
    TreeNode *firstChild; // 第一个子节点
    TreeNode *nextSibling; // 兄弟节点
    TreeNode(){
        val = '\0';
        firstChild = nullptr;
        nextSibling = nullptr;
    }
};
class tree{
private:
    TreeNode *root; //根节点
    int num; //节点数
    bool isForest = false; //是否为森林
public:
    tree(){
        root = nullptr;
    }
    //根据节点数创建树
    tree(int n){
        num = n;
        if (n<=0) {
            root = nullptr;
            return;
        }
        cout<<"请输入根节点的值："<<endl;
        TreeNode *p = new TreeNode;
        cin>>p->val;
        root = p;
        TreeNode *ptr = root;
        add_node(ptr);
    }
    tree(string fileName,bool isforest){
        if(!isforest) {
            fstream file(fileName);
            if (!file.is_open()) {
                cout << "文件打开失败！" << endl;
                return;
            }
            TreeNode *p[200] = {nullptr};
            char c;
            int i = 0;
            map<char, int> map1;
            while (file.get(c)) {
                if (c == ' ')
                    break;
                TreeNode *m = new TreeNode;
                m->val = c;
                map1[c] = i;
                p[i++] = m;
            }
            TreeNode *ptr;
            int cnt = 0;
            while (file.get(c)) {
                if (c == ' ') {
                    cnt = 0;
                    continue;
                } else if (cnt == 0) {
                    ptr = p[map1[c]];
                    cnt = 0;
                    cnt++;
                } else {
                    if (cnt == 1) {
                        ptr->firstChild = p[map1[c]];
                        ptr = ptr->firstChild;
                        cnt++;
                    } else {
                        ptr->nextSibling = p[map1[c]];
                        ptr = ptr->nextSibling;
                        cnt++;
                    }
                }
            }
            root = p[0];
        }
        else{
            TreeNode *ROOT[200] = {nullptr};
            fstream file(fileName);
            if (!file.is_open()) {
                cout << "文件打开失败！" << endl;
                return;
            }

            TreeNode *p[200] = {nullptr};
            char c;
            int i = 0;
            map<char, int> map1;
            while (file.get(c)) {
                if (c == ' ')
                    break;
                TreeNode *m = new TreeNode;
                m->val = c;
                map1[c] = i;
                p[i++] = m;
            }
            TreeNode *ptr;
            int cnt = 0;
            while (file.get(c)) {
                if (c == ' ') {
                    cnt = 0;
                    continue;
                } else if (cnt == 0) {
                    ptr = p[map1[c]];
                    cnt = 0;
                    cnt++;
                } else {
                    if (cnt == 1) {
                        ptr->firstChild = p[map1[c]];
                        ptr = ptr->firstChild;
                        cnt++;
                    } else {
                        ptr->nextSibling = p[map1[c]];
                        ptr = ptr->nextSibling;
                        cnt++;
                    }
                }
            }
            root = p[0];
        }
    }
    ~tree(){
        TreeNode *ptr = root;
        delete_subtree(root);
    }
    void add_node(TreeNode *Root){
        int c;
        while (true) {
            cout << "对于该节点，请输入  0：只有子节点或    1：只有兄弟节点或   2：有子节点和其他兄弟节点或    3：二者皆无" << endl;
            cin >> c;
            if(c!=0&&c!=1&&c!=2&&c!=3) {
                cout<<"输入错误！请重新输入！"<<endl;
                continue;
            }
            break;
        }
        TreeNode *ptr1 = Root;
        TreeNode *ptr2 = Root;
        if(c==0){
            cout<<"请输入该子节点的值："<<endl;
            TreeNode *p = new TreeNode;
            cin>>p->val;
            ptr1->firstChild = p;
            ptr1 = ptr1->firstChild;
            add_node(ptr1);
        }
        else if(c==1){
            cout<<"请输入该兄弟节点的值："<<endl;
            TreeNode *p = new TreeNode;
            cin>>p->val;
            ptr2->nextSibling = p;
            ptr2 = ptr2->nextSibling;
            add_node(ptr2);
        }
        else if(c==2){
            cout<<"请输入"<<ptr1->val<<"的子节点的值："<<endl;
            TreeNode *p = new TreeNode;
            cin>>p->val;
            ptr1->firstChild = p;
            ptr1 = ptr1->firstChild;
            add_node(ptr1);
            cout<<"请输入"<<ptr2->val<<"的兄弟节点的值："<<endl;
            TreeNode *q = new TreeNode;
            cin>>q->val;
            ptr2->nextSibling = q;
            ptr2 = ptr2->nextSibling;
            add_node(ptr2);
        }
        else{
            return;
        }
    }
    void delete_subtree(TreeNode *ROOT){
        TreeNode *ptr = ROOT;
        if(ROOT->firstChild!=nullptr) {
            TreeNode *lptr = ptr->firstChild;
            delete_subtree(lptr);
        }
        if(ROOT->nextSibling!=nullptr) {
            TreeNode *rptr = ptr->nextSibling;
            delete_subtree(rptr);
        }
        delete ptr;
    }
    TreeNode *get_root(){
        return root;
    }
    TreeNode *set_root(TreeNode *ROOT){
        root = ROOT;
    }
};
//前序遍历
void preorderTraversal(TreeNode* root) {
    if (root == nullptr) {
        return;
    }
    std::cout << root->val << " ";
    preorderTraversal(root->firstChild);
    preorderTraversal(root->nextSibling);
}
//中序遍历
void inorderTraversal(TreeNode* root) {
    if (root == nullptr) {
        return;
    }
    inorderTraversal(root->firstChild);
    std::cout << root->val << " ";
    inorderTraversal(root->nextSibling);
}
//后续遍历
void postorderTraversal(TreeNode* root) {
    if (root == nullptr) {
        return;
    }
    postorderTraversal(root->firstChild);
    postorderTraversal(root->nextSibling);
    std::cout << root->val << " ";
}
// 将二叉树转化为森林
vector<tree> binaryTreeToForest(TreeNode* root) {
    vector<tree> forest;
    while (root != nullptr) {
        tree newTree;
        newTree.set_root(root);
        forest.push_back(newTree);
        root = root->nextSibling;
    }
    return forest;
}
// 将森林转化为二叉树
TreeNode* forestToBinaryTree(vector<tree> forest) {
    TreeNode* root = nullptr;
    TreeNode* ptr = nullptr;
    for (int i = 0; i < forest.size(); i++) {
        TreeNode* child = forest[i].get_root();
        if (root == nullptr) {
            root = child;
            ptr = root;
        } else {
            ptr->nextSibling = child;
            ptr = ptr->nextSibling;
        }
    }
    return root;
}
int main() {
    tree a("C:\\Users\\ZYF\\CLionProjects\\tree_forest_system\\trees.txt",0);
    preorderTraversal(a.get_root());

}
