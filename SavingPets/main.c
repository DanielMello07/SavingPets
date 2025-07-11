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

// Prot�tipos de fun��es
void cadastro_inicializar_animais();
void cadastro_initializar_tutores();
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
int cadastro_inserir_tutor(Tutor tutor);
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
int animal_pertence_ao_tutor(int id_animal, int id_tutor);

// Prot�tipos das fun��es de tela
char tela_ler_sexo(const char *mensagem);
void tela_ler_cpf(int cpf[11]);
void tela_ler_cep(int cep[8]);
void tela_ler_telefone(int telefone[11]);
void tela_centralizar_pausa();
void tela_marcas(int tela);
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
    tela_marcas(0);
    tela_centralizar_pausa();

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
                printf("\n\n\t\t\t\tOp��o Inv�lida !!! \n\n");
                tela_centralizar_pausa();
        }
    } while(sair == 0);

    cadastro_salvar_dados_arquivo_animais();
    cadastro_salvar_dados_arquivo_tutores();

    system("cls");
    printf("\t\t\t\tFim da execu��o do programa!\n");

    return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////// TELAS //////////////////////////////////////////

void tela_marcas(int tela) {
    if(tela == 0){
        printf("Bem vindo ao:                                                                          \n");
        printf("\t\t\t\t                                                                             \n");
        printf("\t\t\t\t                            @@@@@@@@@             @@@@@@@@@@                  \n");
        printf("\t\t\t\t                          @@@@@@@@@@@@@         @@@@@@@@@@@@@                 \n");
        printf("\t\t\t\t                         @@@@@@@@@@@@@@@@      @@@@@@@@@@@@@@@                \n");
        printf("\t\t\t\t                         @@@@@@@@@@@@@@@@@    @@@@@@@@@@@@@@@@@              \n");
        printf("\t\t\t\t                         @@@@@@@@@@@@@@@@@   @@@@@@@@@@@@@@@@@@              \n");
        printf("\t\t\t\t                         @@@@@@@@@@@@@@@@@   @@@@@@@@@@@@@@@@@                \n");
        printf("\t\t\t\t                          @@@@@@@@@@@@@@@@   @@@@@@@@@@@@@@@@@                \n");
        printf("\t\t\t\t                           @@@@@@@@@@@@@@@    @@@@@@@@@@@@@@@    @@@@@@@     \n");
        printf("\t\t\t\t               @@@@@@@@@     @@@@@@@@@@@@      @@@@@@@@@@@@   @@@@@@@@@@@@   \n");
        printf("\t\t\t\t             @@@@@@@@@@@@@     @@@@@@@@          @@@@@@@@    @@@@@@@@@@@@@@  \n");
        printf("\t\t\t\t             @@@@@@@@@@@@@@@                               @@@@@@@@@@@@@@@@  \n");
        printf("\t\t\t\t             @@@@@@@@@@@@@@@@                              @@@@@@@@@@@@@@@@  \n");
        printf("\t\t\t\t             @@@@@@@@@@@@@@@@@                            @@@@@@@@@@@@@@@@@  \n");
        printf("\t\t\t\t             @@@@@@@@@@@@@@@@@           @@@@@@@          @@@@@@@@@@@@@@@@@  \n");
        printf("\t\t\t\t              @@@@@@@@@@@@@@@@      @@@@@@@@@@@@@@@@@     @@@@@@@@@@@@@@@@   \n");
        printf("\t\t\t\t               @@@@@@@@@@@@@@@   @@@@@@@@@@@@@@@@@@@@@@    @@@@@@@@@@@@@     \n");
        printf("\t\t\t\t                @@@@@@@@@@@@  @@@@@@@@@@@@@@@@@@@@@@@@@@@  @@@@@@@@@@       \n");
        printf("\t\t\t\t                    @@@@@@   @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@                  \n");
        printf("\t\t\t\t                            @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@                 \n");
        printf("\t\t\t\t                           @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@                \n");
        printf("\t\t\t\t                          @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@              \n");
        printf("\t\t\t\t                         @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@             \n");
        printf("\t\t\t\t                        @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@            \n");
        printf("\t\t\t\t                        @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@            \n");
        printf("\t\t\t\t                        @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@           \n");
        printf("\t\t\t\t                         @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@            \n");
        printf("\t\t\t\t                          @@@@@@@@@@@@               @@@@@@@@@@@@             \n");
        printf("\t\t\t\t                                                                           \n\n\n");

        printf("\t\t\t\t       _______ _______ _    _ _____ __   _  ______  _____  _______ _______ _______\n");
        printf("\t\t\t\t       |______ |_____|  \\  /    |   | \\  | |  ____ |_____] |______    |    |______\n");
        printf("\t\t\t\t       ______| |     |   \\/   __|__ |  \\_| |_____| |       |______    |    ______|\n");
        printf("                                                                           \n");

        printf("\t\t\t\t\t       Sistema Gerenciador de P�s ado��o de Animais Resgatados\n\n");
    } else if(tela == 1) {
        printf("\t\t\t\t\t\t\t                   /\\_/\\   \n");
        printf("\t\t\t\t\t\t\t                  ( o.o )  \n");
        printf("\t\t\t\t\t\t\t                   > ^ <   \n\n");
    } else if(tela == 2) {
        printf("\t\t\t\t\t\t\t                  /^ ^\\ \n");
        printf("\t\t\t\t\t\t\t                 / 0 0 \\ \n");
        printf("\t\t\t\t\t\t\t                 V\\ Y /V \n");
        printf("\t\t\t\t\t\t\t                  / - \\  \n");
        printf("\t\t\t\t\t\t\t                 |    \\\\\n");
        printf("\t\t\t\t\t\t\t                 || (__V \n\n");
    }
}

