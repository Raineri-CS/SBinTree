/* Lucas Roberto Raineri Oliveira - 38346 */
/* Codigo formatado utilizando o clang-format no formato LLVM*/

#include <stdio.h>

#include "gfx/gfx.h"

/* Constantes */
enum {
  INSERT,
  REMOVE,
  SEARCH,
  LEFT,
  RIGHT,
  EMPTY_TREE,
  FOUND,
  LEFT_NOT_FOUND,
  RIGHT_NOT_FOUND
};
#define FONT_SIZE 30

/* O tamanho da janela*/
#define tamX 1280
#define tamY 720

/* Clear pros SOs suportados */
#ifndef _WIN32
#define clear() system("clear");
#else
#define clear() system("cls");
#endif

/* Estrutura auxiliar pra cor */
typedef struct rgbColor {
  int red;
  int green;
  int blue;
} rgb;

typedef struct nodeProto {
  int val;
  struct nodeProto *left, *right;
} node;

typedef struct searchTreeProto {
  node *firstNode;
} searchTree;

/* Libera todos os nos da arvore recursivamente */
void freeTree(node *root);

/* Insere WHO na arvore */
void insertNode(node **root, int who);

/* Procura um no com o valor de who, retorna o ponteiro e um codigo de retorno,
 * definido no enum */
void search(node **root, int who, int *returnCode);

/* Deleta um no da arvore que coincide com o numero de who, nao faz nada se nao
 * achar */
void deleteNode(node *startedNode, int who);

void drawNode();
void drawTree();

int main(int argc, char *argv[]) {
  argc = argc;
  argv = argv;
  searchTree tree;
  node *ptr;

  tree.firstNode = NULL;

  insertNode(&tree.firstNode, 3);
  insertNode(&tree.firstNode, 4);
  insertNode(&tree.firstNode, 5);
  insertNode(&tree.firstNode, 1);
  insertNode(&tree.firstNode, 2);

  ptr = tree.firstNode;

  printf("%d\n", tree.firstNode->val);

  freeTree(tree.firstNode);
  tree.firstNode = NULL;
  
  return 0;
}

/* NOTE: usando os algoritmos passados em aula, conforme instruido */
void insertNode(node **root, int who) {
  int retCode;
  node *ptr, *auxPtr;
  ptr = *root;
  search(&ptr, who, &retCode);

  if (retCode == FOUND) {
    printf("Insercao invalida\n");
  } else {
    auxPtr = malloc(sizeof(node));
    auxPtr->val = who;
    auxPtr->left = NULL;
    auxPtr->right = NULL;
    if (retCode == EMPTY_TREE) {
      *root = auxPtr;
    } else if (retCode == LEFT_NOT_FOUND) {
      ptr->left = auxPtr;
    } else
      ptr->right = auxPtr;
  }
}

void freeTree(node *root) {
  /* Chamar pra todos os nos da direita */
  if (root->right != NULL) {
    freeTree(root->right);
  }
  /* Chamar pra todos os nos da esquerda */
  if (root->left != NULL) {
    freeTree(root->left);
  }
  /* Se chegou no final da arvore, se liberar */
  free(root);
  /* Retornar se ambos os galhos do no forem nulos */
  return;
}

/* NOTE: usando os algoritmos passados em aula, conforme instruido */
void search(node **root, int who, int *returnCode) {
  /* Stack goes BRRRRRR */
  node *localNode;
  localNode = *root;
  if (*root == NULL) {
    *returnCode = EMPTY_TREE;
  } else if (who == localNode->val) {
    *returnCode = FOUND;
  } else if (who < localNode->val) {
    if (localNode->left == NULL) {
      *returnCode = LEFT_NOT_FOUND;
    } else {
      *root = localNode->left;
      search(root, who, returnCode);
    }
  } else if (localNode->right == NULL) {
    *returnCode = RIGHT_NOT_FOUND;
  } else {
    *root = localNode->right;
    search(root, who, returnCode);
  }
}

void deleteNode(node *startedNode, int who) {
  // TODO
}
