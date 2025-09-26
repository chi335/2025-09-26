#include <stdio.h>

void serial_number(long number)
{
    long divisor = 1;

    while (number / divisor >= 10) {
        divisor *= 10;
    }

    while (divisor > 0) {
        long digit = number / divisor;
        printf("%ld\n", digit);
        number %= divisor;
        divisor /= 10;
    }
}

int main(void)
{
    long num;
    printf("숫자를 입력하세요: ");
    scanf("%ld", &num);
    
    printf("자릿수별 출력:\n");
    serial_number(num);

    return 0;
}
