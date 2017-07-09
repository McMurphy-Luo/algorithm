#ifndef ALGORITHM_WINDOWS_TREE_RENDER_H
#define ALGORITHM_WINDOWS_TREE_RENDER_H

#include <string>
#include "data_structure/tree_node.h"
#include <d2d1_1.h>

namespace algorithm
{
    namespace windows
    {
        class TreeRender
        {
        public:
            typedef TreeNode<std::string, std::string> node;

        public:
            explicit TreeRender(const node* root_node);

            TreeRender(const TreeRender&) = delete;

            TreeRender& operator=(const TreeRender* rhs) = delete;

            ~TreeRender();

            void render(ID2D1RenderTarget* render_target);

        protected:
            void reCreateD2D1Resource(ID2D1RenderTarget* render_target);

            void render_node(ID2D1RenderTarget* render_target, const node* current, double x, double y, double offset_to_parent);

            void render_line(ID2D1RenderTarget* render_target, double x1, double y1, double x2, double y2);

            void render_key(ID2D1RenderTarget* render_target);

        private:
            const node* root_;
            ID2D1SolidColorBrush* black_brush_;
            ID2D1SolidColorBrush* white_brush_;
            ID2D1SolidColorBrush* red_brush_;
        };
    }
}


#endif //ALGORITHM_WINDOWS_TREE_RENDER_H
