#include "controller.h"
#include <cassert>
#include <thread>
#include "data_structure/binary_tree.h"
#include "./render/tree_render.h"

using namespace algorithm::windows;

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

    void render()
    {
        assert(the_controller);
        assert(the_window);
        HRESULT result;
        
        algorithm::BinaryTree<std::string, std::string, string_comparator> the_tree;
        the_tree.put("1", "1");
        the_tree.put("2", "2");
        the_tree.put("3", "3");
        the_tree.put("4", "4");
        the_tree.put("5", "5");
        TreeRender<string_comparator> tree_render(&the_tree);

        while (the_controller->getRendering())
        {
            ID2D1HwndRenderTarget* render_target = the_controller->getRenderTarget();
            render_target->BeginDraw();
            render_target->Clear(D2D1::ColorF(D2D1::ColorF::SkyBlue));

            tree_render.render(render_target);

            result = render_target->EndDraw();
            assert(result == S_OK);
            if (the_controller->getNeedResize())
            {
                RECT client_rect = the_window->getSize();
                D2D1_SIZE_U client_size;
                client_size.width = client_rect.right - client_rect.left;
                client_size.height = client_rect.bottom - client_rect.top;
                result = render_target->Resize(client_size);
                assert(result == S_OK);
            }
        }
    }
} // unamed namespace end

Controller::Controller(MainWindow* main_window):
main_window_(main_window),
rendering_(true),
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
    render_thread_ = std::thread(render);
    main_window->bind(Event::SIZE, resize_callback);
    assert(result == S_OK);
}

Controller::~Controller()
{
    main_window_->unbind(Event::SIZE, resize_callback);
    this->stopRender();
    render_thread_.join();
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
