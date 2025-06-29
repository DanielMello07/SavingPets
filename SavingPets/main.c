#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>

#define NUM_MAX_TUTORES 720
#define NUM_MAX_ANIMAIS 1024

typedef struct Endereco {
    int cep[8];
    char rua[120];
    char bairro[120];
    char cidade[80];
    char estado[50];
    char numero_casa[50];
} Endereco;

typedef struct Forma_contato {
    int telefone[11];
    char email[120];
} Forma_contato;

typedef struct Tutor {
    int tutor_ocupado;
    char nome_tutor[256];
    int id_tutor;
    int id_animais[10];
    int cpf[11];
    char sexo;
    Endereco endereco;
    Forma_contato contato;
} Tutor;

typedef struct Animal {
    int ocupado;
    int adotado;
    char nome_animal[256];
    int id_animal;
    int id_tutor;
    char especie[256];
    char sexo;
    char raca[256];
    char vacinas[512];
    char vermifugado;
    char historico[512];
    char castrado;
} Animal;

typedef struct Data {
    int dia, mes, ano;
} Data;

typedef struct ProcessoAdotivo {
    int id_processo;
    int id_animal;
    int id_tutor;
    Data data_adocao;
    char relatorio_adaptacao[300];
    char agendamentos[200];
    char dados_medicos[200];
    int ativo;
} ProcessoAdotivo;

typedef struct Ocorrencia {
    int id_ocorrencia;
    int id_processo;
    int id_tutor;
    char descricao[300];
    Data data_ocorrencia;
    char acao[300];
    int ativo;
} Ocorrencia;

Tutor vetor_tutores[NUM_MAX_TUTORES];
Animal vetor_animais[NUM_MAX_ANIMAIS];
int total_animais = 0;
int total_tutores = 0;
char caminho_arquivo_animais[256] = "animais.txt";
char caminho_arquivo_tutores[256] = "tutores.txt";

// Fun��es
void cadastro_inicializar_animais();
void cadastro_inicializar_tutores();
void cadastro_inicializar_arquivo_animais();
void cadastro_inicializar_arquivo_tutores();
void cadastro_carregar_dados_arquivo_animais();
void cadastro_carregar_dados_arquivo_tutores();
void cadastro_salvar_dados_arquivo_animais();
void cadastro_salvar_dados_arquivo_tutores();
int cadastro_verificar_capacidade_maxima_animais();
int cadastro_verificar_capacidade_maxima_tutores();
int verificar_id_animal_existente(int id);
int verificar_id_tutor_existente(int id);
int verificar_id_tutor_existente2(int id);
void cadastro_inserir_animal(Animal animal);
Animal cadastro_pesquisar_animal(int id);
void cadastro_inserir_tutor(Tutor tutor);
Tutor cadastro_pesquisar_tutor(int id);
int cadastro_remover_animal(int id);
int cadastro_remover_tutor(int id);
int qtde_animais_cadastrados_tutor(int id_tutor);
Tutor animais_id_tutor_inicializador();
int gerar_id_proximo(const char *nome_arquivo, int indice_id);
int controladores_inteiros(char* mensagem);
int controladores_id(char* mensagem);
int inserir_id_animal_em_tutor(int id_animal, int id_tutor);
int tela_limite_animais(int id_tutor);
int tela_exclusao_tutor_opcoes();
int gerar_proximo_id_animal();
int gerar_proximo_id_tutor();

