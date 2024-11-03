#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <ctype.h>

// #define MAX_LENGTH 15
int opcao;
char input[50];     // string a verificar caracteres
int isNumber;       // 1 quando for número e 0 quando não for
int pesquisa;       // pesquisa por id
int encontrado = 0; // verificar se aluno foi encontrado ou não (0 - não encontrado, 1 - encontrado)
int maxNotas = 3;   // m�ximo de notas por aluno
int maxAlunos = 5;  // m�ximo de alunos
char primeiroNome[23], ultimoNome[23];

typedef struct aluno
{
    char nome[50]; // cada nome pode ter 50 caracteres no m�ximo
    int idade;
    int alunoID;
    float notas[3];
    float media;
    int estado;
} ALUNO;

int exibirMenu(ALUNO alunos[], int maxAlunos, int maxNotas);
void inserirRegistos(ALUNO alunos[], int maxAlunos, int maxNotas);
void exibirRegistos(ALUNO alunos[], int maxAlunos);
void calcularMedia(ALUNO alunos[], int maxAlunos, int maxNotas);
void pesquisarRegistos(ALUNO alunos[], int maxAlunos);
void procurarMelhorAluno(ALUNO alunos[], int maxAlunos);
void editarRegistos(ALUNO alunos[], int maxAlunos);
int procurarIndice(ALUNO alunos[], int maxAlunos);
void verificarEstado(ALUNO alunos[], int maxAlunos);
void inicializarAlunos(ALUNO alunos[], int maxAlunos);
int verificarIdade(char nome[], int idade);
int verificarStrings(char nome[]);
void eliminarRegisto(ALUNO alunos[], int maxAlunos);
void ordenarAlunoID(ALUNO alunos[], int maxAlunos);
int verificarAlunoID(ALUNO alunos[], int numAlunos);
void cabecalho();
void rodape();

int main()
{
    setlocale(LC_ALL, "Portuguese");

    ALUNO alunos[maxAlunos];
    exibirMenu(alunos, maxAlunos, maxNotas);

    //  inserir rodap�! & order by a pedido do usar e para voltar atrás!!!
    //  tentar colocar a valida��o de inteiro como fun��o
    //  existe a possibilidade de fazer função para verificar ints, floats e dinâmicas de validação
    //  validar ids entre 0-1000
    //  fazer tabelas
    //  verificar se estou a inicializar antes de procurar melhor aluno

    //  id n�o podem ser iguais (verificar se j� existe algum)
    //  posso retirar a função exibir do insert e obrigar o user a vir ao menu ler o que escreveu (faz sentido!!!)
    //  alterar mensagens de erro
    // adicionar símbolo >
    //  tenho de fazer contagem dos pontos
    //  inicializarAlunos(alunos, maxAlunos);
    // Verificar se aluno � menor de idade
    //  getchar() para qq outro caracter inserido
    //  verificar validação menu e pesquisa por id!
    //  introduzir esta l�gica (aprovado ? "Aprovado" : "Reprovado")
    //  procurarMelhorAluno(alunos, maxAlunos);
    //  posso fazer a verifica��o para o primeiro e �ltimo nome ou apenas avaliar a concatena��o da string e voltar ao inc�cio

    return 0;
}

/**
 * @brief Inicializa os dados dos alunos com valores standard.
 *
 * Esta função define valores standard para todos os atributos de cada aluno.
 * O nome é definido como uma string vazia.
 * A idade, alunoID e os estado como números inteiros (int) iguais a 0.
 * As notas, assim como a média como números reais (floats) 0.0.
 *
 * @param alunos Array de estruturas ALUNO a ser inicializado.
 * @param maxAlunos Número máximo de alunos no array.
 */
void inicializarAlunos(ALUNO alunos[], int maxAlunos)
{
    // Incicializar uma struct pode ser uma boa ideia
    for (int i = 0; i < maxAlunos; i++)
    {
        strcpy(alunos[i].nome, ""); // "sem nome"
        alunos[i].idade = 0;
        alunos[i].alunoID = 0;
        for (int j = 0; j < maxNotas; j++)
        {
            alunos[i].notas[j] = 0.0;
        }
        alunos[i].media = 0.0;
        alunos[i].estado = 0; // não-aprovado
    }
}

