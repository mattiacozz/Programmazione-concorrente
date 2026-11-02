/*
 * Titolo: Simulazione del controllo di LED con processi figli (fork)
 *
 * Il padre legge i comandi da tastiera, imposta la variabile "led"
 * e crea un processo figlio che fa lampeggiare il LED scelto.
 * Il pin fisico e' simulato: lo stato viene scritto a schermo.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/* Numero di lampeggi per ogni comando */
#define LAMPEGGI    10

/* Valori della variabile led */
#define LED_VERDE   1
#define LED_ROSSO   2
#define LED_GIALLO  3

/* Impostata dal padre PRIMA della fork:
   il figlio ne riceve una copia con lo stesso valore */
int led = 0;

/* Simulazione del pin fisico: qui si scrive solo a schermo.
   Su un Raspberry Pi si potrebbe comandare il pin vero da questa funzione. */
void scrivi_pin(const char *nome, int acceso)
{
    if (acceso) {
        printf("led %s acceso\n", nome);
    } else {
        printf("led %s spento\n", nome);
    }
    fflush(stdout);
}

/* Funzione eseguita dal processo figlio:
   legge "led" e fa lampeggiare il LED corrispondente */
void lampeggia(void)
{
    const char *nome;
    useconds_t intervallo;   /* in microsecondi */
    int i;

    if (led == LED_VERDE) {
        nome = "verde";
        intervallo = 300000;      /* 0.3 s */
    } else if (led == LED_ROSSO) {
        nome = "rosso";
        intervallo = 700000;      /* 0.7 s */
    } else {
        nome = "giallo";
        intervallo = 1200000;     /* 1.2 s */
    }

    /* 10 lampeggi: ogni lampeggio = acceso + spento */
    for (i = 0; i < LAMPEGGI; i++) {
        scrivi_pin(nome, 1);
        usleep(intervallo);
        scrivi_pin(nome, 0);
        usleep(intervallo);
    }
}

int main(void)
{
    char comando;
    pid_t pid;

    do {
        printf("Comando (v = verde, r = rosso, g = giallo, q = esci): ");
        fflush(stdout);
        scanf(" %c", &comando);   /* lo spazio prima di %c salta l'invio */

        if (comando == 'v' || comando == 'r' || comando == 'g') {

            /* Il padre imposta led prima di creare il figlio */
            if (comando == 'v') led = LED_VERDE;
            if (comando == 'r') led = LED_ROSSO;
            if (comando == 'g') led = LED_GIALLO;

            pid = fork();

            if (pid < 0) {
                /* fork fallita */
                printf("Errore nella creazione del processo figlio\n");
            } else if (pid == 0) {
                /* Codice del FIGLIO */
                lampeggia();
                exit(0);
            } else {
                /* Codice del PADRE: aspetta la fine del figlio,
                   cosi' non restano processi zombie e non si
                   sovrappongono due lampeggi */
                wait(NULL);
                printf("Lampeggio terminato\n");
            }

        } else if (comando != 'q') {
            printf("Comando non valido\n");
        }

    } while (comando != 'q');

    printf("Programma terminato\n");
    return 0;
}
