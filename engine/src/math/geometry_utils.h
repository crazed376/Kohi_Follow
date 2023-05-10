#pragma once

#include "math_types.h"

// Calculates normals for the given vertex and index data. Modifies vertices in place
void geometry_generate_normals(u32 vertex_count, vertex_3d* vertices, u32 index_count, u32* indices);

// Calculates tangents for the given vertex and index data. Modifies vertices in place
void geometry_generate_tangents(u32 vertex_count, vertex_3d* vertices, u32 index_count, u32* indices);

// De-duplicate vertices, leaving only unique onces. Leaves the original vertices array intact.
// Allocates a new array in  out_vertices. Modifies indices in-place. Original vertex array
// should be freed by caller
void geometry_deduplicate_vertices(u32 vertex_count, vertex_3d* vertices, u32 index_count, u32* indices, u32* out_vertex_count, vertex_3d** out_vertices);
