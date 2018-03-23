/*概述：	一个简单的弹球游戏，基于curses库实现的
 * 		主要利用信号和定时器来实现小球的运动和挡板的移动
 * 		屏蔽了Ctrl+C的信号，还可以创建用户和记录用户退出时的状态
 * 		（利用I/O操作进行）
 * 优化：1.可以考虑引入排名机制
 * 		2.实现网络功能，能够联机游戏
 * 		3.界面和游戏体验
 */
#include<curses.h>
#include<signal.h>
#include<sys/time.h>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<fcntl.h>

#include"bounce.h"

struct ppball the_ball;
char username;

void set_up();
void wrap_up();
int set_ticker(int);
int bounce_or_lose(struct ppball *bp);
void control();
void init();
void defaultset();
void writedata();

int main()
{
	init();
	set_up();
	control();
	wrap_up();
}

void defaultset()
{
	the_ball.y_pos=Y_INIT;
	the_ball.x_pos=X_INIT;
	the_ball.y_dir=1;
	the_ball.x_dir=1;
	the_ball.ledge=LE;
	the_ball.symbol=DFL_SYMBOL;
}

void init()
{
	FILE *fp=NULL;

	initscr();
	clear();
	echo();
	mvaddstr(1,1,"Please enter your username:");
	move(2,1);
	refresh();
	while(getstr(&username)){
		printf("gets username!\n");
	}
	if((fp=fopen( &username, "rb" ))==NULL){
		if(creat(&username, 0644)<0)
			printf("creat username error\n");
		defaultset();
	}else{
		fseek(fp,-sizeof(struct ppball),SEEK_END);
		if(fread( &the_ball, sizeof(struct ppball), 1, fp )==0){
			printf("read record error!\n");
			defaultset();
		}
		fclose(fp);
	}

}

void writedata()
{
    FILE *fp;

    if((fp=fopen(&username,"ab+"))==NULL)
    {
        printf("canot open the file.");
        exit(0);
    }

   fwrite(&the_ball,sizeof(struct ppball),1,fp);
   fclose(fp);
}


void control()
{
	int c;
	while((c=getchar())!='Q'){
			l_cur=the_ball.ledge;

			if(c=='a'){
				the_ball.ledge-=10;
				if(the_ball.ledge<LEFT_EDGE)
					the_ball.ledge=LEFT_EDGE;
			}
			if(c=='d') {
				the_ball.ledge+=10;
				if(the_ball.ledge>RIGHT_EDGE-20)
					the_ball.ledge=RIGHT_EDGE-20;
			}
		}
}

void set_up()
{
	void ball_move(int);

	clear();
	noecho();		//控制从键盘输入字元时不将字元显示在终端机上
	crmode();		//立即从键盘获得输入
	box(stdscr,'|','-');
	
	signal(SIGINT, SIG_IGN);		//忽略^C信号
	mvaddstr(BOT_ROW, the_ball.ledge , "____________________");
	mvaddch(the_ball.y_pos, the_ball.x_pos, the_ball.symbol);
	refresh();
	
	signal(SIGALRM, ball_move);
	set_ticker(1000/TICKS_PER_SEC);
	
}


void wrap_up()
{
	set_ticker(0);
	endwin();
	writedata();
}

void ball_move(int signum)
{
	int y_cur, x_cur;
	
	signal(SIGALRM, SIG_IGN);
	y_cur=the_ball.y_pos;
	x_cur=the_ball.x_pos;


	the_ball.y_pos+=the_ball.y_dir;
	the_ball.x_pos+=the_ball.x_dir;

	box(stdscr,'|','-');
	mvaddch(y_cur, x_cur, BLANK);
	mvaddstr(BOT_ROW, l_cur, "                    ");

	mvaddch(the_ball.y_pos, the_ball.x_pos, the_ball.symbol);
	mvaddstr(BOT_ROW, the_ball.ledge, "____________________");
	bounce_or_lose(&the_ball);
	move(LINES-1, COLS-1);
	refresh();
	
	signal(SIGALRM, ball_move);
}

int bounce_or_lose(struct ppball *bp)
{
	int return_val=0;
	
	if(bp->y_pos<=TOP_ROW){
		bp->y_dir=1;
		if(bp->x_dir>=0)
			bp->x_dir=rand()%3;
		else
			bp->x_dir=-rand()%3;
		return_val=1;
	}else if(bp->y_pos>=BOT_ROW){
		if(bp->x_pos>=bp->ledge && bp->x_pos<=bp->ledge+20){
				bp->y_dir=-1;
				if(bp->x_dir>=0)
					bp->x_dir=rand()%3;
				else
					bp->x_dir=-rand()%3;
				return_val=1;
		}else
		{
			set_ticker(0);///////////////////////////
		}

	}
	if(bp->x_pos<=LEFT_EDGE){
			bp->x_dir=rand()%3;
		return_val=1;
	}else if(bp->x_pos>=RIGHT_EDGE){
			bp->x_dir=-(rand()%3);
			return_val=1;
	}
	return return_val;
}

int set_ticker(int n_msecs)
{
	struct itimerval new_timeset;
	long n_sec, n_usecs;
	
	n_sec=n_msecs/1000;
	n_usecs=(n_msecs%1000)*1000L;
	
	new_timeset.it_interval.tv_sec=n_sec;
	new_timeset.it_interval.tv_usec=n_usecs;
	
	new_timeset.it_value.tv_sec=n_sec;
	new_timeset.it_value.tv_usec=n_usecs;
	
	return setitimer(ITIMER_REAL, &new_timeset, NULL);
}


