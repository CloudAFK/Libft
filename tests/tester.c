/* Libft tester - not part of the submission. Run: bash tests/run.sh */
#include <ctype.h>
#include <fcntl.h>
#include <limits.h>
#include <setjmp.h>
#include <signal.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "libft.h"

#define GREEN "\033[32m"
#define RED "\033[31m"
#define YELLOW "\033[33m"
#define RESET "\033[0m"
#define MAX_SHOWN 5
#define UNUSED __attribute__((unused))

#ifndef O_BINARY
# define O_BINARY 0
#endif
#ifdef _WIN32
# define JMPBUF jmp_buf
# define SETJMP(b) setjmp(b)
# define LONGJMP(b, v) longjmp(b, v)
# define FD_TMP "libft_tester_fd.tmp"
#else
# define JMPBUF sigjmp_buf
# define SETJMP(b) sigsetjmp(b, 1)
# define LONGJMP(b, v) siglongjmp(b, v)
# define FD_TMP "/tmp/libft_tester_fd.tmp"
#endif

static JMPBUF		g_jmp;
static const char	*g_name = "";
static int			g_cases = 0;
static int			g_fail = 0;
static int			g_ok = 0;
static int			g_ko = 0;
static int			g_crash = 0;
static int			g_skip = 0;

/* ------------------------------ framework ------------------------------ */

static void	check(int ok, const char *fmt, ...)
	__attribute__((format(printf, 2, 3)));

static void	check(int ok, const char *fmt, ...)
{
	va_list	ap;

	g_cases++;
	if (ok)
		return ;
	g_fail++;
	if (g_fail > MAX_SHOWN)
		return ;
	printf("     %s: ", g_name);
	va_start(ap, fmt);
	vprintf(fmt, ap);
	va_end(ap);
	printf("\n");
}

static void	on_crash(int sig)
{
	(void)sig;
	LONGJMP(g_jmp, 1);
}

static void	run(const char *name, void (*fn)(void))
{
	volatile int	crashed;

	g_name = name;
	g_cases = 0;
	g_fail = 0;
	crashed = 0;
	signal(SIGSEGV, on_crash);
	signal(SIGABRT, on_crash);
#ifdef SIGBUS
	signal(SIGBUS, on_crash);
#endif
	if (SETJMP(g_jmp) == 0)
		fn();
	else
		crashed = 1;
	if (crashed)
	{
		printf(RED "[CRASH]" RESET " %-18s crashed after %d checks\n", name,
			g_cases);
		g_crash++;
	}
	else if (g_fail == 0)
	{
		printf(GREEN "[OK]   " RESET " %-18s %d checks\n", name, g_cases);
		g_ok++;
	}
	else
	{
		printf(RED "[KO]   " RESET " %-18s %d/%d checks failed\n", name,
			g_fail, g_cases);
		g_ko++;
	}
	fflush(stdout);
}

UNUSED static void	skip(const char *name)
{
	printf(YELLOW "[--]   " RESET " %-18s file not found\n", name);
	g_skip++;
}

UNUSED static int	sgn(int x)
{
	return ((x > 0) - (x < 0));
}

/* --------------------------- Part 1 : ctype ---------------------------- */

UNUSED static void	ctype_bool(int (*mine)(int), int (*real)(int))
{
	int	c;
	int	a;
	int	b;

	c = -1;
	while (c <= 255)
	{
		a = mine(c);
		b = (real(c) != 0);
		check(a == b, "c=%d mine=%d expected=%d (must be exactly 0 or 1)",
			c, a, b);
		c++;
	}
}

UNUSED static void	ctype_conv(int (*mine)(int), int (*real)(int))
{
	int	c;

	c = -1;
	while (c <= 255)
	{
		check(mine(c) == real(c), "c=%d mine=%d libc=%d", c, mine(c),
			real(c));
		c++;
	}
}

#ifdef HAVE_isalpha
static void	t_isalpha(void) { ctype_bool(ft_isalpha, isalpha); }
# define T_isalpha run("ft_isalpha", t_isalpha)
#else
# define T_isalpha skip("ft_isalpha")
#endif

#ifdef HAVE_isdigit
static void	t_isdigit(void) { ctype_bool(ft_isdigit, isdigit); }
# define T_isdigit run("ft_isdigit", t_isdigit)
#else
# define T_isdigit skip("ft_isdigit")
#endif

#ifdef HAVE_isalnum
static void	t_isalnum(void) { ctype_bool(ft_isalnum, isalnum); }
# define T_isalnum run("ft_isalnum", t_isalnum)
#else
# define T_isalnum skip("ft_isalnum")
#endif

#ifdef HAVE_isascii
static void	t_isascii(void) { ctype_bool(ft_isascii, isascii); }
# define T_isascii run("ft_isascii", t_isascii)
#else
# define T_isascii skip("ft_isascii")
#endif

#ifdef HAVE_isprint
static void	t_isprint(void) { ctype_bool(ft_isprint, isprint); }
# define T_isprint run("ft_isprint", t_isprint)
#else
# define T_isprint skip("ft_isprint")
#endif

#ifdef HAVE_toupper
static void	t_toupper(void) { ctype_conv(ft_toupper, toupper); }
# define T_toupper run("ft_toupper", t_toupper)
#else
# define T_toupper skip("ft_toupper")
#endif

