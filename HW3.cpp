
#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

 
using namespace std;

struct Formula {
	char word ;
	int num ;
	Formula *next ;
};

typedef Formula *FormulaPtr ;

void Read( FormulaPtr &formula ) {
	char temp ;
	scanf( "%c", &temp ) ;
	if ( temp != '\n' ) {
		formula->word = temp ;
		formula->next = new Formula() ;
		Read( formula->next ) ;
	} // if
	else {
		formula = NULL ;
   }
		
} // Read()

bool Operator( FormulaPtr formula ) {
	if ( formula->word == '+' || formula->word == '-' || formula->word == '*' || formula->word == '/' || formula->word == '%' ) 
		return true ;
	else
	    return false ;

} // Operator


bool Number( FormulaPtr formula ) {
	if ( formula->word <= '9' && formula->word >= '0' ) 
		return true ;
	else
	    return false ;
} // Number

FormulaPtr NextWord( FormulaPtr formula ) {
    if ( formula->next == NULL )
       return NULL ;
	else if ( formula->next->word != ' ' )
		return formula->next ;
	else 
		return NextWord( formula->next ) ;
} // NextWord()

void Change( FormulaPtr formula1, FormulaPtr &formula2 ) {
	FormulaPtr walk ;
	if ( formula1 != NULL ) {
		if ( ! Number( formula1 ) ) {
			formula2->word = formula1->word ;
			formula2->next = new Formula() ;
			formula1 = NextWord( formula1 ) ;
			Change( formula1, formula2->next ) ;
		} // if
		else {
			formula2->word = 'n' ;
			formula2->num = formula1->word - '0' ;
			walk = formula1->next ;
			while ( walk != NULL && Number( walk ) ) {
				formula2->num = (formula2->num * 10 ) + (walk->word - '0') ;
				walk = NextWord( walk ) ;
			} // while
			formula2->next = new Formula() ;
			Change( walk, formula2->next ) ;
		} // else
	} // if
	else 
		formula2 = NULL ;
} // Change()

bool Check( FormulaPtr formula, int openparenthesis, int closeparenthesis ) { 
	if ( formula != NULL ) {
		if ( formula->word == '(' ) {
			openparenthesis++ ;
			if ( NextWord( formula )->word == ')' || Operator( NextWord( formula ) ) ) {
				cout << "Error 3: it is not infix in the parentheses." ;
				return false ;
			} // if
		} // if
		else if ( formula->word == ')' ) {
			closeparenthesis++ ;
			if ( NextWord( formula ) != NULL && Number( NextWord( formula ) ) ) {
				cout << "Error 3: there is one extra operand." ;
				return false ;
			} // if		
			if ( openparenthesis < closeparenthesis ) {
				cout << "Error 2: there is one extra close parenthesis." ;	
				return false ;
			} // if
		} // if
		else if ( Operator( formula ) ) {
			if ( NextWord( formula ) != NULL && Operator( NextWord( formula ) ) ) {
				cout << "Error 3: there is one extra operator." ;
				return false ;
			} // if
		} // if
		else if ( Number( formula ) ) {
			if ( NextWord( formula ) != NULL && NextWord( formula )->word == '(' ) {
				if ( Operator( NextWord( NextWord( formula ) ) ) )
					cout << "Error 3: it is not infix in the parentheses." ;
				else
					cout << "Error 3: there is one extra operand." ;
				return false ;
			} // if			
		} // if
		else {
			cout << "Error 1: " << formula->word << " is not a legitimate character." ;
			return false ;
		}
		
		if ( openparenthesis < closeparenthesis ) {
			cout << "Error 2: there is one extra close parenthesis." ;	
			return false ;
		} // if

		formula = NextWord( formula ) ;
		return Check( formula, openparenthesis, closeparenthesis ) ;
	}
	else if ( openparenthesis != closeparenthesis ) {
		if ( openparenthesis > closeparenthesis )
			cout << "Error 2: there is one extra open parenthesis." ;	
		return false ;	
	} // if
	else {
		cout << "It is a legetimate infix expression." ;
		return true ;
	}
} // Check()

void Postfix( FormulaPtr formula, FormulaPtr count, bool first ) {
	FormulaPtr temp ;
	if  ( formula != NULL ) {
		if ( formula->word == 'n' ) {
			if ( first ) {
				cout << formula->num ;
				first = false ;
			} // if
			else
				cout << ", " << formula->num ;
			Postfix( formula->next, count, first ) ;
		} // if
		else {
			if ( formula->word == ')' ) {
				while ( count->word != '(' ) {
					cout << ", " << count->word ;
					count = count->next ;
				} // while
				count = count->next ;
				Postfix( formula->next, count, first ) ;
			} // if
			else if ( formula->word == '(' || count == NULL || count->word == '(') {
				temp = count ;
				count = new Formula() ;
				count->word = formula->word ;
				count->next = temp ;
				Postfix( formula->next, count, first ) ;
			} // if
			else if ( formula->word == ')' ) {
				while ( count->word != '(' ) {
					cout << ", " << count->word ;
					count = count->next ;
				} // while
				count = count->next ;
				Postfix( formula->next, count, first ) ;
			} // if
			else if ( formula->word == '+' || formula->word == '-' ) {
				if( count->word == '+' || count->word == '-' ) {
					cout << ", " << count->word ;
					count->word = formula->word ;
					Postfix( formula->next, count, first ) ;
				} // if
				else {
					while ( count != NULL && count->word != '(' ) {
						cout << ", " << count->word ;
						count = count->next ;
					} // while
					Postfix( formula, count, first ) ;
				} // else
			} // if
			else if ( formula->word == '*' || formula->word == '/' || formula->word == '%' ) {
				if( count->word == '*' || count->word == '/' || count->word == '%' ) {
					cout << ", " << count->word ;
					count->word = formula->word ;
				} // if
				else {
					temp = count ;
					count = new Formula() ;
					count->word = formula->word ;
					count->next = temp ;
				} // else
				Postfix( formula->next, count, first ) ;
			} // if
		} // else
	} // if
	else {
		while ( count != NULL ) {
			cout << ", " << count->word  ;

			count = count->next ;
		} // while
		delete count ;
	} // else
} // Postfix

void Print( FormulaPtr formula ) {
	if ( formula != NULL ) {
		if ( formula->word == 'n' )
			printf( "%d", formula->num ) ;
		else
			printf( "%c", formula->word ) ;
			
		Print( formula->next ) ;
	} // if
} // Print()

int main() {
	int openparenthesis = 0 ;
	int closeparenthesis = 0 ;
	bool first = true ;
	FormulaPtr count ;
	FormulaPtr formula ;
	FormulaPtr formula2 ;
	formula = new Formula() ;
	Read( formula ) ;
	if ( Check( formula, openparenthesis, closeparenthesis ) ) {
	    cout << '\n' << "Input: " ;
		Print( formula ) ;
		cout << '\n' ;
		formula2 = new Formula() ;
		count = NULL ;
        Change( formula, formula2 ) ;
        delete formula ;
        cout << "Postfix expression: " ;
        Postfix( formula2, count, first ) ;
        delete formula2 ;
	} // if 

} // main()

