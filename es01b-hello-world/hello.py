#!/usr/bin/env python3
"""Hello World: dal programma Python al processo in esecuzione."""
import os

nome = 'Mattia'
messaggio = "Hello World dell'esercizio b."

print('Hello, World!')
print(f'Studente: {nome}')
print(messaggio)
# Il sistema operativo assegna un PID al processo che esegue il programma.
print(f'PID del processo: {os.getpid()}')
