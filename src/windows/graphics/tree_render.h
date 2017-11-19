#ifndef ALGORITHM_WINDOWS_TREE_RENDER_H
#define ALGORITHM_WINDOWS_TREE_RENDER_H

#include <string>
#include <dwrite.h>
#include <d2d1_1.h>
#include "data_structure/tree_node.h"


namespace algorithm
{
    namespace windows
    {
        class TreeRender
        {
        public:
            typedef TreeNode<std::string, std::string> node;

        public:
            explicit TreeRender();

            TreeRender(const TreeRender&) = delete;

            TreeRender& operator=(const TreeRender* rhs) = delete;

            ~TreeRender();

            void render(ID2D1RenderTarget* render_target, const node* which);

        protected:
            void reCreateD2D1Resource(ID2D1RenderTarget* render_target);

            void render_node(ID2D1RenderTarget* render_target, const node* current, double x, double y, double offset_to_parent);

            void render_line(ID2D1RenderTarget* render_target, double x1, double y1, double x2, double y2);

            void render_key(ID2D1RenderTarget* render_target, const node* current, double x, double y);

        private:
            ID2D1SolidColorBrush* black_brush_;
            ID2D1SolidColorBrush* white_brush_;
            ID2D1SolidColorBrush* red_brush_;
            ID2D1SolidColorBrush* green_brush_;
            IDWriteFactory* write_factory_;
            IDWriteTextFormat* text_format_;
        };
    }
}


#endif //ALGORITHM_WINDOWS_TREE_RENDER_H
