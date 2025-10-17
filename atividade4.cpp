#include <stdio.h>

#ifdef WIN32
#include <windows.h>
#endif

int mdcComPassos(int a, int b) {
    int resto;
    while (b != 0) { // (linha 10)
        resto = a % b;
        printf("Algoritmo de Euclides: %d mod %d = %d\n", a, b, resto);
        a = b;       // (linha 14)
        b = resto;
    }
    return a;
}

int inversoModular(int a, int m) {
    int m0 = m, t, q;
    int x0 = 0, x1 = 1;
    int A = a, B = m;

    int g = mdcComPassos(a, m); // (linha 23)
    if (g != 1) {
        printf("Não existe inverso modular.\n");
        return 0;
    }

    while (m != 0) {
        q = a / m;
        t = m;
        m = a % m;
        a = t;

        t = x0;
        x0 = x1 - q * x0;
        x1 = t;
    }

    if (x1 < 0)
        x1 += m0; // (linha 36)

    printf("Substituindo, temos que o inverso de %d em %d é %d.\n\n", A, B, x1);
    return x1;
}

int expMod(int a, int x, int n1) {
    long long resultado = 1;
    a = a % n1;

    while (x > 0) { // (linha 45)
        if (x % 2 == 1)
            resultado = (resultado * a) % n1;
        a = (a * a) % n1;
        x /= 2;
    }

    return resultado;
}

int main() {
#ifdef WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif

    int H, G, Zn, x, n1;

    printf("Insira H: ");
    scanf("%d", &H);
    printf("Insira G: ");
    scanf("%d", &G);
    printf("Insira Zn: ");
    scanf("%d", &Zn);
    printf("Insira x: ");
    scanf("%d", &x);
    printf("Insira n1: ");
    scanf("%d", &n1);
    printf("\n");

    int inverso = inversoModular(G, Zn); // (linha 72)
    int a = (H * inverso) % Zn;

    printf("Fazendo a multiplicação modular: %d * %d mod %d = %d\n", H, inverso, Zn, a);
    printf("Sendo %d o inverso de %d.\n", inverso, G);

    int resultado = expMod(a, x, n1); // (linha 78)
    printf("Valor final da congruência: %d\n", resultado);

    return 0;
}
