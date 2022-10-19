#include <onix/console.h>
#include <onix/printk.h>
#include <onix/assert.h>
#include <onix/debug.h>
#include <onix/global.h>

void kernel_init()
{
    console_init();
    gdt_init();

    return;
}