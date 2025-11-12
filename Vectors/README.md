# Vector (Array) with Win32 GUI

A simple Win32 dialog-based application demonstrating an array-backed Vector data structure in C, controlled through a GUI.

## Project Structure

- `main.cpp`
  - Win32 dialog code. Wires GUI controls to the vector operations.
  - Initializes/frees the vector; parses inputs; updates the list and status.
- `vector.h`
  - C interface for the vector data structure (safe for C/C++ usage).
- `vector.c`
  - C implementation of a dynamic array vector with rank-based operations.
- `resource.h`
  - Numeric IDs for dialog and controls used by the GUI/resources.
- `resource.rc`
  - Dialog layout and controls (buttons, listbox, status text).
- `manifest.xml`
  - Application manifest.
- `Vectors.cbp`
  - Code::Blocks project file.

## Vector API

Implemented in pure C (array/dynamic reallocation):

- `void vector_init(Vector* v, size_t initial_capacity)`
- `void vector_free(Vector* v)`
- `size_t vector_size(const Vector* v)`
- `bool vector_is_empty(const Vector* v)`
- `bool vector_elemRank(const Vector* v, size_t rank, int* out_value)`
- `bool vector_replaceRank(Vector* v, size_t rank, int new_value, int* old_value)`
- `bool vector_insertRank(Vector* v, size_t rank, int value)`
- `bool vector_removeRank(Vector* v, size_t rank, int* removed_value)`

Notes:
- `rank` is zero-based.
- Insert allows `rank == size` (append).
- Functions return `true` on success; `false` on invalid rank or allocation failure where applicable.

## GUI Overview

The app shows a dialog titled "Vector Operations" with a larger layout:

- Rank (edit) and Value (edit)
- Buttons: elemRank, replaceRank, insertRank, removeRank, size, isEmpty
- Vector (listbox): displays `index: value` for each element
- Status (multiline, read-only): shows results and errors

### Operations via GUI

- Enter a number in `Rank` and (if needed) a number in `Value`.
- Click a button:
  - `elemRank`: Reads value at rank.
  - `replaceRank`: Replaces value at rank with the given value.
  - `insertRank`: Inserts the given value at rank (0..size).
  - `removeRank`: Removes the element at rank.
  - `size`: Displays the number of elements.
  - `isEmpty`: Displays whether the vector is empty.
- The list refreshes after modifying operations.
- The status area displays the last operation outcome.

## Build and Run (Code::Blocks)

1. File → Open → select `Vectors.cbp`.
2. Choose a target (Debug/Release) from the toolbar.
3. Build → Build or F9 (Build & Run).
4. Build → Run or Ctrl+F10.

Toolchain requirements:
- MinGW/GCC with Win32 SDK headers/libraries.
- Resource compiler (WINDRES) available to compile `resource.rc`.
- Project links `user32`, `gdi32`, `kernel32`, `comctl32` (already configured).

## Troubleshooting

- Missing toolchain: Settings → Compiler → Toolchain executables → Auto-detect.
- RC compile error: Ensure `windres`/resource compiler paths are correct.
- Link errors for common controls: Ensure `comctl32` remains linked in the project.
- UI too small: The dialog has been enlarged to 420x300 dialog units; adjust in `resource.rc` if you want even larger.

## Extending

- Add push_back/pop_back convenience wrappers.
- Persist vector to a file (save/load).
- Add input validation hints (e.g., graying out buttons when inputs are empty).
- Add keyboard shortcuts and context menu for the listbox.
