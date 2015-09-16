#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);

struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
 .name = KBUILD_MODNAME,
 .init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
 .exit = cleanup_module,
#endif
 .arch = MODULE_ARCH_INIT,
};

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0x89388970, "module_layout" },
	{ 0x4141f80, "__tracepoint_module_get" },
	{ 0x3c0ae92f, "__register_chrdev" },
	{ 0x6bc3fbc0, "__unregister_chrdev" },
	{ 0x42224298, "sscanf" },
	{ 0x167e7f9d, "__get_user_1" },
	{ 0xa1c76e0a, "_cond_resched" },
	{ 0xeae3dfd6, "__const_udelay" },
	{ 0x50eedeb8, "printk" },
	{ 0xc0f04903, "module_put" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";