#ifdef HAVE_tolower
static void	t_tolower(void) { ctype_conv(ft_tolower, tolower); }
# define T_tolower run("ft_tolower", t_tolower)
#else
# define T_tolower skip("ft_tolower")
#endif

/* -------------------------- Part 1 : strings --------------------------- */

#ifdef HAVE_strlen
static void	t_strlen(void)
{
	static char	big[5001];
	const char	*tab[8];
	int			i;

	memset(big, 'x', 5000);
	big[5000] = '\0';
	tab[0] = "";
	tab[1] = "a";
	tab[2] = "abc";
	tab[3] = "hello world";
	tab[4] = "  42\n\t";
	tab[5] = "ab\0cd";
	tab[6] = "\xff\xfe";
	tab[7] = big;
	i = 0;
	while (i < 8)
	{
		check(ft_strlen(tab[i]) == strlen(tab[i]), "case %d mine=%zu libc=%zu",
			i, ft_strlen(tab[i]), strlen(tab[i]));
		i++;
	}
}
# define T_strlen run("ft_strlen", t_strlen)
#else
# define T_strlen skip("ft_strlen")
#endif

#if defined(HAVE_strchr) || defined(HAVE_strrchr)
static void	chr_loop(char *(*mine)(const char *, int),
		char *(*real)(const char *, int))
{
	const char	*tab[7];
	int			i;
	int			c;

	tab[0] = "";
	tab[1] = "a";
	tab[2] = "aaa";
	tab[3] = "hello";
	tab[4] = "hello world";
	tab[5] = "42 Paris\n";
	tab[6] = "abcabcabc";
	i = 0;
	while (i < 7)
	{
		c = -1;
		while (c <= 511)
		{
			check(mine(tab[i], c) == real(tab[i], c),
				"s=\"%s\" c=%d mine=%p libc=%p", tab[i], c,
				(void *)mine(tab[i], c), (void *)real(tab[i], c));
			c++;
		}
		i++;
	}
}

static char	*real_strchr(const char *s, int c) { return (strchr(s, c)); }
static char	*real_strrchr(const char *s, int c) { return (strrchr(s, c)); }
#endif

#ifdef HAVE_strchr
static void	t_strchr(void) { chr_loop(ft_strchr, real_strchr); (void)real_strrchr; }
# define T_strchr run("ft_strchr", t_strchr)
#else
# define T_strchr skip("ft_strchr")
#endif

#ifdef HAVE_strrchr
static void	t_strrchr(void) { chr_loop(ft_strrchr, real_strrchr); (void)real_strchr; }
# define T_strrchr run("ft_strrchr", t_strrchr)
#else
# define T_strrchr skip("ft_strrchr")
#endif

#ifdef HAVE_strncmp
static void	t_strncmp(void)
{
	const char	*a[] = {"abc", "abc", "abd", "abc", "abcd", "", "", "a",
		"\xff", "a", "abc\0x", "test\200", "Hello", NULL};
	const char	*b[] = {"abc", "abd", "abc", "abcd", "abc", "", "a", "",
		"a", "\xff", "abc\0y", "test\0", "hello", NULL};
	size_t		n[] = {0, 1, 2, 3, 4, 5, 10};
	int			i;
	int			j;

	i = 0;
	while (a[i])
	{
		j = 0;
		while (j < 7)
		{
			check(sgn(ft_strncmp(a[i], b[i], n[j])) == sgn(strncmp(a[i], b[i],
						n[j])), "pair %d n=%zu mine=%d libc=%d (sign must match)",
				i, n[j], ft_strncmp(a[i], b[i], n[j]), strncmp(a[i], b[i],
					n[j]));
			j++;
		}
		i++;
	}
}
# define T_strncmp run("ft_strncmp", t_strncmp)
#else
# define T_strncmp skip("ft_strncmp")
#endif

#ifdef HAVE_strlcpy
static void	t_strlcpy(void)
{
	const char	*src[] = {"hello", "hello", "hello", "hello", "hello", "",
		"a"};
	size_t		size[] = {10, 6, 5, 3, 1, 5, 2};
	const char	*exp[] = {"hello", "hello", "hell", "he", "", "", "a"};
	char		buf[16];
	size_t		ret;
	int			i;

	i = 0;
	while (i < 7)
	{
		memset(buf, 'X', 15);
		buf[15] = '\0';
		ret = ft_strlcpy(buf, src[i], size[i]);
		check(ret == strlen(src[i]), "src=\"%s\" size=%zu return=%zu expected=%zu",
			src[i], size[i], ret, strlen(src[i]));
		check(strcmp(buf, exp[i]) == 0, "src=\"%s\" size=%zu dst=\"%s\" expected=\"%s\"",
			src[i], size[i], buf, exp[i]);
		check(buf[size[i]] == 'X', "src=\"%s\" size=%zu wrote past dstsize",
			src[i], size[i]);
		i++;
	}
	memset(buf, 'X', 15);
	buf[15] = '\0';
	ret = ft_strlcpy(buf, "hello", 0);
	check(ret == 5, "size=0 return=%zu expected=5", ret);
	check(strcmp(buf, "XXXXXXXXXXXXXXX") == 0, "size=0 must not write to dst");
}
# define T_strlcpy run("ft_strlcpy", t_strlcpy)
#else
# define T_strlcpy skip("ft_strlcpy")
#endif

