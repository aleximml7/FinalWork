#include <stdio.h>
#include <windows.h>
#define _CRT_SECURE_NO_WARNINGS

__declspec(naked) int calc_func(int a, int b, int c, int d, int e) {
    __asm {
        push ebp
        mov ebp, esp
        push ebx

        mov eax, [ebp + 8]
        imul dword ptr[ebp + 12]
        add eax, [ebp + 16]
        mov ebx, eax

        mov eax, [ebp + 20]
        cdq
        idiv dword ptr[ebp + 24]
        sub ebx, eax
        mov eax, ebx

        pop ebx
        pop ebp
        ret
    }
}

int main(void) {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    int a, b, c, d, e, y;
    const char* input_msg = "введите a, b, c, d, e (через пробел):\n";
    const char* input_format = "%d %d %d %d %d";
    const char* output_format = "a=%d, b=%d, c=%d , d=%d , e=%d \ny=%d\n";

    __asm {
        push input_msg
        call printf
        add esp, 4

        lea eax, e
        push eax
        lea eax, d
        push eax
        lea eax, c
        push eax
        lea eax, b
        push eax
        lea eax, a
        push eax
        push input_format
        call scanf
        add esp, 24

        push e
        push d
        push c
        push b
        push a
        call calc_func
        add esp, 20
        mov y, eax

        push y
        push e
        push d
        push c
        push b
        push a
        push output_format
        call printf
        add esp, 28
    }
    return 0;
}