#pragma once

#include <renderer/renderer_types.inl>

KAPI b8 plugin_create(renderer_plugin* out_plugin);
KAPI void plugin_destroy(renderer_plugin* plugin);
