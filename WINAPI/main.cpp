#include<Windows.h>
#include<iostream>
#include"resource.h"

CONST CHAR g_sz_LOGIN_INVITATION[] = "Введите имя пользователя";

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR	lpCmdLine, INT nCmdShow)
{
	//MessageBox(NULL, "Hello Windows!", "Window title", MB_OK | MB_ICONINFORMATION);//MB_ICONQUESTION MB_ICONERROR
	//MessageBox(NULL, "Hello Windows!\nThis is MessageBox()","Window title", MB_ABORTRETRYIGNORE | //MB_ICONINFORMATION);//MB_ICONQUESTION MB_ICONERROR
	//MessageBox(NULL, "Hello Windows!\nThis is MessageBox()",
	//	"Window title",
	//	MB_CANCELTRYCONTINUE | MB_HELP | MB_DEFBUTTON2 |
	//	MB_ICONINFORMATION |
	////MB_SYSTEMMODAL//MB_ICONQUESTION MB_ICONERROR
	////MB_DEFAULT_DESKTOP_ONLY |
	//MB_RIGHT |
	//MB_SETFOREGROUND);

	DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), 0, (DLGPROC)DlgProc, 0);

	return 0;
}

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:// это сообщение отправляется один раз при инициализации окна
	{
		HWND hEdit = GetDlgItem(hwnd, IDC_EDIT_LOGIN);
		SendMessage(hEdit, WM_SETTEXT, 0, (LPARAM)g_sz_LOGIN_INVITATION);
	}
		break;
	case WM_COMMAND:// Обрабатывает нажатие кнопок и другие действия пользователя
		switch (LOWORD(wParam))
		{
		case IDC_EDIT_LOGIN:
		{
			CONST INT SIZE = 256;
			CHAR sz_buffer[SIZE]{};
			SendMessage((HWND)lParam, WM_GETTEXT, SIZE, (LPARAM)sz_buffer);
			if (HIWORD(wParam) == EN_SETFOCUS)
			{
				if (strcmp(sz_buffer, g_sz_LOGIN_INVITATION) == 0)
					SendMessage((HWND)lParam, WM_SETTEXT, 0, (LPARAM)"");
			}
			if (HIWORD(wParam) == EN_KILLFOCUS)
			{
				if(strcmp(sz_buffer, "")==0)
					SendMessage((HWND)lParam, WM_SETTEXT, 0, (LPARAM)g_sz_LOGIN_INVITATION);
			}
			break;
		}
		case IDC_BUTTON_COPY:
		{
			CONST INT SIZE = 256;
			CHAR sz_buffer[SIZE] = {};
			HWND hEditLogin = GetDlgItem(hwnd, IDC_EDIT_LOGIN);
			HWND hEditPassword = GetDlgItem(hwnd, IDC_EDIT_PASSWORD);
			SendMessage(hEditLogin, WM_GETTEXT,SIZE,(LPARAM)sz_buffer);

			SendMessage(hEditPassword, WM_SETTEXT,0,(LPARAM)sz_buffer);

		}
		break;
		case IDOK: MessageBox(hwnd, "Была нажата кнопка Ok", "Info", MB_OK | MB_ICONINFORMATION); break;
		case IDCANCEL: EndDialog(hwnd, 0); break;

		}
		break;
	case WM_CLOSE:// отправляется при нажатии кнопки закрыть (х)
		EndDialog(hwnd, 0);
		break;
	}
	return FALSE;


}