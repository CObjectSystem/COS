/**
 * C Object System
 * COS memory allocator
 *
 * Copyright 2006+ Laurent Deniau <laurent.deniau@gmail.com>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

// --- declarations -----------------------------------------------------------

#include <cos/Object.h>

// --- definitions ------------------------------------------------------------

struct cos_mem_pool_ cos_mem_pool_;
size_t cos_mem_pool_max_ = 1<<25;

enum {
  static_assert__node_size_must_be_a_power_of_2
    = 1/!(cos_mem_node_size_&(cos_mem_node_size_-1))
};

size_t __attribute__ ((noinline))
cos_mem_unused (int *count_, size_t *only_)
{
  if (!count_ && !only_) return cos_mem_pool_.size;

  int start = only_ ? cos_mem_get_slot_(*only_) : 0;
  int end   = only_ ? start+1 : cos_mem_slot_max_;

  // sanity checks
  assert(start < cos_mem_slot_max_);

  struct cos_mem_pool_ *restrict pool = &cos_mem_pool_;
  struct cos_mem_slot_ *restrict pptr = pool->slot+start;
  size_t size  = 0;
  int    count = 0;

  for (int slot=start; slot<end; slot++, pptr++) {
    int cnt = 0;

    for (union cos_mem_node_ *ptr=pptr->list; ptr; cnt++)
      ptr = ptr->free.next;

    size  += slot * cnt * cos_mem_node_size_;
    count += cnt;
  }

  if (count_) *count_ = count;
  return size;
}

size_t __attribute__ ((noinline)) // avoid bug slowing code with openmp
cos_mem_collect (int *percent_, size_t *only_)
{
  int start = only_ ? cos_mem_get_slot_(*only_) : 0;
  int end   = only_ ? start : cos_mem_slot_max_-1;

  // sanity checks
  assert(start < cos_mem_slot_max_);
  assert(!percent_ || (*percent_ >= 0 && *percent_ <= 100));

  struct cos_mem_pool_ *restrict pool = &cos_mem_pool_;
  struct cos_mem_slot_ *restrict pptr = pool->slot+end;
  size_t threshold = percent_ && *percent_ < 100 ? pool->size/100.0 * *percent_ : pool->size;
  size_t size = 0;

  for (int slot=end; slot>=start; slot--, pptr--) {
    int cnt = 0;

    for (union cos_mem_node_ *nxt, *ptr=pptr->list; ptr; ptr=nxt, cnt++) {
      nxt = ptr->free.next;
      free(ptr);
    }

    pptr->list = 0;
    size += slot * cnt * cos_mem_node_size_;
    if (size >= threshold) break;
  }

  pool->size -= size;
  return size;
}
