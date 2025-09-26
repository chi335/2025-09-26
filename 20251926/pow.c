#include <stdio.h>
#include <math.h>  // log10, pow 필요

void serial_number(long number)
{
    int length = 0;
    long num, divisor;

    if (number == 0) {
        printf("0\n");
        return;
    }

    // 자리수 계산
    length = (int)log10(number) + 1;

    for (int i = length; i >= 1; i--) {
        divisor = (long)pow(10, i - 1);  // 자릿수 나누기 기준
        num = number / divisor;          // 현재 자릿수 추출
        printf("%ld\n", num);
        number = number % divisor;       // 추출한 자릿수 제거
    }
}

int main(void)
{
    long number;

    printf("숫자를 입력하세요: ");
    if (scanf("%ld", &number) != 1) {
        printf("잘못된 입력입니다.\n");
        return 1;
    }

    serial_number(number);

    return 0;
}
