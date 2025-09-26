## 💡 숫자의 변환 및 표현 함수 모음

이 저장소는 숫자의 다양한 변환 및 표현 방법을 **C 언어 함수**로 구현한 예제들을 포함하고 있습니다. 숫자의 자릿수를 분리하고 출력하는 방법부터, 디지털 형태로 숫자를 시각화하는 방법, 그리고 도형을 이동 및 회전시키는 그래픽 프로그래밍 예제까지 다룹니다.

---

## 1. 숫자의 자릿수 분리 및 출력

### 📌 개요

숫자를 **문자열** 또는 **정수형**으로 입력받아 자릿수별로 분리하고 순서대로 출력하는 방법을 보여줍니다. 정수형 처리 방법은 `log10`과 `pow`를 활용하여 **높은 자릿수부터 출력**하는 예제를 포함합니다.

### 📜 주요 함수

| 함수명 | 설명 | 비고 |
| :--- | :--- | :--- |
| `print_digits_as_string()` | 숫자를 문자열로 입력받아 각 문자를 순서대로 출력 | `scanf`와 문자열 길이 계산 활용 |
| `print_digits_as_int()` | 정수형 숫자를 나눗셈 연산으로 자릿수 분리 | `log10`과 `pow` 함수 활용 |

### 💻 예제 코드 (높은 자릿수부터 출력)

```
#include <stdio.h>
#include <math.h> // log10, pow 함수를 사용하기 위해 필요

// 높은 자릿수부터 출력하는 함수
void print_digits_as_int(int number) {
    if (number == 0) {
        printf("0\n");
        return;
    }

    // log10을 이용해 자릿수 계산
    int num_digits = (int)log10(number) + 1;

    for (int i = num_digits - 1; i >= 0; i--) {
        int divisor = (int)pow(10, i); // 10의 i승 (가장 높은 자리)
        int digit = number / divisor;
        printf("%d ", digit);
        number %= divisor; // 출력한 자릿수 제거
    }
    printf("\n");
}

int main() {
    int num = 756896;
    printf("입력 숫자: %d\n", num);
    printf("높은 자릿수부터 출력: ");
    print_digits_as_int(num);
    return 0;
}
```


## 2. 재귀적 호출을 이용한 자릿수 출력

### 📌 개요

**재귀 함수**를 활용하여 숫자의 자릿수를 순서대로 또는 역순으로 출력하는 효율적인 방법을 소개합니다. 재귀 호출의 **스택 구조**를 이용해 출력 순서를 제어합니다.

---

### 📜 주요 함수

| 함수명 | 설명 | 특징 |
| :--- | :--- | :--- |
| `print_digits_recursive(int n)` | 높은 자릿수부터 순서대로 출력 | 재귀 호출 후 `printf` 실행 (**LIFO** 원리) |
| `print_digits_reverse_recursive(int n)` | 낮은 자릿수부터 역순으로 출력 | 재귀 호출 전 `printf` 실행 |

---

### 💻 예제 코드 (높은 자릿수부터 재귀 출력)

```
#include <stdio.h>

// 높은 자릿수부터 순서대로 출력 (재귀)
void print_digits_recursive(int n) {
    if (n == 0) {
        return; // 재귀 탈출 조건
    }
    // 재귀 호출: 이 시점에서 printf는 보류됨 (스택에 쌓임)
    print_digits_recursive(n / 10);

    // 보류되었던 printf가 스택이 해제되면서 역순으로 실행됨
    printf("%d ", n % 10);
}

int main() {
    int num = 123;
    printf("입력 숫자: %d\n", num);
    printf("높은 자릿수부터 재귀적으로 출력: ");
    print_digits_recursive(num);
    printf("\n");
    return 0;
}
```

---
## 3. 디지털 숫자 출력

### 📌 개요

정수형 숫자를 마치 전광판처럼 **디지털 숫자 형태**로 시각화하여 출력합니다. 각 숫자의 패턴은 2차원 배열에 미리 정의되어 있으며, **재귀 함수**를 통해 각 자릿수의 패턴을 라인(line) 단위로 출력합니다.

---

### 📜 주요 함수

| 함수명 | 설명 | 비고 |
| :--- | :--- | :--- |
| `print_digital_number(int number)` | 숫자를 입력받아 자릿수별로 패턴 출력 | `number_check` 함수를 재귀 호출 |
| `print_digital_digit_line(int digit, int line)` | 특정 숫자의 한 줄(line)을 출력 | 패턴 배열(`digital_patterns`) 참조 |

---

### 💻 예제 코드 (디지털 숫자 출력)

