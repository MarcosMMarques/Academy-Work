#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//To-Do: ToUpper initial letter of name, implenting quicksort, orderning on register function and unit tests.

typedef struct{
char name[60];
char cpf[12];
char BirthDate[11];  // formato dd/mm/aaaa
float BaseSalary;
float TotalSold ;
}Seller;

Seller * NewRegistrations(Seller *array, int *currently_seller_quantity, int quantity_reg){
    if(*currently_seller_quantity == 0){
        array = (Seller *) malloc((*currently_seller_quantity + quantity_reg) * sizeof(Seller));
    }else{
        array = (Seller *) realloc(array,(*currently_seller_quantity + quantity_reg) * sizeof(Seller));
    }

    for(int i = *currently_seller_quantity; i < quantity_reg + *currently_seller_quantity; i++){
        printf("Cadastro do Usuario : %d\n",i+1);
        fflush(stdin);

        printf("Nome:\n");
        scanf("%s",array[i].name);
        fflush(stdin);

        printf("CPF:\n");
        scanf("%s",array[i].cpf);
        fflush(stdin);

        printf("Data de nascimento:\n");
        scanf("%s",array[i].BirthDate);
        fflush(stdin);

        printf("SalarioBase:\n");
        scanf("%f", &array[i].BaseSalary);

        printf("Total Vendido:\n");
        scanf("%f", &array[i].TotalSold);
    }

    return array;
}

void ShowSellers(Seller *array, int *currently_seller_quantity){
    for(int i = 0; i < *currently_seller_quantity; i++){
        printf("\nCliente %d\n",i+1);
        printf("Nome: %s\n", array[i].name);
        printf("CPF: ");
        int x=0;
        while(array[i].cpf[x] != '\0'){
            printf("%c", array[i].cpf[x]);
            x++;
            if(x%3==0 && x != 9){
                printf(".");
            }else if(x == 9){
                printf("-");
            } 
        }
        printf("\nData de nascimento: %s\n",array[i].BirthDate);
        printf("Salario Base: R$%.2f\n",array[i].BaseSalary);
        printf("Total Vendido: R$%.2f\n", array[i].TotalSold);
    }
}

void ComissionCalc(Seller *array, int *currently_seller_quantity){
    for(int i = 0; i < *currently_seller_quantity; i++){
        printf("\n%s: R$%.2f\n", array[i].name, array[i].TotalSold * 3/100);
    }
}

void Order(Seller *array, int *currently_seller_quantity){
    for(int i = 0; i < *currently_seller_quantity - 1 ; i++){
        for(int j = i+1; j < *currently_seller_quantity; j++){
            if(strcmp(array[i].name, array[j].name) > 0){
                Seller * aux;
                *aux = array[i];
                array[i] = array[j];
                array[j] = *aux;
            }
        }
    }
}

//void SearchSeller(Seller *array, int *currently_seller_quantity, char name[60]){

//}

int main(){
    int loop=1, option, quantity_v=0,aux;
    Seller *array;
    while(loop){
        printf("*******************************************\n");
        printf("O que deseja fazer? Digite a opção Desejada:\n");
        printf("Cadastrar Novos Vendedores (1)\n");
        printf("Mostrar os dados de todos os Vendedores Cadastrados (2)\n");
        printf("Calcular comissões (3)\n");
        printf("Mostrar dados de um vendedor específico (4)\n");
        printf("Sair do Programa (0)\n");
        printf("*******************************************\n");
        scanf("%d",&option);
        switch(option){
            case 0:
                free(array);
                loop=0;
                break;
            
            case 1:
                printf("Digite quantos vendedores quer cadastrar:\n");
                scanf("%d",&aux);
                array = NewRegistrations(array,&quantity_v,aux);
                quantity_v+= aux;
                printf("\n");
                break;
            
            case 2:
                ShowSellers(array, &quantity_v);
                break;
            
            case 3:
                ComissionCalc(array, &quantity_v);
                break;
            
            case 4:
                char name[60];
                //printf("Digite o nome do vendedor:\n");
                //scanf("%s", name);
                Order(array, &quantity_v);
                //SearchSeller(array, &quantity_v, name);
        }
    }
}