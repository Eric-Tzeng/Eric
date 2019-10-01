// 10727153 呂宜鴻 10727155 曾博暉 
#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

 
using namespace std;

struct Maze {
	char step ;  // 所在位置為E、O、G 
	bool visited ;  // 是否走過 
	char laststep ; // 前一步所走的方向 
	int otheroads ; // 有幾種可走的方向 
	bool right ; // 是否為到出口經過的 
	bool foundg ; // 是否有找到G 
	int stepnum ;
};

void InputFile(Maze **maze, int line, int column,	FILE *fPtr){  //處理讀檔 


	
	char temp ;
	int i = 0 ;
	int j = 0 ;
	fscanf(fPtr, " %c", &temp) ;	



	do {  
		if(temp!=' '){			
			if(temp!='\n') {
				maze[j][i].step = temp ;
				i++ ;
			}
			else{
				j++ ;
				i=0 ;
			}
		}

	} while(fscanf(fPtr, "%c", &temp) != EOF) ;
	
	fclose(fPtr);
	
	
	
}

void Initialize( Maze **maze, int nowline, int nowcolumn, int column, int line ) {  //初始化二維陣列 
	while ( nowline < line ) {
		while ( nowcolumn < column ) {
			if ( nowline == 0 && nowcolumn == 0 )
				maze[nowline][nowcolumn+1].laststep = 'R' ;
			maze[nowline][nowcolumn].visited = false ;
			maze[nowline][nowcolumn].otheroads = 0 ;
			maze[nowline][nowcolumn].right = false ;
			maze[nowline][nowcolumn].stepnum = 0 ;
			nowcolumn++ ;
		} // while
		nowline++ ;
		nowcolumn = 0 ;
	} // while
} // Initialize()

void Initialize2( Maze **maze, int nowline, int nowcolumn, int column, int line ) {  //初始化二維陣列 
	while ( nowline < line ) {
		while ( nowcolumn < column ) {
			maze[nowline][nowcolumn].right = false ;
			nowcolumn++ ;
		} // while
		nowline++ ;
		nowcolumn = 0 ;
	} // while
} // Initialize()

void PutWrong( Maze **maze, int &nowline, int &nowcolumn, int column, int line, int &count ) { //走到死路後的處理 (任務一) 
	while ( maze[nowline][nowcolumn].otheroads == 0 ) {                            // 退到前一個有岔路的位置 
		count -- ;
        maze[nowline][nowcolumn].right = false ;  //將這個位置設成非正確的 
		if ( maze[nowline][nowcolumn].laststep == 'R' )
			nowcolumn-- ;
		else if ( maze[nowline][nowcolumn].laststep == 'L' )
			nowcolumn++ ;
		else if ( maze[nowline][nowcolumn].laststep == 'U' )
			nowline++ ;		
		else if ( maze[nowline][nowcolumn].laststep == 'D' )
			nowline-- ;
	} // while
	count -- ;
    maze[nowline][nowcolumn].otheroads =0 ; 
} // PutWrong()

void SetBack( Maze **maze, int &nowline, int &nowcolumn, int column, int line, int &count ) { //走到死路後的處理 (任務一) 
	while ( maze[nowline][nowcolumn].otheroads == 0 ) {                            // 退到前一個有岔路的位置 
		count -- ;
		
		if ( maze[nowline][nowcolumn].laststep == 'R' )
			nowcolumn-- ;
		else if ( maze[nowline][nowcolumn].laststep == 'L' )
			nowcolumn++ ;
		else if ( maze[nowline][nowcolumn].laststep == 'U' )
			nowline++ ;		
		else if ( maze[nowline][nowcolumn].laststep == 'D' )
			nowline-- ;
			
	} // while
	count -- ;
    maze[nowline][nowcolumn].otheroads =0 ; 
} // SetBack()


