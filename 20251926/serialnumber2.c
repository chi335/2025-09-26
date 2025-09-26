#include <stdio.h>

// 각 자리수를 재귀적으로 출력하는 함수
void serial_number(long number)
{
    if (number < 0) {
        printf("-\n");
        number = -number;
    }

    // 0 처리
    if (number == 0) {
        printf("0\n");
        return;
    }

    // 재귀적으로 앞자리부터 출력
    if (number >= 1) {
        serial_number(number / 10);
        printf("%ld\n", number % 10);
    }
}

int main(void)
{
    long input;

    printf("숫자를 입력하세요: ");
    if (scanf("%ld", &input) != 1) {
        printf("입력이 올바르지 않습니다.\n");
        return 1;
    }

    serial_number(input);

    return 0;
}
