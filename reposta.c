#include <stdio.h>
#include <string.h>

#define MAX 100
#define TAM_STRING 100

struct Livro {
    char titulo[TAM_STRING];
    char autor[TAM_STRING];
    char editora[TAM_STRING];
    int anoPublicacao;
    int qtdPaginas;
};

void preencherVetor(struct Livro livros[], int *n);
void imprimitVetor(struct Livro livros[], int n);
int buscarPorTitulo(struct Livro livros[], int n, const char *titulo);
void ordenarPorTitulo(struct Livro livros[], int n);
int buscaBinariaPorTitulo(struct Livro livros[], int n, const char *titulo);

void preencherVetor(struct Livro livros[], int *n) {
    printf("Quantos livros deseja cadastrar? ");
    scanf("%d", n);
    getchar(); // limpa o buffer

    for (int i = 0; i < *n; i++) {
        printf("\nLivro %d:\n", i + 1);

        printf("Título: ");
        fgets(livros[i].titulo, TAM_STRING, stdin);
        livros[i].titulo[strcspn(livros[i].titulo, "\n")] = '\0';

        printf("Autor: ");
        fgets(livros[i].autor, TAM_STRING, stdin);
        livros[i].autor[strcspn(livros[i].autor, "\n")] = '\0';

        printf("Editora: ");
        fgets(livros[i].editora, TAM_STRING, stdin);
        livros[i].editora[strcspn(livros[i].editora, "\n")] = '\0';

        printf("Ano de Publicação: ");
        scanf("%d", &livros[i].anoPublicacao);

        printf("Quantidade de Páginas: ");
        scanf("%d", &livros[i].qtdPaginas);
        getchar(); // Limpa o buffer
    }
}

void imprimirVetor(struct Livro livros[], int n) {
    printf("\nLista de Livros:\n");
    for (int i = 0; i < n; i++) {
        printf("%d. Título: %s | Autor: %s | Editora: %s | Ano: %d | Páginas: %d\n",
               i, livros[i].titulo, livros[i].autor, livros[i].editora,
               livros[i].anoPublicacao, livros[i].qtdPaginas);
    }
}

int buscarPorTitulo(struct Livro livros[], int n, const char *titulo) {
    for (int i = 0; i < n; i++) {
        if (strcmp(livros[i].titulo, titulo) == 0) {
            return i;
        }
    }
    return -1;
}

void ordenarPorTitulo(struct Livro livros[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1; j++) {
            if (strcmp(livros[j].titulo, livros[j + 1].titulo) > 0) {
                struct Livro temp = livros[j];
                livros[j] = livros[j + 1];
                livros[j + 1] = temp;
            }
        }
    }
}

int buscaBinariaPorTitulo(struct Livro livros[], int n, const char *titulo) {
    int esquerda = 0, direita = n - 1;
    while (esquerda <= direita) {
        int meio = (esquerda + direita) / 2;
        int cmp = strcmp(livros[meio].titulo, titulo);

        if (cmp == 0)
            return meio;
        else if (cmp < 0)
            esquerda = meio + 1;
        else
            direita = meio - 1;
    }
    return -1;
}

int main() {
    struct Livro livros[MAX];
    int n;

    preencherVetor(livros, &n);
    imprimirVetor(livros, n);

    char tituloBusca[TAM_STRING];
    printf("\nDigite o título para busca sequencial: ");
    fgets(tituloBusca, TAM_STRING, stdin);
    tituloBusca[strcspn(tituloBusca, "\n")] = '\0';

    int pos = buscarPorTitulo(livros, n, tituloBusca);
    if (pos != -1)
        printf("Livro encontrado na posição %d.\n", pos);
    else
        printf("Livro não encontrado.\n");

    printf("\nOrdenando por título...\n");
    ordenarPorTitulo(livros, n);
    imprimirVetor(livros, n);

    printf("\nDigite o título para busca binária: ");
    fgets(tituloBusca, TAM_STRING, stdin);
    tituloBusca[strcspn(tituloBusca, "\n")] = '\0';

    pos = buscaBinariaPorTitulo(livros, n, tituloBusca);
    if (pos != -1)
        printf("Livro encontrado na posição %d (após ordenação).\n", pos);
    else
        printf("Livro não encontrado (após ordenação).\n");

    return 0;
}
