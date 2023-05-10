#pragma once

#include "defines.h"
#include "math/math_types.h"

// Returns the length of the given string
KAPI u64 string_length(const char* str);

// Gets the length of a string in UTF-8 (potentially multibyte) characters
KAPI u32 string_utf8_length(const char* str);

// Obtains bytes needed from the byte array to form a UTF-8 codepoint,
// also providing how many bytes the current character is
KAPI b8 bytes_to_codepoint(const char* bytes, u32 offset, i32* out_codepoint, u8* out_advance);

KAPI char* string_duplicate(const char* str);

// Frees the memory of the given string
KAPI void string_free(char* str);

// Case-sensitive string comparison. True if the same, otherwise false
KAPI b8 strings_equal(const char* str0, const char* str1);

// Case-insensitive string comparison. True if the same, otherwise false
KAPI b8 strings_equali(const char* str0, const char* str1);

// Case-sensitive string comparison for a number of characters
KAPI b8 strings_nequal(const char* str0, const char* str1, u64 length);

// Case-insensitive string comparison for a number of characters
KAPI b8 strings_nequali(const char* str0, const char* str1, u64 length);

// Performs string formatting to dest given format string and parametes
KAPI i32 string_format(char* dest, const char* format, ...);

/**
 * Performs variadic string formatting to dest given format string and va_list.
 * @param dest The destination for the formatted string.
 * @param format The string to be formatted.
 * @param va_list The variadic argument list.
 * @return The size of the data written
 */
KAPI i32 string_format_v(char* dest, const char* format, void* va_list);

/**
 * Empties the provided string by setting the first character to a 0.
 * 
 * @param str The string to be emptied.
 * @return A pointer to str
 */
KAPI char* string_empty(char* str);

KAPI char* string_copy(char* dest, const char* source);

KAPI char* string_ncopy(char* dest, const char* source, i64 length);

KAPI char* string_trim(char* str);

KAPI void string_mid(char* dest, const char* source, i32 start, i32 length);

/**
 * Returns the index of the first occurance of c in str; otherwise -1.
 * 
 * @param str The string to be scanned.
 * @param c The character to search for.
 * @return The index of the first occurance of c; otherwise -1 if not found.
 */
KAPI i32 string_index_of(const char* str, char c);

/**
 * Attempts to parse a transform from the provided string
 * If the string contains 10 elements, rotation is parsed as quaternion.
 * If it contains 9 elements, rotation is parsed as euler angles and is
 * converted to quaternion. Anything else is invalid.
 *
 * @param str The string to parse from
 * @param out_transform A pointer to the transform to write to
 * @return True if parsed successfully, otherwise false
 */
KAPI b8 string_to_transform(const char* str, transform* out_transform);
/**

 * Attempts to parse a vector from the provided string.
 * 
 * @param str The string to parse from. Should be space-delimited (ie. "1.0 2.0 3.0 4.0").
 * @param out_vector A pointer to the vector to write to
 * @return True if parse successfully, otherwise false.
 */
KAPI b8 string_to_vec4(const char* str, vec4* out_vector);

/**
 * Attempts to parse a vector from the provided string.
 * 
 * @param str The string to parse from. Should be space-delimited (ie. "1.0 2.0 3.0").
 * @param out_vector A pointer to the vector to write to
 * @return True if parse successfully, otherwise false.
 */
KAPI b8 string_to_vec3(const char* str, vec3* out_vector);

/**
 * Attempts to parse a vector from the provided string.
 * 
 * @param str The string to parse from. Should be space-delimited (ie. "1.0 2.0").
 * @param out_vector A pointer to the vector to write to
 * @return True if parse successfully, otherwise false.
 */
KAPI b8 string_to_vec2(const char* str, vec2* out_vector);

/**
 * Attempts to parse a 32-bit floating point number from the provided string.
 * 
 * @param str The string to parse from. Should *not* be postfixed with 'f'.
 * @param f A pointer to the float to write to.
 * @return True if parsed successfully, otherwise false.
 */
KAPI b8 string_to_f32(const char* str, f32* f);