// Telas
void marcas(int tela);
int tela_menu_opcoes();
int tela_menu_processos_adotivos();
int tela_novo_tutor_cadatro_animal(int id_tutor);
int tela_novo_animal_cadatro_tutor(int id_animal, int id_tutor);
Endereco tela_cadastar_endereco();
Forma_contato tela_cadastrar_forma_contato();
void tela_cadastrar_animal();
void tela_cadastrar_tutor();
void tela_relatorio();
void tela_relatorio_animais();
void tela_relatorio_tutores();
void tela_pesquisar();
void tela_pesquisar_tutor();
void tela_remover();
void tela_remover_tutor();
int tela_sair();
int tela_mensagem(char *mensagem);
void tela_processos_adotivos();
void tela_cadastrar_processo_adotivo();
void tela_consultar_processos_adotivos();
void tela_cadastrar_ocorrencia();
void tela_consultar_ocorrencias();

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main() {
    setlocale(LC_ALL, "");
    system("chcp 1252 > nul");

    int sair = 0;
    int opcao;

    cadastro_inicializar_animais();
    cadastro_inicializar_tutores();
    cadastro_inicializar_arquivo_tutores();
    cadastro_inicializar_arquivo_animais();
    cadastro_carregar_dados_arquivo_tutores();
    cadastro_carregar_dados_arquivo_animais();
    marcas(0);

    do {
        opcao = tela_menu_opcoes();
        switch(opcao) {
            case 1:
                tela_cadastrar_animal();
                break;
            case 2:
                tela_cadastrar_tutor();
                break;
            case 3:
                tela_relatorio();
                break;
            case 4:
                tela_pesquisar();
                break;
            case 5:
                tela_pesquisar_tutor();
                break;
            case 6:
                tela_remover();
                break;
            case 7:
                tela_remover_tutor();
                break;
            case 8:
                tela_processos_adotivos();
                break;
            case 9:
                sair = tela_sair();
                break;
            default:
                printf("\nOp��o Inv�lida !!! \n");
                system("pause");
        }
    } while(sair == 0);

    cadastro_salvar_dados_arquivo_animais();
    cadastro_salvar_dados_arquivo_tutores();

    system("cls");
    printf("\nFim da execu��o do programa!\n");

    return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////// TELAS //////////////////////////////////////////

void marcas(int tela) {
    if(tela == 0){
        printf("\t\t\t\t                                                                          \n");
        printf("\t\t\t\t                                                                          \n");
        printf("\t\t\t\t                         @@@@@@@@@             @@@@@@@@@@                  \n");
        printf("\t\t\t\t                       @@@@@@@@@@@@@         @@@@@@@@@@@@@                 \n");
        printf("\t\t\t\t                      @@@@@@@@@@@@@@@@      @@@@@@@@@@@@@@@                \n");
        printf("\t\t\t\t                      @@@@@@@@@@@@@@@@@    @@@@@@@@@@@@@@@@@              \n");
        printf("\t\t\t\t                      @@@@@@@@@@@@@@@@@    @@@@@@@@@@@@@@@@@              \n");
        printf("\t\t\t\t                      @@@@@@@@@@@@@@@@@   @@@@@@@@@@@@@@@@@@              \n");
        printf("\t\t\t\t                      @@@@@@@@@@@@@@@@@   @@@@@@@@@@@@@@@@@                \n");
        printf("\t\t\t\t                       @@@@@@@@@@@@@@@@   @@@@@@@@@@@@@@@@@                \n");
        printf("\t\t\t\t                        @@@@@@@@@@@@@@@    @@@@@@@@@@@@@@@    @@@@@@@     \n");
        printf("\t\t\t\t            @@@@@@@@@     @@@@@@@@@@@@      @@@@@@@@@@@@   @@@@@@@@@@@@   \n");
        printf("\t\t\t\t          @@@@@@@@@@@@@     @@@@@@@@          @@@@@@@@    @@@@@@@@@@@@@@  \n");
        printf("\t\t\t\t          @@@@@@@@@@@@@@@                               @@@@@@@@@@@@@@@@  \n");
        printf("\t\t\t\t          @@@@@@@@@@@@@@@@                              @@@@@@@@@@@@@@@@  \n");
        printf("\t\t\t\t          @@@@@@@@@@@@@@@@@                            @@@@@@@@@@@@@@@@@  \n");
        printf("\t\t\t\t          @@@@@@@@@@@@@@@@@           @@@@@@@          @@@@@@@@@@@@@@@@@  \n");
        printf("\t\t\t\t           @@@@@@@@@@@@@@@@      @@@@@@@@@@@@@@@@@     @@@@@@@@@@@@@@@@   \n");
        printf("\t\t\t\t            @@@@@@@@@@@@@@@   @@@@@@@@@@@@@@@@@@@@@@    @@@@@@@@@@@@@     \n");
        printf("\t\t\t\t             @@@@@@@@@@@@  @@@@@@@@@@@@@@@@@@@@@@@@@@@  @@@@@@@@@@       \n");
        printf("\t\t\t\t                 @@@@@@   @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@                  \n");
        printf("\t\t\t\t                         @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@                 \n");
        printf("\t\t\t\t                        @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@                \n");
        printf("\t\t\t\t                       @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@              \n");
        printf("\t\t\t\t                      @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@             \n");
        printf("\t\t\t\t                     @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@            \n");
        printf("\t\t\t\t                     @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@            \n");
        printf("\t\t\t\t                     @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@           \n");
        printf("\t\t\t\t                      @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@            \n");
        printf("\t\t\t\t                       @@@@@@@@@@@@               @@@@@@@@@@@@             \n");
        printf("\t\t\t\t                                                                           \n\n\n");

        printf("\t\t\t\t\tSavingPets - Sistema Gerenciador de P�s ado��o de Animais Resgatados\n\n\n");
        system("pause");
    } else if(tela == 1) {
        printf("\t\t\t\t           /\\_/\\   \n");
        printf("\t\t\t\t          ( o.o )  \n");
        printf("\t\t\t\t           > ^ <   \n");
    } else if(tela == 2) {
        printf("\t\t\t\t           /^ ^\\ \n");
        printf("\t\t\t\t          / 0 0 \\ \n");
        printf("\t\t\t\t          V\\ Y /V \n");
        printf("\t\t\t\t           / - \\  \n");
        printf("\t\t\t\t          |    \\\\\n");
        printf("\t\t\t\t          || (__V \n");
    }
}

int tela_menu_opcoes() {
    int opcao, erro;
    system("cls");
    printf("***** Menu de Op��es *****\n");
    printf("1 - Cadastrar Animal\n");
    printf("2 - Cadastrar Tutor\n");
    printf("3 - Relat�rio Geral de Animais Cadastrados\n");
    printf("4 - Pesquisar Animal por ID\n");
    printf("5 - Pesquisar Tutor por ID\n");
    printf("6 - Remover Animal\n");
    printf("7 - Remover Tutor\n");
    printf("8 - Processos Adotivos\n");
    printf("9 - Sair\n\n");
    printf("Escolha uma op��o: ");

    erro = scanf("%d", &opcao);
    fflush(stdin);

    if(erro != 1) {
         opcao = -1;
    }

    return opcao;
}

int tela_menu_processos_adotivos() {
    int opcao, erro;
    system("cls");
    printf("***** Menu de Processos Adotivos *****\n");
    printf("1 - Cadastrar Processo Adotivo\n");
    printf("2 - Consultar Processos Adotivos\n");
    printf("3 - Cadastrar Ocorr�ncia\n");
    printf("4 - Consultar Ocorr�ncias\n");
    printf("5 - Voltar ao Menu Principal\n\n");
    printf("Escolha uma op��o: ");

    erro = scanf("%d", &opcao);
    fflush(stdin);

    if(erro != 1) {
        opcao = -1;
    }

    return opcao;
}

void tela_processos_adotivos() {
    int sair = 0;
    int opcao;

    do {
        opcao = tela_menu_processos_adotivos();
        switch(opcao) {
            case 1:
                tela_cadastrar_processo_adotivo();
                break;
            case 2:
                tela_consultar_processos_adotivos();
                break;
            case 3:
                tela_cadastrar_ocorrencia();
                break;
            case 4:
                tela_consultar_ocorrencias();
                break;
            case 5:
                sair = 1;
                break;
            default:
                printf("\nOp��o Inv�lida !!! \n");
                system("pause");
        }
    } while(sair == 0);
}

int tela_novo_tutor_cadatro_animal(int id_tutor) {
    if (cadastro_verificar_capacidade_maxima_tutores() == 1) {
        printf("Erro: Capacidade m�xima de tutores atingida!\n");
        system("pause");
        return 0;
    }

    Tutor t = animais_id_tutor_inicializador();
    t.id_tutor = id_tutor;

    system("cls");
    printf("--- Cadastro de Novo Tutor (ID: %d) ---\n", id_tutor);

    printf("Nome do tutor: ");
    scanf(" %255[^\n]", t.nome_tutor);
    fflush(stdin);

    printf("Sexo (M/F): ");
    scanf(" %c", &t.sexo);
    fflush(stdin);

    printf("CPF (11 d�gitos): ");
    for(int j = 0; j < 11; j++) {
        scanf("%1d", &t.cpf[j]);
    }
    fflush(stdin);

    t.endereco = tela_cadastar_endereco();
    t.contato = tela_cadastrar_forma_contato();

    t.tutor_ocupado = 1;
    cadastro_inserir_tutor(t);

    printf("\nTutor cadastrado com sucesso!\n");
    system("pause");
    return 1;
}

int tela_novo_animal_cadatro_tutor(int id_animal, int id_tutor) {
    Animal a;
    a.ocupado = 0;

    system("cls");
    printf("--- Cadastro de Novo Animal ---\n");

    if (cadastro_verificar_capacidade_maxima_animais() == 1) {
        printf("Erro: Capacidade m�xima de animais atingida!\n");
        system("pause");
        return 0;
    }

    a.id_animal = id_animal;
    a.id_tutor = id_tutor;

    printf("Nome do animal: ");
    scanf(" %255[^\n]", a.nome_animal);
    fflush(stdin);

    printf("Esp�cie: ");
    scanf(" %255[^\n]", a.especie);
    fflush(stdin);

    printf("Sexo (M/F): ");
    scanf(" %c", &a.sexo);
    fflush(stdin);

    printf("Ra�a: ");
    scanf(" %255[^\n]", a.raca);
    fflush(stdin);

    printf("Vacinas: ");
    scanf(" %511[^\n]", a.vacinas);
    fflush(stdin);

    printf("Vermifugado (S/N): ");
    scanf(" %c", &a.vermifugado);
    fflush(stdin);

    printf("Hist�rico de sa�de: ");
    scanf(" %511[^\n]", a.historico);
    fflush(stdin);

    printf("Castrado (S/N): ");
    scanf(" %c", &a.castrado);
    fflush(stdin);

    a.ocupado = 1;
    cadastro_inserir_animal(a);

    printf("\nAnimal cadastrado com sucesso!\n");
    system("pause");
    return 1;
}

void tela_cadastrar_animal() {
    int continuar;
    Animal a;
    int opcao;

    do {
        system("cls");
        printf("--- Cadastro de Animal ---\n");

        if (cadastro_verificar_capacidade_maxima_animais() == 1) {
            printf("Erro: Capacidade m�xima de animais atingida!\n");
            system("pause");
            return;
        }

        // Gera ID autom�tico
        a.id_animal = gerar_proximo_id_animal();
        printf("ID do animal gerado automaticamente: %d\n", a.id_animal);

        if (verificar_id_animal_existente(a.id_animal)) {
            printf("Erro: ID de animal j� cadastrado!\n");
            system("pause");
            continue;
        }

        a.id_tutor = controladores_id("Digite o ID do tutor: ");

        if (!verificar_id_tutor_existente(a.id_tutor)) {
            printf("Tutor n�o encontrado.\n");
            printf("1 - Cadastrar novo tutor\n");
            printf("2 - Cancelar\n");
            opcao = controladores_inteiros("Escolha: ");

            if (opcao == 1) {
                if (tela_novo_tutor_cadatro_animal(a.id_tutor)) {
                    // Continua ap�s cadastrar o tutor
                } else {
                    continue;
                }
            } else {
                continue;
            }
        }

        printf("Nome do animal: ");
        scanf(" %255[^\n]", a.nome_animal);
        fflush(stdin);

        printf("Esp�cie: ");
        scanf(" %255[^\n]", a.especie);
        fflush(stdin);

        printf("Sexo (M/F): ");
        scanf(" %c", &a.sexo);
        fflush(stdin);

        printf("Ra�a: ");
        scanf(" %255[^\n]", a.raca);
        fflush(stdin);

        printf("Vacinas: ");
        scanf(" %511[^\n]", a.vacinas);
        fflush(stdin);

        printf("Vermifugado (S/N): ");
        scanf(" %c", &a.vermifugado);
        fflush(stdin);

        printf("Hist�rico de sa�de: ");
        scanf(" %511[^\n]", a.historico);
        fflush(stdin);

        printf("Castrado (S/N): ");
        scanf(" %c", &a.castrado);
        fflush(stdin);

        a.ocupado = 1;
        a.adotado = 0;
        cadastro_inserir_animal(a);
        inserir_id_animal_em_tutor(a.id_animal, a.id_tutor);

        continuar = tela_mensagem("Deseja cadastrar outro animal?");
    } while (continuar == 1);
}

Endereco tela_cadastar_endereco() {
    Endereco endereco;

    printf("\t\t\t\tDigite o CEP: ");
    for(int j = 0; j < 8; j++) {
        scanf("%1d", &endereco.cep[j]);
    }
    fflush(stdin);

    printf("Informe a rua: ");
    scanf(" %119[^\n]", endereco.rua);
    fflush(stdin);

    printf("Informe o bairro: ");
    scanf(" %119[^\n]", endereco.bairro);
    fflush(stdin);

    printf("Informe a cidade: ");
    scanf(" %79[^\n]", endereco.cidade);
    fflush(stdin);

    printf("Informe o estado: ");
    scanf(" %49[^\n]", endereco.estado);
    fflush(stdin);

    printf("Informe o n�mero da casa: ");
    scanf(" %49[^\n]", endereco.numero_casa);
    fflush(stdin);

    return endereco;
}

Forma_contato tela_cadastrar_forma_contato() {
    Forma_contato contato;

    printf("Digite o telefone com ddd: ");
    for(int j = 0; j < 11; j++) {
        scanf("%1d", &contato.telefone[j]);
    }
    fflush(stdin);

    printf("Digite o e-mail: ");
    scanf(" %119[^\n]", contato.email);
    fflush(stdin);

    return contato;
}

void tela_cadastrar_tutor() {
    int quantidade_adotados;
    char cadastrar_novo_animal;
    int continuar;

    Tutor t;
    t = animais_id_tutor_inicializador();

    do {
        system("cls");
        printf("--- Cadastro de Tutor ---\n");

        if (cadastro_verificar_capacidade_maxima_tutores() == 1) {
            printf("Erro: Capacidade m�xima de tutores atingida!\n");
            system("pause");
            break;
        }

        // Gera ID autom�tico
        t.id_tutor = gerar_proximo_id_tutor();
        printf("ID do tutor gerado automaticamente: %d\n", t.id_tutor);

        if (verificar_id_tutor_existente(t.id_tutor)) {
            printf("Erro: ID de tutor j� cadastrado!\n");
            system("pause");
            continue;
        }

        quantidade_adotados = controladores_inteiros("Digite a quantidade de animais adotados: ");

        if (quantidade_adotados < 1 || quantidade_adotados > 10) {
            printf("N�o � poss�vel cadastrar tutores com menos de 1 animal ou mais de 10 animais\n");
            system("pause");
            continue;
        }

        for(int i = 0; i < quantidade_adotados; i++) {
            int id_valido = 0;

            while (!id_valido) {
                int id_animal = controladores_id("Digite o ID do animal: ");

                if (verificar_id_animal_existente(id_animal)) {
                    t.id_animais[i] = id_animal;
                    id_valido = 1;
                } else {
                    printf("Animal n�o encontrado!\n");
                    printf("1 - Cadastrar novo animal\n");
                    printf("2 - Cancelar\n");
                    int opcao = controladores_inteiros("Escolha: ");

                    if (opcao == 1) {
                        if (tela_novo_animal_cadatro_tutor(id_animal, t.id_tutor)) {
                            t.id_animais[i] = id_animal;
                            id_valido = 1;
                        }
                    } else {
                        t.id_animais[i] = 0;
                        break;
                    }
                }
            }
        }

        printf("Nome do tutor: ");
        scanf(" %255[^\n]", t.nome_tutor);
        fflush(stdin);

        printf("Sexo (M/F): ");
        scanf(" %c", &t.sexo);
        fflush(stdin);

        printf("CPF (11 d�gitos): ");
        for(int j = 0; j < 11; j++) {
            scanf("%1d", &t.cpf[j]);
        }
        fflush(stdin);

        t.endereco = tela_cadastar_endereco();
        t.contato = tela_cadastrar_forma_contato();

        t.tutor_ocupado = 1;
        cadastro_inserir_tutor(t);
        printf("Tutor cadastrado com sucesso!\n");
        system("pause");

        continuar = tela_mensagem("Deseja cadastrar outro tutor?");
    } while (continuar == 1);
}

void tela_relatorio() {
    int opcao, erro;
    do {
        system("cls");
        printf("***** Menu de Relat�rios *****\n");
        printf("1 - Relat�rio de Animais Cadastrados\n");
        printf("2 - Relat�rio de Tutores Cadastrados\n");
        printf("3 - Voltar ao Menu Principal\n\n");
        printf("Escolha uma op��o: ");

        erro = scanf("%d", &opcao);
        fflush(stdin);

        if(erro != 1) {
            opcao = -1;
        }

        switch(opcao) {
            case 1:
                tela_relatorio_animais();
                break;
            case 2:
                tela_relatorio_tutores();
                break;
            case 3:
                return;
            default:
                printf("\nOp��o Inv�lida !!! \n");
                system("pause");
        }
    } while(1);
}

void tela_relatorio_animais() {
    system("cls");
    printf("Relat�rio de Animais Cadastrados\n\n");
    printf("Total de Animais Cadastrados: %d\n\n", total_animais);

    for (int i = 0; i < NUM_MAX_ANIMAIS; i++) {
        if (vetor_animais[i].ocupado == 1) {
            printf("ID Animal: %d\n", vetor_animais[i].id_animal);
            printf("ID Tutor: %d\n", vetor_animais[i].id_tutor);
            printf("Nome: %s\n", vetor_animais[i].nome_animal);
            printf("Esp�cie: %s\n", vetor_animais[i].especie);
            printf("Sexo: %c\n", vetor_animais[i].sexo);
            printf("Ra�a: %s\n", vetor_animais[i].raca);
            printf("Vacinas: %s\n", vetor_animais[i].vacinas);
            printf("Vermifugado: %c\n", vetor_animais[i].vermifugado);
            printf("Hist�rico: %s\n", vetor_animais[i].historico);
            printf("Castrado: %c\n", vetor_animais[i].castrado);
            printf("Adotado: %d\n\n", vetor_animais[i].adotado);
        }
    }
    system("pause");
}

void tela_relatorio_tutores() {
    system("cls");
    printf("Relat�rio de Tutores Cadastrados\n\n");
    printf("Total de Tutores Cadastrados: %d\n\n", total_tutores);

    for (int i = 0; i < NUM_MAX_TUTORES; i++) {
        if (vetor_tutores[i].tutor_ocupado == 1) {
            printf("ID Tutor: %d\n", vetor_tutores[i].id_tutor);
            printf("Nome: %s\n", vetor_tutores[i].nome_tutor);
            printf("Sexo: %c\n", vetor_tutores[i].sexo);

            printf("CPF: ");
            for(int j = 0; j < 11; j++) {
                printf("%d", vetor_tutores[i].cpf[j]);
            }
            printf("\n");

            printf("Animais: ");
            for(int j = 0; j < 10; j++) {
                if(vetor_tutores[i].id_animais[j] != 0) {
                    printf("%d ", vetor_tutores[i].id_animais[j]);
                }
            }
            printf("\n");

            printf("CEP: ");
            for(int j = 0; j < 8; j++) {
                printf("%d", vetor_tutores[i].endereco.cep[j]);
            }
            printf("\n");

            printf("Rua: %s\n", vetor_tutores[i].endereco.rua);
            printf("Bairro: %s\n", vetor_tutores[i].endereco.bairro);
            printf("Cidade: %s\n", vetor_tutores[i].endereco.cidade);
            printf("Estado: %s\n", vetor_tutores[i].endereco.estado);
            printf("N�mero: %s\n", vetor_tutores[i].endereco.numero_casa);

            printf("Telefone: ");
            for(int j = 0; j < 11; j++) {
                printf("%d", vetor_tutores[i].contato.telefone[j]);
            }
            printf("\n");

            printf("Email: %s\n\n", vetor_tutores[i].contato.email);
        }
    }
    system("pause");
}

void tela_pesquisar() {
    int continuar, id;
    do {
        system("cls");
        printf("--- Pesquisar Animal ---\n");
        id = controladores_id("Digite o ID do animal: ");

        Animal a = cadastro_pesquisar_animal(id);

        if (a.ocupado == 1) {
            printf("\nAnimal encontrado:\n");
            printf("ID: %d\n", a.id_animal);
            printf("Tutor ID: %d\n", a.id_tutor);
            printf("Nome: %s\n", a.nome_animal);
            printf("Esp�cie: %s\n", a.especie);
            printf("Sexo: %c\n", a.sexo);
            printf("Ra�a: %s\n", a.raca);
            printf("Vacinas: %s\n", a.vacinas);
            printf("Vermifugado: %c\n", a.vermifugado);
            printf("Hist�rico: %s\n", a.historico);
            printf("Castrado: %c\n", a.castrado);
            printf("Adotado: %d\n", a.adotado);
        } else {
            printf("\nAnimal n�o encontrado.\n");
        }
        system("pause");
        continuar = tela_mensagem("Deseja pesquisar outro animal?");
    } while (continuar == 1);
}

void tela_pesquisar_tutor() {
    int continuar, id;
    do {
        system("cls");
        printf("--- Pesquisar Tutor ---\n");
        id = controladores_id("Digite o ID do tutor: ");

        Tutor t = cadastro_pesquisar_tutor(id);

        if (t.tutor_ocupado == 1) {
            printf("\nTutor encontrado:\n");
            printf("ID: %d\n", t.id_tutor);
            printf("Nome: %s\n", t.nome_tutor);
            printf("Sexo: %c\n", t.sexo);

            printf("CPF: ");
            for(int j = 0; j < 11; j++) {
                printf("%d", t.cpf[j]);
            }
            printf("\n");

            printf("Animais: ");
            for(int j = 0; j < 10 && t.id_animais[j] != 0; j++) {
                printf("%d ", t.id_animais[j]);
            }
            printf("\n");

            printf("CEP: ");
            for(int j = 0; j < 8; j++) {
                printf("%d", t.endereco.cep[j]);
            }
            printf("\n");

            printf("Rua: %s\n", t.endereco.rua);
            printf("Bairro: %s\n", t.endereco.bairro);
            printf("Cidade: %s\n", t.endereco.cidade);
            printf("Estado: %s\n", t.endereco.estado);
            printf("N�mero: %s\n", t.endereco.numero_casa);

            printf("Telefone: ");
            for(int j = 0; j < 11; j++) {
                printf("%d", t.contato.telefone[j]);
            }
            printf("\n");

            printf("Email: %s\n", t.contato.email);
        } else {
            printf("\nTutor n�o encontrado.\n");
        }
        system("pause");
        continuar = tela_mensagem("Deseja pesquisar outro tutor?");
    } while (continuar == 1);
}

void tela_remover() {
    int continuar, id;

    do {
        system("cls");
        printf("--- Remover Animal ---\n");
        id = controladores_id("Digite o ID do animal a ser removido: ");

        if (cadastro_remover_animal(id)) {
            printf("Animal removido com sucesso.\n");
        } else {
            printf("Animal n�o encontrado.\n");
        }

        system("pause");
        continuar = tela_mensagem("Deseja remover outro animal?");
    } while (continuar == 1);
}

void tela_remover_tutor() {
    int continuar, id;
    do {
        system("cls");
        printf("--- Remover Tutor ---\n");
        id = controladores_id("Digite o ID do tutor a ser removido: ");

        if (cadastro_remover_tutor(id)) {
            printf("Tutor removido com sucesso.\n");
        } else {
            printf("Tutor n�o encontrado ou opera��o cancelada.\n");
        }

        system("pause");
        continuar = tela_mensagem("Deseja remover outro tutor?");
    } while (continuar == 1);
}

int tela_sair() {
    system("cls");
    return tela_mensagem("Deseja realmente sair?");
}

int tela_mensagem(char *mensagem) {
    char resp;
    do {
        printf("%s (s/n): ", mensagem);
        scanf(" %c", &resp);
        fflush(stdin);
        resp = toupper(resp);

        if (resp == 'S') return 1;
        if (resp == 'N') return 0;

        printf("Erro: Digite apenas 's' ou 'n'!\n");
    } while (1);
}

void tela_cadastrar_processo_adotivo() {
    FILE *file = fopen("processos.txt", "a");
    if (file == NULL) {
        printf("Erro ao abrir arquivo de processos.\n");
        return;
    }

    ProcessoAdotivo processo;
    int opcao;

    marcas(1);
    printf("--- Cadastro de Processo Adotivo ---\n");

    processo.id_processo = gerar_id_proximo("processos.txt", 0);
    printf("ID do Processo gerado: %d\n", processo.id_processo);

    // Valida��o Animal
    int animal_valido = 0;
    while (!animal_valido) {
        processo.id_animal = controladores_id("Digite o ID do Animal: ");

        if (verificar_id_animal_existente(processo.id_animal)) {
            animal_valido = 1;
        } else {
            printf("Animal n�o encontrado! Cadastre o animal primeiro.\n");
            system("pause");
            fclose(file);
            return;
        }
    }

    // Valida��o Tutor
    int tutor_valido = 0;
    while (!tutor_valido) {
        processo.id_tutor = controladores_id("Digite o ID do Tutor: ");

        if (verificar_id_tutor_existente(processo.id_tutor)) {
            tutor_valido = 1;
        } else {
            printf("Tutor n�o encontrado! Cadastre o tutor primeiro.\n");
            system("pause");
            fclose(file);
            return;
        }
    }

    printf("Data da ado��o (dd mm aaaa): ");
    scanf("%d %d %d", &processo.data_adocao.dia, &processo.data_adocao.mes, &processo.data_adocao.ano);
    getchar();

    printf("Relat�rio de adapta��o: ");
    scanf(" %299[^\n]", processo.relatorio_adaptacao);
    fflush(stdin);

    printf("Agendamentos de visitas: ");
    scanf(" %199[^\n]", processo.agendamentos);
    fflush(stdin);

    printf("Atualiza��o de dados m�dicos: ");
    scanf(" %199[^\n]", processo.dados_medicos);
    fflush(stdin);

    processo.ativo = 1;

    fprintf(file, "%d;%d;%d;%d/%d/%d;%s;%s;%s;%d\n",
        processo.id_processo, processo.id_animal, processo.id_tutor,
        processo.data_adocao.dia, processo.data_adocao.mes, processo.data_adocao.ano,
        processo.relatorio_adaptacao, processo.agendamentos, processo.dados_medicos, processo.ativo);

    fclose(file);
    printf("Processo adotivo cadastrado com sucesso!\n");
    system("pause");
}

void tela_consultar_processos_adotivos() {
    FILE *file = fopen("processos.txt", "r");
    if (file == NULL) {
        printf("Erro ao abrir arquivo de processos.\n");
        system("pause");
        return;
    }

    ProcessoAdotivo processo;
    char linha[1024];
    char data[15];

    system("cls");
    marcas(1);
    printf("\n--- Processos Adotivos ---\n");

    while (fgets(linha, sizeof(linha), file) != NULL) {
        if (sscanf(linha, "%d;%d;%d;%14[^;];%299[^;];%199[^;];%199[^;];%d",
            &processo.id_processo, &processo.id_animal, &processo.id_tutor,
            data, processo.relatorio_adaptacao, processo.agendamentos, processo.dados_medicos, &processo.ativo) == 8) {

            sscanf(data, "%d/%d/%d", &processo.data_adocao.dia, &processo.data_adocao.mes, &processo.data_adocao.ano);

            printf("\nID Processo: %d | ID Animal: %d | ID Tutor: %d\n",
                   processo.id_processo, processo.id_animal, processo.id_tutor);
            printf("Data da ado��o: %02d/%02d/%04d\n",
                   processo.data_adocao.dia, processo.data_adocao.mes, processo.data_adocao.ano);
            printf("Relat�rio de adapta��o: %s\n", processo.relatorio_adaptacao);
            printf("Agendamentos: %s\n", processo.agendamentos);
            printf("Dados m�dicos: %s\n", processo.dados_medicos);
            printf("Status: %s\n", (processo.ativo == 1 ? "Ativo" : "Inativo"));
            printf("----------------------------------------\n");
        } else {
            printf("\n[Erro] Linha mal formatada: %s", linha);
        }
    }

    fclose(file);
    system("pause");
}

void tela_cadastrar_ocorrencia() {
    FILE *file = fopen("ocorrencias.txt", "a");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo de ocorr�ncias.\n");
        return;
    }

    Ocorrencia ocorrencia;

    marcas(1);
    printf("--- Cadastro de Ocorrencia ---\n");

    ocorrencia.id_ocorrencia = gerar_id_proximo("ocorrencias.txt", 0);
    printf("ID da Ocorr�ncia gerado: %d\n", ocorrencia.id_ocorrencia);

    ocorrencia.id_processo = controladores_id("Digite o ID do Processo Adotivo: ");
    ocorrencia.id_tutor = controladores_id("Digite o ID do Tutor: ");

    // Valida��o do tutor
    if (!verificar_id_tutor_existente(ocorrencia.id_tutor)) {
        printf("ERRO! N�o foi encontrado o tutor com este ID. Cadastre o tutor primeiro.\n");
        system("pause");
        fclose(file);
        return;
    }

    // Valida��o do animal via processo
    int processo_valido = 0;
    int id_animal = -1;
    FILE *fp = fopen("processos.txt", "r");
    if (fp) {
        char linha[1024];
        while (fgets(linha, sizeof(linha), fp) != NULL) {
            int id_processo, id_animal_temp, id_tutor, ativo;
            char data[15], relatorio[300], agendamento[200], dados[200];
            if (sscanf(linha, "%d;%d;%d;%14[^;];%299[^;];%199[^;];%199[^;];%d",
                &id_processo, &id_animal_temp, &id_tutor, data, relatorio, agendamento, dados, &ativo) == 8) {
                if (id_processo == ocorrencia.id_processo) {
                    processo_valido = 1;
                    id_animal = id_animal_temp;
                    break;
                }
            }
        }
        fclose(fp);
    }

    if (!processo_valido) {
        printf("ERRO! Processo adotivo n�o encontrado.\n");
        system("pause");
        fclose(file);
        return;
    }

    if (!verificar_id_animal_existente(id_animal)) {
        printf("ERRO! Animal associado ao processo n�o encontrado. Cadastre o animal primeiro.\n");
        system("pause");
        fclose(file);
        return;
    }

    getchar();

    printf("Descreva o ocorrido: ");
    scanf(" %299[^\n]", ocorrencia.descricao);
    fflush(stdin);

    printf("Data da ocorr�ncia (dd mm aaaa): ");
    scanf("%d %d %d", &ocorrencia.data_ocorrencia.dia, &ocorrencia.data_ocorrencia.mes, &ocorrencia.data_ocorrencia.ano);
    getchar();

    printf("A��o tomada: ");
    scanf(" %299[^\n]", ocorrencia.acao);
    fflush(stdin);

    ocorrencia.ativo = 1;

    fprintf(file, "%d;%d;%d;%s;%d/%d/%d;%s;%d\n",
        ocorrencia.id_ocorrencia, ocorrencia.id_processo, ocorrencia.id_tutor,
        ocorrencia.descricao, ocorrencia.data_ocorrencia.dia, ocorrencia.data_ocorrencia.mes,
        ocorrencia.data_ocorrencia.ano, ocorrencia.acao, ocorrencia.ativo);

    fclose(file);
    printf("Ocorr�ncia registrada com sucesso!\n");
    system("pause");
}

