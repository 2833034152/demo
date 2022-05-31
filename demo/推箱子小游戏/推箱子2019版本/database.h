#pragma once
#include <string>

#define LINE   48
#define COLUMN 48
using namespace std;
typedef struct _userinfo {
	int id;
	string username;
	string password;
	int level_id;
}userinfo;

bool fetch_user_info(userinfo & user);

typedef struct _levelinfo {
	int id;            //�ؿ���id
	string name;       //�ؿ�������
	int map_row;       //��ͼ������
	int map_column;    //��ͼ������
	string  map_data;  //��ά��ͼ����
	int next_level;    //��һ�ؿ���id 
}levelinfo;


bool fetch_level_info(levelinfo& level, int level_id);

bool transform_map_db2array(levelinfo& level, int map[LINE][COLUMN]);

bool update_user_level(userinfo& user, int next_level_id);