/**
 * @brief Exibe o menu principal para gerir os dados dos alunos e processa as opções do usuário.
 *
 * O menu apresenta opção para inserir um número máximo de alunos definido globalmente (maxAlunos),
 * apresenta uma tabela com o registo de todos os alunos ordenados por id por ordem crescente,
 * permite ao utilizador procurar por um aluno por id editando os dados do mesmo e
 * caso o utilizador assim queira poderá eliminar o registo de um aluno ou mesmo procurar pelo melhor aluno.
 *
 * @param alunos Array de estruturas ALUNO, que guarda os dados dos alunos.
 * @param maxAlunos Número máximo de alunos no array.
 * @param maxNotas Número máximo de notas que um aluno.
 *
 * @return Retorna 1 ao selecionar a opção "Sair (6)", saindo do menu.
 */
int exibirMenu(ALUNO alunos[], int maxAlunos, int maxNotas)
{
    inicializarAlunos(alunos, maxAlunos);
    while (1)
    {
        system("clear");
        cabecalho();
        printf("\t\t\t*** Menu ***\n");
        printf("\t\t\tInserir registos (1)\n");
        printf("\t\t\tLer registos (2)\n");
        printf("\t\t\tEditar registos (3)\n");
        printf("\t\t\tEliminar registos (4)\n");
        printf("\t\t\tProcurar Melhor Aluno (5)\n");
        printf("\t\t\tSair (6)\n");
        printf("\t\t\tSelecione a opção pretendida.\n");
        printf("\t\t\t***************************************************************************************");
        printf("\n\t\t\t>");

        // valida as opções e impede que o utilizador introduza caracteres que não aqueles pretendidos
        if (scanf("%d", &opcao) != 1 || (opcao < 1 || opcao > 6))
        {
            while (getchar() != '\n')
                ;
            printf("\t\t\tEntrada inválida! Por favor, insira um número entre 1 e 6.\n");
        }

        system("clear");

        printf("\n\t\t\tSelecionou a opção: \n");
        switch (opcao)
        {
        case 1:
            printf("\t\t\tInserir registos (1)\n\n");
            cabecalho();
            inserirRegistos(alunos, maxAlunos, maxNotas);
            rodape();
            break;
        case 2:
            printf("\t\t\tLer registos (2)\n\n");
            cabecalho();
            exibirRegistos(alunos, maxAlunos);
            rodape();
            break;
        case 3:
            printf("\t\t\tEditar registos (3)\n\n");
            cabecalho();
            editarRegistos(alunos, maxAlunos);
            rodape();
            break;
        case 4:
            printf("\t\t\tEliminar registos (4)\n\n");
            cabecalho();
            eliminarRegisto(alunos, maxAlunos);
            rodape();
            break;
        case 5:
            printf("\t\t\tProcurar Melhor Aluno (5)\n\n");
            cabecalho();
            procurarMelhorAluno(alunos, maxAlunos);
            rodape();
            break;
        case 6:
            printf("\t\t\tSair (6)\n\n");
            return 1;
            break;
        default:
            printf("\t\t\tOpção inválida! Por favor tente outra!\n\n");
            break;
        }
        system("clear");
    }
}

/**
 * @brief Exibe os registros de todos os alunos numa lista ordenada por ordem crescente de id.
 *
 * A função exibe uma lista formatada com nome, idade, ID, média e
 * estado de aprovação (convertido de bool ou binário para "Aprovado" e/ou  "Reprovado") de cada aluno.
 * A função 'void ordenarAlunoID(ALUNO alunos[], int maxAlunos)' é chamada no para ordenar os alunos por id por ordem crescente.
 *
 * @param alunos Array de estruturas ALUNO com os dados dos alunos.
 * @param maxAlunos Número máximo de alunos no array.
 */
void exibirRegistos(ALUNO alunos[], int maxAlunos)
{
    ordenarAlunoID(alunos, maxAlunos);
    printf("\t\t\tNome\t\tIdade\t\tID\t\tMédia\t\tEstado\n");
    for (int u = 0; u < maxAlunos; u++)
    {
        if (strcmp(alunos[u].nome, "") != 0)
        {
            printf("\t\t\t%s\t\t%d\t\t%d\t\t%.2f\t\t%s\n", alunos[u].nome, alunos[u].idade, alunos[u].alunoID, alunos[u].media, alunos[u].estado ? "Aprovado" : "Reprovado");
        }
    }
}

