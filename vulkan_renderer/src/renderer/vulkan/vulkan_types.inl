#pragma once

#include "defines.h"
#include "core/asserts.h"
#include "renderer/renderer_types.inl"
#include "containers/freelist.h"
#include "containers/hashtable.h"

#include <vulkan/vulkan.h>

// Checks the given expression's return value against VK_SUCCESS
#define VK_CHECK(expr)                  \
    {                                   \
        KASSERT(expr == VK_SUCCESS);    \
    }

struct vulkan_context;
typedef struct vulkan_buffer {
    VkBuffer handle;
    VkBufferUsageFlagBits usage;
    b8 is_locked;
    VkDeviceMemory memory;
    VkMemoryRequirements memory_requirements;
    i32 memory_index;
    u32 memory_property_flags;
} vulkan_buffer;

typedef struct vulkan_swapchain_support_info {
    VkSurfaceCapabilitiesKHR capabilities;
    u32 format_count;
    VkSurfaceFormatKHR* formats;
    u32 present_mode_count;
    VkPresentModeKHR* present_modes;
} vulkan_swapchain_support_info;

typedef struct vulkan_device {
    VkPhysicalDevice physical_device;
    VkDevice logical_device;
    vulkan_swapchain_support_info swapchain_support;
    i32 graphics_queue_index;
    i32 present_queue_index;
    i32 transfer_queue_index;
    b8 supports_device_local_host_visible;

    VkQueue graphics_queue;
    VkQueue present_queue;
    VkQueue transfer_queue;

 	VkCommandPool graphics_command_pool;
    VkPhysicalDeviceProperties properties;
    VkPhysicalDeviceFeatures features;
    VkPhysicalDeviceMemoryProperties memory;

    VkFormat depth_format;
    u8 depth_channel_count;
} vulkan_device;

typedef struct vulkan_image {
    VkImage handle;
    VkDeviceMemory memory;
    VkImageView view;
    VkMemoryRequirements memory_requirements;
    VkMemoryPropertyFlags memory_flags;
    u32 width;
    u32 height;
	char* name;
} vulkan_image;

typedef enum vulkan_render_pass_state {
    READY,
    RECORDING,
    IN_RENDER_PASS,
    RECORDING_ENDED,
    SUBMITTED,
    NOT_ALLOCATED
} vulkan_render_pass_state;

typedef struct vulkan_renderpass {
    VkRenderPass handle;
    f32 depth;
    u32 stencil;

    vulkan_render_pass_state state;
} vulkan_renderpass;

typedef struct vulkan_swapchain {
    VkSurfaceFormatKHR image_format;
    u8 max_frames_in_flight;
	
	renderer_config_flags flags;
    VkSwapchainKHR handle;
    u32 image_count;
    texture* render_textures;

    texture* depth_textures;

    render_target render_targets[3];
} vulkan_swapchain;

// Represents all of the available states that a command buffer can be in
typedef enum vulkan_command_buffer_state {
    COMMAND_BUFFER_READY,
    COMMAND_BUFFER_RECORDING,
    COMMAND_BUFFER_IN_RENDER_PASS,
    COMMAND_BUFFER_RECORDING_ENDED,
    COMMAND_BUFFER_SUBMITTED,
    COMMAND_BUFFER_NOT_ALLOCATED
} vulkan_command_buffer_state;

typedef struct vulkan_command_buffer {
    VkCommandBuffer handle;

    // Command buffer state
    vulkan_command_buffer_state state;
} vulkan_command_buffer;

typedef struct vulkan_shader_stage {
    VkShaderModuleCreateInfo create_info;
    VkShaderModule handle;
    VkPipelineShaderStageCreateInfo shader_stage_create_info;
} vulkan_shader_stage;

typedef struct vulkan_pipeline_config {
	vulkan_renderpass* renderpass;
	u32 stride;
	u32 attribute_count;
	VkVertexInputAttributeDescription* attributes;
	u32 descriptor_set_layout_count;
	VkDescriptorSetLayout* descriptor_set_layouts;
	u32 stage_count;
	VkPipelineShaderStageCreateInfo* stages;
	VkViewport viewport;
	VkRect2D scissor;
	face_cull_mode cull_mode;
	b8 is_wireframe;
	u32 shader_flags;
	u32 push_constant_range_count;
	range* push_constant_ranges;	
} vulkan_pipeline_config;

typedef struct vulkan_pipeline {
    VkPipeline handle;
    VkPipelineLayout pipeline_layout;
} vulkan_pipeline;

// Max number of material instances
// TODO: make configurable
#define VULKAN_MAX_MATERIAL_COUNT 1024

// Max number of simultaneously uploaded geometries
// TODO: make configurable
#define VULKAN_MAX_GEOMETRY_COUNT 4096

// Internal buffer data for geometry
typedef struct vulkan_geometry_data {
    u32 id;
    u32 generation;
    u32 vertex_count;
    u32 vertex_element_size;
    u64 vertex_buffer_offset;
    u32 index_count;
    u32 index_element_size;
    u64 index_buffer_offset;
} vulkan_geometry_data;

// Max number of ui control instances
// TODO: make configurable
#define VULKAN_MAX_UI_COUNT 1024

