#include <stdio.h>
#include <math.h>   // log10, pow 사용

// 함수 선언
void serial_number(long number);
void reverse_number(long number);

int main(void)
{
    long number = 12345698;

    printf("입력 숫자 : %ld\n\n", number);

    printf("높은 단위부터 출력\n");
    serial_number(number);

    printf("\n낮은 단위부터 출력\n");
    reverse_number(number);

    printf("\nPress Enter to continue...");
    getchar();  // getch() 대신 cross-platform 대체
    return 0;
}

// 상위 자릿수부터 한 자리씩 출력
void serial_number(long number)
{
    long divisor = 1;

    // 가장 큰 자리수 나눗셈 기준 찾기
    while (number / divisor >= 10)
    {
        divisor *= 10;
    }

    // 한 자리씩 왼쪽부터 출력
    while (divisor > 0)
    {
        long digit = number / divisor;
        printf("%ld\n", digit);
        number %= divisor;
        divisor /= 10;
    }
}

// 하위 자릿수부터 한 자리씩 출력
void reverse_number(long number)
{
    if (number == 0)
    {
        printf("0\n");
        return;
    }

    while (number > 0)
    {
        printf("%ld\n", number % 10);
        number /= 10;
    }
}
