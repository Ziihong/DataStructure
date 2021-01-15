#include <iostream>
using namespace std;

class Node{
friend class List;
private:
    int data;
    Node *next;
    Node(int value){
        data=value;
        next=0;
    }
};

class List{
private:
    Node *head;
public:
    List(){head=0;}
    void insertNode(int data);
    void deleteNode(int num);
    void listNode();
    void searchNode(int num);
    void printLastNode();
    void printNthNode(int n);
    bool isEmpty();
    ~List();
};
void List::insertNode(int data){
    Node *temp = new Node(data);
    Node *p, *q;
    if(head==0) head=temp;
    else if(temp->data < head->data){
        temp->next=head;
        head=temp;
    }
    else{
        p=head; q=head;
        while(p!=0 && p->data < temp->data){
            q=p;
            p=p->next;
        }
        if(p!=0){
            temp->next=p;
            q->next=temp;
        }
        else{
            q->next=temp;
        }
    }
}
void List::deleteNode(int num){
    Node *p, *q;
    if(isEmpty()){
        cout << "List is empty!" << endl;
    }
    else if(head->data==num){
        p=head;
        head=head->next;
        delete p;
    }
    else{
        p=head; q=head;
        while(p!=0 && p->data!=num){
            q=p;
            p=p->next;
        }
        if(p!=0){
            q->next=p->next;
            delete p;
        }
        else cout << num << " is not found" << endl;        
    }
}
void List::listNode(){
    if(isEmpty()) cout << "List is empty!" << endl;
    else {
        Node *p;
        p=head;
        cout << "List: ";
        while(p!=0){
            cout << p->data << " ";
            p=p->next;
        }
    }
}
void List::searchNode(int num){
    Node *p=head;
    if(isEmpty()) cout << "List is empty!" << endl;
    else{
        while(p->next!=0 && p->data!=num){
        p=p->next;
        }
    if(p->data==num) cout << num << " is in the list" << endl;
    else cout << num << " is not in the list" << endl;
    }
}
void List::printLastNode(){
    Node *p=head;
    if(isEmpty()) cout << "List is empty" << endl;
    else{
        while(p->next!=0){
            p=p->next;
        }
        cout << "Last node: " << p->data << endl;
    }
}
void List::printNthNode(int n){
    Node *p=head;
    if(isEmpty()) cout << "List is empty" << endl;
    else{
        int count=1; //head
        while(count<=n && p->next!=0){
            if(count!=1) p=p->next;
            count++;
        }
        if(--count==n) cout << n << "th node:" << p->data << endl;
        else cout << "Not found. out of boundary" << endl;
    }
}
bool List::isEmpty(){
    if(head==0) return true;
    else return false;
}
List::~List(){
    Node *p;
    while(head!=0){
        p=head;
        head=head->next;
        delete p;
    }
}

int main(){
    List sll;
    int menu, number;
    while(true){
        cout << "Command: 1.Insert  2.Delete  3.List  4.Search  5.Print Last  6.Print Nth  7.Quit";
        cout << " >>>";
        cin >> menu;
        switch (menu)
        {
        case 1: 
            cout << "Input a Number:";
            cin >> number;
            sll.insertNode(number);
            break;
        case 2: 
            cout << "Input a Number:";
            cin >> number;
            sll.deleteNode(number);
            break;
        case 3: 
            sll.listNode();
            break;
        case 4: 
            cout << "Input a Number:";
            cin >> number;
            sll.searchNode(number);
            break;
        case 5: 
            sll.printLastNode();
            break;
        case 6: 
            cout << "Nth: ";
            cin >> number;
            sll.printNthNode(number);
            break;
        case 7:
            cout << "Quit!" << endl;
            sll.~List();
            break;
        }
        cout << endl;
        if(menu==7){
            break;
        }
    }
    return 0;
}