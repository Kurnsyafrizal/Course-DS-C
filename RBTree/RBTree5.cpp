#include <stdio.h>
#include <stdlib.h>

enum COLOR {Red, Black};

typedef struct tree_node {
  int data;
  struct tree_node *right;
  struct tree_node *left;
  struct tree_node *parent;
  enum COLOR color;
}tree_node;

typedef struct red_black_tree {
  tree_node *root;
  tree_node *NIL;
}red_black_tree;

tree_node* new_tree_node(int data) {
  tree_node* n = (struct tree_node*)malloc(sizeof(tree_node));
  n->left = NULL;
  n->right = NULL;
  n->parent = NULL;
  n->data = data;
  n->color = Red;

  return n;
}

red_black_tree* new_red_black_tree() {
  red_black_tree *t = (struct red_black_tree*)malloc(sizeof(red_black_tree));
  tree_node *nil_node = (struct tree_node*) malloc(sizeof(tree_node));
  nil_node->left = NULL;
  nil_node->right = NULL;
  nil_node->parent = NULL;
  nil_node->color = Black;
  nil_node->data = 0;
  t->NIL = nil_node;
  t->root = t->NIL;

  return t;
}

void left_rotate(red_black_tree *t, tree_node *x) {
  tree_node *y = x->right;
  x->right = y->left;
  if(y->left != t->NIL) {
    y->left->parent = x;
  }
  y->parent = x->parent;
  if(x->parent == t->NIL) { //x is root
    t->root = y;
  }
  else if(x == x->parent->left) { //x is left child
    x->parent->left = y;
  }
  else { //x is right child
    x->parent->right = y;
  }
  y->left = x;
  x->parent = y;
}

void right_rotate(red_black_tree *t, tree_node *x) {
  tree_node *y = x->left;
  x->left = y->right;
  if(y->right != t->NIL) {
    y->right->parent = x;
  }
  y->parent = x->parent;
  if(x->parent == t->NIL) { //x is root
    t->root = y;
  }
  else if(x == x->parent->right) { //x is left child
    x->parent->right = y;
  }
  else { //x is right child
    x->parent->left = y;
  }
  y->right = x;
  x->parent = y;
}

void insertion_fixup(red_black_tree *t, tree_node *z) {
  while(z->parent->color == Red) {
    if(z->parent == z->parent->parent->left) { //z.parent is the left child

      tree_node *y = z->parent->parent->right; //uncle of z

      if(y->color == Red) { //case 1
        z->parent->color = Black;
        y->color = Black;
        z->parent->parent->color = Red;
        z = z->parent->parent;
      }
      else { //case2 or case3
        if(z == z->parent->right) { //case2
          z = z->parent; //marked z.parent as new z
          left_rotate(t, z);
        }
        //case3
        z->parent->color = Black; //made parent black
        z->parent->parent->color = Red; //made parent red
        right_rotate(t, z->parent->parent);
      }
    }
    else { //z.parent is the right child
      tree_node *y = z->parent->parent->left; //uncle of z

      if(y->color == Red) {
        z->parent->color = Black;
        y->color = Black;
        z->parent->parent->color = Red;
        z = z->parent->parent;
      }
      else {
        if(z == z->parent->left) {
          z = z->parent; //marked z.parent as new z
          right_rotate(t, z);
        }
        z->parent->color = Black; //made parent black
        z->parent->parent->color = Red; //made parent red
        left_rotate(t, z->parent->parent);
      }
    }
  }
  t->root->color = Black;
}

void insert(red_black_tree *t, tree_node *z) {
  tree_node* y = t->NIL; //variable for the parent of the added node
  tree_node* temp = t->root;

  while(temp != t->NIL) {
    y = temp;
    if(z->data < temp->data)
      temp = temp->left;
    else
      temp = temp->right;
  }
  z->parent = y;

  if(y == t->NIL) { //newly added node is root
    t->root = z;
  }
  else if(z->data < y->data) //data of child is less than its parent, left child
    y->left = z;
  else
    y->right = z;

  z->right = t->NIL;
  z->left = t->NIL;

  insertion_fixup(t, z);
}

