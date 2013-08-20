#include "RomanAdder.h"

#include <iostream>
using std::cout;
using std::endl;

#include <string>
using std::string;

#include <cstring>
using std::memset;

RomanAdder::RomanAdder() : _addend1(), _addend2() {
}

RomanAdder::RomanAdder( const string& a, const string& b ){
    _addend1 = a;
    _addend2 = b;
}

RomanAdder::~RomanAdder(){
    _addend1.clear();
    _addend2.clear();
}

void RomanAdder::setAddend1( const string& a ){
    _addend1 = a;
}

void RomanAdder::setAddend2( const string& b ){
    _addend2 = b;
}

const char* RomanAdder::getAddend1() const{
    return _addend1.c_str();
}

const char* RomanAdder::getAddend2() const{
    return _addend1.c_str();
}

string RomanAdder::add(){
    string result = "";
    char letterOrder[] = {'M', 'D', 'C', 'L', 'X', 'V', 'I' };
    int size = 7;
    int i, j, index;
    bool done;
    
    normalizeAddend( _addend1, _addend1 );
    normalizeAddend( _addend2, _addend2 );
    // cout << _addend1 << " " << _addend2 << endl;
    memset( symbolCounter, 0, sizeof( int ) * LETTERS );
    countSymbols( _addend1 );
    countSymbols( _addend2 );
    simplify( symbolCounter );
    
    index = letterOrder[0] - 'A';
    for( j = 0; j < symbolCounter[index]; j++ ){
        result += letterOrder[0];
    }
    for( i = 1; i < size; i++ ){
        done = false;
        index = letterOrder[i] - 'A';
        if( i % 2 == 0 ){
            if( symbolCounter[index] == 4 ){
                result += letterOrder[i];
                result += letterOrder[i - 1];
                done = true;
            }
        }
        else if( symbolCounter[index] == 1 && symbolCounter[letterOrder[i + 1] - 'A'] == 4 ){
            result += letterOrder[i + 1];
            result += letterOrder[i - 1];
            done = true;
            i++;
        }
        if( !done ){
            for( j = 0; j < symbolCounter[index]; j++ ){
                result += letterOrder[i];
            }
        }
    }
    
    return result;
}

int RomanAdder::getValue( char symbol ){
    int value;
    
    switch( symbol ){
    case 'I':
        value = 1;
        break;
    case 'V':
        value = 5;
        break;
    case 'X':
        value = 10;
        break;
    case 'L':
        value = 50;
        break;
    case 'C':
        value = 100;
        break;
    case 'D':
        value = 500;
        break;
    case 'M':
        value = 1000;
        break;
    }
    
    return value;
}

char RomanAdder::getLetter( int value ){
    char letter;
    
    switch( value ){
        case 1:
            letter = 'I';
            break;
        case 5:
            letter = 'V';
            break;
        case 10:
            letter = 'X';
            break;
        case 50:
            letter = 'L';
            break;
        case 100:
            letter = 'C';
            break;
        case 500:
            letter = 'D';
            break;
        case 1000:
            letter = 'M';
            break;
    }
    
    return letter;
}

void RomanAdder::appendLetters( int value, int nextValue, string& addend ){
    char letter = 0;
    int times = 4;
    
    if( nextValue == value * 10 ){
        letter = getLetter( value * 5 );
    }
    
    if( letter ){
        addend += letter;
    }
    letter = getLetter( value );
    for( int i = 0; i < times; i++ ){
        addend += letter;
    }
}

void RomanAdder::normalizeAddend( string input, string& addend ){
    int size = input.length();
    int letterValue, nextValue;
    int i;
    
    addend.clear();
    nextValue = getValue( input[0] );
    for( i = 0; i < size - 1; i++ ){
        letterValue = nextValue;
        nextValue = getValue( input[i + 1] );
        if( letterValue < nextValue ){
            appendLetters( letterValue, nextValue, addend );
            i++;
            nextValue = getValue( input[i + 1] );
        }
        else{
            addend += input[i];
        }
    }
    addend += input[i];
}

void RomanAdder::countSymbols( const string& addend ){
    int size = addend.length();
    int i;
    
    for( i = 0; i < size; i++ ){
        symbolCounter[addend[i] - 'A']++;
    }
}

void RomanAdder::simplify( int symbolCounter[] ){
    char letterOrder[] = {'I', 'V', 'X', 'L', 'C', 'D', 'M' };
    int size = 6;
    int i, value;
    int index;
    
    for( i = 0; i < size; i++ ){
        index = letterOrder[i] - 'A';
        if( i % 2 == 0 ){
            if( symbolCounter[index] > 4 ){
                symbolCounter[letterOrder[i + 1] - 'A']++;
                symbolCounter[index] %= 5;
            }
        }
        else{
            symbolCounter[letterOrder[i + 1] - 'A'] += symbolCounter[index] / 2;
            symbolCounter[index] %= 2;
        }
    }
}