#ifdef HAVE_strlcat
static void	t_strlcat(void)
{
	const char	*dst[] = {"abc", "abc", "abc", "abc", "abc", "abc", "abc",
		"abc", "", "", "abc", ""};
	const char	*src[] = {"def", "def", "def", "def", "def", "def", "def",
		"def", "xyz", "xyz", "", ""};
	size_t		size[] = {20, 7, 6, 5, 4, 3, 2, 0, 4, 1, 10, 5};
	size_t		eret[] = {6, 6, 6, 6, 6, 6, 5, 3, 3, 3, 3, 0};
	const char	*exp[] = {"abcdef", "abcdef", "abcde", "abcd", "abc", "abc",
		"abc", "abc", "xyz", "", "abc", ""};
	char		buf[30];
	size_t		ret;
	int			i;

	i = 0;
	while (i < 12)
	{
		memset(buf, 'X', 30);
		strcpy(buf, dst[i]);
		ret = ft_strlcat(buf, src[i], size[i]);
		check(ret == eret[i], "dst=\"%s\" src=\"%s\" size=%zu return=%zu expected=%zu",
			dst[i], src[i], size[i], ret, eret[i]);
		check(strcmp(buf, exp[i]) == 0,
			"dst=\"%s\" src=\"%s\" size=%zu result=\"%s\" expected=\"%s\"",
			dst[i], src[i], size[i], buf, exp[i]);
		check(buf[29] == 'X' && buf[25] == 'X', "wrote far past the buffer");
		i++;
	}
}
# define T_strlcat run("ft_strlcat", t_strlcat)
#else
# define T_strlcat skip("ft_strlcat")
#endif

#ifdef HAVE_strnstr
static void	t_strnstr(void)
{
	const char	*h[] = {"hello world", "hello world", "hello world", "hello",
		"hello", "hello", "hello", "", "", "aaab", "abc", "hello", "hello",
		"hello world", "abcabcd"};
	const char	*n[] = {"world", "world", "", "hello", "hello", "lo", "lo", "",
		"a", "aab", "abcd", "h", "", "o w", "abcd"};
	size_t		len[] = {11, 10, 5, 5, 4, 5, 4, 0, 5, 4, 10, 0, 0, 20, 7};
	int			idx[] = {6, -1, 0, 0, -1, 3, -1, 0, -1, 1, -1, -1, 0, 4, 3};
	char		*res;
	int			i;

	i = 0;
	while (i < 15)
	{
		res = ft_strnstr(h[i], n[i], len[i]);
		if (idx[i] < 0)
			check(res == NULL, "big=\"%s\" little=\"%s\" len=%zu expected NULL",
				h[i], n[i], len[i]);
		else
			check(res == h[i] + idx[i],
				"big=\"%s\" little=\"%s\" len=%zu expected index %d, got %s",
				h[i], n[i], len[i], idx[i], res ? "another address" : "NULL");
		i++;
	}
}
# define T_strnstr run("ft_strnstr", t_strnstr)
#else
# define T_strnstr skip("ft_strnstr")
#endif

#ifdef HAVE_atoi
static void	t_atoi(void)
{
	const char	*tab[] = {"0", "42", "-42", "+42", "   42", " \t\n\v\f\r42",
		"2147483647", "-2147483648", "42abc", "abc", "", "--42", "+-42",
		"-+42", "  -0012", "4 2", " + 42", "-", "+", "  -", "0000", "-0",
		"\t-2147483648xyz", "9", "-9", NULL};
	int			i;

	i = 0;
	while (tab[i])
	{
		check(ft_atoi(tab[i]) == atoi(tab[i]), "str=\"%s\" mine=%d libc=%d",
			tab[i], ft_atoi(tab[i]), atoi(tab[i]));
		i++;
	}
}
# define T_atoi run("ft_atoi", t_atoi)
#else
# define T_atoi skip("ft_atoi")
#endif

/* --------------------------- Part 1 : memory --------------------------- */

#ifdef HAVE_memset
static void	t_memset(void)
{
	unsigned char	a[40];
	unsigned char	b[40];
	int				vals[] = {0, 'A', 255, 300, -1};
	size_t			lens[] = {0, 1, 7, 32};
	int				i;
	int				j;
	void			*ret;

	i = 0;
	while (i < 5)
	{
		j = 0;
		while (j < 4)
		{
			memset(a, '#', 40);
			memset(b, '#', 40);
			ret = ft_memset(a + 4, vals[i], lens[j]);
			memset(b + 4, vals[i], lens[j]);
			check(ret == a + 4, "c=%d len=%zu return value is not dest",
				vals[i], lens[j]);
			check(memcmp(a, b, 40) == 0, "c=%d len=%zu wrong bytes", vals[i],
				lens[j]);
			j++;
		}
		i++;
	}
}
# define T_memset run("ft_memset", t_memset)
#else
# define T_memset skip("ft_memset")
#endif

#ifdef HAVE_bzero
static void	t_bzero(void)
{
	unsigned char	a[40];
	size_t			lens[] = {0, 1, 7, 32};
	size_t			i;
	int				j;
	int				bad;

	j = 0;
	while (j < 4)
	{
		memset(a, '#', 40);
		ft_bzero(a + 4, lens[j]);
		bad = 0;
		i = 0;
		while (i < 40)
		{
			if (i >= 4 && i < 4 + lens[j] && a[i] != 0)
				bad = 1;
			if ((i < 4 || i >= 4 + lens[j]) && a[i] != '#')
				bad = 1;
			i++;
		}
		check(!bad, "n=%zu wrong bytes (not zeroed, or wrote outside)", lens[j]);
		j++;
	}
}
# define T_bzero run("ft_bzero", t_bzero)
#else
# define T_bzero skip("ft_bzero")
#endif

