#include <onix/console.h>
#include <onix/printk.h>
#include <onix/assert.h>
#include <onix/debug.h>

void kernel_init()
{
    console_init();
    //assert(3 < 5);
    //assert(3 > 5);
    //panic("Out of Memory");

    BMB;

    DEBUGK("debug onix!!!\n");

    return;
}