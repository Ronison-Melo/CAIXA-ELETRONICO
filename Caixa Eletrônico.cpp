#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#define true 1
#define false 0

typedef struct nodo{
	char nome[60], cpf[15];
	int idade,senha,conta;
	float valor_conta;
	struct nodo *prox;
	
}no;
//--------------------------------------//
//Função que cria o novo nó.
no* criaNo(){
	no *aux;
	aux=(no*)malloc(sizeof(no));
	aux->valor_conta=0.0;
	aux->conta=0;
	aux->senha=0;
	aux->prox=NULL;
	return aux;
}
void cabecario(){
	system("cls");
	printf("	----------SISTEMA BANCARIO----------\n\n");
}
void cab_operacoes(no *aux){
	cabecario();
	printf("CONTA: %d		%s\n",aux->conta,aux->nome);
	printf("SALDO EM CONTA: %.2f\n\n",aux->valor_conta);
	printf("(1) - SAQUE		(2) - DEPOSITO		(3) - MENU PRINCIPAL\n");
}
int veri_senha(int nsenha, no *raiz){//VERIFICA SE AS SENHAS SÃO IGUAIS
	no *aux=raiz;
	while(aux!=NULL){
		if(nsenha==aux->senha){
			return true;
		}
		aux=aux->prox;
}
return false;
}
//Insere o nó na lista
void insereNo(no **raiz,no *aux,int *qtd){
	no *novoNo; int senha_aux,verifica;
	novoNo=criaNo();//chama a função que criará o novo nó.
	
	cabecario();//funcao que mostra o titulo do programa em cada execucao.
	printf("	DIGITE O NOME DO CLIENTE: ");//Após o nó criado, inserir os dados.
	fflush(stdin);
	gets(novoNo->nome);
	printf("	CPF: ");
	gets(novoNo->cpf);
	printf("	IDADE: ");
	scanf("%d",&novoNo->idade);
	
	do{cabecario();
	printf("	Digite uma Senha (numeros inteiros): ");
	scanf("%d",&senha_aux);
	verifica=veri_senha(senha_aux,aux);//verifica se a senha digitada ja existe.
	if(verifica==true){
	cabecario();
	printf("SENHA JA EXISTE.  TENTE NOVAMENTE.\n\n");system("PAUSE");
}
}while(verifica==true);//Enquanto houver senha igual o laço repete.
	novoNo->senha=senha_aux;
	
	printf("	DEPOSITAR VALOR EM CONTA: ");
	scanf("%f",&novoNo->valor_conta);
	novoNo->conta=*qtd+=1;
	if(*(raiz)==NULL){//Se ainda não há elementos em minha lista, então a raiz recebe o novo no.
		*(raiz)=novoNo;
	}else{
		novoNo->prox=*(raiz);//Se ja existe elementos, então o novo no é inserido no inicio da lista.
		*(raiz)=novoNo;
	}
	
}
//-----------------------------------//
void imprime(no *raiz){
	cabecario();
		printf("Conta: %d	Senha: %d\n",raiz->conta,raiz->senha);
		printf("NOME: %s\n",raiz->nome);
		printf("CPF: %s\n",raiz->cpf);
		printf("IDADE: %d\n",raiz->idade);
		printf("VALOR EM CONTA: R$ %.2f\n\n",raiz->valor_conta);
		system("pause");
}
no *buscaNo(no *aux,int conta, int senha){
	while(aux!=NULL){
		if(conta==aux->conta && senha==aux->senha){
			return aux;
		}
		aux=aux->prox;
	}
	return NULL;
}
void operacao(no **raiz){
	int conta,senha,op,valor=0;
	no *aux;
	cabecario();
	printf("Numero da Conta: ");
	scanf("%d",&conta);
	printf("Senha: ");
	scanf("%d",&senha);
	
	aux=buscaNo(*raiz,conta,senha);
	if(aux!=NULL){
		do{
		cab_operacoes(aux);
		scanf("%d",&op);
		switch(op){
			case 1: printf("\n\nDigite o valor: ");
						scanf("%d",&valor);
						aux->valor_conta-=valor;//subtrai do valor em conta.
						cabecario();
						printf("SAQUE REALIZADO!\n\n	Valor em conta: %.2f\n\n",aux->valor_conta);system("pause");break;
				case 2:printf("\n\nDigite o valor: ");
						scanf("%d",&valor);
							aux->valor_conta+=valor;//soma ao valor em conta.
							cabecario();
							printf("DEPOSITO REALIZADO!\n\n	Valor em conta: %.2f\n\n",aux->valor_conta);system("pause");break;
					case 3: break;
					default: cabecario(); printf("OPCAO INVALIDA!\n\n");system("pause");
		}
	}while(op!=3);
	}else{cabecario();
		printf("	DADOS INVALIDOS!\n\n");system("pause");
	}	
	
	
}
void dados_cliente(no *raiz){
	char cpf[15];
	cabecario();
		printf("Digite o CPF: ");
		fflush(stdin);//limpa a memória para evitar problemas entre tipos de dados.
		gets(cpf);
		while(raiz!=NULL){
			if(strcmp(cpf,raiz->cpf)==0){//compara se as duas strings são iguais.
				imprime(raiz);
				return ;//sai após exibir os dados
			}
			raiz=raiz->prox;
		}
		cabecario();
		printf("CPF IVALIDO!\n\n");
		system("pause");
}
int main(){
	int op,qtd_cliente=1000;
	no *raiz=NULL;
	do{
		cabecario();
		printf("Escolha:\n	(1) - Cadastrar Cliente\n	(2) - Operacoes Bancarias\n	(3) - Exibir dados do Cliente\n	(4) - Sair\n");
		scanf("%d",&op);
		switch(op){
			case 1: insereNo(&raiz,raiz,&qtd_cliente);system("cls"); 
			imprime(raiz);break;/*como a insercao do novo elemento ocorre no inicio da lista entao, imprime sempre
												sempre exibirá o primeiro elemento, não é necessário realiza operação nenhuma para exibir o elemto recém criado*/
			case 2: operacao(&raiz);break;
			case 3: dados_cliente(raiz);//busca e exibe os dados do cliente.
			case 4: system("cls");printf("	Fim do Programa!\n");break;
			default: cabecario();printf("OPCAO IVALIDA!  TENTE NOVAMENTE!\n\n");system("pause");
		}
		
	}while(op!=4);
}


