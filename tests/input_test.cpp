#include "../ConsoleInput.h"
#include <cassert>
#include <sstream>
int main() {
    std::ostringstream out;
    int column=-1, row=-1, choice=-1;
    std::istringstream squares("I1\nA0\nA9\nA2junk\na2\nA2\nH8\n");
    assert(readSquare(squares,out,"",8,column,row) && column==0 && row==1);
    assert(readSquare(squares,out,"",8,column,row) && column==7 && row==7);
    assert(!readSquare(squares,out,"",8,column,row));
    std::istringstream cards("0\n8\nwrong\n2extra\n7\n");
    assert(readChoice(cards,out,"",7,choice) && choice==6);
    assert(!readChoice(cards,out,"",7,choice));
    std::istringstream edge("K10\nJ10\n");
    assert(readSquare(edge,out,"",10,column,row) && column==9 && row==9);
}
