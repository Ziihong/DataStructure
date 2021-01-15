/*
Name: 김지홍
Student ID: 20191572
Program ID: hw5_MakeSortHeap
Description: binary tree로 이루어진 자료를 Max Heap으로 변환하는 함수를 만들고 Max Heap을 오름차순으로 정렬하는 sort()함수를 구현한다.
Algorithm: make Max Heap=> (배열의 크기/2)부터 하나씩 줄여가며 adjust()함수를 실행한다.
           make sort Heap=> (배열의 크기-1)부터 하나씩 줄여가며 배열의 첫번째 값과 마지막 값을 변경하고 adjust()함수를 실행한다.
           adjust(array, index, size)=> child의 index=주어진 index*2
                                        array[index]=temp로 임시저장
                                        (child가 heap의 크키보다 작을 때까지) left child < right child 라면, child=child+1
                                                                             현재 부모 index의 값 < 현재 자식 index의 값이라면 array[parent]=array[child], child=child*2, array[child]=temp
Variables: 
        insertHeap()=>binary tree 또는 heap 구조에 새로운 data 삽입
        deleteHeap()=>binary tree 또는 heap 구조에서 top element 삭제
        searchHeap()=>binart tree 또는 heap 구조에서 특정 값이 있는지 확인
        print()=>배열의 내용 출력
        printLevel()=>배열의 level 출력
        adjust()=>binary tree->heap으로 변활할때, Max heap을 sort할 때 사용하는 함수. 부모 노드의 값과 자식 노드의 값을 비교하여 부모 노드의 위치에 더 큰 값이 오도록 조정
        makeHeap()=>binary tree->heap으로 변환
        sortHeap()=>Max heap을 오름차순으로 정렬
        heapFull()=>배열이 최대 크기만큼 채워졌는지 확인
        heapEmpty()=>배열이 비어있는지 확인
*/
#include <iostream>
#include <algorithm>
using namespace std;

#define MAX_SIZE 11 //heap 최대 크기는 11로 지정
/*class: Heap
description: binary tree 또는 heap 형태로 저장된 data를 제어하기 위한 클래스
variables: heap_size=> Heap의 크기
           heap[]=> binary tree or heap 저장 공간
           is_Heap=> 자료구조가 heap인지 아닌지(makeHeap()이 실행 되었는지 아닌지) 확인*/
class Heap{
public:
    int heap_size=0;
    int heap[MAX_SIZE+1];
    bool is_Heap=false;
    //생성자 함수에서 초기 입력 데이터 하나씩 insertHeap함수 실행
    Heap(){
        int createArray[]={26, 5, 77, 1, 61, 11, 59, 15, 48, 19};
        for(int i=0; i<sizeof(createArray)/sizeof(createArray[0]); i++){
            insertHeap(createArray[i]);
        }
    }
    void insertHeap(int data);
    int deleteHeap();
    void searchHeap(int data);
    void print();
    int printLevel();
    void adjust(int* lst, int idx, int size);
    void makeHeap();
    void sortHeap();
    bool heapFull();
    bool heapEmpty();
};
/*function: insertHeap
description: 배열에 새로운 data 추가
             binary tree일때=>배열의 마지막 위치에 data 저장
             heap일때=>배열의 마지막 위치에 저장하고 부모 노드의 값과 비교하며 (추가한 값 > 부모 노드의 값)일 경우, 두 노드의 위치 변경*/
void Heap::insertHeap(int data){
    if(!heapFull()){
        //binary tree일 때
        if(is_Heap==false){
            heap[++heap_size]=data;
        }
        //heap일 때
        else{
            int idx=++heap_size;//heap[0]는 사용하지 않음
            while(idx!=1 && data>heap[idx/2]){ //새로운 값이 부모 노드의 값보다 클 경우, 부모 노드의 값을 자식 노드의 값으로 저장
                heap[idx]=heap[idx/2];
                idx=idx/2;
            }
            heap[idx]=data;
        }
        return ;
    }
    cout << "Heap is full!" << endl;
}
/*function: deleteHeap
description: 배열의 top element 삭제
             binary tree일 때=>배열의 마지막 값을 배열의 첫번째 위치로 이동하고 배열의 첫번째 값 삭제
             heap일 때=>배열의 마지막 값을 배열의 첫번째 위치로 이동하고 배열의 첫번째 값 삭제. 그 이동한 값을 시작으로 다시 Max heap을 구성
variables: deleteItem=>삭제할 노드. 배열의 첫번째 값
           parent=>부모 인덱스 값
           child=>자식 인덱스 값(=부모 인덱스 *2)
           last=>heap일 경우, 배열의 마지막 값을 저장*/
