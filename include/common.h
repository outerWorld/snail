// -*- encoding=utf-8 -*-

#ifndef __COMMON_H
#define __COMMON_H

#define MEM_ALLOC(pbuf, type, size, errRet) \
	pbuf = (type)malloc(size); \
	if (!pbuf) return errRet; \
	memset(pbuf, 0x00, size);

#define MEM_FREE(pbuf) free(pbuf); pbuf = NULL;

#endif // __COMMON_H
