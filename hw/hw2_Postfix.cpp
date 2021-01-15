/*
Name: 김지홍
Student ID:  20191572
Program ID: Hw2_Postfix
Description: 수식을 중위 표기법(Infix notation)에서 후위 표기법(Postfix notation)으로 변환한다.
            후위 표기법은 괄호를 사용하지 않고 연산자의 우선순위가 없어, 계산이 간편하다는 장점이 있다.(주로 compiler 사용) 
Algorithm: 중위 표기법(Infix notation)으로 표현된 수식을 차례로 읽는다.
            '('일 경우-stack에 저장한다.
            ')'일 경우-stack에 저장되어 있는 '('을 만나기 전까지 최상위 요소들을 차례로 출력하고 삭제한다. '('은 출력하지 않고 삭제한다.
            연산자일 경우-방금 읽은 연산자가 stack 최상위에 저장되어 있는 연산자 보다 우선 순위가 높으면(>), 그대로 stack에 저장한다.
                        그렇지 않으면(<=), stack 최상위 요소를 출력하고 삭제한다. 그 다음 방금 읽은 연산자를 stack에 저장한다.
            피연산자일 경우-그대로 출력한다.
Variables: 
    main()=>File I/O를 이용하여 수식을 읽고 중위 표기법(Infix notation)->후위 표기법(Postfix notation)변환 결과를 출력한다.
    prior()=>연산자들 우선 순위를 return한다.
    postfix()=>중위 표기법(Infix notation)으로 표현된 수식을 입력 받고 후위 표기법(Postfix notation) 변환 결과를 return한다.
    eval()=>후위 표기법(Postfix notation)으로 표현된 수식을 입력 받아, 계산하고 그 결과를 return한다.
*/

#include <iostream>
#include <fstream>
#include <string>
#include <stack>
using namespace std;

/*Function: prior()
  Description: Infix->Postfix 변환 과정에서 연산자들 우선순위를 비교한다.
  Variables: ch->연산자 
             prior->우선순위*/
int prior(char c){
    char ch=c;
    int prior;
    if(ch=='('){
        prior=0;
    }
    else if(ch=='+' || ch=='-'){
        prior=1;
    }
    else if(ch=='*' || ch=='/'){
        prior=2;
    }
    else if(ch==')'){
        prior=3;
    }
    return prior;
}

/*Function: postfix()
  Description: 중위 표기법(Infix notation)으로 표시된 수식을 후위 표기법(Postfix notation)으로 변환한다.(Algorithm 참고)
  Variables: line->수식
             s->stack
             answer->출력 요소들을 저장*/
string postfix(string l){
    stack <char> s;
    string line=l;
    string answer="";
    for(int i=0; i<line.length(); i++){
        if(line.at(i)=='('){
            s.push(line.at(i));
        }
        else if(line.at(i)==')'){
            while(s.top()!='('){ //'('을 만나기 전까지 출력하고 삭제.
                answer.push_back(s.top());
                s.pop();
            }
            s.pop(); //'('삭제
        }
        else if(isdigit(line.at(i))){
            answer.push_back(line.at(i));           
        }
        else if(!isdigit(line.at(i))){
            if(s.empty()){ //stack이 비어있을 때. 즉, 연산자를 처음 만났을 때.
                s.push(line.at(i));
            }
            else {
                if(prior(line.at(i)) > prior(s.top())){
                    s.push(line.at(i));
                }
                else{
                    answer.push_back(s.top());
                    s.pop();
                    s.push(line.at(i));   
                }
            }
        }
    }
    while(!s.empty()){ //stack에 저장되어 있는 모든 요소 출력
        answer.push_back(s.top());
        s.pop();
    }
    return answer;


}

/*Function: eval
  Description: 후위 표기법(Postfix notation)으로 표현된 수식을 받아, 계산한다.
               Algorithm: 수식을 차례로 읽는다.
                          피연산자일 경우-stack에 저장한다.
                          연산자일 경우-stack에 저장된 최상위 피연산자 두개를 차례로 불러와 저장하고 stack에서 삭제한다. 읽은 연산자를 이용하여 두 숫자를 계산하고
                          계산 결과를 stack에 저장한다.
  Variables: op1, op2->피연산자
             result->계산 결과*/
int eval(string postfix) {
    stack <int> st;
    int op1, op2;
    int result=0;
    for(int i=0; i<postfix.length(); i++){
        if(isdigit(postfix.at(i))){
            st.push(postfix.at(i)-'0');//char형태로 되어 있는 숫자를 stack에 저장할 때 int형으로 바꾸어 저장한다.
        }
        else{ //연산자
            op2=st.top();
            st.pop();
            op1=st.top();
            st.pop();
            switch (postfix.at(i)){
                case '+':
                    st.push(op1+op2);
                    break;
                case '-':
                    st.push(op1-op2);
                    break;
                case '*':
                    st.push(op1*op2);
                    break;
                case '/':
                    st.push(op1/op2);
                    break;
                default:
                    break;
            }
        }
    }
    result = st.top();
    return result;
}


int main(){
    ifstream file;
    string line, answer;
    int evaluation;
    file.open("C_C++_PROJECTS\\data_hw\\hw2.txt");
    if(!file.is_open()){
        cout << "File open fail!" << endl;
    }
    while(getline(file, line)){
        cout << "1) Enter data(infix form): " << line << endl;
        answer=postfix(line);
        cout << "2) Conversion(postfix form): " << answer << endl;
        evaluation=eval(answer);
        cout << "3) Result: " << evaluation << endl;
        cout << endl;
    }
    return 0;
}