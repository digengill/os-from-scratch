#include "kmalloc.h"

u32 placement_address;
u32 kmalloc(u32 sz)
{
  u32 tmp = placement_address;
  placement_address += sz;
  return tmp;
}

u32 kmalloc_a(u32 sz, int align)
{
  if (align == 1 && (placement_address & 0xFFFFF000)) // If the address is not already page-aligned
  {
    // Align it.
    placement_address &= 0xFFFFF000;
    placement_address += 0x1000;
  }
  u32 tmp = placement_address;
  placement_address += sz;
  return tmp;
}

u32 kmalloc_ap(u32 sz,int align, u32 *phys)
{
  if (align == 1 && (placement_address & 0xFFFFF000)) // If the address is not already page-aligned
  {
    // Align it.
    placement_address &= 0xFFFFF000;
    placement_address += 0x1000;
  }
  if (phys)
  {
    *phys = placement_address;
  }
  u32 tmp = placement_address;
  placement_address += sz;
  return tmp;
}
