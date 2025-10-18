// Daniel Fernandes Silva 222008459
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


//Algoritmo de Euclides: 3 mod 11 = 3
//Algoritmo de Euclides: 11 mod 3 = 2
//Algoritmo de Euclides: 3 mod 2 = 1
//Algoritmo de Euclides: 2 mod 1 = 0
//Substituindo, temos que o inverso de 3 em 11 é 4.
//
//Fazendo a multiplicação modular: 7 * 4 mod 11 = 6
//Sendo 4 o inverso de 3.
//Valor final da congruência: 4
//
//
//Considere o código abaixo, que realiza o cálculo da divisão modular H ÷ G (mod Zn) e
//depois computa a^x mod n1, aplicando o Pequeno Teorema de Fermat ou o Teorema de
//Euler, conforme a natureza de n1, classifique como Verdadeiro (V) ou Falso (F) cada uma
//das afirmativas a seguir:
//
//
//(V) O algoritmo de Euclides estendido é utilizado para calcular o inverso modular de um número.
//
//(F) Se mdc(G, Zn) ≠ 1, o programa ainda consegue encontrar o inverso de G em Zn.
//
//(V) A operação (H * inverso) % Zn representa a divisão modular de H por G.
//
//(V) Se n1 for primo, o código aplica o Pequeno Teorema de Fermat para simplificar o cálculo de
//a^x mod n1.
//
//(F) A função powMod implementa o cálculo de potência modular utilizando multiplicações diretas
//sem otimização.
//
//(V) Quando o resultado do inverso é negativo, o código ajusta o valor somando o módulo m0.
//
//(V) O cálculo de fi(n1) (função totiente de Euler) é utilizado apenas quando n1 não é primo.