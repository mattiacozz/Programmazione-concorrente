#include <stdio.h>   // printf
#include <unistd.h>  // getpid, fork

int main() {
    // Il processo padre inizializza le variabili per base, altezza e risultato
    int base = 5;
    int altezza = 10;
    int risultato;

    // Creazione del processo figlio
    int pid = fork();

    if (pid < 0) {
        // Controllo di errore in caso di fallimento della fork
        printf("Creazione del processo figlio fallita!\n");
        return 1;
    } else if (pid == 0) {
        // Codice eseguito dal processo figlio: calcola e stampa il perimetro
        risultato = (base + altezza) * 2;
        printf("[Figlio] - PID: %d, Il perimetro del rettangolo è: %d\n", getpid(), risultato);
    } else {
        // Codice eseguito dal processo padre: calcola e stampa l'area
        risultato = base * altezza;
        printf("[Padre] - PID: %d, L'area del rettangolo è: %d (PID Figlio: %d)\n", getpid(), risultato, pid);
    }

    return 0;
}
