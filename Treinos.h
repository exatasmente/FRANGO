typedef struct equipamento{    
    char *nomeEquipamento;
    int series;
    int repeticoes;
    int carga;

}Equipamento;

typedef struct Exercicio{
    char *grupamento;
    Equipamento **equipamentos;
    int qtE;
}Exercicio;

typedef struct treino{
    Exercicio *exercicios[5];

}Treino;

Exercicio *novoExercicio(char *grupamento,Equipamento **equipamento){
    Exercicio *novo;
    novo = (Exercicio*) malloc(sizeof(Exercicio));

    novo->grupamento  = grupamento;
    novo->equipamentos = equipamento;
    novo->qtE = sizeof(equipamento)/sizeof(Equipamento*);

    return novo;
}

Treino *novoTreino(){
    Treino *novo;
    novo = (Treino*) malloc(sizeof(Treino));
    for(int i = 0 ; i < 5 ; i++){
        novo->exercicios[i] = (Exercicio*) malloc(sizeof(Exercicio));
    }
    return novo;
}

Equipamento *novoEquipamento(char *nome,int series, int repeticoes , int carga){
    Equipamento *novo;
    novo = (Equipamento*) malloc(sizeof(Equipamento));
    novo->nomeEquipamento = nome;
    novo->series = series;
    novo->repeticoes = repeticoes;
    novo->carga = carga;

    return novo;
}