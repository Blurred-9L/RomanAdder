#ifndef ROMAN_ADDER
#define ROMAN_ADDER

#include <string>
using std::string;

#define LETTERS 26

class RomanAdder{
    private:
        string _addend1;
        string _addend2;
        int symbolCounter[LETTERS];
        
        int getValue( char symbol );
        char getLetter( int value );
        void appendLetters( int value, int nextValue, string& addend );
        void normalizeAddend( string input, string& addend );
        void countSymbols( const string& addend );
        void simplify( int symbolCounter[] );
        
    public:
        RomanAdder();
        RomanAdder( const string& a, const string& b );
        ~RomanAdder();
        void setAddend1( const string& a );
        void setAddend2( const string& b );
        const char* getAddend1() const;
        const char* getAddend2() const;
        string add();
};

#endif //ROMAN_ADDER