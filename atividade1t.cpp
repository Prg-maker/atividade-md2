// Daniel Fernandes Silva 222008459

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <cmath>
#include <stdexcept>
#include <cctype>
using namespace std;

// --- Funções auxiliares ---
long long mdc(long long a, long long b) {
    cout << "  Calculando MDC(" << a << ", " << b << "):" << endl;
    long long resto;
    int passo = 1;
    while (b != 0) {
        resto = a % b;
        cout << "    Passo " << passo++ << ": " << a << " = " << b << " * " << (a/b) 
             << " + " << resto << endl;
        a = b;
        b = resto;
    }
    cout << "    MDC = " << a << endl;
    return a;
}

long long mdc_silent(long long a, long long b) {
    long long resto;
    while (b != 0) {
        resto = a % b;
        a = b;
        b = resto;
    }
    return a;
}

long long primo(long long b) {
    if (b < 2) return 0;
    for (long long i = 2; i <= sqrt(b); i++) {
        if (b % i == 0) return 0;
    }
    return 1;
}

long long phi_euler(long long n) {
    cout << "  Calculando φ(" << n << "):" << endl;
    if (primo(n)) {
        cout << "    " << n << " é primo → φ(" << n << ") = " << n << " - 1 = " << (n-1) << endl;
        return n - 1;
    }
    
    long long result = n;
    long long temp = n;
    for (long long p = 2; p * p <= n; p++) {
        if (n % p == 0) {
            cout << "    Fator primo encontrado: " << p << endl;
            while (n % p == 0) n /= p;
            result -= result / p;
            cout << "    φ atualizado: " << result << endl;
        }
    }
    if (n > 1) {
        cout << "    Fator primo restante: " << n << endl;
        result -= result / n;
    }
    cout << "    φ(" << temp << ") = " << result << endl;
    return result;
}

long long mod_pow(long long base, long long exponent, long long mod) {
    cout << "    Exponenciação modular (" << base << "^" << exponent << " mod " << mod << "):" << endl;
    if (mod == 1) return 0;
    long long result = 1;
    base %= mod;
    int passo = 1;
    
    while (exponent > 0) {
        if (exponent % 2 == 1) {
            cout << "      Passo " << passo << ": resultado = (" << result << " * " << base << ") mod " << mod;
            result = (result * base) % mod;
            cout << " = " << result << endl;
        } else {
            cout << "      Passo " << passo << ": expoente par, apenas eleva base ao quadrado" << endl;
        }
        cout << "      Passo " << passo << ": base = (" << base << " * " << base << ") mod " << mod;
        base = (base * base) % mod;
        cout << " = " << base << endl;
        exponent >>= 1;
        passo++;
    }
    cout << "    Resultado final: " << result << endl;
    return result;
}

