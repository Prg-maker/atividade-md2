#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <cmath>
using namespace std;

// --- Funções auxiliares ---
long long mdc(long long a, long long b) {
    if (b == 0) return a;
    return mdc(b, a % b);
}

long long primo(long long b) {
    if (b < 2) return 0;
    for (long long i = 2; i <= sqrt(b); i++) {
        if (b % i == 0) return 0;
    }
    return 1;
}

long long phi_euler(long long n) {
    if (primo(n)) return n - 1;
    long long result = n;
    for (long long p = 2; p * p <= n; p++) {
        if (n % p == 0) {
            while (n % p == 0) n /= p;
            result -= result / p;
        }
    }
    if (n > 1) result -= result / n;
    return result;
}

long long mod_pow(long long base, long long exponent, long long mod) {
    if (mod == 1) return 0;
    long long result = 1;
    base %= mod;
    while (exponent > 0) {
        if (exponent % 2 == 1) result = (result * base) % mod;
        exponent >>= 1;
        base = (base * base) % mod;
    }
    return result;
}

long long expo_modular_automatico(long long base, long long exponent, long long mod) {
    if (primo(mod) && mdc(base, mod) == 1) {
        long long reduced_exponent = exponent % (mod - 1);
        return mod_pow(base, reduced_exponent, mod);
    } else if (mdc(base, mod) == 1) {
        long long phi_n = phi_euler(mod);
        long long reduced_exponent = exponent % phi_n;
        return mod_pow(base, reduced_exponent, mod);
    } else {
        return mod_pow(base, exponent, mod);
    }
}

long long euclides_estendido(long long E, long long z) {
    long long t0 = 0, t1 = 1;
    long long r0 = z, r1 = E;
    while (r1 != 0) {
        long long quo = r0 / r1;
        long long temp_r = r0; r0 = r1; r1 = temp_r - quo * r1;
        long long temp_t = t0; t0 = t1; t1 = temp_t - quo * t1;
    }
    if (r0 != 1) return -1;
    long long d = t0 % z;
    if (d < 0) d += z;
    return d;
}

// --- Função Pollard para fatoração ---
long long f(long long x, long long N) {
    return (x * x + 1) % N;
}

long long P(long long N, long long x0) {
    long long l = x0, t = x0;
    if (primo(N)) return N;
    for (long long i = 0; i < 100; i++) {
        t = f(t, N);
        l = f(l, N);
        l = f(l, N);
        long long d = mdc(abs(l - t), N);
        if (d != 1 && d != N) {
            if (primo(d)) return d;
            return P(d, 2);
        }
        if (t == l) return P(N, x0 + 1);
    }
    for (long long i = 2; i * i <= N; i++)
        if (N % i == 0 && primo(i)) return i;
    return N;
}

// --- RSA Criptografia ---
string RSA(long long p, long long q, vector<long long> &blocos_crypto) {
    long long n = p * q;
    long long z = (p - 1) * (q - 1);
    long long e = 2;
    while (e < z && mdc(e, z) != 1) e++;
    long long d = euclides_estendido(e, z);

    map<char, string> numero = {
        {'A',"11"}, {'B',"12"}, {'C',"13"}, {'D',"14"}, {'E',"15"}, {'F',"16"},
        {'G',"17"}, {'H',"18"}, {'I',"19"}, {'J',"20"}, {'K',"21"}, {'L',"22"},
        {'M',"23"}, {'N',"24"}, {'O',"25"}, {'P',"26"}, {'Q',"27"}, {'R',"28"},
        {'S',"29"}, {'T',"30"}, {'U',"31"}, {'V',"32"}, {'W',"33"}, {'X',"34"},
        {'Y',"35"}, {'Z',"36"}, {' ',"00"}
    };

    string mensagem = "CODIGO DE MD";
    string mensagem_precodificada = "";
    for (char c : mensagem) mensagem_precodificada += numero[c];

    vector<long long> blocos;
    for (size_t i = 0; i < mensagem_precodificada.size(); i += 2) {
        string par = mensagem_precodificada.substr(i, 2);
        blocos.push_back(stoll(par));
    }

    string crypto = "";
    for (long long M : blocos) {
        long long C = expo_modular_automatico(M, e, n);
        blocos_crypto.push_back(C);
        crypto += to_string(C);
    }

    return crypto;
}

// --- RSA Descriptografia ---
string decrypto(long long p, long long q, vector<long long> &blocos_crypto) {
    long long n = p * q;
    long long z = (p - 1) * (q - 1);
    long long e = 2;
    while (e < z && mdc(e, z) != 1) e++;
    long long d = euclides_estendido(e, z);

    map<string, char> letra = {
        {"11",'A'}, {"12",'B'}, {"13",'C'}, {"14",'D'}, {"15",'E'}, {"16",'F'},
        {"17",'G'}, {"18",'H'}, {"19",'I'}, {"20",'J'}, {"21",'K'}, {"22",'L'},
        {"23",'M'}, {"24",'N'}, {"25",'O'}, {"26",'P'}, {"27",'Q'}, {"28",'R'},
        {"29",'S'}, {"30",'T'}, {"31",'U'}, {"32",'V'}, {"33",'W'}, {"34",'X'},
        {"35",'Y'}, {"36",'Z'}, {"00",' '}
    };

    string msg = "";
    for (long long C : blocos_crypto) {
        long long M = expo_modular_automatico(C, d, n);
        string bloco = to_string(M);
        if (bloco.size() == 1) bloco = "0" + bloco;
        if (letra.count(bloco)) msg += letra[bloco];
        else msg += '?';
    }

    return msg;
}

// --- MAIN ---
int main() {
    long long x, y;
    cout << "Digite dois números compostos: ";
    cin >> x >> y;

    long long p = P(x, 2);
    long long q = P(y, 2);

    cout << "\nResultado da fatoração:\n";
    cout << "p: " << p << ", q: " << q << endl;

    if (p != q && primo(p) && primo(q)) {
        vector<long long> blocos_crypto;
        string texto_cripto = RSA(p, q, blocos_crypto);

        cout << "\nTexto criptografado: " << texto_cripto << endl;
        string texto_decripto = decrypto(p, q, blocos_crypto);
        cout << "Texto descriptografado: " << texto_decripto << endl;
    } else {
        cout << "ERRO: p e q devem ser primos diferentes!" << endl;
    }

    return 0;
}
