#include <iostream>
#include <string>

#include "RomanAdder.h"

using namespace std;

int main(){
    RomanAdder r( "MD", "CDXLIV" );
    
    cout << r.add() << endl;
    
    return 0;
}
