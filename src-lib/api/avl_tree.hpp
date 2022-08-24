#ifndef MY_AVL_TREE_HPP
#define MY_AVL_TREE_HPP

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

void left_rotate(node* x);
void right_rotate(node* x);
node * fix_avl_property(avl_detail::node* new_node);

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

    int find_min() const {
        return find_min_node(m_head)->value;
    }

    void remove(int value) {
        avl_detail::node* affected_node = remove_node_with_value(m_head, value);
        m_head = fix_avl_property(affected_node);
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

        // update heights
        // this is done anyway when we iterate up the tree to confirm
        // avl_property is maintained, so no need to do here
        avl_detail::node * inserted_node = node;
        /*while (node) {
            node->update_heights();
            node = node->parent;
        }*/
        return inserted_node;
    }

    avl_detail::node* find_min_node(avl_detail::node* root) const {
        assert(root);
        while (root->left_child) {
            root = root->left_child;
        }
        return root;
    }

    avl_detail::node* delete_node(avl_detail::node * node) {
        if (!node->left_child && !node->right_child) {
            if (node->parent && node->parent->left_child == node) {
                node->parent->left_child = nullptr;
            } else if(node->parent && node->parent->right_child == node) {
                node->parent->right_child = nullptr;
            }
            avl_detail::node* parent_node = node->parent;
            if (node->parent) {
                node->parent->update_heights();
            }
            node->detach();
            if (m_head == node) {
                m_head = nullptr;
            }
            delete node;
            m_size--;
            return parent_node;
        } else if(!node->left_child || !node->right_child) {
            avl_detail::node* replacement_node = node->left_child;
            if (!replacement_node) {
                replacement_node = node->right_child;
            }
            if (node->parent && node->parent->left_child == node) {
                node->parent->left_child = replacement_node;
            } else if(node->parent && node->parent->right_child == node) {
                node->parent->right_child = replacement_node;
            }
            replacement_node->parent = node->parent;
            if (m_head == node) {
                m_head = replacement_node;
            }
            if (node->parent) {
                node->parent->update_heights();
            }
            node->detach();
            delete node;
            m_size--;
            return replacement_node;
        } else {
            // 2 children
            avl_detail::node* replacement_node = find_min_node(node->right_child);
            node->value = replacement_node->value;
            return remove_node_with_value(node->right_child, replacement_node->value);
        }
    }

    avl_detail::node* remove_node_with_value(avl_detail::node* root, int value) {
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

    avl_detail::node * m_head;
    std::size_t m_size;
};

}

#endif
