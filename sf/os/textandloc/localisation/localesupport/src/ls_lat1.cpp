/*
* Copyright (c) 1995-2009 Nokia Corporation and/or its subsidiary(-ies).
* All rights reserved.
* This component and the accompanying materials are made available
* under the terms of "Eclipse Public License v1.0"
* which accompanies this distribution, and is available
* at the URL "http://www.eclipse.org/legal/epl-v10.html".
*
* Initial Contributors:
* Nokia Corporation - initial contribution.
*
* Contributors:
*
* Description: 
* WINDOWS ISO LATIN 1 Western European Alphabetic Conversions etc (excludes
* Scandinavia).
*
*/


#include "ls_std.h"

// This file is only used in the non-Unicode build.
#ifndef _UNICODE

// The character type conversion table
const TUint8 LAlphabet::TypeTable[KMaxTranslateTable] =
	{
	(__C),      // 0x00 - NUL
	(__C),      // 0x01 - SOH
	(__C),      // 0x02 - STX
	(__C),      // 0x03 - ETX
	(__C),      // 0x04 - EOT
	(__C),      // 0x05 - ENQ
	(__C),      // 0x06 - ACK
	(__C),      // 0x07 - BEL
	(__C),      // 0x08 - BS 
	(__C|__S),  // 0x09 - HT 
	(__C|__S),  // 0x0a - NL 
	(__C|__S),  // 0x0b - VT 
	(__C|__S),  // 0x0c - FF 
	(__C|__S),  // 0x0d - CR 
	(__C),      // 0x0e - SO 
	(__C),      // 0x0f - SI 
	(__C|__S),	// 0x10 - DLE
	(__C),      // 0x11 - DC1
	(__C),      // 0x12 - DC2
	(__C),      // 0x13 - DC3
	(__C),      // 0x14 - DC4
	(__C),      // 0x15 - NAK
	(__C),      // 0x16 - SYN
	(__C),      // 0x17 - ETB
	(__C),      // 0x18 - CAN
	(__C),      // 0x19 - EM 
	(__C),      // 0x1a - SUB
	(__C),      // 0x1b - ESC
	(__C),      // 0x1c - FS 
	(__C),      // 0x1d - GS 
	(__C),      // 0x1e - RS 
	(__C),      // 0x1f - US 
	(__S|__B),  // 0x20 - ' '
	(__P),      // 0x21 - '!'
	(__P),      // 0x22 - '"'
	(__P),      // 0x23 - '#'
	(__P),      // 0x24 - '$'
	(__P),      // 0x25 - '%'
	(__P),      // 0x26 - '&'
	(__P),      // 0x27 - '''
	(__P),      // 0x28 - '('
	(__P),      // 0x29 - ')'
	(__P),      // 0x2a - '*'
	(__P),      // 0x2b - '+'
	(__P),      // 0x2c - ','
	(__P),      // 0x2d - '-'
	(__P),      // 0x2e - '.'
	(__P),      // 0x2f - '/'
	(__D|__X),  // 0x30 - '0'
	(__D|__X),  // 0x31 - '1'
	(__D|__X),  // 0x32 - '2'
	(__D|__X),  // 0x33 - '3'
	(__D|__X),  // 0x34 - '4'
	(__D|__X),  // 0x35 - '5'
	(__D|__X),  // 0x36 - '6'
	(__D|__X),  // 0x37 - '7'
	(__D|__X),  // 0x38 - '8'
	(__D|__X),  // 0x39 - '9'
	(__P),      // 0x3a - ':'
	(__P),      // 0x3b - ';'
	(__P),      // 0x3c - '<'
	(__P),      // 0x3d - '='
	(__P),      // 0x3e - '>'
	(__P),      // 0x3f - '?'
	(__P),      // 0x40 - '@'
	(__U|__X),  // 0x41 - 'A'
	(__U|__X),  // 0x42 - 'B'
	(__U|__X),  // 0x43 - 'C'
	(__U|__X),  // 0x44 - 'D'
	(__U|__X),  // 0x45 - 'E'
	(__U|__X),  // 0x46 - 'F'
	(__U),      // 0x47 - 'G'
	(__U),      // 0x48 - 'H'
	(__U),      // 0x49 - 'I'
	(__U),      // 0x4a - 'J'
	(__U),      // 0x4b - 'K'
	(__U),      // 0x4c - 'L'
	(__U),      // 0x4d - 'M'
	(__U),      // 0x4e - 'N'
	(__U),      // 0x4f - 'O'
	(__U),      // 0x50 - 'P'
	(__U),      // 0x51 - 'Q'
	(__U),      // 0x52 - 'R'
	(__U),      // 0x53 - 'S'
	(__U),      // 0x54 - 'T'
	(__U),      // 0x55 - 'U'
	(__U),      // 0x56 - 'V'
	(__U),      // 0x57 - 'W'
	(__U),      // 0x58 - 'X'
	(__U),      // 0x59 - 'Y'
	(__U),      // 0x5a - 'Z'
	(__P),      // 0x5b - '['
	(__P),      // 0x5c - '\'
	(__P),      // 0x5d - ']'
	(__P),      // 0x5e - '^'
	(__P),      // 0x5f - '_'
	(__P),      // 0x60 - '`'
	(__L|__X),  // 0x61 - 'a'
	(__L|__X),  // 0x62 - 'b'
	(__L|__X),  // 0x63 - 'c'
	(__L|__X),  // 0x64 - 'd'
	(__L|__X),  // 0x65 - 'e'
	(__L|__X),  // 0x66 - 'f'
	(__L),      // 0x67 - 'g'
	(__L),      // 0x68 - 'h'
	(__L),      // 0x69 - 'i'
	(__L),      // 0x6a - 'j'
	(__L),      // 0x6b - 'k'
	(__L),      // 0x6c - 'l'
	(__L),      // 0x6d - 'm'
	(__L),      // 0x6e - 'n'
	(__L),      // 0x6f - 'o'
	(__L),      // 0x70 - 'p'
	(__L),      // 0x71 - 'q'
	(__L),      // 0x72 - 'r'
	(__L),      // 0x73 - 's'
	(__L),      // 0x74 - 't'
	(__L),      // 0x75 - 'u'
	(__L),      // 0x76 - 'v'
	(__L),      // 0x77 - 'w'
	(__L),      // 0x78 - 'x'
	(__L),      // 0x79 - 'y'
	(__L),      // 0x7a - 'z'
	(__P),      // 0x7b - '{'
	(__P),      // 0x7c - '|'
	(__P),      // 0x7d - '}'
	(__P),      // 0x7e - '~'
	(__C),      // 0x7f - DEL
	(__P),      // 0x80 - euro currency symbol
    (__C),      // 0x81 - <control>
	(__P),      // 0x82 - single low-9 quotation mark
	(__L),      // 0x83 - small f with hook	 
	(__P),      // 0x84 - double low-9 quotation mark 
	(__P),      // 0x85 - horizontal ellipsis (...)			
	(__P),      // 0x86 - dagger							
	(__P),      // 0x87 - double dagger						
	(__P),      // 0x88 - circumflex accent
	(__P),      // 0x89 - per mille sign
	(__U),      // 0x8a - S with caron
	(__P),      // 0x8b - single left-pointing angle quotation mark
	(__U),      // 0x8c - capital ligature OE
	(__C),      // 0x8d - <control>
	(__U),      // 0x8e - Z with caron
	(__C),      // 0x8f - <control>
	(__C),      // 0x90 - <control>
	(__P),      // 0x91 - left single quotation mark
	(__P),      // 0x92 - right single quotation mark
	(__P),      // 0x93 - left double quotation mark
	(__P),      // 0x94 - right double quotation mark
	(__P),      // 0x95 - bullet
	(__P),      // 0x96 - en dash
	(__P),      // 0x97 - em dash
	(__P),      // 0x98 - small tilde
	(__P),      // 0x99 - trade mark sign
	(__L),      // 0x9a - small s with caron
	(__P),      // 0x9b - single right-pointing angle quotation mark
	(__L),      // 0x9c - small ligature oe
	(__C),      // 0x9d - <control>
	(__L),      // 0x9e - small z with caron
	(__U),      // 0x9f - Y umlaut
	(__C),      // 0xa0 - no-break space
	(__P),      // 0xa1 - inverted exclamation mark
	(__P),      // 0xa2 - cent sign
	(__P),      // 0xa3 - pound sign
	(__P),      // 0xa4 - currency sign
	(__P),      // 0xa5 - yen sign
	(__P),      // 0xa6 - broken bar
	(__P),      // 0xa7 - section sign
	(__P),      // 0xa8 - diaresis
	(__P),      // 0xa9 - copyright sign
	(__P),      // 0xaa - feminine ordinal indicator
	(__P),      // 0xab - <<
	(__P),      // 0xac - � logical not sign
	(__P),      // 0xad - soft hyphen
	(__P),      // 0xae - registered sign
	(__P),      // 0xaf - macron
	(__P),      // 0xb0 - degree sign
	(__P),      // 0xb1 - plus-minus sign
	(__P),      // 0xb2 - superscript 2
	(__P),      // 0xb3 - superscript 3
	(__P),      // 0xb4 - acute accent
	(__L),      // 0xb5 - micro sign  **** lower case letter or symbol??? ****
	(__P),      // 0xb6 - pilcrow sign
	(__P),      // 0xb7 - middle dot
	(__P),      // 0xb8 - cedilla
	(__P),      // 0xb9 - superscript 1
	(__P),      // 0xba - masculine ordinal indicator
	(__P),      // 0xbb - >>
	(__P),      // 0xbc - 1/4
	(__P),      // 0xbd - 1/2
	(__P),      // 0xbe - 3/4
	(__P),      // 0xbf - inverted ?
	(__U),      // 0xc0 - A grave
	(__U),      // 0xc1 - A acute
	(__U),      // 0xc2 - A circumflex
	(__U),      // 0xc3 - A tilde
	(__U),      // 0xc4 - A umlaut
	(__U),      // 0xc5 - A with ring above
	(__U),      // 0xc6 - AE ligature
	(__U),      // 0xc7 - C cedilla
	(__U),      // 0xc8 - E grave
	(__U),      // 0xc9 - E acute
	(__U),      // 0xca - E circumflex
	(__U),      // 0xcb - E umlaut
	(__U),      // 0xcc - I grave
	(__U),      // 0xcd - I acute
	(__U),      // 0xce - I circumflex
	(__U),      // 0xcf - I umlaut
	(__U),      // 0xd0 - Eth
	(__U),      // 0xd1 - N tilde
	(__U),      // 0xd2 - O grave
	(__U),      // 0xd3 - O acute
	(__U),      // 0xd4 - O circumflex	
	(__U),      // 0xd5 - O tilde
	(__U),      // 0xd6 - O umlaut
	(__P),      // 0xd7 - multiplication
	(__U),      // 0xd8 - O slash
	(__U),      // 0xd9 - U grave
	(__U),      // 0xda - U acute
	(__U),      // 0xdb - U circumflex
	(__U),      // 0xdc - U umlaut
	(__U),      // 0xdd - Y acute
	(__U),      // 0xde - Thorn
	(__L),      // 0xdf - small letter sharp s
	(__L),      // 0xe0 - a grave
	(__L),      // 0xe1 - a acute
	(__L),      // 0xe2 - a circumflex
	(__L),      // 0xe3 - a tilde
	(__L),      // 0xe4 - a umlaut
	(__L),      // 0xe5 - a ring
	(__L),      // 0xe6 - ae ligature
	(__L),      // 0xe7 - c cedilla
	(__L),      // 0xe8 - e grave
	(__L),      // 0xe9 - e acute
	(__L),      // 0xea - e circumflex
	(__L),      // 0xeb - e umlaut
	(__L),      // 0xec - i grave
	(__L),      // 0xed - i acute
	(__L),      // 0xee - i circumflex
	(__L),      // 0xef - i umlaut
	(__L),      // 0xf0 - eth
	(__L),      // 0xf1 - n tilde
	(__L),      // 0xf2 - o grave
	(__L),      // 0xf3 - o acute
	(__L),      // 0xf4 - o circumflex
	(__L),      // 0xf5 - o tilde
	(__L),      // 0xf6 - o umlaut
	(__P),      // 0xf7 - division sign
	(__L),      // 0xf8 - o slash
	(__L),      // 0xf9 - u grave
	(__L),      // 0xfa - u acute
	(__L),      // 0xfb - u circumflex
	(__L),      // 0xfc - u umlaut
	(__L),      // 0xfd - y acute
	(__L),      // 0xfe - thorn
	(__L)       // 0xff - y umlaut
	};