void tela_consultar_ocorrencias() {
    FILE *file = fopen("ocorrencias.txt", "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo de ocorr�ncias.\n");
        system("pause");
        return;
    }

    Ocorrencia ocorrencia;
    char linha[1024];

    marcas(1);
    printf("\n--- Ocorr�ncias ---\n");

    while (fgets(linha, sizeof(linha), file)) {
        if (sscanf(linha, "%d;%d;%d;%299[^;];%d/%d/%d;%299[^;];%d",
            &ocorrencia.id_ocorrencia, &ocorrencia.id_processo, &ocorrencia.id_tutor,
            ocorrencia.descricao, &ocorrencia.data_ocorrencia.dia, &ocorrencia.data_ocorrencia.mes,
            &ocorrencia.data_ocorrencia.ano, ocorrencia.acao, &ocorrencia.ativo) == 9) {

            printf("\nID Ocorr�ncia: %d\nProcesso: %d | Tutor: %d\n",
                   ocorrencia.id_ocorrencia, ocorrencia.id_processo, ocorrencia.id_tutor);
            printf("Data: %02d/%02d/%04d\n",
                   ocorrencia.data_ocorrencia.dia, ocorrencia.data_ocorrencia.mes, ocorrencia.data_ocorrencia.ano);
            printf("Descri��o: %s\n", ocorrencia.descricao);
            printf("A��o: %s\n", ocorrencia.acao);
            printf("Status: %s\n", ocorrencia.ativo == 1 ? "Ativa" : "Inativa");
            printf("----------------------------------------\n");
        } else {
            printf("\n[Erro] Linha mal formatada: %s", linha);
        }
    }

    fclose(file);
    system("pause");
}

