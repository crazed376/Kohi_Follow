#pragma once

#include "defines.h"
#include "input.h"

typedef enum keymap_modifier_bits {
	KEYMAP_MODIFIER_NONE_BIT = 0x0,
	KEYMAP_MODIFIER_SHIFT_BIT = 0x1,
	KEYMAP_MODIFIER_CONTROL_BIT = 0x2,
	KEYMAP_MODIFIER_ALT_BIT = 0x4,
} keymap_modifier_bits;

typedef u32 keymap_modifier;

typedef enum keymap_entry_bind_type {
	KEYMAP_BIND_TYPE_UNDEFINED = 0x0,
	KEYMAP_BIND_TYPE_PRESS = 0x1,
	KEYMAP_BIND_TYPE_RELEASE = 0x2,
	KEYMAP_BIND_TYPE_HOLD = 0x4,
	KEYMAP_BIND_TYPE_UNSET = 0x8
} keymap_entry_bind_type;

typedef void (*PFN_keybind_callback)(keys key, keymap_entry_bind_type type, keymap_modifier modifiers, void* user_data);

typedef struct keymap_binding {
	keymap_entry_bind_type type;
	keymap_modifier modifiers;
	PFN_keybind_callback callback;
	void* user_data;
	struct keymap_binding* next;
} keymap_binding;

typedef struct keymap_entry {
	keys key;
	// Linked list of bindings
	keymap_binding* bindings;
} keymap_entry;

typedef struct keymap {
	b8 overrides_all;
	keymap_entry entries[KEYS_MAX_KEYS];
} keymap;

KAPI keymap keymap_create(void);

KAPI void keymap_binding_add(keymap* map, keys key, keymap_entry_bind_type type, keymap_modifier modifiers, void* user_data, PFN_keybind_callback callback);
KAPI void keymap_binding_remove(keymap* map, keys key, keymap_entry_bind_type type, keymap_modifier modifiers, PFN_keybind_callback callback);

KAPI void keymap_clear(keymap* map);
