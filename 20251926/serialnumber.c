#include <stdio.h>

void serial_number(long number)
{
    // 0 처리
    if (number == 0) {
        printf("0\n");
        return;
    }

    // 음수 처리
    if (number < 0) {
        printf("-\n");
        number = -number;
    }

    // 재귀적으로 각 자리수 출력
    if (number >= 10) {
        serial_number(number / 10);
    }

    printf("%ld\n", number % 10);
}

int main(void)
{
    long num;

    printf("숫자를 입력하세요: ");
    if (scanf("%ld", &num) != 1) {
        printf("올바른 숫자가 아닙니다.\n");
        return 1;
    }

    serial_number(num);

    return 0;
}