//////////////////////// FUN��ES ///////////////////////////////////////////

int controladores_inteiros(char* mensagem) {
    int valor;
    int resultado;
    do {
        printf("%s", mensagem);
        resultado = scanf("%d", &valor);
        fflush(stdin);
        if (resultado != 1) {
            printf("Erro: Digite um n�mero inteiro v�lido.\n");
        }
    } while (resultado != 1);
    return valor;
}

int controladores_id(char* mensagem) {
    int id;
    do {
        id = controladores_inteiros(mensagem);
        if (id <= 0) {
            printf("Erro: O ID deve ser um n�mero positivo.\n");
        }
    } while (id <= 0);
    return id;
}

int gerar_proximo_id_animal() {
    int max_id = 0;
    for (int i = 0; i < NUM_MAX_ANIMAIS; i++) {
        if (vetor_animais[i].ocupado == 1 && vetor_animais[i].id_animal > max_id) {
            max_id = vetor_animais[i].id_animal;
        }
    }
    return max_id + 1;
}

int gerar_proximo_id_tutor() {
    int max_id = 0;
    for (int i = 0; i < NUM_MAX_TUTORES; i++) {
        if (vetor_tutores[i].tutor_ocupado == 1 && vetor_tutores[i].id_tutor > max_id) {
            max_id = vetor_tutores[i].id_tutor;
        }
    }
    return max_id + 1;
}