/**
 * @brief Insere registros de novos alunos verificando e validando (ou não) os dados introduzidos pelo utilizador.
 *
 * A função permite ao utilizador inserir dados de um novo aluno, tais como o nome, idade, id e notas obtidas.
 * Cada parâmetro é avaliado com grande escrutínio antes do registo ser validado. Isto quer dizer que mensagens de erro,
 * assim como indicações relativamente ao tipo e valor de variáveis podem (e muitas das vezes devem!!!) surgir.
 * Os parâmetros de entrada devem respeitar as seguintes condicionantes:
 * - Nome do aluno: deve conter apenas caracteres alfabéticos [A-Z], sem acentos.
 * - Idade: deve ser um numérico inteiro positivo entre 18-65.
 * - ID do aluno: deve ser um número inteiro (int) ÚNICO e positivo.
 * - Notas: devem ser números reais (float) entre 0.0 a 20.0.
 *
 * @param alunos Array de estruturas ALUNO com dados dos alunos.
 * @param maxAlunos Número máximo de alunos.
 * @param maxNotas Número máximo de notas por aluno.
 */
void inserirRegistos(ALUNO alunos[], int maxAlunos, int maxNotas)
{
    for (int i = 0; i < maxAlunos; i++)
    {

        /* --- Registo de Primeiro e Ultimo Nome --- */
        // a função `verificarStrings` é chamada para garantir que ambos contêm apenas caracteres alfabéticos.

        // estabeleci várias condições para garantir que não tenho nenhum erro
        // strcmp retorna 0 se a strings forem iguais
        // posso comentar && alunos[0].idade == 0 && alunos[0].alunoID == 0 funciona na mesma
        if (strcmp(alunos[i].nome, "") == 0)
        {

            while (1)
            {
                printf("\t\t\tIntroduza o apelidos do aluno %d: ", i + 1);
                printf("\n\t\t\t>");
                //            fgets(ultimoNome, 50, stdin); // MAX_LENGTH instead of sizeof()
                //            ultimoNome[strcspn(ultimoNome, "\n")] = 0;
                scanf("%s", ultimoNome);

                if (verificarStrings(ultimoNome) == 1) // fgets = 0 && scanf = 1
                {
                    break; // sucesso!!!!! YEAHHHH!!
                }
                else
                {
                    printf("\t\t\tIntroduza apenas caracteres alfabéticos!\n");
                }
            }

            getchar();

            while (1)
            {
                printf("\t\t\tIntroduza o primeiro nome do aluno %d: ", i + 1);
                printf("\n\t\t\t>");
                //            fgets(primeiroNome, 50, stdin); // MAX_LENGTH instead of sizeof()
                //            primeiroNome[strcspn(primeiroNome, "\n")] = 0;
                scanf("%s", primeiroNome);

                if (verificarStrings(primeiroNome) == 1)
                {
                    break;
                }
                else
                {
                    printf("\t\t\tIntroduza apenas caracteres alfabéticos!\n");
                }
            }

            getchar();

            // Concatenação de nomes
            //        printf("%s.\n",primeiroNome);
            strcat(primeiroNome, " ");
            //        printf("%s.\n",primeiroNome);
            strcat(primeiroNome, ultimoNome);
            //        printf("%s.\n",primeiroNome);
            strcpy(alunos[i].nome, primeiroNome);

            /* --- Registo  de idade --- */
            // o input do user é recolhido em string e posteriormente convertido em número inteiro
            // caso todos os caracteres da string sejam números inteiros.
            // a idade do usuário deve estar compreendida entre 18-65, a verificação é feita com recurso à função
            // verificarIdade(char nome[], int idade).

            do
            {

                printf("\t\t\tQual a idade do aluno %d? ", i + 1);
                printf("\n\t\t\t>");

                do
                {
                    isNumber = 1;
                    scanf("%s", input);

                    for (int j = 0; j < strlen(input); j++)
                    {
                        if (!isdigit(input[j]))
                        {
                            isNumber = 0;
                            break;
                        }
                    }

                    if (!isNumber)
                    {
                        printf("\t\t\tIntroduza caracteres válidos.\n");
                        printf("\n\t\t\t>");
                    }

                } while (!isNumber);

                /*
                atoi (ASCII to Integer) is a C standard library function that
                converts a string (which represents a number) into an integer (int).
                */

                alunos[i].idade = atoi(input);

                if (verificarIdade(alunos[i].nome, alunos[i].idade) == 0)
                {
                    alunos[i].idade = -1;
                }

            } while (alunos[i].idade < 0);

            /* --- Registo do id do Aluno --- */
            // o input do user é recolhido em string e posteriormente convertido em número inteiro
            // caso todos os caracteres da string sejam números inteiros.
            // o id do aluno deve ser ÚNICO e positivo. a função verificarAlunoID(ALUNO alunos[], int numAlunos)
            // verifica se algum aluno com o mesmo id já foi registado ou não.

            do
            {

                printf("\t\t\tQual o ID do aluno do aluno %d? ", i + 1);
                printf("\n\t\t\t>");

                do
                {
                    isNumber = 1;
                    scanf("%s", input);

                    for (int j = 0; j < strlen(input); j++)
                    {
                        if (!isdigit(input[j]))
                        {
                            isNumber = 0;
                            break;
                        }
                    }

                    if (!isNumber)
                    {
                        printf("\t\t\tIntroduza caracteres válidos.");
                        printf("\n\t\t\t>");
                    }

                } while (!isNumber);

                if (verificarAlunoID(alunos, maxAlunos) == 1)
                {
                    alunos[i].alunoID = atoi(input);
                }
                else
                {
                    alunos[i].alunoID = -1;
                }

            } while (alunos[i].alunoID < 0);

            /* --- Registo das notas do Aluno --- */
            // as notas são avalidas de forma identica à da idade e id, contudo como as notas são números reais (float)
            // as notas podem conter UM ponto e devem encontrar-se entre 0 e 20. toda a verificação e validação é feita aqui.

            for (int j = 0; j < maxNotas; j++)
            {

                printf("\t\t\tIndique a %d avaliação do aluno %d? ", j + 1, i + 1);
                printf("\n\t\t\t>");

                do
                {
                    isNumber = 1;

                    scanf("%s", input);

                    for (int k = 0; k < strlen(input); k++)
                    {
                        if (!isdigit(input[k]) && input[k] != '.')
                        {
                            isNumber = 0;
                            break;
                        }
                    }

                    if (isNumber)
                    {
                        if (atof(input) < 0 || atof(input) > 20)
                        {
                            printf("\t\t\tA nota deve estar entre 0-20.\n");
                            printf("\t\t\t>");
                            isNumber = 0;
                        }
                        else
                        {
                            alunos[i].notas[j] = atof(input);
                        }
                    }
                    else
                    {
                        printf("\t\t\tIntroduza uma nota válida.\n");
                        printf("\t\t\t>");
                    }

                } while (!isNumber);
            }

            // após inseridos as notas, as médias e os estados são calculados

            calcularMedia(alunos, maxAlunos, maxNotas);

            verificarEstado(alunos, maxAlunos);
        }
        // exibirRegistos(alunos, maxAlunos);
    }

    // é possivel inicialmente inserir o número máximo de alunos (maxAlunos), eleminar um ou vários por id e voltar a
    // inserir de novo até maxAlunos. sempre que o número maxAlunos for atingido estas mensagens serão exibidas ao utilizador
    printf("\t\t\tNão é possível adicionar mais registos.\n");
    printf("\t\t\tO número máximo de registos %d foi atingido.\n", maxAlunos);
}

