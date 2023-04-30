#include <immintrin.h>
#include <stdio.h>
#include <time.h>

int main()
{
    // set and load individual ints
    
    /*     
        __m128i values = _mm_setr_epi32(0x1234, 0x2345, 0x3456, 0x4567);
        int first = _mm_extract_epi32(values, 0);
        int second = _mm_extract_epi32(values, 1);
        
        // load and store arrays from memory
        int array[4];
        _mm_storeu_si128((__m128i *)array, values);
        
        __m128i firstVals = _mm_setr_epi32(10, 20, 30, 40);
        __m128i secondVals = _mm_setr_epi32(5, 6, 7, 8);
        __m128i resultVals = _mm_add_epi32(firstVals, secondVals);
         */
    
    int *ArrayLinear = malloc(sizeof(int)*32768*32768);
    int *LinPtr = ArrayLinear;
    
    // linear set to 0
    clock_t LinStart = clock();
    for (int c = 10; c > 0; c--)
    {
        for (int r=0;r<32768;++r)
        {
            for(int c=0;c<32768;++c)
            {
                *LinPtr++ = 0;
            }
        }
        LinPtr = ArrayLinear;
    }
    clock_t LinEnd = clock();
    double LinTime = (LinEnd - LinStart)/(double)CLOCKS_PER_SEC;
    printf("LINEAR: set 0 = %fms\n", LinTime);
    
    clock_t SimdStart = clock();
    int *ArraySimd = malloc(sizeof(int)*32768*32768);
    int *SimdPtr = ArraySimd;
    __m128i ToSetVals = _mm_setr_epi8(0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0);
    for (int c = 10; c > 0; c--)
    {
        int i = 0;
        for (;i<(32768*32768);i+=16)
        {
            _mm_storeu_epi8((__m128i *)SimdPtr, ToSetVals);
            SimdPtr+=16;
        }
        // left over
        /* 
                for (;i<(2048*2048);i++)
                {
                    SimdPtr[i] = 0;
                }*/
        SimdPtr = ArraySimd;
        
    }
    clock_t SimdEnd = clock();
    double SimdTime = (SimdEnd - SimdStart)/(double)CLOCKS_PER_SEC;
    printf("SIMD: set 0 = %fms\n", SimdTime);
    return;
    
    
    // linear set to 1
    for (int r=0;r<32;++r)
    {
        for(int c=0;c<32;++c)
        {
            *LinPtr++ = 1;
        }
    }
    
    // linear set to 2
    for (int r=0;r<32;++r)
    {
        for(int c=0;c<32;++c)
        {
            *LinPtr++ = 2;
        }
    }
    
    
    // linear set to 3
    for (int r=0;r<32;++r)
    {
        for(int c=0;c<32;++c)
        {
            *LinPtr++ = 3;
        }
    }
    
    
    // linear set to 4
    for (int r=0;r<32;++r)
    {
        for(int c=0;c<32;++c)
        {
            *LinPtr++ = 4;
        }
    }
    
    
    // linear set to 5
    for (int r=0;r<32;++r)
    {
        for(int c=0;c<32;++c)
        {
            *LinPtr++ = 5;
        }
    }
}