int cadastro_verificar_capacidade_maxima_animais() {
    return total_animais >= NUM_MAX_ANIMAIS;
}

int cadastro_verificar_capacidade_maxima_tutores() {
    return total_tutores >= NUM_MAX_TUTORES;
}

void cadastro_inicializar_animais() {
    total_animais = 0;
    for (int i = 0; i < NUM_MAX_ANIMAIS; i++) {
        vetor_animais[i].ocupado = 0;
        vetor_animais[i].adotado = 0;
    }
}

void cadastro_inicializar_tutores() {
    total_tutores = 0;
    for (int i = 0; i < NUM_MAX_TUTORES; i++) {
        vetor_tutores[i].tutor_ocupado = 0;
    }
}

void cadastro_inicializar_arquivo_tutores() {
    FILE *fp = fopen(caminho_arquivo_tutores, "r");
    if (fp == NULL) {
        fp = fopen(caminho_arquivo_tutores, "w");
        fprintf(fp, "%d\n", total_tutores);
        fclose(fp);
    } else {
        fclose(fp);
    }
}

void cadastro_inicializar_arquivo_animais() {
    FILE *fp = fopen(caminho_arquivo_animais, "r");
    if (fp == NULL) {
        fp = fopen(caminho_arquivo_animais, "w");
        fprintf(fp, "%d\n", total_animais);
        fclose(fp);
    } else {
        fclose(fp);
    }
}