int Heap::deleteHeap(){
    if(heapEmpty()){
        cout << "Heap is empty!" << endl;
    }
    else{
        int deleteItem=heap[1];
        //binary tree일 때
        if(is_Heap==false){
            heap[1]=heap[heap_size];
        }
        //heap일 때
        else{
            int parent, child, last;
            last=heap[heap_size];
            parent=1; child=2;
            while(child <= heap_size){
                if(child<heap_size && heap[child]<heap[child+1]) child++;//left child < right child 일때 child+=1을 함으로써 더 큰 값으로 실행
                if(last >= heap[child]) break; //아래 코드들은 (부모 노드의 값 < 자식 노드의 값)일 때 부모 노드에 큰 값 저장
                heap[parent]=heap[child];
                parent=child;
                child=child*2;
            }
            heap[parent]=last;
        }
        heap_size--;//삭제한 다음 heap 크기 -1
        return deleteItem;
    }
}
/*function: searchHeap
description: 특정 값이 배열 안에 존재하는지 확인*/
void Heap::searchHeap(int data){
    for(int i=1; i<=heap_size; i++){
        if(data==heap[i]){
            cout << data << " is found" << endl;
            return;
        }
    }
    cout << data << " is not found" << endl;
}
/*function: print
description: 배열 안의 값 출력*/
void Heap::print(){
    for(int i=1; i<=heap_size; i++){
        cout << heap[i] << " ";
    }
    cout << endl;
}
/*fucntion: printLevel
description: 배열의 level 출력
variables: idx=>1, 2, 4, 8,,,과 같이 2의 거듭제곱을 나타내며, level 계산의 기준점
           level=>해당 배열의 level*/
int Heap::printLevel(){
    int idx=1, level=0;
    for(int i=1; i<=heap_size; i++){
        if(i==idx){
            level++;
            idx*=2;
        }
    }
    return level;
}
/*function: adjust
description: Make heap이나 Sort heap할 때 이용하는 함수. 
            주어진 index의 값의 노드를 temp에 저장. child 노드는 주어진 index*2하여 (부모 노드의 값 < 자식 노드의 값)일 때 부모 노드에 더 큰 값을 저장하도록 while문 구현*/
void Heap::adjust(int* lst, int idx, int size){
    int child, pos, temp;
    child=2*idx;
    temp=lst[idx];
    while(child <= size){
        if(child<size && lst[child]<lst[child+1]) child=child+1;
        if(temp>=lst[child]) break;
        pos=child/2;
        lst[pos]=lst[child];
        child=child*2;
    }
    pos=child/2;
    lst[pos]=temp;
    return ;
}
/*function: makeHeap
description: binary tree->heap 으로 변환*/
void Heap::makeHeap(){
    is_Heap=true;
    cout << "Before make heap: "; print();

    for(int idx=heap_size/2; idx>0; idx--){
        adjust(heap, idx, heap_size);
    }

    cout << "After make heap: "; print();
}
/*function: sortHeap
description: Max heap을 오름차순으로 정렬*/
void Heap::sortHeap(){
    for(int idx=heap_size-1; idx>0; idx--){
        swap(heap[1], heap[idx+1]);
        adjust(heap, 1, idx);
        if(idx==1) cout << "Heap Sort: "; 
        print();
    }
}
/*function: heapFull
description: 배열의 크기가 최대 크기만큼 인지 확인*/
bool Heap::heapFull(){
    if(heap_size==MAX_SIZE) return true;
    else return false;
}
/*function: heapEmpty
description: 배열이 비어있는지 확인*/
bool Heap::heapEmpty(){
    if(heap_size==0) return true;
    else return false;
}
int main(){
    int menu, number;
    Heap h;
    
    while(true){
        cout << "Menu: 1.Insert 2.Delete 3.Search 4.Print 5.Level Print 6.Make Heap 7.Heap Sort 8.Quit >>";
        cin >> menu; 
        switch(menu){
            case 1:
                cout << "Input Number: ";
                cin >> number;
                h.insertHeap(number);
                break;
            case 2:
                h.deleteHeap();
                break;
            case 3:
                cout << "Input search data: ";
                cin >> number;
                h.searchHeap(number);
                break;
            case 4:
                h.print();
                break;
            case 5:
                cout << "Heap level: " << h.printLevel() << endl;
                break;
            case 6:
                h.makeHeap();
                break;
            case 7:
                h.sortHeap();
                break;
            default:
                break;
        }
        if(menu==8) break;
    }
}