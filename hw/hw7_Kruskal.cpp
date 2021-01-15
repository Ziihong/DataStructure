/*
Name: 김지홍
Student ID: 20191572
Program ID: hw7_Kruskal
Description: 가중치를 가진 Graph edge에 cost값을 저장한다. kruskal은 cost가 가장 적은 신장트리(MST)를 구현하는 방법 중 하나이다.
Algorithm: kruskal=>cost가 적은 edge 순으로 정렬한다(오름차순 정렬)
                    1) 한 번에 한 edge씩 최소 비용 신장 트리를 구축한다. 최소 비용의 edge를 선택한다
                    2) 선택한 edge가 cycle을 형성하지 않으면, MST의 edge로 저장한다.
                       선택한 edge가 cycle을 형성하면, 다음 최소 비용의 edge를 탐색한다.
                    (MST의 edge의 개수 < vertex의 개수 -1)이 될 때까지 1과 2를 반복한다.          
Variables: class Tree=> 받아들인 data를 저장하고 활용하는 클래스
*/

#include <iostream>
#include <fstream>
#include <string>
#define MAX_SIZE 6
using namespace std;

class Node{
friend class Tree;
    char data;
    Node *next;
public:
    Node(char value){
        data=value;
        next=0;
    }
};
/*class Tree
description: 받아들인 data를 저장하고 활용하기 위한 클래스
variables:
        size=>edge의 개수
        data=>파일 입력으로 받아들인 data를 저장하기 위한 배열
        parent=>각 vertex로 구성. kruskal 방식으로 MST를 구할 때 cycle이 형성되는지 확인하기 위한 배열
*/
class Tree{
    int size;
    string *data; 
    char parent[MAX_SIZE];
public:
    Tree();
    void buildTree();
    void printData();
    void sortData();
    int kruskal();
    char findParent(char v);
    bool checkCircle(char v1, char v2);
};
Tree::Tree(){
    char inputData[MAX_SIZE]={'A', 'B', 'C', 'D', 'E', 'F'};
    for(int i=0; i<MAX_SIZE; i++){
        parent[i]=inputData[i]; //parent 배열 각 vertex 값으로 초기화
    }
    buildTree();
}
/*function: buildTree
description: 파일 입력으로 받아들인 data를 저장한다. 
*/
void Tree::buildTree(){
    ifstream file;
    file.open("C:\\vscode\\C++_PROJECTS\\data_hw\\hw7.txt");
    if(!file.is_open()) {
        cout << "File open is error!" << endl;
        return ;
    }
    string line;
    int lines=0;
    while(getline(file, line)){//input 라인수 세기
        lines++;
    }
    size=lines; //size->edge의 개수
    data=new string[size];
    file.clear(); //eofbit 플래그 리셋(파일 다시 읽기 위해)
    file.seekg(0); //파일의 커서 위치를 맨 위로 이동

    int idx=0;
    while(getline(file, line)){//데이터 저장
        data[idx]=line;
        idx++;
    }
}
/*function: printData
description: data 배열을 출력한다.
*/
void Tree::printData(){
    for(int i=0; i<size; i++){
        if(i!=size-1) cout << data[i] << ", ";
        else cout << data[i] << endl;
    }
    cout << endl;
}
/*function: sortData
description: data를 cost가 적은 순서대로 정렬한다.
*/
void Tree::sortData(){
    string temp;
    for(int i=0; i<size-1; i++){
        for(int j=i+1; j<size; j++){
            if(data[j].at(1) < data[i].at(1)){ //data[].at(1)=>cost
                temp=data[i];
                data[i]=data[j];
                data[j]=temp;
            }
        }
    }
}
/*function: kruskal
description: 최소 비용 순대로, cycle을 형성하지 않는 edge를 선택하며 최소 비용을 구한다.
variables:
    count=>MST를 구현하는 edge의 개수
    pos=>data배열의 인덱스
    cost=>최소 비용
*/
int Tree::kruskal(){
    int count=0, pos=0, cost=0;
    while(count < MAX_SIZE-1){
        if(!checkCircle(data[pos].at(0), data[pos].at(2))){ //cycle을 형성하지않으면
            cout << "Edge" << count+1 << ": " << data[pos] << endl;
            cost+=data[pos].at(1)-'0';
            count++;
        }
        pos++;
    }
    cout << endl;
    return cost;
}
/*function: findParent
description: edge들이 cycle을 형성하는지 확인할 때 사용. vertex의 부모 노드를 확인하는 함수
*/
char Tree::findParent(char v){
    int idx=v-'A';
    if(parent[idx]==v) return v;
    else return parent[idx]=findParent(parent[idx]);
}
/*function: checkCircle
description: 두 vertex가 cycle을 형성하는지 확인 
*/
bool Tree::checkCircle(char v1, char v2){
    bool check=false;
    v1=findParent(v1); 
    v2=findParent(v2);
    if(v1==v2) return true; //두 정점의 부모노드가 같으면 cycle형성
    parent[v1-'A']=v2; 
    return false;
}

int main(){
    Tree t;
    cout << "----------------Input Data Print----------------" << endl;
    t.printData(); 
    cout << "----------------Sort Data Print----------------" << endl;
    t.sortData(); t.printData();
    cout << "-----------------Kruskal's MST------------------" << endl;
    cout << "Total Cost: " << t.kruskal() << endl;
    return 0;
}