```
#include <stdio.h>

// 0~9까지의 디지털 숫자 패턴 (1은 ■, 0은 공백)을 단순화한 예시
// 실제 구현에서는 5줄 * 3칸의 15개 요소를 가질 수 있습니다.
int digital_patterns[10][15] = {
    // 0의 패턴 (5줄, 3칸씩)
    {1, 1, 1,  1, 0, 1,  1, 0, 1,  1, 0, 1,  1, 1, 1},
    // ... 나머지 1~9 패턴은 생략 ...
};

// 특정 자릿수와 라인에 해당하는 패턴을 출력
void print_digital_digit_line(int digit, int line) {
    int start_index = line * 3;
    for (int i = 0; i < 3; i++) {
        if (digital_patterns[digit][start_index + i] == 1) {
            printf("■");
        } else {
            printf("  "); // 공백 두 칸
        }
    }
}

// 재귀를 이용해 각 자릿수를 순서대로 출력 (라인별로 호출)
void print_digital_number(int n, int line) {
    if (n == 0) {
        return;
    }
    // 높은 자릿수부터 처리하기 위해 재귀 먼저 호출
    print_digital_number(n / 10, line);

    // 현재 자릿수의 해당 라인 출력
    print_digital_digit_line(n % 10, line);
}

int main() {
    int num = 123;
    printf("입력 숫자: %d\n", num);

    // 총 5라인을 순회하며 출력
    for (int i = 0; i < 5; i++) {
        print_digital_number(num, i);
        printf("\n");
    }
    return 0;
}
```


---
## 4. 슬라이드 바 구현

### 📌 개요

키보드 화살표 키 입력을 통해 수평 및 수직 슬라이드 바를 제어하는 예제입니다. 슬라이드 바의 막대와 움직이는 슬라이드(**■**)를 그립니다.

---

### 📜 주요 함수

| 함수명 | 설명 | 매개변수 |
| :--- | :--- | :--- |
| `draw_rectangle()` | 슬라이드 바의 긴 막대 부분을 그리는 함수 | 좌표, 너비, 높이 |
| `update_slidebar_position()` | 화살표 키 입력을 처리하고 슬라이드 위치 업데이트 | 입력된 키 |
| `draw_slidebar()` | 슬라이드 바의 전체적인 모양을 그리는 함수 | `draw_rectangle()`과 `printf()` 조합 |

---


## 5. 도형의 이동 및 회전

### 📌 개요

화면에 표시된 도형을 키보드로 연속적으로 **이동**시키고, 시계 방향 또는 반시계 방향으로 **회전**시키는 프로그램입니다. 회전은 **행렬의 인덱스 변환**을 통해 구현하여 시각적인 효과를 나타냅니다.

---

### 📜 회전 원리 (90도 시계 방향 회전, N×N 행렬 기준)

기존 행렬 `A[i][j]`의 값이 새로운 행렬 `B`의 `B[j][N-1-i]`로 이동합니다.

```
A[i][j] → B[j][N-1-i]
```
---

### 💻 예제 코드 (도형 이동 및 90도 회전)

이 예제는 간단한 3x3 크기의 도형을 정의하고, 이를 **90도 시계 방향**으로 회전시키는 `rotate_shape_90` 함수를 보여줍니다. 키보드 입력 처리는 복잡하므로, 여기서는 회전 로직에 중점을 둡니다.

```
#include <stdio.h>

#define N 3 // 도형을 담을 행렬의 크기 (N x N)

// 초기 도형 (3x3 행렬)
int shape[N][N] = {
    {1, 1, 0},
    {1, 0, 0},
    {0, 0, 0}
};

// 도형을 화면에 그리는 함수
void draw_shape(int s[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (s[i][j] == 1) {
                printf("■ ");
            } else {
                printf("  "); // 공백 두 칸
            }
        }
        printf("\n");
    }
}

// 90도 시계 방향으로 도형을 회전시키는 함수
void rotate_shape_90(int s[N][N]) {
    int temp[N][N]; // 회전된 도형을 임시로 저장할 배열

    // 회전 원리: A[i][j] → B[j][N-1-i]
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            // 기존 (i, j)의 값을 새로운 (j, N-1-i) 위치에 저장
            temp[j][N - 1 - i] = s[i][j];
        }
    }

    // 회전된 결과를 원본 배열에 복사
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            s[i][j] = temp[i][j];
        }
    }
}

int main() {
    printf("--- 초기 도형 ---\n");
    draw_shape(shape);

    // 회전 실행
    rotate_shape_90(shape);
    printf("\n--- 90도 회전 후 ---\n");
    draw_shape(shape);

    // 한 번 더 회전 실행
    rotate_shape_90(shape);
    printf("\n--- 180도 회전 후 ---\n");
    draw_shape(shape);
    
    // (참고: move_shape() 함수는 키보드 입력을 받아야 하므로 여기서는 생략합니다.)

    return 0;
}
```
---



### 📜 주요 함수

| 함수명 | 설명 | 기능 |
| :--- | :--- | :--- |
| `draw_shape()` | 2D 배열의 값에 따라 도형을 화면에 그림 | 값 1은 **■**, 0은 공백으로 출력 |
| `move_shape()` | 화살표 키 입력에 따라 도형을 상하좌우로 이동 | 도형의 좌표를 업데이트 |
| `rotate_shape_90()` | 스페이스 키 입력 시 도형을 90도 회전 | 회전 원리에 따라 배열의 인덱스를 변환 |