long long expo_modular_automatico(long long base, long long exponent, long long mod) {
    cout << "\n  === CALCULO DE " << base << "^" << exponent << " mod " << mod << " ===" << endl;
    
    if (primo(mod) && mdc_silent(base, mod) == 1) {
        cout << "  ✓ APLICANDO PEQUENO TEOREMA DE FERMAT" << endl;
        cout << "    Condições satisfeitas:" << endl;
        cout << "    - " << mod << " é primo" << endl;
        cout << "    - mdc(" << base << ", " << mod << ") = 1" << endl;
        cout << "    Fórmula: a^(p-1) ≡ 1 mod p" << endl;
        cout << "    Redução: " << exponent << " mod " << (mod-1);
        
        long long reduced_exponent = exponent % (mod - 1);
        cout << " = " << reduced_exponent << endl;
        cout << "    Cálculo: " << base << "^" << reduced_exponent << " mod " << mod << endl;
        
        long long resultado = mod_pow(base, reduced_exponent, mod);
        return resultado;
    } 
    else if (mdc_silent(base, mod) == 1) {
        cout << "  ✓ APLICANDO TEOREMA DE EULER" << endl;
        cout << "    Condições satisfeitas:" << endl;
        cout << "    - mdc(" << base << ", " << mod << ") = 1" << endl;
        cout << "    Fórmula: a^φ(n) ≡ 1 mod n" << endl;
        
        long long phi_n = phi_euler(mod);
        cout << "    Redução: " << exponent << " mod " << phi_n;
        
        long long reduced_exponent = exponent % phi_n;
        cout << " = " << reduced_exponent << endl;
        cout << "    Cálculo: " << base << "^" << reduced_exponent << " mod " << mod << endl;
        
        long long resultado = mod_pow(base, reduced_exponent, mod);
        return resultado;
    } 
    else {
        cout << "  ✓ APLICANDO TEOREMA DA DIVISÃO EUCLIDIANA" << endl;
        cout << "    Condições:" << endl;
        cout << "    - Não é possível aplicar Fermat (mod não primo ou mdc ≠ 1)" << endl;
        cout << "    - Não é possível aplicar Euler (mdc ≠ 1)" << endl;
        cout << "    Fórmula: Cálculo direto sem redução de expoente" << endl;
        cout << "    Cálculo direto: " << base << "^" << exponent << " mod " << mod << endl;
        
        long long resultado = mod_pow(base, exponent, mod);
        return resultado;
    }
}

long long euclides_estendido(long long E, long long z) {
    cout << "\n  === ALGORITMO ESTENDIDO DE EUCLIDES ===" << endl;
    cout << "  Calculando inverso de " << E << " mod " << z << endl;
    
    if (mdc_silent(E, z) != 1) {
        cout << "  ERRO: " << E << " e " << z << " não são coprimos! MDC = " << mdc_silent(E, z) << endl;
        return -1;
    }
    
    long long t0 = 0, t1 = 1;
    long long r0 = z, r1 = E;
    int passo = 1;
    
    cout << "  Inicialização:" << endl;
    cout << "    r0 = " << r0 << ", r1 = " << r1 << endl;
    cout << "    t0 = " << t0 << ", t1 = " << t1 << endl;
    
    while (r1 != 0) {
        long long quo = r0 / r1;
        cout << "\n  Passo " << passo++ << ":" << endl;
        cout << "    q = " << r0 << " / " << r1 << " = " << quo << endl;
        
        long long temp_r = r0;
        r0 = r1;
        r1 = temp_r - quo * r1;
        cout << "    r0 = " << r0 << ", r1 = " << r1 << endl;
        
        long long temp_t = t0;
        t0 = t1;
        t1 = temp_t - quo * t1;
        cout << "    t0 = " << t0 << ", t1 = " << t1 << endl;
    }
    
    if (r0 != 1) {
        cout << "  ERRO: MDC não é 1, é " << r0 << endl;
        return -1;
    }
    
    long long d = t0 % z;
    if (d < 0) d += z;
    
    cout << "  Inverso encontrado: " << d << endl;
    cout << "  Verificação: " << E << " * " << d << " mod " << z << " = " << (E * d) % z << endl;
    
    return d;
}

// --- Função Pollard para fatoração ---
long long f(long long x, long long N) {
    return (x * x + 1) % N;
}

