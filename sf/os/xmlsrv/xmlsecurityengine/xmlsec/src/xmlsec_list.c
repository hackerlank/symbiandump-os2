/** 
 * XML Security Library (http://www.aleksey.com/xmlsec).
 *
 * List of pointers.
 *
 * This is free software; see Copyright file in the source
 * distribution for preciese wording.
 * 
 * Copyright (C) 2002-2003 Aleksey Sanin <aleksey@aleksey.com>
 * Portion Copyright � 2009 Nokia Corporation and/or its subsidiary(-ies). All rights reserved. 
 */
#include "xmlsec_globals.h"

#include <stdlib.h>
#include <string.h>
 
#include <stdapis/libxml2/libxml2_tree.h>
#include <stdapis/libxml2/libxml2_globals.h>

#include "xmlsec_xmlsec.h"
#include "xmlsec_list.h"
#include "xmlsec_errors.h"


static int		xmlSecPtrListEnsureSize			(xmlSecPtrListPtr list,
								 xmlSecSize size);
								 
static xmlSecAllocMode gAllocMode = xmlSecAllocModeDouble;
static xmlSecSize gInitialSize = 64;

/** 
 * xmlSecPtrListSetDefaultAllocMode:
 * @defAllocMode:	the new default memory allocation mode.
 * @defInitialSize:	the new default minimal initial size.
 *
 * Sets new default allocation mode and minimal initial list size.
 */
EXPORT_C
void 
xmlSecPtrListSetDefaultAllocMode(xmlSecAllocMode defAllocMode, xmlSecSize defInitialSize) {
    xmlSecAssert(defInitialSize > 0);
    
    gAllocMode = defAllocMode;
    gInitialSize = defInitialSize;
}

/**
 * xmlSecPtrListCreate:
 * @id:			the list klass.
 * 
 * Creates new list object. Caller is responsible for freeing returned list
 * by calling #xmlSecPtrListDestroy function.
 *
 * Returns pointer to newly allocated list or NULL if an error occurs.
 */
EXPORT_C
xmlSecPtrListPtr 
xmlSecPtrListCreate(xmlSecPtrListId id) {
    xmlSecPtrListPtr list;
    int ret;
    
    xmlSecAssert2(id != xmlSecPtrListIdUnknown, NULL);
    
    /* Allocate a new xmlSecPtrList and fill the fields. */
    list = (xmlSecPtrListPtr)xmlMalloc(sizeof(xmlSecPtrList));
    if(list == NULL) {
	xmlSecError(XMLSEC_ERRORS_HERE,
		    xmlSecErrorsSafeString(xmlSecPtrListKlassGetName(id)),
		    NULL,
		    XMLSEC_ERRORS_R_MALLOC_FAILED,
		    "sizeof(xmlSecPtrList)=%d", 
		    sizeof(xmlSecPtrList));
	return(NULL);
    }
    
    ret = xmlSecPtrListInitialize(list, id);
    if(ret < 0) {
	xmlSecError(XMLSEC_ERRORS_HERE,
		    xmlSecErrorsSafeString(xmlSecPtrListKlassGetName(id)),
		    "xmlSecPtrListInitialize",
		    XMLSEC_ERRORS_R_XMLSEC_FAILED,
		    XMLSEC_ERRORS_NO_MESSAGE);
	xmlFree(list);
	return(NULL);
    }
    
    return(list);    
}

/**
 * xmlSecPtrListDestroy:
 * @list:		the pointer to list.
 *
 * Destroys @list created with #xmlSecPtrListCreate function.
 */
EXPORT_C
void 
xmlSecPtrListDestroy(xmlSecPtrListPtr list) {
    xmlSecAssert(xmlSecPtrListIsValid(list));
    xmlSecPtrListFinalize(list);
    xmlFree(list);
}

/**
 * xmlSecPtrListInitialize:
 * @list:		the pointer to list.
 * @id:			the list klass.
 *
 * Initializes the list of given klass. Caller is responsible 
 * for cleaning up by calling #xmlSecPtrListFinalize function.
 *
 * Returns 0 on success or a negative value if an error occurs.
 */
EXPORT_C
int 
xmlSecPtrListInitialize(xmlSecPtrListPtr list, xmlSecPtrListId id) {
    xmlSecAssert2(id != xmlSecPtrListIdUnknown, -1);
    xmlSecAssert2(list != NULL, -1);

    memset(list, 0, sizeof(xmlSecPtrList));    
    list->id = id;
    list->allocMode = gAllocMode;
    
    return(0);
}