// The uppercase table
const TText LAlphabet::UpperTable[KMaxTranslateTable] =
	{
	0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07, // 0x00
	0x08,0x09,0x0a,0x0b,0x0c,0x0d,0x0e,0x0f,
	0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17, // 0x10
	0x18,0x19,0x1a,0x1b,0x1c,0x1d,0x1e,0x1f,
	0x20,0x21,0x22,0x23,0x24,0x25,0x26,0x27, // 0x20
	0x28,0x29,0x2a,0x2b,0x2c,0x2d,0x2e,0x2f,
	0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37, // 0x30
	0x38,0x39,0x3a,0x3b,0x3c,0x3d,0x3e,0x3f,
	0x40,0x41,0x42,0x43,0x44,0x45,0x46,0x47, // 0x40
	0x48,0x49,0x4a,0x4b,0x4c,0x4d,0x4e,0x4f,
	0x50,0x51,0x52,0x53,0x54,0x55,0x56,0x57, // 0x50
	0x58,0x59,0x5a,0x5b,0x5c,0x5d,0x5e,0x5f,
	0x60,0x41,0x42,0x43,0x44,0x45,0x46,0x47, // 0x60
	0x48,0x49,0x4a,0x4b,0x4c,0x4d,0x4e,0x4f,
	0x50,0x51,0x52,0x53,0x54,0x55,0x56,0x57, // 0x70
	0x58,0x59,0x5a,0x7b,0x7c,0x7d,0x7e,0x7f,
	0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87, // 0x80
	0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,
	0x90,0x91,0x92,0x93,0x94,0x95,0x96,0x97, // 0x90
	0x98,0x99,0x8a,0x9b,0x8c,0x9d,0x8e,0x9f,
	0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7, // 0xa0 
	0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,
	0xb0,0xb1,0xb2,0xb3,0xb4,0xb5,0xb6,0xb7, // 0xb0
	0xb8,0xb9,0xba,0xbb,0xbc,0xbd,0xbe,0xbf,
	0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7, // 0xc0
	0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,
	0xd0,0xd1,0xd2,0xd3,0xd4,0xd5,0xd6,0xd7, // 0xd0
	0xd8,0xd9,0xda,0xdb,0xdc,0xdd,0xde,0xdf,
	0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7, // 0xe0
	0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,
	0xd0,0xd1,0xd2,0xd3,0xd4,0xd5,0xd6,0xf7, // 0xf0
	0xd8,0xd9,0xda,0xdb,0xdc,0xdd,0xde,0x9f
	};

