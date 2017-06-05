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
            typedef typename BinaryTree<std::string, std::string, Comparator>::node node;

        public:
            explicit TreeRender(BinaryTree<std::string, std::string, Comparator>* the_tree, ID2D1RenderTarget* render_target)
            :render_target_(render_target),
            the_tree_(the_tree)
            {
                HRESULT result = render_target->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Black, 1.0f), &black_brush_);
                assert(result == S_OK);
            };

            TreeRender(const TreeRender&) = delete;

            TreeRender& operator=(const TreeRender* rhs) = delete;

            ~TreeRender()
            {
                if (black_brush_)
                {
                    black_brush_->Release();
                }
            }

            void render()
            {
                const node *root = the_tree_->getRootNode();
                if (!root)
                {
                    return;
                }

                D2D1_SIZE_F render_target_size = render_target_->GetSize();
                render_node(root, render_target_size.width, render_target_size.width / 2, 20);
            };

            void render_node(const node* current, const double render_target_width, double x, double y)
            {
                if (!current)
                {
                    return;
                }
                D2D1_ELLIPSE ellipse;
                ellipse.point.x = static_cast<float>(x);
                ellipse.point.y = static_cast<float>(y);
                ellipse.radiusX = 20;
                ellipse.radiusY = 20;
                render_target_->FillEllipse(ellipse, black_brush_);
                if (current->left)
                {
                    render_node(current->left, render_target_width, x / 2, y + 100);
                    render_line(x, y, x / 2, y + 100);
                }
                
                if (current->right)
                {
                    render_node(current->right, render_target_width, render_target_width - x / 2, y + 100);
                    render_line(x, y, render_target_width - x / 2, y + 100);
                }
            }

            void render_line(double x1, double y1, double x2, double y2)
            {
                render_target_->DrawLine(
                    D2D1::Point2F(static_cast<float>(x1), static_cast<float>(y1)),
                    D2D1::Point2F(static_cast<float>(x2), static_cast<float>(y2)),
                    black_brush_,
                    1
                );
            }

        private:
            ID2D1RenderTarget* render_target_;
            ID2D1SolidColorBrush* black_brush_;
            BinaryTree<std::string, std::string, Comparator> *the_tree_;
        };
    }
}


#endif //ALGORITHM_WINDOWS_TREE_RENDER_H