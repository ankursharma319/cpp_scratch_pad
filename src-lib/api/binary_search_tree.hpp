#include <cassert>
#include <cstddef>
#include <string>
#include <iostream>
#include <sstream>

namespace ankur {

namespace bst_detail {

struct node {
    int value;
    node* parent;
    node* left_child;
    node* right_child;

    node(
        int _value=0,
        node* _parent = nullptr,
        node* _left_child=nullptr,
        node* _right_child=nullptr
    ): value(_value)
    , parent(_parent)
    , left_child(_left_child)
    , right_child(_right_child)
    {}

    void fill_string(std::stringstream & ss, std::string prefix, std::string children_prefix) const {
        ss << prefix << value << std::endl;
        if (left_child) {
            left_child->fill_string(ss, children_prefix + "|--", children_prefix + "|  ");
        }
        if (right_child) {
            right_child->fill_string(ss, children_prefix + "|--", children_prefix + "   ");
        }
    }
};

}

class binary_search_tree {
public:
    binary_search_tree() : m_head(nullptr), m_size(0) {}

    ~binary_search_tree() {}

    bool contains(int value) const {
        return getNode(value) != nullptr;
    }

    void insert(int value) {
        if (!m_head) {
            m_head = new bst_detail::node(value, nullptr, nullptr, nullptr);
            m_size ++;
            return;
        }
        bst_detail::node * node = m_head;
        while (node != nullptr) {
            if (node->value == value) {
                // duplicates not allowed
                return;
            }
            if (node->value > value) {
                if (node->left_child) {
                    node = node->left_child;
                } else {
                    node->left_child = new bst_detail::node(value, node, nullptr, nullptr);
                    m_size ++;
                    node = nullptr;
                }
            } else {
                if (node->right_child) {
                    node = node->right_child;
                } else {
                    node->right_child = new bst_detail::node(value, node, nullptr, nullptr);
                    m_size++;
                }
            }
        }
    }

    std::string to_string() {
        if (!m_head) return "";
        std::stringstream ss {};
        m_head->fill_string(ss, "", "");
        return ss.str();
    }

    std::size_t size() const {
        return m_size;
    }

private:
    bst_detail::node* getNode(int value) const {
        bst_detail::node * node = m_head;
        while (node != nullptr) {
            if (node->value == value) {
                return node;
            } else if (node->value > value) {
                node = node->left_child;
            } else {
                node = node->right_child;
            }
        }
        return nullptr;  
    }

    bst_detail::node * m_head;
    std::size_t m_size;
};

}