/**
 * Attempts to parse a 64-bit floating point number from the provided string.
 * 
 * @param str The string to parse from. Should *not* be postfixed with 'f'.
 * @param f A pointer to the float to write to.
 * @return True if parsed successfully, otherwise false.
 */
KAPI b8 string_to_f64(const char* str, f64* f);

/**
 * Attempts to parse an 8-bit signed integer from the provided string.
 * 
 * @param str The string to parse from.
 * @param i A pointer to the int to write to.
 * @return True if parsed successfully; otherwise false.
 */
KAPI b8 string_to_i8(const char* str, i8* i);

/**
 * Attempts to parse a 16-bit signed integer from the provided string.
 * 
 * @param str The string to parse from.
 * @param i A pointer to the int to write to.
 * @return True if parsed successfully; otherwise false.
 */
KAPI b8 string_to_i16(const char* str, i16* i);

/**
 * Attempts to parse a 32-bit signed integer from the provided string.
 * 
 * @param str The string to parse from.
 * @param i A pointer to the int to write to.
 * @return True if parsed successfully; otherwise false.
 */
KAPI b8 string_to_i32(const char* str, i32* i);

/**
 * Attempts to parse a 64-bit signed integer from the provided string.
 * 
 * @param str The string to parse from.
 * @param i A pointer to the int to write to.
 * @return True if parsed successfully; otherwise false.
 */
KAPI b8 string_to_i64(const char* str, i64* i);

/**
 * Attempts to parse an 8-bit unsigned integer from the provided string.
 * 
 * @param str The string to parse from.
 * @param u A pointer to the int to write to.
 * @return True if parsed successfully; otherwise false.
 */
KAPI b8 string_to_u8(const char* str, u8* u);

/**
 * Attempts to parse a 16-bit unsigned integer from the provided string.
 * 
 * @param str The string to parse from.
 * @param u A pointer to the int to write to.
 * @return True if parsed successfully; otherwise false.
 */
KAPI b8 string_to_u16(const char* str, u16* u);

/**
 * Attempts to parse a 32-bit unsigned integer from the provided string.
 * 
 * @param str The string to parse from.
 * @param u A pointer to the int to write to.
 * @return True if parsed successfully; otherwise false.
 */
KAPI b8 string_to_u32(const char* str, u32* u);

/**
 * Attempts to parse a 64-bit unsigned integer from the provided string.
 * 
 * @param str The string to parse from.
 * @param u A pointer to the int to write to.
 * @return True if parsed successfully; otherwise false.
 */
KAPI b8 string_to_u64(const char* str, u64* u);

/**
 * Attempts to parse a boolean from the provided string.
 * "true" or "1" are considered true; anything else is false.
 * 
 * @param str The string to parse from. "true" or "1" are considered true; anything else is false.
 * @param b A pointer to the boolean to write to.
 * @return True if parsed successfully; otherwise false.
 */
KAPI b8 string_to_bool(const char* str, b8* b);

KAPI u32 string_split(const char* str, char delimiter, char*** str_darray, b8 trim_entries, b8 include_empty);

KAPI void string_cleanup_split_array(char** str_darray);

KAPI void string_append_string(char* dest, const char* source, const char* append);

KAPI void string_append_int(char* dest, const char* source, i64 i);

KAPI void string_append_float(char* dest, const char* source, f32 f);

KAPI void string_append_bool(char* dest, const char* source, b8 b);

KAPI void string_append_char(char* dest, const char* source, char c);

KAPI void string_directory_from_path(char* dest, const char* path);

KAPI void string_filename_from_path(char* dest, const char* path);

KAPI void string_filename_no_extension_from_path(char* dest, const char* path);

// ----------------------
// KString implementation
// ----------------------

typedef struct kstring {
	u32 length;
	u32 allocated;
	char* data;
} kstring;

KAPI void kstring_create(kstring* out_string);
KAPI void kstring_from_cstring(const char* source, kstring* out_string);
KAPI void kstring_destroy(kstring* string);

KAPI u32 kstring_length(const kstring* string);
KAPI u32 kstring_utf8_length(const kstring* string);

KAPI void kstring_append_str(kstring* string, const char* s);
KAPI void kstring_append_kstring(kstring* string, const kstring* other);
