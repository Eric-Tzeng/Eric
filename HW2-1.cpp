
#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

 
using namespace std;

struct Maze {
	char step ;
	bool visited ;
	char laststep ;
	int otheroads ;
	bool right ;
};

void Read( Maze **maze, int nowline, int nowcolumn, int column, int line ) {
	
	while ( nowline < line ) {
		while ( nowcolumn < column ) {
			cin >> maze[nowline][nowcolumn].step ;
			nowcolumn++ ;
		} // while
		nowline++ ;
		nowcolumn = 0 ;
	} // while
} // Read()

void Initialize( Maze **maze, int nowline, int nowcolumn, int column, int line ) {
	while ( nowline < line ) {
		while ( nowcolumn < column ) {
			if ( nowline == 0 && nowcolumn == 0 )
				maze[nowline][nowcolumn+1].laststep = 'R' ;
			maze[nowline][nowcolumn].visited = false ;
			maze[nowline][nowcolumn].otheroads = 0 ;
			maze[nowline][nowcolumn].right = false ;
			nowcolumn++ ;
		} // while
		nowline++ ;
		nowcolumn = 0 ;
	} // while
} // Initialize()

void PutWrong( Maze **maze, int &nowline, int &nowcolumn, int column, int line ) {
	while ( maze[nowline][nowcolumn].otheroads == 0 ) {
		if ( nowline == 0 && nowline == 0 )
		  break ;
        maze[nowline][nowcolumn].right = false ;
		if ( maze[nowline][nowcolumn].laststep == 'R' )
			nowcolumn-- ;
		else if ( maze[nowline][nowcolumn].laststep == 'L' )
			nowcolumn++ ;
		else if ( maze[nowline][nowcolumn].laststep == 'U' )
			nowline++ ;		
		else if ( maze[nowline][nowcolumn].laststep == 'D' )
			nowline-- ;
	} // while
    maze[nowline][nowcolumn].otheroads = 0 ;
} // PutWrong()

bool AnyOtherRoads( Maze **maze, int nowline, int nowcolumn, int column, int line ) {
	if ( maze[nowline][nowcolumn].laststep == 'R' ) {
		
		if (  nowline < line-1 && maze[nowline+1][nowcolumn].step != 'O' && ! maze[nowline+1][nowcolumn].visited )
			maze[nowline][nowcolumn].otheroads++ ;
		if (  nowline > 0 && maze[nowline-1][nowcolumn].step != 'O' && ! maze[nowline-1][nowcolumn].visited )
			maze[nowline][nowcolumn].otheroads++ ;
		if (  nowcolumn < column-1 && maze[nowline][nowcolumn+1].step != 'O' && ! maze[nowline][nowcolumn+1].visited )
			maze[nowline][nowcolumn].otheroads++ ;		
			
	} // if
	else if ( maze[nowline][nowcolumn].laststep == 'L' ) {
		
		if (  nowline < line-1 && maze[nowline+1][nowcolumn].step != 'O' && ! maze[nowline+1][nowcolumn].visited )
			maze[nowline][nowcolumn].otheroads++ ;
		if (  nowline > 0 && maze[nowline-1][nowcolumn].step != 'O' && ! maze[nowline-1][nowcolumn].visited )
			maze[nowline][nowcolumn].otheroads++ ;
		if (  nowcolumn > 0 && maze[nowline][nowcolumn-1].step != 'O' && ! maze[nowline][nowcolumn-1].visited )
			maze[nowline][nowcolumn].otheroads++ ;	
			
	} // if
	else if ( maze[nowline][nowcolumn].laststep == 'U' ) {
		
		if (  nowline > 0 && maze[nowline-1][nowcolumn].step != 'O' && ! maze[nowline-1][nowcolumn].visited )
			maze[nowline][nowcolumn].otheroads++ ;
		if (  nowcolumn > 0 && maze[nowline][nowcolumn-1].step != 'O' && ! maze[nowline][nowcolumn-1].visited )
			maze[nowline][nowcolumn].otheroads++ ;
		if (  nowcolumn < column-1 && maze[nowline][nowcolumn+1].step != 'O' && ! maze[nowline][nowcolumn+1].visited )
			maze[nowline][nowcolumn].otheroads++ ;
			
	} // if
	else if ( maze[nowline][nowcolumn].laststep == 'D' ) {
		
		if (  nowline < line-1 && maze[nowline+1][nowcolumn].step != 'O' && ! maze[nowline+1][nowcolumn].visited )
			maze[nowline][nowcolumn].otheroads++ ;
		if (  nowcolumn > 0 && maze[nowline][nowcolumn-1].step != 'O' && ! maze[nowline][nowcolumn-1].visited )
			maze[nowline][nowcolumn].otheroads++ ;
		if (  nowcolumn < column-1 && maze[nowline][nowcolumn+1].step != 'O' && ! maze[nowline][nowcolumn+1].visited )
			maze[nowline][nowcolumn].otheroads++ ;	
			
	} // if
	
} // AnyOtherRoads()

