#define MAX 1000
int Pilha[MAX];
char PilhaString [MAX];
int tam = 0;
int a,b;
void push(int valor) {
	Pilha[tam++] = valor;
}
int pop() {
	return Pilha[--tam];
}
int topo() {
    return Pilha[tam-1];
}

void pushString(char String) {
    PilhaString[tam++] = String;
}

