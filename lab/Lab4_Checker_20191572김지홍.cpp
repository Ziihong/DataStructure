#include <iostream>
#include <fstream>
#include <string>
#include <stack>
using namespace std;


class Count{
private:
    int balanced, unbalanced, mismatched; 

public:
    Count() {

    }
    Count(int size) {
        balanced = 0; unbalanced = 0; mismatched = 0;
    }
    
    void upBalanced() {
        balanced++;
    }
    void upUnbalanced() {
        unbalanced++;
    }
    void upMismatched() {
        mismatched++;
    }

    int getBalanced() {
        return balanced;
    }
    int getUnbalanced() {
        return unbalanced;
    }
    int getMismatched() {
        return mismatched;
    }

    void check(string exp){
        stack<char> s;
        bool check = false;
        for(int i=0; i<exp.length(); i++){
            char ch;
            if(exp[i]=='(' || exp[i]=='[' || exp[i]=='{'){
                s.push(exp[i]);
            }
            else if(exp[i]==')' || exp[i]==']' || exp[i]=='}'){
                if(s.empty()){
                    cout << "The Expression has unbalanced parentheses" << endl;
                    upUnbalanced();
                    check = true;
                    break;
                }
                else{
                    ch=s.top();
                    s.pop();
                    if(!match(ch, exp[i])){
                        cout << "The Mismatched Parenthes in the Expression are " << ch << "and " << exp[i] << endl; 
                        upMismatched();
                        check = true;
                        break;
                    }
                }
            }
        }
        if (!s.empty() && !check) {
            cout << "The Expression has unbalanced parentheses" << endl;
            upUnbalanced();
        }
        else if(!check) {
            upBalanced();
            cout << "The Expression is Valid" << endl;
        }
    }

    int match(char x, char y){
    	if (x == '(' && y == ')')
    	{
    		return 1;
    	}
    	else if (x == '[' && y == ']')
    	{
    		return 1;
    	}
    	else if (x == '{' && y == '}')
    	{
    		return 1;
    	}
    	return 0;
    }

};


int main(){
    ifstream file;
    string line;
    file.open("C_C++_PROJECTS\\data_lab\\lab4.txt");
    if(!file.is_open()){
        cout << "File open Error!" << endl;
    }
    int i=1;
    Count count(10);
    while(getline(file, line)){
        cout << i << "." << line << endl;
        count.check(line);
        cout << endl;
        i++;
    }
    cout << "Total:  Balanced:" << count.getBalanced() << " Unbalanced:" << count.getUnbalanced() << " Mismatched:" << count.getMismatched() << endl;
    file.close();
    return 0;
}