# Graph Generator

## Opis
Ten projekt składa się z dwóch głównych modułów:
1. **Generator grafu** (`graph.c`) - Program generuje graf z określoną liczbą wierzchołków, który może być skierowany lub nieskierowany. Graf zapisywany jest do pliku tekstowego w formacie czytelnym dla użytkownika.
2. **Ekstraktor liczb** (`extract.c`, `extract.h`) - Odpowiada za wybór liczby wierzchołków

## Jak działa

### Generator Grafu
- Graf jest generowany na podstawie liczby wierzchołków podanej przez użytkownika lub wylosowanej losowo.
- Wierzchołki są rozmieszczane na siatce.
- Użytkownik może wybrać, czy graf ma być skierowany (z kierunkowymi strzałkami), czy nieskierowany.

### Ekstraktor Liczb
- Funkcja `extract_number` w pliku `extract.c` wyciąga liczbę z podanego ciągu wejściowego:

## Instrukcja

1. **Kompilacja**
   - Skorzystaj z kompilatora `gcc`:
     ```
     gcc -o graph_generator graph.c extract.c
     ```

2. **Uruchomienie programu**
   - Po skompilowaniu uruchom plik wykonywalny:
     ```
     ./graph_generator
     ```

3. **Interakcja z programem**
   - Program zapyta, czy chcesz podać liczbę wierzchołków:
     - Wprowadź `y`, aby podać liczbę (w zapisie słownym lub cyfrowym).
     - Wprowadź `n`, aby wygenerować losową liczbę wierzchołków.
   - Program zapyta, czy graf ma być skierowany:
     - Wprowadź `y`, aby wybrać graf skierowany.
     - Wprowadź `n`, aby wybrać graf nieskierowany.
   - Graf zostanie zapisany w pliku `output.txt`.

## Output

Po uruchomieniu programu, graf zostanie zapisany w pliku `output.txt`. Wynik zawiera:

1. **Lista połączeń w grafie**  
   Każde połączenie między wierzchołkami jest przedstawione w postaci:
   - `[x] --> [y]`: skierowane połączenie od wierzchołka `x` do `y`.
   - `[x] <-> [y]`: obustronne połączenie między wierzchołkami `x` i `y`.
   - `[x] <-- [y]`: skierowane połączenie od wierzchołka `y` do `x`.

   Przykład:

    [1] --> [0]                                 
    [1] <-- [4]     
    [0] <-> [2]     
    [2] --> [3] 


2. **Macierz połączeń (układ wierzchołków)**  
Macierz wizualizuje rozmieszczenie wierzchołków w siatce. Liczby oznaczają kolejne wierzchołki, a `[-]` oznacza puste miejsce (bez wierzchołka).

Przykład:

    [1][4][-][-][-] 
    [0][-][-][-][-]
    [2][-][-][-][-]
    [3][-][-][-][-] 
    [-][-][-][-][-] 