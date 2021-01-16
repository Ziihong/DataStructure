#include <iostream>
using namespace std;
const int S_MAXSIZE=2;
const int Q_MAXSIZE=3;
class Stack{
private:
    char stack[S_MAXSIZE]; int top;
public: 
    Stack() {top=-1;}
    void push(char item) {if(top==S_MAXSIZE-1) stackFull(); else stack[++top]=item;}
    char pop(){
        if(top==-1) return stackEmpty();
        else return stack[top--];
    }
    bool stackFull(){
        if(top==S_MAXSIZE-1){
            cout << "Stack is Full!" << endl;
            return true;
        }
        else return false;
    }
    bool stackEmpty(){
        if(top==-1){
            cout << "Stack is Empty!" << endl;
            return true;
        }    
        else return false;}
    void displayStack(){
        if(top==-1) stackEmpty();
        else{
            int index=top;
            while(index!=-1){
                cout << stack[index] << " ";
                --index;
            }
            cout << endl;
        }
    }
};
class Queue{
private:
    char queue[Q_MAXSIZE]; int front, rear;
public: 
    Queue(){front=-1; rear=-1;}
    void enqueue(char item){
        if(rear==Q_MAXSIZE-1){queueFull();}
        else queue[++rear]=item;
    }
    char dequeue(){
        if(front==rear){
            return queueEmpty(); 
        }
        else return queue[++front];
    }
    bool queueFull(){
        if(rear==Q_MAXSIZE-1){
        cout << "Queue is Full!" << endl; 
        return true;
        } 
        else return false;
    }
    bool queueEmpty(){
        if(front==rear){
            cout << "Queue is Empty!" << endl;
            return true;
        }
        else return false;
    }
    void displayQueue(){
        if(front==rear){
            queueEmpty();
        }
        else{
            int index=front+1;
            while(index<=rear){
                cout << queue[index] << " ";
                index++;
            }
            cout << endl;
        }
    }
};
class C_Queue{
private:
    char c_queue[Q_MAXSIZE]; int front=-1, rear=-1, flag=0;
public:
    void c_enqueue(char item){
        rear=(rear+1)%Q_MAXSIZE;
        if(front==rear && flag==1) cout << "Circular is Queue is Empty!" << endl;
        else c_queue[rear]=item;
        flag=1;
    }
    char c_dequeue(){
        if(front==rear && flag==0){
            cout << "Circular is Queue is Empty!" << endl;
            return '\0';
        }
        else{
            front=(front+1)%Q_MAXSIZE;
            flag=0;
            return c_queue[front];
        }
    }
    void c_queueDisplay(){
        if(front==rear && flag==0){
            cout << "Circular Queue is Empty!" << endl;
        }
        else{
            int index=front+1;
            while(index!=rear){
                cout << c_queue[index] << " ";
                index=(index+1)%Q_MAXSIZE;
            }
            cout << c_queue[rear] << endl;
        }
    }

};
int main(){
    Stack s; Queue q; C_Queue c;
    //1)
    s.push('a');
    q.enqueue('b');
    q.enqueue('c'); 
    q.enqueue('d');
    s.push('e');
    //2)
    cout << "2--------------------" << endl;
    s.push('F');
    q.enqueue('G');
    //3)4)
    cout << "3,4------------------" << endl;
    cout << "Stack: ";
    s.displayStack();
    cout << "Queue: ";
    q.displayQueue();
    //5
    cout << "5--------------------" << endl;
    cout << "Output: " << s.pop() << " " << q.dequeue() << " " << q.dequeue() << " " << q.dequeue() << " " << s.pop() << endl;
    //6
    cout << "6---------------------" << endl;
    s.pop();
    q.dequeue();
    //7
    c.c_enqueue('A');
    c.c_enqueue('B');
    c.c_enqueue('C');
    c.c_dequeue();
    c.c_enqueue('D');
    //8
    cout << "8---------------------" << endl;
    c.c_queueDisplay();
    //9
    cout << "9----------------------" << endl;
    c.c_dequeue();
    c.c_dequeue();
    c.c_dequeue();
    c.c_dequeue();
    return 0;

}
