#include <stdio.h>   // printf
#include <unistd.h>  // getpid

int main(int argc, char **argv) {

  printf("\nAvvio del processo con pid=%d\n", getpid());
  for(;;) {;}
}
