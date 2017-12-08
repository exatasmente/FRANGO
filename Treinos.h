typedef struct equipamento{    
    char *nomeEquipamento[50];
    int series;
    int repeticoes;
    int grupo;
}Equipamento;
typedef struct exercicio{
    char *grupamento[30];
    Equipamento *equipamentos[3];

}Exercicio;

typedef struct treino{
    Exercicio *exercicios[5];

}Treino;


Treino *novoTreino(){
    Treino *novo;
    novo = (Treino*) malloc(sizeof(Treino));
    return novo;
}
