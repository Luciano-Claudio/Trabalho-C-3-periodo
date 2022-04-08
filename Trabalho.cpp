#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define	MAX 60

typedef struct data {
	char disciplina[50];
	int nota;
} t_dados;

typedef struct no{
	t_dados dado; 
	struct no * prox;
} t_no;

typedef struct a {
	char RGM[50];
	t_no * dadosLista;
} Aluno;

typedef struct l {
	Aluno alunos[MAX];
	int	ultimo_aluno;
} Lista;

typedef t_no * t_lista;  



//Funções para lista sequencial
Lista	criarSequencial() {
	Lista listaAluno;
	listaAluno.ultimo_aluno = -1;
	
	return listaAluno;
}


int	isCheia (Lista * l) {
	return (l->ultimo_aluno == (MAX -1));
}

int	getTamanhoSequencial (Lista * l) {
	return (l->ultimo_aluno + 1);
}

int deslocaDireita(Lista * lista, int pos) {
    int i;

    for (i=lista->ultimo_aluno + 1; i>pos; i--)
        lista->alunos[i] = lista->alunos[i-1];

    return 1;
}
int deslocaEsquerda(Lista * lista, int pos) {
    int i;
    for (i=pos; i<lista->ultimo_aluno; i++){
        lista->alunos[i] = lista->alunos[i+1];
    }

    return 1;
}

int inserirSequencial (Lista * lista, Aluno aluno) {
	int pos = lista->ultimo_aluno+1;
	int i;
	
	for(i = 0; i < getTamanhoSequencial(lista); i++){
		if(strcmp(aluno.RGM, lista->alunos[i].RGM) == -1){
			pos = i;
			break;
		} 
	}
	
    if ( isCheia(lista) || (pos > lista->ultimo_aluno + 1) || (pos < 0) )
        return 0;

    deslocaDireita(lista, pos);
    lista->alunos[pos] = aluno;
    (lista->ultimo_aluno)++;
    return 1;
}



Aluno * getElementoSequencial (Lista * l, int pos) {
	if ((pos > l->ultimo_aluno) || (pos < 0))
		return NULL;
		
	return &(l->alunos[pos]);
}

int findAluno(Lista * l, char *RGM){
	int pos = -1;
	int i;
	for(i = 0; i < getTamanhoSequencial(l); i++){
		if(strcmp(RGM, l->alunos[i].RGM) == 0){
			pos = i;
			break;
		} 
	}		
	return pos;
}


int remover(Lista * lista, char *RGM){
	int pos = findAluno(lista, RGM);
	if(pos < 0){
		printf("Aluno não encontrado.");
		return -1;
	}
	printf("%d\n",pos);
	printf("%d\n",lista->ultimo_aluno);
	deslocaEsquerda(lista,pos);
	//lista->alunos[lista->ultimo_aluno] = NULL;
    (lista->ultimo_aluno)--;
}

//Funções para lista encadeadas
t_no * criaNo() {
    t_no * no = (t_no *) malloc(sizeof(t_no));

    if (no)
        no->prox = NULL;

    return no;
}

int isVazia(t_lista lista) {
    return (lista == NULL);
}

int getTamanhoEncadeada(t_lista lista) {
    int n = 0;
    while (lista != NULL) {
        lista = lista->prox;
        n++;
    }
    return n;
}

t_no * getNo(t_lista lista, int pos) {
    // Retorna 0 se posicao invalida. Do contrario, retorna o elemento
    int n = 0;

    if (pos<0)
        return 0; // erro: posicao invalida

    while (lista != NULL) {
        if (n==pos)
            return lista;
        lista = lista->prox;
        n++;
    }
    return 0; // erro: posicao invalida
}

t_dados * getElementoEncadeada(t_lista lista, int pos){
    t_no * no = getNo(lista, pos);
    if (no != NULL)
        return &(no->dado);
    else
        return NULL;
}

int inserirEncadeada(t_lista * lista, int pos, t_dados dado) {
    t_no * p, * novo;

    if (pos == 0) {
        novo = criaNo();
        if (novo == NULL)
            return 0; // erro: memoria insuficiente
        novo->dado = dado;
        novo->prox = *lista;
        *lista = novo;
        return 1;
    }
    
    p = getNo(*lista, pos-1);
    if (p == NULL)
         return 0; // erro: posicao invalida 
    novo = criaNo();
    if (novo == NULL)
        return 0; // erro: memoria insuficiente
    novo->dado = dado;
    novo->prox = p->prox;
    p->prox = novo;

    return 1;
}




// Mostrar
void mostrar(Lista * lista){
	int i,u;
	for(i=0;i<getTamanhoSequencial(lista);i++){
		printf("Aluno(RGM): %s, matriculado nas disciplinas:\n", getElementoSequencial(lista, i)->RGM);
		t_lista l = getElementoSequencial(lista,i)->dadosLista;
		for(u=0;u<getTamanhoEncadeada(l);u++){
			printf("Disciplina: %s - Nota = %d\n", getElementoEncadeada(l,u)->disciplina, getElementoEncadeada(l,u)->nota);
		}
	}
}

void mostrarProcura(Lista * lista, char * RGM){
	int pos = findAluno(lista, RGM);
	if(pos < 0){
		printf("Aluno não encontrado.\n");
		return;
	}
	Aluno * aluno = getElementoSequencial(lista, pos);
	t_lista l = aluno->dadosLista;
	printf("Aluno Encontrado!! RGM: %s, matriculado nas disciplinas:\n", aluno->RGM);
	int u;
	for(u=0;u<getTamanhoEncadeada(l);u++){
		printf("Disciplina: %s - Nota = %d\n", getElementoEncadeada(l,u)->disciplina, getElementoEncadeada(l,u)->nota);
	}
}


int main(){
	
  	setlocale(LC_ALL, "Portuguese");
  	
	int n;
	char rgm[50];
	char escolhaAluno, escolhaDados;
	
	Lista listaAluno = criarSequencial();
	
	Aluno aluno;
	t_dados d;
	
	
	do{
		printf("Digite o RGM do aluno que deseja inserir: ");
		scanf("%s", aluno.RGM);
		aluno.dadosLista = NULL;
		
		n = 0;
		do{
			printf("Digite o nome disciplina %d° do aluno %s: ", (n + 1), aluno.RGM);
			scanf("%s", d.disciplina);
			
			printf("Digite a nota da disciplina %s do aluno %s: ", d.disciplina, aluno.RGM);
			scanf("%d", &d.nota);
			
			inserirEncadeada(&aluno.dadosLista, n, d);
			
			
			
			fflush(stdin);
			n++;
			printf("Mais diciplina (s/n)? ");
			scanf("%c", &escolhaDados);
		}while(escolhaDados == 's');
		
		inserirSequencial(&listaAluno,aluno);
		
		
		fflush(stdin);
		printf("Deseja adicionar outro aluno (s/n)? ");
		scanf("%c", &escolhaAluno);
	}while(escolhaAluno == 's');
	
	mostrar(&listaAluno);
	
	
	
	printf("Digite o RGM do aluno que deseja encontrar: ");
	scanf("%s", rgm);
	
	mostrarProcura(&listaAluno,rgm);
	
	fflush(stdin);
	printf("Digite o RGM do aluno que deseja remover: ");
	scanf("%s", rgm);
	
	remover(&listaAluno,rgm);
	
	mostrar(&listaAluno);
}
