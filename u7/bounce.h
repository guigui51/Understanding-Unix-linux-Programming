#define	BLANK	'  '
#define	DFL_SYMBOL	'o'
#define	TOP_ROW	10
#define	BOT_ROW	30
#define	LEFT_EDGE	10
#define	RIGHT_EDGE	30
#define	X_INIT	10
#define	Y_INIT	10
#define	TICKS_PER_SEC	100

#define	X_TTM	8
#define	Y_TTM	8

struct ppball{
	int y_pos, x_pos,
		y_ttm, x_ttm,		//调整小球速度，有八个档
		y_ttg, x_ttg,
		y_dir, x_dir;
	char symbol;
};