// The lowercase table
const TText LAlphabet::LowerTable[KMaxTranslateTable] =
	{
	0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07, // 0x00
	0x08,0x09,0x0a,0x0b,0x0c,0x0d,0x0e,0x0f,
	0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17, // 0x10
	0x18,0x19,0x1a,0x1b,0x1c,0x1d,0x1e,0x1f,
	0x20,0x21,0x22,0x23,0x24,0x25,0x26,0x27, // 0x20
	0x28,0x29,0x2a,0x2b,0x2c,0x2d,0x2e,0x2f,
	0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37, // 0x30
	0x38,0x39,0x3a,0x3b,0x3c,0x3d,0x3e,0x3f,
	0x40,0x61,0x62,0x63,0x64,0x65,0x66,0x67, // 0x40
	0x68,0x69,0x6a,0x6b,0x6c,0x6d,0x6e,0x6f,
	0x70,0x71,0x72,0x73,0x74,0x75,0x76,0x77, // 0x50
	0x78,0x79,0x7a,0x5b,0x5c,0x5d,0x5e,0x5f,
	0x60,0x61,0x62,0x63,0x64,0x65,0x66,0x67, // 0x60
	0x68,0x69,0x6a,0x6b,0x6c,0x6d,0x6e,0x6f,
	0x70,0x71,0x72,0x73,0x74,0x75,0x76,0x77, // 0x70
	0x78,0x79,0x7a,0x7b,0x7c,0x7d,0x7e,0x7f,
	0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87, // 0x80
	0x88,0x89,0x9a,0x8b,0x9c,0x8d,0x9e,0x8f,
	0x90,0x91,0x92,0x93,0x94,0x95,0x96,0x97, // 0x90
	0x98,0x99,0x9a,0x9b,0x9c,0x9d,0x9e,0xff,
	0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7, // 0xa0
	0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,
	0xb0,0xb1,0xb2,0xb3,0xb4,0xb5,0xb6,0xb7, // 0xb0
	0xb8,0xb9,0xba,0xbb,0xbc,0xbd,0xbe,0xbf,
	0xe0,0xe1,0xe2,0xe3,0xe4,0xe5,0xe6,0xe7, // 0xc0
	0xe8,0xe9,0xea,0xeb,0xec,0xed,0xee,0xef,
	0xf0,0xf1,0xf2,0xf3,0xf4,0xf5,0xf6,0xd7, // 0xd0
	0xf8,0xf9,0xfa,0xfb,0xfc,0xfd,0xfe,0xdf,
	0xe0,0xe1,0xe2,0xe3,0xe4,0xe5,0xe6,0xe7, // 0xe0
	0xe8,0xe9,0xea,0xeb,0xec,0xed,0xee,0xef,
	0xf0,0xf1,0xf2,0xf3,0xf4,0xf5,0xf6,0xf7, // 0xf0
	0xf8,0xf9,0xfa,0xfb,0xfc,0xfd,0xfe,0xff
	};

