
#include<curses.h>
#include<signal.h>
#include<sys/time.h>
#include<string.h>
#include<stdio.h>

#define	BLANK	'  '
#define	DFL_SYMBOL	'o'


main()
{
	
	initscr();\
	clear();

	for(int i=0;i<20; i++){
		mvaddch(10+i, 10+2*i, DFL_SYMBOL);
		refresh();
		usleep(500000);
		mvaddch(10+i, 10+2*i, BLANK);
		refresh();
	}
	getchar();
	endwin();
	

	
}