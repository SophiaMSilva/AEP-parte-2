#include <stdio.h>
//#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//funçao criptografia
void cripto(char *senha){
	int tam=strlen(senha);
	
	for (int i=0; i<tam; i++){
		if (isalpha(senha[i])){       //se for caractere alpha numerico
			if (isupper(senha[i])){  //se for maiuscula
				senha[i]='Z'-(senha[i]-'A');
			} else {               //se for minuscula
				senha[i]='z'-(senha[i]-'a');
			}
		} else if (isdigit(senha[i])){ //se for numero
			senha[i]='9'-(senha[i]-'0');
		}
	}
}

//funcao ler usuarios
int lerUser(char nomes[50][50], char senhas[50][50]){ //tem que ser bidimensional, senao da erro
	FILE *arquivo=fopen("usuarios.txt","r");
	if(arquivo == NULL){
		printf("Erro ao abrir o arquivo.\n");
		return 0;
	}
	int cont=0;
	while (fscanf(arquivo, "%s %s\n", nomes[cont], senhas[cont]) != EOF){
		cont++; //contador de usuarios
	}
	fclose(arquivo);
	return cont; //retornando valor total de usuarios cadastrados
}

//funcao para salvar usuario
void saveUser(char nomes[50][50], char senhas[50][50], int cont){
	FILE *arquivo=fopen("usuarios.txt","w");
	if(arquivo == NULL){
		printf("Erro ao abrir o arquivo.\n");
		return;
	}
	for(int i=0; i<cont; i++){
		fprintf(arquivo, "%s %s\n", nomes[i], senhas[i]);
	}
	fclose(arquivo);
}

//funcao adicionar usuarios
void addUser(){
	FILE *arquivo=fopen("usuarios.txt","a");
	if(arquivo == NULL){
		printf("Erro ao abrir o arquivo.\n");
		return;
	}
	
	printf("\n");
	char usuario[50], senha[50];
	printf("Digite o nome do usuario: ");
	scanf("%s", usuario);
	printf("Digite a senha: ");
	scanf("%s", senha);
	
	cripto(senha); // funcao criptografia
	fprintf(arquivo, "%s %s\n", usuario, senha); //escreva usuario e senha no .txt
	fclose(arquivo);
	printf("\nUsuario adicionado!\n");
}

//funcao alterar senha do usuario
void altUser(){
	char nomes[50][50], senhas[50][50];
	int cont=lerUser(nomes, senhas); //chamando a funcao lerUser para determinar a quantidade de usuarios no txt
	char usuario[50], senha[50];
	
	printf("\n");
	printf("Digite o usuario que deseja alterar a senha: ");
	scanf("%s",usuario);
	
	int add=0;
	for(int i=0; i<cont; i++){
		if(strcmp(nomes[i], usuario)==0){ //comparando nome digitado com adicionado anteriormente
			add++;
			printf("\nDigite a nova senha: ");
			scanf("%s",senha);;
			cripto(senha); //funcao criptografia
			strcpy(senhas[i], senha); //substituindo senhas
			break; //parar de contar "i"
		}
	}
	if(add){
		saveUser(nomes, senhas, cont);
		printf("\nSenha alterada com sucesso!\n");
	} else {
		printf("\nUsuario nao encontrado.\n");
	}
}

//funcao excluir usuario
void delUser(){
	char nomes[50][50], senhas[50][50];
	int cont=lerUser(nomes, senhas); //chamando a funcao lerUser para determinar a quantidade de usuarios no txt
	char usuario[50],senha[50];
	
	printf("\n");
	printf("Digite o nome do usuario que deseja excluir: ");
	scanf("%s",usuario);
	printf("Digite a senha do usuario que deseja excluir: ");
	scanf("%s",senha);
	cripto(senha);
	
	int add=0;
	for(int i=0; i<cont; i++){
		if(strcmp(nomes[i], usuario)==0 && strcmp(senhas[i], senha)==0){ //comparando nome e senha digitado com o adicionado anteriormente
			add++;
			for(int x=i; x<cont-1;x++){ //contador para substituir usuarios da linha vizinha, evitando espaï¿½os em branco
				strcpy(nomes[x], nomes[x+1]);
				strcpy(senhas[x], senhas[x+1]);
			}
			cont--; //diminuindo total de usuarios
			break;
		}
	}
	if(add){
		saveUser(nomes, senhas, cont); //chamando funcao void de salvar usuario
		printf("\n");
		printf("\nUsuario excluido com sucesso!\n");
	} else {
		printf("\nUsuario/senha incorretos ou nao encontrados!\n");
	}
}

//funcao listar usuarios
void listUser(){
	char nomes[50][50], senhas[50][50];
	int cont=lerUser(nomes, senhas); //chamando a funcao lerUser para determinar a quantidade de usuarios no txt
	
	printf("\n");
	printf("Usuarios cadastrados: %d\n",cont);
	
	if(cont>0){
		printf("\nLista de usuarios:\n");
		for(int i=0; i<cont; i++){
		//cripto(senhas[i]);
		printf("Usuario: %s\n", nomes[i]);
		}
	}
}

//funcao login
int loginStatus=0;
int login(){
	char nomes[50][50], senhas [50][50]; //tem que ser bidimencional, senao da erro
	int cont=lerUser(nomes, senhas);
	char usuario[50], senha[50];
	
	printf("\n");
	printf("Digite o nome de usuario: ");
	scanf("%s",usuario);
	printf("Digite a senha: ");
	scanf("%s",senha);
	
	cripto(senha); //funciona nos dois sentidos, chamar uma primeira vez para criptografar e uma segunda para reverter
	
	for(int i=0; i<cont; i++){
		if(strcmp(nomes[i], usuario)==0 && strcmp(senhas[i], senha)==0){ //comparando senha e user
			loginStatus=1;
			printf("\n");
			printf("\nLogin realizado com sucesso!\n");
			return 1;
		}
	}
	printf("\n");
	printf("\nUsuario ou senha incorretos!\n");
	return 0;
}

int main(){
	int op;
	
	do{
		printf("\nBem vindo!\n");
		
		if(loginStatus==0){
			printf("1. Login\n");
			printf("2. Cadastrar usuario\n");
			printf("0. Sair\n");
			printf("\nEscolha uma opcao: ");
			scanf("%d", &op);
			
			switch(op){
        	case 1:
        		login();
        		break;
        	case 2:
        		addUser();
        		break;
        	case 0:
        		printf("Saindo.\n");
        		break;
        	default:
        		printf("Opcao invalida!\n");
        	}
		} else {
			printf("1. Adicionar usuario\n");
        	printf("2. Alterar senha do usuario\n");
        	printf("3. Excluir usuario\n");
        	printf("4. Listar usuarios\n");
        	printf("0. Sair\n");
        	printf("\nEscolha uma opcao: ");
        	scanf("%d", &op);
        	
        	switch(op){
			case 1:
        		addUser();
        		break;
        	case 2:
        		altUser();
        		break;
        	case 3:
        		delUser();
        		break;
        	case 4:
        		listUser();
        		break;
        	case 0:
        		printf("Saindo.\n");
        		break;
        	default:
        		printf("Opcao invalida!\n");
			}
		}
	} while(op!=0);
	
	return 0;
}










