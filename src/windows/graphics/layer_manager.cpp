#include <common/macro.h> // global macro staff
#include <cassert>
#include "./layer_manager.h"
#include <common/map_util.h>

using std::set;
using std::map;
using std::string;
using std::to_string;
using algorithm::windows::LayerManager;
using algorithm::common::keySet;

ID2D1BitmapRenderTarget* LayerManager::getLayer(int index, ID2D1RenderTarget* parent)
{
    if (layers_.find(index) == layers_.end()) {
        ID2D1BitmapRenderTarget* new_created_render_target;
        assert(SUCCEEDED(parent->CreateCompatibleRenderTarget(&new_created_render_target)));
        layers_[index] = new_created_render_target;
    }
    return layers_[index];
}

void LayerManager::freeLayer(int index)
{
    map<int, ID2D1BitmapRenderTarget*>::const_iterator find_result = layers_.find(index);
    if (find_result == layers_.cend()) {
        return;
    }
    find_result->second->Release();
    layers_.erase(find_result);
}

void LayerManager::freeLayers(set<int> layers)
{
    for (set<int>::const_iterator iterator = layers.cbegin(); iterator != layers.cend(); ++iterator) {
        freeLayer(*iterator);
    }
}

void LayerManager::freeLayers()
{
    for (
        map<int, ID2D1BitmapRenderTarget*>::const_iterator layer_iterator = layers_.cbegin();
        layer_iterator != layers_.cend();
        ++layer_iterator
        )
    {
        layer_iterator->second->Release();
    }
    layers_.clear();
}

ID2D1Bitmap* LayerManager::combineLayer(int which, ID2D1RenderTarget* parent)
{
    set<int> layer_index_set;
    layer_index_set.insert(which);
    return combineLayers(layer_index_set, parent);
}

ID2D1Bitmap* LayerManager::combineLayers(set<int> which, ID2D1RenderTarget* parent)
{
    ID2D1BitmapRenderTarget *temporary_layer;
    ID2D1Bitmap *temporary_bitmap;
    assert(SUCCEEDED(parent->CreateCompatibleRenderTarget(&temporary_layer)));
    temporary_layer->BeginDraw();
    for (set<int>::const_iterator iterator = which.cbegin(); iterator != which.cend(); ++iterator) {
        map<int, ID2D1BitmapRenderTarget*>::const_iterator layer_find_result = layers_.find(*iterator);
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
    return combineLayers(keySet(layers_), parent);
}

string LayerManager::toString()
{
    string result = "Currently, I am managing "
        + to_string(size()) + " ID2D1BitmapRenderTarget pointers. ";
    return result;
}