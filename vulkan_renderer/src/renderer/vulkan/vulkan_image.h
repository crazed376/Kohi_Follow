#pragma once

#include "vulkan_types.h"

void vulkan_image_create(vulkan_context* context,
                         texture_type type,
                         u32 width,
                         u32 height,
                         VkFormat format,
                         VkImageTiling tiling,
                         VkImageUsageFlags usage,
                         VkMemoryPropertyFlags memory_flags,
                         b32 create_view,
                         VkImageAspectFlags view_aspect_flags,
						 const char* name,
                         vulkan_image* out_image);

void vulkan_image_view_create(vulkan_context* context,
                              texture_type type,
                              VkFormat format,
                              vulkan_image* image,
                              VkImageAspectFlags aspect_flags);

/**
 * Transitions the provided image from old_layout to new_layout
 */
void vulkan_image_transition_layout(vulkan_context* context,
                                    texture_type type,
                                    vulkan_command_buffer* command_buffer,
                                    vulkan_image* image,
                                    VkFormat format,
                                    VkImageLayout old_layout,
                                    VkImageLayout new_layout);

/**
 * Copies data in buffer to provided image
 */
void vulkan_image_copy_from_buffer(vulkan_context* context,
                                   texture_type type,
                                   vulkan_image* image,
                                   VkBuffer buffer,
                                   vulkan_command_buffer* command_buffer);

/**
 * Copies data in the provided image to the given buffer.
 */
void vulkan_image_copy_to_buffer(vulkan_context* context,
								 texture_type type,
								 vulkan_image* image,
								 VkBuffer buffer,
								 vulkan_command_buffer* command_buffer);

/**
 * Copies a single pixel's data from the given image to the provided buffer.
 */
void vulkan_image_copy_pixel_to_buffer(vulkan_context* context,
									   texture_type type,
									   vulkan_image* image,
									   VkBuffer buffer,
									   u32 x,
									   u32 y,
									   vulkan_command_buffer* command_buffer);

void vulkan_image_destroy(vulkan_context* context, vulkan_image* image);
