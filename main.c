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
  node *root;
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
void deleteNode(searchTree *tree, node *who);

/* substitui a subarvore com raiz em u pela com raiz em v */
void transplant(searchTree *tree, node *u, node *v);

node *tree_min(node *root);
node *tree_max(node *root);

void drawNode();
void drawTree();

int main(int argc, char *argv[]) {
  argc = argc;
  argv = argv;
  searchTree tree;
  node *ptr;
  int retCode;

  tree.root = NULL;

  insertNode(&tree.root, 3);
  insertNode(&tree.root, 1);
  insertNode(&tree.root, 7);
  insertNode(&tree.root, 2);
  insertNode(&tree.root, 5);
  insertNode(&tree.root, 4);
  insertNode(&tree.root, 6);

  ptr = tree.root;

  printf("%d\n", tree.root->val);

  search(&ptr, 5, &retCode);
  if (retCode == FOUND) {
    deleteNode(&tree, ptr);
    free(ptr);
  }

  freeTree(tree.root);
  tree.root = NULL;

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

void deleteNode(searchTree *tree, node *who) {
  if (who->left == NULL) {
    transplant(tree, who, who->right);
  } else if (who->right == NULL) {
    transplant(tree, who, who->left);
  } else {
    node *y;
    y = tree_min(who->right);
    if (y != who) {
      transplant(tree, y, y->right);
      y->right = who->right;
    }
    transplant(tree, who, y);
    y->left = who->left;
  }
}

/* NOTE: usando os algoritmos passados em aula, conforme instruido */
void transplant(searchTree *tree, node *u, node *v) {
  if (u == NULL) {
    tree->root = v;
  } else if (u == u->left) {
    u->left = v;
  } else
    u->right = v;
  if (v != NULL)
    v = u;
}

/* NOTE: como nao tinha implementacao desses metodos nos slides, eu fiz o meu
 * proprio */
node *tree_min(node *root) {
  if (root->left == NULL)
    return root;
  return tree_min(root->left);
}

/* NOTE: como nao tinha implementacao desses metodos nos slides, eu fiz o meu
 * proprio */
node *tree_max(node *root) {
  if (root->right == NULL)
    return root;
  return tree_min(root->right);
}
