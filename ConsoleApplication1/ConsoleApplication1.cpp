#include <windows.h>
#include <iostream>
using namespace std;




int main()
{
	setlocale(LC_ALL, "ru");
	HKEY razd;
	int number_of_razd;
	cout << "Введите номер раздела" << endl;
	cout << "1-HKEY_CLASSES_ROOT" << endl;
	cout << "2-HKEY_CURRENT_USER" << endl;
	cout << "3-HKEY_LOCAL_MACHINE" << endl;
	cout << "4-HKEY_USERS" << endl;
	cout << "5-HKEY_CURRENT_CONFIG" << endl;

	cin >> number_of_razd;
	razd = ff(number_of_razd);
	
	string s;
	cout << "Введите путь" << endl;
	cin >> s;
	wstring ws(s.begin(), s.end());
	HKEY key;
	unsigned char lpValeName[MAX_PATH];
	unsigned char lpName[MAX_PATH];
	unsigned char Reget[512];

	DWORD RegetPath = sizeof(Reget);
	DWORD index = 0;
	DWORD kol = 0;
	DWORD val = 0;

	LPCWSTR str = ws.c_str();
	string sl = "\\";
	wstring sleh(sl.begin(), sl.end());
	DWORD type;

	DWORD lpcValueName = MAX_PATH;
	DWORD lpcName = MAX_PATH;
	RegOpenKeyEx(razd, str, NULL, KEY_READ | KEY_WOW64_64KEY, &key);
	RegQueryInfoKey(key, NULL, NULL, NULL, &kol, NULL, NULL, &val, NULL, NULL, NULL, NULL);

	for (int j = 0; j <= kol; j++)
	{

		RegQueryInfoKey(key, NULL, NULL, NULL, NULL, NULL, NULL, &val, NULL, NULL, NULL, NULL);
		for (index; index < val; index++)
		{
			if (RegEnumValue(key, index, (LPWSTR)lpValeName, &lpcValueName, NULL, &type, Reget, &RegetPath) == ERROR_SUCCESS)
				if (type == 1)
				{
					for (int i = 0; i < RegetPath; i++)
					{
						if (Reget[i] != '\0')
							cout << Reget[i];
					}


					cout << endl;
					memset(Reget, 'М', 512);
					memset(lpValeName, 'М', MAX_PATH);
					lpcValueName = MAX_PATH;
					RegetPath = sizeof(Reget);
				}
			memset(Reget, 'М', 512);
			memset(lpValeName, 'М', MAX_PATH);
			lpcValueName = MAX_PATH;
			RegetPath = sizeof(Reget);
		}
		RegOpenKeyEx(razd, str, NULL, KEY_READ | KEY_WOW64_64KEY, &key);
		memset(lpName, 'М', MAX_PATH);
		lpcName = MAX_PATH;
		RegetPath = sizeof(Reget);
		lpcValueName = MAX_PATH;
		RegEnumKeyEx(key, j, (LPWSTR)lpName, &lpcName, NULL, NULL, NULL, NULL);
		index = 0;

		wstring df = wstring(ws) + wstring(sleh) + (LPWSTR)lpName;
		LPCWSTR str1 = df.c_str();
		RegOpenKeyEx(razd, str1, NULL, KEY_READ | KEY_WOW64_64KEY, &key);
	}

	cout << kol << ' ' << val << endl;



}
