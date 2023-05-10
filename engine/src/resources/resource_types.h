#pragma once

#include "math/math_types.h"

// Pre-defined resource types
typedef enum resource_type {
    RESOURCE_TYPE_TEXT,
    RESOURCE_TYPE_BINARY,
    RESOURCE_TYPE_IMAGE,
    RESOURCE_TYPE_MATERIAL,
    RESOURCE_TYPE_SHADER,
    RESOURCE_TYPE_MESH,
    RESOURCE_TYPE_BITMAP_FONT,
    RESOURCE_TYPE_SYSTEM_FONT,
	RESOURCE_TYPE_SIMPLE_SCENE,
    RESOURCE_TYPE_CUSTOM
} resource_type;

// A magic number indicating the file as a kohi binary file
#define RESOURCE_MAGIC 0xcafebabe

typedef struct resource_header {
    u32 magic_number;
    u8 resource_type;
    u8 version;
    u16 reserved;
} resource_header;

typedef struct resource {
    u32 loader_id;
    const char* name;
    char* full_path;
    u64 data_size;
    void* data;
} resource;

typedef struct image_resource_data {
    u8 channel_count;
    u32 width;
    u32 height;
    u8* pixels;
} image_resource_data;

typedef struct image_resource_params {
    b8 flip_y;
} image_resource_params;

typedef enum face_cull_mode {
    FACE_CULL_MODE_NONE = 0x0,
    FACE_CULL_MODE_FRONT = 0x1,
    FACE_CULL_MODE_BACK = 0x2,
    FACE_CULL_MODE_FRONT_AND_BACK = 0x3
} face_cull_mode;

#define TEXTURE_NAME_MAX_LENGTH 512

typedef enum texture_flag {
    TEXTURE_FLAG_HAS_TRANSPARENCY = 0x1,
    TEXTURE_FLAG_IS_WRITEABLE = 0x2,
    TEXTURE_FLAG_IS_WRAPPED = 0x4,
	TEXTURE_FLAG_DEPTH = 0x8
} texture_flag;

typedef u8 texture_flag_bits;

typedef enum texture_type {
    TEXTURE_TYPE_2D,
    TEXTURE_TYPE_CUBE
} texture_type;

typedef struct texture {
    u32 id;
    texture_type type;
    u32 width;
    u32 height;
    u8 channel_count;
    texture_flag_bits flags;
    u32 generation;
    char name[TEXTURE_NAME_MAX_LENGTH];
    void* internal_data;
} texture;

typedef enum texture_use {
    TEXTURE_USE_UNKNOWN = 0x00,
    TEXTURE_USE_MAP_DIFFUSE = 0x01,
    TEXTURE_USE_MAP_SPECULAR = 0x02,
    TEXTURE_USE_MAP_NORMAL = 0x03,
    TEXTURE_USE_MAP_CUBEMAP = 0x04,
} texture_use;

// Represents supported texture filtering modes
typedef enum texture_filter {
    TEXTURE_FILTER_MODE_NEAREST = 0x0,
    TEXTURE_FILTER_MODE_LINEAR = 0x1
} texture_filter;

typedef enum texture_repeat {
    TEXTURE_REPEAT_REPEAT = 0x1,
    TEXTURE_REPEAT_MIRRORED_REPEAT = 0x2,
    TEXTURE_REPEAT_CLAMP_TO_EDGE = 0x3,
    TEXTURE_REPEAT_CLAMP_TO_BORDER = 0x4
} texture_repeat;

typedef struct texture_map {
    texture* texture;
    texture_use use;
    texture_filter filter_minify;
    texture_filter filter_magnify;
    texture_repeat repeat_u;
    texture_repeat repeat_v;
    texture_repeat repeat_w;
    void* internal_data;
} texture_map;

typedef struct font_glyph {
    i32 codepoint;
    u16 x;
    u16 y;
    u16 width;
    u16 height;
    i16 x_offset;
    i16 y_offset;
    i16 x_advance;
    u8 page_id;
} font_glyph;

typedef struct font_kerning {
    i32 codepoint_0;
    i32 codepoint_1;
    i16 amount;
} font_kerning;

typedef enum font_type {
    FONT_TYPE_BITMAP,
    FONT_TYPE_SYSTEM
} font_type;

typedef struct font_data {
    font_type type;
    char face[256];
    u32 size;
    i32 line_height;
    i32 baseline;
    i32 atlas_size_x;
    i32 atlas_size_y;
    texture_map atlas;
    u32 glyph_count;
    font_glyph* glyphs;
    u32 kerning_count;
    font_kerning* kernings;
    f32 tab_x_advance;
    u32 internal_data_size;
    void* internal_data;
} font_data;

typedef struct bitmap_font_page {
    i8 id;
    char file[256];
} bitmap_font_page;

typedef struct bitmap_font_resource_data {
    font_data data;
    u32 page_count;
    bitmap_font_page* pages;
} bitmap_font_resource_data;

typedef struct system_font_face {
    char name[256];
} system_font_face;

typedef struct system_font_resource_data {
    // darray
    system_font_face* fonts;
    u64 binary_size;
    void* font_binary;
} system_font_resource_data;

#define MATERIAL_NAME_MAX_LENGTH 256

typedef struct material_config {
    char name[MATERIAL_NAME_MAX_LENGTH];
    char* shader_name;
    b8 auto_release;
    vec4 diffuse_color;
    f32 shininess;
    char diffuse_map_name[TEXTURE_NAME_MAX_LENGTH];  
    char specular_map_name[TEXTURE_NAME_MAX_LENGTH];
    char normal_map_name[TEXTURE_NAME_MAX_LENGTH];
} material_config;

