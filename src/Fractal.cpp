#include <cmath>
#include "Fractal.hpp"

using namespace std;

// hackerrank.com/domainsut
// wersja ściśnięta:
// for(int i=0;i<9;i++{do();}
// 9*[]{do();};
// - o 14 znaków mniej
// wersja rozlazła:
// for (int i = 0; i < 9; i++ { do(); }
// 9 * [] {do(); };
// - o 20 znaków mniej
