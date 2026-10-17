#!/bin/bash
# Libft tester launcher. From the repository root:
#   bash tests/run.sh         -> run all tests
#   bash tests/run.sh leak    -> same, under valgrind (memory leaks)
ROOT="$(cd "$(dirname "$0")/.." && pwd)"
BIN="/tmp/libft_tester"
FUNCS="isalpha isdigit isalnum isascii isprint strlen memset bzero memcpy
memmove strlcpy strlcat toupper tolower strchr strrchr strncmp memchr memcmp
strnstr atoi calloc strdup substr strjoin strtrim split itoa strmapi striteri
putchar_fd putstr_fd putendl_fd putnbr_fd lstnew lstadd_front lstsize lstlast
lstadd_back lstdelone lstclear lstiter lstmap"

FLAGS=()
SRCS=()
for f in $FUNCS; do
	if [ -f "$ROOT/ft_$f.c" ]; then
		FLAGS+=("-DHAVE_$f")
		SRCS+=("$ROOT/ft_$f.c")
	fi
done

if [ ${#SRCS[@]} -eq 0 ]; then
	echo "No ft_*.c file found in $ROOT"
	exit 1
fi

if ! ${CC:-cc} -Wall -Wextra -Werror -g "${FLAGS[@]}" -I "$ROOT" "$ROOT/tests/tester.c" "${SRCS[@]}" -o "$BIN"; then
	echo "Compilation failed: read the first error above."
	exit 1
fi

if [ "$1" = "leak" ]; then
	valgrind --leak-check=full --show-leak-kinds=all --error-exitcode=42 -q "$BIN"
else
	"$BIN"
fi