/**
 * @brief Pede ao utilizador o id de um aluno e exibe o registo do mesmo.
 *
 * O id fornecido pelo utilizador é analisado como string de modo a auferir se é um número inteiro (int)
 * e posteriormente fornece ao utilizador ou uma mensagem para inserir um id válido e/ou exibe o registo do aluno pretendido.
 * caso o id seja válido (inteiro positivo) porém não correspondente a qualquer registo, a informação de que o aluno não existe
 * também será transmitida ao utilizador.
 *
 * @param alunos Array de estruturas ALUNO com os dados dos alunos.
 * @param maxAlunos Número máximo de alunos no array.
 */
void pesquisarRegistos(ALUNO alunos[], int maxAlunos)
{

    printf("\t\t\tInsira o ID do estudante a procurar: ");
    printf("\n\t\t\t>");
    do
    {
        isNumber = 1;
        // scanf("%d", &pesquisa);
        scanf("%s", input); // string

        for (int j = 0; j < strlen(input); j++)
        {
            if (!isdigit(input[j]))
            {
                isNumber = 0;
                break;
            }
        }

        if (!isNumber)
        {
            printf("\t\t\tIntroduza um caracter válido.");
            printf("\n\t\t\t>");
        }
        else
        {
            pesquisa = atoi(input); // string to int
            break;
        }

    } while (1);

    for (int k = 0; k < maxAlunos; k++)
    {
        if (alunos[k].alunoID == pesquisa)
        {

            printf("\t\t\tNome\t\tIdade\t\tID\t\tMédia\t\tEstado\n");

            printf("\t\t\t%s\t\t%d\t\t%d\t\t%.2f\t\t%s\n", alunos[k].nome, alunos[k].idade, alunos[k].alunoID, alunos[k].media, alunos[k].estado ? "Aprovado" : "Reprovado");
            encontrado = 1;
            break; // não é necessário continuar no ciclo, já encontrámos o aluno
        }
    }

    if (encontrado == 0)
    {
        printf("\t\t\tO aluno com o ID #%d não foi encontrado.\n", pesquisa);
    }
}

