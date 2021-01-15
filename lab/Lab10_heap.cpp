#include <iostream>
#include <string>
using namespace std;

#define MAX_SIZE 8
class Heap{
public:
    int heap[MAX_SIZE+1];
    int heap_size=0;
    Heap(){
        int array[]={8, 6, 4, 2, 5, 3};
        for(int i=0; i<sizeof(array)/sizeof(array[0]); i++){
            insertHeap(array[i]);
        }
    }
    void insertHeap(int data);
    int deleteHeap();
    void searchHeap(int data);
    int printLevel();
    void print();
    bool heapFull();
    bool heapEmpty();

};
void Heap::insertHeap(int data){
    if(heapFull()){
        cout << "Heap is full!" << endl;
        return;
    }
    int idx=++heap_size;
    while(idx!=1 && data>heap[idx/2]){
        heap[idx]=heap[idx/2];
        idx=idx/2;
    }
    heap[idx]=data;   
}
int Heap::deleteHeap(){
    int deleteItem, last, parent, child;
    deleteItem=heap[1];
    last=heap[heap_size];
    parent=1;
    child=2;
    while(child <= heap_size){
        if(child<heap_size && heap[child]<heap[child+1]) child++;
        if(last>heap[child]) break;
        heap[parent]=heap[child];
        parent=child;
        child=2*child;
    }
    heap[parent]=last;
    heap_size--;
    return deleteItem;
}
void Heap::searchHeap(int data){
    int answer=0;
    for(int idx=1; idx<=heap_size; idx++){
        if(heap[idx]==data){
            answer=1;
            break;
        }
    }
    if(answer==1) cout << data << " is found." << endl;
    else cout << data << " is not found." << endl;
}
void Heap::print(){
    for(int idx=1; idx<=heap_size; idx++){
        cout << heap[idx] << " ";
    }
    cout << endl;
}
int Heap::printLevel(){
    int level=0, pos=1;
    for(int idx=1; idx<=heap_size; idx++){
        if(idx==pos){
            level++;
            pos*=2;
        }
    }
    return level;
}
bool Heap::heapFull(){
    if(heap_size==MAX_SIZE) return true;
    else return false;
}
bool Heap::heapEmpty(){
    if(heap_size==0) return true;
    else return false;
}
int main(){
    int menu;
    int array[MAX_SIZE], array_size=0;

    Heap h;
    while(true){
        cout << "Menu: 1.Insert 2.Delete 3.Search 4.Print 5.Heap_empty 6.Heap_full 7.levelPrint 8.Quit >>";
        cin >> menu;
        if(menu==1){
            int number;
            cout << "Input Number: "; cin >> number;
            h.insertHeap(number);
        }
        else if(menu==2) {
            h.deleteHeap();
        }
        else if(menu==3){
            int number;
            cout << "Input Number: "; cin >> number;
            h.searchHeap(number);
        }
        else if(menu==4){
            h.print();
        }
        else if(menu==5){
            if(h.heapEmpty()) cout << "Heap is empty!" << endl;
            else cout << "Heap is not empty!" << endl;
        }
        else if(menu==6){
            if(h.heapFull()) cout << "Heap is full!" << endl;
            else cout << "Heap is not full!" << endl;
        }
        else if(menu==7){
            cout << "Heap level: " << h.printLevel() << endl;
        }
        else if(menu==8) break;
        else{
            cout << "Please Input Menu number." << endl;
        }
    }
    return 0;
}