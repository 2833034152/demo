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
	int id;            //关卡的id
	string name;       //关卡的名字
	int map_row;       //地图总行数
	int map_column;    //地图总列数
	string  map_data;  //二维地图数据
	int next_level;    //下一关卡的id 
}levelinfo;


bool fetch_level_info(levelinfo& level, int level_id);

bool transform_map_db2array(levelinfo& level, int map[LINE][COLUMN]);

bool update_user_level(userinfo& user, int next_level_id);