/**
 * @brief Edita os registros de um aluno existente.
 *
 * Esta função permite ao utilizador editar o nome, idade e notas de um aluno, através de uma pesquisa válida de id.
 * O utilizador tem ainda a opção de escolher individualmente qual dos parâmetros pretende modificar.
 * As entradas são verificadas e validadas tal como no primeiro registo. Caso esteja tudo correto as médias
 * e os estados de aprovação são calculados novamente.
 *
 * @param alunos Array de estruturas ALUNO com os dados dos alunos.
 * @param maxAlunos Número máximo de alunos no array.
 */
void editarRegistos(ALUNO alunos[], int maxAlunos)
{
    // exibirRegistos(alunos, maxAlunos);
    pesquisarRegistos(alunos, maxAlunos);

    // caso o aluno seja encontrado!
    if (encontrado == 1)
    {

        /* --- Alteração do Nome --- */
        // a função `verificarStrings` é chamada para garantir que ambos contêm apenas caracteres alfabéticos.
        // Nota que na opção Editar é possivel alterar o nome concatenado previamente inserido sem necessidade em
        // inserir o primeiro e último nome novamente.

        int editarNome; // parâmetro que controla a edição ou não

        do
        {
            printf("\t\t\tInsira editar o nome do aluno? (1 - Sim, 0 - Não): ");
            printf("\n\t\t\t>");
            scanf("%d", &editarNome);

            while (getchar() != '\n')
                ; // limpar buffer

            if (editarNome != 0 && editarNome != 1)
            {
                printf("\t\t\tEntrada Inválida.\n");
            }
        } while (editarNome != 0 && editarNome != 1);

        if (editarNome == 1)
        {

            while (1)
            {
                printf("\t\t\tInsira o novo nome: ");
                printf("\n\t\t\t>");
                fgets(alunos[procurarIndice(alunos, maxAlunos)].nome, sizeof(alunos[procurarIndice(alunos, maxAlunos)].nome), stdin);
                alunos[procurarIndice(alunos, maxAlunos)].nome[strcspn(alunos[procurarIndice(alunos, maxAlunos)].nome, "\n")] = 0;

                if (verificarStrings(alunos[procurarIndice(alunos, maxAlunos)].nome) == 1)
                {
                    break; // sucesso!!!!! YEAHHHH!!
                }
                else
                {
                    printf("\t\t\tIntroduza apenas caracteres alfabéticos.\n");
                }
            }
        }

        /* --- Alteração da idade --- */
        // o input do user é recolhido em string e posteriormente convertido em número inteiro
        // caso todos os caracteres da string sejam números inteiros.
        // a idade do usuário deve estar compreendida entre 18-65, a verificação é feita com recurso à função
        // verificarIdade(char nome[], int idade).

        int editarIdade;

        do
        {
            printf("\t\t\tInsira editar a idade do aluno? (1 - Sim, 0 - Não): ");
            printf("\n\t\t\t>");
            scanf("%d", &editarIdade);
            while (getchar() != '\n')
                ; // limpar buffer

            if (editarIdade != 0 && editarIdade != 1)
            {
                printf("\t\t\tEntrada Inválida.\n");
            }
        } while (editarIdade != 0 && editarIdade != 1);

        if (editarIdade == 1)
        {
            do
            {
                printf("\t\t\tInsira a nova idade: ");
                printf("\n\t\t\t>");

                do
                {
                    isNumber = 1;
                    scanf("%s", input);

                    for (int j = 0; j < strlen(input); j++)
                    {
                        if (!isdigit(input[j]))
                        {
                            isNumber = 0;
                            break;
                        }
                    }

                    if (!isNumber)
                    {
                        printf("\t\t\tIntroduza caracteres válidos.");
                        printf("\n\t\t\t>");
                    }

                } while (!isNumber);

                /*
                atoi (ASCII to Integer) is a C standard library function that
                converts a string (which represents a number) into an integer (int).
                */

                alunos[procurarIndice(alunos, maxAlunos)].idade = atoi(input);
                if (verificarIdade(alunos[procurarIndice(alunos, maxAlunos)].nome, alunos[procurarIndice(alunos, maxAlunos)].idade) == 0)
                {
                    alunos[procurarIndice(alunos, maxAlunos)].idade = -1;
                }
            } while (alunos[procurarIndice(alunos, maxAlunos)].idade < 0);
        }

        /* --- Registo das notas do Aluno --- */
        // as notas são avalidas de forma identica à da idade e id, contudo como as notas são números reais (float)
        // as notas podem conter UM ponto e devem encontrar-se entre 0 e 20. toda a verificação e validação é feita aqui.
        // Nota importante!!! A edição das notas é feita uma a uma i.e. caso pretenda editar as notas devo editar as 3 uma a uma.

        int editarNotas;

        do
        {
            printf("\t\t\tPretende editar as notas do aluno? (1 - Sim, 0 - Não): ");
            printf("\n\t\t\t>");
            scanf("%d", &editarNotas);
            while (getchar() != '\n')
                ; // limpar buffer

            if (editarNotas != 0 && editarNotas != 1)
            {
                printf("\t\t\tEntrada Inválida.\n");
            }
        } while (editarNotas != 0 && editarNotas != 1);

        if (editarNotas == 1)
        {

            for (int j = 0; j < maxNotas; j++)
            {

                printf("\t\t\tInsira a nota %d: ", j + 1);
                printf("\n\t\t\t>");

                do
                {
                    isNumber = 1;

                    scanf("%s", input);

                    for (int k = 0; k < strlen(input); k++)
                    {
                        if (!isdigit(input[k]) && input[k] != '.')
                        {
                            isNumber = 0;
                            break;
                        }
                    }

                    if (isNumber) // se for um número
                    {
                        // estar entre 0 e 20 para ser validada
                        if (atof(input) < 0 || atof(input) > 20)
                        {
                            printf("\t\t\tA nota deve estar entre 0-20.");
                            printf("\n\t\t\t>");
                            isNumber = 0; // digo que não é um número embora seja
                        }
                        else
                        {
                            // caso esteja no intervalo o valor é atribuído
                            alunos[procurarIndice(alunos, maxAlunos)].notas[j] = atof(input);
                        }
                    }
                    else // se não for um número
                    {
                        printf("\t\t\tIntroduza uma nota válida.");
                        printf("\n\t\t\t>");
                    }

                } while (!isNumber);
            }

            // atualização da média e do estado do aluno
            calcularMedia(alunos, maxAlunos, maxNotas); 
            verificarEstado(alunos, maxAlunos);
        }
    }
}

