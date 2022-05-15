#include "avl_tree.hpp"

namespace ankur::avl_detail {

void left_rotate(node* x) {
    assert(x);
    node * y = x->right_child;
    assert(y != nullptr);
    node * b = y->left_child;

    y->parent = x->parent;
    if (x->parent && x->parent->value > x->value) {
        assert(x->parent->left_child);
        x->parent->left_child = y;
    } else if(x->parent && x->parent->value < x->value) {
        assert(x->parent->right_child);
        x->parent->right_child = y;
    }
    x->parent = y;
    y->left_child = x;
    x->right_child = b;
    if (b) {
        b->parent = x;
    }
    x->update_heights();
    y->update_heights();
}

void right_rotate(node* x) {
    assert(x);
    node * y = x->left_child;
    assert(y != nullptr);
    node * b = y->right_child;

    y->parent = x->parent;
    if (x->parent && x->parent->value > x->value) {
        assert(x->parent->left_child);
        x->parent->left_child = y;
    } else if(x->parent && x->parent->value < x->value) {
        assert(x->parent->right_child);
        x->parent->right_child = y;
    }
    x->parent = y;
    y->right_child = x;
    x->left_child = b;
    if (b) {
        b->parent = x;
    }
    x->update_heights();
    y->update_heights();
}

void _do_fix_avl_property(avl_detail::node* node) {
    node->update_heights();
    if (node->heaviness() > 1) {
        if (node->right_child->heaviness() >= 0) {
            left_rotate(node);
        } else {
            right_rotate(node->right_child);
            left_rotate(node);
        }
    } else if (node->heaviness() < -1) {
        if (node->left_child->heaviness() <= 0) {
            right_rotate(node);
        } else {
            left_rotate(node->left_child);
            right_rotate(node);
        }
    }
}

node * fix_avl_property(avl_detail::node* new_node) {
    avl_detail::node * node = new_node;
    if (!node) {
        return node;
    }
    while (true) {
        _do_fix_avl_property(node);
        if (!node->parent) {
            return node;
        }
        node = node->parent;
    }
}

}
