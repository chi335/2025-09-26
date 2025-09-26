#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

// 함수 선언
void draw_horizontal_slide(int x, int y, int length, char *s);
void draw_vertical_slide(int x, int y, int length, char *s);
void draw_rectangle(int c, int r);
void move_arrow_key(char key, int *x1, int *y1, int x_b, int y_b);
void gotoxy(int x, int y);

int main(void)
{
    char *slide = "■", key;
    int x = 1, y = 1;
    int h_slide_length, v_slide_length;

    printf("슬라이드바 표시\n\n");
    printf("수평 슬라이드바의 길이(최대 70)를 입력하고 Enter> ");
    scanf("%d", &h_slide_length);
    if (h_slide_length < 1 || h_slide_length > 70) {
        printf("잘못된 길이입니다. 1~70 사이 입력.\n");
        return 1;
    }

    printf("수직 슬라이드바의 길이(최대 19)를 입력하고 Enter> ");
    scanf("%d", &v_slide_length);
    if (v_slide_length < 1 || v_slide_length > 19) {
        printf("잘못된 길이입니다. 1~19 사이 입력.\n");
        return 1;
    }

    system("cls");

    do {
        draw_vertical_slide(1, y, v_slide_length, slide);
        draw_horizontal_slide(x, v_slide_length + 3, h_slide_length, slide);
        key = getch();
        move_arrow_key(key, &x, &y, h_slide_length, v_slide_length);
    } while (key != 27);  // ESC 키를 누를 때까지

    return 0;
}

// 사각형 테두리 그리기
void draw_rectangle(int c, int r)
{
    int i, j;
    unsigned char a = 0xa6;
    unsigned char b[7];

    for (i = 1; i < 7; i++)
        b[i] = 0xa0 + i;

    // 상단 테두리
    printf("%c%c", a, b[3]);
    for (i = 0; i < c; i++)
        printf("%c%c", a, b[1]);
    printf("%c%c\n", a, b[4]);

    // 중간 부분
    for (i = 0; i < r; i++) {
        printf("%c%c", a, b[2]);
        for (j = 0; j < c; j++)
            printf("  "); // 공간 확보
        printf("%c%c\n", a, b[2]);
    }

    // 하단 테두리
    printf("%c%c", a, b[6]);
    for (i = 0; i < c; i++)
        printf("%c%c", a, b[1]);
    printf("%c%c\n", a, b[5]);
}

// 수평 슬라이드바 그리기
void draw_horizontal_slide(int x, int y, int length, char *s)
{
    int real_length = length;
    gotoxy(1, y);
    draw_rectangle(real_length, 1);  // 가로 길이 그대로, 높이 1줄

    gotoxy(x + 2, y + 1);  // 핸들 위치
    printf("%s", s);

    // 위치 표시
    gotoxy(real_length * 2 + 5, y + 1);
    printf("X: %2d  ", x);
}

// 수직 슬라이드바 그리기
void draw_vertical_slide(int x, int y, int length, char *s)
{
    gotoxy(x, 1);
    draw_rectangle(1, length);  // 세로 길이 length, 너비 1

    gotoxy(x + 2, y + 1);  // 핸들 위치
    printf("%s", s);

    // 위치 표시
    gotoxy(x + 6, length + 2);
    printf("Y: %2d  ", y);
}

// 방향키 처리
void move_arrow_key(char key, int *x1, int *y1, int x_b, int y_b)
{
    switch (key) {
        case 72: // 위쪽
            (*y1)--;
            if (*y1 < 1) *y1 = 1;
            break;
        case 80: // 아래쪽
            (*y1)++;
            if (*y1 > y_b) *y1 = y_b;
            break;
        case 75: // 왼쪽
            (*x1)--;
            if (*x1 < 1) *x1 = 1;
            break;
        case 77: // 오른쪽
            (*x1)++;
            if (*x1 > x_b) *x1 = x_b;
            break;
        default:
            return;
    }
}

// 콘솔 커서 이동
void gotoxy(int x, int y)
{
    COORD Pos = {x - 1, y - 1};  // 0-based index
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}