#ifdef HAVE_memcpy
static void	t_memcpy(void)
{
	const char		*src = "0123456789abcdefghijklmnopqrstuv";
	unsigned char	a[40];
	unsigned char	b[40];
	size_t			lens[] = {0, 1, 5, 32};
	int				j;
	void			*ret;

	j = 0;
	while (j < 4)
	{
		memset(a, '#', 40);
		memset(b, '#', 40);
		ret = ft_memcpy(a + 4, src, lens[j]);
		memcpy(b + 4, src, lens[j]);
		check(ret == a + 4, "n=%zu return value is not dest", lens[j]);
		check(memcmp(a, b, 40) == 0, "n=%zu wrong bytes", lens[j]);
		j++;
	}
	memcpy(a, "ab\0cd\0ef", 8);
	memset(b, '#', 40);
	ft_memcpy(b, a, 8);
	check(memcmp(a, b, 8) == 0, "must copy bytes after a '\\0' too");
}
# define T_memcpy run("ft_memcpy", t_memcpy)
#else
# define T_memcpy skip("ft_memcpy")
#endif

#ifdef HAVE_memmove
static void	t_memmove(void)
{
	size_t	d[] = {2, 0, 0, 5, 1, 0, 8, 3};
	size_t	s[] = {0, 2, 0, 5, 0, 1, 0, 4};
	size_t	n[] = {8, 8, 8, 0, 15, 15, 4, 12};
	char	a[17];
	char	b[17];
	void	*ret;
	int		i;

	i = 0;
	while (i < 8)
	{
		memcpy(a, "0123456789abcdef", 17);
		memcpy(b, "0123456789abcdef", 17);
		ret = ft_memmove(a + d[i], a + s[i], n[i]);
		memmove(b + d[i], b + s[i], n[i]);
		check(ret == a + d[i], "dst+%zu src+%zu n=%zu return value is not dest",
			d[i], s[i], n[i]);
		check(memcmp(a, b, 17) == 0,
			"dst+%zu src+%zu n=%zu mine=\"%s\" libc=\"%s\" (overlap)", d[i],
			s[i], n[i], a, b);
		i++;
	}
}
# define T_memmove run("ft_memmove", t_memmove)
#else
# define T_memmove skip("ft_memmove")
#endif

#ifdef HAVE_memchr
static void	t_memchr(void)
{
	const char	buf[] = "hello\0world\xff!";
	size_t		n[] = {0, 1, 5, 6, 13};
	int			c;
	int			j;

	j = 0;
	while (j < 5)
	{
		c = -1;
		while (c <= 300)
		{
			check(ft_memchr(buf, c, n[j]) == memchr(buf, c, n[j]),
				"c=%d n=%zu mine=%p libc=%p", c, n[j],
				ft_memchr(buf, c, n[j]), memchr(buf, c, n[j]));
			c++;
		}
		j++;
	}
}
# define T_memchr run("ft_memchr", t_memchr)
#else
# define T_memchr skip("ft_memchr")
#endif

#ifdef HAVE_memcmp
static void	t_memcmp(void)
{
	const char	a[][9] = {"abcdefgh", "abcdefgh", "abc\0defg", "\xff" "bcdefgh",
		"a\200cdefgh", "abcdefgh", "\0\0\0\0\0\0\0\1"};
	const char	b[][9] = {"abcdefgh", "abcdefgX", "abc\0dezg", "\x01" "bcdefgh",
		"a\0cdefgh", "Abcdefgh", "\0\0\0\0\0\0\0\2"};
	size_t		n[] = {0, 1, 4, 7, 8};
	int			i;
	int			j;

	i = 0;
	while (i < 7)
	{
		j = 0;
		while (j < 5)
		{
			check(sgn(ft_memcmp(a[i], b[i], n[j])) == sgn(memcmp(a[i], b[i],
						n[j])), "pair %d n=%zu mine=%d libc=%d (sign must match)",
				i, n[j], ft_memcmp(a[i], b[i], n[j]), memcmp(a[i], b[i],
					n[j]));
			j++;
		}
		i++;
	}
}
# define T_memcmp run("ft_memcmp", t_memcmp)
#else
# define T_memcmp skip("ft_memcmp")
#endif

#ifdef HAVE_calloc
static void	t_calloc(void)
{
	unsigned char	*p;
	size_t			i;
	int				bad;

	p = ft_calloc(250, 4);
	check(p != NULL, "calloc(250, 4) returned NULL");
	if (p)
	{
		bad = 0;
		i = 0;
		while (i < 1000)
			if (p[i++] != 0)
				bad = 1;
		check(!bad, "memory is not zeroed");
		memset(p, 'A', 1000);
		free(p);
	}
	p = ft_calloc(0, 8);
	check(p != NULL, "calloc(0, 8) must return a pointer that can be freed");
	free(p);
	p = ft_calloc(8, 0);
	check(p != NULL, "calloc(8, 0) must return a pointer that can be freed");
	free(p);
	p = ft_calloc(1, 1);
	check(p != NULL && p[0] == 0, "calloc(1, 1) wrong");
	free(p);
}
# define T_calloc run("ft_calloc", t_calloc)
#else
# define T_calloc skip("ft_calloc")
#endif