char tela_ler_sexo(const char *mensagem) {
    char sexo;
    do {
        printf("%s (M/F): ", mensagem);
        scanf(" %c", &sexo);
        fflush(stdin);
        sexo = toupper(sexo);
        if (sexo != 'M' && sexo != 'F') {
            printf("\n\n\t\t\t\tErro: Sexo inv�lido. Digite M ou F.\n\n");
        }
    } while (sexo != 'M' && sexo != 'F');
    return sexo;
}

void tela_ler_cpf(int cpf[11]) {
    char entrada[12];
    int valido = 0;
    do {
        printf("\t\t\t\tCPF (11 d�gitos): ");
        if (scanf(" %11[^\n]", entrada) != 1) {
            fflush(stdin);
            continue;
        }
        fflush(stdin);
        if (strlen(entrada) != 11) {
            printf("\n\n\t\t\t\tErro: CPF deve ter exatamente 11 d�gitos.\n\n");
            continue;
        }
        valido = 1;
        for (int i = 0; i < 11; i++) {
            if (!isdigit(entrada[i])) {
                printf("\n\n\t\t\t\tErro: CPF deve conter apenas n�meros.\n\n");
                valido = 0;
                break;
            }
        }
    } while (!valido);

    for (int i = 0; i < 11; i++) {
        cpf[i] = entrada[i] - '0';
    }
}

void tela_ler_cep(int cep[8]) {
    char entrada[9];
    int valido = 0;
    do {
        printf("\t\t\t\tDigite o CEP (8 d�gitos): ");
        if (scanf(" %8[^\n]", entrada) != 1) {
            fflush(stdin);
            continue;
        }
        fflush(stdin);
        if (strlen(entrada) != 8) {
            printf("\n\n\t\t\t\tErro: CEP deve ter exatamente 8 d�gitos.\n\n");
            continue;
        }
        valido = 1;
        for (int i = 0; i < 8; i++) {
            if (!isdigit(entrada[i])) {
                printf("\n\n\t\t\t\tErro: CEP deve conter apenas n�meros.\n\n");
                valido = 0;
                break;
            }
        }
    } while (!valido);

    for (int i = 0; i < 8; i++) {
        cep[i] = entrada[i] - '0';
    }
}

void tela_ler_telefone(int telefone[11]) {
    char entrada[12];
    int valido = 0;
    do {
        printf("\t\t\t\tDigite o telefone com DDD (11 d�gitos): ");
        if (scanf(" %11[^\n]", entrada) != 1) {
            fflush(stdin);
            continue;
        }
        fflush(stdin);
        if (strlen(entrada) != 11) {
            printf("\n\n\t\t\t\tErro: Telefone deve ter exatamente 11 d�gitos.\n\n");
            continue;
        }
        valido = 1;
        for (int i = 0; i < 11; i++) {
            if (!isdigit(entrada[i])) {
                printf("\n\n\t\t\t\tErro: Telefone deve conter apenas n�meros.\n\n");
                valido = 0;
                break;
            }
        }
    } while (!valido);

    for (int i = 0; i < 11; i++) {
        telefone[i] = entrada[i] - '0';
    }
}

void tela_centralizar_pausa() {
    printf("\n\t\t\t\t\t\t\t     Pressione Enter para continuar...");
    fflush(stdin);
    getchar();
}

int tela_menu_opcoes() {
    int opcao, erro;
    system("cls");
    printf("\t\t\t\t\t\t     ********* Menu de Op��es *********\n\n");
    printf("\t\t\t\t\t\t           1 - Cadastrar Animal\n");
    printf("\t\t\t\t\t\t           2 - Cadastrar Tutor\n");
    printf("\t\t\t\t\t\t           3 - Relat�rio Geral \n");
    printf("\t\t\t\t\t\t           4 - Pesquisar Animal por ID\n");
    printf("\t\t\t\t\t\t           5 - Pesquisar Tutor por ID\n");
    printf("\t\t\t\t\t\t           6 - Remover Animal\n");
    printf("\t\t\t\t\t\t           7 - Remover Tutor\n");
    printf("\t\t\t\t\t\t           8 - Processos Adotivos\n");
    printf("\t\t\t\t\t\t           9 - Sair\n\n");
    printf("\t\t\t\t\t\t           Escolha uma op��o: ");

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

    printf("\t\t\t\t\t\t     ***** Menu de Processos Adotivos *****\n\n");
    printf("\t\t\t\t\t\t           1 - Cadastrar Processo Adotivo\n");
    printf("\t\t\t\t\t\t           2 - Consultar Processos Adotivos\n");
    printf("\t\t\t\t\t\t           3 - Cadastrar Ocorr�ncia\n");
    printf("\t\t\t\t\t\t           4 - Consultar Ocorr�ncias\n");
    printf("\t\t\t\t\t\t           5 - Voltar ao Menu Principal\n\n");
    printf("\n\t\t\t\t\t\t           Escolha uma op��o: ");

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
                printf("\n\n\t\t\t\t\t\t           Op��o Inv�lida! \n\n");
                tela_centralizar_pausa();
        }
    } while(sair == 0);
}

int tela_novo_tutor_cadatro_animal(int id_tutor) {
    if (cadastro_verificar_capacidade_maxima_tutores() == 1) {
        printf("\n\n\t\t\t\tErro: Capacidade m�xima de tutores atingida!\n\n");
        tela_centralizar_pausa();
        return 0;
    }

    Tutor t = animais_id_tutor_inicializador();
    t.id_tutor = id_tutor;

    system("cls");
    printf("\t\t\t\t\t\t\t     --- Cadastro de Novo Tutor (ID: %d) ---\n\n", id_tutor);

    printf("\t\t\t\tNome do tutor: ");
    scanf(" %255[^\n]", t.nome_tutor);
    fflush(stdin);

    t.sexo = tela_ler_sexo("\t\t\t\tSexo");

    tela_ler_cpf(t.cpf);

    t.endereco = tela_cadastar_endereco();
    t.contato = tela_cadastrar_forma_contato();

    t.tutor_ocupado = 1;
    cadastro_inserir_tutor(t);

    printf("\t\t\t\tTutor cadastrado com sucesso!\n");
    tela_centralizar_pausa();

    system("cls");
    return 1;
}

