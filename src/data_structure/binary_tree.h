//
// Created by luojiayi on 5/18/17.
//

#ifndef ALGORITHM_DATA_STRUCTURE_BINARY_TREE_H
#define ALGORITHM_DATA_STRUCTURE_BINARY_TREE_H

namespace algorithm{
    template <typename KeyType, typename ValueType, class Comparator>
    class BinaryTree{
    public:
        typedef KeyType key_type;
        typedef ValueType value_type;

    protected:
        struct Node{
            key_type key;
            value_type value;
            Node* left;
            Node* right;
        };

    public:
        BinaryTree(): root(nullptr) {

        };

        BinaryTree(const BinaryTree &another){

        };

        ~BinaryTree(){

        };

        value_type get(key_type key){

        };

        void put(key_type key, value_type value){

            int compare_result = Comparator(key, root->key) < 0;


            if (compare_result){

            }



        };

        void remove(key_type key){

        };






    protected:
        Node* root;
    };
}

#endif //ALGORITHM_DATA_STRUCTURE_BINARY_TREE_H
