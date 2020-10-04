// Lab1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <chrono>
#include <stdint.h>

int main()
{
    int8_t newArray[] = { 5, 3, 6, 7, 2, 0, 15, 25, 5, 5, 5, 5, 7, 7, 0, 95, 45, 63, 87, 10, 0, 0, 2, 3, 4 };
    volatile int maxDistance = 0;
    
    auto begin = std::chrono::high_resolution_clock::now();
    __asm
    {
        lea ecx, newArray
        xor edx, edx
        xor eax, eax
        xor ebx, ebx
        mov eax, 25
        mov ebx, 8
        div ebx
        mov edi, eax
        mov ebx, 0

        movsd xmm2, [ecx + 8 * ebx + 0]
        movsd xmm0, [ecx + 8 * ebx + 0]
        movsd xmm1, [ecx + 8 * ebx + 1]

        psubusb xmm0, xmm1
        psubusb xmm1, xmm2
        por xmm0, xmm1

        inc ebx
        
    start:
        cmp eax, ebx
        jle end

        movsd xmm3, [ecx+8*ebx+0]
        movsd xmm1, [ecx+8*ebx+0]
        movsd xmm2, [ecx+8*ebx+1]

        psubusb xmm1, xmm2
        psubusb xmm2, xmm3
        por xmm1, xmm2
        pmaxub xmm0, xmm1

        inc ebx
        jmp start

    end: 
        /*32 bit*/
        xor ebx, ebx
        xor eax, eax

        movd ebx, xmm0
        psrlq xmm0, 32
        movd eax, xmm0

        movd xmm1, eax
        movd xmm2, ebx
        pmaxub xmm1, xmm2

        /*16 bit*/
        xor ebx, ebx
        xor eax, eax

        movd ebx, xmm1
        shl ebx, 16
        shr ebx, 16
        psrlq xmm1, 16
        movd eax, xmm1

        movd xmm1, ebx
        movd xmm2, eax
        pmaxub xmm1, xmm2

        xor ebx, ebx

        /*8 bit*/
        movd eax, xmm1
        mov bl, al
        shr eax, 8

        movd xmm1, ebx
        movd xmm2, eax
        pmaxub xmm1, xmm2

        movd eax, xmm1
        mov maxDistance, eax
        emms
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "\nResult is: " << maxDistance << "\nTime is: " << std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count();
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
