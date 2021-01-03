#include "types.h"

u32 placement_address;

u32 kmalloc_a(u32 sz, int align);  // page aligned.
u32 kmalloc_p(u32 sz, u32 *phys); // returns a physical address.
u32 kmalloc_ap(u32 sz,int align, u32 *phys); // page aligned and returns a physical address.
u32 kmalloc(u32 sz); // vanilla (normal). 