// Put some hard limits in place for the count of supported textures,
// attributes, uniforms, etc. This is to maintain memory locality
// and avoid dynamic allocations.
#define VULKAN_SHADER_MAX_STAGES 8
#define VULKAN_SHADER_MAX_GLOBAL_TEXTURES 31
#define VULKAN_SHADER_MAX_INSTANCE_TEXTURES 31
#define VULKAN_SHADER_MAX_ATTRIBUTES 16
#define VULKAN_SHADER_MAX_UNIFORMS 128
#define VULKAN_SHADER_MAX_BINDINGS 2
#define VULKAN_SHADER_MAX_PUSH_CONST_RANGES 32

// Configuration for a shader stage, such as vertex or fragment
typedef struct vulkan_shader_stage_config {
    VkShaderStageFlagBits stage;
    char file_name[255];
} vulkan_shader_stage_config;

typedef struct vulkan_descriptor_set_config {
    u8 binding_count;
    VkDescriptorSetLayoutBinding bindings[VULKAN_SHADER_MAX_BINDINGS];
    u8 sampler_binding_index;
}vulkan_descriptor_set_config;

typedef struct vulkan_shader_config {
    u8 stage_count;
    vulkan_shader_stage_config stages[VULKAN_SHADER_MAX_STAGES];
    VkDescriptorPoolSize pool_sizes[2];
    u16 max_descriptor_set_count;
    u8 descriptor_set_count;
    vulkan_descriptor_set_config descriptor_sets[2];
    VkVertexInputAttributeDescription attributes[VULKAN_SHADER_MAX_ATTRIBUTES];
    face_cull_mode cull_mode;
} vulkan_shader_config;

// Represents a state for a given descriptor. This is used
// to determine when a descriptor needs updating. There is
// a state per frame (with a max of 3).
typedef struct vulkan_descriptor_state {
    u8 generations[3];
    u32 ids[3];
} vulkan_descriptor_state;

// Represents the state for a descriptor set. This is used to track
// generations and updates, potentially for optimizations via
// skipping sets which do not need updating
typedef struct vulkan_shader_descriptor_set_state {
    VkDescriptorSet descriptor_sets[3];
    vulkan_descriptor_state descriptor_states[VULKAN_SHADER_MAX_BINDINGS];
} vulkan_shader_descriptor_set_state;

typedef struct vulkan_shader_instance_state {
    u32 id;
    u64 offset;
    vulkan_shader_descriptor_set_state descriptor_set_state;
    struct texture_map** instance_texture_maps;
} vulkan_shader_instance_state;

typedef struct vulkan_shader {
    void* mapped_uniform_buffer_block;
    u32 id;
    vulkan_shader_config config;
    vulkan_renderpass* renderpass;
    vulkan_shader_stage stages[VULKAN_SHADER_MAX_STAGES];
    VkDescriptorPool descriptor_pool;
    VkDescriptorSetLayout descriptor_set_layouts[2];
    VkDescriptorSet global_descriptor_sets[3];
    renderbuffer uniform_buffer;
    vulkan_pipeline pipeline;
    u32 instance_count;
    vulkan_shader_instance_state instance_states[VULKAN_MAX_MATERIAL_COUNT];

    u8 global_uniform_count;
    u8 global_uniform_sampler_count;
    u8 instance_uniform_count;
    u8 instance_uniform_sampler_count;
    u8 local_uniform_count;
} vulkan_shader;

typedef struct vulkan_context {
	// The framebuffer's current width
    u32 framebuffer_width;

    // The framebuffer's current height
    u32 framebuffer_height;

    // Current generation of framebuffer size. If it does not match 
    // framebuffer_size_last_generation, a new one should be generated
    u64 framebuffer_size_generation;

    // The generation of the framebuffer when it was last created.
    // Set to framebuffer_size_generation when updated
    u64 framebuffer_size_last_generation;

	vec4 viewport_rect;
	vec4 scissor_rect;
    VkInstance instance;
    VkAllocationCallbacks* allocator;
    VkSurfaceKHR surface;

#if defined(_DEBUG)
    VkDebugUtilsMessengerEXT debug_messenger;

    PFN_vkSetDebugUtilsObjectNameEXT pfnSetDebugUtilsObjectNameEXT;
    PFN_vkSetDebugUtilsObjectTagEXT pfnSetDebugUtilsObjectTagEXT;
    PFN_vkCmdBeginDebugUtilsLabelEXT pfnCmdBeginDebugUtilsLabelEXT;
    PFN_vkCmdEndDebugUtilsLabelEXT pfnCmdEndDebugUtilsLabelEXT;
#endif

    vulkan_device device;

    vulkan_swapchain swapchain;

    renderbuffer object_vertex_buffer;
    renderbuffer object_index_buffer;

    // darray
    vulkan_command_buffer* graphics_command_buffers;

    // darray
    VkSemaphore* image_available_semaphores;

    // darray
    VkSemaphore* queue_complete_semaphores;

    u32 in_flight_fence_count;
    VkFence in_flight_fences[2];

    // Holds pointers to fences which exist and are owned elsewhere, one per frame
    VkFence images_in_flight[3];

    u32 image_index;
    u32 current_frame;

    b8 recreating_swapchain;

	b8 render_flag_changed;
	
    // TODO: make dynamic
    vulkan_geometry_data geometries[VULKAN_MAX_GEOMETRY_COUNT];

    // Render targets used for world rendering
    render_target world_render_targets[3];

    // Indicates if multi-threading is supported by this device
    b8 multithreading_enabled;

    // A function pointer to find a memory index of the given type and with the given properties
    i32 (*find_memory_index)(struct vulkan_context* context, u32 type_filter, u32 property_flags);
} vulkan_context;
