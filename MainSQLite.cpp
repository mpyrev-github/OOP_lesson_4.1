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
	sqlite3 *db = 0; // хэндл объекта соединение к БД
	// открываем соединение
	if( sqlite3_open("places.sqlite", &db) )
		cout<< stderr << "Ошибка открытия/создания БД: %s\n" << sqlite3_errmsg(db);
	else {
		cout << "БД открыта" << endl;
		const char* SQLdel = "DELETE FROM FOO; INSERT INTO FOO VALUES (541216,03,2019),(21,03,1997);";
		char *err = 0;
		if (sqlite3_exec(db, SQLdel, 0, 0, &err)){
			cout << stderr << "Ошибка SQL: %sn" << err;
			sqlite3_free(err);
		} else cout << "Выполнение запроса..." << endl;
		//-------------------------------------------------------------------------------------------
		char *errmsgFirstOutput;
		sqlite3_stmt *pStatementFirstOutput;
		const char* SQLselect = "SELECT * FROM FOO;";
		int resultFirstOutput = sqlite3_prepare_v2(db,SQLselect,-1,&pStatementFirstOutput,NULL); // UTF-8
		int col1FirstOutput,col2FirstOutput,col3FirstOutput;
		while(true){
			resultFirstOutput = sqlite3_step(pStatementFirstOutput);
			if(resultFirstOutput != SQLITE_ROW) break;
				col1FirstOutput = sqlite3_column_int(pStatementFirstOutput, 0 /*номер столбца*/);
				cout << col1FirstOutput << " ";
				col2FirstOutput = sqlite3_column_int(pStatementFirstOutput, 1 /*номер столбца*/);
				cout << col2FirstOutput << " ";
				col3FirstOutput = sqlite3_column_int(pStatementFirstOutput, 2 /*номер столбца*/);
				cout << col3FirstOutput << endl;
		}
		sqlite3_finalize(pStatementFirstOutput);
		//-------------------------------------------------------------------------------------------
		SQLdel = "DELETE FROM FOO WHERE a = 21;";
		char *errOfDelRow = 0;
		if (sqlite3_exec(db, SQLdel, 0, 0, &err)){
			cout << stderr << "Ошибка SQL: %sn" << errOfDelRow;
			sqlite3_free(err);
		} else cout << "Удаление второй строки..." << endl;
		//-------------------------------------------------------------------------------------------
		char *errmsgSecondOutput;
		sqlite3_stmt *pStatementSecondOutput;
		int resultSecondOutput = sqlite3_prepare_v2(db,SQLselect,-1,&pStatementSecondOutput,NULL); // UTF-8
		int col1SecondOutput,col2SecondOutput,col3SecondOutput;
		while(true){
			resultSecondOutput = sqlite3_step(pStatementSecondOutput);
			if(resultSecondOutput != SQLITE_ROW) break;
				col1SecondOutput = sqlite3_column_int(pStatementSecondOutput, 0 /*номер столбца*/);
				cout << col1SecondOutput << " ";
				col2SecondOutput = sqlite3_column_int(pStatementSecondOutput, 1 /*номер столбца*/);
				cout << col2SecondOutput << " ";
				col3SecondOutput = sqlite3_column_int(pStatementSecondOutput, 2 /*номер столбца*/);
				cout << col3SecondOutput << endl;
		}
		sqlite3_finalize(pStatementSecondOutput);
	}
	// закрываем соединение
	sqlite3_close(db);
	cout << "БД закрыта" << endl;
	cin.get();
	return 0;
}
