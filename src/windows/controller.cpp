﻿#include "controller.h"
#include <cassert>
#include <thread>
#include "./render/tree_render.h"

namespace algorithm
{
    namespace windows
    {
        namespace detail
        {
            int string_comparator(const std::string& lhs, const std::string& rhs)
            {
                if (lhs < rhs)
                {
                    return -1;
                }
                if (lhs > rhs)
                {
                    return 1;
                }
                return 0;
            }
        }
    }
}

using namespace algorithm::windows;

Controller::Controller(MainWindow* main_window):
    main_window_(main_window),
    resize_callback_(
        std::make_shared<std::function<LRESULT(WPARAM, LPARAM)>>(
            std::bind([](Controller* controller, WPARAM w_param, LPARAM l_param) ->LRESULT
                {
                    controller->setNeedResize(true);
                    return 0;
                },
                this,
                std::placeholders::_1,
                std::placeholders::_2
            )
        )
    ),
    paint_callback_(
        std::make_shared<std::function<LRESULT(WPARAM, LPARAM)>>(
            std::bind(
                std::mem_fn(&Controller::render),
                this,
                std::placeholders::_1,
                std::placeholders::_2
            )
        )
    ),
    need_resize_(true),
    the_tree_(RBTree<std::string, std::string, detail::string_comparator>()),
    tree_render_()
{
    HRESULT result = CoInitialize(NULL);
    assert(result == S_OK);
    result = D2D1CreateFactory(D2D1_FACTORY_TYPE_MULTI_THREADED, __uuidof(ID2D1Factory), reinterpret_cast<void**>(&factory_));
    assert(result == S_OK);
    RECT client_rect = main_window->getSize();
    D2D1_SIZE_U client_size;
    client_size.width = client_rect.right - client_rect.left;
    client_size.height = client_rect.bottom - client_rect.top;
    result = factory_->CreateHwndRenderTarget(
        D2D1::RenderTargetProperties(),
        D2D1::HwndRenderTargetProperties(main_window->getWindowHandler(), client_size),
        &render_target_
    );
    assert(result == S_OK);
    main_window->bind(Event::SIZE, resize_callback_);
    the_tree_.put("1", "1");
    the_tree_.put("2", "2");
    the_tree_.put("3", "3");
    the_tree_.put("4", "4");
    the_tree_.put("5", "5");
    the_tree_.put("6", "6");
    the_tree_.put("7", "7");
    the_tree_.put("8", "8");
    the_tree_.put("9", "9");
    the_tree_.put("10", "10");
    the_tree_.put("11", "11");
    the_tree_.put("12", "12");
    the_tree_.put("13", "13");
    the_tree_.put("14", "14");
    the_tree_.put("15", "15");
    startRender();
}

Controller::~Controller()
{
    main_window_->unbind(Event::SIZE, resize_callback_);
    stopRender();
    if (factory_)
    {
        factory_->Release();
    }
    if (render_target_)
    {
        render_target_->Release();
    }
    CoUninitialize();
}

LRESULT Controller::render(WPARAM w_param, LPARAM l_param)
{
    HRESULT result;
    ID2D1RenderTarget* render_target = this->getRenderTarget();
    render_target->BeginDraw();
    render_target->Clear(D2D1::ColorF(D2D1::ColorF::SkyBlue));

    tree_render_.render(render_target_, the_tree_.getRootNode());

    result = render_target->EndDraw();
    assert(result == S_OK);
    if (need_resize_)
    {
        RECT client_rect = main_window_->getSize();
        D2D1_SIZE_U client_size;
        client_size.width = client_rect.right - client_rect.left;
        client_size.height = client_rect.bottom - client_rect.top;
        result = render_target_->Resize(client_size);
        assert(result == S_OK);
    }
    return 0;
}

void Controller::startRender() const
{
    main_window_->bind(Event::PAINT, paint_callback_);
}

void Controller::stopRender() const
{
    main_window_->unbind(Event::PAINT, paint_callback_);
}