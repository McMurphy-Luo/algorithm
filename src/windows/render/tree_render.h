#ifndef ALGORITHM_WINDOWS_TREE_RENDER
#define ALGORITHM_WINDOWS_TREE_RENDER

#include <string>
#include "../../data_structure/binary_tree.h"
#include <d2d1.h>

namespace algorithm
{
    namespace windows
    {
        template<typename value_type, int (*Comparator)(const std::string&, const std::string&)>
        class TreeRender
        {
        public:
            TreeRender(BinaryTree<std::string, value_type, Comparator>* the_tree)
                :the_tree_(the_tree) {};

            void render(ID2D1RenderTarget* render_target);

        private:
            D2D1_ELLIPSE ellipse_;
<<<<<<< HEAD
            BinaryTree<std::string, value_type, Comparator>* the_tree_;
=======
            BinaryTree<key_type, value_type, Comparator>* the_tree_;
>>>>>>> 8a5bcab8652461a6b2c712b808956ad0a4d45c78
        };

    }
}


#endif //ALGORITHM_WINDOWS_TREE_RENDER