#ifdef HAVE_strdup
static void	t_strdup(void)
{
	static char	big[2001];
	const char	*tab[4];
	char		*d;
	int			i;

	memset(big, 'z', 2000);
	big[2000] = '\0';
	tab[0] = "";
	tab[1] = "hello";
	tab[2] = "hello world\n\t42";
	tab[3] = big;
	i = 0;
	while (i < 4)
	{
		d = ft_strdup(tab[i]);
		check(d != NULL, "case %d returned NULL", i);
		if (d)
		{
			check(strcmp(d, tab[i]) == 0, "case %d content differs", i);
			check(d != tab[i], "case %d returned the same pointer (no copy)", i);
			free(d);
		}
		i++;
	}
}
# define T_strdup run("ft_strdup", t_strdup)
#else
# define T_strdup skip("ft_strdup")
#endif

/* ------------------------ Part 2 : additional -------------------------- */

#if defined(HAVE_substr) || defined(HAVE_strjoin) || defined(HAVE_strtrim) \
	|| defined(HAVE_itoa) || defined(HAVE_strmapi)
static void	expect_str(char *got, const char *exp, const char *label)
{
	check(got != NULL, "%s returned NULL, expected \"%s\"", label, exp);
	if (got)
	{
		check(strcmp(got, exp) == 0, "%s got \"%s\" expected \"%s\"", label,
			got, exp);
		free(got);
	}
}
#endif

#ifdef HAVE_substr
static void	t_substr(void)
{
	const char		*s[] = {"hello world", "hello world", "hello world",
		"hello world", "hello world", "hello world", "", "hello", "hello",
		"hello"};
	unsigned int	st[] = {0, 6, 6, 11, 50, 0, 0, 2, 4, 0};
	size_t			len[] = {5, 5, 100, 5, 5, 0, 5, 2, 10, 5};
	const char		*exp[] = {"hello", "world", "world", "", "", "", "", "ll",
		"o", "hello"};
	char			label[64];
	int				i;

	i = 0;
	while (i < 10)
	{
		snprintf(label, 64, "(\"%s\", %u, %zu)", s[i], st[i], len[i]);
		expect_str(ft_substr(s[i], st[i], len[i]), exp[i], label);
		i++;
	}
}
# define T_substr run("ft_substr", t_substr)
#else
# define T_substr skip("ft_substr")
#endif

#ifdef HAVE_strjoin
static void	t_strjoin(void)
{
	expect_str(ft_strjoin("hello", " world"), "hello world", "(hello, world)");
	expect_str(ft_strjoin("", "abc"), "abc", "(\"\", abc)");
	expect_str(ft_strjoin("abc", ""), "abc", "(abc, \"\")");
	expect_str(ft_strjoin("", ""), "", "(\"\", \"\")");
	expect_str(ft_strjoin("a", "b"), "ab", "(a, b)");
}
# define T_strjoin run("ft_strjoin", t_strjoin)
#else
# define T_strjoin skip("ft_strjoin")
#endif

#ifdef HAVE_strtrim
static void	t_strtrim(void)
{
	const char	*s[] = {"  hello  ", "xxhelloxx", "hello", "", "", "aaaa",
		"abcHELLOcba", "a b a", "hello", " \t\nhi\n\t ", "x"};
	const char	*set[] = {" ", "x", "", "", "abc", "a", "abc", "a", "xyz",
		" \t\n", "x"};
	const char	*exp[] = {"hello", "hello", "hello", "", "", "", "HELLO",
		" b ", "hello", "hi", ""};
	char		label[64];
	int			i;

	i = 0;
	while (i < 11)
	{
		snprintf(label, 64, "case %d (\"%s\", set)", i, s[i]);
		expect_str(ft_strtrim(s[i], set[i]), exp[i], label);
		i++;
	}
}
# define T_strtrim run("ft_strtrim", t_strtrim)
#else
# define T_strtrim skip("ft_strtrim")
#endif

#ifdef HAVE_split
static void	split_case(const char *s, char c, const char **exp, int n)
{
	char	**tab;
	int		i;

	tab = ft_split(s, c);
	check(tab != NULL, "(\"%s\", %d) returned NULL", s, c);
	if (!tab)
		return ;
	i = 0;
	while (i < n && tab[i])
	{
		check(strcmp(tab[i], exp[i]) == 0,
			"(\"%s\", %d) word %d got \"%s\" expected \"%s\"", s, c, i, tab[i],
			exp[i]);
		i++;
	}
	check(i == n, "(\"%s\", %d) only %d words, expected %d", s, c, i, n);
	if (i == n)
		check(tab[n] == NULL, "(\"%s\", %d) array not NULL-terminated after %d words",
			s, c, n);
	i = 0;
	while (tab[i])
		free(tab[i++]);
	free(tab);
}

