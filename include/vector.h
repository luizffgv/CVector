/*
    Copyright © 2021 Luiz Fernando F. G. Valle
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#ifndef VECTOR_VECTOR_H_INCLUDED
#define VECTOR_VECTOR_H_INCLUDED

#include <stdbool.h>
#include <stddef.h>

typedef struct Vector_ *Vector;

/**
 * @brief Creates a new Vector.
 *
 * @param elem_sz Size of each element
 *
 * @return Newly created vector
 */
Vector VecNew(size_t elem_sz);

/**
 * @brief Deletes a Vector.
 *
 * @param vec Target Vector
 */
void VecDelete(Vector vec);

/**
 * @brief Returns the number of elements in the Vector.
 *
 * @param Target Vector
 */
size_t VecLength(Vector vec);

/**
 * @brief Returns the size of an Element of the Vector.
 *
 * @param vec Target Vector
 */
size_t VecSize(Vector vec);

/**
 * @brief Returns how many elements the Vector's data can currently hold.
 *
 * @param vec Target Vector
 */
size_t VecCapacity(Vector vec);

/**
 * @brief Returns the Vector's raw data.
 *
 * @param vec Target Vector
 *
 * @return Pointer to the Vector's data
 */
void *VecData(Vector vec);

/**
 * @brief Deletes the Vector's elements.
 *
 * @param vec Target Vector
 */
void VecDataFree(Vector vec);

/**
 * @brief Steals the Vector's data and its ownership.
 *
 * Stolen data should be freed later.
 *
 * @param vec Target Vector
 *
 * @return Pointer to the stolen data
 */
void *VecDataSteal(Vector vec);

/**
 * @brief Gets a pointer to an element of the Vector.
 *
 * @param vec Target Vector
 * @param index Element index
 */
void *VecAt(Vector vec, size_t index);

/**
 * @brief Steals the desired element and its ownership from the Vector.
 *
 * Stolen element should be freed later
 *
 * @param vec Target Vector
 * @param index Index of the desired element
 *
 * @return Pointer to the element
 */
void *VecPopAt(Vector vec, size_t index);

/**
 * @brief Returns a pointer to the last element of the Vector.
 *
 * @param vec Target Vector
 */
void *VecBack(Vector vec);

/**
 * @brief Steals the last element and its ownership from the Vector.
 *
 * Popped element should be freed later
 *
 * @param vec Target Vector
 *
 * @return Pointer to the element
 */
void *VecPopBack(Vector vec);

/**
 * @brief Appends an element to the Vector by copy.
 *
 * @param vec Target Vector
 * @param elem Pointer to the element
 */
void VecPushBack(Vector vec, void *elem);

/**
 * @brief Executes a callback on each of the Vector's elements, in order.
 *
 * @param vec Target Vector
 * @param callback Callback
 */
void VecForEach(Vector vec, void (*callback)(void *));

/**
 * @brief Returns the first element that matches a predicate.
 *
 * @param vec Target vector
 * @param predicate Predicate
 *
 * @return Pointer to the element if matched, NULL otherwise
 */
void *VecFindIf(Vector vec, bool (*predicate)(void *));

#endif // #ifndef VECTOR_VECTOR_H_INCLUDED
