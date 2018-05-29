#include <cmath>
#include "Fractal.hpp"

using namespace std;

// hackerrank.com/domainsut
// wersja ściśnięta:
// for(int i=0;i<9;i++){do();}
// 9*[]{do();};
// - o 15 znaków mniej
// wersja rozlazła:
// for (int i = 0; i < 9; i++) { do(); }
// 9 * [] {do(); };
// - o 21 znaków mniej
// wersja superrozlazła:
// for ( int i = 0 ; i < 9 ; i ++ ) { do () ; }
// 9 * [] { do () ; };
// - o 25 znaków mniej
// nazwy indeksów dłuższe, np. index
// for ( int index = 0 ; index < 9 ; index ++ ) { do () ; }
// 9 * [] { do () ; } ;
// - o 37 znaków mniej