int tela_novo_animal_cadatro_tutor(int id_animal, int id_tutor) {
    Animal a;
    a.ocupado = 0;

    system("cls");
    printf("\t\t\t\t\t\t\t     --- Cadastro de Novo Animal ---\n");

    if (cadastro_verificar_capacidade_maxima_animais() == 1) {
        printf("\n\n\t\t\t\tErro: Capacidade m�xima de animais atingida!\n\n");
        tela_centralizar_pausa();
        return 0;
    }

    a.id_animal = id_animal;
    a.id_tutor = id_tutor;

    printf("\t\t\t\tNome do animal: ");
    scanf(" %255[^\n]", a.nome_animal);
    fflush(stdin);

    printf("\t\t\t\tEsp�cie: ");
    scanf(" %255[^\n]", a.especie);
    fflush(stdin);

    a.sexo = tela_ler_sexo("\t\t\t\tSexo");

    printf("\t\t\t\tRa�a: ");
    scanf(" %255[^\n]", a.raca);
    fflush(stdin);

    printf("\t\t\t\tVacinas: ");
    scanf(" %511[^\n]", a.vacinas);
    fflush(stdin);

    printf("\t\t\t\tVermifugado (S/N): ");
    scanf(" %c", &a.vermifugado);
    fflush(stdin);

    printf("\t\t\t\tHist�rico de sa�de: ");
    scanf(" %511[^\n]", a.historico);
    fflush(stdin);

    printf("\t\t\t\tCastrado (S/N): ");
    scanf(" %c", &a.castrado);
    fflush(stdin);

    a.ocupado = 1;
    a.adotado = 1;
    cadastro_inserir_animal(a);

    printf("\n\t\t\t\tAnimal cadastrado com sucesso!\n\n");
    tela_centralizar_pausa();
    system("cls");
    return 1;
}

Endereco tela_cadastar_endereco() {
    Endereco endereco;

    tela_ler_cep(endereco.cep);

    printf("\t\t\t\tInforme a rua: ");
    scanf(" %119[^\n]", endereco.rua);
    fflush(stdin);

    printf("\t\t\t\tInforme o bairro: ");
    scanf(" %119[^\n]", endereco.bairro);
    fflush(stdin);

    printf("\t\t\t\tInforme a cidade: ");
    scanf(" %79[^\n]", endereco.cidade);
    fflush(stdin);

    printf("\t\t\t\tInforme o estado: ");
    scanf(" %49[^\n]", endereco.estado);
    fflush(stdin);

    printf("\t\t\t\tInforme o n�mero da casa: ");
    scanf(" %49[^\n]", endereco.numero_casa);
    fflush(stdin);

    return endereco;
}

Forma_contato tela_cadastrar_forma_contato() {
    Forma_contato contato;

    tela_ler_telefone(contato.telefone);

    printf("\t\t\t\tDigite o e-mail: ");
    scanf(" %119[^\n]", contato.email);
    fflush(stdin);

    return contato;
}

