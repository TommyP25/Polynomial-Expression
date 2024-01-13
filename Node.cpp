#include "Node.h"
#include <string>
#include <sstream>
#include <iomanip>

// Default
Node::Node()
{
    coefficient = 1;
    exponent = 1;
    next = NULL;
}

// Overload
Node::Node(double coef, int expo)
{
    coefficient = coef;
    exponent = expo;
    next = NULL;
}

// << overload operator
std::ostream& operator<<(std::ostream& os, const Node* n)
{
    std::string expres = "";
    // Check if coef is 1 or -1, either term is 1, x, or x^ with some exponent
    if(n->getCoef() == 1 || n->getCoef() == -1){
            // If expo is 0, means term is just 1
            if(n->getExp() == 0){
            std::string coef = std::to_string(std::abs(n->getCoef()) );
            size_t decPos = coef.find('.');
            
            if(decPos != std::string::npos && decPos + 4 < coef.length()){
                coef = coef.substr(0, decPos + 4);
            }
            
            expres = coef;
        // If expo is 1, means term is just x
        }else if(n->getExp() == 1){
            expres = expres + "x";
        // If expo is greater than 1, means term is x^ of expo
        }else{
            std::string expo = std::to_string(n->getExp());
            expres = expres + "x^";
            expres = expres + expo;
        }
    // Else term is coef, coef x, or coef x^ with some expo
    }else{
        // Parse the coef
        std::string coef = std::to_string(std::abs(n->getCoef()) );
        size_t decPos = coef.find('.');
        if(decPos != std::string::npos && decPos + 4 < coef.length()){
            coef = coef.substr(0, decPos + 4);
        }
        // Add coef to string
        expres = expres + coef;
        // If expo is zero, term is coef 
        if(n->getExp() == 0){
            
        // If expo is 1, term is coef x
        }else if(n->getExp() == 1){
            expres = expres + "x";
        // Else term is coef x^ expo
        }else{
            std::string expo = std::to_string(n->getExp());
            expres = expres + "x^";
            expres = expres + expo;
        }
    }
    os << expres;
    return os;
}