/**
 * @brief Calcula a média das notas de cada aluno.
 * 
 * Esta função percorre um array de estruturas ALUNO, calculando a média
 * das notas (até maxNotas) para cada aluno. A média é calculada somando todas as
 * notas e dividindo pelo número de notas válidas (em princípio maxNotas).
 *
 * @param alunos Array de estruturas ALUNO com os dados dos alunos.
 * @param maxAlunos Número máximo de alunos no array.
 * @param maxNotas Número máximo de notas de cada aluno.
 */
void calcularMedia(ALUNO alunos[], int maxAlunos, int maxNotas)
{
    for (int u = 0; u < maxAlunos; u++)
    {
        // reseta os valores para cada aluno
        float soma = 0;
        int count = 0;
        for (int v = 0; v < maxNotas; v++)
        {
            soma += alunos[u].notas[v];
            count++;
        }

        if (count > 0)
        {
            alunos[u].media = soma / count;
        }
        else
        {
            alunos[u].media = 0;
        }
    }
}

/**
 * @brief Verifica o estado de aprovação de cada aluno com base na média.
 * 
 * Caso a média de um aluno for igual ou superior a 10, o estado do aluno
 * é definido como aprovado (1). Caso contrário, o estado é definido como
 * reprovado (0).
 *
 * @param alunos Array de estruturas ALUNO com os dados dos alunos.
 * @param maxAlunos Número máximo de alunos no array.
 */
void verificarEstado(ALUNO alunos[], int maxAlunos)
{

    for (int i = 0; i < maxAlunos; i++)
    {
        if (alunos[i].media >= 10)
        {
            alunos[i].estado = 1;
        }
        else
        {
            alunos[i].estado = 0;
        }
    }
}

/**
 * @brief Procura o aluno com a maior média.
 * 
 * Esta função permite identificar qual o aluno com a média mais alta, 
 * ou apresentar os vários ids dos alunos com as notas mais altas.
 * Caso não existam alunos registados a função também indica que não existem alunos registados.
 *
 * @param alunos Array de estruturas ALUNO com os dados dos alunos.
 * @param maxAlunos Número máximo de alunos no array.
 */
void procurarMelhorAluno(ALUNO alunos[], int maxAlunos)

