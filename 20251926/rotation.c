#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

// 함수 선언
void rotation_right(int m[][3]);
void move_shape(int m[][3]);
void print_shape(int m[][3]);
void move_control(int m[][3]);
void gotoxy(int x, int y);
void print_direction(void);

// 전역 좌표 변수
int x = 35, y = 12;
int inx = 0, iny = 0;

int main(void)
{
    int shape1[3][3] = {
        {0, 1, 0},
        {0, 1, 0},
        {1, 1, 1}
    };

    move_control(shape1);

    return 0;
}

// 3x3 행렬 오른쪽으로 회전
void rotation_right(int m[][3])
{
    int i, j;
    int temp[3][3];

    for (i = 0; i < 3; i++)
        for (j = 0; j < 3; j++)
            temp[j][2 - i] = m[i][j];

    for (i = 0; i < 3; i++)
        for (j = 0; j < 3; j++)
            m[i][j] = temp[i][j];
}

// 방향 설명 출력
void print_direction(void)
{
    gotoxy(25, 1);
    printf("화살표: 이동, 스페이스 키: 회전, ESC: 종료");
}

// 콘솔 커서 위치 지정
void gotoxy(int x, int y)
{
    COORD Pos = {x - 1, y - 1};  // 콘솔 좌표는 0 기반
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

// 블록 이동 컨트롤
void move_control(int m[][3])
{
    char key;

    do {
        system("cls");
        move_shape(m);

        while (!kbhit()) {
            Sleep(50);  // CPU 낭비 방지
        }

        key = getch();

        switch (key) {
            case 32:  // 스페이스바 → 회전
                rotation_right(m);
                break;
            case 72:  // ↑
                inx = 0; iny = -1;
                break;
            case 80:  // ↓
                inx = 0; iny = 1;
                break;
            case 75:  // ←
                inx = -1; iny = 0;
                break;
            case 77:  // →
                inx = 1; iny = 0;
                break;
            default:
                inx = 0; iny = 0;
                break;
        }

    } while (key != 27);  // ESC 종료
}

// 블록 출력
void print_shape(int m[][3])
{
    int i, j;

    for (i = 0; i < 3; i++) {
        gotoxy(x, y + i);
        for (j = 0; j < 3; j++) {
            if (m[i][j] == 1)
                printf("□");
            else
                printf("  ");
        }
    }
}

// 블록 위치 및 출력 처리
void move_shape(int m[][3])
{
    // 다음 위치 미리 계산
    int next_x = x + inx;
    int next_y = y + iny;

    // 경계 체크 (콘솔 창 크기에 따라 조정)
    if (next_x < 1) next_x = 1;
    if (next_x > 75) next_x = 75;
    if (next_y < 2) next_y = 2;
    if (next_y > 22) next_y = 22;

    // 위치 갱신
    x = next_x;
    y = next_y;

    // 화면 클리어 & 출력
    system("cls");
    print_shape(m);
    print_direction();

    // 이동 방향 초기화
    inx = 0;
    iny = 0;
}
