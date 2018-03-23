#define	BLANK	' '
#define	DFL_SYMBOL	'o'
#define	TOP_ROW	1
#define	BOT_ROW	50
#define	LEFT_EDGE	10
#define	RIGHT_EDGE	170
#define	X_INIT	10
#define	Y_INIT	1
#define	TICKS_PER_SEC	20
#define BUFFSIZE 4096

#define LE	(RIGHT_EDGE-LEFT_EDGE)/2

static	int l_cur;
//char	BLOCK[20]="____________________";
//char 	BLOCK_BLANK[20]="                    ";
struct ppball{
	int y_pos, x_pos,
		y_dir, x_dir,
		ledge;
	char symbol;
};
