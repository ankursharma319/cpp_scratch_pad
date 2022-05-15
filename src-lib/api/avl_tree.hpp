#include <cassert>
#include <cstddef>
#include <string>
#include <iostream>
#include <sstream>

namespace ankur {

namespace avl_detail {

struct node {
    int value;
    node* parent;
    node* left_child;
    node* right_child;
    int left_height;
    int right_height;

    node(
        int _value=0,
        node* _parent = nullptr,
        node* _left_child=nullptr,
        node* _right_child=nullptr
    ): value(_value)
    , parent(_parent)
    , left_child(_left_child)
    , right_child(_right_child)
    , left_height(-1)
    , right_height(-1)
    {
        update_heights();
    }

    int height() const {
        return 1 + std::max(left_height, right_height);
    }

    int heaviness() const {
        return right_height - left_height;
    }

    void update_heights() {
        left_height = left_child ? left_child->height() : -1;
        right_height = right_child ? right_child->height() : -1;
    }

    void fill_string(std::stringstream & ss, std::string prefix, std::string children_prefix) const {
        ss << prefix << value << "(s=" << heaviness() << ",h=" << height() << ")" << std::endl;
        if (left_child) {
            left_child->fill_string(ss, children_prefix + "|--", children_prefix + "|  ");
        }
        if (right_child) {
            right_child->fill_string(ss, children_prefix + "|--", children_prefix + "   ");
        }
    }

    void detach() {
        left_child = nullptr;
        right_child = nullptr;
        parent = nullptr;
    }
    ~node() {
        if (left_child) {
            delete left_child;
        }
        if (right_child) {
            delete right_child;
        }
        if (parent && parent->left_child == this) {
            parent->left_child = nullptr;
        } else if (parent && parent->right_child == this) {
            parent->right_child = nullptr;
        }
    }
};

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
    node->update_heights();
}

node * fix_avl_property(avl_detail::node* new_node) {
    avl_detail::node * node = new_node;
    while (true) {
        _do_fix_avl_property(node);
        if (!node->parent) {
            return node;
        }
        node = node->parent;
    }
}

}

class avl_tree {

public:
    avl_tree() : m_head(nullptr), m_size(0) {}

    ~avl_tree() {
        if (m_head) {
            delete m_head;
        }
    }

    std::size_t size() const {
        return m_size;
    }

    void insert(int value) {
        avl_detail::node * inserted_node = bst_insert(value);
        if (!inserted_node) {
            return;
        }
        m_head = fix_avl_property(inserted_node);
    }
    std::string to_string() const {
        if (!m_head) return "";
        std::stringstream ss {};
        m_head->fill_string(ss, "", "");
        return ss.str();
    }
private:
    avl_detail::node* bst_insert(int value) {
        if (!m_head) {
            m_head = new avl_detail::node(value, nullptr, nullptr, nullptr);
            m_size ++;
            return m_head;
        }
        avl_detail::node * node = m_head;
        while (node != nullptr) {
            if (node->value == value) {
                // duplicates not allowed
                return nullptr;
            }
            if (node->value > value) {
                if (node->left_child) {
                    node = node->left_child;
                } else {
                    node->left_child = new avl_detail::node(value, node, nullptr, nullptr);
                    m_size ++;
                    node = node->left_child;
                    break;
                }
            } else {
                if (node->right_child) {
                    node = node->right_child;
                } else {
                    node->right_child = new avl_detail::node(value, node, nullptr, nullptr);
                    m_size++;
                    node = node->right_child;
                    break;
                }
            }
        }

        avl_detail::node * inserted_node = node;
        //update heights
        while (node) {
            node->update_heights();
            node = node->parent;
        }
        return inserted_node;
    }

    avl_detail::node * m_head;
    std::size_t m_size;
};

}
