/*
Name: 김지홍
Student ID: 20191572
Program ID:Hw4_DLL
Description: 
        Doubly Linked List는 앞서 배웠던 Singly Linked List와 달리, 양방향 Link를 사용하여 검색 시간을 줄일 수 있다.
        현재의 노드 위치를 지정하여 이를 활용하여 많은 기능을 수행할 수 있다.
Algorithm: 
        class Node=>데이터와 rlink, llink 양방향 링크 저장
        class DLL=>리스트 첫번째 노드인 head와 현재 위치 노드 current를 저장
        insertAfter()/insertBefore()/insertFisrt()/insertLast()=>insert할 위치 선정 후 데이터를 입력하여 함수를 호출. 함수 실행 후, current 노드=insert 노드.
        insert한 노드들을 이용하여 여러 기능 사용가능.
Variables: 
        <class DLL>
        insertAfter(int data)=>새로운 노드를 현재 위치 노드 뒤에 삽입하는 함수
        insertBefore(int data)=>새로운 노드를 현재 위치 노드 앞에 삽입하는 함수
        insertFirst(int data)=>새로운 노드를 리스트 맨 앞에 삽입하는 함수
        insertLast(int data)=>새로운 노드를 리스트 맨 뒤에 삽입하는 함수
        deleteCurrent()=>현재 노드를 삭제하는 함수
        locateCurrent(int n)=>n번째 위치를 입력받고 n번째 데이터 출력하고 현재 위치 노드를 n번째 노드로 지정하는 함수
        updateCurrent(int data)=>현재 위치 노드의 값을 새로운 값으로 변경하는 함수
        displayCurrent()=>현재 위치 노드의 값 출력하는 함수
        display()=>전체 리스트를 출력하는 함수
        length()=>리스트의 길이를 계산하는 함수
        isEmpty()=>리스트가 비어 있는지 확인하는 함수
*/

#include <iostream>
using namespace std;
class Node{
private:
    int data;
    Node *llink, *rlink; //양방향 링크
public:
    Node(int value){
        data=value;
        llink=0; rlink=0; 
    }
    friend class DLL;
};

class DLL{
private:
    Node *head;
    Node *current;
public:
    DLL();
    void insertAfter(int data);
    void insertBefore(int data);
    void insertFirst(int data);
    void insertLast(int data);
    void deleteCurrent();
    void locateCurrent(int n);
    void updateCurrent(int data);
    void displayCurrent();
    void display();
    int length();
    bool isEmpty();
};
DLL::DLL(){
    head=0; current=0;
}
/*function: insertAfter
description: 새로운 노드를 현재 위치 노드 바로 앞에 삽입
variables: temp->새로운 노드
           insert후에는 새로운 노드를 current로 지정*/
void DLL::insertAfter(int data){
    Node *temp=new Node(data);
    if(isEmpty()) {
        head=temp;
        current=head;
    }
    else if(current->rlink!=0){
        temp->llink=current;
        temp->rlink=current->rlink;
        current->rlink=temp;
        temp->rlink->llink=temp;
    }
    else{//current가 마지막 노드일 때
        current->rlink=temp;
        temp->llink=current;
        temp->rlink=0;//마지막 노드의 rlink는 NULL
    }
    current=temp;
}
/*function: insertBefore
description: 새로운 노드를 현재 위치 노드 바로 뒤에 삽입
variables: temp->새로운 노드
           insert후에는 새로운 노드를 current로 지정*/
void DLL::insertBefore(int data){
    Node *temp=new Node(data);
    if(isEmpty()) {
        head=temp;
        current=temp;
    }
    else if(current==head){//원소 하나일 때
        temp->rlink=head;
        head->llink=temp;
        head=temp;
        current=temp;
    }
    else{
        int holdData=current->data;//현재 위치의 노드의 값을 새로운 변수에 저장
        current->data=temp->data; //현재 노드의 값을 삽입되는 노드의 값으로 변경
        insertAfter(holdData); //원래 노드의 값을 insertAfter함수를 이용하여 삽입
        current=current->llink;//insertAfter로 current변했음으로 다시 조정
    }
}
/*function: insertFirst
description: 새로운 노드를 리스트 맨 앞에 삽입
variables: temp->새로운 노드
           insert후에는 새로운 노드를 current로 지정*/
void DLL::insertFirst(int data){
    Node *temp=new Node(data);
    if(isEmpty()) head=temp;
    else{
        head->llink=temp;
        temp->rlink=head;
        head=temp;
    }
    current=temp;
}
/*function: insertLast
description: 새로운 노드를 리스트 맨 뒤에 삽입
variables: temp->새로운 노드
           insert후에는 새로운 노드를 current로 지정*/
