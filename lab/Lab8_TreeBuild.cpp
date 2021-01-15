#include <iostream>
#include <string>
using namespace std;

class Node{
friend class Tree;
public:
    char data;
    int prior;
    Node *left;
    Node *right;
    Node(char value){
        data=value;
        prior=4;
        left=0;
        right=0; 
    }
};

class Tree{
public: 
    Node *root;
    Tree(){root=0;}
    void createOperand(Node *temp);
    void createOperator(Node *temp);
    void inorder(Node *t);
    void postorder(Node *t);
    void preorder(Node *t);
    int evalTree(Node *t);
};
void Tree::createOperand(Node *temp){
    if(root==0) root=temp;
    else{
        Node *p=root;
        while(p->right!=0){
            p=p->right;
        }
        p->right=temp;
    }
}
void Tree::createOperator(Node *temp){
    if(root->prior >= temp->prior){
        temp->left=root;
        root=temp;
    }
    else{
        temp->left=root->right;
        root->right=temp;   
    }
}
void Tree::inorder(Node *t){
    if(t){
        inorder(t->left);
        cout << t->data << " ";
        inorder(t->right);
    } 
}
void Tree::postorder(Node *t){
    if(t){
        postorder(t->left);
        postorder(t->right);
        cout << t->data << " ";
    }    
}
void Tree::preorder(Node *t){
    if(t){
        cout << t->data << " ";
        preorder(t->left);
        preorder(t->right);
    }
}
int Tree::evalTree(Node *t){
    int value, left, right;
    if(t!=0){
        if(isdigit(t->data)){
            value=t->data-'0';
        }
        else{
            left=evalTree(t->left);
            right=evalTree(t->right);
            switch (t->data){
                case '*':
                    value=left*right;
                    break;
                case '/':
                    value=left/right;
                    break;
                case '+':
                    value=left+right;
                    break;
                case '-':
                    value=left-right;
                    break;
                default:
                    break;
            }
        }

    }
    return value;
}
int main(){
    string input;
    Tree tree; Tree *treeptr=&tree;
    cout << "Input Infix Expression: "; cin >> input;
    
    char prec[4][2]={{'*',2}, {'/', 2}, {'+', 1}, {'-', 1}};
    for(int idx=0; idx<input.length(); idx++){
        Node *temp=new Node (input.at(idx));
        for(int i=0; i<4; i++){
            if(temp->data==prec[i][0]){
                temp->prior=prec[i][1];
            }
        }
        if(temp->prior==4) tree.createOperand(temp);
        else tree.createOperator(temp);
    }
    cout << "Inorder: "; tree.inorder(treeptr->root); cout << endl;
    cout << "Postorder: "; tree.postorder(treeptr->root); cout << endl;
    cout << "Preorder: "; tree.preorder(treeptr->root); cout << endl;
    if(isdigit(input.at(0))) cout << "Eval Tree: " << tree.evalTree(treeptr->root) << endl;
    
    return 0;
}