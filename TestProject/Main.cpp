#include <windows.h>

int main() {
    // 콘솔 창 핸들 가져오기
    HWND hConsole = GetConsoleWindow();
    errno = 0;
    if (hConsole != NULL) {
        RECT rect;
        // 콘솔 창의 좌표 가져오기
        if (GetWindowRect(hConsole, &rect)) {
            // 마우스 커서를 콘솔 창 영역으로 제한
            ClipCursor(&rect);
        }
    }

    // 프로그램 작업 수행...
    Sleep(10000); // 예시: 10초 동안 제한 유지

    // 마우스 제한 해제
    ClipCursor(NULL);

    return 0;
}