Tutor animais_id_tutor_inicializador() {
    Tutor inicializador;

    inicializador.tutor_ocupado = 0;
    strcpy(inicializador.nome_tutor, "");
    inicializador.id_tutor = 0;

    for(int i = 0; i < 10; i++) {
        inicializador.id_animais[i] = 0;
    }

    for(int i = 0; i < 11; i++) {
        inicializador.cpf[i] = 0;
    }

    inicializador.sexo = ' ';

    for(int i = 0; i < 8; i++) {
        inicializador.endereco.cep[i] = 0;
    }
    strcpy(inicializador.endereco.rua, "");
    strcpy(inicializador.endereco.bairro, "");
    strcpy(inicializador.endereco.cidade, "");
    strcpy(inicializador.endereco.estado, "");
    strcpy(inicializador.endereco.numero_casa, "");

    for(int i = 0; i < 11; i++) {
        inicializador.contato.telefone[i] = 0;
    }
    strcpy(inicializador.contato.email, "");

    return inicializador;
}

void cadastro_carregar_dados_arquivo_tutores() {
    FILE *fp = fopen(caminho_arquivo_tutores, "r");
    if (fp == NULL) return;

    fscanf(fp, "%d\n", &total_tutores);

    for (int i = 0; i < total_tutores; i++) {
        Tutor tutor = {0};

        fgets(tutor.nome_tutor, 256, fp);
        tutor.nome_tutor[strcspn(tutor.nome_tutor, "\n")] = 0;

        fscanf(fp, "%d\n", &tutor.id_tutor);

        for(int j = 0; j < 10; j++){
            fscanf(fp, "%d", &tutor.id_animais[j]);
        }
        fscanf(fp, "\n");

        for(int j = 0; j < 11; j++) {
            fscanf(fp, "%1d", &tutor.cpf[j]);
        }
        fscanf(fp, "\n");

        fscanf(fp, "%c\n", &tutor.sexo);

        for(int j = 0; j < 8; j++){
            fscanf(fp, "%1d", &tutor.endereco.cep[j]);
        }
        fscanf(fp, "\n");

        fgets(tutor.endereco.rua, 120, fp);
        tutor.endereco.rua[strcspn(tutor.endereco.rua, "\n")] = 0;

        fgets(tutor.endereco.bairro, 120, fp);
        tutor.endereco.bairro[strcspn(tutor.endereco.bairro, "\n")] = 0;

        fgets(tutor.endereco.cidade, 80, fp);
        tutor.endereco.cidade[strcspn(tutor.endereco.cidade, "\n")] = 0;

        fgets(tutor.endereco.estado, 50, fp);
        tutor.endereco.estado[strcspn(tutor.endereco.estado, "\n")] = 0;

        fgets(tutor.endereco.numero_casa, 50, fp);
        tutor.endereco.numero_casa[strcspn(tutor.endereco.numero_casa, "\n")] = 0;

        for(int j = 0; j < 11; j++) {
            fscanf(fp, "%1d", &tutor.contato.telefone[j]);
        }
        fscanf(fp, "\n");

        fgets(tutor.contato.email, 120, fp);
        tutor.contato.email[strcspn(tutor.contato.email, "\n")] = 0;

        tutor.tutor_ocupado = 1;
        vetor_tutores[i] = tutor;
    }
    fclose(fp);
}

