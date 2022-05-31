#include <graphics.h>//����easyxͼ�ο�
#include <iostream>
#include  <stdlib.h>
#include <string>
#include <conio.h>
#include <Windows.h>
#include "database.h"

using namespace std;

#define MAX_RETRY_TIMES  3

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


struct _POS {
	int x;
	int y;

};
struct _POS man;

IMAGE images[6];
IMAGE bg_image;
//using namespace std;


//int ::count = 0 ;
/*��Ϸ��ͼ*/
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

int  count = 0;
void changeMap(struct _POS* pos, enum _PROPS pros) {
	map[pos->x][pos->y] = pros;
	//loadimage(&images[pros],_T("wall.bmp"),RATIO,RATIO,true);
	putimage(100 + pos->y * RATIO, 150 + pos->x * RATIO, &images[pros]);
}


void gameControl(enum _DIRECT direct) {
	int x = man.x;
	int y = man.y;

	struct _POS next_pos = man;
	struct _POS next_next_pos = man;
	struct _POS last_pos = man;
	switch (direct) {
	case UP:
		next_pos.x--;
		next_next_pos.x -= 2;
		last_pos.x++;
		break;
	case DOWN:
		next_pos.x++;
		next_next_pos.x += 2;
		last_pos.x--;
		break;
	case LEFT:
		next_pos.y--;
		next_next_pos.y -= 2;
		last_pos.y++;
		break;
	case RIGHT:
		next_pos.y++;
		next_next_pos.y += 2;
		last_pos.y--;

		break;

	}
	//if(direct == UP){
	if (isValid(next_pos) && map[man.x][man.y] == MAN && map[next_pos.x][next_pos.y] == FLOOR) {	           //����һ���ǵذ�
		changeMap(&next_pos, MAN);
		changeMap(&man, FLOOR);
		man = next_pos;
		::count++;
	}
	else if (isValid(next_next_pos) && map[next_pos.x][next_pos.y] == BOX) { //��һ��������
		if (map[next_next_pos.x][next_next_pos.y] == FLOOR) {                //����������
			changeMap(&next_pos, MAN);
			changeMap(&man, FLOOR);
			changeMap(&next_next_pos, BOX);
			man = next_pos;
			::count++;
		}
		else if (isValid(next_next_pos) && map[next_next_pos.x][next_next_pos.y] == BOX_DES) { //�Ƶ�Ŀ�ĵ�
			changeMap(&man, FLOOR);
			changeMap(&next_pos, MAN);
			changeMap(&next_next_pos, BOX);
			man = next_pos;
			::count++;

		}
	}//�˿����߹�Ŀ�ĵ�  

	else if (isValid(next_pos) && map[next_pos.x][next_pos.y] == BOX_DES) {
		//if(map[next_next_pos.x][next_next_pos.y]  == FLOOR){
		changeMap(&next_pos, MAN);
		map[next_pos.x][next_pos.y] = BOX_DES;
		changeMap(&man, FLOOR);

		man = next_pos;
		::count++;

		//}

	}

	else if (isValid(next_pos) && map[man.x][man.y] == BOX_DES && map[next_pos.x][next_pos.y] == FLOOR) {

		changeMap(&next_pos, MAN);
		changeMap(&man, BOX_DES);
		man = next_pos;
		::count++;





	}





}

bool isGameOver() {
	for (int i = 0; i < LINE; i++) {
		for (int j = 0; j < COLUMN; j++) {
			if (map[i][j] == BOX_DES)
				return false;
		}
	}
	return true;
}


