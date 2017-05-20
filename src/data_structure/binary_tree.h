//
// Created by luojiayi on 5/18/17.
//

#ifndef ALGORITHM_DATA_STRUCTURE_BINARY_TREE_H
#define ALGORITHM_DATA_STRUCTURE_BINARY_TREE_H

namespace algorithm{
    template <typename KeyType, typename PayloadType, class Comparator>
    class BinaryTree{
    public:
        typedef key_type KeyType;
        typedef value_type PayloadType;

    protected:
        struct Node{
            KeyType key;
            PayloadType payload;
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
            * current = root;

            int compare_result = Comparator(key, root->key) < 0;


            if (compare_result){

            }



        };

        void remove(key_type key){

        };






    protected:
        node_type *root;
    };
}

#endif //ALGORITHM_DATA_STRUCTURE_BINARY_TREE_H