void cadastro_carregar_dados_arquivo_animais() {
    FILE *fp = fopen(caminho_arquivo_animais, "r");
    if (fp == NULL) return;

    fscanf(fp, "%d ", &total_animais);

    for (int i = 0; i < total_animais; i++) {
        Animal a;

        fscanf(fp, "%d %d ", &a.id_animal, &a.id_tutor);
        a.adotado = (a.id_tutor != 0) ? 1 : 0;

        fgets(a.nome_animal, 256, fp);
        a.nome_animal[strcspn(a.nome_animal, "\n")] = 0;

        fgets(a.especie, 256, fp);
        a.especie[strcspn(a.especie, "\n")] = 0;

        fscanf(fp, "%c ", &a.sexo);

        fgets(a.raca, 256, fp);
        a.raca[strcspn(a.raca, "\n")] = 0;

        fgets(a.vacinas, 512, fp);
        a.vacinas[strcspn(a.vacinas, "\n")] = 0;

        fscanf(fp, "%c ", &a.vermifugado);

        fgets(a.historico, 512, fp);
        a.historico[strcspn(a.historico, "\n")] = 0;

        fscanf(fp, "%c ", &a.castrado);

        a.ocupado = 1;
        vetor_animais[i] = a;
    }
    fclose(fp);
}

void cadastro_salvar_dados_arquivo_tutores() {
    FILE *fp = fopen(caminho_arquivo_tutores, "w");
    if (fp == NULL) return;

    fprintf(fp, "%d\n", total_tutores);

    for (int i = 0; i < NUM_MAX_TUTORES; i++) {
        if (vetor_tutores[i].tutor_ocupado == 1) {
            fprintf(fp, "%s\n", vetor_tutores[i].nome_tutor);
            fprintf(fp, "%d\n", vetor_tutores[i].id_tutor);

            for(int j = 0; j < 10; j++) {
                fprintf(fp, "%d ", vetor_tutores[i].id_animais[j]);
            }
            fprintf(fp, "\n");

            for(int j = 0; j < 11; j++) {
                fprintf(fp, "%d", vetor_tutores[i].cpf[j]);
            }
            fprintf(fp, "\n");

            fprintf(fp, "%c\n", vetor_tutores[i].sexo);

            for(int j = 0; j < 8; j++) {
                fprintf(fp, "%d", vetor_tutores[i].endereco.cep[j]);
            }
            fprintf(fp, "\n");

            fprintf(fp, "%s\n", vetor_tutores[i].endereco.rua);
            fprintf(fp, "%s\n", vetor_tutores[i].endereco.bairro);
            fprintf(fp, "%s\n", vetor_tutores[i].endereco.cidade);
            fprintf(fp, "%s\n", vetor_tutores[i].endereco.estado);
            fprintf(fp, "%s\n", vetor_tutores[i].endereco.numero_casa);

            for(int j = 0; j < 11; j++) {
                fprintf(fp, "%d", vetor_tutores[i].contato.telefone[j]);
            }
            fprintf(fp, "\n");

            fprintf(fp, "%s\n", vetor_tutores[i].contato.email);
        }
    }
    fclose(fp);
}

void cadastro_salvar_dados_arquivo_animais() {
    FILE *fp = fopen(caminho_arquivo_animais, "w");
    if (fp == NULL) return;

    fprintf(fp, "%d\n", total_animais);

    for (int i = 0; i < NUM_MAX_ANIMAIS; i++) {
        if (vetor_animais[i].ocupado == 1) {
            fprintf(fp, "%d\n%d\n", vetor_animais[i].id_animal, vetor_animais[i].id_tutor);
            fprintf(fp, "%s\n", vetor_animais[i].nome_animal);
            fprintf(fp, "%s\n", vetor_animais[i].especie);
            fprintf(fp, "%c\n", vetor_animais[i].sexo);
            fprintf(fp, "%s\n", vetor_animais[i].raca);
            fprintf(fp, "%s\n", vetor_animais[i].vacinas);
            fprintf(fp, "%c\n", vetor_animais[i].vermifugado);
            fprintf(fp, "%s\n", vetor_animais[i].historico);
            fprintf(fp, "%c\n", vetor_animais[i].castrado);
        }
    }
    fclose(fp);
}

int verificar_id_tutor_existente(int id) {
    for (int i = 0; i < NUM_MAX_TUTORES; i++) {
        if (vetor_tutores[i].tutor_ocupado == 1 && vetor_tutores[i].id_tutor == id)
        return 1;
    }
    return 0;
}

int verificar_id_animal_existente(int id) {
    for (int i = 0; i < NUM_MAX_ANIMAIS; i++) {
        if (vetor_animais[i].ocupado == 1 && vetor_animais[i].id_animal == id)
            return 1;
    }
    return 0;
}

int verificar_id_tutor_existente2(int id_tutor) {
    FILE *fp = fopen(caminho_arquivo_tutores, "r");
    if (fp == NULL) return 0;

    int total, id;
    fscanf(fp, "%d", &total);

    for (int i = 0; i < total; i++) {
        fscanf(fp, "%d", &id);
        if (id == id_tutor) {
            fclose(fp);
            return 1;
        }
        char lixo[256];
        fgets(lixo, 256, fp);
        fgets(lixo, 256, fp);
        fgets(lixo, 256, fp);
        fgets(lixo, 256, fp);
    }
    fclose(fp);
    return 0;
}

void cadastro_inserir_tutor(Tutor tutor) {
    for (int i = 0; i < NUM_MAX_TUTORES; i++) {
        if (vetor_tutores[i].tutor_ocupado == 1 && vetor_tutores[i].id_tutor == tutor.id_tutor) {
            printf("\nErro: J� existe um tutor com este ID.\n");
            system("pause");
            return;
        }
    }

    for (int i = 0; i < NUM_MAX_TUTORES; i++) {
        if (vetor_tutores[i].tutor_ocupado == 0) {
            vetor_tutores[i] = tutor;
            vetor_tutores[i].tutor_ocupado = 1;
            total_tutores++;
            printf("\nTutor cadastrado com sucesso!\n");
            system("pause");
            break;
        }
    }
}

void cadastro_inserir_animal(Animal a) {
    for (int i = 0; i < NUM_MAX_ANIMAIS; i++) {
        if (vetor_animais[i].ocupado == 1 && vetor_animais[i].id_animal == a.id_animal) {
            printf("\nErro: J� existe um animal com este ID.\n");
            system("pause");
            return;
        }
    }
    for (int i = 0; i < NUM_MAX_ANIMAIS; i++) {
        if (vetor_animais[i].ocupado == 0) {
            vetor_animais[i] = a;
            vetor_animais[i].ocupado = 1;
            total_animais++;
            printf("\nAnimal cadastrado com sucesso!\n");
            system("pause");
            break;
        }
    }
}