/**
 * xmlSecPtrListFinalize:
 * @list:		the pointer to list.
 *  
 * Cleans up the list initialized with #xmlSecPtrListInitialize
 * function.
 */
EXPORT_C
void
xmlSecPtrListFinalize(xmlSecPtrListPtr list) {
    xmlSecAssert(xmlSecPtrListIsValid(list));

    xmlSecPtrListEmpty(list);
    memset(list, 0, sizeof(xmlSecPtrList));    
}

/**
 * xmlSecPtrListEmpty:
 * @list:		the pointer to list.
 *
 * Remove all items from @list (if any).
 */
EXPORT_C
void 
xmlSecPtrListEmpty(xmlSecPtrListPtr list) {
    xmlSecAssert(xmlSecPtrListIsValid(list));

    if(list->id->destroyItem != NULL) {
	xmlSecSize pos;
	
	for(pos = 0; pos < list->use; ++pos) {
	    xmlSecAssert(list->data != NULL);
	    if(list->data[pos] != NULL) {
		list->id->destroyItem(list->data[pos]);
	    }
	}
    }
    if(list->max > 0) {
	xmlSecAssert(list->data != NULL);

	memset(list->data, 0, sizeof(xmlSecPtr) * list->use);
	xmlFree(list->data);
    }
    list->max = list->use = 0;
    list->data = NULL;
}

/**
 * xmlSecPtrListCopy:
 * @dst:		the pointer to destination list.
 * @src:		the pointer to source list.
 *
 * Copies @src list items to @dst list using #duplicateItem method
 * of the list klass. If #duplicateItem method is NULL then 
 * we jsut copy pointers to items.
 *
 * Returns 0 on success or a negative value if an error occurs.
 */
EXPORT_C
int
xmlSecPtrListCopy(xmlSecPtrListPtr dst, xmlSecPtrListPtr src) {
    xmlSecSize i;
    int ret;
    
    xmlSecAssert2(xmlSecPtrListIsValid(dst), -1);
    xmlSecAssert2(xmlSecPtrListIsValid(src), -1);
    xmlSecAssert2(dst->id == src->id, -1);
    
    /* allocate memory */
    ret = xmlSecPtrListEnsureSize(dst, dst->use + src->use);
    if(ret < 0) {
	xmlSecError(XMLSEC_ERRORS_HERE,
		    xmlSecErrorsSafeString(xmlSecPtrListGetName(src)),
		    "xmlSecPtrListEnsureSize",
		    XMLSEC_ERRORS_R_XMLSEC_FAILED,
		    "size=%d", src->use);
	return(-1);
    }

    /* copy one item after another */    
    for(i = 0; i < src->use; ++i, ++dst->use) {
	xmlSecAssert2(src->data != NULL, -1);
	xmlSecAssert2(dst->data != NULL, -1);
	
	if((dst->id->duplicateItem != NULL) && (src->data[i] != NULL)) {
	    dst->data[dst->use] = dst->id->duplicateItem(src->data[i]);
	    if(dst->data[dst->use] == NULL) {
		xmlSecError(XMLSEC_ERRORS_HERE,
			    xmlSecErrorsSafeString(xmlSecPtrListGetName(src)),
			    "duplicateItem",
			    XMLSEC_ERRORS_R_XMLSEC_FAILED,
			    XMLSEC_ERRORS_NO_MESSAGE);
		return(-1);
	    }
	} else {
	    dst->data[dst->use] = src->data[i];
	}
    }
    
    return(0);
}

/**
 * xmlSecPtrListDuplicate:
 * @list:		the pointer to list.
 *  
 * Creates a new copy of @list and all its items.
 *
 * Returns pointer to newly allocated list or NULL if an error occurs.
 */
EXPORT_C
xmlSecPtrListPtr 
xmlSecPtrListDuplicate(xmlSecPtrListPtr list) {
    xmlSecPtrListPtr newList;
    int ret;
    
    xmlSecAssert2(xmlSecPtrListIsValid(list), NULL);
    
    newList = xmlSecPtrListCreate(list->id);
    if(newList == NULL) {
	xmlSecError(XMLSEC_ERRORS_HERE,
		    xmlSecErrorsSafeString(xmlSecPtrListGetName(list)),
		    "xmlSecPtrListCreate",
		    XMLSEC_ERRORS_R_XMLSEC_FAILED,
		    XMLSEC_ERRORS_NO_MESSAGE);
	return(NULL);
    }
    
    ret = xmlSecPtrListCopy(newList, list);
    if(ret < 0) {
	xmlSecError(XMLSEC_ERRORS_HERE,
		    xmlSecErrorsSafeString(xmlSecPtrListGetName(list)),
		    "xmlSecPtrListCopy",
		    XMLSEC_ERRORS_R_XMLSEC_FAILED,
		    XMLSEC_ERRORS_NO_MESSAGE);
	xmlSecPtrListDestroy(newList);
	return(NULL);
    }
    return(newList);
}