bool Walk( Maze **maze, int nowline, int nowcolumn, int column, int line ) {
    Maze *p[10] ;
	while ( nowline < line ) {
		p[nowline] = maze[nowline] ;
		nowline++ ;
	} // while
    nowline = 0 ;
	while ( maze[nowline][nowcolumn].step != 'G' ) {
       maze[nowline][nowcolumn].right = true ;
		AnyOtherRoads( p, nowline, nowcolumn, column, line ) ;
		maze[nowline][nowcolumn].visited = true ;
		
		if ( nowcolumn != column-1 && maze[nowline][nowcolumn+1].step != 'O' && maze[nowline][nowcolumn].laststep != 'L' && ! maze[nowline][nowcolumn+1].visited ) {
			maze[nowline][nowcolumn].otheroads-- ;
			nowcolumn++ ;
			maze[nowline][nowcolumn].laststep = 'R' ;
		} // if
		else if ( nowline != line-1 && maze[nowline+1][nowcolumn].step != 'O' && maze[nowline][nowcolumn].laststep != 'U' && ! maze[nowline+1][nowcolumn].visited ) {
			maze[nowline][nowcolumn].otheroads-- ;
			nowline++ ;
			maze[nowline][nowcolumn].laststep = 'D' ;
		} // if
		else if ( nowcolumn != 0 && maze[nowline][nowcolumn-1].step != 'O' && maze[nowline][nowcolumn].laststep != 'R' && ! maze[nowline][nowcolumn-1].visited ) {
			maze[nowline][nowcolumn].otheroads-- ;
			nowcolumn-- ;
			maze[nowline][nowcolumn].laststep = 'L' ;
		} // if
		else if ( nowline != 0 && maze[nowline-1][nowcolumn].step != 'O' && maze[nowline][nowcolumn].laststep != 'D' && ! maze[nowline-1][nowcolumn].visited ) {
			maze[nowline][nowcolumn].otheroads-- ;
			nowline-- ;
			maze[nowline][nowcolumn].laststep = 'U' ;
		} // if
		else if ( nowline == 0 && nowline == 0 && maze[nowline][nowcolumn].otheroads == 0 )
			return false ;
		else 
			PutWrong( p, nowline, nowcolumn, column, line ) ;
			
	} // while 
	return true ;
	
}

void PrintVisit( Maze **maze, int nowline, int nowcolumn, int column, int line ) {
	
	cout << '\n' ;
	while ( nowline < line ) {
		while ( nowcolumn < column ){
			if ( maze[nowline][nowcolumn].visited )
				cout << 'V' ;
			else
				cout << maze[nowline][nowcolumn].step ;
			
			nowcolumn++ ;
		}
		cout << '\n' ;
		nowcolumn = 0 ;
		nowline++ ;
	}
	
} // PrintVisit()

void PrintRight( Maze **maze, int nowline, int nowcolumn, int column, int line ) {
	
	cout << '\n' ;
	while ( nowline < line ) {
		while ( nowcolumn < column ){
			if ( maze[nowline][nowcolumn].right )
				cout << 'R' ;
			else
				cout << maze[nowline][nowcolumn].step ;
			
			nowcolumn++ ;
		}
		cout << '\n' ;
		nowcolumn = 0 ;
		nowline++ ;
	}
	
} // PrintRight()
int main() {
    Maze maze[10][10];
    Maze *p[10] ;
	int line = 0 ;
	int column = 0 ;
	int nowline = 0 ;
	int nowcolumn = 0 ;
	bool success = false ;
	cin >> column >> line ;

	while ( nowline < line ) {
		p[nowline] = maze[nowline] ;
		nowline++ ;
	} // while
	
	nowline = 0 ;
	Read( p, nowline, nowcolumn, column, line ) ;
	Initialize( p, nowline, nowcolumn, column, line ) ;
	success = Walk( p, nowline, nowcolumn, column, line ) ;
	PrintVisit( p, nowline, nowcolumn, column, line ) ;
	if ( success )
		PrintRight( p, nowline, nowcolumn, column, line ) ;
	
} // Main()
	





/*
	while ( nowline < line ) {
		while ( nowcolumn < column ) {
			cout << maze[nowline][nowcolumn].step ;
			nowcolumn++ ;
		} // while
		cout << '\n' ;
		nowline++ ;
		nowcolumn = 0 ;
	} // while
*/



