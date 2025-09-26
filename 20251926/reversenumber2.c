#include <stdio.h>

void reverse_number(long number)
{
    if (number < 0) {
        printf("-");
        number = -number;
    }

    if (number == 0) {
        printf("0\n");
        return;
    }

    while (number > 0)
    {
        printf("%ld\n", number % 10);
        number /= 10;
    }
}

int main(void)
{
    long num;
    printf("숫자를 입력하세요: ");
    if (scanf("%ld", &num) != 1) {
        printf("잘못된 입력입니다.\n");
        return 1;
    }

    reverse_number(num);

    return 0;
}