// The new fold table
const TText LAlphabet::FoldTable[KMaxTranslateTable] =
	{
	0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07, // 0x00
	0x08,0x09,0x0a,0x0b,0x0c,0x0d,0x0e,0x0f,
	0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17, // 0x10
	0x18,0x19,0x1a,0x1b,0x1c,0x1d,0x1e,0x1f,
	0x20,0x21,0x22,0x23,0x24,0x25,0x26,0x27, // 0x20
	0x28,0x29,0x2a,0x2b,0x2c,0x2d,0x2e,0x2f,
	0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37, // 0x30
	0x38,0x39,0x3a,0x3b,0x3c,0x3d,0x3e,0x3f,
	0x40,0x41,0x42,0x43,0x44,0x45,0x46,0x47, // 0x40
	0x48,0x49,0x4a,0x4b,0x4c,0x4d,0x4e,0x4f,
	0x50,0x51,0x52,0x53,0x54,0x55,0x56,0x57, // 0x50
	0x58,0x59,0x5a,0x5b,0x5c,0x5d,0x5e,0x5f,
	0x60,0x41,0x42,0x43,0x44,0x45,0x46,0x47, // 0x60
	0x48,0x49,0x4a,0x4b,0x4c,0x4d,0x4e,0x4f,
	0x50,0x51,0x52,0x53,0x54,0x55,0x56,0x57, // 0x70
	0x58,0x59,0x5a,0x7b,0x7c,0x7d,0x7e,0x7f,
	0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87, // 0x80
	0x88,0x89,0x53,0x8b,0x8c,0x8d,0x5a,0x8f,
	0x90,0x91,0x92,0x93,0x94,0x95,0x96,0x97, // 0x90
	0x98,0x99,0x53,0x9b,0x8c,0x9d,0x5a,0x59,
	0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7, // 0xa0 
	0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,
	0xb0,0xb1,0xb2,0xb3,0xb4,0xb5,0xb6,0xb7, // 0xb0
	0xb8,0xb9,0xba,0xbb,0xbc,0xbd,0xbe,0xbf,
	0x41,0x41,0x41,0x41,0x41,0x41,0x41,0x43, // 0xc0
	0x45,0x45,0x45,0x45,0x49,0x49,0x49,0x49,
	0xd0,0x4e,0x4f,0x4f,0x4f,0x4f,0x4f,0xd7, // 0xd0
	0x4f,0x55,0x55,0x55,0x55,0x59,0xde,0xdf,
	0x41,0x41,0x41,0x41,0x41,0x41,0x41,0x43, // 0xe0
	0x45,0x45,0x45,0x45,0x49,0x49,0x49,0x49,
	0xd0,0x4e,0x4f,0x4f,0x4f,0x4f,0x4f,0xf7, // 0xf0
	0x4f,0x55,0x55,0x55,0x55,0x59,0xde,0x59
	};
	
 // The new collate table
