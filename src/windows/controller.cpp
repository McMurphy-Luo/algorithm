#include <common/macro.h> // config macro staff
#include "./controller.h"
#include <cassert>
#include <thread>
#include <cinttypes>
#include <string>
#include <memory>
#include <common/string_util.h>
#include <common/log_manager.h>
#include "./graphics/color.h"
#include "./graphics/text.h"

using std::wstring;
using std::string;
using std::make_shared;
using std::shared_ptr;
using algorithm::common::LogManager;
using algorithm::common::wStringToU8String;
using algorithm::windows::MainWindow;
using algorithm::windows::Controller;

int algorithm::windows::detail::string_comparator(const std::string& lhs, const std::string& rhs)
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

Controller::Controller(MainWindow *main_window):
    class_logger(LogManager::getLogger("algorithm.windows.Controller")),
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
    command_callback_(
        std::make_shared<std::function<LRESULT(WPARAM, LPARAM)>>(
            std::bind(
                std::mem_fn(&Controller::onCommand),
                this,
                std::placeholders::_1,
                std::placeholders::_2
            )
        )
    ),
    need_resize_(true),
    main_scene_(make_shared<Scene>()),
    the_tree_(),
    button_(CreateWindowExW(
        0,
        L"BUTTON",
        L"OK",
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        10,
        10,
        70,
        40,
        main_window->getWindowHandler(),
        nullptr,
        main_window->getAppHandler(),
        nullptr
    )),
    input_(CreateWindowExW(
        0,
        L"EDIT",
        L"",
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | WS_BORDER,
        100,
        100,
        100,
        100,
        main_window->getWindowHandler(),
        nullptr,
        main_window->getAppHandler(),
        nullptr
    )),
    factory_(nullptr),
    render_target_(nullptr)
{
    HRESULT result = CoInitialize(NULL);
    assert(result == S_OK);
    result = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, __uuidof(ID2D1Factory), reinterpret_cast<void**>(&factory_));
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
    main_window->bind(Event::COMMAND, command_callback_);
    main_window->bind(Event::PAINT, paint_callback_);
}

Controller::~Controller()
{
    main_window_->unbind(Event::SIZE, resize_callback_);
    main_window_->unbind(Event::COMMAND, command_callback_);
    main_window_->unbind(Event::PAINT, paint_callback_);
    DestroyWindow(button_);
    DestroyWindow(input_);
    if (render_target_)
    {
        render_target_->Release();
    }
    if (factory_)
    {
        factory_->Release();
    }
    CoUninitialize();
}

LRESULT Controller::render(WPARAM w_param, LPARAM l_param)
{
    main_scene_->render(render_target_);
    HRESULT result;
    if (need_resize_)
    {
        RECT client_rect = main_window_->getSize();
        D2D1_SIZE_U client_size;
        client_size.width = client_rect.right - client_rect.left;
        client_size.height = client_rect.bottom - client_rect.top;
        result = render_target_->Resize(client_size);
        assert(result == S_OK);
        createRenderObjects();
    }
    return 0; // always succeed
}

LRESULT Controller::onCommand(WPARAM w_param, LPARAM l_param)
{
    if (HIWORD(w_param) == BN_CLICKED) {
        int input_text_length = GetWindowTextLengthW(input_);
        wchar_t* buf = new wchar_t[input_text_length + 1];
        GetWindowTextW(input_, buf, input_text_length + 1);
        buf[input_text_length] = 0;
        the_tree_.put(wStringToU8String(wstring(buf)), wStringToU8String(wstring(buf)));
        createRenderObjects();
        render(w_param, l_param);
        delete[] buf;
    }
    return 0;
}

void Controller::createRenderObjects()
{
    main_scene_->clearChildren();
    const TreeNode<string, string> *root_node = the_tree_.getRootNode();
    if (!root_node) {
        return;
    }
    Color black(0, 0, 0);
    Color red(255, 0, 0);
    Color node_color(0, 0, 0);
    if (NodeColor::black == root_node->color) {
        node_color = black;
    } else if (NodeColor::red == root_node->color) {
        node_color = red;
    }
    RECT scene_size = main_window_->getSize();
    double circle_radius = 30;
    double circle_x = (scene_size.right - scene_size.left) / 2 - circle_radius;
    double circle_y = circle_radius;
    class_logger.debug("Creating circle, its x,y is set to %f,%f, its radius is set to %f.", circle_x, circle_y, circle_radius);
    shared_ptr<Circle> tree_node = make_shared<Circle>(circle_radius, node_color, node_color, circle_y, circle_x);
    main_scene_->appendChild(tree_node);
    shared_ptr<Text> node_text = make_shared<Text>(root_node->value, 0, 0);
    tree_node->appendChild(node_text);
}