#include "database.h"
#include <mysql.h>
#include <stdio.h>

#define DB_NAME "ggbond"
#define DB_HOST "127.0.0.1"
#define DB_PORT 3306
#define DB_USER "root"
#define DB_USER_PASSWORD "123234abc"

static bool connect_db(MYSQL& mysql);


/*ͨ���û�������������ݿ��ȡuser��Ϣ
  ����ֵ�� �ɹ�true,ʧ��false*/

bool fetch_user_info(userinfo &user)
{
	MYSQL mysql;
	MYSQL_RES* res; //��ѯ�����
	MYSQL_ROW row;  //��¼�ṹ��
	char sql[256];
	bool ret = false;

	//1.���ӵ����ݿ�
	if (connect_db(mysql) == false)
	{
		return false;
	}

	//2.�����û����������ȡ�û���Ϣ(id, level_id)
	snprintf(sql, 256, "select id, level_id from users where username = '%s' and password = md5('%s');", user.username.c_str(), user.password.c_str());  //c_str()��stringת��Ϊchar����
	ret = mysql_query(&mysql, sql); //�ɹ�����0
	if (ret )
	{
		printf("���ݿ��ѯ���� %s ����ԭ��: %s\n", sql, mysql_error(&mysql));
		mysql_close(&mysql);   //�ȹر����ݿ⣬��ռ����Դ
		return false;
	}

	//3.��ȡ���
	res = mysql_store_result(&mysql);
	row = mysql_fetch_row(res);

	if (row == NULL) //û�в鵽��¼
	{
		mysql_free_result(res);
		mysql_close(&mysql);
		return false;
	}

	user.id = atoi(row[0]);    //atoi()���Խ��ַ���ת��Ϊ���α���
	user.level_id = atoi(row[1]);
	printf("user_id: %d \nlevel_id: %d\n", user.id, user.level_id);  //��ӡID
	Sleep(500);
	//4.���ؽ��

	//�ͷŽ����
	mysql_free_result(res);

	//�ر����ݿ�
	mysql_close(&mysql);

	return true;
}


bool connect_db(MYSQL& mysql)
{
	//1.��ʼ�����ݿ���
	mysql_init(&mysql);

	//2.�����ַ�����
	mysql_options(&mysql, MYSQL_SET_CHARSET_NAME, "gbk");  /*gbkΪ�����ַ����루�������壩*/

	//3.�������ݿ�
	if (mysql_real_connect(&mysql, DB_HOST, DB_USER, DB_USER_PASSWORD, DB_NAME, DB_PORT, NULL, 0) == NULL)
	{
		printf("���ݿ����ӳ��� ����ԭ��: %s\n", mysql_error(&mysql));
		return false;
	}
	printf("���ݿ����ӳɹ�\n", mysql_error(&mysql));
	Sleep(500);    //�Ӿ�Ч������ȡ��
	return true;
}