#define TAM_DISCIPLINA 3
#define TAM_NOME_DISCIPLINA 20
#define CAD_DISCIPLINA_SUCESSO -10
#define DISCIPLINA_INVALIDA -11
#define ATUALIZACAO_DISCIPLINA_SUCESSO -12
#define DISCIPLINA_INEXISTE -13
#define EXCLUIR_DISCIPLINA_SUCESSO -14
#define LISTA_DISCIPLINA_CHEIA -16

typedef struct dis {
  char nome[TAM_NOME_DISCIPLINA];
  int codigo;
  int ativo;
} Disciplina;

int menuDisciplina();
int cadastrarDisciplina(Disciplina listaDisciplinas[], int qtdDisciplinas);
void listarDisciplina(Disciplina listaDisciplinas[], int qtdDisciplinas);
int atualizarDisciplina(Disciplina listaDisciplinas[], int qtdDisciplinas);
int excluirDisciplina(Disciplina listaDisciplinas[], int qtdDisciplinas);