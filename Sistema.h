typedef struct sistema{
    Pessoa *listaPessoas[500];
    Equipamento *listaEquipamentos[30];
    int qtP;

}Sistema;

Sistema *sistema;
FILE *arq;
FILE *arqT;

Sistema *novoSistema();
int buscarPessoa(Sistema *sistema, int matricula);
Pessoa *buscarPessoaNome(Sistema *sistema, char *nome);
void cadastrarPessoa(Sistema *sistema,Pessoa *pessoa);
void defineObjetivo(Sistema *sistema,Medidas *medidas,int sexo,char *ret);
void carregaArquivos(Sistema *sistema);
Treino *geraTreino(Sistema *sistema,char *objetivo);
void salvarTudo(Sistema *sistema);
void salvaArquivo();

Sistema *novoSistema(){
    /*
    Funçao responsavél por alocar dinâmicamente uma estrutura do tipo Sistema 
    após alocado o procedimento carregaArquivos é chamado mandando a estrutura alocada
    */
    Sistema *novo;
    novo = (Sistema*) malloc(sizeof(Sistema));
    novo->qtP = 0;
    carregaArquivos(novo);
    return novo;
}
Treino *geraTreino(Sistema *sistema,char *objetivo){
    //inicializa o rand
    srand(time(NULL));
    //instância e aloca um espaço de memória para a variavé abaixo
    Treino *treino = (Treino*)malloc(sizeof(Treino));
    // pega uma das posições do vetor de exercicios
    int pos = rand()%30 ;
    //laco de repetição para carregar os valores para cada dia da semana
    for(int i = 0 ; i < 5 ; i++){
        //aloca um espaço de memória para o exercicio do dia i
        treino->exercicios[i] = (Exercicio*)malloc(sizeof(Exercicio));
        // laco de repetição para carregar os quipamentos usados no dia i
        for(int j = 0 ; j < 3; j++){
            // verifica se a posição aleatória é do grupo de equipamentos do dia 
            while(sistema->listaEquipamentos[pos]->grupo != i){
                pos = rand()%30;
            }
            //aloca um espaço de memória para o equipamento j do dia i
            treino->exercicios[i]->equipamentos[j] = (Equipamento*)malloc(sizeof(Equipamento));
            // copia o nome do equipamento para a variavél alocada acima
            strcpy(treino->exercicios[i]->equipamentos[j]->nomeEquipamento,sistema->listaEquipamentos[pos]->nomeEquipamento);
            //pega outra posição aleatória do vetor de equipamentos
            pos = rand()%30;
        }
    }
    //abre o arquivo relacionado ao objetivo da pessoa 
    arqT = fopen(objetivo,"rb");
    //laco de repetição para carregar os valores das séries e repetições de cada equipamento para cada dia da semana
    for(int i=0; i <5; i++){
        for(int j = 0 ; j < 3 ; j++){                
            //le o arquivo e armazena os valores nas variavéis abaixo
            fscanf(arqT,"%d\t%d\n",&treino->exercicios[i]->equipamentos[j]->series,&treino->exercicios[i]->equipamentos[j]->repeticoes);
        }
    }
    //fecha o arquivo
    fclose(arqT);
    //retorna o treino gerado
    return treino;
}
void cadastrarPessoa(Sistema *sistema,Pessoa *pessoa){
    // verifica se existe espaço livre no vetor de pessoas do sistema
    if(sistema->qtP < 500){
        // caso exista a pessoa ira receber como nũmero de matricula a sua posição no vetor
        pessoa->matricula = sistema->qtP;
        //armazena a pessoa na ultima posição válida no vetor
        sistema->listaPessoas[sistema->qtP] = pessoa;
        // incremente a quanitidade de pessoas
        sistema->qtP++;
        // chamada do procedimento para salvar a pessoa adicionada ao arquivo
        salvaArquivo(pessoa);
    }
    
}
void salvarTudo(Sistema *sistema){
    // abre o arquivo de pessoas no modo escrita
    arq = fopen("pessoas.data","w");
    // percorre o vetor até a ultima posição válida
    for(int i = 0 ; i < sistema->qtP ; i++){
        // fprintf tem o objetivo de imprimir no arquivo, semalhante ao printf
        fprintf(arq,"%s|%s|%d\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\n",sistema->listaPessoas[i]->nome,
                        sistema->listaPessoas[i]->objetivo,
                        &sistema->listaPessoas[i]->sexo,
                        &sistema->listaPessoas[i]->imc,
                        &sistema->listaPessoas[i]->medidas->abdomen,
                        &sistema->listaPessoas[i]->medidas->altura,
                        &sistema->listaPessoas[i]->medidas->bracoDireito,
                        &sistema->listaPessoas[i]->medidas->bracoEsquerdo,
                        &sistema->listaPessoas[i]->medidas->cintura,
                        &sistema->listaPessoas[i]->medidas->panturrilhaDireita,
                        &sistema->listaPessoas[i]->medidas->panturrilhaEsquerda,
                        &sistema->listaPessoas[i]->medidas->peito,
                        &sistema->listaPessoas[i]->medidas->pernaDireita,
                        &sistema->listaPessoas[i]->medidas->peso);
        }
        // fecha o arquivo
        fclose(arq);
    
}
void salvaArquivo(Pessoa *pessoa){
    //abre o rquivo de pessoas no modo escrita no final do arquivo
    arq = fopen("pessoas.data","a+");
    //salva a pessoa na ultima linha do arquivo
    fprintf(arq,"%s|%s|%d\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\n",pessoa->nome,
                    pessoa->objetivo,
                    pessoa->sexo,
                    pessoa->imc,
                    pessoa->medidas->abdomen,
                    pessoa->medidas->altura,
                    pessoa->medidas->bracoDireito,
                    pessoa->medidas->bracoEsquerdo,
                    pessoa->medidas->cintura,
                    pessoa->medidas->panturrilhaDireita,
                    pessoa->medidas->panturrilhaEsquerda,
                    pessoa->medidas->peito,
                    pessoa->medidas->pernaDireita,
                    pessoa->medidas->pernaEsquerda,
                    pessoa->medidas->peso);
    // fecha o arquivo
    fclose(arq);
    
}
void removerPessoa(Sistema *sistema,int matricula){
    // busca a posição da pessoas no vetor
    int posicao = buscarPessoa(sistema,matricula);
    // caso a variavél posição seja diferente de -1 inidica que a posição retornada é válida
    if(posicao != -1){
        
        if(posicao < sistema->qtP-1){
            for(int i = posicao; i < sistema->qtP-1 ; i++){
                sistema->listaPessoas[i] = sistema->listaPessoas[i+1];
            }
            free(sistema->listaPessoas[sistema->qtP-1]);
          
        }else{
            free(sistema->listaPessoas[posicao]);
            
        }
        sistema->qtP--;
        salvarTudo(sistema);
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
void defineObjetivo(Sistema *sistema,Medidas *medidas,int sexo,char *ret){
    float imc = calculaImc(medidas->peso,medidas->altura);

    if(sexo){
        if(imc < 20.7){
            strcpy(ret,"abaixodopeso.obj");
        }else if(imc < 26.4){
            strcpy(ret,"manutencao.obj");
        }else if(imc  < 27.8){
            strcpy(ret,"manutencao.obj");
        }else if(imc < 31.1){
            strcpy(ret,"acimadopeso.obj");
        }else{
            strcpy(ret,"acimadopeso.obj");
        }
    }else{      
        if(imc < 19.1){
            strcpy(ret,"abaixodopeso.obj");
        }else if(imc < 25.8){
            strcpy(ret,"manutencao.obj");
        }else if(imc  < 27.3){
            strcpy(ret,"manutencao.obj");
        }else if(imc < 32.3){
            strcpy(ret,"acimadopeso.obj");
        }else{
            strcpy(ret,"acimadopeso.obj");
        }
    
    }
}
void carregaArquivos(Sistema *sistema){
    char *maquinas[] ={"puxada inversa","puxada frontal",
                        "extensora","leg45","agachamento livre","abdução","adução","flexora sentada","mesa flexora","HACK","panturrilha em pé","panturrilha sentada",
                        "biceps rosca direta","biceps com halteres halternado","biceps barrabanco","biceps biceps barra invertida",
                        "triceps testa","triceps banco","triceps corda","trisceps barra","triceps barra",
                        "desenvolvimento maquina","elevação frontal","elevação lateras","puxada baixa-ombro",
                        "supino reto","supino inclinado","supino declinado","peck deck","croos over"};

    int grupo[6] = {1,11,15,20,24,29};
    int g = 0;
    for(int j=0; j<30; j++){
        sistema->listaEquipamentos[j] = (Equipamento*) malloc(sizeof(Equipamento));
        strcpy(sistema->listaEquipamentos[j]->nomeEquipamento,maquinas[j]);
        sistema->listaEquipamentos[j]->grupo = g; 
        if(grupo[g] == j){
            g++;
        }
    
    }
   
    int qt1 = 0;
    int c;
    arq = fopen("pessoas.data","rb");
    while( (c=getc(arq) ) != EOF){
        if(c=='\n'){
                qt1++;
        }
    }
    fclose(arq);
    arq = fopen("pessoas.data","rb");
    for(int i = 0 ; i < qt1 ; i++){
        sistema->listaPessoas[i] = (Pessoa*) malloc(sizeof(Pessoa));
        sistema->listaPessoas[i]->medidas = (Medidas*)malloc(sizeof(Medidas));
        sistema->qtP++;
        fscanf(arq,"%[^|]|%[^|]|%d\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\n",sistema->listaPessoas[i]->nome,
                        sistema->listaPessoas[i]->objetivo,
                        &sistema->listaPessoas[i]->sexo,
                        &sistema->listaPessoas[i]->imc,
                        &sistema->listaPessoas[i]->medidas->abdomen,
                        &sistema->listaPessoas[i]->medidas->altura,
                        &sistema->listaPessoas[i]->medidas->bracoDireito,
                        &sistema->listaPessoas[i]->medidas->bracoEsquerdo,
                        &sistema->listaPessoas[i]->medidas->cintura,
                        &sistema->listaPessoas[i]->medidas->panturrilhaDireita,
                        &sistema->listaPessoas[i]->medidas->panturrilhaEsquerda,
                        &sistema->listaPessoas[i]->medidas->peito,
                        &sistema->listaPessoas[i]->medidas->pernaDireita,
                        &sistema->listaPessoas[i]->medidas->peso);

        sistema->listaPessoas[i]->treino = geraTreino(sistema,sistema->listaPessoas[i]->objetivo);
        }

        fclose(arq);
    
}
