/*-
 * Copyright (c) 1983, 1987, 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

/*
 * Portions Copyright (c) 1996 by Internet Software Consortium.
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND INTERNET SOFTWARE CONSORTIUM DISCLAIMS
 * ALL WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL INTERNET SOFTWARE
 * CONSORTIUM BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
 * DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR
 * PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS
 * ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS
 * SOFTWARE.
 * Portions Copyright (c) 2007 Nokia Corporation and/or its subsidiary(-ies). All rights reserved.
 */

/*
 *	@(#)resolv.h	8.1 (Berkeley) 6/2/93
 *	From Id: resolv.h,v 8.12 1998/04/28 19:36:46 halley Exp $
 * $FreeBSD: src/include/resolv.h,v 1.26 2004/09/09 17:39:47 yar Exp $
 */

#ifndef _RESOLV_H_
#define	_RESOLV_H_

#include <sys/param.h>
#include <sys/types.h>
#include <sys/cdefs.h>
#include <sys/socket.h>
#include <stdio.h>

/*
 * Revision information.  This is the release date in YYYYMMDD format.
 * It can change every day so the right thing to do with it is use it
 * in preprocessor commands such as "#if (__RES > 19931104)".  Do not
 * compare for equality; rather, use it to determine whether your resolver
 * is new enough to contain a certain feature.
 */

#define	__RES	19960801

/*
 * Resolver configuration file.
 * Normally not present, but may contain the address of the
 * inital name server(s) to query and the domain search list.
 */

#ifndef _PATH_RESCONF
#define	_PATH_RESCONF        "/etc/resolv.conf"
#endif

/*
 * Global defines and variables for resolver stub.
 */
#define	MAXNS			3	/* max # name servers we'll track */
#define	MAXDFLSRCH		3	/* # default domain levels to try */
#define	MAXDNSRCH		6	/* max # domains in search path */
#define	LOCALDOMAINPARTS	2	/* min levels in name that is "local" */

#define	RES_TIMEOUT		5	/* min. seconds between retries */
#define	RES_DFLRETRY		4	/* retries per each name server */
#define	MAXRESOLVSORT		10	/* number of net to sort on */
#define	RES_MAXNDOTS		15	/* should reflect bit field size */
#define	RES_MAXRETRANS		30	/* only for resolv.conf/RES_OPTIONS */
#define	RES_MAXRETRY		5	/* only for resolv.conf/RES_OPTIONS */

struct __res_state {
	int	retrans;	 	/* retransmition time interval */
	int	retry;			/* number of times to retransmit */
	u_long	options;		/* option flags - see below. */
	int	nscount;		/* number of name servers */
	struct sockaddr_in
		nsaddr_list[MAXNS];	/* address of name server */
#define	nsaddr	nsaddr_list[0]		/* for backward compatibility */
	u_short	id;			/* current message id */
	char	*dnsrch[MAXDNSRCH+1];	/* components of domain to search */
	char	defdname[256];		/* default domain (deprecated) */
	u_long	pfcode;			/* RES_PRF_ flags - see below. */
	unsigned ndots:4;		/* threshold for initial abs. query */
	unsigned nsort:4;		/* number of elements in sort_list[] */
	char	unused[3];
	struct {
		struct in_addr	addr;
		u_int32_t	mask;
	} sort_list[MAXRESOLVSORT];
	char	pad[72];		/* on an i386 this means 512b total */
};

/* for INET6 */
/*
 * replacement of __res_state, separated to keep binary compatibility.
 */
struct __res_state_ext {
	struct sockaddr_storage nsaddr_list[MAXNS];
	struct {
		int	af;		/* address family for addr, mask */
		union {
			struct	in_addr ina;
			struct	in6_addr in6a;
		} addr, mask;
	} sort_list[MAXRESOLVSORT];
};

/*
 * Resolver options (keep these in synch with res_debug.c, please)
 */
#define RES_INIT	0x00000001	/* address initialized */
#define RES_DEBUG	0x00000002	/* print debug messages */
#define RES_AAONLY	0x00000004	/* authoritative answers only (!IMPL)*/
#define RES_USEVC	0x00000008	/* use virtual circuit */
#define RES_PRIMARY	0x00000010	/* query primary server only (!IMPL) */
#define RES_IGNTC	0x00000020	/* ignore truncation errors */
#define RES_RECURSE	0x00000040	/* recursion desired */
#define RES_DEFNAMES	0x00000080	/* use default domain name */
#define RES_STAYOPEN	0x00000100	/* Keep TCP socket open */
#define RES_DNSRCH	0x00000200	/* search up local domain tree */
#define	RES_INSECURE1	0x00000400	/* type 1 security disabled */
#define	RES_INSECURE2	0x00000800	/* type 2 security disabled */
#define	RES_NOALIASES	0x00001000	/* shuts off HOSTALIASES feature */
#define	RES_USE_INET6	0x00002000	/* use/map IPv6 in gethostbyname() */
#define	RES_NOTLDQUERY	0x00004000	/* Don't query TLD names */
/* KAME extensions: use higher bit to avoid conflict with ISC use */
#define	RES_USE_EDNS0	0x40000000	/* use EDNS0 */

