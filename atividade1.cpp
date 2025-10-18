//Daniel Fernandes Silva 222008459

#include <bits/stdc++.h>
#include <vector>
#include <math.h>
#include <map>
#include <string>
#include <cstring>

using namespace std;

long long mdc(long a, long long b) {
    if (b == 0) return a;
    return mdc(b, a % b);
}

long long primo(long long b) {
    if (b < 2) return 0;
    for (long long i = 2; i <= sqrt(b); i++) {
        if (b % i == 0)
            return 0;
    }
    return 1;
}

long long f(long long x, long long N) {
    return (x * x + 1) % N;
}

long long P(long long N, long long x0) {
    long long l = x0, t = x0;
    
    if (primo(N)) {
        cout  << N << " é primo" << endl;
        return N;
    }
    
       
    for (long long i = 0; i < 10000; i++) {
        t = f(t, N);
        l = f(l, N);
        l = f(l, N);

        long long d = mdc(abs(l - t), N);

        if (d != 1 && d != N) {
            cout << "i:" << i << " t:" << t << " l:" << l << " mdc:" << d << endl;
            
            cout << "  Fator: " << d;
            if (primo(d)) {
                cout << " (primo)" << endl;
                return d;
            } else {
                cout << " (composto - continuando fatoração)" << endl;
                return P(d, x0);
            }
        }
        
        
        if (t == l) {
            return P(N, x0 + 1);
        }
    }
    
    
    cout << "Pollard falhou" << endl;
    for (long long i = 2; i * i <= N; i++) {
        if (N % i == 0 && primo(i)) {
            return i;
        }
    }
    
    return N;
}

long long euclides_estendido(long long E, long long z) {
    
    if (mdc(E, z) != 1) {
        cout  << E << " e " << z << " não são coprimos! MDC = " << mdc(E, z) << endl;
        return -1;
    }
    
    long long t0 = 0, t1 = 1;
    long long r0 = z, r1 = E;
    
    while (r1 != 0) {
        long long quo = r0 / r1;
        
        
        long long temp_r = r1;
        r1 = r0 - quo * r1;
        r0 = temp_r;
        
        
        long long temp_t = t1;
        t1 = t0 - quo * t1;
        t0 = temp_t;
    }
    
    long long d = (t0 % z + z) % z;
    return d;
}

long long expo_m(long long b, long long ex, long long md, bool dg = false) {
    long long res = 1;
    long long base_atual = b % md;
    
    if (dg) {
        cout << "  Calculando " << b << "^" << ex << " mod " << md << endl;
    }
    
    while (ex > 0) {
        if (ex % 2 == 1) {
            res = (res * base_atual) % md;
            if (dg) {
                cout << "    Multiplica: resultado = " << res << endl;
            }
        }
        base_atual = (base_atual * base_atual) % md;
        ex = ex / 2;
        if (dg) {
            cout << "    Quadrado: base = " << base_atual << ", expoente = " << ex << endl;
        }
    }
    
    if (dg) {
        cout << "  Resultado: " << res << endl;
    }
    
    return res;
}

string RSA(long long p, long long q) {
    long long n = p * q;
    long long z = (p - 1) * (q - 1);
    long long e = 2;
    
    map<char, string> numero = {
        {'A', "11"}, {'B', "12"}, {'C', "13"}, {'D', "14"}, {'E', "15"}, {'F', "16"},
        {'G', "17"}, {'H', "18"}, {'I', "19"}, {'J', "20"}, {'K', "21"}, {'L', "22"},
        {'M', "23"}, {'N', "24"}, {'O', "25"}, {'P', "26"}, {'Q', "27"}, {'R', "28"},
        {'S', "29"}, {'T', "30"}, {'U', "31"}, {'V', "32"}, {'W', "33"}, {'X', "34"},
        {'Y', "35"}, {'Z', "36"}, {' ', "00"}
    };

    
    for (; e < z; e++) {
        if (mdc(z, e) == 1) {
            cout << " E = " << e << " (mdc(" << e << "," << z << ") = 1)" << endl;
            break;
        }
    }

    
    long long d = euclides_estendido(e, z);
    if (d == -1) {
        cout << " Não foi possível calcular D" << endl;
        return "";
    }

    cout << " D = " << d << endl;
    cout << " Verificação: " << e << " × " << d << " = " << (e * d) << " ≡ " << (e * d) % z << " mod " << z << endl;

    cout << " Chave pública: (" << n << ", " << e << ")" << endl;
    cout << " Chave privada: (" << n << ", " << d << ")" << endl;

    string mensagem = "CODIGO DE MD";
    string mensagemprecodificada = "";
    
    
    for (long long i = 0; i < mensagem.size(); i++) {
        mensagemprecodificada += numero[mensagem[i]];
    }

    cout << " Mensagem pré-codificada: " << mensagemprecodificada << endl;

    
    vector<long long> bloco;
    for (size_t i = 0; i < mensagemprecodificada.length(); i += 2) {
        string par = mensagemprecodificada.substr(i, 2);
        long long v = stoi(par);
        bloco.push_back(v);
    }

    cout << " Blocos M: ";
    for (long long i = 0; i < bloco.size(); i++) cout << bloco[i] << " ";
    cout << endl;

    
    cout << "\n CRIPTOGRAFANDO..." << endl;
    string crypto = "";
    vector<long long> bloco_crypto;

    for (long long i = 0; i < bloco.size(); i++) {
        long long M = bloco[i];
        long long C = expo_m(M, e, n, true);  
        
        bloco_crypto.push_back(C);
        crypto += to_string(C);  
        
        cout << "  M[" << i << "] = " << M << " → C[" << i << "] = " << C << endl;
    }
		
    cout << " Texto criptografado: " << crypto << endl;
    return crypto;
}

void decrypto(string crypto, long long p, long long q) {
  
}

int main() {
    long long x, y;
    
    cout << "=== SISTEMA RSA COMPLETO ===" << endl;
    cout << "Digite dois números compostos:  ";
    cin >> x >> y;
    
    cout << "\n=== ETAPA 1: FATORAÇÃO ===" << endl;
    long long p = P(x, 2);
    long long q = P(y, 2);
    
    cout << "\n=== RESULTADO DA FATORAÇÃO ===" << endl;
    cout << "p: " << p << " (primo: " << primo(p) << ")" << endl;
    cout << "q: " << q << " (primo: " << primo(q) << ")" << endl;
    
    if (p != q && primo(p) && primo(q)) {
        cout << "\n=== ETAPA 2: CRIPTOGRAFIA RSA ===" << endl;
        string result = RSA(p, q);
        
        cout << "\n=== ETAPA 3: DESCRIPTOGRAFIA ===" << endl;
        decrypto(result, p, q);
    } else {
        cout << " ERRO: p e q devem ser primos diferentes!" << endl;
    }
    
    return 0;
}
