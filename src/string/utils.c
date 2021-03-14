#include "string/utils.h"
#include "memory/alloc.h"
#include <string.h>

char *trim(char **str)
{
	char *aux;
	int len, i, start, end;

	aux = *str;
	len = strlen(aux);

	if (!len) goto end;

	for (i = 0; i < len; i++) {
		if (aux[i] != ' ' && aux[i] != '\t' && aux[i] != '\n') {
			break;
		}
	}
	start = i;

	for (i = len - 1; i >= 0; i--) {
		if (aux[i] != ' ' && aux[i] != '\t' && aux[i] != '\n') {
			break;
		}
	}
	end = i + 1;

	// the string has only space chars
	if (end < start) {
		aux = xstrdup("");
		free(*str);
		*str = aux;
		goto end;
	}

	aux = xstrdupn(aux + start, end - start);
	free(*str);
	*str = aux;

end:
	return *str;
}

char *xstrdupn(const char *str, size_t n)
{
	char *string;

	xmalloc(string, n + 1);
	memcpy(string, str, n);
	string[n] = 0x0;

	return string;
}

char *xstrdup(const char *string)
{
	size_t len = strlen(string);
	return xstrdupn(string, len);
}

char *randomstr(char *buf, int len)
{
	static const char alphanum[] =
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		"abcdefghijklmnopqrstuvwxyz"
		"0123456789";

	int i;

	for (i = 0; i < len - 1; i++) {
		buf[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
	}

	buf[i] = 0x0;

	return buf;
}