/**
 * xmlSecPtrListGetSize:
 * @list:		the pointer to list.
 *
 * Gets list size.
 * 
 * Returns the number of itmes in @list.
 */
EXPORT_C
xmlSecSize	
xmlSecPtrListGetSize(xmlSecPtrListPtr list) {
    xmlSecAssert2(xmlSecPtrListIsValid(list), 0);
    
    return(list->use);
}

/**
 * xmlSecPtrListGetItem:
 * @list:		the pointer to list.
 * @pos:		the item position.
 *
 * Gets item from the list.
 *
 * Returns the list item at position @pos or NULL if @pos is greater
 * than the number of items in the list or an error occurs.
 */
EXPORT_C
xmlSecPtr 
xmlSecPtrListGetItem(xmlSecPtrListPtr list, xmlSecSize pos) {
    xmlSecAssert2(xmlSecPtrListIsValid(list), NULL);
    xmlSecAssert2(list->data != NULL, NULL);
    xmlSecAssert2(pos < list->use, NULL);

    return(list->data[pos]);
}

/**
 * xmlSecPtrListAdd:
 * @list:		the pointer to list.
 * @item:		the item.
 *
 * Adds @item to the end of the @list.
 *
 * Returns 0 on success or a negative value if an error occurs.
 */
EXPORT_C
int 
xmlSecPtrListAdd(xmlSecPtrListPtr list, xmlSecPtr item) {
    int ret;
    
    xmlSecAssert2(xmlSecPtrListIsValid(list), -1);
    
    ret = xmlSecPtrListEnsureSize(list, list->use + 1);
    if(ret < 0) {
	xmlSecError(XMLSEC_ERRORS_HERE,
		    xmlSecErrorsSafeString(xmlSecPtrListGetName(list)),
		    "xmlSecPtrListAdd",
		    XMLSEC_ERRORS_R_XMLSEC_FAILED,
		    "size=%d", list->use + 1);
	return(-1);
    }
    
    list->data[list->use++] = item;
    return(0);
}

/**
 * xmlSecPtrListSet:
 * @list:		the pointer to list.
 * @item:		the item.
 * @pos:		the pos.
 *
 * Sets the value of list item at position @pos. The old value
 * is destroyed.
 *
 * Returns 0 on success or a negative value if an error occurs.
 */
EXPORT_C
int 
xmlSecPtrListSet(xmlSecPtrListPtr list, xmlSecPtr item, xmlSecSize pos) {
    xmlSecAssert2(xmlSecPtrListIsValid(list), -1);
    xmlSecAssert2(list->data != NULL, -1);
    xmlSecAssert2(pos < list->use, -1);

    if((list->id->destroyItem != NULL) && (list->data[pos] != NULL)) {
	list->id->destroyItem(list->data[pos]);
    }
    list->data[pos] = item;
    return(0);
}

/**
 * xmlSecPtrListRemove:
 * @list:		the pointer to list.
 * @pos:		the position.
 *
 * Destroys list item at the position @pos and sets it value to NULL.
 *
 * Returns 0 on success or a negative value if an error occurs.
 */
EXPORT_C
int 
xmlSecPtrListRemove(xmlSecPtrListPtr list, xmlSecSize pos) {
    xmlSecAssert2(xmlSecPtrListIsValid(list), -1);
    xmlSecAssert2(list->data != NULL, -1);
    xmlSecAssert2(pos < list->use, -1);

    if((list->id->destroyItem != NULL) && (list->data[pos] != NULL)) {
	list->id->destroyItem(list->data[pos]);
    }
    list->data[pos] = NULL;
    if(pos == list->use - 1) {
	--list->use;
    }
    return(0);
}

/**
 * xmlSecPtrListDebugDump:
 * @list:		the pointer to list.
 * @output:		the pointer to output FILE.
 *
 * Prints debug information about @list to the @output.
 */
