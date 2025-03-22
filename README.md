# pointers-in-3D

Acest proiect foloseste pointerii 3D pentru a realiza functionalitatile unui joc de tip *minecraft*

## Task1

A fost creata si functia ajutatoare "is_in_chunk" care verifica daca un block este in interiorul chunk-ului. Functia "chunk_place_block" o foloseste pe cea din urma si adauga pe pozitia (x,y,z) (daca este in interiorul chunkului), block-ul de tip "block".

## Task2

Functia "chunk_fill_cuboid" parcurge cuboidul dat de colturile (x,y,z) si (x0,y0,z0), de la coltul cel mai jos la cel mai de sus si il umple cu block-uri de tip "block" cu ajutorul functiei "chunk_place_block". De asemenea pentru simplitate am implementat si functiile "mini" si "maxi".

## Task3

Functia "chunk_fill_sphere" parcurge chunk-ul si calculeaza distanta de la centrul sferei la fiecare block din chunk, iar daca aceasta distanta este mai mica sau egala cu raza, block-ul respectiv este plasat.

## Task4

Functia "chunk_shell" realizeaza o copie a chunk-ului original, il parcurge iar la intalnirea fiecarui target_block ii este umplut "shell-ul".

## Task 5

Functia "chunk_fill_xz" foloseste o metoda recursiva pornind de la block-ul de coordonate (x,y,z) parcurgand toate block-urile de acelasi tip vecine in planul XOZ la care se poate ajunge prin deplasare cu cate un block si inlocuindu-le cu block-uri de tip "block".

## Task 6

Functia "chunk_fill" foloseste metoda recursiva de la task-ul 5, dar fiind parcursi vecinii si din planele paralele cu XOZ (parcurgere in spatiu).

## Task 7

Functia "chunk_rotate_y" realizeaza transpunerea (transpusa matricei) fiecarui plan XOZ din chunk-ul original, schimband si dimensiunile acestuia.

## Task 8

Functia "chunk_apply_gravity" realizeaza o copie INT a chunk-ului original in care sunt numerotate cu numere de la 1 la "block" fiecare structura de block-uri diferita cu ajutorul functiei "chunk_numerotate_structs". Apoi, structurile blocate, care nu se pot misca una din cauza celeilalte sunt numerotate cu aceeasi valoare. Dupa aceea, sunt mutate structurile cate un block in jos pana cand nu mai poate fi mutata niciuna. Este actualizat "new_height" si eliberata memoria neutilizata.

## Task 9

Functia "chunk_encode" calculeaza numarul de octeti necesari pentru alocarea de memorie a vectorului de caractere, apoi fiecare block din chunk incepand cu cel de la pozitia (0,0,0) este encodat si salvat in vectorul de caractere "encoded".

## Task 10

Functia "chunk_decode" cu ajutorul unor "masti" si a operatiilor pe biti reuseste sa decodifice vectorul de caractere code si sa construiasca chunk-ul. Pentru fiecare element al vectorului se stabileste daca acesta retine mai putin sau mai mult de 32 de block uri, iar apoi acestea se plaseaza in chunk in ordine.