{
    int contador = 0; // utilizado para saber quantos alunos obtiveram a média mais alta
    int idMelhorAluno[maxAlunos];
    //    float notaMaisAlta = alunos[0].media;
    float notaMaisAlta = -1;
    for (int w = 0; w < maxAlunos; w++)
    {
        if (strcmp(alunos[w].nome, "") != 0)
        {
            if (alunos[w].media > notaMaisAlta)
            {
                notaMaisAlta = alunos[w].media;       // maior média
                idMelhorAluno[0] = alunos[w].alunoID; // aluno com melhor média
                contador = 1;
            }
            else if (alunos[w].media == notaMaisAlta)
            {
                idMelhorAluno[contador] = alunos[w].alunoID;
                contador++;
            }
        }
    }
    // fora do loop !!!
    if (contador == 0)
    {
        printf("\t\t\tNão foi encontrado nenhum aluno.\n");
    }
    else if (contador == 1)
    {
        printf("\t\t\tO aluno com a média mais alta e o aluno com o id #%d, com uma média de %.2f.\n", idMelhorAluno[0], notaMaisAlta);
    }
    else
    {
        printf("\t\t\tForam encontrados mais do que uma nota alta %.2f.\n", notaMaisAlta);
        for (int i = 0; i < contador; i++)
        {
            printf("\t\t\tAlunoID: %d\n", idMelhorAluno[i]); // mostra todos os alunos com
        }
    }
}

/**
 * @brief Procura o índice de um aluno no array de alunos com base no ID do aluno.
 * 
 * O id dos alunos registados difere do índice do array de estruturas ALUNO, 
 * assim esta função percorre todo esse array à procura do índice correspondente ao
 * id do aluno pesquisado pelo utilizador. Caso esse valor seja encontrado a função devolve 
 * esse mesmo valor, caso contrário retorna -1.
 *
 * @param alunos Array de estruturas ALUNO com os dados dos alunos.
 * @param maxAlunos Número máximo de alunos no array.
 * @return O índice do aluno encontrado ou -1 caso o aluno não seja encontrado.
 */
int procurarIndice(ALUNO alunos[], int maxAlunos)
{
    for (int j = 0; j < maxAlunos; j++)
    {
        if (alunos[j].alunoID == pesquisa)
        {
            return j;
        };
    }
    return -1;
}

/**
 * @brief Verifica se um aluno é elegível com base na idade.
 * 
 * O aluno apenas pode ser registado caso se encontre em idade ativa i.e. tenha entre 18 e 65 anos. 
 * Se o aluno não cumprir esses critérios, uma mensagem apropriada é exibida e a função 
 * retorna 0 (não elegivel), caso contrário, retorna 1 (eligivel).
 *
 * @param nome Nome do aluno.
 * @param idade Idade do aluno.
 * @return 1 se o aluno for elegível, 0 caso contrário.
 */
int verificarIdade(char nome[], int idade)
{
    // verifica se o aluno é elegível
    if (idade < 18)
    {
        printf("\t\t\tO aluno deve ser maior de idade.\n");
        return 0; // não elegível
    }
    else if (idade > 65)
    {
        printf("\t\t\tO aluno deve ter menos de 65 anos.\n");
        return 0; // não elegível
    }
    return 1; // elegível
}

/**
 * @brief Verifica se uma string contém apenas caracteres alfabéticos e espaços.
 * 
 * Esta função percorre uma string e verifica se todos os caracteres são letras 
 * do alfabeto [A-Z] ou espaços. Permite a validação de nomes de aluno completos.
 *
 * @param nome A string a ser verificada.
 * @return 1 se a string contém apenas letras e espaços, 0 caso contrário.
 */
int verificarStrings(char nome[])
{
    for (int i = 0; nome[i] != '\0'; i++) // até atingir o null checker '\0'
    {
        if (!isalpha(nome[i]) && nome[i] != ' ')
        {
            return 0;
        }
    }
    return 1;
}

/**
 * @brief Elimina o registo de um aluno por id.
 * 
 * O utilizador tem a opção de eliminar um aluno por id. Caso o id seja válido, 
 * todos os dados relativos a esse aluno serão eliminados. Caso o id não exista, 
 * o utilizador será informado que o aluno não foi encontrado. O id é previamente verificado e validado.
 *
 * @param alunos Array de alunos onde os registos serão eliminados (ou inicializados).
 * @param maxAlunos Número máximo de alunos permitidos pelo sistema.
 */
