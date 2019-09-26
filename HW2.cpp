
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
	bool otheroads ;
	bool right ;
};


int main() {
    Maze maze[10][10];
    Maze *p[10] ;
	int line = 0 ;
	int column = 0 ;
	int nowline = 0 ;
	int nowcolumn = 0 ;
	cin >> column >> line ;
	while ( nowline < line ) {
		while ( nowcolumn < column ) {
			cin >> maze[nowline][nowcolumn].step ;
			nowcolumn++ ;
		} // while
		nowline++ ;
		nowcolumn = 0 ;
	} // while
	
	nowline = 0 ;
	while ( nowline < line ) {
		p[nowline] = maze[nowline] ;
		nowline++ ;
	} // while
	
	nowline = 0 ;
	while ( nowline < line ) {
		while ( nowcolumn < column ) {
			maze[nowline][nowcolumn].visited = false ;
			maze[nowline][nowcolumn].otheroads = false ;
			maze[nowline][nowcolumn].right = false ;
			nowcolumn++ ;
		} // while
		nowline++ ;
		nowcolumn = 0 ;
	} // while
	
	nowline = 0 ;
	while ( maze[nowline][nowcolumn].step != 'G' ) {
		maze[nowline][nowcolumn].visited = true ;
		
		if ( nowcolumn != column-1 && maze[nowline][nowcolumn+1].step != 'O' && maze[nowline][nowcolumn].laststep != 'L' ) {
			nowcolumn++ ;
			maze[nowline][nowcolumn].laststep = 'R' ;
		} // if
		else if ( nowline != line-1 && maze[nowline+1][nowcolumn].step != 'O' && maze[nowline][nowcolumn].laststep != 'U' ) {
			nowline++ ;
			maze[nowline][nowcolumn].laststep = 'D' ;
		} // if
		else if ( nowcolumn != 0 && maze[nowline][nowcolumn-1].step != 'O' && maze[nowline][nowcolumn].laststep != 'R' ) {
			nowcolumn-- ;
			maze[nowline][nowcolumn].laststep = 'L' ;
		} // if
		else if ( nowline != 0 && maze[nowline-1][nowcolumn].step != 'O' && maze[nowline][nowcolumn].laststep != 'D' ) {
			nowline-- ;
			maze[nowline][nowcolumn].laststep = 'U' ;
		} // if
		else {
			
		}
	}
}
	





/*	countl = 0 ;
	while ( countl < line ) {
		while ( countc < column ) {
			cout << maze[countl][countc].step ;
			countc++ ;
		} // while
		cout << '\n' ;
		countl++ ;
		countc = 0 ;
	} // while
*/

