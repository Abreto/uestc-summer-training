/* UESTC Summer Training Petrozavodsk Summer-2015. Petr Mitrichev Contest 13. */
/* Problem H, by Abreto. */
#include <stdio.h>
#include <math.h>
#include <string.h>

double vars[26] = {0.0};

typedef struct _treenode
{
  struct _treenode *lchild;
  struct _treenode *rchild;
  char data;  /* if a variable is saved, it's saved as 0-25. */
}treenode, *p_treenode;

double c(p_treenode root)
{
  switch (root->data) {
    case '+':
      return c(root->lchild) + c(root->rchild);
      break;
    case 's':
      return sin(c(root->lchild));
      break;
    default:
      return vars[root->data];
  }
}

double d(p_treenode root, char v)
{
  switch (root->data) {
    case '+':
      return d(root->lchild, v) + d(root->rchild, v);
      break;
    case 's':
      return cos(c(root->lchild)) * d(root->lchild, v);
      break;
    default:
      if( v == root->data )
        return 1;
      else
        return 0;
      break;
  }
}

p_treenode root;
treenode nodes[1024];
int __nodes_index[1024] = {0};

void init_nodes(void)
{
  int i = 0;
  for(i = 0;i < 1024;++i)
    __nodes_index[i] = i+1;
  __nodes_index[1023] = 0;
}

p_treenode new_node(void)
{
  if( __nodes_index[0] > 0 )
  {
    int alloced = __nodes_index[0];
    __nodes_index[0] = __nodes_index[alloced];
    return &(nodes[alloced]);
  }
  else
    return NULL;
}

char expression[512] = "";

char op_stack[1024] = "";  int op_top = 0;
p_treenode node_stack[1024]; int node_top = 0;

void merge_sin(void)
{
  p_treenode si = new_node();
  si->lchild = node_stack[node_top-1];
  si->rchild = NULL;
  si->data = 's';
  op_top--;
  node_stack[node_top-1] = si;
}

void merge_plus(void)
{
  p_treenode plus = new_node();
  plus->lchild = node_stack[node_top-2];
  plus->rchild = node_stack[node_top-1];
  plus->data = '+';
  op_top--;
  node_top--;
  node_stack[node_top-1] = plus;
}

p_treenode generate_tree(void)
{
  int i = 0, l = strlen(expression);
  for(i = 0;i < l;++i)
  {
    switch (expression[i])
    {
      case 's':
        op_stack[op_top++] = 's';
        i += 3;
        break;
      case '+':
        op_stack[op_top++] = '+';
        break;
      case ')':
        merge_sin();
        if( '+' == op_stack[op_top-1] )
          merge_plus();
        break;
      default:
        {
          p_treenode n = new_node();
          n->lchild = n->rchild = NULL;
          n->data = expression[i] - 'a';
          node_stack[node_top++] = n;
          if( '+' == op_stack[op_top-1] )
            merge_plus();
        }
        break;
    }
  }
  return node_stack[0];
}

int main(void)
{
  int i = 0;

  scanf("%s", expression);
  for(i = 0;i < 26;++i)
    scanf("%lf", vars+i);

  init_nodes();
  root = generate_tree();

  printf("%.16f", d(root, 0));
  for(i = 1;i < 26;++i)
    printf(" %.16f", d(root, i));
  return 0;
}
