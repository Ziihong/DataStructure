#include <iostream>
using namespace std;

class LinkedStack;
class LinkedQueue;
class List;

class Node{
private:
    char data;
    Node *next;
public:
    Node(char value){
        data=value;
        next=0;
    }
    friend class LinkedStack;
    friend class LinkedQueue;
    friend class List;
};

class LinkedStack{
private:
    Node *top;
public:
    LinkedStack();
    void push(char data);
    char pop();
    void display();
    bool isEmpty();
    friend class List;
};

class LinkedQueue{
private:
    Node *front;
    Node *rear;
public:
    LinkedQueue();
    void enqueue(char data);
    char dequeue();
    void display();
    bool isEmpty();
    friend class List;
};

class List{
private:
    Node*head;
public: 
    List();
    void createLink(char data);
    void concatenate(LinkedStack *s, LinkedQueue *q);
    void invert();
    void display();
    bool isEmpty();
};


LinkedStack::LinkedStack(){top=0;}

void LinkedStack::push(char data){
    Node *temp=new Node(data);
    if(isEmpty()) top=temp;
    else{
        temp->next=top;
        top=temp;
    }
}
char LinkedStack::pop(){
    Node *p; char c;
    if(isEmpty()){
        cout << "Stack is empty!" << endl;
        return '\0';
    }
    else{
        c=top->data;
        p=top;
        top=top->next;
        delete p;
        return c;
    }
}
void LinkedStack::display(){
    Node *p;
    p=top;
    cout << "Stack: ";
    while(p!=0){
        cout << p->data << " ";
        p=p->next;
    }
    cout << endl;
}
bool LinkedStack::isEmpty(){
    if(top==0) return true;
    else return false;
}


LinkedQueue::LinkedQueue(){front=0; rear=0;}

void LinkedQueue::enqueue(char data){
    Node *temp=new Node(data);
    if(isEmpty()){front=temp; rear=temp;}
    else{
        rear->next=temp;
        rear=temp;
    }
}
char LinkedQueue::dequeue(){
    Node *p; char c;
    if(isEmpty()){
        cout << "Queue is empty!" << endl;
        return '\0';
    }
    else{
        c=front->data;
        p=front;
        if(front==rear){front=0; rear=0;}
        else front=front->next;
        delete p;
        return c;
    }
}
void LinkedQueue::display(){
    Node *p;
    p=front;
    cout << "Queue: ";
    while(p!=0){
        cout << p->data << " ";
        p=p->next;
    }
    cout << endl;
}
bool LinkedQueue::isEmpty(){
    if(front==0) return true;
    else return false;
}


List::List(){head=0;}

void List::createLink(char data){
    Node *temp=new Node(data);

    Node *p, *q;
    if(isEmpty()){head=temp;}
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
void List::concatenate(LinkedStack *s, LinkedQueue *q){
    Node *p;
    if(s==0){
        p=q->front;
        while(p!=0){
            createLink(p->data);
            p=p->next;
        }
    }
    else{
        p=s->top;
        while(p!=0){
            createLink(p->data);
            p=p->next;
        }
        if(q!=0){
            p=q->front;
            while(p!=0){
                createLink(p->data);
                p=p->next;
            }
        }
    }
    delete p;
}
void List::display(){
    Node *p;
    p=head;
    cout << "List: ";
    while(p!=0){
        cout << p->data << " ";
        p=p->next;
    }
    cout << endl;
}
void List::invert(){
    Node *p, *q, *r;
    p=head; q=0;
    while(p!=0){
        r=q;
        q=p;
        p=p->next;
        q->next=r;
    }
    head=q;
    while(q!=0){
        cout << q->data << " ";
        q=q->next;
    }
    cout << endl;
}
bool List::isEmpty(){
    if(head==0) return true;
    else return false;
}

int main(){
    LinkedStack s; LinkedQueue q; List l;
    LinkedStack *ptr1=&s;
    LinkedQueue *ptr2=&q;
    int menu;
    char input;
    while(true){
        cout << "Menu: 1.Push 2.Pop 3.Display Stack 4.Enqueue 5.Dequeue 6.Display Queue 7.Merge 8.Invert 9.Display List 10.Quit ";
        cout << ">> ";
        cin >> menu;
        switch (menu)
        {
        case 1:
            cout << "Input data: ";
            cin >> input;
            s.push(input);
            break;
        case 2:
            s.pop();
            break;
        case 3:
            s.display();
            break;
        case 4:
            cout << "Input data: ";
            cin >> input;
            q.enqueue(input);
            break;
        case 5:
            q.dequeue();
            break;
        case 6:
            q.display();
            break;
        case 7:
            l.concatenate(ptr1, ptr2);
            break;
        case 8:
            l.invert();
            break;
        case 9:
            l.display();
            break;
        default:
            break;
        }
        cout << endl;
        if(menu==10) break;
    }
    return 0;
}