typedef struct material {
    u32 id;
    u32 generation;
    u32 internal_id;
    char name[MATERIAL_NAME_MAX_LENGTH];
    vec4 diffuse_color;
    texture_map diffuse_map;
    texture_map specular_map;
    texture_map normal_map;
    f32 shininess;

    u32 shader_id;

    // Synced to the renderer's current frame number when the material has been applied that frame
    u32 render_frame_number;
} material;

#define GEOMETRY_NAME_MAX_LENGTH 256

/**
 * Represents actual geometry in the world. Typically (but
 * not always, depending on use) paired with a material.
 */
typedef struct geometry {
    u32 id;
    u32 internal_id;
    u16 generation;
    vec3 center;
    extents_3d extents;
    char name[GEOMETRY_NAME_MAX_LENGTH];
    material* material;
} geometry;

struct geometry_config;
typedef struct mesh_config {
	char* name;
	char* parent_name;
	char* resource_name;
	u16 geometry_count;
	struct geometry_config* g_configs;
} mesh_config;

typedef struct mesh {
	char* name;
	mesh_config config;
	u32 unique_id;
    u8 generation;
    u16 geometry_count;
    geometry** geometries;
    transform transform;
} mesh;

// Shader stages available in the system
typedef enum shader_stage {
    SHADER_STAGE_VERTEX = 0x00000001,
    SHADER_STAGE_GEOMETRY = 0x00000002,
    SHADER_STAGE_FRAGMENT = 0x00000004,
    SHADER_STAGE_COMPUTE = 0x0000008
} shader_stage;

// Available attribute types
typedef enum shader_attribute_type {
    SHADER_ATTRIB_TYPE_FLOAT32 = 0U,
    SHADER_ATTRIB_TYPE_FLOAT32_2 = 1U,
    SHADER_ATTRIB_TYPE_FLOAT32_3 = 2U,
    SHADER_ATTRIB_TYPE_FLOAT32_4 = 3U,
    SHADER_ATTRIB_TYPE_MATRIX_4 = 4U,
    SHADER_ATTRIB_TYPE_INT8 = 5U,
    SHADER_ATTRIB_TYPE_UINT8 = 6U,
    SHADER_ATTRIB_TYPE_INT16 = 7U,
    SHADER_ATTRIB_TYPE_UINT16 = 8U,
    SHADER_ATTRIB_TYPE_INT32 = 9U,
    SHADER_ATTRIB_TYPE_UINT32 = 10U,
} shader_attribute_type;

// Available uniform types
typedef enum shader_uniform_type {
    SHADER_UNIFORM_TYPE_FLOAT32 = 0U,
    SHADER_UNIFORM_TYPE_FLOAT32_2 = 1U,
    SHADER_UNIFORM_TYPE_FLOAT32_3 = 2U,
    SHADER_UNIFORM_TYPE_FLOAT32_4 = 3U,
    SHADER_UNIFORM_TYPE_INT8 = 4U,
    SHADER_UNIFORM_TYPE_UINT8 = 5U,
    SHADER_UNIFORM_TYPE_INT16 = 6U,
    SHADER_UNIFORM_TYPE_UINT16 = 7U,
    SHADER_UNIFORM_TYPE_INT32 = 8U,
    SHADER_UNIFORM_TYPE_UINT32 = 9U,
    SHADER_UNIFORM_TYPE_MATRIX_4 = 10U,
    SHADER_UNIFORM_TYPE_SAMPLER = 11U,
    SHADER_UNIFORM_TYPE_CUSTOM = 255U
} shader_uniform_type;

// Defines shader scope, which indicates how often it gets updated
typedef enum shader_scope {
    SHADER_SCOPE_GLOBAL = 0,
    SHADER_SCOPE_INSTANCE = 1,
    SHADER_SCOPE_LOCAL = 2
} shader_scope;

// Configuration for an attribute
typedef struct shader_attribute_config {
    u8 name_length;
    char* name;
    u8 size;
    shader_attribute_type type;
} shader_attribute_config;

// Configuration for a uniform
typedef struct shader_uniform_config {
    u8 name_length;
    char* name;
    u16 size;
    u32 location;
    shader_uniform_type type;
    shader_scope scope;
} shader_uniform_config;

// Configuration for a shader. Typically created and destroyed by the shader
//  resource loader, and set to the properties found in a .shadercfg resource file
typedef struct shader_config {
    char* name;

    face_cull_mode cull_mode;

    u8 attribute_count;
    shader_attribute_config* attributes;

    u8 uniform_count;
    shader_uniform_config* uniforms;
    u8 stage_count;
    shader_stage* stages;
    char** stage_names;
    char** stage_filenames;
	b8 depth_test;
	b8 depth_write;
} shader_config;

typedef struct skybox_simple_scene_config {
	char* name;
	char* cubemap_name;
} skybox_simple_scene_config;

typedef struct directional_light_simple_scene_config {
	char* name;
	vec4 color;
	vec4 direction;
} directional_light_simple_scene_config;

typedef struct point_light_simple_scene_config {
	char* name;
	vec4 color;
	vec4 position;
	f32 constant_f;
	f32 linear;
	f32 quadratic;
} point_light_simple_scene_config;

typedef struct mesh_simple_scene_config {
	char* name;
	char* resource_name;
	transform transform;
	char* parent_name; // Optional
} mesh_simple_scene_config;

typedef struct simple_scene_config {
	char* name;
	char* description;
	skybox_simple_scene_config skybox_config;
	directional_light_simple_scene_config directional_light_config;
	
	// darray
	point_light_simple_scene_config* point_lights;
	
	// darray
	mesh_simple_scene_config* meshes;
} simple_scene_config;
