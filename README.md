
# FRANGO Fup Ncurses GYM Application

# Feito com suor e lágrimas e &hearts; em C

## Bibliotecas

Ncurses, Form, Menu, Stdio, Stdlib, Assert, String, Time, Math

# Ncurses:



Biblioteca Responsavél pela interface da aplicação com o usuário
Tem como objetivo, preparar um ambiente mais amigavél ao usuário final da aplicação durante sua execução no terminal, proporcionando funcões e estruturas
para controlar o mesmo

# Form:

Utilizada juntamente com a biblioteca Ncuses, responsavél por gerar e controlar estruturas de formulário, tais estruturas são usadas para a interação de entrada de dados do usuário

#  Menu:

Assim como a biblioteca Form ela é usada juntamente com a biblioteca Ncurses, onde ela é utilizada na criação de menus exibidos ao usuário

# Assert:

Usada para tratamento de erros em tempo de execução em relação à biblioteca Ncurses, Form, Menu

# Stdio :

Biblioteca usada pra controle de entrada e saida

# Stdlib:

Tal Biblioteca tem funcões que auxiliam na mainpulação de variavéis ex : malloc, calloc

# String :

Biblioteca usada na manipulação de vetores de caracteres (String), tal biblioteca possui funções para auxilio de tal estrutura

# Time:

Biblioteca  utilizada para auxilio e facilidade de ineração com o usuário (mostrar data e hora de alguns processos ralizados)

# Math:

Biblioteca Utilizada elaboração de funções matemáticas , ex : calculaImc

# Estruturas:

## Medidas:

Esturura responsavél por armazenar todos os valores relacionados as medidas do cliente

# Pessoa:

Estrutura responsavél por armazenar os atributos relacionados ao cliente dentro da aplicação

# Treino:

Estrutura de auxilio pra manipulação de certos atributos relacionados ao cliente dentro da aplicação

## Exercicio:

Estrutura reponsavél por armazenar os exercicios à serem realizados no dia especificado

## Equipamento:

Estrutura responsavél por armazenar os valores relacionados ao equipamento utilizado pelo cliente 

##  Sistema:

Estrutura responsavél por armazendar os clientes e equipamentos dentro da aplicação

# Esquema das Estruturas

<img src="Esquema.png">

# Funções e Procedimentos da Biblioteca Ncurses e suas dependênicas

initscr : Procedimento responsavél por inicializar a biblioteca Ncurses

noecho : desativa a função de echo do terminal

cbreak : desativa a interpretação de comandos do terminal exeternos a aplicação

keypad : inicializa o telado para uso da aplicação

refresh : atualiza todas as janelas da aplicação

wrefresh : atualiza uma janela especĩfica da aplicação
