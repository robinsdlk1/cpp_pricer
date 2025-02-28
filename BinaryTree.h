#pragma once
#include <vector>
#include <iostream>
#include <iomanip>

template <typename T>
class BinaryTree {
public:
    BinaryTree() : _depth(0) {}

    void setDepth(int depth);
    void setNode(int level, int index, T value);
    T getNode(int level, int index) const;
    void display() const;

private:
    int _depth;
    std::vector<std::vector<T>> _tree;
};

template <typename T>
void BinaryTree<T>::setDepth(int depth) {
    _depth = depth;
    _tree.resize(_depth + 1);
    for (int i = 0; i <= _depth; ++i) {
        _tree[i].resize(i + 1);
    }
}

template <typename T>
void BinaryTree<T>::setNode(int level, int index, T value) {
    if (level <= _depth && index <= level) {
        _tree[level][index] = value;
    }
}

template <typename T>
T BinaryTree<T>::getNode(int level, int index) const {
    if (level <= _depth && index <= level) {
        return _tree[level][index];
    }
    throw std::out_of_range("Invalid indices");
}

template <typename T>
void BinaryTree<T>::display() const {

    if (_depth == 0) return;
    else {

        for (int i = 0; i <= _depth && i < _tree.size(); ++i) {
            for (int j = 0; j <= i && j < _tree[i].size(); ++j) {
                std::cout << _tree[i][j] << " ";
            }
            std::cout << std::endl;
        }
        for (int e = 0; e < 2; e++) {
            std::cout << std::endl;
        }
        for (int i = 0; i <= _depth; ++i) {
            int leadingSpaces = 3 * (_depth - i);

            for (int space = 0; space < leadingSpaces; ++space) {
                std::cout << " ";
            }
            for (int j = 0; j <= i; ++j) {
                std::cout << std::setw(2) << _tree[i][j];
                if (j < i) {
                    for (int space = 0; space < 3; ++space) {
                        std::cout << " ";
                    }
                    if (_tree[i][j] < 99 && std::floor(_tree[i][j]) == _tree[i][j]) {
                        std::cout << " ";
                    }
                }
            }
            std::cout << std::endl;

            if (i < _depth) {
                int slashLeadingSpaces = 3 * (_depth - i) - 1;

                for (int space = 0; space < slashLeadingSpaces; ++space) {
                    std::cout << " ";
                }

                for (int j = 0; j <= i; ++j) {
                    std::cout << "/";
                    for (int space = 0; space < 3; ++space) {
                        std::cout << " ";
                    }
                    std::cout << "\\";
                    if (j < i) {
                        for (int space = 0; space < 1; ++space) {
                            std::cout << " ";
                        }
                    }
                }
                std::cout << std::endl;
            }
        }

        std::cout << std::endl;
    }
}