/* Lucas Roberto Raineri Oliveira - 38346 */
/* Codigo formatado utilizando o clang-format no formato LLVM*/

#include <stdio.h>

#include "gfx/gfx.h"

/* Constantes */
enum { INSERT, REMOVE, SEARCH, LEFT, RIGHT };
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

void allocateNode(node *starterNode, int value);
node *allocateFirstNode(node *which, int value);
void drawNode();
void drawTree();

int main(int argc, char *argv[]) {
  argc = argc;
  argv = argv;
  searchTree tree;

  tree.firstNode = NULL;

  tree.firstNode = allocateFirstNode(tree.firstNode, 3);

  printf("%d\n", tree.firstNode->val);

  free(tree.firstNode);

  return 0;
}

void allocateNode(node *starterNode, int value) {
  if (starterNode->val < value) {
    /* right block */
    if (starterNode->right != NULL)
      allocateNode(starterNode->right, value);
    starterNode->right = (node *)malloc(sizeof(node));
    starterNode->right->right = NULL;
    starterNode->right->left = NULL;
    starterNode->right->val = value;
    printf("Alocado o valor %d.\n", starterNode->right->val);
  } else {
    /* left block */
    if (starterNode->left != NULL)
      allocateNode(starterNode->left, value);
    starterNode->left = (node *)malloc(sizeof(node));
    starterNode->left->right = NULL;
    starterNode->left->left = NULL;
    starterNode->left->val = value;
    printf("Alocado o valor %d.\n", starterNode->left->val);
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
