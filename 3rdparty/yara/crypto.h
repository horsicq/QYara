/*
Copyright (c) 2017. The YARA Authors. All Rights Reserved.

Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice,
this list of conditions and the following disclaimer in the documentation and/or
other materials provided with the distribution.

3. Neither the name of the copyright holder nor the names of its contributors
may be used to endorse or promote products derived from this software without
specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef YR_CRYPTO_H
#define YR_CRYPTO_H

#define YR_MD5_LEN    16
#define YR_SHA1_LEN   20
#define YR_SHA256_LEN 32

//#if defined(HAVE_LIBCRYPTO)
//#include <openssl/crypto.h>
//#include <openssl/md5.h>
//#include <openssl/sha.h>

#define MD5_LONG unsigned int

#define MD5_CBLOCK 64
#define MD5_LBLOCK (MD5_CBLOCK/4)

typedef struct MD5state_st {
    MD5_LONG A, B, C, D;
    MD5_LONG Nl, Nh;
    MD5_LONG data[MD5_LBLOCK];
    unsigned int num;
} MD5_CTX;

# define SHA_LONG unsigned int

# define SHA_LBLOCK 16
# define SHA_CBLOCK (SHA_LBLOCK*4)/* SHA treats input data as a
                                         * contiguous array of 32 bit wide
                                         * big-endian values. */
# define SHA_LAST_BLOCK (SHA_CBLOCK-8)

typedef struct SHAstate_st {
    SHA_LONG h0, h1, h2, h3, h4;
    SHA_LONG Nl, Nh;
    SHA_LONG data[SHA_LBLOCK];
    unsigned int num;
} SHA_CTX;

#  define SHA256_CBLOCK   (SHA_LBLOCK*4)/* SHA-256 treats input data as a
                                        * contiguous array of 32 bit wide
                                        * big-endian values. */

typedef struct SHA256state_st {
    SHA_LONG h[8];
    SHA_LONG Nl, Nh;
    SHA_LONG data[SHA_LBLOCK];
    unsigned int num, md_len;
} SHA256_CTX;

typedef MD5_CTX yr_md5_ctx;
typedef SHA_CTX yr_sha1_ctx;
typedef SHA256_CTX yr_sha256_ctx;

#define yr_md5_init(ctx)              MD5_Init(ctx)
#define yr_md5_update(ctx, data, len) MD5_Update(ctx, data, len)
#define yr_md5_final(digest, ctx)     MD5_Final(digest, ctx)

#define yr_sha1_init(ctx)              SHA1_Init(ctx)
#define yr_sha1_update(ctx, data, len) SHA1_Update(ctx, data, len)
#define yr_sha1_final(digest, ctx)     SHA1_Final(digest, ctx)

#define yr_sha256_init(ctx)              SHA256_Init(ctx)
#define yr_sha256_update(ctx, data, len) SHA256_Update(ctx, data, len)
#define yr_sha256_final(digest, ctx)     SHA256_Final(digest, ctx)

#endif