const TText LAlphabet::CollTable[KMaxTranslateTable] =
	{
	0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07, // 0x00
	0x08,0x09,0x0a,0x0b,0x0c,0x0d,0x0e,0x0f,
	0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17, // 0x10
	0x18,0x19,0x1a,0x1b,0x1c,0x1d,0x1e,0x1f,
	0x20,0x21,0x22,0x23,0x24,0x25,0x26,0x27, // 0x20
	0x28,0x29,0x2a,0x2b,0x2c,0x2d,0x2e,0x2f,
	0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37, // 0x30
	0x38,0x39,0x3a,0x3b,0x3c,0x3d,0x3e,0x3f,
	0x40,0x41,0x42,0x43,0x44,0x45,0x46,0x47, // 0x40
	0x48,0x49,0x4a,0x4b,0x4c,0x4d,0x4e,0x4f,
	0x50,0x51,0x52,0x53,0x54,0x55,0x56,0x57, // 0x50
	0x58,0x59,0x5a,0x5b,0x5c,0x5d,0x5e,0x5f,
	0x60,0x41,0x42,0x43,0x44,0x45,0x46,0x47, // 0x60
	0x48,0x49,0x4a,0x4b,0x4c,0x4d,0x4e,0x4f,
	0x50,0x51,0x52,0x53,0x54,0x55,0x56,0x57, // 0x70
	0x58,0x59,0x5a,0x7b,0x7c,0x7d,0x7e,0x7f,
	0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87, // 0x80
	0x88,0x89,0x53,0x8b,0x8c,0x8d,0x5a,0x8f,
	0x90,0x91,0x92,0x93,0x94,0x95,0x96,0x97, // 0x90
	0x98,0x99,0x53,0x9b,0x8c,0x9d,0x5a,0x59,
	0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7, // 0xa0 
	0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,
	0xb0,0xb1,0xb2,0xb3,0xb4,0xb5,0xb6,0xb7, // 0xb0
	0xb8,0xb9,0xba,0xbb,0xbc,0xbd,0xbe,0xbf,
	0x41,0x41,0x41,0x41,0x41,0x41,0x41,0x43, // 0xc0
	0x45,0x45,0x45,0x45,0x49,0x49,0x49,0x49,
	0xd0,0x4e,0x4f,0x4f,0x4f,0x4f,0x4f,0xd7, // 0xd0
	0x4f,0x55,0x55,0x55,0x55,0x59,0xde,0xdf,
	0x41,0x41,0x41,0x41,0x41,0x41,0x41,0x43, // 0xe0
	0x45,0x45,0x45,0x45,0x49,0x49,0x49,0x49,
	0xd0,0x4e,0x4f,0x4f,0x4f,0x4f,0x4f,0xf7, // 0xf0
	0x4f,0x55,0x55,0x55,0x55,0x59,0xde,0x59
	};

#endif // #ifndef _UNICODE