#define RES_DEFAULT	(RES_RECURSE | RES_DEFNAMES | RES_DNSRCH)

/*
 * Resolver "pfcode" values.  Used by dig.
 */
#define	RES_PRF_STATS	0x00000001
#define	RES_PRF_UPDATE	0x00000002
#define	RES_PRF_CLASS   0x00000004
#define	RES_PRF_CMD	0x00000008
#define	RES_PRF_QUES	0x00000010
#define	RES_PRF_ANS	0x00000020
#define	RES_PRF_AUTH	0x00000040
#define	RES_PRF_ADD	0x00000080
#define	RES_PRF_HEAD1	0x00000100
#define	RES_PRF_HEAD2	0x00000200
#define	RES_PRF_TTLID	0x00000400
#define	RES_PRF_HEADX	0x00000800
#define	RES_PRF_QUERY	0x00001000
#define	RES_PRF_REPLY	0x00002000
#define	RES_PRF_INIT    0x00004000
/*			0x00008000	*/

typedef enum { res_goahead, res_nextns, res_modified, res_done, res_error }
	res_sendhookact;

typedef res_sendhookact (*res_send_qhook)(struct sockaddr * const *ns,
					  const u_char **query,
					  int *querylen,
					  u_char *ans,
					  int anssiz,
					  int *resplen);

typedef res_sendhookact (*res_send_rhook)(const struct sockaddr *ns,
					  const u_char *query,
					  int querylen,
					  u_char *ans,
					  int anssiz,
					  int *resplen);

struct res_sym {
	int	number;		/* Identifying number, like T_MX */
	char *	name;		/* Its symbolic name, like "MX" */
	char *	humanname;	/* Its fun name, like "mail exchanger" */
};

__BEGIN_DECLS
extern struct __res_state *___res(void);
extern struct __res_state_ext *___res_ext(void);
__END_DECLS
#define	_res		(*___res())
#define	_res_ext	(*___res_ext())
/* for INET6 */
extern struct __res_state_ext _res_ext;

extern const struct res_sym __p_class_syms[];
extern const struct res_sym __p_type_syms[];

/* Private routines shared between libc/net, named, nslookup and others. */
#define	res_hnok	__res_hnok
#define	res_ownok	__res_ownok
#define	res_mailok	__res_mailok
#define	res_dnok	__res_dnok
#define	sym_ston	__sym_ston
#define	sym_ntos	__sym_ntos
#define	sym_ntop	__sym_ntop
#define	b64_ntop	__b64_ntop
#define	b64_pton	__b64_pton
#define	loc_ntoa	__loc_ntoa
#define	loc_aton	__loc_aton
#define	fp_resstat	__fp_resstat
#define	p_query		__p_query
#define	dn_skipname	__dn_skipname
#define	fp_resstat	__fp_resstat
#define	fp_query	__fp_query
#define	fp_nquery	__fp_nquery
#define	hostalias	__hostalias
#define	putlong		__putlong
#define	putshort	__putshort
#define	p_class		__p_class
#define	p_time		__p_time
#define	p_type		__p_type
#define	p_query		__p_query
#define	p_cdnname	__p_cdnname
#define	p_section	__p_section
#define	p_cdname	__p_cdname
#define	p_fqnname	__p_fqnname
#define	p_fqname	__p_fqname
#define	p_option	__p_option
#define	p_secstodate	__p_secstodate
#define	dn_count_labels	__dn_count_labels
#define	dn_comp		__dn_comp
#define	dn_expand	__dn_expand
#define	res_init	__res_init
#define	res_randomid	__res_randomid
#define	res_query	__res_query
#define	res_search	__res_search
#define	res_querydomain	__res_querydomain
#define	res_mkquery	__res_mkquery
#define	res_send	__res_send
#define	res_isourserver	__res_isourserver
#define	res_nameinquery	__res_nameinquery
#define	res_queriesmatch __res_queriesmatch
#define	res_close	__res_close
#define	res_opt		__res_opt
#define	res_mkupdate	__res_mkupdate
#define	res_mkupdrec	__res_mkupdrec
#define	res_freeupdrec	__res_freeupdrec


#endif /* !_RESOLV_H_ */
