// Cache line lock
// if two variables are in the same cache line
// writes on the two variables are sequential 
// even on two threads
//
// Remove padding2 to see that.
//
// Ref: Maximize Locality, Minimize Contention by Herb Sutter
#include "common.h"

using namespace std;

char padding0[128];

int a;
// char padding3[64];
int b;

void thread_a(int max) { a = 0; for (int i = 0; i < max; ++i) ++a; }
void thread_b(int max) { b = 0; for (int i = 0; i < max; ++i) ++b; }

char padding1[128];

int c;
char padding2[64];
int d;

void thread_c(int max) { c = 0; for (int i = 0; i < max; ++i) ++c; }
void thread_d(int max) { d = 0; for (int i = 0; i < max; ++i) ++d; }


int main(void)
{
    for (int i = 0, max = 8; i < 14; ++i, max <<= 2) {
        auto begin = std::chrono::high_resolution_clock::now();
        std::thread ta(thread_a, max);
        std::thread tb(thread_b, max);
        ta.join(); tb.join();
        auto end = std::chrono::high_resolution_clock::now();
        auto nopad = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);								
        begin = std::chrono::high_resolution_clock::now();
        std::thread tc(thread_c, max);
        std::thread td(thread_d, max);
        tc.join(); td.join();
        end = std::chrono::high_resolution_clock::now();
        auto pad = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
        
        std::cout << setw(20) << max
                  << setw(20) << nopad.count()
                  << setw(20) << pad.count()
                  << std::endl;
    }
}
