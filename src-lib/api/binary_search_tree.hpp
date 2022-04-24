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

}

class binary_search_tree {
public:
    binary_search_tree() : m_head(nullptr), m_size(0) {}

    ~binary_search_tree() {
        if (m_head) {
            delete m_head;
        }
    }

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

    int find_min() const {
        return find_min_node(m_head)->value;
    }

    int find_max() const {
        return find_max_node(m_head)->value;
    }

    void remove(int value) {
        remove_node_with_value(m_head, value);
    }

private:
    bst_detail::node* find_min_node(bst_detail::node* root) const {
        assert(root);
        while (root->left_child) {
            root = root->left_child;
        }
        return root;
    }

    bst_detail::node* find_max_node(bst_detail::node* root) const {
        assert(root);
        while (root->right_child) {
            root = root->right_child;
        }
        return root;
    }

    bst_detail::node* delete_node(bst_detail::node * node) {
        if (!node->left_child && !node->right_child) {
            if (node->parent->left_child == node) {
                node->parent->left_child = nullptr;
            } else if(node->parent->right_child == node) {
                node->parent->right_child = nullptr;
            }
            node->detach();
            delete node;
            m_size--;
            return nullptr;
        } else if(!node->left_child || !node->right_child) {
            bst_detail::node* replacement_node = node->left_child;
            if (!replacement_node) {
                replacement_node = node->right_child;
            }
            if (node->parent->left_child == node) {
                node->parent->left_child = replacement_node;
            } else if(node->parent->right_child == node) {
                node->parent->right_child = replacement_node;
            }
            replacement_node->parent = node->parent;
            node->detach();
            delete node;
            m_size--;
            return replacement_node;
        } else {
            // 2 children
            bst_detail::node* replacement_node = find_min_node(node->right_child);
            node->value = replacement_node->value;
            return remove_node_with_value(node->right_child, replacement_node->value);
        }
    }

    bst_detail::node* remove_node_with_value(bst_detail::node* root, int value) {
        if(!root) {
            return nullptr;
        } else if (root->value > value) {
            return remove_node_with_value(root->left_child, value);
        } else if (root->value < value) {
            return remove_node_with_value(root->right_child, value);
        } else {
            //found the node to be deleted
            return delete_node(root);
        }
    }

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