void DLL::insertLast(int data){
    Node *temp=new Node(data);
    Node *p;
    if(isEmpty()) head=temp;
    else{
        p=head;
        while(p->rlink!=0){//마지막으로 이동
            p=p->rlink;
        }
        p->rlink=temp;
        temp->llink=p;
    }
    current=temp;
}
/*function: deleteCurrent
description: 현재 위치의 노드를 삭제*/
void DLL::deleteCurrent(){
    Node *p, *q; 
    if(isEmpty()) cout << "Doubly linkedList is empty!" << endl;
    else if(head==current){//노드가 하나 있을 때 head와 current 둘 다 NULL
        p=head;
        head=0; current=0;
        delete p;
    }
    else if(current->rlink==0){//current가 마지막 노드일때
        p=head; q=head; 
        while(p->rlink!=0){
            q=p;
            p=p->rlink;
        }
        p=p->rlink;
        q->rlink=0;//current 앞의 노드의 rlink는 NULL
        current=q;
        delete p;
    }
    else{
        p=head; q=head;
        while(p!=current){
            q=p;
            p=p->rlink;
        }
        q->rlink=current->rlink;
        p->rlink->llink=q;
        current=p->rlink;
        delete p;
    }
}
/*function: locateCurrent
description: 입력 받은 N번째 노드를 출력하고 현재 위치의 노드를 N번재 노드로 지정
variables: count->N번째 만큼 이동하기 위해 이동 횟수 계산*/
void DLL::locateCurrent(int N){
    Node *p; int count=1;//isEmpty=false이면, 적어도 노드의 개수 1이므로 count 1부터 시작
    if(isEmpty()) cout << "Doubly linkedList is empty!" << endl;
    else{
        if(length()>=N){
            p=head;
            while(p!=0 && count<N){
                p=p->rlink;
                count++;
            }
            if(p!=0){
                cout << N << "th Node: " << p->data << endl;
            }
            current=p;
        }
        else cout << "No such a line" << endl;
    }    
}
/*function: updateCurrent
description: 현재 노드의 값을 입력받은 새로운 값으로 변경
variables: temp->새로운 노드 생성
           현재 위치 노드의 data값을 새로운 노드의 data값으로 변경*/
void DLL::updateCurrent(int data){
    Node *temp=new Node(data);
    current->data=temp->data;
}
/*function: displayCurrent
description: 현재 위치 노드의 값 출력*/
void DLL::displayCurrent(){
    Node *p;
    if(isEmpty()) cout << "Doubly linkedList is empty!" << endl;
    else{
        p=head;
        while(p!=current){
            p=p->rlink;
        }
        cout << "Current Data: " << p->data << endl;
    }

}
/*function: display
description: 전체 리스트 값 출력*/
void DLL::display(){
    Node *p;
    if(isEmpty()) cout << "Doubly linekedList is empty!" << endl;
    else{
        p=head;
        int n=0;
        while(p!=0){
            cout << ++n;
            if(p==current) cout << " * ";
            else cout << " : ";
            cout << p->data << " " << endl;
            p=p->rlink;
        }
    }
}
/*function: length
description: 리스트의 전체 길이 계산
variables: size->리스트 길이*/
int DLL::length(){
    Node *p;
    int size=0;
    if(!isEmpty()){
        p=head;
        while(p!=0){
            size++;
            p=p->rlink;
        }
    }
    return size;
}
/*function: isEmpty
description: 리스트가 비어 있는지 확인*/
bool DLL::isEmpty(){
    if(head==0) return true;
    else return false;
}
int main(){
    int menu, number, N;
    DLL d;
    while(true){
        cout << "Menu: 1.insertAfter 2.insertBefore 3.insertFirst 4.insertLast 5.deleteCurrent 6.locateCurrent 7. updateCurrent 8.displayCurrent 9.Display 10.Quit ";
        cout << ">>";
        cin >> menu;
        switch (menu){
            case 1:
                cout << "Input node: ";
                cin >> number;
                d.insertAfter(number);
                break;
            case 2:
                cout << "Input node: ";
                cin >> number;
                d.insertBefore(number);
                break;
            case 3:
                cout << "Input node: ";
                cin >> number;
                d.insertFirst(number);
                break;
            case 4:
                cout << "Input node: ";
                cin >> number;
                d.insertLast(number);
                break;
            case 5:
                d.deleteCurrent();
                break;
            case 6:
                cout << "Input Nth: ";
                cin >> N;
                d.locateCurrent(N);
                break;
            case 7:
                cout << "Input new Data: ";
                cin >> number;
                d.updateCurrent(number); 
                break;
            case 8:
                d.displayCurrent();
                break;
            case 9:
                d.display();
                break;
            default:
                break;
        }
        cout << endl;
        if(menu==10) break;
    }
    return 0;
}