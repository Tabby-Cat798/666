#pragma once
#include <string>

using namespace std;

typedef struct _userinfo{
	int id;          //�û�id
	string username; //�û���
	string password; //����
	int level_id;    //�ؿ�id
}userinfo;

bool fetch_user_info(userinfo &user);