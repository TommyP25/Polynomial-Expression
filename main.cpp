#include "Node.h"
#include "LinkedList.h"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <cmath>
#include <iomanip>

using namespace std;

double getVariable(string givenLine){
    size_t start = givenLine.find_first_of("(");
    size_t end = givenLine.find_first_of(")");
    string strVar = givenLine.substr(start + 1, end - start - 1);
    double variable = stod(strVar);
    return variable;
    
}

void combineSimilarExpo(LinkedList& list){
    Node* curr = list.getHead();
    while(curr->getNext() != NULL){
        if(curr->getExp() == curr->getNext()->getExp()){
            curr->setCoef(curr->getCoef() + curr->getNext()->getCoef());
            Node* temp = curr->getNext();
            curr->setNext(temp->getNext());
            delete temp;
        }else{
            curr = curr->getNext();
        }
    }
}


Node* enterNode(string termSpace){
    Node *node = new Node();
    string term = "";
    for (long unsigned int i = 0; i < termSpace.length(); i++) {
        if (termSpace[i] != ' ' && termSpace[i] != '+') {
            term += termSpace[i];
        }
    }
    
    size_t Pos = term.find("x^");
    stringstream ss(term);
    string temp;
    ss >> temp;
    double coef = 0;
    int expo = 0;
    
    if(temp == "x"){
        coef = 1;
        expo = 1;
        node->setCoef(coef);
        node->setExp(expo);
        return node;
    }
    
    if (Pos != string::npos) {
        string coef_str = temp.substr(0, Pos);
        if (!coef_str.empty()) {
            coef = stod(coef_str);
        }else{
            coef = 1;
        }
        string expo_str = temp.substr(Pos + 2);
        if (!expo_str.empty()) {
            expo = stoi(expo_str);
        }
    } else {
        string coefOnly = "";
        for (long unsigned int i = 0; i < temp.length(); i++) {
            if (temp[i] != 'x' && temp[i] != '^') {
                coefOnly += temp[i];
            }
        }
        
        coef = stod(coefOnly);
    }
            node->setCoef(coef);
            node->setExp(expo);

    
    return node;
}

int main()
{
    string fileName;
    cout << "Input file name: ";
    cin >> fileName;

    ifstream input(fileName);
    
    if(!input){
        cout << "Unable to open file" << endl;
        return 0;
    }
    string line, variable;
    double total = 0;
    while(getline(input, line)){
        LinkedList expression = LinkedList();
        
        double var = getVariable(line);
        
        size_t equal_pos = line.find("=");
        if(equal_pos != string::npos){
            line = line.substr(equal_pos + 1);
        }
        
        string term, endTerm, sign = "";
        while(line.length() != 0){
            size_t plus = line.find('+');
            size_t minus = line.find('-');
            int endTerm = min(plus, minus);
            
            string term = "";
            if (endTerm != -1) {
                term = line.substr(0, endTerm);
                term = sign + term;
                
                sign = line.substr(endTerm, 1);
                if (sign != "+" && sign != "-")
                    sign = "";
                        
                line = line.substr(endTerm + 1);
            } else {
                term = sign + line;
                line = "";
            }
            
            
            Node *newTerm = enterNode(term);
            total += (newTerm->getCoef()) * (pow(var, newTerm->getExp()));
            expression += newTerm;
        }
        
        expression.sortList();
        combineSimilarExpo(expression);
        cout << expression << " = " << fixed << setprecision(3) << total << endl;
        total = 0;
    }
    

    return 0;
}