bool AnyOtherRoads( Maze **maze, int nowline, int nowcolumn, int column, int line ) {  //有幾個可走的方向 
	if ( maze[nowline][nowcolumn].laststep == 'R' ) { //前一步為向右，檢查右、上、下是否為空格 
		
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

int Walk( Maze **maze, int nowline, int nowcolumn, int column, int line ) { //處理任務一走迷宮 
    Maze *p[50] ;
    int count = 0 ;
    int answer = 0 ;
    bool foundg = false ; 
	while ( nowline < line ) {
		p[nowline] = maze[nowline] ;
		nowline++ ;
	} // while
    nowline = 0 ;
	while ( nowline == 0 && nowcolumn == 0 && maze[nowline][nowcolumn].otheroads == 0 ) {
        maze[nowline][nowcolumn].right = true ;   
		AnyOtherRoads( p, nowline, nowcolumn, column, line ) ;
		maze[nowline][nowcolumn].visited = true ;
		maze[nowline][nowcolumn].stepnum = count ;
		if ( maze[nowline][nowcolumn].step == 'G' ) {
			if ( ! foundg ) 
				answer = count ;	
			else if ( foundg && count < answer ) 
				answer = count ;

			SetBack( p, nowline, nowcolumn, column, line, count ) ;	
			foundg = true ;
		} // if 
		else if ( (nowcolumn != column-1 && maze[nowline][nowcolumn+1].step != 'O' && maze[nowline][nowcolumn].laststep != 'L' && ! maze[nowline][nowcolumn+1].visited) || (foundg && maze[nowline][nowcolumn+1].right && nowline != 0 && nowcolumn+1 != 0 ) ) {
			maze[nowline][nowcolumn].otheroads-- ;
			nowcolumn++ ;
			maze[nowline][nowcolumn].laststep = 'R' ;
		} // if
		else if ( nowline != line-1 && maze[nowline+1][nowcolumn].step != 'O' && maze[nowline][nowcolumn].laststep != 'U' && ! maze[nowline+1][nowcolumn].visited || (foundg && maze[nowline+1][nowcolumn].right && nowline+1 != 0 && nowcolumn != 0 ) ) {
			maze[nowline][nowcolumn].otheroads-- ;
			nowline++ ;
			maze[nowline][nowcolumn].laststep = 'D' ;
		} // if
		else if ( nowcolumn != 0 && maze[nowline][nowcolumn-1].step != 'O' && maze[nowline][nowcolumn].laststep != 'R' && ! maze[nowline][nowcolumn-1].visited || (foundg && maze[nowline][nowcolumn-1].right && nowline != 0 && nowcolumn-1 != 0 ) ) {
			maze[nowline][nowcolumn].otheroads-- ;
			nowcolumn-- ;
			maze[nowline][nowcolumn].laststep = 'L' ;
		} // if
		else if ( nowline != 0 && maze[nowline-1][nowcolumn].step != 'O' && maze[nowline][nowcolumn].laststep != 'D' && ! maze[nowline-1][nowcolumn].visited || (foundg && maze[nowline-1][nowcolumn].right && nowline-1 != 0 && nowcolumn != 0 ) ) {
			maze[nowline][nowcolumn].otheroads-- ;
			nowline-- ;
			maze[nowline][nowcolumn].laststep = 'U' ;
		} // if
		else 
			PutWrong( p, nowline, nowcolumn, column, line, count ) ; // 無路可走後退回去 

		count ++ ;
	} // while 
	
	if ( foundg )
		return answer ;
	else
		return -1 ;
	
}

void PrintVisit( Maze **maze, int nowline, int nowcolumn, int column, int line ) {  // 印出所走過的路徑 
	
	cout << '\n' ;
	while ( nowline < line ) {
		while ( nowcolumn < column ){
			if ( maze[nowline][nowcolumn].visited )
				if(maze[nowline][nowcolumn].step=='G')
					cout<<'G' ;
				else 
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

void PrintRight( Maze **maze, int nowline, int nowcolumn, int column, int line ) {  // 印出正確的路徑 
	
	cout << '\n' ;
	while ( nowline < line ) {
		while ( nowcolumn < column ){
			if ( maze[nowline][nowcolumn].right ){
				if(maze[nowline][nowcolumn].step=='G')
					cout<<'G' ;
				else
					cout << 'R' ;
			}
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
    Maze maze[50][50];
    Maze *p[50] ;
	int line = 0 ;
	int column = 0 ;
	int nowline = 0 ;
	int nowcolumn = 0 ;
	int success = 0 ;
	string fileName ;
	string fileNumber ;
	
	int input ;
	cout<<"0 : Quit" << endl << "1 : one goal" << endl << "2 : more goal" << endl ;
	cin>> input ;
	while(input!=0&&input!=1&&input!=2) {
		cout<<endl<<"0 : " << endl; 
		cin>> input ;
	}
	
	while(input!=0){		
		cout << "FileNumber(201,202...) : " << endl ;   
		cin >> fileNumber ;                       // 輸入要讀的檔案名稱
		fileName = "input" + fileNumber + ".txt" ;
		FILE *fPtr = NULL;
		fPtr=fopen(fileName.c_str(),"r");
		if(fPtr==NULL)
			cout<<"ERROR FILE"<<endl ;
		else{		
			fscanf(fPtr, "%d", &column) ;
			fscanf(fPtr, "%d", &line) ;

				while ( nowline < line ) {
				p[nowline] = maze[nowline] ;
				nowline++ ;
			} // while
	
			nowline = 0 ;

	
			InputFile( p, column, line ,fPtr ) ;
			Initialize( p, nowline, nowcolumn, column, line ) ;
			if(input==1)
				success = Walk( p, nowline, nowcolumn, column, line ) ;

			Initialize2( p, nowline, nowcolumn, column, line ) ;
			PrintVisit( p, nowline, nowcolumn, column, line ) ;
			if ( success != -1 )
				
				PrintRight( p, nowline, nowcolumn, column, line ) ;
			
			cout<<"0 : Quit" << endl << "1 : one goal" << endl << "2 : more goal" << endl ;
			
			cin>> input ;
			while(input!=0&&input!=1&&input!=2) {
				cout<<"0 : Quit" << endl << "1 : one goal" << endl << "2 : more goal" << endl ;
				cin>> input ;
			}
		}
	}
	
} // Main


	









