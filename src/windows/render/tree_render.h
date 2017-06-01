#ifndef ALGORITHM_WINDOWS_TREE_RENDER
#define ALGORITHM_WINDOWS_TREE_RENDER

#include <string>
#include "../../data_structure/binary_tree.h"
#include "../graphics/transformation.h"
#include <d2d1.h>

namespace algorithm
{
    namespace windows
    {
        template<typename value_type, int (*Comparator)(const std::string&, const std::string&)>
        class TreeRender:  public Transformation
        {
        public:
            TreeRender(BinaryTree<std::string, value_type, Comparator>* the_tree)
                :the_tree_(the_tree) {};

            void render(ID2D1RenderTarget* render_target);

        private:
            BinaryTree<key_type, value_type, Comparator>* the_tree_;
        };

    }
}


#endif //ALGORITHM_WINDOWS_TREE_RENDER