#include <bits/stdc++.h>
using namespace std;
struct TreeNode {
    char val; // �ڵ��ֵ
    TreeNode *firstChild; // ��һ���ӽڵ�
    TreeNode *nextSibling; // �ֵܽڵ�
    TreeNode(){
        val = '\0';
        firstChild = nullptr;
        nextSibling = nullptr;
    }
};
class tree{
private:
    TreeNode *root; //���ڵ�
    int num; //�ڵ���
    bool isForest = false; //�Ƿ�Ϊɭ��
public:
    tree(){
        root = nullptr;
    }
    //���ݽڵ���������
    tree(int n){
        num = n;
        if (n<=0) {
            root = nullptr;
            return;
        }
        cout<<"��������ڵ��ֵ��"<<endl;
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
                cout << "�ļ���ʧ�ܣ�" << endl;
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
                cout << "�ļ���ʧ�ܣ�" << endl;
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
            cout << "���ڸýڵ㣬������  0��ֻ���ӽڵ��    1��ֻ���ֵܽڵ��   2�����ӽڵ�������ֵܽڵ��    3�����߽���" << endl;
            cin >> c;
            if(c!=0&&c!=1&&c!=2&&c!=3) {
                cout<<"����������������룡"<<endl;
                continue;
            }
            break;
        }
        TreeNode *ptr1 = Root;
        TreeNode *ptr2 = Root;
        if(c==0){
            cout<<"��������ӽڵ��ֵ��"<<endl;
            TreeNode *p = new TreeNode;
            cin>>p->val;
            ptr1->firstChild = p;
            ptr1 = ptr1->firstChild;
            add_node(ptr1);
        }
        else if(c==1){
            cout<<"��������ֵܽڵ��ֵ��"<<endl;
            TreeNode *p = new TreeNode;
            cin>>p->val;
            ptr2->nextSibling = p;
            ptr2 = ptr2->nextSibling;
            add_node(ptr2);
        }
        else if(c==2){
            cout<<"������"<<ptr1->val<<"���ӽڵ��ֵ��"<<endl;
            TreeNode *p = new TreeNode;
            cin>>p->val;
            ptr1->firstChild = p;
            ptr1 = ptr1->firstChild;
            add_node(ptr1);
            cout<<"������"<<ptr2->val<<"���ֵܽڵ��ֵ��"<<endl;
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
//ǰ�����
void preorderTraversal(TreeNode* root) {
    if (root == nullptr) {
        return;
    }
    std::cout << root->val << " ";
    preorderTraversal(root->firstChild);
    preorderTraversal(root->nextSibling);
}
//�������
void inorderTraversal(TreeNode* root) {
    if (root == nullptr) {
        return;
    }
    inorderTraversal(root->firstChild);
    std::cout << root->val << " ";
    inorderTraversal(root->nextSibling);
}
//��������
void postorderTraversal(TreeNode* root) {
    if (root == nullptr) {
        return;
    }
    postorderTraversal(root->firstChild);
    postorderTraversal(root->nextSibling);
    std::cout << root->val << " ";
}
// ��������ת��Ϊɭ��
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
// ��ɭ��ת��Ϊ������
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