void gameoverSceen(IMAGE* bg_image) {

	putimage(0, 0, bg_image);
	settextcolor(WHITE);
	RECT rec = { 0, 0,SCREEN_WIDTH, SCREEN_HEIGHT };
	settextstyle(20, 0, _T("����"));

	drawtext(_T("��ϲ��~ \n ���ڴ��سɹ�!�ټ�"), &rec, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}

void gameNextSceen(IMAGE* bg_image) {

	putimage(0, 0, bg_image);
	settextcolor(WHITE);
	RECT rec = { 0, 0,SCREEN_WIDTH, SCREEN_HEIGHT };
	settextstyle(20, 0, _T("����"));

	drawtext(_T("��ϲ��~ \n ���������ת����һ��"), &rec, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	::system("pause");
	cleardevice();
}

void failSceen(IMAGE* bg_image) {

	putimage(0, 0, bg_image);


	settextcolor(WHITE);
	RECT rec = { 0, 0,SCREEN_WIDTH, SCREEN_HEIGHT };
	settextstyle(20, 0, _T("����"));


	drawtext(_T("����̫�࣬����ʧ��!"), &rec, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}

bool login(userinfo& user) {
	int times = 0;
	bool ret = false;


	do {
		cout << "�������û���: ";
		cin >> user.username;

		cout << "����������: ";
		cin >> user.password;

		//���� bool ,�ɹ�����true ,ʧ�ܷ���false .
		ret = fetch_user_info(user);
		times++;

		if (times >= MAX_RETRY_TIMES) {
			break;
		}
		if (ret == false) {
			cout << "��½ʧ�ܣ�����������!" << endl;
		}
	} while (!ret);

	return ret;
}

void init_game_graph()
{
	initgraph(960, 768);
	loadimage(&bg_image, _T("blackground.bmp"), 960, 768, true);//�Ƿ�����ͼƬ
	putimage(0, 0, &bg_image);

	loadimage(&images[WALL], _T("wall.bmp"), RATIO, RATIO, true);
	loadimage(&images[FLOOR], _T("floor.bmp"), RATIO, RATIO, true);
	loadimage(&images[BOX_DES], _T("des.bmp"), RATIO, RATIO, true);
	loadimage(&images[MAN], _T("man.bmp"), RATIO, RATIO, true);
	loadimage(&images[BOX], _T("box.bmp"), RATIO, RATIO, true);
	loadimage(&images[HIT], _T("box.bmp"), RATIO, RATIO, true);
}



int main() {
	//�û������֤
	userinfo user;
	levelinfo level;
	bool ret = false;
	
	if (login(user) == 0)
	{
		cout << "��¼ʧ�ܣ������µ�¼��" << endl;
		::system("pause");
		exit(-1);
	}
	else
	{
		cout << "��¼�ɹ����û�ID: " << user.id <<"�����ڹؿ��ǣ�"<<user.level_id<<"���뿪ʼ��ı��ݣ�" << endl;
		::system("pause");
	}
	//��ʼ����̨
	init_game_graph();
	
	bool quit = false;
	do {
		//��ȡ�ؿ���ͼ
		ret = fetch_level_info(level, user.level_id);

		if (!ret)
		{
			cout << "��ȡ�ؿ�����ʧ�ܣ������ԣ�" << endl;
			::system("pause");
			exit(-1);
		}

		//�����ݿ��еĵ�ͼ����ת����map ��
		ret = transform_map_db2array(level, map);
		::system("pause");

		for (int i = 0; i < level.map_row; i++) {
			for (int j = 0; j < level.map_column; j++) {
				if (map[i][j] == MAN) {
					man.x = i;
					man.y = j;
				}
				putimage(100 + j * RATIO, 150 + i * RATIO, &images[map[i][j]]);
			}
		}
		//setbkcolor(RGB (256, 128, 128)); //���ñ���ɫ
		//cleardevice(); //�ñ���ɫ���������Ļ(��������)

		//loadimage(&bg_image,_T("blackground.bmp"),61,61,true);

		//putimage(0, 0 ,&bg_image );


		
		do {
			if (_kbhit()) { //��Ұ���
				char ch = _getch();
				if (ch == KEY_UP) {
					gameControl(UP);
				}
				else if (ch == KEY_DOWN) {
					gameControl(DOWN);
				}
				else if (ch == KEY_LEFT) {
					gameControl(LEFT);
				}
				else if (ch == KEY_RIGHT) {
					gameControl(RIGHT);
				}
				else  if (ch == KEY_QUIT) {
					quit = true;
				}
				if (::count == 100) {
					failSceen(&bg_image);
					quit = true;

				}
				if (isGameOver()) {                           //��һ��
					gameNextSceen(&bg_image);
					if (level.next_level < 1)                     //��Ϸ����
					{
						gameoverSceen(&bg_image);
						quit = true;
						break;
					}
					if (update_user_level(user, level.next_level))
					{
						user.level_id = level.next_level;
					}
					break;
				}

				
			}

			Sleep(100);

		} while (quit == false);
	} while (quit == false);
	system("pause");
	closegraph();


	return 0;
}