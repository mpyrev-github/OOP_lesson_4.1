#pragma hdrstop
#pragma argsused

#ifdef _WIN32
#include <tchar.h>
#else
  typedef char _TCHAR;
  #define _tmain main
#endif

#include <stdio.h>
#include <iostream>
#include "sqlite3.h"
#include "windows.h"

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	sqlite3 *db = 0; // ����� ������� ���������� � ��
	// ��������� ����������
	if( sqlite3_open("places.sqlite", &db) )
		cout<< stderr << "������ ��������/�������� ��: %s\n" << sqlite3_errmsg(db);
	else {
		cout << "�� �������" << endl;
		const char* SQLdel = "DELETE FROM FOO; INSERT INTO FOO VALUES (541216,03,2019),(21,03,1997);";
		char *err = 0;
		if (sqlite3_exec(db, SQLdel, 0, 0, &err)){
			cout << stderr << "������ SQL: %sn" << err;
			sqlite3_free(err);
		} else cout << "���������� �������..." << endl;
		//-------------------------------------------------------------------------------------------
		char *errmsgFirstOutput;
		sqlite3_stmt *pStatementFirstOutput;
		const char* SQLselect = "SELECT * FROM FOO;";
		int resultFirstOutput = sqlite3_prepare_v2(db,SQLselect,-1,&pStatementFirstOutput,NULL); // UTF-8
		int col1FirstOutput,col2FirstOutput,col3FirstOutput;
		while(true){
			resultFirstOutput = sqlite3_step(pStatementFirstOutput);
			if(resultFirstOutput != SQLITE_ROW) break;
				col1FirstOutput = sqlite3_column_int(pStatementFirstOutput, 0 /*����� �������*/);
				cout << col1FirstOutput << " ";
				col2FirstOutput = sqlite3_column_int(pStatementFirstOutput, 1 /*����� �������*/);
				cout << col2FirstOutput << " ";
				col3FirstOutput = sqlite3_column_int(pStatementFirstOutput, 2 /*����� �������*/);
				cout << col3FirstOutput << endl;
		}
		sqlite3_finalize(pStatementFirstOutput);
		//-------------------------------------------------------------------------------------------
		SQLdel = "DELETE FROM FOO WHERE a = 21;";
		char *errOfDelRow = 0;
		if (sqlite3_exec(db, SQLdel, 0, 0, &err)){
			cout << stderr << "������ SQL: %sn" << errOfDelRow;
			sqlite3_free(err);
		} else cout << "�������� ������ ������..." << endl;
		//-------------------------------------------------------------------------------------------
		char *errmsgSecondOutput;
		sqlite3_stmt *pStatementSecondOutput;
		int resultSecondOutput = sqlite3_prepare_v2(db,SQLselect,-1,&pStatementSecondOutput,NULL); // UTF-8
		int col1SecondOutput,col2SecondOutput,col3SecondOutput;
		while(true){
			resultSecondOutput = sqlite3_step(pStatementSecondOutput);
			if(resultSecondOutput != SQLITE_ROW) break;
				col1SecondOutput = sqlite3_column_int(pStatementSecondOutput, 0 /*����� �������*/);
				cout << col1SecondOutput << " ";
				col2SecondOutput = sqlite3_column_int(pStatementSecondOutput, 1 /*����� �������*/);
				cout << col2SecondOutput << " ";
				col3SecondOutput = sqlite3_column_int(pStatementSecondOutput, 2 /*����� �������*/);
				cout << col3SecondOutput << endl;
		}
		sqlite3_finalize(pStatementSecondOutput);
	}
	// ��������� ����������
	sqlite3_close(db);
	cout << "�� �������" << endl;
	cin.get();
	return 0;
}