Tutor cadastro_pesquisar_tutor(int id) {
    for (int i = 0; i < NUM_MAX_TUTORES; i++) {
        if (vetor_tutores[i].tutor_ocupado == 1 && vetor_tutores[i].id_tutor == id) {
            return vetor_tutores[i];
        }
    }

    Tutor vazio = {0};
    return vazio;
}

Animal cadastro_pesquisar_animal(int id) {
    for (int i = 0; i < NUM_MAX_ANIMAIS; i++) {
        if (vetor_animais[i].ocupado == 1 && vetor_animais[i].id_animal == id) {
            return vetor_animais[i];
        }
    }

    Animal vazio = {0};
    return vazio;
}

int tela_limite_animais(int id_tutor) {
    system("cls");
    printf("\t\t\t\tERRO! O tutor em quest�o atingiu o limite de animais alocados.\n\n");
    printf("\t\t\t\tSelecione como proceder:\n");
    printf("\t\t\t\t1 - Deletar um animal do tutor vigente.\n");
    printf("\t\t\t\t2 - Interromper cadastro.\n");
    printf("\t\t\t\tOpcao: ");

    int opcao;
    scanf("%d", &opcao);
    fflush(stdin);

    if (opcao == 1) {
        Tutor tutor = cadastro_pesquisar_tutor(id_tutor);
        if (tutor.tutor_ocupado == 0) {
            printf("\t\t\t\tTutor n�o encontrado.\n");
            system("pause");
            return 0;
        }

        printf("\t\t\t\tIDs dos animais:\n");
        for (int i = 0; i < 10; i++) {
            if (tutor.id_animais[i] != 0) {
                printf("\t\t\t\t%d\n", tutor.id_animais[i]);
            }
        }

        int id_animal_remover;
        printf("\t\t\t\tDigite o ID do animal a ser removido: ");
        scanf("%d", &id_animal_remover);
        fflush(stdin);

        // Remove o animal do tutor
        for (int i = 0; i < NUM_MAX_TUTORES; i++) {
            if (vetor_tutores[i].tutor_ocupado == 1 && vetor_tutores[i].id_tutor == id_tutor) {
                for (int j = 0; j < 10; j++) {
                    if (vetor_tutores[i].id_animais[j] == id_animal_remover) {
                        vetor_tutores[i].id_animais[j] = 0;
                        break;
                    }
                }
                break;
            }
        }

        // Atualiza o status do animal
        for (int i = 0; i < NUM_MAX_ANIMAIS; i++) {
            if (vetor_animais[i].ocupado == 1 && vetor_animais[i].id_animal == id_animal_remover) {
                vetor_animais[i].adotado = 0;
                vetor_animais[i].id_tutor = 0;
                break;
            }
        }

        return 1;
    } else {
        return 0;
    }
}

int tela_exclusao_tutor_opcoes() {
    system("cls");
    printf("\t\t\t\tOp��es de exclus�o de tutor\n\n");
    printf("\t\t\t\t1- Excluir o tutor e manter os animais (Recomendado somente no caso de recadastro ou realoca��o do animal).\n");
    printf("\t\t\t\t2- Excluir todos os animais associados ao tutor.\n");
    printf("\t\t\t\tOpcao: ");

    int opcao;
    scanf("%d", &opcao);
    fflush(stdin);

    return opcao;
}

int cadastro_remover_tutor(int id) {
    for (int i = 0; i < NUM_MAX_TUTORES; i++) {
        if (vetor_tutores[i].tutor_ocupado == 1 && vetor_tutores[i].id_tutor == id) {
            int opcao = tela_exclusao_tutor_opcoes();

            if (opcao == 1) {
                // Mant�m os animais, apenas remove o tutor e desassocia os animais
                for (int j = 0; j < 10; j++) {
                    int id_animal = vetor_tutores[i].id_animais[j];
                    if (id_animal != 0) {
                        for (int k = 0; k < NUM_MAX_ANIMAIS; k++) {
                            if (vetor_animais[k].ocupado == 1 && vetor_animais[k].id_animal == id_animal) {
                                vetor_animais[k].adotado = 0;
                                vetor_animais[k].id_tutor = 0;
                                break;
                            }
                        }
                    }
                }
                vetor_tutores[i].tutor_ocupado = 0;
                total_tutores--;
                return 1;
            } else if (opcao == 2) {
                // Remove o tutor e todos os animais associados
                for (int j = 0; j < 10; j++) {
                    int id_animal = vetor_tutores[i].id_animais[j];
                    if (id_animal != 0) {
                        cadastro_remover_animal(id_animal);
                    }
                }
                vetor_tutores[i].tutor_ocupado = 0;
                total_tutores--;
                return 1;
            } else {
                return 0; // Opera��o cancelada
            }
        }
    }
    return 0;
}

int cadastro_remover_animal(int id) {
    // Encontra o tutor associado e remove o ID do animal
    for (int i = 0; i < NUM_MAX_TUTORES; i++) {
        if (vetor_tutores[i].tutor_ocupado == 1) {
            for (int j = 0; j < 10; j++) {
                if (vetor_tutores[i].id_animais[j] == id) {
                    vetor_tutores[i].id_animais[j] = 0;
                    break;
                }
            }
        }
    }

    // Remove o animal
    for (int i = 0; i < NUM_MAX_ANIMAIS; i++) {
        if (vetor_animais[i].ocupado == 1 && vetor_animais[i].id_animal == id) {
            vetor_animais[i].ocupado = 0;
            total_animais--;
            return 1;
        }
    }
    return 0;
}

int gerar_id_proximo(const char *nome_arquivo, int indice_id) {
    FILE *file = fopen(nome_arquivo, "r");
    if (!file) return 1;  // Retorna 1 se o arquivo n�o existir (primeiro ID)

    int maior_id = 0;
    char linha[1024];

    while (fgets(linha, sizeof(linha), file) != NULL) {
        int id_atual;
        // Tenta extrair o ID do in�cio da linha
        if (sscanf(linha, "%d", &id_atual) == 1) {
            if (id_atual > maior_id) {
                maior_id = id_atual;
            }
        }
    }

    fclose(file);
    return maior_id + 1;
}

int inserir_id_animal_em_tutor(int id_animal, int id_tutor) {
    for (int i = 0; i < NUM_MAX_TUTORES; i++) {
        if (vetor_tutores[i].tutor_ocupado == 1 && vetor_tutores[i].id_tutor == id_tutor) {
            int count = 0;
            for (int j = 0; j < 10; j++) {
                if (vetor_tutores[i].id_animais[j] != 0) {
                    count++;
                }
            }

            if (count >= 10) {
                if (tela_limite_animais(id_tutor) == 1) {
                    return inserir_id_animal_em_tutor(id_animal, id_tutor);
                } else {
                    return 0;
                }
            }

            for (int j = 0; j < 10; j++) {
                if (vetor_tutores[i].id_animais[j] == 0) {
                    vetor_tutores[i].id_animais[j] = id_animal;
                    for (int k = 0; k < NUM_MAX_ANIMAIS; k++) {
                        if (vetor_animais[k].ocupado == 1 && vetor_animais[k].id_animal == id_animal) {
                            vetor_animais[k].adotado = 1;
                            vetor_animais[k].id_tutor = id_tutor;
                            break;
                        }
                    }
                    return 1;
                }
            }
        }
    }
    return 0;
}
