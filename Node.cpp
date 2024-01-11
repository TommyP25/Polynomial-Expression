#include "Node.h"
#include <string>
#include <sstream>
#include <iomanip>


Node::Node()
{
    coefficient = 1;
    exponent = 1;
    next = NULL;
}

Node::Node(double coef, int expo)
{
    coefficient = coef;
    exponent = expo;
    next = NULL;
}

std::ostream& operator<<(std::ostream& os, const Node* n)
{
    std::string expres = "";
    
    if(n->getCoef() == 1 || n->getCoef() == -1){
        if(n->getExp() == 0){
            expres = n->getCoef();
        }else if(n->getExp() == 1){
            expres = expres + "x";
        }else{
            std::string expo = std::to_string(n->getExp());
            expres = expres + "x^";
            expres = expres + expo;
        }
    }else{
        std::string coef = std::to_string(std::abs(n->getCoef()) );
        size_t decPos = coef.find('.');
        
        if(decPos != std::string::npos && decPos + 4 < coef.length()){
            coef = coef.substr(0, decPos + 4);
        }
        
        expres = expres + coef;
        if(n->getExp() == 0){
            
        }else if(n->getExp() == 1){
            expres = expres + "x";
        }else{
            std::string expo = std::to_string(n->getExp());
            expres = expres + "x^";
            expres = expres + expo;
        }
    }
    os << expres;
    return os;
}