long long P(long long N, long long x0) {
    cout << "\n  === METODO ρ DE POLLARD ===" << endl;
    cout << "  Fatorando N = " << N << " com x0 = " << x0 << endl;
    
    if (x0 > 1000) {
        cout << "  Pollard falhou após muitas tentativas" << endl;
        return N;
    }
    
    long long l = x0, t = x0;
    if (primo(N)) {
        cout << "  " << N << " é primo" << endl;
        return N;
    }
    
    for (long long i = 0; i < 100; i++) {
        cout << "\n  Iteração " << (i+1) << ":" << endl;
        t = f(t, N);
        l = f(l, N);
        l = f(l, N);
        cout << "    t = f(t) = " << t << endl;
        cout << "    l = f(f(l)) = " << l << endl;
        
        long long diff = abs(l - t);
        cout << "    |l - t| = " << diff << endl;
        cout << "    Calculando mdc(" << diff << ", " << N << ")" << endl;
        
        long long d = mdc(diff, N);
        
        if (d != 1 && d != N) {
            cout << "  ✓ Fator não trivial encontrado: " << d << endl;
            if (primo(d)) {
                cout << "    " << d << " é primo" << endl;
                return d;
            } else {
                cout << "    " << d << " é composto, continuando fatoração..." << endl;
                return P(d, 2);
            }
        }
        
        if (t == l) {
            cout << "  Colisão detectada, tentando com x0 = " << (x0 + 1) << endl;
            return P(N, x0 + 1);
        }
    }
    
    cout << "  Pollard falhou, usando força bruta..." << endl;
    for (long long i = 2; i * i <= N; i++) {
        if (N % i == 0 && primo(i)) {
            cout << "  Fator encontrado (força bruta): " << i << endl;
            return i;
        }
    }
    
    return N;
}

// --- Função para converter mensagem para maiúsculas ---
string paraMaiusculas(const string& str) {
    string resultado = str;
    for (char& c : resultado) {
        c = toupper(c);
    }
    return resultado;
}

// --- Função para validar mensagem ---
bool mensagemValida(const string& mensagem) {
    for (char c : mensagem) {
        if (!isalpha(c) && c != ' ') {
            return false;
        }
    }
    return true;
}

// --- RSA Criptografia ---
string RSA(long long p, long long q, vector<long long> &blocos_crypto, const string& mensagem) {
    cout << "\n=== CONFIGURAÇÃO RSA ===" << endl;
    long long n = p * q;
    long long z = (p - 1) * (q - 1);
    
    cout << "p = " << p << ", q = " << q << endl;
    cout << "n = p * q = " << n << endl;
    cout << "z = (p-1)*(q-1) = " << z << endl;
    
    if (n <= 36) {
        cout << "AVISO: n = " << n << " é pequeno, pode haver problemas com blocos grandes." << endl;
    }
    
    cout << "\n=== BUSCANDO EXPOENTE e ===" << endl;
    long long e = 2;
    while (e < z && mdc_silent(e, z) != 1) {
        cout << "  e = " << e << " → mdc(" << e << "," << z << ") = " << mdc_silent(e, z) << " (não serve)" << endl;
        e++;
    }
    
    if (e >= z) {
        cout << "ERRO: Não foi possível encontrar e coprimo com z!" << endl;
        return "";
    }
    
    cout << "  e = " << e << " → mdc(" << e << "," << z << ") = 1 (✓ adequado)" << endl;
    
    long long d = euclides_estendido(e, z);
    
    if (d == -1) {
        cout << "ERRO: Não foi possível calcular d!" << endl;
        return "";
    }

    cout << "\n=== CHAVES GERADAS ===" << endl;
    cout << "Chave Pública: (n=" << n << ", e=" << e << ")" << endl;
    cout << "Chave Privada: (n=" << n << ", d=" << d << ")" << endl;

    map<char, string> numero = {
        {'A',"11"}, {'B',"12"}, {'C',"13"}, {'D',"14"}, {'E',"15"}, {'F',"16"},
        {'G',"17"}, {'H',"18"}, {'I',"19"}, {'J',"20"}, {'K',"21"}, {'L',"22"},
        {'M',"23"}, {'N',"24"}, {'O',"25"}, {'P',"26"}, {'Q',"27"}, {'R',"28"},
        {'S',"29"}, {'T',"30"}, {'U',"31"}, {'V',"32"}, {'W',"33"}, {'X',"34"},
        {'Y',"35"}, {'Z',"36"}, {' ',"00"}
    };

    cout << "\n=== PRÉ-CODIFICAÇÃO DA MENSAGEM ===" << endl;
    cout << "Mensagem original: " << mensagem << endl;
    
    string mensagem_precodificada = "";
    for (char c : mensagem) {
        string codigo = numero[c];
        cout << "  '" << c << "' → " << codigo << endl;
        mensagem_precodificada += codigo;
    }

    cout << "Mensagem pré-codificada: " << mensagem_precodificada << endl;

    vector<long long> blocos;
    cout << "\n=== DIVISÃO EM BLOCOS ===" << endl;
    for (size_t i = 0; i < mensagem_precodificada.size(); i += 2) {
        string par = mensagem_precodificada.substr(i, 2);
        long long bloco = stoll(par);
        blocos.push_back(bloco);
        cout << "  Bloco " << (i/2) << ": " << par << " → " << bloco << endl;
    }

    cout << "\n=== VERIFICAÇÃO DOS BLOCOS ===" << endl;
    for (size_t i = 0; i < blocos.size(); i++) {
        long long M = blocos[i];
        cout << "  Bloco " << i << ": M = " << M;
        if (M >= n) {
            cout << " → ERRO: M >= n (" << n << ")!" << endl;
            cout << "A criptografia não pode continuar. Use números maiores." << endl;
            return "";
        } else {
            cout << " → OK (M < n)" << endl;
        }
    }

    string crypto = "";
    int largura = to_string(n).length();
    
    cout << "\n=== PROCESSO DE CRIPTOGRAFIA ===" << endl;
    for (size_t i = 0; i < blocos.size(); i++) {
        long long M = blocos[i];
        cout << "\n--- Criptografando Bloco " << i << " ---" << endl;
        cout << "M = " << M << ", e = " << e << ", n = " << n << endl;
        cout << "C = M^e mod n = " << M << "^" << e << " mod " << n << endl;
        
        long long C = expo_modular_automatico(M, e, n);
        blocos_crypto.push_back(C);
        
        string C_str = to_string(C);
        while (C_str.length() < largura) {
            C_str = "0" + C_str;
        }
        crypto += C_str;
        
        cout << "✓ Bloco " << i << " criptografado: " << C << " (formatado: " << C_str << ")" << endl;
    }

    return crypto;
}

