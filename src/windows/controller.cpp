#include <common/macro.h> // config macro staff
#include "./controller.h"
#include <cassert>
#include <thread>
#include <cinttypes>
#include <string>
#include <memory>
#include <Windowsx.h>
#include <common/string_util.h>
#include <common/log_manager.h>
#include "./graphics/color.h"
#include "./graphics/text.h"

using std::wstring;
using std::string;
using std::function;
using std::make_shared;
using std::shared_ptr;
using std::bind;
using std::mem_fn;
using std::dynamic_pointer_cast;
using algorithm::common::LogManager;
using algorithm::common::wStringToU8String;
using algorithm::data_structure::RBTree;
using algorithm::data_structure::TreeNode;
using algorithm::data_structure::NodeColor;
using algorithm::windows::MainWindow;
using algorithm::windows::Color;
using algorithm::windows::Controller;
using algorithm::windows::GraphicsBase;
using algorithm::windows::Scene;
using algorithm::windows::Text;
using algorithm::windows::Circle;
using algorithm::windows::detail::string_comparator;

int algorithm::windows::detail::string_comparator(const string& lhs, const string& rhs)
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

namespace // unamed namespace for this file static staff
{
    const int BUTTON_WIDTH = 40;
    const int BUTTON_HEIGHT = 20;
    const int INPUT_WIDTH = 150;
    const int INPUT_HEIGHT = 20;
    const double RADIUS = 30.0;

    void createRenderObjectsForEveryNode(
        const TreeNode<string, string> *node,
        shared_ptr<GraphicsBase> parent,
        double radius,
        double left,
        double top,
        double offset
    )
    {
        if (!node) {
            return;
        }
        Color black(0, 0, 0);
        Color red(255, 0, 0);
        Color white(255, 255, 255);
        Color node_color(0, 0, 0);
        if (NodeColor::black == node->color) {
            node_color = black;
        } else if (NodeColor::red == node->color) {
            node_color = red;
        }
        shared_ptr<Circle> new_circle = make_shared<Circle>(radius, node_color, node_color, left, top);
        new_circle->setBorderWidth(2);
        shared_ptr<Text> circle_content = make_shared<Text>(node->value, 0, 0);
        circle_content->setColor(white);
        new_circle->appendChild(circle_content);
        parent->appendChild(new_circle);
        createRenderObjectsForEveryNode(node->left, parent, radius, left + offset, top + radius * 2, offset / 2);
        createRenderObjectsForEveryNode(node->right, parent, radius, left - offset, top + radius * 2, offset / 2);
    }

    void createRenderObjects(
        ID2D1RenderTarget *render_target,
        const RBTree<string, string, string_comparator> &the_tree,
        shared_ptr<Scene> scene
    )
    {
        double radius = RADIUS;
        scene->clearChildren();
        D2D1_SIZE_F render_target_size = render_target->GetSize();
        createRenderObjectsForEveryNode(
            the_tree.getRootNode(),
            scene,
            radius,
            (render_target_size.width / 2) - radius,
            radius,
            (render_target_size.width / 4)
        );
    }
} // end unamed namespace

