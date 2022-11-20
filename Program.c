#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
#include<stdlib.h>
//To-Do: Unit tests.

typedef struct{
char name[60];
char cpf[12];
char BirthDate[11];  // formato dd/mm/aaaa
float BaseSalary;
float TotalSold ;
}Seller;

Seller * NewRegistrations(Seller *array, int *currently_seller_quantity, int quantity_reg){
    system("clear");
    if(*currently_seller_quantity == 0){
        array = (Seller *) malloc(quantity_reg * sizeof(Seller));
    }else{
        array = (Seller *) realloc(array,(*currently_seller_quantity + quantity_reg) * sizeof(Seller));
    }

    for(int i = *currently_seller_quantity; i < quantity_reg + *currently_seller_quantity; i++){
        printf("Cadastro do Usuario : %d\n",i+1);
        printf("Nome: ");
        scanf("%[^\n]%*c",array[i].name);
        int x = 0;
        while(array[i].name[x] != '\0'){
            if(x == 0){
                array[i].name[x] = toupper(array[i].name[x]);
            }
            if(array[i].name[x] == ' '){
                array[i].name[x+1] = toupper(array[i].name[x+1]);
            }
            x++;
        }

        printf("CPF: ");                
        scanf("%[^\n]%*c",array[i].cpf);


        printf("Data de nascimento: ");
        scanf("%[^\n]",array[i].BirthDate);


        printf("SalarioBase: ");
        scanf("%f", &array[i].BaseSalary);

        printf("Total Vendido: ");
        scanf("%f%*c", &array[i].TotalSold);
        printf("\n\n");
    }
    return array;
}

void ShowSellers(Seller *array, int *currently_seller_quantity){
    system("clear"); 
    for(int i = 0; i < *currently_seller_quantity; i++){
        printf("Cliente %d\n",i+1);
        printf("Nome: %s", array[i].name);
        printf("\nCPF: ");
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
        printf("Total Vendido: R$%.2f\n\n", array[i].TotalSold);
    }
}

void ComissionCalc(Seller *array, int *currently_seller_quantity){
    system("clear");
    for(int i = 0; i < *currently_seller_quantity; i++){
        printf("\n%s: R$%.2f\n", array[i].name, array[i].TotalSold * 3/100);
    }
}

void Order(Seller *array, int *currently_seller_quantity){
    for(int i = 0; i < *currently_seller_quantity - 1 ; i++){
        for(int j = i+1; j < *currently_seller_quantity; j++){
            if(strcmp(array[i].name, array[j].name) > 0){
                Seller aux;

                strcpy(aux.name, array[i].name);
                strcpy(aux.cpf, array[i].cpf);
                strcpy(aux.BirthDate, array[i].BirthDate);
                aux.BaseSalary = array[i].BaseSalary;
                aux.TotalSold = array[i].TotalSold;
                
                strcpy(array[i].name, array[j].name);
                strcpy(array[i].cpf, array[j].cpf);
                strcpy(array[i].BirthDate, array[j].BirthDate);
                array[i].BaseSalary = array[j].BaseSalary;
                array[i].TotalSold = array[j].TotalSold;

                strcpy(array[j].name, aux.name);
                strcpy(array[j].cpf, aux.cpf);
                strcpy(array[j].BirthDate, aux.BirthDate);
                array[j].BaseSalary = aux.BaseSalary;
                array[j].TotalSold = aux.TotalSold;    
            }
        }
    }
}

int SearchSeller(Seller *array, int start, int final, char name[60]){
    int middle;
    char selected_name[60];
    if(start > final){
        return -1;
    }else{
        middle = (start + final)/2;
        strcpy(selected_name, array[middle].name);

        if(strcmp(name, selected_name) == 0){
            return middle;
        }else if(strcmp(name, selected_name) > 0){
            SearchSeller(array, middle+1, final, name);
        }else{
            SearchSeller(array, start, middle-1, name);
        }
    }
}

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
        scanf("%d%*c",&option);
        switch(option){
            case 0:
                free(array);
                loop=0;
                break;
            
            case 1:
                printf("Digite quantos vendedores quer cadastrar:\n");
                scanf("%d%*c",&aux);
                array = NewRegistrations(array,&quantity_v,aux);
                quantity_v+= aux;
                Order(array, &quantity_v);
                break;
            
            case 2:
                ShowSellers(array, &quantity_v);
                printf("\n\n");
                break;
            
            case 3:
                ComissionCalc(array, &quantity_v);
                printf("\n\n");
                break;
            
            case 4:
                char name[60];
                int position;
                printf("Digite o nome do vendedor:\n");
                scanf("%[^\n]", name);
                int aux=0;
                while(name[aux] != '\0'){
                    if(aux == 0){
                        name[aux] = toupper(name[aux]);
                    }
                    if(name[aux] == ' '){
                        name[aux+1] = toupper(name[aux+1]);
                    }
                        aux++;
                }
                position = SearchSeller(array, 0, quantity_v, name);
                system("clear");
                if(position == -1){
                    printf("!!!!!!!!!!!!!!!!!!!!!!!!!\n");
                    printf("!Vendedor não encontrado!\n");
                    printf("!!!!!!!!!!!!!!!!!!!!!!!!!\n\n");
                }else{
                    printf("Cliente %d\n",position+1);
                    printf("Nome: %s\n", array[position].name);
                    printf("CPF: ");
                    int x=0;
                    while(array[position].cpf[x] != '\0'){
                        printf("%c", array[position].cpf[x]);
                        x++;
                        if(x%3==0 && x != 9){
                            printf(".");
                        }else if(x == 9){
                            printf("-");
                        } 
                    }
                    printf("\nData de nascimento: %s\n",array[position].BirthDate);
                    printf("Salario Base: R$%.2f\n",array[position].BaseSalary);
                    printf("Total Vendido: R$%.2f\n\n", array[position].TotalSold);    
                }
        }
    }
}
