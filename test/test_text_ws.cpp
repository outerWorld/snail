
#include <stdio.h>
#include "common.h"

#include "ictclas50.h"
#include "text_ws.h"

int main(int argc, char *argv[])
{
	text_ws * tw;

	tw = new text_ws(1, argv[1]);

	tw->parse_file(argv[2], CODE_TYPE_UTF8);

	tw->show_paragraph();
	delete tw;

	return 0;
}