// --- RSA Descriptografia ---
string decrypto(long long p, long long q, vector<long long> &blocos_crypto) {
    long long n = p * q;
    long long z = (p - 1) * (q - 1);
    
    cout << "\n=== RECUPERANDO CHAVES PARA DESCRIPTOGRAFIA ===" << endl;
    long long e = 2;
    while (e < z && mdc_silent(e, z) != 1) e++;
    
    if (e >= z) {
        cout << "ERRO: Não foi possível encontrar e!" << endl;
        return "";
    }
    
    long long d = euclides_estendido(e, z);
    
    if (d == -1) {
        cout << "ERRO: Não foi possível calcular d!" << endl;
        return "";
    }

    map<string, char> letra = {
        {"11",'A'}, {"12",'B'}, {"13",'C'}, {"14",'D'}, {"15",'E'}, {"16",'F'},
        {"17",'G'}, {"18",'H'}, {"19",'I'}, {"20",'J'}, {"21",'K'}, {"22",'L'},
        {"23",'M'}, {"24",'N'}, {"25",'O'}, {"26",'P'}, {"27",'Q'}, {"28",'R'},
        {"29",'S'}, {"30",'T'}, {"31",'U'}, {"32",'V'}, {"33",'W'}, {"34",'X'},
        {"35",'Y'}, {"36",'Z'}, {"00",' '}
    };

    string msg = "";
    
    cout << "\n=== PROCESSO DE DESCRIPTOGRAFIA ===" << endl;
    for (size_t i = 0; i < blocos_crypto.size(); i++) {
        long long C = blocos_crypto[i];
        cout << "\n--- Descriptografando Bloco " << i << " ---" << endl;
        cout << "C = " << C << ", d = " << d << ", n = " << n << endl;
        cout << "M = C^d mod n = " << C << "^" << d << " mod " << n << endl;
        
        long long M = expo_modular_automatico(C, d, n);
        string bloco = to_string(M);
        if (bloco.size() == 1) bloco = "0" + bloco;
        
        char caractere = '?';
        if (letra.count(bloco)) {
            caractere = letra[bloco];
        }
        msg += caractere;
        
        cout << "✓ Bloco " << i << " descriptografado: " << M << " → '" << caractere << "'" << endl;
    }

    cout << "\n=== RECONVERSÃO NUMÉRICA PARA TEXTO ===" << endl;
    cout << "Mensagem numérica reconstruída: ";
    for (size_t i = 0; i < blocos_crypto.size(); i++) {
        long long M = expo_modular_automatico(blocos_crypto[i], d, n);
        string bloco = to_string(M);
        if (bloco.size() == 1) bloco = "0" + bloco;
        cout << bloco << " ";
    }
    cout << endl;

    return msg;
}