void eliminarRegisto(ALUNO alunos[], int maxAlunos)
{
    printf("\t\t\tInsira o ID do estudante a eliminar: ");
    printf("\n\t\t\t>");
    do
    {
        isNumber = 1;
        scanf("%s", input); // string

        for (int j = 0; j < strlen(input); j++)
        {
            if (!isdigit(input[j]))
            {
                isNumber = 0;
                break;
            }
        }

        if (!isNumber)
        {
            printf("\t\t\tIntroduza um caracter válido.");
            printf("\n\t\t\t>");
        }
        else
        {
            pesquisa = atoi(input); // string to int
            break;
        }

    } while (1);

    // se não definir variável quando volto a listar(pesquisar) tenho erro (segmentation fault 11)
    int indice = procurarIndice(alunos, maxAlunos);
    // printf("%d", indice); // retorna o índice do aluno a eliminar

    if (indice != -1) // Verifica se o aluno existe
    {
        strcpy(alunos[indice].nome, "");
        alunos[indice].idade = 0;
        alunos[indice].alunoID = 0;
        for (int j = 0; j < maxNotas; j++)
        {
            alunos[indice].notas[j] = 0.0;
        }
        alunos[indice].media = 0.0;
        alunos[indice].estado = 0;

        printf("\n\t\t\tO aluno com id #%d foi eliminado.\n", pesquisa);
    }
    else
    {
        printf("\n\t\t\tAluno com id #%d não encontrado.\n", pesquisa);
    }
}

/**
 * @brief Ordena os alunos com base no ID em ordem crescente.
 *
 * Esta função ordena o id dos alunos por ordem crescente.
 * 
 * @param alunos Array de alunos a ser ordenado.
 * @param maxAlunos Número máximo de alunos permitidos registar.
 */
void ordenarAlunoID(ALUNO alunos[], int maxAlunos)
{

    if (strcmp(alunos[0].nome, "") != 0) // retorna 1 se as strings forem diferentes (estrutura populada)
    {
        // ordem crescente
        // na primeira iteração i, o maior valor com indíce j vai sempre parar a último
        for (int i = 0; i < maxAlunos - 1; i++)
        {
            // se for maior troca senão mantém a posição na array
            for (int j = 0; j < maxAlunos - i - 1; j++)
            {
                if (alunos[j].alunoID > alunos[j + 1].alunoID)
                {

                    ALUNO temp = alunos[j];
                    alunos[j] = alunos[j + 1];
                    alunos[j + 1] = temp;
                }
            }
        }
    }
}

/**
 * @brief Verifica se o id do aluno é único.
 *
 * O utilizador deve inserir ids únicos. Esta função garante que o utilizador não repete 
 * ids. A array de alunos é percorrida e caso já exista um id igual, o utilizador é informado que 
 * o id já está associado a outro aluno retornando 0. Caso o id seja único, a função retorna 1.
 * 
 * @param alunos Array de alunos.
 * @param maxAlunos Número máximo de alunos perminitdo.
 * @return 0 se o AlunoID já existir, 1 se for único.
 */
int verificarAlunoID(ALUNO alunos[], int maxAlunos)
{
    for (int i = 0; i < maxAlunos; i++)
    {
        if (alunos[i].alunoID == atoi(input))
        {
            printf("\t\t\tAlunoID existente, tente outro.\n");
            return 0; // retorna 0 se AlunoID já existir
        }
    }
    return 1; // retorna 1 se AlunoID não existir
}

/**
 * @brief Exibe o cabeçalho do sistema de gestão de dados dos alunos.
 *
 * Esta função imprime um cabeçalho formatado que apresenta o
 * sistema de gestão de dados dos alunos.
 */
void cabecalho()
{
    printf("\t\t\t***************************************************************************************\n");
    printf("\t\t\t           Sistema básico de gestão de dados dos alunos.                              \n");
    printf("\t\t\t***************************************************************************************\n");
}

/**
 * @brief Exibe o rodapé do sistema.
 *
 * Após o utilizador realizar as operações que pretende pode dar a sua 
 * ação por concluída e voltar ao menu pressionando '6'. A entrada de dados 
 * por parte do utilizador é verificada apenas quando este inserir uma entrada válida.
 * 
 */
void rodape()
{
    printf("\t\t\t***************************************************************************************\n");
    printf("\t\t\t                                                                   Voltar ao Menu (6)  \n");
    printf("\t\t\t***************************************************************************************\n");

    int voltar;

    do
    {
        printf("\t\t\t>");

        scanf("%s", input);

        isNumber = 1;
        for (int j = 0; j < strlen(input); j++)
        {
            if (!isdigit(input[j]))
            {
                isNumber = 0;
                break;
            }
        }

        if (isNumber)
        {
            voltar = atoi(input);
            if (voltar == 6)
            {
                break;
            }
        }

        printf("\t\t\tPressione 6 para voltar ao menu.\n");

    } while (1);
}