void rb_transplant(red_black_tree *t, tree_node *u, tree_node *v) {
  if(u->parent == t->NIL)
    t->root = v;
  else if(u == u->parent->left)
    u->parent->left = v;
  else
    u->parent->right = v;
  v->parent = u->parent;
}

tree_node* minimum(red_black_tree *t, tree_node *x) {
  while(x->left != t->NIL)
    x = x->left;
  return x;
}

void rb_delete_fixup(red_black_tree *t, tree_node *x) {
  while(x != t->root && x->color == Black) {
    if(x == x->parent->left) {
      tree_node *w = x->parent->right;
      if(w->color == Red) {
        w->color = Black;
        x->parent->color = Red;
        left_rotate(t, x->parent);
        w = x->parent->right;
      }
      if(w->left->color == Black && w->right->color == Black) {
        w->color = Red;
        x = x->parent;
      }
      else {
        if(w->right->color == Black) {
          w->left->color = Black;
          w->color = Red;
          right_rotate(t, w);
          w = x->parent->right;
        }
        w->color = x->parent->color;
        x->parent->color = Black;
        w->right->color = Black;
        left_rotate(t, x->parent);
        x = t->root;
      }
    }
    else {
      tree_node *w = x->parent->left;
      if(w->color == Red) {
        w->color = Black;
        x->parent->color = Red;
        right_rotate(t, x->parent);
        w = x->parent->left;
      }
      if(w->right->color == Black && w->left->color == Black) {
        w->color = Red;
        x = x->parent;
      }
      else {
        if(w->left->color == Black) {
          w->right->color = Black;
          w->color = Red;
          left_rotate(t, w);
          w = x->parent->left;
        }
        w->color = x->parent->color;
        x->parent->color = Black;
        w->left->color = Black;
        right_rotate(t, x->parent);
        x = t->root;
      }
    }
  }
  x->color = Black;
}

void rb_delete(red_black_tree *t, tree_node *z) {
  tree_node *y = z;
  tree_node *x;
  enum COLOR y_orignal_color = y->color;
  if(z->left == t->NIL) {
    x = z->right;
    rb_transplant(t, z, z->right);
  }
  else if(z->right == t->NIL) {
    x = z->left;
    rb_transplant(t, z, z->left);
  }
  else {
    y = minimum(t, z->right);
    y_orignal_color = y->color;
    x = y->right;
    if(y->parent == z) {
      x->parent = z;
    }
    else {
      rb_transplant(t, y, y->right);
      y->right = z->right;
      y->right->parent = y;
    }
    rb_transplant(t, z, y);
    y->left = z->left;
    y->left->parent = y;
    y->color = z->color;
  }
  if(y_orignal_color == Black)
    rb_delete_fixup(t, x);
}

void inorder(red_black_tree *t, tree_node *n) {
  if(n != t->NIL) {
    inorder(t, n->left);
    printf("%d\n", n->data);
    inorder(t, n->right);
  }
}

int main() {
  red_black_tree *t = new_red_black_tree();

  tree_node *a, *b, *c, *d, *e, *f, *g, *h, *i, *j, *k, *l, *m;
  a = new_tree_node(10);
  b = new_tree_node(20);
  c = new_tree_node(30);
  d = new_tree_node(100);
  e = new_tree_node(90);
  f = new_tree_node(40);
  g = new_tree_node(50);
  h = new_tree_node(60);
  i = new_tree_node(70);
  j = new_tree_node(80);
  k = new_tree_node(150);
  l = new_tree_node(110);
  m = new_tree_node(120);

  insert(t, a);
  insert(t, b);
  insert(t, c);
  insert(t, d);
  insert(t, e);
  insert(t, f);
  insert(t, g);
  insert(t, h);
  insert(t, i);
  insert(t, j);
  insert(t, k);
  insert(t, l);
  insert(t, m);

  rb_delete(t, a);
  rb_delete(t, m);

  inorder(t, t->root);

  return 0;
}