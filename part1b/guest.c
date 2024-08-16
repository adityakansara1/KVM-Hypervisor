#include <stddef.h>
#include <stdint.h>

static void outb(uint16_t port, uint8_t value)
{
	asm("outb %0,%1" : /* empty */ : "a"(value), "Nd"(port) : "memory");
}

static void outl(uint16_t port, uint32_t value)
{
	asm("outl %0,%1" : /* empty */ : "a"(value), "Nd"(port) : "memory");
}

static void in(uint16_t port, uint32_t *value)
{
	asm("in %1,%0" : "=a"(*value) : "Nd"(port) : "memory");
}

void HC_print8bit(uint8_t val)
{
	outb(0xE9, val);
}

void HC_print32bit(uint32_t val)
{
	outl(0xE8, val);
}

uint32_t HC_numExits()
{
	uint32_t value;
	in(0xE7, &value);
	return value;
}

void HC_printStr(char *str)
{
	outl(0xE6, (unsigned long)str);
}

uint8_t flag = 1;
char *HC_numExitsByType()
{
	if (flag)
	{
		outb(0xE5, 1);
		flag = 0;
	}
	else
	{
		outb(0xE5, 2);
	}
	uint32_t p;
	in(0xE5, &p);
	return (char *)(unsigned long)p;
}

uint32_t HC_gvaToHva(uint32_t gva)
{
	uint32_t hva;
	outl(0xE4, gva);
	in(0xE4, &hva);
	return hva;
}

void
	__attribute__((noreturn))
	__attribute__((section(".start")))
	_start(void)
{
	const char *p;

	for (p = "Hello 695!\n"; *p; ++p)
		HC_print8bit(*p);

	/*----------Don't modify this section. We will use grading script---------*/
	/*---Your submission will fail the testcases if you modify this section---*/
	HC_print32bit(2048);
	HC_print32bit(4294967295);

	uint32_t num_exits_a, num_exits_b;
	num_exits_a = HC_numExits();

	char *str = "CS695 Assignment 2\n";
	HC_printStr(str);

	num_exits_b = HC_numExits();

	HC_print32bit(num_exits_a);
	HC_print32bit(num_exits_b);

	char *firststr = HC_numExitsByType();
	uint32_t hva;
	hva = HC_gvaToHva(1024);
	HC_print32bit(hva);
	hva = HC_gvaToHva(4294967295);
	HC_print32bit(hva);
	char *secondstr = HC_numExitsByType();

	HC_printStr(firststr);
	HC_printStr(secondstr);
	/*------------------------------------------------------------------------*/

	*(long *)0x400 = 42;

	for (;;)
		asm("hlt" : /* empty */ : "a"(42) : "memory");
}
