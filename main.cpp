/*
		Calculator made in C++ by L-amichevoleprogrammatorediquartiere
		7/6/2020 Italy
*/

#define IDM_RECTANGLE  1200

#include <windows.h>
#include <string.h>
#include <iostream>

HWND hwndedit;
HFONT hFont;

char stringtoprint[27];
int counter=0;
int draw_button(HWND);
char cmd_button(char);

using namespace std;

float eval(char string[])
{
	//atof=float    atoi=int
	int operator_=0;
	for(int i=0;i<counter;i++)
	{
		if ((string[i]=='+')||(string[i]=='-')||(string[i]=='*')||(string[i]=='/'))
		{
			operator_++;
		}
	}
	float factor[operator_];
	int position=0;
	int operator_position[operator_];
	char operator_type[operator_-1];
	for(int i=0;i<counter;i++)
	{
		if ((string[i]=='+')||(string[i]=='-')||(string[i]=='*')||(string[i]=='/'))
		{
			operator_position[position]=i;
			operator_type[position]=string[i];
			position++;
		}
	}
	bool start=true,comma=false;
	bool medium,finish=false;
	int place=0,posto=0;
	char num[10];
	for(int i=0;i<counter;i++)
	{
		if ((string[i]!='+')&&(string[i]!='-')&&(string[i]!='*')&&(string[i]!='/'))
		{
			num[posto]=string[i];
			if (string[i]=='.')
			{
				comma=true;
			}
			posto++;
		}
		if ((i==counter-1)||(string[i]=='+')||(string[i]=='-')||(string[i]=='*')||(string[i]=='/'))
		{
			if (comma)
			{
				factor[place]=atof(num);
			}
			else
			{
				factor[place]=atoi(num);
			}
			memset(num,0,10);
			place++;
			comma=false;
			posto=0;
		}
	}
	int choice=0;
	float result=0;
	for(int i=0;i<operator_;i++)
	{
		for(int o=0;o<operator_;o++)
		{
			if((operator_type[o]=='*')||(operator_type[o]=='/'))
			{
				choice=o;
				o=operator_;
			}
			else if((operator_type[o]=='+')||(operator_type[o]=='-'))
			{
				choice=o;
			}
		}
		switch(operator_type[choice])
		{
			case '*':
				result+=factor[choice]*factor[choice+1];
				break;
			case '/':
				result+=factor[choice]/factor[choice+1];
				break;
			case '+':
				result+=factor[choice]+factor[choice+1];
				break;
			case '-':
				result+=factor[choice]-factor[choice+1];
				break;
		}
		factor[choice]=result;
		for (int o=choice+1;o<operator_;o++)
		{
			factor[o]=factor[o+1];
		}
		for (int o=choice;o<operator_;o++)
		{
			operator_type[o]=operator_type[o+1];
		}
		result=0;
	}
	return factor[0];
}
/* This is where all the input to the window goes to */
LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	switch(Message) {
		case WM_PAINT: {
			PAINTSTRUCT ps;
			HDC hdc;
			BeginPaint(hwnd, &ps); 
			Rectangle(ps.hdc,10,20,250,105);
			hFont= CreateFont (90, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, "Techno");
			EndPaint(hwnd, &ps);
			break;
		}
		case WM_CREATE:{
			SetWindowTextA(hwnd,"Calcolatrice");
			draw_button(hwnd);
		}
		case WM_COMMAND:
			for(int i=1;i<=9;i++)
			{
				if (LOWORD(wParam) == i) 
				{
					cmd_button(char(48+i));
        		}
			}
			if (LOWORD(wParam) == 10) {
				cmd_button('0');
        	}
        	else if (LOWORD(wParam) == 11) {
				cmd_button('.');
        	}
			else if (LOWORD(wParam) == 12) {
				float a=eval(stringtoprint);
				counter=0;
			    string s = to_string(a);
			    memset(stringtoprint,0,strlen(stringtoprint));
			    strcpy(stringtoprint,s.c_str());
				SendMessage(hwndedit, WM_SETTEXT, 0, (LPARAM)stringtoprint);
        	}
			else if (LOWORD(wParam) == 13) {
				cmd_button('+');
        	}
			else if (LOWORD(wParam) == 14) {
				cmd_button('-');
        	}
			else if (LOWORD(wParam) == 20) {
				cmd_button('*');
        	}
			else if (LOWORD(wParam) == 18) {
				cmd_button('/');
        	}
        	//Delete 
			else if (LOWORD(wParam) == 16) {
				if (counter>0)
				{
					counter-=1;
				}
				stringtoprint[counter]=NULL;
				SendMessage(hwndedit, WM_SETTEXT, 0, (LPARAM)stringtoprint);
        	}
        	//Cancel
			else if (LOWORD(wParam) == 17) {
				counter=0;
				memset(stringtoprint,0,strlen(stringtoprint));
				SendMessage(hwndedit, WM_SETTEXT, 0, (LPARAM)stringtoprint);
        	}
			break;
		case WM_DESTROY: {
			PostQuitMessage(0);
			break;
		}
		
		default:
			return DefWindowProc(hwnd, Message, wParam, lParam);
	}
	return 0;
}
char cmd_button(char c)
{
	stringtoprint[counter]=c;
	counter+=1;
	SendMessage(hwndedit, WM_SETTEXT, 0, (LPARAM)stringtoprint);
	
}
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	
	WNDCLASSEX wc; 
	HWND hwnd;
	MSG msg;

	memset(&wc,0,sizeof(wc));
	wc.cbSize		 = sizeof(WNDCLASSEX);
	wc.lpfnWndProc	 = WndProc; 
	wc.hInstance	 = hInstance;
	
	wc.hCursor		 = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
	wc.lpszClassName = "WindowClass";

	if(!RegisterClassEx(&wc)) {
		MessageBox(NULL, "Window Registration Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	hwnd = CreateWindowEx(WS_EX_CLIENTEDGE,"WindowClass","Caption",WS_VISIBLE|WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, /* x */
		CW_USEDEFAULT, /* y */
		280, /* width */
		360, /* height */
		NULL,NULL,hInstance,NULL);

	if(hwnd == NULL) {
		MessageBox(NULL, "Window Creation Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	/*
		This is the heart of our program where all input is processed and 
		sent to WndProc. Note that GetMessage blocks code flow until it receives something, so
		this loop will not produce unreasonably high CPU usage
	*/
	while(GetMessage(&msg, NULL, 0, 0) > 0) { /* If no error is received... */
		TranslateMessage(&msg); /* Translate key codes to chars if present */
		DispatchMessage(&msg); /* Send it to WndProc */
	}
	return msg.wParam;
}
int draw_button(HWND hwnd)
{
	CreateWindow(TEXT("button"),TEXT("0"),WS_VISIBLE | WS_CHILD, 	  5, 265, 116, 25, hwnd, (HMENU) 10, NULL, NULL);
	CreateWindow(TEXT("button"),TEXT("."),WS_VISIBLE | WS_CHILD,	137, 265,  50, 25, hwnd, (HMENU) 11, NULL, NULL);
	CreateWindow(TEXT("button"),TEXT("="),WS_VISIBLE | WS_CHILD,	203, 265,  50, 25, hwnd, (HMENU) 12, NULL, NULL);
	CreateWindow(TEXT("button"),TEXT("1"),WS_VISIBLE | WS_CHILD,      5, 230,  50, 25, hwnd, (HMENU)  1, NULL, NULL);
	CreateWindow(TEXT("button"),TEXT("2"),WS_VISIBLE | WS_CHILD, 	 70, 230,  50, 25, hwnd, (HMENU)  2, NULL, NULL);
	CreateWindow(TEXT("button"),TEXT("3"),WS_VISIBLE | WS_CHILD,	137, 230,  50, 25, hwnd, (HMENU)  3, NULL, NULL);
	CreateWindow(TEXT("button"),TEXT("+"),WS_VISIBLE | WS_CHILD,    203, 230,  50, 25, hwnd, (HMENU) 13, NULL, NULL);
	CreateWindow(TEXT("button"),TEXT("4"),WS_VISIBLE | WS_CHILD,      5, 195,  50, 25, hwnd, (HMENU)  4, NULL, NULL);
	CreateWindow(TEXT("button"),TEXT("5"),WS_VISIBLE | WS_CHILD,     70, 195,  50, 25, hwnd, (HMENU)  5, NULL, NULL);
	CreateWindow(TEXT("button"),TEXT("6"),WS_VISIBLE | WS_CHILD,    137, 195,  50, 25, hwnd, (HMENU)  6, NULL, NULL);
	CreateWindow(TEXT("button"),TEXT("-"),WS_VISIBLE | WS_CHILD,    203, 195,  50, 25, hwnd, (HMENU) 14, NULL, NULL);
	CreateWindow(TEXT("button"),TEXT("7"),WS_VISIBLE | WS_CHILD,      5, 160,  50, 25, hwnd, (HMENU)  7, NULL, NULL);
	CreateWindow(TEXT("button"),TEXT("8"),WS_VISIBLE | WS_CHILD,     70, 160,  50, 25, hwnd, (HMENU)  8, NULL, NULL);
	CreateWindow(TEXT("button"),TEXT("9"),WS_VISIBLE | WS_CHILD,    137, 160,  50, 25, hwnd, (HMENU)  9, NULL, NULL);
	CreateWindow(TEXT("button"),TEXT("*"),WS_VISIBLE | WS_CHILD,    203, 160,  50, 25, hwnd, (HMENU) 20, NULL, NULL);
	CreateWindow(TEXT("button"),TEXT("Del"),WS_VISIBLE | WS_CHILD,   70, 125,  50, 25, hwnd, (HMENU) 16, NULL, NULL);
	CreateWindow(TEXT("button"),TEXT("Canc"),WS_VISIBLE | WS_CHILD, 137, 125,  50, 25, hwnd, (HMENU) 17, NULL, NULL);
	CreateWindow(TEXT("button"),TEXT("/"),WS_VISIBLE | WS_CHILD,    203, 125,  50, 25, hwnd, (HMENU) 18, NULL, NULL);
	
	hwndedit=CreateWindow(TEXT("Edit"), TEXT(""), WS_CHILD | WS_VISIBLE | SS_RIGHT |  ES_READONLY, 15, 70, 230, 30, hwnd, (HMENU) 15, NULL, NULL);
    SendMessage (hwndedit, WM_SETFONT, WPARAM (CreateFont (30, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, ANSI_CHARSET, 
	OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, "Arial")), TRUE); 
}
