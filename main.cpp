#include "Node.h"
#include "LinkedList.h"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <cmath>
#include <iomanip>

// Thompson Pham TXP210003

using namespace std;

// This function gets the value of the variable from the function
double getVariable(string givenLine){
    // Finds position of parethesis then cuts the string to only include the value
    size_t start = givenLine.find_first_of("(");
    size_t end = givenLine.find_first_of(")");
    string strVar = givenLine.substr(start + 1, end - start - 1);
    // Converts string to double to be returned
    double variable = stod(strVar);
    return variable;
    
}

// Function looks through sorted list, since its sorted we can look at pairs
// to see if they have the same exponent and combine the term
void combineSimilarExpo(LinkedList& list){
    Node* curr = list.getHead();
    // While loop to look through entire linked list
    while(curr->getNext() != NULL){
        // Looks at pair wise terms to see if the exponents matches
        if(curr->getExp() == curr->getNext()->getExp()){
            // If matches adds the coeficient together, then removes extra linked
            // list and connects
            curr->setCoef(curr->getCoef() + curr->getNext()->getCoef());
            Node* temp = curr->getNext();
            curr->setNext(temp->getNext());
            delete temp;
        }else{
            // If no match, it moves to next pair
            curr = curr->getNext();
        }
    }
}

// Recieves parsed string containing the term, and inserts the values from the 
// term into a Node class
Node* enterNode(string termSpace){
    Node *node = new Node();
    string term = "";
    // Created an empty string, then used a for loop to remove excess characters
    // of spaces and '+'
    for (long unsigned int i = 0; i < termSpace.length(); i++) {
        if (termSpace[i] != ' ' && termSpace[i] != '+') {
            term += termSpace[i];
        }
    }
    
    // Looks through string to find the postion of "x^" if its in the string
    size_t Pos = term.find("x^");
    stringstream ss(term);
    string temp;
    ss >> temp;
    double coef = 0;
    int expo = 0;

    // If the term is just x, we know coef and expo will be 1
    if(temp == "x"){
        coef = 1;
        expo = 1;
        node->setCoef(coef);
        node->setExp(expo);
        return node;
    }
    
    // If the term is just empty, we know is coef is zero and expo can be any number
    if(temp == ""){
        coef = 0;
        expo = 0;
        node->setCoef(coef);
        node->setExp(expo);
        return node;
    }
    
    // This checks if we found a postion for "x^"
    if (Pos != string::npos) {
        // If found we make a string for coef
        string coef_str = temp.substr(0, Pos);
        // If the coef string isn't empty, we can convert to double
        if (!coef_str.empty()) {
            coef = stod(coef_str);
            // Else we make coef = 1
        }else{
            coef = 1;
        }
        // If found we make a string for expo
        string expo_str = temp.substr(Pos + 2);
        // If the expo string isn't empty, we can convert to int
        // Else it is zero
        if (!expo_str.empty()) {
            expo = stoi(expo_str);
        }
    // If "x^" is not found
    }else{
        // It means there is only the coef
        string coefOnly = "";
        // Remove any excess character so we can convert to double
        for (long unsigned int i = 0; i < temp.length(); i++) {
            if (temp[i] != 'x' && temp[i] != '^') {
                coefOnly += temp[i];
            }
        }
        
        coef = stod(coefOnly);
    }
    // Put coef and expo value we found into node
    node->setCoef(coef);
    node->setExp(expo);
    
    return node;
}

int main()
{
    string fileName;
    // Ask file name
    cout << "Input file name: ";
    cin >> fileName;
    // Check if file is able to be opened, if not close program
    ifstream input(fileName);
    if(!input){
        cout << "Unable to open file" << endl;
        return 0;
    }
    
    string line, variable;
    double total = 0;
    // If open we read file per line
    while(getline(input, line)){
        LinkedList expression = LinkedList();
        // Get variable
        double var = getVariable(line);
        // Remove to get just expression
        size_t equal_pos = line.find("=");
        if(equal_pos != string::npos){
            line = line.substr(equal_pos + 1);
        }
        
        string term, endTerm, sign = "";
        // While loop to go through each term
        while(line.length() != 0){
            // Find postion of addition and substraction sign
            size_t plus = line.find('+');
            size_t minus = line.find(" -");
            // Which ever is smaller means the end of the string for one term
            long unsigned int endTerm = min(plus, minus);
            
            string term = "";
            // If end of the string for the term is valid
            if (endTerm != -1) {
                // Parses term
                term = line.substr(0, endTerm);
                term = sign + term;
                
                // Take record if were add and substracting with the next term,
                // then deleting the term with the sign else the sign would block
                // figuring out next term
                sign = line.substr(endTerm, 1);
                if (sign != "+" && sign != "-")
                    sign = "";
                line = line.substr(endTerm + 1);
                
            // If end of string not valid, it means were on the last term
            }else{
                term = sign + line;
                line = "";
            }
            //Enter into node
            Node *newTerm = enterNode(term);
            total += (newTerm->getCoef()) * (pow(var, newTerm->getExp()));
            // Add the calulated total from the term and variable value
            
            // Check if the the value of the coef is too small to add to link list
            // and print out
            if(abs(newTerm->getCoef()) < 0.00099999){
                
            }else{
                  expression += newTerm;
            }
        }
        // Sort Expression
        expression.sortList();
        // Combine terms with same exponent value
        combineSimilarExpo(expression);
        // Print results
        cout << expression << " = " << fixed << setprecision(3) << total << endl;
        // Reset total for next line
        total = 0;
    }
    

    return 0;
}
