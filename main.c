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

/* Aloca um no na arvore */
void allocateNode(node *root, int value);

/* Aloca o primeiro no na arvore */
node *allocateFirstNode(node *which, int value);

/* Libera todos os nos da arvore recursivamente */
void freeTree(node *root);

/* Procura um no com o valor de who, retorna o ponteiro se achar, NULL se nao
 * achar */
void search(node *root, int who, int *returnCode);

/* Deleta um no da arvore que coincide com o numero de who, nao faz nada se nao
 * achar */
void deleteNode(node *startedNode, int who);

void drawNode();
void drawTree();

int main(int argc, char *argv[]) {
  argc = argc;
  argv = argv;
  searchTree tree;

  tree.firstNode = NULL;

  tree.firstNode = allocateFirstNode(tree.firstNode, 3);

  printf("%d\n", tree.firstNode->val);

  allocateNode(tree.firstNode, 5);

  freeTree(tree.firstNode);

  return 0;
}

void allocateNode(node *root, int value) {
  if (root->val < value) {
    /* right block */
    if (root->right != NULL)
      allocateNode(root->right, value);
    root->right = (node *)malloc(sizeof(node));
    root->right->right = NULL;
    root->right->left = NULL;
    root->right->val = value;
    printf("Alocado o valor %d.\n", root->right->val);
  } else {
    /* left block */
    if (root->left != NULL)
      allocateNode(root->left, value);
    root->left = (node *)malloc(sizeof(node));
    root->left->right = NULL;
    root->left->left = NULL;
    root->left->val = value;
    printf("Alocado o valor %d.\n", root->left->val);
  }
}

node *allocateFirstNode(node *which, int value) {
  which = (node *)malloc(sizeof(node));
  which->left = NULL;
  which->right = NULL;
  which->val = value;
  printf("Alocado o valor %d no primeiro no.\n", which->val);
  return which;
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
void search(node *root, int who, int *returnCode) {
  if (root == NULL) {
    *returnCode = EMPTY_TREE;
  } else if (who == root->val) {
    *returnCode = FOUND;
  } else if (who < root->val) {
    if (root->left == NULL) {
      *returnCode = LEFT_NOT_FOUND;
    } else {
      root = root->left;
      search(root, who, returnCode);
    }
  } else if (root->right == NULL) {
    *returnCode = RIGHT_NOT_FOUND;
  } else {
    root = root->right;
    search(root, who, returnCode);
  }
}

void deleteNode(node *startedNode, int who) {
  // TODO
}
