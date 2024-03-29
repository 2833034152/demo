#include <graphics.h>//加载easyx图形库
#include <iostream>
#include  <stdlib.h>
#include <string>
#include <conio.h>
#include <Windows.h>

#define LINE 9 
#define COLUMN 12
#define RATIO 61
#define  SCREEN_HEIGHT 768
#define  SCREEN_WIDTH 960
 
#define START_X 100
#define STARR_Y 150


#define KEY_UP     'w'
#define KEY_LEFT   'a'
#define KEY_RIGHT  'd'
#define KEY_DOWN   's'
#define KEY_QUIT   'q'


#define  isValid(pos)  pos.x >= 0 && pos.x < LINE && pos.y >= 0 && pos.y < COLUMN

enum _PROPS {
	WALL,
	FLOOR,
	BOX_DES,
	MAN,
	BOX,
	HIT,
	ALL

};

enum _DIRECT {
	UP,
	DOWN,
	LEFT,
	RIGHT
};


struct _POS{
	int x;
	int y;

};
struct _POS man;

IMAGE images[6];
IMAGE bg_image;
using namespace std;


//int count = 0 ;
/*游戏地图*/
int map[LINE][COLUMN] = {
{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
{ 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0 },
{ 0, 1, 4, 1, 0, 2, 1, 0, 2, 1, 0, 0 },
{ 0, 1, 0, 1, 0, 1, 0, 0, 1, 1, 1, 0 },
{ 0, 1, 0, 2, 0, 1, 1, 4, 1, 1, 1, 0 },
{ 0, 1, 1, 1, 0, 3, 1, 1, 1, 4, 1, 0 },
{ 0, 1, 2, 1, 1, 4, 1, 1, 1, 1, 1, 0 },
{ 0, 1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 0 },
{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
};

 int count = 0;	
void changeMap(struct _POS  *pos ,enum _PROPS pros){
	map[pos->x][pos->y] =  pros;
	//loadimage(&images[pros],_T("wall.bmp"),RATIO,RATIO,true);
	putimage(100+pos->y *RATIO,150+pos->x* RATIO,&images[pros]);
}


void gameControl(enum _DIRECT direct){
	int x = man.x;
	int y = man.y;

	struct _POS next_pos  = man;
	struct _POS next_next_pos = man;
	struct _POS last_pos = man;
	switch (direct){
	case UP:
		next_pos.x--;
		next_next_pos.x -=2;
		last_pos.x++;
		break;
	case DOWN:
		next_pos.x++;
		next_next_pos.x +=2;
		last_pos.x--;
		break;
	case LEFT:
		next_pos.y--;
		next_next_pos.y -=2;
		last_pos.y++;
		break;
	case RIGHT:
		next_pos.y++;
		next_next_pos.y +=2;
		last_pos.y--;

		break;
	
	}
	//if(direct == UP){
	if(isValid(next_pos) &&map[man.x][man.y] == MAN &&map[next_pos.x][next_pos.y] == FLOOR ){	           //人下一步是地板
		changeMap( &next_pos,MAN);
		changeMap(&man,FLOOR);
		man = next_pos;	
		count++;
	}   else if(isValid(next_next_pos) &&map[next_pos.x][next_pos.y] == BOX  ){ //下一步是箱子
			if( map[next_next_pos.x][next_next_pos.y] == FLOOR){                //可以正常推
				changeMap( &next_pos,MAN);
				changeMap(&man,FLOOR); 
				changeMap( &next_next_pos,BOX);
				man = next_pos;
				count++;
			}	else if(isValid(next_next_pos) &&map[next_next_pos.x][next_next_pos.y] == BOX_DES ){ //推到目的地
					changeMap(&man,FLOOR);
					changeMap( &next_pos,MAN);
					changeMap( &next_next_pos,BOX);
					man = next_pos;
					count++;

				}
		}//人可以走过目的地  

		else if(isValid(next_pos) &&map[next_pos.x][next_pos.y] == BOX_DES){
			//if(map[next_next_pos.x][next_next_pos.y]  == FLOOR){
				changeMap( &next_pos,MAN);
				map[next_pos.x][next_pos.y] = BOX_DES;
				changeMap(&man,FLOOR);
					
				man = next_pos;	
				count++;
			
			//}
			
	}	

		else if( isValid(next_pos) && map[man.x][man.y] == BOX_DES &&map[next_pos.x][next_pos.y]  == FLOOR ){
			
				changeMap( &next_pos,MAN);
				changeMap(&man,BOX_DES);
				man = next_pos;	
				count++;
			
			
			
			

		}





}

	bool isGameOver(){
		for(int i = 0; i< LINE; i++){
			for(int j = 0; j < COLUMN; j++){
				if(map[i][j] == BOX_DES)
					return false;
				}
		}
		return true;
	}


	void gameoverSceen(IMAGE  *bg_image ){

		putimage(0, 0, bg_image);
		
	
		settextcolor(WHITE);
		RECT rec = { 0, 0,SCREEN_WIDTH, SCREEN_HEIGHT};
		settextstyle(20, 0, _T("宋体"));    

	
		drawtext(_T("恭喜您~ \n 终于闯关成功!"),&rec, DT_CENTER| DT_VCENTER| DT_SINGLELINE );
	}


	void failSceen(IMAGE  *bg_image ){

		putimage(0, 0, bg_image);
		
	
		settextcolor(WHITE);
		RECT rec = { 0, 0,SCREEN_WIDTH, SCREEN_HEIGHT};
		settextstyle(20, 0, _T("宋体"));    

	
		drawtext(_T("步数太多，闯关失败!"),&rec, DT_CENTER| DT_VCENTER| DT_SINGLELINE );
	}





int main(){

	initgraph(960,768);
	loadimage(&bg_image,_T("blackground.bmp"),960,768,true);//是否拉伸图片
	putimage(0,0,&bg_image);

	loadimage(&images[WALL],_T("wall.bmp"),RATIO,RATIO,true);
	loadimage(&images[FLOOR],_T("floor.bmp"),RATIO,RATIO,true);
	loadimage(&images[BOX_DES],_T("des.bmp"),RATIO,RATIO,true);
	loadimage(&images[MAN],_T("man.bmp"),RATIO,RATIO,true);
	loadimage(&images[BOX],_T("box.bmp"),RATIO,RATIO,true);
	loadimage(&images[HIT],_T("box.bmp"),RATIO,RATIO,true);
	
	for(int i = 0; i< 9; i++){
		for(int j = 0; j< 12; j++){
			if(map[i][j] == MAN){
				man.x = i;
				man.y = j;
			}
			putimage(100+j*RATIO,150+i*RATIO,&images[map[i][j]]);
		}
	}
	//setbkcolor(RGB (256, 128, 128)); //设置背景色
	//cleardevice(); //用背景色清空整个屏幕(整个画布)

	//loadimage(&bg_image,_T("blackground.bmp"),61,61,true);
	
	//putimage(0, 0 ,&bg_image );
	

	bool quit  = false;
	do{
		if(_kbhit()){ //玩家按键
			char ch = _getch();
			if(ch == KEY_UP){
				gameControl(UP);
			}else if(ch == KEY_DOWN){
				gameControl(DOWN);
			}else if(ch == KEY_LEFT){
				gameControl(LEFT);
			}else if (ch == KEY_RIGHT){
				gameControl(RIGHT);
			}else  if(ch == KEY_QUIT){
				quit = true;
			}
			if(count == 40){
				failSceen( &bg_image);
				quit =true;
			
			}
			if( isGameOver()){
				gameoverSceen( &bg_image);
				quit = true;
			}
		}

		Sleep(100);
	
	}while (quit == false);

		system("pause");
		closegraph();
	

	return 0;
}