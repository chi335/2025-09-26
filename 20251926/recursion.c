#include <stdio.h>

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
    getchar();  // getch() 대체 (표준 C)

    return 0;
}

// 상위 자릿수부터 출력 (재귀)
void serial_number(long number)
{
    if (number < 0) {
        printf("-\n");
        number = -number;
    }

    if (number >= 10) {
        serial_number(number / 10);
    }
    printf("%ld\n", number % 10);
}

// 하위 자릿수부터 출력 (재귀)
void reverse_number(long number)
{
    if (number < 0) {
        printf("-\n");
        number = -number;
    }

    printf("%ld\n", number % 10);

    if (number >= 10) {
        reverse_number(number / 10);
    }
}