void tela_cadastrar_animal() {
    int continuar;
    Animal a = {0};
    int opcao;

    do {
        system("cls");
        printf("\t\t\t\t\t\t\t     --- Cadastro de Animal ---\n");

        if (cadastro_verificar_capacidade_maxima_animais() == 1) {
            printf("\n\n\t\t\t\tErro: Capacidade m�xima de animais atingida!\n\n");
            tela_centralizar_pausa();
            return;
        }

        a.id_animal = gerar_proximo_id_animal();
        printf("\n\t\t\t\tID do animal: %d\n\n", a.id_animal);

        if (verificar_id_animal_existente(a.id_animal)) {
            printf("\n\n\t\t\t\tErro: ID de animal j� cadastrado!\n\n");
            tela_centralizar_pausa();
            continue;
        }

        a.id_tutor = controladores_id("\t\t\t\tDigite o ID do tutor: ");

        if (!verificar_id_tutor_existente(a.id_tutor)) {
            printf("\t\t\t\tTutor n�o encontrado.\n\n");
            printf("\t\t\t\t1 - Cadastrar novo tutor\n");
            printf("\t\t\t\t2 - Cancelar\n");
            opcao = controladores_inteiros("\n\t\t\t\tEscolha: ");

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

        Tutor tutor = cadastro_pesquisar_tutor(a.id_tutor);
        int count = 0;
        for (int j = 0; j < 10; j++) {
            if (tutor.id_animais[j] != 0) {
                count++;
            }
        }

        if (count >= 10) {
            int result = tela_limite_animais(a.id_tutor);
            if (result == 0) {
                printf("\n\n\t\t\t\tOpera��o cancelada. O tutor n�o tem espa�o.\n\n");
                tela_centralizar_pausa();
                continue;
            }
        }

        printf("\t\t\t\tNome do animal: ");
        scanf(" %255[^\n]", a.nome_animal);
        fflush(stdin);

        printf("\t\t\t\tEsp�cie: ");
        scanf(" %255[^\n]", a.especie);
        fflush(stdin);

        a.sexo = tela_ler_sexo("\t\t\t\tSexo");

        printf("\t\t\t\tRa�a: ");
        scanf(" %255[^\n]", a.raca);
        fflush(stdin);

        printf("\t\t\t\tVacinas: ");
        scanf(" %511[^\n]", a.vacinas);
        fflush(stdin);

        printf("\t\t\t\tVermifugado (S/N): ");
        scanf(" %c", &a.vermifugado);
        fflush(stdin);

        printf("\t\t\t\tHist�rico de sa�de: ");
        scanf(" %511[^\n]", a.historico);
        fflush(stdin);

        printf("\t\t\t\tCastrado (S/N): ");
        scanf(" %c", &a.castrado);
        fflush(stdin);

        a.ocupado = 1;
        a.adotado = 0;
        cadastro_inserir_animal(a);
        inserir_id_animal_em_tutor(a.id_animal, a.id_tutor);

        printf("\n\t\t\t\tAnimal cadastrado com sucesso!\n");

        continuar = tela_mensagem("\n\n\t\t\t\tDeseja cadastrar outro animal?");
    } while (continuar == 1);
}

void tela_cadastrar_tutor() {
    int quantidade_adotados;
    int continuar;

    Tutor t;
    t = animais_id_tutor_inicializador();

    do {
        system("cls");
        printf("\t\t\t\t\t\t\t     --- Cadastro de Tutor ---\n\n");

        if (cadastro_verificar_capacidade_maxima_tutores() == 1) {
            printf("\n\n\t\t\t\tErro: Capacidade m�xima de tutores atingida!\n\n");
            tela_centralizar_pausa();
            system("cls");
            break;
        }

        t.id_tutor = gerar_proximo_id_tutor();
        printf("\t\t\t\tID do tutor: %d\n\n", t.id_tutor);

        quantidade_adotados = controladores_inteiros("\t\t\t\tDigite a quantidade de animais adotados: ");

        if (quantidade_adotados < 1 || quantidade_adotados > 10) {
            printf("\n\n\t\t\t\tN�o � poss�vel cadastrar tutores com menos de 1 animal ou mais de 10 animais\n\n");
            tela_centralizar_pausa();
            system("cls");
            continue;
        }

        for(int i = 0; i < quantidade_adotados; i++) {
            int id_valido = 0;

            while (!id_valido) {
                int id_animal = controladores_id("\n\t\t\t\tDigite o ID do animal: ");

                if (verificar_id_animal_existente(id_animal)) {
                    Animal animal = cadastro_pesquisar_animal(id_animal);
                    if (animal.adotado == 1) {
                        printf("\n\n\t\t\t\tErro: O animal de ID %d j� est� adotado por outro tutor.\n", id_animal);
                        printf("\t\t\t\tPor favor, escolha outro animal.\n\n");
                        tela_centralizar_pausa();
                        system("cls");
                    } else {
                        t.id_animais[i] = id_animal;
                        id_valido = 1;
                    }
                } else {
                    printf("\n\t\t\t\tAnimal n�o encontrado!\n\n");
                    printf("\t\t\t\t1 - Cadastrar novo animal\n");
                    printf("\t\t\t\t2 - Cancelar\n\n");
                    int opcao = controladores_inteiros("\t\t\t\tEscolha: ");

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

        printf("\t\t\t\tNome do tutor: ");
        scanf(" %255[^\n]", t.nome_tutor);
        fflush(stdin);

        t.sexo = tela_ler_sexo("\t\t\t\tSexo");

        tela_ler_cpf(t.cpf);

        t.endereco = tela_cadastar_endereco();
        t.contato = tela_cadastrar_forma_contato();

        t.tutor_ocupado = 1;
        cadastro_inserir_tutor(t);

        for (int i = 0; i < quantidade_adotados; i++) {
            if (t.id_animais[i] != 0) {
                for (int j = 0; j < NUM_MAX_ANIMAIS; j++) {
                    if (vetor_animais[j].ocupado == 1 && vetor_animais[j].id_animal == t.id_animais[i]) {
                        vetor_animais[j].adotado = 1;
                        vetor_animais[j].id_tutor = t.id_tutor;
                        break;
                    }
                }
            }
        }

        printf("\n\t\t\t\tTutor cadastrado com sucesso!\n\n");
        tela_centralizar_pausa();
        system("cls");
        continuar = tela_mensagem("\n\t\t\t\tDeseja cadastrar outro tutor?");
    } while (continuar == 1);
}

void tela_relatorio() {
    int opcao, erro;
    do {
        system("cls");
        printf("\t\t\t\t\t\t\t     ***** Menu de Relat�rios *****\n\n");
        printf("\t\t\t\t\t1 - Relat�rio de Animais Cadastrados\n");
        printf("\t\t\t\t\t2 - Relat�rio de Tutores Cadastrados\n");
        printf("\t\t\t\t\t3 - Voltar ao Menu Principal\n\n");
        printf("\t\t\t\t\tEscolha uma op��o: ");

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
                printf("\n\n\t\t\t\t\tOp��o Inv�lida !!! \n\n");
                tela_centralizar_pausa();
                system("cls");
        }
    } while(1);
}

void tela_relatorio_animais() {
    system("cls");
    printf("\t\t\t\t\t\t\t     Relat�rio de Animais Cadastrados\n\n");
    printf("\t\t\t\t\t\t\t      Total de Animais Cadastrados: %d\n\n", total_animais);

    for (int i = 0; i < NUM_MAX_ANIMAIS; i++) {
        if (vetor_animais[i].ocupado == 1) {
            printf("\t+-------------------------------------------------+\n");
            printf("\t| ID Animal: %d\n", vetor_animais[i].id_animal);
            printf("\t| ID Tutor: %d\n", vetor_animais[i].id_tutor);
            printf("\t| Nome: %s\n", vetor_animais[i].nome_animal);
            printf("\t| Esp�cie: %s\n", vetor_animais[i].especie);
            printf("\t| Sexo: %c\n", vetor_animais[i].sexo);
            printf("\t| Ra�a: %s\n", vetor_animais[i].raca);
            printf("\t| Vacinas: %s\n", vetor_animais[i].vacinas);
            printf("\t| Vermifugado: %c\n", vetor_animais[i].vermifugado);
            printf("\t| Hist�rico: %s\n", vetor_animais[i].historico);
            printf("\t| Castrado: %c\n", vetor_animais[i].castrado);
            printf("\t+-------------------------------------------------+\n\n");
        }
    }
    tela_centralizar_pausa();
}

void tela_relatorio_tutores() {
    system("cls");
    printf("\t\t\t\t\t\t\t     Relat�rio de Tutores Cadastrados\n\n");
    printf("\t\t\t\t\t\t\t      Total de Tutores Cadastrados: %d\n\n", total_tutores);

    for (int i = 0; i < NUM_MAX_TUTORES; i++) {
        if (vetor_tutores[i].tutor_ocupado == 1) {
            printf("\t+-------------------------------------------------+\n");
            printf("\t| ID Tutor: %d\n", vetor_tutores[i].id_tutor);
            printf("\t| Nome: %s\n", vetor_tutores[i].nome_tutor);
            printf("\t| Sexo: %c\n", vetor_tutores[i].sexo);

            printf("\t| CPF: ");
            for(int j = 0; j < 11; j++) {
                printf("%d", vetor_tutores[i].cpf[j]);
            }
            printf("\n");

            printf("\t| Animais: ");
            for(int j = 0; j < 10; j++) {
                if(vetor_tutores[i].id_animais[j] != 0) {
                    printf("%d ", vetor_tutores[i].id_animais[j]);
                }
            }
            printf("\n");

            printf("\t| CEP: ");
            for(int j = 0; j < 8; j++) {
                printf("%d", vetor_tutores[i].endereco.cep[j]);
            }
            printf("\n");

            printf("\t| Rua: %s\n", vetor_tutores[i].endereco.rua);
            printf("\t| Bairro: %s\n", vetor_tutores[i].endereco.bairro);
            printf("\t| Cidade: %s\n", vetor_tutores[i].endereco.cidade);
            printf("\t| Estado: %s\n", vetor_tutores[i].endereco.estado);
            printf("\t| N�mero: %s\n", vetor_tutores[i].endereco.numero_casa);

            printf("\t| Telefone: ");
            for(int j = 0; j < 11; j++) {
                printf("%d", vetor_tutores[i].contato.telefone[j]);
            }
            printf("\n");

            printf("\t| Email: %s\n", vetor_tutores[i].contato.email);
            printf("\t+-------------------------------------------------+\n\n");
        }
    }
    tela_centralizar_pausa();
}

void tela_pesquisar() {
    int continuar, id;
    do {
        system("cls");
        printf("\t\t\t\t\t\t\t     --- Pesquisar Animal ---\n\n");
        id = controladores_id("\tDigite o ID do animal: ");

        Animal a = cadastro_pesquisar_animal(id);

        if (a.ocupado == 1) {
            printf("\n\t+-------------------------------------------------+\n");
            printf("\t| ID: %d\n", a.id_animal);
            printf("\t| Tutor ID: %d\n", a.id_tutor);
            printf("\t| Nome: %s\n", a.nome_animal);
            printf("\t| Esp�cie: %s\n", a.especie);
            printf("\t| Sexo: %c\n", a.sexo);
            printf("\t| Ra�a: %s\n", a.raca);
            printf("\t| Vacinas: %s\n", a.vacinas);
            printf("\t| Vermifugado: %c\n", a.vermifugado);
            printf("\t| Hist�rico: %s\n", a.historico);
            printf("\t| Castrado: %c\n", a.castrado);
            printf("\t+-------------------------------------------------+\n\n");
        } else {
            printf("\n\n\t\t\t\tAnimal n�o encontrado.\n\n");
        }
        tela_centralizar_pausa();
        continuar = tela_mensagem("\n\tDeseja pesquisar outro animal?");
    } while (continuar == 1);
}

void tela_pesquisar_tutor() {
    int continuar, id;
    do {
        system("cls");
        printf("\t\t\t\t\t\t\t     --- Pesquisar Tutor ---\n\n");
        id = controladores_id("\tDigite o ID do tutor: ");

        Tutor t = cadastro_pesquisar_tutor(id);

        if (t.tutor_ocupado == 1) {
            printf("\n\n\t+-------------------------------------------------+\n");
            printf("\t| ID: %d\n", t.id_tutor);
            printf("\t| Nome: %s\n", t.nome_tutor);
            printf("\t| Sexo: %c\n", t.sexo);

            printf("\t| CPF: ");
            for(int j = 0; j < 11; j++) {
                printf("%d", t.cpf[j]);
            }
            printf("\n");

            printf("\t| Animais: ");
            for(int j = 0; j < 10 && t.id_animais[j] != 0; j++) {
                printf("%d ", t.id_animais[j]);
            }
            printf("\n");

            printf("\t| CEP: ");
            for(int j = 0; j < 8; j++) {
                printf("%d", t.endereco.cep[j]);
            }
            printf("\n");

            printf("\t| Rua: %s\n", t.endereco.rua);
            printf("\t| Bairro: %s\n", t.endereco.bairro);
            printf("\t| Cidade: %s\n", t.endereco.cidade);
            printf("\t| Estado: %s\n", t.endereco.estado);
            printf("\t| N�mero: %s\n", t.endereco.numero_casa);

            printf("\t| Telefone: ");
            for(int j = 0; j < 11; j++) {
                printf("%d", t.contato.telefone[j]);
            }
            printf("\n");

            printf("\t| Email: %s\n", t.contato.email);
            printf("\t+-------------------------------------------------+\n\n");
        } else {
            printf("\n\n\t\t\t\tTutor n�o encontrado.\n\n");
        }
        tela_centralizar_pausa();
        continuar = tela_mensagem("\n\tDeseja pesquisar outro tutor?");
    } while (continuar == 1);
}

void tela_remover() {
    int continuar, id;

    do {
        system("cls");
        printf("\t\t\t\t\t\t\t     --- Remover Animal ---\n\n");
        id = controladores_id("\t\t\t\tDigite o ID do animal a ser removido: ");

        if (cadastro_remover_animal(id)) {
            printf("\n\n\t\t\t\tAnimal removido com sucesso.\n\n");
        } else {
            printf("\n\n\t\t\t\tAnimal n�o encontrado.\n\n");
        }

        tela_centralizar_pausa();
        continuar = tela_mensagem("\n\t\t\t\tDeseja remover outro animal?");
    } while (continuar == 1);
}

void tela_remover_tutor() {
    int continuar, id;
    do {
        system("cls");
        printf("\t\t\t\t\t\t\t     --- Remover Tutor ---\n\n");
        id = controladores_id("\t\t\t\tDigite o ID do tutor a ser removido: ");

        if (cadastro_remover_tutor(id)) {
            printf("\n\n\t\t\t\tTutor removido com sucesso.\n\n");
        } else {
            printf("\n\n\t\t\t\tTutor n�o encontrado ou opera��o cancelada.\n\n");
        }

        tela_centralizar_pausa();
        continuar = tela_mensagem("\n\t\t\t\tDeseja remover outro tutor?");
    } while (continuar == 1);
}

int tela_sair() {
    system("cls");
    return tela_mensagem("\n\n\t\t\t\tDeseja realmente sair?");
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

        printf("\n\n\t\t\t\tErro: Digite apenas 's' ou 'n'!\n\n");
    } while (1);
}

void tela_cadastrar_processo_adotivo() {
    FILE *file = fopen("processos.txt", "a");
    if (file == NULL) {
        printf("\n\n\t\t\t\tErro ao abrir arquivo de processos.\n\n");
        return;
    }

    ProcessoAdotivo processo;
    int opcao;

    system("cls");

    tela_marcas(1);
    printf("\t\t\t\t\t\t\t     --- Cadastro de Processo Adotivo ---\n\n");

    processo.id_processo = gerar_id_proximo("processos.txt", 0);
    printf("\t\t\t\tID do Processo gerado: %d\n\n", processo.id_processo);

    int animal_valido = 0;
    while (!animal_valido) {
        processo.id_animal = controladores_id("\t\t\t\tDigite o ID do Animal: ");

        if (verificar_id_animal_existente(processo.id_animal)) {
            animal_valido = 1;
        } else {
            printf("\n\n\t\t\t\tAnimal n�o encontrado! Cadastre o animal primeiro.\n\n");
            tela_centralizar_pausa();
            fclose(file);
            return;
        }
    }

    int tutor_valido = 0;
    while (!tutor_valido) {
        processo.id_tutor = controladores_id("\n\t\t\t\tDigite o ID do Tutor: ");

        if (verificar_id_tutor_existente(processo.id_tutor)) {
            tutor_valido = 1;
        } else {
            printf("\n\n\t\t\t\tTutor n�o encontrado! Cadastre o tutor primeiro.\n\n");
            tela_centralizar_pausa();
            fclose(file);
            return;
        }
    }

    if (!animal_pertence_ao_tutor(processo.id_animal, processo.id_tutor)) {
        printf("\n\n\t\t\t\tErro: Este animal n�o pertence ao tutor informado!\n\n");
        tela_centralizar_pausa();
        fclose(file);
        return;
    }

    printf("\t\t\t\tData da ado��o (dd mm aaaa): ");
    scanf("%d %d %d", &processo.data_adocao.dia, &processo.data_adocao.mes, &processo.data_adocao.ano);
    getchar();

    printf("\t\t\t\tRelat�rio de adapta��o: ");
    scanf(" %299[^\n]", processo.relatorio_adaptacao);
    fflush(stdin);

    printf("\t\t\t\tAgendamentos de visitas: ");
    scanf(" %199[^\n]", processo.agendamentos);
    fflush(stdin);

    printf("\t\t\t\tAtualiza��o de dados m�dicos: ");
    scanf(" %199[^\n]", processo.dados_medicos);
    fflush(stdin);

    processo.ativo = 1;

    fprintf(file, "%d;%d;%d;%d/%d/%d;%s;%s;%s;%d\n",
        processo.id_processo, processo.id_animal, processo.id_tutor,
        processo.data_adocao.dia, processo.data_adocao.mes, processo.data_adocao.ano,
        processo.relatorio_adaptacao, processo.agendamentos, processo.dados_medicos, processo.ativo);

    fclose(file);
    printf("\n\t\t\t\tProcesso adotivo cadastrado com sucesso!\n");
    tela_centralizar_pausa();
}

void tela_consultar_processos_adotivos() {
    FILE *file = fopen("processos.txt", "r");
    if (file == NULL) {
        printf("\n\n\t\t\t\tErro ao abrir arquivo de processos.\n\n");
        tela_centralizar_pausa();
        return;
    }

    ProcessoAdotivo processo;
    char linha[1024];
    char data[15];

    system("cls");
    tela_marcas(1);
    printf("\n\t\t\t\t\t\t\t     --- Processos Adotivos ---\n\n");

    while (fgets(linha, sizeof(linha), file) != NULL) {
        if (sscanf(linha, "%d;%d;%d;%14[^;];%299[^;];%199[^;];%199[^;];%d",
            &processo.id_processo, &processo.id_animal, &processo.id_tutor,
            data, processo.relatorio_adaptacao, processo.agendamentos, processo.dados_medicos, &processo.ativo) == 8) {

            sscanf(data, "%d/%d/%d", &processo.data_adocao.dia, &processo.data_adocao.mes, &processo.data_adocao.ano);

            printf("\n\t\t\t\tID Processo: %d | ID Animal: %d | ID Tutor: %d\n",
                   processo.id_processo, processo.id_animal, processo.id_tutor);
            printf("\t\t\t\tData da ado��o: %02d/%02d/%04d\n",
                   processo.data_adocao.dia, processo.data_adocao.mes, processo.data_adocao.ano);
            printf("\t\t\t\tRelat�rio de adapta��o: %s\n", processo.relatorio_adaptacao);
            printf("\t\t\t\tAgendamentos: %s\n", processo.agendamentos);
            printf("\t\t\t\tDados m�dicos: %s\n", processo.dados_medicos);
            printf("\t\t\t\tStatus: %s\n", (processo.ativo == 1 ? "Ativo" : "Inativo"));
            printf("\t\t\t\t----------------------------------------\n\n");
        } else {
            printf("\n\n\t\t\t\t[Erro] Linha mal formatada: %s", linha);
        }
    }

    fclose(file);
    tela_centralizar_pausa();
}

void tela_cadastrar_ocorrencia() {
    FILE *file = fopen("ocorrencias.txt", "a");
    if (file == NULL) {
        printf("\n\n\t\t\t\tErro ao abrir o arquivo de ocorr�ncias.\n\n");
        return;
    }

    Ocorrencia ocorrencia;

    system("cls");

    printf("\t\t\t\t\t\t\t       --- Cadastro de Ocorrencia ---\n\n\n");
    tela_marcas(1);

    ocorrencia.id_ocorrencia = gerar_id_proximo("ocorrencias.txt", 0);
    printf("\n\t\t\t\tID da Ocorr�ncia gerado: %d\n\n", ocorrencia.id_ocorrencia);

    ocorrencia.id_processo = controladores_id("\t\t\t\tDigite o ID do Processo Adotivo: ");
    ocorrencia.id_tutor = controladores_id("\t\t\t\tDigite o ID do Tutor: ");

    if (!verificar_id_tutor_existente(ocorrencia.id_tutor)) {
        printf("\n\n\t\t\t\tERRO! N�o foi encontrado o tutor com este ID. Cadastre o tutor primeiro.\n\n");
        tela_centralizar_pausa();
        fclose(file);
        return;
    }

    int processo_valido = 0;
    int id_tutor_processo = -1;
    int id_animal = -1;

    FILE *fp = fopen("processos.txt", "r");
    if (fp) {
        char linha[1024];
        while (fgets(linha, sizeof(linha), fp) != NULL) {
            int id_processo, id_animal_temp, id_tutor_temp, ativo;
            char data[15], relatorio[300], agendamento[200], dados[200];
            if (sscanf(linha, "%d;%d;%d;%14[^;];%299[^;];%199[^;];%199[^;];%d",
                &id_processo, &id_animal_temp, &id_tutor_temp, data, relatorio, agendamento, dados, &ativo) == 8) {
                if (id_processo == ocorrencia.id_processo) {
                    processo_valido = 1;
                    id_animal = id_animal_temp;
                    id_tutor_processo = id_tutor_temp;
                    break;
                }
            }
        }
        fclose(fp);
    }

    if (!processo_valido) {
        printf("\n\n\t\t\t\tERRO! Processo adotivo n�o encontrado.\n\n");
        tela_centralizar_pausa();
        fclose(file);
        return;
    }

    if (ocorrencia.id_tutor != id_tutor_processo) {
        printf("\n\n\t\t\t\tERRO! O tutor informado n�o � o tutor deste processo adotivo.\n\n");
        tela_centralizar_pausa();
        fclose(file);
        return;
    }

    if (!verificar_id_animal_existente(id_animal)) {
        printf("\n\n\t\t\t\tERRO! Animal associado ao processo n�o encontrado. Cadastre o animal primeiro.\n\n");
        tela_centralizar_pausa();
        fclose(file);
        return;
    }

    if (!animal_pertence_ao_tutor(id_animal, ocorrencia.id_tutor)) {
        printf("\n\n\t\t\t\tERRO! Inconsist�ncia: animal n�o pertence ao tutor!\n\n");
        tela_centralizar_pausa();
        fclose(file);
        return;
    }

    printf("\t\t\t\tDescreva o ocorrido: ");
    scanf(" %299[^\n]", ocorrencia.descricao);
    fflush(stdin);

    printf("\t\t\t\tData da ocorr�ncia (dd mm aaaa): ");
    scanf("%d %d %d", &ocorrencia.data_ocorrencia.dia, &ocorrencia.data_ocorrencia.mes, &ocorrencia.data_ocorrencia.ano);
    getchar();

    printf("\t\t\t\tA��o tomada: ");
    scanf(" %299[^\n]", ocorrencia.acao);
    fflush(stdin);

    ocorrencia.ativo = 1;

    fprintf(file, "%d;%d;%d;%s;%d/%d/%d;%s;%d\n",
        ocorrencia.id_ocorrencia, ocorrencia.id_processo, ocorrencia.id_tutor,
        ocorrencia.descricao, ocorrencia.data_ocorrencia.dia, ocorrencia.data_ocorrencia.mes,
        ocorrencia.data_ocorrencia.ano, ocorrencia.acao, ocorrencia.ativo);

    fclose(file);
    printf("\n\t\t\t\tOcorr�ncia registrada com sucesso!\n");
    tela_centralizar_pausa();
    system("cls");
}

void tela_consultar_ocorrencias() {
    FILE *file = fopen("ocorrencias.txt", "r");
    if (file == NULL) {
        printf("\n\n\t\t\t\tErro ao abrir o arquivo de ocorr�ncias.\n\n");
        tela_centralizar_pausa();
        return;
    }

    Ocorrencia ocorrencia;
    char linha[1024];

    system("cls");
    printf("\t\t\t\t     +-------------------------- 4 - Consultar Ocorr�ncia ---------------------------+\n\n\n");
    tela_marcas(1);

    printf("\n\t\t\t\t\t\t\t-------------- Ocorr�ncias --------------\n");

    while (fgets(linha, sizeof(linha), file) != NULL) {
        if (sscanf(linha, "%d;%d;%d;%299[^;];%d/%d/%d;%299[^;];%d",
            &ocorrencia.id_ocorrencia, &ocorrencia.id_processo, &ocorrencia.id_tutor,
            ocorrencia.descricao, &ocorrencia.data_ocorrencia.dia, &ocorrencia.data_ocorrencia.mes,
            &ocorrencia.data_ocorrencia.ano, ocorrencia.acao, &ocorrencia.ativo) == 9) {

            printf("\n\t-----------------------------------------\n");
            printf("\n\n\tID Ocorr�ncia: %d\n\tProcesso: %d | Tutor: %d\n",
                   ocorrencia.id_ocorrencia, ocorrencia.id_processo, ocorrencia.id_tutor);
            printf("\tData: %02d/%02d/%04d\n",
                   ocorrencia.data_ocorrencia.dia, ocorrencia.data_ocorrencia.mes, ocorrencia.data_ocorrencia.ano);
            printf("\tDescri��o: %s\n", ocorrencia.descricao);
            printf("\tA��o: %s\n", ocorrencia.acao);
            printf("\tStatus: %s\n", ocorrencia.ativo == 1 ? "Ativa" : "Inativa");
        }
    }

    fclose(file);
    tela_centralizar_pausa();
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
            printf("\n\n\t\t\t\tErro: Digite um n�mero inteiro v�lido.\n\n");
        }
    } while (resultado != 1);
    return valor;
}