// --- MAIN ---
int main() {
    cout << "=== SISTEMA RSA COM PASSO A PASSO DETALHADO ===" << endl;
    cout << "Integrantes: Daniel Fernandes Silva - 222008459" << endl << endl;
    
    long long x, y;
    cout << "Digite dois números compostos (sugestão: 143 187): ";
    cin >> x >> y;

    if (x < 2 || y < 2) {
        cout << "ERRO: Números devem ser maiores que 1!" << endl;
        return 1;
    }

    cout << "\n=== ETAPA 1: FATORAÇÃO DOS NÚMEROS ===" << endl;
    
    cout << "\n--- Fatorando primeiro número: " << x << " ---" << endl;
    long long p = P(x, 2);
    
    cout << "\n--- Fatorando segundo número: " << y << " ---" << endl;
    long long q = P(y, 2);

    cout << "\n=== RESULTADO DA FATORAÇÃO ===" << endl;
    cout << "p: " << p << " (primo: " << (primo(p) ? "sim" : "não") << ")" << endl;
    cout << "q: " << q << " (primo: " << (primo(q) ? "sim" : "não") << ")" << endl;

    if (p != q && primo(p) && primo(q)) {
        vector<long long> blocos_crypto;
        
        cout << "\n=== ETAPA 2: CRIPTOGRAFIA RSA ===" << endl;
        cout << "Digite uma mensagem (apenas letras e espaços): ";
        cin.ignore();
        string mensagem;
        getline(cin, mensagem);
        
        mensagem = paraMaiusculas(mensagem);
        if (!mensagemValida(mensagem)) {
            cout << "ERRO: Mensagem contém caracteres inválidos!" << endl;
            return 1;
        }
        
        string texto_cripto = RSA(p, q, blocos_crypto, mensagem);
        
        if (!texto_cripto.empty()) {
            cout << "\n=== TEXTO CRIPTOGRAFADO FINAL ===" << endl;
            cout << texto_cripto << endl;

            cout << "\n=== ETAPA 3: DESCRIPTOGRAFIA RSA ===" << endl;
            string texto_decripto = decrypto(p, q, blocos_crypto);
            
            if (!texto_decripto.empty()) {
                cout << "\n=== RESULTADO FINAL ===" << endl;
                cout << "Mensagem original:  " << mensagem << endl;
                cout << "Mensagem decifrada: " << texto_decripto << endl;
                cout << "Mensagem criptografada: " << texto_cripto << endl;
                if (mensagem == texto_decripto) {
                    cout << "\n  SUCESSO " << endl;
                } else {
                    cout << "\n FALHA" << endl;
                }
            }
        }
    } else {
        cout << "ERRO: p e q devem ser primos diferentes!" << endl;
        if (p == q) cout << "  - p e q são iguais" << endl;
        if (!primo(p)) cout << "  - p não é primo" << endl;
        if (!primo(q)) cout << "  - q não é primo" << endl;
    }

    return 0;
}