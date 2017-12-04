
typedef struct funcionario{
    char *nome;
    int id;
    int senha;
    int cargo;
}Funcionario;

typedef struct sistema{
    Funcionario *listaFincionarios[3];
    Pessoa *listaPessoas[500];
    Equipamento *listaEquipamentos[40];
    int qtP;

}Sistema;

Sistema *sistema;

Sistema *novoSistema();
Funcionario *novoFuncionario(char *nome, int id, int senha ,int cargo);
int buscarPessoa(Sistema *sistema, int matricula);
Pessoa *buscarPessoaNome(Sistema *sistema, char *nome);
int cadastrarPessoa(Sistema *sistema,Pessoa *pessoa);
Treino *geraTreino(Medidas *medidas,int sexo);

Funcionario *novoFuncionario(char *nome, int id, int senha ,int cargo){
    Funcionario *novo;
    novo = (Funcionario*) malloc(sizeof(Funcionario));
    novo->nome = nome;
    novo->id = id;
    novo->senha = senha;
    novo->cargo = cargo;

    return novo;
}

Sistema *novoSistema(){
    Sistema *novo;
    novo = (Sistema*) malloc(sizeof(Sistema));
    novo->qtP = 0;
    
    return novo;
}

void inicializaSistema(Sistema *sistema){
    

}

int cadastrarPessoa(Sistema *sistema,Pessoa *pessoa){
    if(sistema->qtP < 500){
        pessoa->matricula = sistema->qtP;
        sistema->listaPessoas[sistema->qtP] = pessoa;
        sistema->qtP++;
        return 1;
    }else{
        return 0;
    }
}

void removerPessoa(Sistema *sistema,int matricula){
    int posicao = buscarPessoa(sistema,matricula);
    if(posicao != -1){
        if(posicao < sistema->qtP-1)
        for(int i = posicao; i < sistema->qtP-1 ; i++){
            sistema->listaPessoas[i] = sistema->listaPessoas[i+1];
        }else{
            free(sistema->listaPessoas[posicao]);
        }
    }
}

int buscarPessoa(Sistema *sistema, int matricula){
    for(int i = 0 ; i < sistema->qtP ; i++){
        if(sistema->listaPessoas[i]->matricula == matricula){
            return i;
        }
    }
    return -1;
}
Pessoa *buscarPessoaNome(Sistema *sistema, char *nome){
    for(int i = 0 ; i < sistema->qtP ; i++){
        if(strcmp(sistema->listaPessoas[i]->nome,nome)== 0){
            return sistema->listaPessoas[i];
        }
    }
    return NULL;
}

void atualizaCadastro(Sistema *sistema,Pessoa *pessoa){
    sistema->listaPessoas[pessoa->matricula] = pessoa;
}
Treino *geraTreino(Medidas *medidas,int sexo){
    return NULL;
}