int controladores_id(char* mensagem) {
    int id;
    do {
        id = controladores_inteiros(mensagem);
        if (id <= 0) {
            printf("\n\n\t\t\t\tErro: O ID deve ser um n�mero positivo.\n\n");
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

int animal_pertence_ao_tutor(int id_animal, int id_tutor) {
    Animal animal = cadastro_pesquisar_animal(id_animal);
    if (animal.ocupado != 1) {
        return 0;
    }

    if (animal.id_tutor != id_tutor) {
        return 0;
    }

    Tutor tutor = cadastro_pesquisar_tutor(id_tutor);
    if (tutor.tutor_ocupado != 1) {
        return 0;
    }

    for (int i = 0; i < 10; i++) {
        if (tutor.id_animais[i] == id_animal) {
            return 1;
        }
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

int cadastro_inserir_tutor(Tutor tutor) {
    for (int i = 0; i < NUM_MAX_TUTORES; i++) {
        if (vetor_tutores[i].tutor_ocupado == 1 && vetor_tutores[i].id_tutor == tutor.id_tutor) {
            printf("\n\n\t\t\t\tErro: J� existe um tutor com este ID.\n\n");
            tela_centralizar_pausa();
            return 0;
        }
    }

    for (int i = 0; i < NUM_MAX_TUTORES; i++) {
        if (vetor_tutores[i].tutor_ocupado == 0) {
            vetor_tutores[i] = tutor;
            vetor_tutores[i].tutor_ocupado = 1;
            total_tutores++;
            return 1;
        }
    }

    printf("\n\n\t\t\t\tErro: Capacidade m�xima de tutores atingida.\n\n");
    tela_centralizar_pausa();
    return 0;
}

void cadastro_inserir_animal(Animal a) {
    for (int i = 0; i < NUM_MAX_ANIMAIS; i++) {
        if (vetor_animais[i].ocupado == 1 && vetor_animais[i].id_animal == a.id_animal) {
            printf("\n\n\t\t\t\tErro: J� existe um animal com este ID.\n\n");
            tela_centralizar_pausa();
            return;
        }
    }
    for (int i = 0; i < NUM_MAX_ANIMAIS; i++) {
        if (vetor_animais[i].ocupado == 0) {
            vetor_animais[i] = a;
            vetor_animais[i].ocupado = 1;
            total_animais++;
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
    printf("\n\n\t\t\t\tERRO! O tutor em quest�o atingiu o limite de animais alocados.\n\n");
    printf("\t\t\t\tSelecione como proceder:\n\n");
    printf("\t\t\t\t1 - Deletar um animal do tutor vigente.\n");
    printf("\t\t\t\t2 - Interromper cadastro.\n");
    printf("\n\t\t\t\tOpcao: ");

    int opcao;
    scanf("%d", &opcao);
    fflush(stdin);

    if (opcao == 1) {
        Tutor tutor = cadastro_pesquisar_tutor(id_tutor);
        if (tutor.tutor_ocupado == 0) {
            printf("\n\n\t\t\t\tTutor n�o encontrado.\n\n");
            tela_centralizar_pausa();
            return 0;
        }

        printf("\n\t\t\t\tIDs dos animais:\n");
        for (int i = 0; i < 10; i++) {
            if (tutor.id_animais[i] != 0) {
                printf("\n\t\t\t\t%d\n", tutor.id_animais[i]);
            }
        }

        int id_animal_remover;
        printf("\n\t\t\t\tDigite o ID do animal a ser removido: ");
        scanf("%d", &id_animal_remover);
        fflush(stdin);

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
    printf("\t\t\t\t\t\t\t*****Op��es de exclus�o de tutor*****\n\n");
    printf("\t\t\t\t  1- Excluir o tutor e manter os animais (Recomendado somente no caso de recadastro ou realoca��o do animal).\n");
    printf("\t\t\t\t  2- Excluir todos os animais associados ao tutor.\n");
    printf("\n\t\t\t\t  Opcao: ");

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
                return 0;
            }
        }
    }
    return 0;
}

int cadastro_remover_animal(int id) {
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
    if (!file) return 1;

    int maior_id = 0;
    char linha[1024];

    while (fgets(linha, sizeof(linha), file) != NULL) {
        int id_atual;
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