static void	t_split(void)
{
	const char	*hw[] = {"hello", "world"};
	const char	*one[] = {"hello"};
	const char	*abc[] = {"a", "b", "c"};
	const char	*a[] = {"a"};

	split_case("hello world", ' ', hw, 2);
	split_case("  hello   world  ", ' ', hw, 2);
	split_case("", ' ', NULL, 0);
	split_case("     ", ' ', NULL, 0);
	split_case("hello", ' ', one, 1);
	split_case("a,b,,c", ',', abc, 3);
	split_case("hello", '\0', one, 1);
	split_case(",a", ',', a, 1);
	split_case("a,", ',', a, 1);
	split_case("", '\0', NULL, 0);
}
# define T_split run("ft_split", t_split)
#else
# define T_split skip("ft_split")
#endif

#ifdef HAVE_itoa
static void	t_itoa(void)
{
	int		vals[] = {0, 42, -42, INT_MAX, INT_MIN, 7, -1, 1000, 10, -10, 99,
		100, -2147483647};
	char	exp[16];
	char	label[32];
	int		i;

	i = 0;
	while (i < 13)
	{
		snprintf(exp, 16, "%d", vals[i]);
		snprintf(label, 32, "(%d)", vals[i]);
		expect_str(ft_itoa(vals[i]), exp, label);
		i++;
	}
}
# define T_itoa run("ft_itoa", t_itoa)
#else
# define T_itoa skip("ft_itoa")
#endif

#ifdef HAVE_strmapi
static char	map_fn(unsigned int i, char c)
{
	if (i % 2 == 0)
		return ((char)toupper((unsigned char)c));
	return (c);
}

static void	t_strmapi(void)
{
	expect_str(ft_strmapi("hello", map_fn), "HeLlO", "(hello, f)");
	expect_str(ft_strmapi("", map_fn), "", "(\"\", f)");
	expect_str(ft_strmapi("a", map_fn), "A", "(a, f)");
	expect_str(ft_strmapi("abcdefgh", map_fn), "AbCdEfGh", "(abcdefgh, f)");
}
# define T_strmapi run("ft_strmapi", t_strmapi)
#else
# define T_strmapi skip("ft_strmapi")
#endif

#ifdef HAVE_striteri
static void	iter_fn(unsigned int i, char *c)
{
	*c = (char)(*c + i);
}

static void	t_striteri(void)
{
	char	a[] = "aaaa";
	char	b[] = "";
	char	c[] = "0000000000";

	ft_striteri(a, iter_fn);
	check(strcmp(a, "abcd") == 0, "\"aaaa\" got \"%s\" expected \"abcd\"", a);
	ft_striteri(b, iter_fn);
	check(b[0] == '\0', "empty string was modified");
	ft_striteri(c, iter_fn);
	check(strcmp(c, "0123456789") == 0, "got \"%s\" expected \"0123456789\"", c);
}
# define T_striteri run("ft_striteri", t_striteri)
#else
# define T_striteri skip("ft_striteri")
#endif

#if defined(HAVE_putchar_fd) || defined(HAVE_putstr_fd) \
	|| defined(HAVE_putendl_fd) || defined(HAVE_putnbr_fd)
static int	fd_open(void)
{
	return (open(FD_TMP, O_RDWR | O_CREAT | O_TRUNC | O_BINARY, 0600));
}

static void	fd_expect(int fd, const char *exp, const char *label)
{
	char	buf[128];
	long	r;

	lseek(fd, 0, SEEK_SET);
	r = (long)read(fd, buf, 127);
	if (r < 0)
		r = 0;
	buf[r] = '\0';
	check(r == (long)strlen(exp) && memcmp(buf, exp, (size_t)r) == 0,
		"%s wrote \"%s\" (%ld bytes) expected \"%s\"", label, buf, r, exp);
	close(fd);
	unlink(FD_TMP);
}
#endif

#ifdef HAVE_putchar_fd
static void	t_putchar_fd(void)
{
	int	fd;

	fd = fd_open();
	ft_putchar_fd('A', fd);
	fd_expect(fd, "A", "('A')");
	fd = fd_open();
	ft_putchar_fd('\n', fd);
	fd_expect(fd, "\n", "('\\n')");
	fd = fd_open();
	ft_putchar_fd('4', fd);
	ft_putchar_fd('2', fd);
	fd_expect(fd, "42", "('4') then ('2')");
}
# define T_putchar_fd run("ft_putchar_fd", t_putchar_fd)
#else
# define T_putchar_fd skip("ft_putchar_fd")
#endif

#ifdef HAVE_putstr_fd
static void	t_putstr_fd(void)
{
	int	fd;

	fd = fd_open();
	ft_putstr_fd("hello", fd);
	fd_expect(fd, "hello", "(\"hello\")");
	fd = fd_open();
	ft_putstr_fd("", fd);
	fd_expect(fd, "", "(\"\")");
	fd = fd_open();
	ft_putstr_fd("a\nb", fd);
	fd_expect(fd, "a\nb", "(\"a\\nb\")");
}
# define T_putstr_fd run("ft_putstr_fd", t_putstr_fd)
#else
# define T_putstr_fd skip("ft_putstr_fd")
#endif

#ifdef HAVE_putendl_fd
static void	t_putendl_fd(void)
{
	int	fd;

	fd = fd_open();
	ft_putendl_fd("hello", fd);
	fd_expect(fd, "hello\n", "(\"hello\")");
	fd = fd_open();
	ft_putendl_fd("", fd);
	fd_expect(fd, "\n", "(\"\")");
}
# define T_putendl_fd run("ft_putendl_fd", t_putendl_fd)
#else
# define T_putendl_fd skip("ft_putendl_fd")
#endif

