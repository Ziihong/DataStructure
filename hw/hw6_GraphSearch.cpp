/*
Name: 김지홍
Student ID: 20191572
Program ID: hw6_GraphSearch
Description: graph를 adjacent List(인접 리스트)를 이용하여 표현한다. 각 vertex에 대해 Singliy Linked List가 존재한다.
Algorithm: 각 vertex를 나타내는 싱글 리스트 형태의 배열을 만들고 파일을 읽어 인접한 정점의 쌍을 받아 graph를 그린다.
Variables: buildTree=>Undirected Graph일 경우, 두 vertex가 양방향인 것을 고려한 함수
           linkeNode=>입력 받은 두 개의 vertex 값으로 싱글 리스트 형태의 배열에 저장 가능한 함수
           printTree=>각 vertex와 연결된 vertex출력하는 함수
           dfs=>특정 노드에서 시작해서 다음 branch로 넘어가기 전에 해당 branch를 완벽하게 탐색하는 함수
*/
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

/*class: Node
description: 각 Node의 data와 link값*/
class Node{
friend class Tree;
private:
    int data;
    Node *link;
public:
    Node(int value){data=value; link=0;}
};
/*class: Tree
description: Graph를 생성하고 Graph와 관련된 함수 실행
variables:
        graph_size=>해당 Graph의 크기
        visite[]=>탐색할 때에 그 vertex를 방문했는지 확인
        vertexx[][]=>인접 리스트. 각 vertex에 대해 싱글 리스트가 존재*/
class Tree{
private:
    int graph_size;
    int *visited;
    Node **vertex;
public:
    Tree(int size);
    void buildTree(int v1, int v2);
    void linkNode(int v_idx, int v);
    void printTree();
    void dfs(int v);
};
Tree::Tree(int size){
    graph_size=size;//클래스 생성시 전달 받은 size로 Graph 크기 초기화
    vertex=new Node *[size];
    visited=new int[size];
    for(int i=0; i<size; i++){
        Node *temp=new Node(i);
        vertex[i]=temp;//인접 리스트
        visited[i]=0;//방문했는지 확인
    }
}
/*function: buildTree
description: Undirected Graph일 경우 두 vertex가 양방향으로 인접할 수 있도록한다*/
void Tree::buildTree(int v1, int v2){//입력 받는 데이터 비방향
    linkNode(v1, v2);
    linkNode(v2, v1);
}
/*function: linkNode
description: 인접 리스트 구현. 두 vertex를 인접하게 만든다
*/
void Tree::linkNode(int v_idx, int v){
    Node *temp=new Node(v);
    Node *p=vertex[v_idx];//vertex

    while(p->link!=0){
        p=p->link;
    }
    p->link=temp;//vertex의 마지막에 연결
}
/*
function: dfs
description: 깊이 우선 탐색. 특정 노드에서 시작해서 다음 branch로 넘어가기 전에 해당 branch를 완벽하게 탐색한다*/
void Tree::dfs(int v){
    visited[v]=1; //방문하였으므로
    cout << v << " ";
    Node *p=vertex[v];
    while(p!=0){
        if(!visited[p->data]) dfs(p->data);//방문하지 않은 정점->탐색
        p=p->link;
    }
}
/*function: printTree
description: 인접 리스트의 data값을 출력한다*/
void Tree::printTree(){
    for(int i=0; i<graph_size; i++){
        cout << "Vertex[" << i << "]: ";
        Node *p=vertex[i];
        while(p->link!=0){
            p=p->link;
            cout << p->data << " ";
        }
        cout << endl;
    }
}
int main(){
    ifstream file; string line;
    file.open("C:\\vscode\\C++_PROJECTS\\data_hw\\hw6.txt");
    if(!file.is_open()) {
        cout << "File open is error!" << endl;
        return 0;
    }

    Tree t1(8), t2(6);
    int is_diffent=0;//입력 데이터가 2개이므로 구분하기 위한 변수
    while(getline(file, line)){
        if(line==""){
            is_diffent=1;
            continue;
        }
        if(is_diffent==0) t1.buildTree(line.at(0)-'0', line.at(2)-'0');
        else t2.buildTree(line.at(0)-'0', line.at(2)-'0');
    }
    cout << "----------Graph data 1----------" << endl;
    t1.printTree();
    cout << "Depth first search: "; t1.dfs(0); cout << endl << endl;

    cout << "----------Graph data 2----------" << endl;
    t2.printTree();
    cout << "Depth first search result: "; t2.dfs(0); cout << endl;
    
    return 0;
}