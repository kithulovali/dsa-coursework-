#include <windows.h>
#include <commctrl.h>
#include <stdio.h>
#include "resource.h"
#include <stdlib.h>
#include "skiplist.h"

HINSTANCE hInst;
static SkipList g_sl;

static void SetStatus(HWND hwndDlg, const char* msg)
{
    SetDlgItemTextA(hwndDlg, IDC_STATUS, msg ? msg : "");
}

static void RefreshList(HWND hwndDlg)
{
    HWND hList = GetDlgItem(hwndDlg, IDC_LISTBOX);
    SendMessage(hList, LB_RESETCONTENT, 0, 0);
    if (!g_sl.header) return;
    SLNode* x = g_sl.header->forward[0];
    char buf[64];
    unsigned idx = 0;
    while (x) {
        sprintf(buf, "%u: %d", idx++, x->value);
        SendMessageA(hList, LB_ADDSTRING, 0, (LPARAM)buf);
        x = x->forward[0];
    }
}

static bool GetIntFromEdit(HWND hwndDlg, int editId, int* out)
{
    char txt[64] = {0};
    if (!GetDlgItemTextA(hwndDlg, editId, txt, (int)sizeof(txt))) return false;
    char* end = NULL;
    long v = strtol(txt, &end, 10);
    if (end == txt) return false;
    *out = (int)v;
    return true;
}

BOOL CALLBACK DlgMain(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch(uMsg)
    {
    case WM_INITDIALOG:
    {
        skiplist_init(&g_sl);
        RefreshList(hwndDlg);
        SetStatus(hwndDlg, "Initialized skiplist.");
    }
    return TRUE;

    case WM_CLOSE:
    {
        skiplist_free(&g_sl);
        EndDialog(hwndDlg, 0);
    }
    return TRUE;

    case WM_COMMAND:
    {
        switch(LOWORD(wParam))
        {
        case IDC_BTN_FIND:
        {
            int v;
            if (!GetIntFromEdit(hwndDlg, IDC_EDIT_VALUE, &v)) { SetStatus(hwndDlg, "Invalid value."); break; }
            SetStatus(hwndDlg, skiplist_findElement(&g_sl, v) ? "findElement: found" : "findElement: not found");
        } break;

        case IDC_BTN_INSERT:
        {
            int v;
            if (!GetIntFromEdit(hwndDlg, IDC_EDIT_VALUE, &v)) { SetStatus(hwndDlg, "Invalid value."); break; }
            if (skiplist_insertElement(&g_sl, v)) {
                RefreshList(hwndDlg);
                SetStatus(hwndDlg, "insertElement: ok");
            } else {
                SetStatus(hwndDlg, "insertElement: failed");
            }
        } break;

        case IDC_BTN_REMOVE:
        {
            int v;
            if (!GetIntFromEdit(hwndDlg, IDC_EDIT_VALUE, &v)) { SetStatus(hwndDlg, "Invalid value."); break; }
            if (skiplist_removeElement(&g_sl, v)) {
                RefreshList(hwndDlg);
                SetStatus(hwndDlg, "removeElement: removed one");
            } else {
                SetStatus(hwndDlg, "removeElement: value not found");
            }
        } break;

        case IDC_BTN_FINDALL:
        {
            int v; if (!GetIntFromEdit(hwndDlg, IDC_EDIT_VALUE, &v)) { SetStatus(hwndDlg, "Invalid value."); break; }
            size_t count = skiplist_findAllElements(&g_sl, v, NULL, 0);
            char msg[64]; sprintf(msg, "findAllElements: %u match(es)", (unsigned)count);
            SetStatus(hwndDlg, msg);
        } break;

        case IDC_BTN_REMOVEALL:
        {
            int v; if (!GetIntFromEdit(hwndDlg, IDC_EDIT_VALUE, &v)) { SetStatus(hwndDlg, "Invalid value."); break; }
            size_t removed = skiplist_removeAllElements(&g_sl, v);
            RefreshList(hwndDlg);
            char msg[64]; sprintf(msg, "removeAllElements: removed %u", (unsigned)removed);
            SetStatus(hwndDlg, msg);
        } break;
        }
    }
    return TRUE;
    }
    return FALSE;
}

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    hInst=hInstance;
    InitCommonControls();
    return DialogBox(hInst, MAKEINTRESOURCE(DLG_MAIN), NULL, (DLGPROC)DlgMain);
}