#ifdef HAVE_putnbr_fd
static void	t_putnbr_fd(void)
{
	int		vals[] = {0, 42, -42, INT_MAX, INT_MIN, 7, -7, 100000, 10, -10};
	char	exp[16];
	char	label[32];
	int		fd;
	int		i;

	i = 0;
	while (i < 10)
	{
		snprintf(exp, 16, "%d", vals[i]);
		snprintf(label, 32, "(%d)", vals[i]);
		fd = fd_open();
		ft_putnbr_fd(vals[i], fd);
		fd_expect(fd, exp, label);
		i++;
	}
}
# define T_putnbr_fd run("ft_putnbr_fd", t_putnbr_fd)
#else
# define T_putnbr_fd skip("ft_putnbr_fd")
#endif

/* --------------------------- Part 3 : lists ---------------------------- */

#if defined(HAVE_lstdelone) || defined(HAVE_lstclear) || defined(HAVE_lstmap)
static int	g_del = 0;

UNUSED static void	del_count(void *content)
{
	g_del++;
	free(content);
}

UNUSED static t_list	*heap_node(int value)
{
	t_list	*n;
	int		*v;

	n = malloc(sizeof(t_list));
	v = malloc(sizeof(int));
	if (!n || !v)
		exit(2);
	*v = value;
	n->content = v;
	n->next = NULL;
	return (n);
}
#endif

#ifdef HAVE_lstnew
static void	t_lstnew(void)
{
	t_list	*n;
	int		x;

	x = 42;
	n = ft_lstnew(&x);
	check(n != NULL, "returned NULL");
	if (n)
	{
		check(n->content == &x, "content is not the given pointer");
		check(n->next == NULL, "next is not NULL");
		free(n);
	}
	n = ft_lstnew(NULL);
	check(n != NULL, "lstnew(NULL) returned NULL (a node with NULL content is valid)");
	if (n)
	{
		check(n->content == NULL && n->next == NULL, "lstnew(NULL) wrong fields");
		free(n);
	}
}
# define T_lstnew run("ft_lstnew", t_lstnew)
#else
# define T_lstnew skip("ft_lstnew")
#endif

#ifdef HAVE_lstadd_front
static void	t_lstadd_front(void)
{
	t_list	a;
	t_list	b;
	t_list	*lst;

	a.content = NULL;
	a.next = NULL;
	b.content = NULL;
	b.next = NULL;
	lst = NULL;
	ft_lstadd_front(&lst, &a);
	check(lst == &a && a.next == NULL, "adding to an empty list failed");
	ft_lstadd_front(&lst, &b);
	check(lst == &b, "list head is not the new node");
	check(b.next == &a, "new->next is not the old head");
	check(a.next == NULL, "old head was modified");
}
# define T_lstadd_front run("ft_lstadd_front", t_lstadd_front)
#else
# define T_lstadd_front skip("ft_lstadd_front")
#endif

#ifdef HAVE_lstsize
static void	t_lstsize(void)
{
	t_list	a;
	t_list	b;
	t_list	c;

	a.next = &b;
	b.next = &c;
	c.next = NULL;
	check(ft_lstsize(NULL) == 0, "size of NULL list = %d expected 0",
		ft_lstsize(NULL));
	check(ft_lstsize(&c) == 1, "size = %d expected 1", ft_lstsize(&c));
	check(ft_lstsize(&a) == 3, "size = %d expected 3", ft_lstsize(&a));
}
# define T_lstsize run("ft_lstsize", t_lstsize)
#else
# define T_lstsize skip("ft_lstsize")
#endif

#ifdef HAVE_lstlast
static void	t_lstlast(void)
{
	t_list	a;
	t_list	b;
	t_list	c;

	a.next = &b;
	b.next = &c;
	c.next = NULL;
	check(ft_lstlast(NULL) == NULL, "last of NULL list must be NULL");
	check(ft_lstlast(&c) == &c, "last of a 1-node list is wrong");
	check(ft_lstlast(&a) == &c, "last of a 3-node list is wrong");
}
# define T_lstlast run("ft_lstlast", t_lstlast)
#else
# define T_lstlast skip("ft_lstlast")
#endif

#ifdef HAVE_lstadd_back
static void	t_lstadd_back(void)
{
	t_list	a;
	t_list	b;
	t_list	c;
	t_list	*lst;

	a.next = NULL;
	b.next = NULL;
	c.next = NULL;
	lst = NULL;
	ft_lstadd_back(&lst, &a);
	check(lst == &a, "adding to an empty list must set the head");
	ft_lstadd_back(&lst, &b);
	check(lst == &a && a.next == &b, "second node not linked at the end");
	ft_lstadd_back(&lst, &c);
	check(lst == &a && b.next == &c && c.next == NULL,
		"third node not linked at the end");
}
# define T_lstadd_back run("ft_lstadd_back", t_lstadd_back)
#else
# define T_lstadd_back skip("ft_lstadd_back")
#endif

#ifdef HAVE_lstdelone
static void	t_lstdelone(void)
{
	t_list	*n1;
	t_list	*n2;

	n1 = heap_node(1);
	n2 = heap_node(2);
	n1->next = n2;
	g_del = 0;
	ft_lstdelone(n1, del_count);
	check(g_del == 1, "del called %d time(s), expected 1", g_del);
	check(*(int *)n2->content == 2 && n2->next == NULL,
		"the next node was modified or freed");
	free(n2->content);
	free(n2);
}
# define T_lstdelone run("ft_lstdelone", t_lstdelone)
#else
# define T_lstdelone skip("ft_lstdelone")
#endif

