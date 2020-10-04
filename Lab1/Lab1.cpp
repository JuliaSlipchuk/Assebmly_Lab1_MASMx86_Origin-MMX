// Lab1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <chrono>

int main()
{
    unsigned int array[] = { 5, 3, 6, 7, 2, 0, 15, 25, 5, 5, 5, 5, 7, 7, 0, 95, 45, 63, 87, 10, 0, 0, 2, 3, 4 };
    int counter = 0;
    int maxDistance = 0;
    int arrayStart = 0;

    auto begin = std::chrono::high_resolution_clock::now();
    __asm
    {
        lp:
            cmp counter, 23
            jg end

            mov eax, counter
            lea ebx, array[eax * 4]
            inc counter
            mov eax, counter
            lea edx, array[eax * 4]

            mov ecx, [edx]
            sub ecx, [ebx]

            or ecx, ecx
            jns ifPos
            neg ecx
            ifPos :

        cmp ecx, maxDistance
            jl lp
            mov maxDistance, ecx
            jmp lp
            mov eax, maxDistance

            end :
        
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Result is: " << maxDistance << "\nTime is: " << std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count();

    int8_t newArray[] = { 5, 3, 6, 7, 2, 0, 15, 25, 5, 5, 5, 5, 7, 7, 0, 95, 45, 63, 87, 10, 0, 0, 2, 3, 4 };
    begin = std::chrono::high_resolution_clock::now();
    __asm 
    {
        lea ecx, newArray

        /*5, 3, 6, 7, 2, 0, 15, 25, 5*/
        movq mm2, [ecx]
        movq mm0, [ecx]
        movq mm1, 1[ecx]

        psubusb mm0, mm1
        psubusb mm1, mm2
        por mm0, mm1

        /*5, 5, 5, 5, 7, 7, 0, 95, 45*/
        movq mm3, 8[ecx]
        movq mm1, 8[ecx]
        movq mm2, 9[ecx]

        psubusb mm1, mm2
        psubusb mm2, mm3
        por mm1, mm2
        pmaxub mm0, mm1

        /*45, 63, 87, 10, 0, 0, 2, 3, 4*/
        movq mm3, 16[ecx]
        movq mm1, 16[ecx]
        movq mm2, 17[ecx]

        psubusb mm1, mm2
        psubusb mm2, mm3
        por mm1, mm2
        pmaxub mm0, mm1

        /*32 bit*/
        xor ebx, ebx
        xor eax, eax

        movd ebx, mm0
        psrlq mm0, 32
        movd eax, mm0

        movd mm1, eax
        movd mm2, ebx
        pmaxub mm1, mm2

        /*16 bit*/
        xor ebx, ebx
        xor eax, eax

        movd ebx, mm1
        shl ebx, 16
        shr ebx, 16
        psrlq mm1, 16
        movd eax, mm1

        movd mm1, ebx
        movd mm2, eax
        pmaxub mm1, mm2

        xor ebx, ebx

        /*8 bit*/
        movd eax, mm1
        mov bl, al
        shr eax, 8

        movd mm1, ebx
        movd mm2, eax
        pmaxub mm1, mm2

        movd maxDistance, mm1
        emms
    }
    end = std::chrono::high_resolution_clock::now();
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
