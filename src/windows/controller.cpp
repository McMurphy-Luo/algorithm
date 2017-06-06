#include "controller.h"
#include <cassert>
#include <thread>
#include "data_structure/binary_tree.h"
#include "./render/tree_render.h"

using namespace algorithm;
using namespace windows;

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


namespace // unamed namespace start for this file static staff
{
    Controller* the_controller = nullptr;
    MainWindow* the_window = nullptr;
    
    LRESULT resize_callback(WPARAM w_param, LPARAM l_param)
    {
        assert(the_controller);
        assert(the_window);
        the_controller->setNeedResize(true);
        return 0;
    }

    LRESULT render_callback(WPARAM w_param, LPARAM l_param)
    {
        assert(the_controller);
        assert(the_window);
        the_controller->render();
        return 0;
    }
} // unamed namespace end

Controller::Controller(MainWindow* main_window):
main_window_(main_window),
need_resize_(false)
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
    the_controller = this;
    the_window = main_window;
    main_window->bind(Event::SIZE, resize_callback);
    assert(result == S_OK);

    auto the_tree = std::make_shared<BinaryTree<std::string, std::string, detail::string_comparator>>();
    the_tree->put("1", "1");
    the_tree->put("2", "2");
    the_tree->put("3", "3");
    the_tree->put("4", "4");
    the_tree->put("5", "5");
    tree_render_ = new TreeRender<detail::string_comparator>(the_tree, render_target_);

    startRender();
}

Controller::~Controller()
{
    main_window_->unbind(Event::SIZE, resize_callback);
    stopRender();
    the_window = nullptr;
    the_controller = nullptr;
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

void Controller::render()
{
    HRESULT result;
    render_target_->BeginDraw();
    render_target_->Clear(D2D1::ColorF(D2D1::ColorF::SkyBlue));

    tree_render_->render();

    result = render_target_->EndDraw();
    assert(result == S_OK);
    if (the_controller->getNeedResize())
    {
        RECT client_rect = the_window->getSize();
        D2D1_SIZE_U client_size;
        client_size.width = client_rect.right - client_rect.left;
        client_size.height = client_rect.bottom - client_rect.top;
        result = render_target_->Resize(client_size);
        assert(result == S_OK);
    }
}

void Controller::startRender() const
{
    main_window_->bind(Event::PAINT, render_callback);
}

void Controller::stopRender() const
{
    main_window_->unbind(Event::PAINT, render_callback);
}