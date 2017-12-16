#include <common/macro.h> // global macro staff
#include <cassert>
#include "./layer_manager.h"
#include <common/map_util.h>

using std::set;
using std::map;
using std::string;
using std::to_string;
using std::pair;
using algorithm::windows::LayerManager;
using algorithm::common::keySet;
using algorithm::common::differenceTwoSets;

namespace
{
    void initializeSingleLayer(ID2D1BitmapRenderTarget* target)
    {
        target->BeginDraw();
        target->Clear(D2D1::ColorF(1.0, 1.0, 1.0, 0));
    }
}

LayerManager::~LayerManager()
{
    for (
        LayerIterator iterator = layers_.cbegin();
        iterator != layers_.cend();
        ++iterator
        )
    {
        iterator->second->Release();
    }
}

ID2D1BitmapRenderTarget* LayerManager::getLayer(int index, ID2D1RenderTarget* parent)
{
    assert(am_i_in_render_round_);
    ID2D1BitmapRenderTarget* result;
    LayerIterator find_result = layers_.find(index);
    if (find_result == layers_.cend()) {
        ID2D1BitmapRenderTarget* new_created_render_target;
        assert(SUCCEEDED(parent->CreateCompatibleRenderTarget(&new_created_render_target)));
        result = layers_[index] = new_created_render_target;
        initializeSingleLayer(new_created_render_target);
    } else {
        result = find_result->second;
    }
    used_layers_of_render_round_.insert(index);
    return result;
}

void LayerManager::beginDraw()
{
    used_layers_of_render_round_.clear();
    for (
        LayerIterator iterator = layers_.cbegin();
        iterator != layers_.cend();
        ++iterator
        )
    {
        initializeSingleLayer(iterator->second);
    }
    am_i_in_render_round_ = true;
}

void LayerManager::endDraw()
{
    set<int> useless_layers = differenceTwoSets(keySet(layers_), used_layers_of_render_round_);
    for (
        const int useless_layer : useless_layers
        )
    {
        LayerIterator find_result = layers_.find(useless_layer);
        if (find_result == layers_.cend()) {
            return;
        }
        find_result->second->Release();
        layers_.erase(find_result);
    }
    for (
        LayerIterator iterator = layers_.cbegin();
        iterator != layers_.cend();
        ++iterator
        )
    {
        assert(SUCCEEDED(iterator->second->EndDraw()));
    }
    am_i_in_render_round_ = false;
}

ID2D1Bitmap* LayerManager::combineLayer(int which, ID2D1RenderTarget* parent)
{
    assert(am_i_in_render_round_);
    set<int> layer_index_set;
    layer_index_set.insert(which);
    return combineLayers(layer_index_set, parent);
}

ID2D1Bitmap* LayerManager::combineLayers(set<int> which, ID2D1RenderTarget* parent)
{
    assert(am_i_in_render_round_);
    ID2D1BitmapRenderTarget *temporary_layer;
    ID2D1Bitmap *temporary_bitmap;
    assert(SUCCEEDED(parent->CreateCompatibleRenderTarget(&temporary_layer)));
    temporary_layer->BeginDraw();
    temporary_layer->Clear();
    for (set<int>::const_iterator iterator = which.cbegin(); iterator != which.cend(); ++iterator) {
        LayerIterator layer_find_result = layers_.find(*iterator);
        if (layer_find_result == layers_.cend()) {
            continue;
        }
        assert(SUCCEEDED(layer_find_result->second->GetBitmap(&temporary_bitmap)));
        temporary_layer->DrawBitmap(temporary_bitmap);
        temporary_bitmap->Release();
    }
    assert(SUCCEEDED(temporary_layer->EndDraw()));
    assert(SUCCEEDED(temporary_layer->GetBitmap(&temporary_bitmap)));
    temporary_layer->Release();
    return temporary_bitmap;
}

ID2D1Bitmap* LayerManager::combineLayers(ID2D1RenderTarget* parent)
{
    assert(am_i_in_render_round_);
    return combineLayers(keySet(layers_), parent);
}

string LayerManager::toString() const
{
    string result = "Currently, I am managing "
        + to_string(layers_.size()) + " ID2D1BitmapRenderTarget pointers. ";
    return result;
}