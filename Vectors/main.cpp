#include <windows.h>
#include <commctrl.h>
#include <stdio.h>
#include <stdlib.h>
#include "resource.h"
#include "vector.h"

static Vector g_vec;

static void SetStatus(HWND hwndDlg, const char* msg)
{
    SetDlgItemTextA(hwndDlg, IDC_STATUS, msg ? msg : "");
}

static void RefreshList(HWND hwndDlg)
{
    HWND hList = GetDlgItem(hwndDlg, IDC_LISTBOX);
    SendMessage(hList, LB_RESETCONTENT, 0, 0);
    char buf[64];
    for (size_t i = 0; i < vector_size(&g_vec); ++i) {
        int v = 0;
        vector_elemRank(&g_vec, i, &v);
        sprintf(buf, "%u: %d", (unsigned)i, v);
        SendMessageA(hList, LB_ADDSTRING, 0, (LPARAM)buf);
    }
}

static bool GetUintFromEdit(HWND hwndDlg, int editId, size_t* out)
{
    char txt[64] = {0};
    if (!GetDlgItemTextA(hwndDlg, editId, txt, (int)sizeof(txt))) return false;
    char* end = NULL;
    unsigned long val = strtoul(txt, &end, 10);
    if (end == txt) return false;
    *out = (size_t)val;
    return true;
}

static bool GetIntFromEdit(HWND hwndDlg, int editId, int* out)
{
    char txt[64] = {0};
    if (!GetDlgItemTextA(hwndDlg, editId, txt, (int)sizeof(txt))) return false;
    char* end = NULL;
    long val = strtol(txt, &end, 10);
    if (end == txt) return false;
    *out = (int)val;
    return true;
}

HINSTANCE hInst;

BOOL CALLBACK DlgMain(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch(uMsg)
    {
    case WM_INITDIALOG:
    {
        vector_init(&g_vec, 8);
        RefreshList(hwndDlg);
        SetStatus(hwndDlg, "Initialized vector.");
    }
    return TRUE;

    case WM_CLOSE:
    {
        vector_free(&g_vec);
        EndDialog(hwndDlg, 0);
    }
    return TRUE;

    case WM_COMMAND:
    {
        switch(LOWORD(wParam))
        {
        case IDC_BTN_ELEM:
        {
            size_t r;
            if (!GetUintFromEdit(hwndDlg, IDC_EDIT_RANK, &r)) { SetStatus(hwndDlg, "Invalid rank."); break; }
            int val;
            if (vector_elemRank(&g_vec, r, &val)) {
                char msg[64]; sprintf(msg, "elemRank(%u) = %d", (unsigned)r, val);
                SetStatus(hwndDlg, msg);
            } else {
                SetStatus(hwndDlg, "Rank out of range.");
            }
        } break;

        case IDC_BTN_REPLACE:
        {
            size_t r; int newv;
            if (!GetUintFromEdit(hwndDlg, IDC_EDIT_RANK, &r)) { SetStatus(hwndDlg, "Invalid rank."); break; }
            if (!GetIntFromEdit(hwndDlg, IDC_EDIT_VALUE, &newv)) { SetStatus(hwndDlg, "Invalid value."); break; }
            int oldv;
            if (vector_replaceRank(&g_vec, r, newv, &oldv)) {
                RefreshList(hwndDlg);
                char msg[64]; sprintf(msg, "replaceRank(%u,%d), old=%d", (unsigned)r, newv, oldv);
                SetStatus(hwndDlg, msg);
            } else {
                SetStatus(hwndDlg, "Rank out of range.");
            }
        } break;

        case IDC_BTN_INSERT:
        {
            size_t r; int v;
            if (!GetUintFromEdit(hwndDlg, IDC_EDIT_RANK, &r)) { SetStatus(hwndDlg, "Invalid rank."); break; }
            if (!GetIntFromEdit(hwndDlg, IDC_EDIT_VALUE, &v)) { SetStatus(hwndDlg, "Invalid value."); break; }
            if (vector_insertRank(&g_vec, r, v)) {
                RefreshList(hwndDlg);
                char msg[64]; sprintf(msg, "insertRank(%u,%d) ok", (unsigned)r, v);
                SetStatus(hwndDlg, msg);
            } else {
                SetStatus(hwndDlg, "Insert failed (rank out of range or OOM). ");
            }
        } break;

        case IDC_BTN_REMOVE:
        {
            size_t r; int removed;
            if (!GetUintFromEdit(hwndDlg, IDC_EDIT_RANK, &r)) { SetStatus(hwndDlg, "Invalid rank."); break; }
            if (vector_removeRank(&g_vec, r, &removed)) {
                RefreshList(hwndDlg);
                char msg[64]; sprintf(msg, "removeRank(%u) = %d", (unsigned)r, removed);
                SetStatus(hwndDlg, msg);
            } else {
                SetStatus(hwndDlg, "Rank out of range.");
            }
        } break;

        case IDC_BTN_SIZE:
        {
            char msg[64]; sprintf(msg, "size() = %u", (unsigned)vector_size(&g_vec));
            SetStatus(hwndDlg, msg);
        } break;

        case IDC_BTN_EMPTY:
        {
            SetStatus(hwndDlg, vector_is_empty(&g_vec) ? "isEmpty() = true" : "isEmpty() = false");
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