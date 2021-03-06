## Algorytm spiralny dla zagadnienia QAP

Repozytorium zawiera wstępną wersję implementacji algorytmu spiralnego(SPO), dla przestrzeni n-wymiarowej.

### Opis algorytmu

Algorytm spiralny zaliczany jest do algorytmów stadnych. Opiera się on na zjawisku spiralnym występującym w naturze, które łączy w sobie mechanizmy zarówno dywersyfikacji jak i intesyfikacji.

Algorytm spiralny w swoim działaniu wykorzystuje przybliżenie funkcji celu kilkoma punktami, które w kolejnych iteracjach podążają za aktualnym najlepszym przybliżeniem po trajektoriach spiralnych.

Kolejno kroki algorytmu spiralnego:
1. Ustalenie liczby punktów przybliżeń funkcji celu: m > 2, oraz kryterium zakończenia.
   Ustalenie wartości macierzy rotacji: R(θ)
   Ustalenie wartość parametru h ∈ (0, 1).
2. Wylosowanie wartości punktów przybliżeń i wybranie aktualnego centrum.
3. Przypisanie wartości parametru r(k).

![alt text](https://image.ibb.co/kpavgS/1.png "r(k)")

gdzie:
* k - nr aktualnej iteracji algorytmu
* k* - liczba iteracji w których zostało zmienione centrum
4. Aktualizacja punktów przybliżeń.

![alt text](https://image.ibb.co/csNGMS/2.png "nowe przyblizenia")

gdzie:
* xi - punkty przybliżeń

5. Aktualizacja centrum.

![alt text](https://image.ibb.co/idqaFn/3.png "nowe centrum")

gdzie:
* *ib = min{argmin{f(xi(k+1))}}*

6. Sprawdzenie warunku stopu lub powrót do punktu 3.

### Wizualizacja działania algorytmu:

![alt text](https://image.ibb.co/gq7Bo7/4.png "nowe centrum")

### Przykładowe wyniki działania algorytmu:

funkcja celu | ilość punktów przybliżeń | ilość potrzebnych iteracji
-|-|-
x1^2 + x2^2 | 1 | 159
x1^2 + x2^2 | 4 | 35
x1^2 + x2^2 | 10 | 29
x1^2 + x2^2 + x3^2 | 1 | 170
x1^2 + x2^2 + x3^2 | 4 | 42
x1^2 + x2^2 + x3^2 | 10 | 36




### Parametry algorytmu:

Parametry algorytmu dostępne są w pliku utils.h.
Dostępne parametry:
* MAX_RANDOM_ARG - maksymalny wartość argumentów losowanych podczas inicjalizacji algorytmu
* MIN_RANDOM_ARG - minimalna wartość argumentów losowanych podczas inicjalizacji algorytmu
* NUMBER_OF_SEARCH_POINTS - liczba wykorzystywanych punktów przybliżeń
* NUMBER_OF_ITERATIONS - maksymalna liczba iteracji (jedyne kryterium stop)
* STEP_RATE - wartość parametru h
* DIMENTIONS - wymiar przesteni danych
* REVOLUTION_ANGLE - kąt obrotu spirali

### Kompilacja i uruchomienie w zależności od systemu operacyjnego:

#### Linux:
* g++ main.cpp Point.cpp RandomValuesGenerator.cpp SpiralOptimization.cpp utils.cpp
* ./a.out

#### Windows z cygwin:
* g++ main.cpp Point.cpp RandomValuesGenerator.cpp SpiralOptimization.cpp utils.cpp
* ./a.exe

