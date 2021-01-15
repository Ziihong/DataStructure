#include <iostream>
#include <queue>
using namespace std;

class Node{
friend class BST;
private:
    int data;
    Node *left, *right;
public:
    Node(int value){
        data=value;
        left=0;
        right=0;
    }
};

class BST{
public:
    Node *root;
    BST(){root=0;}
    Node *insertTree(Node *ptr, int num);
    Node *deleteTree(Node *ptr, int num);
    Node *searchTree(Node *ptr, int num);
    void traverse(Node *ptr);
    bool printLevel(Node *ptr, int level);
    int  levelCount();
    int numOfNodes();
    int leavesCount(Node *ptr, int count);
    int nonleavesCount(Node *ptr, int count);
    void drawBST(Node *ptr, int level);
    Node *findMax(Node *ptr);
    Node *findMin(Node *ptr);
    bool tree_empty();
};

Node *BST::insertTree(Node *ptr, int num){
    if(ptr==0){
        ptr=new Node(num);
        if(root==0) root=ptr;
    }
    else if(ptr->data > num) ptr->left=insertTree(ptr->left, num);
    else if(ptr->data < num) ptr->right=insertTree(ptr->right, num);
    return ptr;
}
Node *BST::deleteTree(Node *ptr, int num){
    if(tree_empty()) {
        cout << "Tree is empty!" << endl;
        return 0;
    }
    else{
        if(ptr==0) cout << "Not found" << endl;
        else{
            Node *p;
            if(ptr->left==0 && ptr->right==0) ptr=0;
            else if(ptr->data > num) ptr->left=deleteTree(ptr->left, num);
            else if(ptr->data < num) ptr->right=deleteTree(ptr->right, num);
            else if(ptr->left==0){
                p=ptr;
                ptr=ptr->right; 
                delete p;
            }
            else if(ptr->right==0){
                p=ptr;
                ptr=ptr->left;
                delete p;
            }
            else{
                Node *temp=findMax(ptr->left);
                ptr->data=temp->data;
                ptr->left=deleteTree(ptr->left, ptr->data);
            }
        }
        return ptr;
    }
}
Node *BST::searchTree(Node *ptr, int num){
    if(tree_empty()){
        cout << "Tree is empty!" << endl;
        return 0;
    }
    else{
        if(ptr==0) cout << "Not found" << endl;
        else {
            if(ptr->data==num) {
                cout << num << " is found" << endl;
                return ptr;
            }
            else if(ptr->data > num) ptr=searchTree(ptr->left, num);
            else if(ptr->data < num) ptr=searchTree(ptr->right, num);
        }
        return ptr;
    }
}
void BST::traverse(Node *ptr){
    if(!tree_empty()){
        printLevel(ptr, levelCount());
    }
    else cout << "Tree is empty!" << endl;
}
bool BST::printLevel(Node *ptr, int level){
    if(ptr==0) return false;
    if(level==1){
        cout << ptr->data << " ";
        return true;
    }
    else{
        bool left=printLevel(ptr->left, level-1);
        bool right=printLevel(ptr->right, level-1);
        return (left || right);
    }
}
int BST::levelCount(){
    int level=1;
    while(printLevel(root, level)){
        level++;
    }
    return level;
}

int BST::numOfNodes(){
    int leaves=0, nonleaves=0;
    if(tree_empty()) cout << "Tree is empty!" << endl;
    else{
        leaves=leavesCount(root, leaves);
        nonleaves=nonleavesCount(root, nonleaves);
    }
    cout << "number of leaves: " << leaves << " number of Nonleaves: " << nonleaves << endl;
    return leaves+nonleaves;
}
int BST::leavesCount(Node *ptr, int count){
    if(ptr){
        if(ptr->left==0 && ptr->right==0) count++;
        else count=leavesCount(ptr->left, count)+leavesCount(ptr->right, count);
    }
    else count=0;
    return count;
}
int BST::nonleavesCount(Node *ptr, int count){
    if(ptr){
        if(ptr->left==0 && ptr->right==0) count=0;
        else count=nonleavesCount(ptr->left, count)+nonleavesCount(ptr->right, count)+1;
    }
    else count=0;
    return count;
}
void BST::drawBST(Node *ptr, int level){
    if(ptr!=0 && level<=7){
        drawBST(ptr->right, level+1);
        for(int i=1; i<=(level-1); i++){
            cout << "   ";
        }
        cout << ptr->data;
        if(ptr->left !=0 && ptr->right !=0) cout << "<" << endl;
        else if(ptr->right !=0) cout << "/" << endl;
        else if(ptr->left !=0) cout << "\\" << endl;
        else cout << endl;
        drawBST(ptr->left, level+1);
    }
}
Node *BST::findMax(Node *ptr){
    if(ptr->right==0) return ptr;
    else return findMax(ptr->right);
}
Node *BST::findMin(Node *ptr){
    if(ptr->left==0) return ptr;
    else return findMin(ptr->left);
}
bool BST::tree_empty(){
    if(root==0) return true;
    else return false;
}
int main(){
    int menu, data;
    BST bst;
    while(true){
        cout << "Menu: 1.Insert 2.Delete 3.Search 4.Traverse 5.Num of Nodes 6.Print 7. Quit >>";
        cin >> menu;
        switch (menu){
            case 1:
                cout << "Data: ";
                cin  >> data;
                bst.insertTree(bst.root, data);
                break;
            case 2:
                cout << "Data: ";
                cin >> data;
                bst.deleteTree(bst.root, data);
                break;
            case 3:
                cout << "Data: ";
                cin >> data;
                bst.searchTree(bst.root, data);
                break;
            case 4:
                bst.traverse(bst.root);
                cout << endl;
                break;
            case 5:
                cout << "Num of Nodes: " << bst.numOfNodes() << endl;
                break;
            case 6:
                bst.drawBST(bst.root, 1);
                break;
            default:
                break;
        }
        if(menu==7) break;
    }
    return 0;
}