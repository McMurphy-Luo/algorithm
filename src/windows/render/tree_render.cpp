#include "tree_render.h"
#include <cassert>

namespace algorithm
{
    namespace windows
    {
        TreeRender::TreeRender(const node* root_node):
            root_(root_node),
            black_brush_(nullptr),
            red_brush_(nullptr),
            white_brush_(nullptr)
        {
            
        }

        TreeRender::~TreeRender()
        {
            if (black_brush_)
            {
                black_brush_->Release();
                black_brush_ = nullptr;
            }
            if (white_brush_)
            {
                white_brush_->Release();
                white_brush_ = nullptr;
            }
            if (red_brush_)
            {
                red_brush_->Release();
                red_brush_ = nullptr;
            }
        }

        void TreeRender::reCreateD2D1Resource(ID2D1RenderTarget* render_target)
        {
            HRESULT result = render_target->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Black, 1.0f), &black_brush_);
            assert(result == S_OK);
            result = render_target->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Red, 1.0F), &red_brush_);
            assert(result == S_OK);
            result = render_target->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::White, 1.0F), &white_brush_);
            assert(result == S_OK);
        }

        void TreeRender::render(ID2D1RenderTarget* render_target)
        {
            if (!root_)
            {
                return;
            }

            D2D1_SIZE_F render_target_size = render_target->GetSize();
            render_node(render_target, root_, render_target_size.width / 2, 50, render_target_size.width / 2);
        };

        void TreeRender::render_node(ID2D1RenderTarget* render_target, const node* current, double x, double y, double offset_to_parent)
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
            if (current->color == NodeColor::black)
            {
                render_target->FillEllipse(ellipse, black_brush_);
            }
            if (current->color == NodeColor::red)
            {
                render_target->FillEllipse(ellipse, red_brush_);
            }

            if (current->left)
            {
                render_node(render_target, current->left, x - offset_to_parent / 2, y + 50, offset_to_parent / 2);
                render_line(render_target, x, y, x - offset_to_parent / 2, y + 50);
            }

            if (current->right)
            {
                render_node(render_target, current->right, x + offset_to_parent / 2, y + 50, offset_to_parent / 2);
                render_line(render_target, x, y, x + offset_to_parent / 2, y + 50);
            }
        }

        void TreeRender::render_line(ID2D1RenderTarget* render_target, double x1, double y1, double x2, double y2)
        {
            render_target->DrawLine(
                D2D1::Point2F(static_cast<float>(x1), static_cast<float>(y1)),
                D2D1::Point2F(static_cast<float>(x2), static_cast<float>(y2)),
                black_brush_,
                1
            );
        }

        void TreeRender::render_key(ID2D1RenderTarget* render_target)
        {

        }
    }
}