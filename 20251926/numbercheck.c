#include <stdio.h>

// 함수 선언
void number_check(int k, int i);
void digit_print(int dim[], int line);

// 숫자 배열 (4x5 LED 형태로 표현)
int zero[20] = {
    1,1,1,1,
    1,0,0,1,
    1,0,0,1,
    1,0,0,1,
    1,1,1,1
};
int one[20] = {
    0,0,1,0,
    0,0,1,0,
    0,0,1,0,
    0,0,1,0,
    0,0,1,0
};
int two[20] = {
    1,1,1,1,
    0,0,0,1,
    1,1,1,1,
    1,0,0,0,
    1,1,1,1
};
int three[20] = {
    1,1,1,1,
    0,0,0,1,
    1,1,1,1,
    0,0,0,1,
    1,1,1,1
};
int four[20] = {
    1,0,0,1,
    1,0,0,1,
    1,1,1,1,
    0,0,0,1,
    0,0,0,1
};
int five[20] = {
    1,1,1,1,
    1,0,0,0,
    1,1,1,1,
    0,0,0,1,
    1,1,1,1
};
int six[20] = {
    1,0,0,0,
    1,0,0,0,
    1,1,1,1,
    1,0,0,1,
    1,1,1,1
};
int seven[20] = {
    1,1,1,1,
    0,0,0,1,
    0,0,0,1,
    0,0,0,1,
    0,0,0,1
};
int eight[20] = {
    1,1,1,1,
    1,0,0,1,
    1,1,1,1,
    1,0,0,1,
    1,1,1,1
};
int nine[20] = {
    1,1,1,1,
    1,0,0,1,
    1,1,1,1,
    0,0,0,1,
    0,0,0,1
};

int main(void)
{
    int num, line;

    printf("디지털 숫자 출력 프로그램\n");
    printf("1 이상의 정수만 입력합니다.\n\n");
    printf("정수 숫자 입력 후 Enter> ");
    if (scanf("%d", &num) != 1 || num < 0) {
        printf("올바른 양의 정수를 입력하세요.\n");
        return 1;
    }

    printf("\n\n");

    for (line = 0; line < 5; line++) {
        number_check(num, line);
        printf("\n");
    }

    return 0;
}

// 각 숫자 라인 출력 (왼쪽 -> 오른쪽 재귀)
void number_check(int k, int line)
{
    if (k >= 10) {
        number_check(k / 10, line);
    }

    switch (k % 10) {
        case 0: digit_print(zero, line); break;
        case 1: digit_print(one, line); break;
        case 2: digit_print(two, line); break;
        case 3: digit_print(three, line); break;
        case 4: digit_print(four, line); break;
        case 5: digit_print(five, line); break;
        case 6: digit_print(six, line); break;
        case 7: digit_print(seven, line); break;
        case 8: digit_print(eight, line); break;
        case 9: digit_print(nine, line); break;
    }
}

// 각 숫자의 한 줄 출력 (■ 또는 공백)
void digit_print(int dim[], int line)
{
    for (int i = line * 4; i < line * 4 + 4; i++) {
        if (dim[i] == 1)
            printf("■");
        else
            printf("  ");
    }
    printf("  "); // 숫자 간 간격
}
