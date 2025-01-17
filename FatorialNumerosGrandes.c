#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define pi  3.14159265358979323846
#define exp 2.71828182845904523536

int Qntd_Algarismos(int n) {
    double x;

    if (n < 0) {
        return 0;
    }
    if (n <= 1) {
        return 1;
    }

    x = (n * log10(n / exp) + log10(2 * pi * n) / 2.0);

    return floor(x) + 1;
}

void multiplicacao(char *p, int num) {
    int carry = 0;
    int tam = strlen(p);

    for (int i = 0; i < tam; i++) {
        int digit = p[i] - '0';
        int prod = digit * num + carry;
        p[i] = (prod % 10) + '0';
        carry = prod / 10;
    }

    while (carry) {
        p[tam++] = (carry % 10) + '0';
        carry /= 10;
    }
    p[tam] = '\0';
}

void fatorial(int n, char *p) {
    int tam;
    
    p[0] = '1'; 
    p[1] = '\0';

    for (int i = 2; i <= n; i++) {
        multiplicacao(p, i);
    }

    tam = strlen(p);
    
    for (int i = 0; i < tam / 2; i++) {
        char aux = p[i];
        p[i] = p[tam - i - 1];
        p[tam - i - 1] = aux;
    }
}

int main() {
    double num_entrada;
    int num_digitos;

    scanf("%lf", &num_entrada);

    if (num_entrada == 0 || num_entrada == 1) {
        printf("Resultado: 1\n");
        return 0;
    }

    num_digitos = Qntd_Algarismos(num_entrada);

    char *resultado = malloc((num_digitos + 1) * sizeof(char));

    fatorial(num_entrada, resultado);

    printf("Resultado: %s\n", resultado);

    free(resultado);
    return 0;
}