Controller::Controller(MainWindow *main_window):
    class_logger(LogManager::getLogger("algorithm.windows.Controller")),
    main_window_(main_window),
    resize_callback_(
        make_shared<function<LRESULT(WPARAM, LPARAM)>>(
            bind(
                mem_fn(&Controller::onSize),
                this,
                std::placeholders::_1,
                std::placeholders::_2
            )
        )
    ),
    paint_callback_(
        make_shared<function<LRESULT(WPARAM, LPARAM)>>(
            bind(
                mem_fn(&Controller::onPaint),
                this,
                std::placeholders::_1,
                std::placeholders::_2
            )
        )
    ),
    command_callback_(
        make_shared<function<LRESULT(WPARAM, LPARAM)>>(
            bind(
                mem_fn(&Controller::onCommand),
                this,
                std::placeholders::_1,
                std::placeholders::_2
            )
        )
    ),
    mouse_move_callback_(
        make_shared<function<LRESULT(WPARAM, LPARAM)>>(
            bind(
                mem_fn(&Controller::onMouseMove),
                this,
                std::placeholders::_1,
                std::placeholders::_2
            )
        )
    ),
    need_resize_(true),
    main_scene_(make_shared<Scene>()),
    current_graphics_under_mouse_(main_scene_),
    previous_border_color_of_circle_(0, 0, 0),
    the_tree_(),
    button_(CreateWindowExW(
        0,
        L"BUTTON",
        L"OK",
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        10,
        10,
        BUTTON_WIDTH,
        BUTTON_HEIGHT,
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
        30,
        100,
        INPUT_WIDTH,
        INPUT_HEIGHT,
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
    main_window->bind(Event::MOUSE_MOVE, mouse_move_callback_);
}

Controller::~Controller()
{
    main_window_->unbind(Event::SIZE, resize_callback_);
    main_window_->unbind(Event::COMMAND, command_callback_);
    main_window_->unbind(Event::PAINT, paint_callback_);
    DestroyWindow(button_);
    DestroyWindow(input_);
    if (render_target_) {
        render_target_->Release();
    }
    if (factory_) {
        factory_->Release();
    }
    CoUninitialize();
}

void Controller::render()
{
    main_scene_->render(render_target_);
    HRESULT result;
    if (need_resize_) {
        RECT client_rect = main_window_->getSize();
        D2D1_SIZE_U client_size;
        client_size.width = client_rect.right - client_rect.left;
        client_size.height = client_rect.bottom - client_rect.top;
        result = render_target_->Resize(client_size);
        assert(result == S_OK);
        createRenderObjects(render_target_, the_tree_, main_scene_);
    }
    need_resize_ = false;
}

void Controller::reArrangeChildWindow()
{
    int two_child_window_combined_width = INPUT_WIDTH + BUTTON_WIDTH + 5;
    RECT main_window_size = main_window_->getSize();
    int main_window_width = main_window_size.right - main_window_size.left;
    int left_most_position = main_window_width / 2 - two_child_window_combined_width / 2;
    SetWindowPos(input_, 0, left_most_position, 5, INPUT_WIDTH, INPUT_HEIGHT, SWP_NOZORDER | SWP_SHOWWINDOW);
    SetWindowPos(button_, 0, left_most_position + INPUT_WIDTH + 5, 5, BUTTON_WIDTH, BUTTON_HEIGHT, SWP_NOZORDER | SWP_SHOWWINDOW);
}

LRESULT Controller::onCommand(WPARAM w_param, LPARAM l_param)
{
    if (HIWORD(w_param) == BN_CLICKED) {
        int input_text_length = GetWindowTextLengthW(input_);
        wchar_t* buf = new wchar_t[input_text_length + 1];
        GetWindowTextW(input_, buf, input_text_length + 1);
        buf[input_text_length] = 0;
        the_tree_.put(wStringToU8String(wstring(buf)), wStringToU8String(wstring(buf)));
        createRenderObjects(render_target_, the_tree_, main_scene_);
        render();
        delete[] buf;
    }
    return 0;
}

LRESULT Controller::onMouseMove(WPARAM w_param, LPARAM l_param)
{
    int top = GET_Y_LPARAM(l_param);
    int left = GET_X_LPARAM(l_param);
    Color green(0, 255, 0);
    shared_ptr<GraphicsBase> graphics_under_mouse_now = main_scene_;
    for (shared_ptr<GraphicsBase> child : main_scene_->getChildren()) {
        if (!child->containsPoint(left, top)) {
            continue;
        }
        graphics_under_mouse_now = child;
    }
    if (current_graphics_under_mouse_ != graphics_under_mouse_now) {
        if (current_graphics_under_mouse_->getType() == Graphics::circle) {
            dynamic_pointer_cast<Circle>(current_graphics_under_mouse_)->setBorderColor(previous_border_color_of_circle_);
        }
        if (graphics_under_mouse_now->getType() == Graphics::circle) {
            previous_border_color_of_circle_ = dynamic_pointer_cast<Circle>(graphics_under_mouse_now)->getBorderColor();
            dynamic_pointer_cast<Circle>(graphics_under_mouse_now)->setBorderColor(green);
        }
    }
    current_graphics_under_mouse_ = graphics_under_mouse_now;
    render();
    return 0;
}

LRESULT Controller::onPaint(WPARAM w_param, LPARAM l_param)
{
    render();
    return 0;
}

LRESULT Controller::onSize(WPARAM w_param, LPARAM l_param)
{
    need_resize_ = true;
    reArrangeChildWindow();
    UpdateWindow(main_window_->getWindowHandler());
    return 0;
}