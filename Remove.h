void exibirRemoverForm(){

}
void controleRemove(char *nome){
	if(strcmp(nome, "CANCELA") == 0 ){
		voltarMenu(3);
	}else if(strcmp(nome,"CONFIRMA") == 0){
		confirmaBuscar();	
	}else if(strcmp(nome,"VOLTAR") == 0){
		voltarMenu(3);
	}
}