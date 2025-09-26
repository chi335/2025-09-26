#include <stdio.h>

void reverse_number(long number)
{
    while (number > 0)
    {
        printf("%ld\n", number % 10);
        number /= 10;
    }
}

int main(void)
{
    long number;

    printf("숫자를 입력하세요: ");
    if (scanf("%ld", &number) != 1 || number < 0) {
        printf("잘못된 입력입니다.\n");
        return 1;
    }

    reverse_number(number);

    return 0;
}
