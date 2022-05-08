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

int node_height(node * n) {
    if(!n) {
        return -1;
    }
    return n->height();
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
        fix_avl_property();
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

    void fix_avl_property() {

    }

    avl_detail::node * m_head;
    std::size_t m_size;
};

}
