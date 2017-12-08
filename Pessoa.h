typedef struct medidas{
    float peso;
    float altura;
    float bracoDireito;
    float bracoEsquerdo;
    float pernaDireita;
    float pernaEsquerda;
    float panturrilhaDireita;
    float panturrilhaEsquerda;
    float abdomen;
    float cintura;
    float peito;
}Medidas;

typedef struct pessoa{
    char *nome[50];
    char *objetivo[15];
    float imc;
    int matricula;
    int sexo;
    Medidas *medidas;
    Treino *treino;
}Pessoa;


Pessoa *novaPessoa(char *nome,int matricula,Medidas *medidas,int sexo);
Medidas *novoMedidas(float peso, float altura, float bracoDireito, float bracoEsquerdo, float pernaDireita, float pernaEsquerda, float panturrilhaDireita, float panturrilhaEsquerda, float abdomen, float cintura,float peito);
void condicaoImc(float imc,int sexo, char *ret);
float calculaImc(float peso,float altura);


Pessoa *novaPessoa(char *nome,int matricula,Medidas *medidas,int sexo){
    Pessoa *nova;
    nova = (Pessoa*) malloc(sizeof(Pessoa));
    strcpy(nova->nome,nome);
    nova->matricula = matricula;
    nova->medidas = medidas;
    
    nova->sexo = sexo;
    nova->imc = calculaImc(medidas->peso,medidas->altura);
   
    return nova;
}
Medidas *novoMedidas(float peso,float altura, float bracoDireito, float bracoEsquerdo,float pernaDireita, float pernaEsquerda, float panturrilhaDireita, float panturrilhaEsquerda, float abdomen, float cintura, float peito){
    Medidas *novo;
    novo = (Medidas*) malloc(sizeof(Medidas));
    
    novo->peso = peso;
    novo->altura = altura;
    novo->bracoDireito = bracoDireito;
    novo->bracoEsquerdo = bracoEsquerdo;
    novo->pernaDireita = pernaDireita;
    novo->pernaEsquerda = pernaEsquerda;
    novo->panturrilhaDireita = panturrilhaDireita;
    novo->panturrilhaEsquerda = panturrilhaEsquerda;
    novo->abdomen = abdomen;
    novo->cintura = cintura;
    novo->peito = peito;
    return novo;
}
float calculaImc(float peso,float altura){
    
    return peso / pow(altura,2);
}
void condicaoImc(float imc,int sexo,char ret[]){
   
    if(sexo){
        if(imc < 20.7){
            strcpy(ret,"Abaixo do Ideal");
    
        }else if(imc < 26.4){
            strcpy(ret,"Ideal");
    
            
        }else if(imc  < 27.8){
            strcpy(ret,"um Pouco acima do Ideal");
    
        }else if(imc < 31.1){
            strcpy(ret,"acima do Ideal");
    
        }else{
            strcpy(ret,"muito acima do Ideal");
    
        }
    }else{
      
        if(imc < 19.1){
            strcpy(ret,"Abaixo do Ideal");

        }else if(imc < 25.8){
            strcpy(ret,"Ideal");

        }else if(imc  < 27.3){
              strcpy(ret,"um Pouco acima do Ideal");
            
        }else if(imc < 32.3){
                  strcpy(ret,"acima do Ideal");
            
        }else{
            strcpy(ret,"muito acima do Ideal");
            
        }
    
    }
}