EXPORT_C
void 
xmlSecPtrListDebugDump(xmlSecPtrListPtr list, FILE* output) {
    xmlSecAssert(xmlSecPtrListIsValid(list));
    xmlSecAssert(output != NULL);

    fprintf(output, "=== list size: %d\n", list->use);    
    if(list->id->debugDumpItem != NULL) {
	xmlSecSize pos;
	
	for(pos = 0; pos < list->use; ++pos) {
	    xmlSecAssert(list->data != NULL);
	    if(list->data[pos] != NULL) {
		list->id->debugDumpItem(list->data[pos], output);
	    }
	}	
    }
}

/**
 * xmlSecPtrListDebugXmlDump:
 * @list:		the pointer to list.
 * @output:		the pointer to output FILE.
 *
 * Prints debug information about @list to the @output in XML format.
 */
EXPORT_C
void 
xmlSecPtrListDebugXmlDump(xmlSecPtrListPtr list, FILE* output) {
    xmlSecAssert(xmlSecPtrListIsValid(list));
    xmlSecAssert(output != NULL);
    
    fprintf(output, "<List size=\"%d\">\n", list->use);    
    if(list->id->debugXmlDumpItem != NULL) {
	xmlSecSize pos;
	
	for(pos = 0; pos < list->use; ++pos) {
	    xmlSecAssert(list->data != NULL);
	    if(list->data[pos] != NULL) {
		list->id->debugXmlDumpItem(list->data[pos], output);
	    }
	}	
    }
    fprintf(output, "</List>\n");    
}

static int 
xmlSecPtrListEnsureSize(xmlSecPtrListPtr list, xmlSecSize size) {
    xmlSecPtr* newData;
    xmlSecSize newSize = 0;

    xmlSecAssert2(xmlSecPtrListIsValid(list), -1);
    
    if(size < list->max) {
	return(0);
    }

    switch(list->allocMode) {
	case xmlSecAllocModeExact:
	    newSize = size + 8;
	    break;
	case xmlSecAllocModeDouble:
	    newSize = 2 * size + 32;
	    break;
    }
    
    if(newSize < gInitialSize) {
	newSize = gInitialSize;
    }
    
    if(list->data != NULL) {
    	newData = (xmlSecPtr*)xmlRealloc(list->data, sizeof(xmlSecPtr) * newSize);
    } else {
    	newData = (xmlSecPtr*)xmlMalloc(sizeof(xmlSecPtr) * newSize);
    }
    if(newData == NULL) {
	xmlSecError(XMLSEC_ERRORS_HERE,
		    xmlSecErrorsSafeString(xmlSecPtrListGetName(list)),
		    NULL,
		    XMLSEC_ERRORS_R_MALLOC_FAILED,
		    "sizeof(xmlSecPtr)*%d=%d", 
		    newSize, sizeof(xmlSecPtr) * newSize);
	return(-1);
    }
    
    list->data = newData;
    list->max = newSize;
    
    return(0);
}

/***********************************************************************
 *
 * strings list
 *
 **********************************************************************/
static xmlSecPtr 	xmlSecStringListDuplicateItem		(xmlSecPtr ptr);
static void		xmlSecStringListDestroyItem		(xmlSecPtr ptr);

static xmlSecPtrListKlass xmlSecStringListKlass = {
    BAD_CAST "strings-list",
    xmlSecStringListDuplicateItem,		/* xmlSecPtrDuplicateItemMethod duplicateItem; */
    xmlSecStringListDestroyItem,		/* xmlSecPtrDestroyItemMethod destroyItem; */
    NULL,					/* xmlSecPtrDebugDumpItemMethod debugDumpItem; */
    NULL,					/* xmlSecPtrDebugDumpItemMethod debugXmlDumpItem; */
};

/**
 * xmlSecStringListGetKlass:
 * 
 * The strins list class.
 *
 * Returns strings list klass.
 */
EXPORT_C
xmlSecPtrListId 
xmlSecStringListGetKlass(void) {
    return(&xmlSecStringListKlass);
}

static xmlSecPtr 
xmlSecStringListDuplicateItem(xmlSecPtr ptr) {
    xmlSecAssert2(ptr != NULL, NULL);
    
    return(xmlStrdup((xmlChar*)ptr));
}

static void 
xmlSecStringListDestroyItem(xmlSecPtr ptr) {
    xmlSecAssert(ptr != NULL);
    
    xmlFree(ptr);
}


