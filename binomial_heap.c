
#include <binomial_heap.h>


Binomial_heap*
make_binomial_heap(void)
{
    return NULL;
}

Node*
binomial_heap_minimum(Binomial_heap* bh)
{
    Node* min_node = NULL;
    Node* x = bh->head;
    int min = INT_MAX;
    while (x) {
        if (x->key < min) {
            min = x->key;
            min_node = x;
        }
        x = x->sibling;
    }
    return min_node;
}

void
binomial_link(Node* y, Node* z)
{
    y->p = z;
    y->sibling = z->child;
    z->child = y;
    z->degree++
}

Node*
add_nodes_roots(Node* n1, Node* n2)
{
    if (!n1)
        return n2;
    n1->sibling = n2;
    n2->p = n1;
    return n1;
}

void
binomial_heap_merge(Binomial_heap* h1, Binomial_heap* h2)
{
    Node* h1_nodes = h1->head;
    Node* h2_nodes = h2->head;
    Node* resulting = NULL;
    while (h1_nodes && h2_nodes) {
        if (h1_nodes->degree >= h2_nodes) {
            resulting = add_nodes_roots(resulting, h1_nodes);
        } else {
            resulting = add_nodes_roots(resulting, h2_nodes);
        }
    }
    resulting = add_nodes_roots(resulting, h1_nodes ? h1_nodes : h2_nodes);
    return resulting
}

Binomial_heap*
binomial_heap_union(Binomial_heap* h1, Binomial_heap* h2)
{
    Binomial_heap* new_heap = make_binomial_heap();
    new_heap->head = binomial_heap_merge(h1, h2);
    free(h1);
    free(h2);
    if (!new_heap->head)
        return new_heap;
    Node* prev_x = NULL
    Node* x = new_heap->head;
    Node* next_x = x->sibling;
    while (next_x) {
        if ( (x->degree != next_x->degree)
            || (next_x->sibling && next_x->sibling->degree = x->degree)) {
            prev_x = x;
            x = next_x;
        } else if (x->key <= next_x->key) {
            x->sibling = next_x->sibling;
            binomial_link(next_x, x);
        } else if (!prev_x) {
            new_heap->head = next_x;
        } else {
            prev_x->sibling = next_x;
            binomial_link(x, next_x);
            x = next_x;
        }
        next_x = x->sibling;
    }
    return new_heap;
}

Binomial_heap*
binomial_heap_insert(Binomial_heap* H, Node* x)
{
    Binomial_heap* new_heap = make_binomial_heap();
    x->p = NULL;
    x->child = NULL;
    x->sibling = NULL;
    x->degree = 0;
    new_heap->head = x;
    return binomial_heap_union(H, new_heap);
}

void
remove_root_node(Node* n)
{
    if (n->p)
        n->p->sibling = n->sibling;
    if (n->sibling) {
        n->sibling->p = n->p;
    }
}

Binomial_heap*
binomial_heap_extract_min(Binomial_heap* H)
{
    if (!H->head) {
        return H;
    }
    Binomial_heap* new_heap = make_binomial_heap();
    /* Find and remove minimum */
    Node* min_node = NULL;
    int min = INT_MAX;
    Node* current = H->head;
    while (current) {
        if (current->key < min) {
            min = current->key;
            min_node = current;
        }
    }
    remove_root_node(min_node);
    /* Not done yet */
}
