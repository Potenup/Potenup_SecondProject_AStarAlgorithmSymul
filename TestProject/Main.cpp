#include <windows.h>

int main() {
    // �ܼ� â �ڵ� ��������
    HWND hConsole = GetConsoleWindow();
    errno = 0;
    if (hConsole != NULL) {
        RECT rect;
        // �ܼ� â�� ��ǥ ��������
        if (GetWindowRect(hConsole, &rect)) {
            // ���콺 Ŀ���� �ܼ� â �������� ����
            ClipCursor(&rect);
        }
    }

    // ���α׷� �۾� ����...
    Sleep(10000); // ����: 10�� ���� ���� ����

    // ���콺 ���� ����
    ClipCursor(NULL);

    return 0;
}