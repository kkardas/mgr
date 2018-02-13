## Algorytm spiralny dla zagadnienia QAP

Repozytorium zawiera wstępną wersję implementacji algorytmu spiralnego(SPO), dla przestrzeni n-wymiarowej.

### Opis algorytmu

Algorytm spiralny zaliczany jest do algorytmów stadnych. Opiera się on na zjawisku spiralnym występującym w naturze, które łączy w sobie mechanizmy zarówno dywersyfikacji jak i intesyfikacji.

Algorytm spiralny w swoim działaniu wykorzystuje przybliżenie funkcji celu kilkoma punktami, które w kolejnych iteracjach podążają za aktualnym najlepszym przybliżeniem po trajektoriach spiralnych.

### Kompilacja i uruchomienie w zależności od systemu operacyjnego:

#### Linux:
* g++ main.cpp Point.cpp RandomValuesGenerator.cpp SpiralOptimization.cpp utils.cpp
* ./a.out

#### Windows z cygwin:
* g++ main.cpp Point.cpp RandomValuesGenerator.cpp SpiralOptimization.cpp utils.cpp
* ./a.exe