#ifdef HAVE_lstclear
static void	t_lstclear(void)
{
	t_list	*lst;

	lst = heap_node(1);
	lst->next = heap_node(2);
	lst->next->next = heap_node(3);
	g_del = 0;
	ft_lstclear(&lst, del_count);
	check(g_del == 3, "del called %d time(s), expected 3", g_del);
	check(lst == NULL, "list pointer not set to NULL");
	lst = NULL;
	g_del = 0;
	ft_lstclear(&lst, del_count);
	check(g_del == 0 && lst == NULL, "clearing an empty list went wrong");
}
# define T_lstclear run("ft_lstclear", t_lstclear)
#else
# define T_lstclear skip("ft_lstclear")
#endif

#ifdef HAVE_lstiter
static void	iter_inc(void *content)
{
	*(int *)content += 1;
}

static void	t_lstiter(void)
{
	t_list	a;
	t_list	b;
	t_list	c;
	int		v[3];

	v[0] = 1;
	v[1] = 10;
	v[2] = 100;
	a.content = &v[0];
	a.next = &b;
	b.content = &v[1];
	b.next = &c;
	c.content = &v[2];
	c.next = NULL;
	ft_lstiter(&a, iter_inc);
	check(v[0] == 2 && v[1] == 11 && v[2] == 101,
		"values are %d %d %d expected 2 11 101", v[0], v[1], v[2]);
	ft_lstiter(NULL, iter_inc);
	check(1, "empty list");
}
# define T_lstiter run("ft_lstiter", t_lstiter)
#else
# define T_lstiter skip("ft_lstiter")
#endif

#ifdef HAVE_lstmap
static void	*map_double(void *content)
{
	int	*v;

	v = malloc(sizeof(int));
	if (!v)
		exit(2);
	*v = *(int *)content * 2;
	return (v);
}

static void	t_lstmap(void)
{
	t_list	a;
	t_list	b;
	t_list	c;
	t_list	*res;
	t_list	*cur;
	t_list	*next;
	int		v[3];
	int		i;

	v[0] = 1;
	v[1] = 2;
	v[2] = 3;
	a.content = &v[0];
	a.next = &b;
	b.content = &v[1];
	b.next = &c;
	c.content = &v[2];
	c.next = NULL;
	g_del = 0;
	res = ft_lstmap(&a, map_double, del_count);
	check(res != NULL, "returned NULL");
	check(res != &a, "returned the original list instead of a new one");
	cur = res;
	i = 0;
	while (cur && i < 3)
	{
		check(cur->content != NULL && *(int *)cur->content == v[i] * 2,
			"node %d has a wrong content", i);
		cur = cur->next;
		i++;
	}
	check(i == 3 && cur == NULL, "new list has a wrong length");
	check(v[0] == 1 && v[1] == 2 && v[2] == 3 && a.next == &b && b.next == &c,
		"the original list was modified");
	check(g_del == 0, "del was called %d time(s) without any failure", g_del);
	cur = res;
	while (cur)
	{
		next = cur->next;
		free(cur->content);
		free(cur);
		cur = next;
	}
	check(ft_lstmap(NULL, map_double, del_count) == NULL,
		"lstmap(NULL) must return NULL");
}
# define T_lstmap run("ft_lstmap", t_lstmap)
#else
# define T_lstmap skip("ft_lstmap")
#endif

/* -------------------------------- main --------------------------------- */

int	main(void)
{
	printf("========== Part 1 : libc ==========\n");
	T_isalpha;
	T_isdigit;
	T_isalnum;
	T_isascii;
	T_isprint;
	T_strlen;
	T_memset;
	T_bzero;
	T_memcpy;
	T_memmove;
	T_strlcpy;
	T_strlcat;
	T_toupper;
	T_tolower;
	T_strchr;
	T_strrchr;
	T_strncmp;
	T_memchr;
	T_memcmp;
	T_strnstr;
	T_atoi;
	T_calloc;
	T_strdup;
	printf("========== Part 2 : additional ==========\n");
	T_substr;
	T_strjoin;
	T_strtrim;
	T_split;
	T_itoa;
	T_strmapi;
	T_striteri;
	T_putchar_fd;
	T_putstr_fd;
	T_putendl_fd;
	T_putnbr_fd;
	printf("========== Part 3 : linked list ==========\n");
	T_lstnew;
	T_lstadd_front;
	T_lstsize;
	T_lstlast;
	T_lstadd_back;
	T_lstdelone;
	T_lstclear;
	T_lstiter;
	T_lstmap;
	printf("==========================================\n");
	printf("OK: %d   KO: %d   CRASH: %d   not written yet: %d   (43 functions)\n",
		g_ok, g_ko, g_crash, g_skip);
	if (g_ko == 0 && g_crash == 0 && g_skip == 0)
		printf(GREEN "All 43 functions pass.\n" RESET);
	else if (g_ko == 0 && g_crash == 0)
		printf(GREEN "Everything written so far passes.\n" RESET);
	else
		printf(RED "Some functions fail: read the lines above.\n" RESET);
	return (g_ko != 0 || g_crash != 0);
}
