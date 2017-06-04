#ifndef ALGORITHM_WINDOWS_TREE_RENDER_H
#define ALGORITHM_WINDOWS_TREE_RENDER_H

#include <string>
#include "data_structure/binary_tree.h"
#include <d2d1_1.h>

namespace algorithm
{
    namespace windows
    {
        namespace detail
        {
            void render_node(ID2D1RenderTarget* render_target, ID2D1SolidColorBrush* brush, double x, double y);

            void render_line(ID2D1SolidColorBrush* brush, double x1, double y1, double x2, double y2);
        }

        template<int (*Comparator)(const std::string&, const std::string&)>
        class TreeRender
        {
        public:
            explicit TreeRender(BinaryTree<std::string, std::string, Comparator>* the_tree): the_tree_(the_tree){};

            TreeRender(const TreeRender&) = delete;

            TreeRender& operator=(const TreeRender* rhs) = delete;

            void render(ID2D1RenderTarget* render_target)
            {
                ID2D1SolidColorBrush* black_brush;
                render_target->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Black, 1.0f), &black_brush);
                auto *root = the_tree_->getRootNode();
                if (!root)
                {
                    return;
                }
                detail::render_node(render_target, black_brush, 10, 10);
            };
            

        private:
            BinaryTree<std::string, std::string, Comparator> *the_tree_;
        };
    }
}


#endif //ALGORITHM_WINDOWS_TREE_RENDER_H