#include "main.h"

/*
* Adapted from hmac.c (HMAC-MD5) for use by SHA1.
* by <mcr@sandelman.ottawa.on.ca>. Test cases from RFC2202.
*
*/

/*
** Function: hmac_sha1
*/

void lrad_hmac_sha1(const unsigned char *text, int text_len, const unsigned char *key, int key_len, unsigned char *digest)
{
	sha1_context context;

	unsigned char k_ipad[65] = { 0 };
	unsigned char k_opad[65] = { 0 };
	unsigned char tk[20] = { 0 };

	int i = 0;
	/* if key is longer than 64 bytes reset it to key=SHA1(key) */
	if (key_len > 64) {

		sha1_context tctx;

		sha1_starts(&tctx);
		sha1_update(&tctx, (uint8*)key, key_len);
		sha1_finish(&tctx, tk);

		key = tk;
		key_len = 20;
	}


	memset(k_ipad, 0, sizeof(k_ipad));
	memset(k_opad, 0, sizeof(k_opad));
	memcpy(k_ipad, key, key_len);
	memcpy(k_opad, key, key_len);

	for (i = 0; i < 64; i++) {
		k_ipad[i] ^= 0x36;
		k_opad[i] ^= 0x5c;
	}

	sha1_starts(&context);

	sha1_update(&context, k_ipad, 64);
	sha1_update(&context, (uint8*)text, text_len);
	sha1_finish(&context, digest);


	sha1_starts(&context);

	sha1_update(&context, k_opad, 64);
	sha1_update(&context, digest, 20);

	sha1_finish(&context, digest);

}

