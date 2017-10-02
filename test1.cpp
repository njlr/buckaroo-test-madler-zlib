#include <gtest/gtest.h>
#include <zlib.h>

TEST(zlib, basics) {

  char a[50] = "Hello Hello Hello Hello Hello Hello!";

  // placeholder for the compressed (deflated) version of "a"
  char b[50];

  // placeholder for the UNcompressed (inflated) version of "b"
  char c[50];

  // STEP 1.
  // deflate a into b. (that is, compress a into b)

  // zlib struct
  z_stream defstream;

  defstream.zalloc = Z_NULL;
  defstream.zfree = Z_NULL;
  defstream.opaque = Z_NULL;

  // setup "a" as the input and "b" as the compressed output
  defstream.avail_in = (uInt)strlen(a)+1; // size of input, string + terminator
  defstream.next_in = (Bytef *)a; // input char array
  defstream.avail_out = (uInt)sizeof(b); // size of output
  defstream.next_out = (Bytef *)b; // output char array

  // the actual compression work.
  deflateInit(&defstream, Z_BEST_COMPRESSION);
  deflate(&defstream, Z_FINISH);
  deflateEnd(&defstream);

  // STEP 2.
  // inflate b into c
  // zlib struct
  z_stream infstream;

  infstream.zalloc = Z_NULL;
  infstream.zfree = Z_NULL;
  infstream.opaque = Z_NULL;

  // setup "b" as the input and "c" as the compressed output
  infstream.avail_in = (uInt)((char*)defstream.next_out - b); // size of input
  infstream.next_in = (Bytef *)b; // input char array
  infstream.avail_out = (uInt)sizeof(c); // size of output
  infstream.next_out = (Bytef *)c; // output char array

  // the actual DE-compression work.
  inflateInit(&infstream);
  inflate(&infstream, Z_NO_FLUSH);
  inflateEnd(&infstream);

  // make sure uncompressed is exactly equal to original.
  EXPECT_TRUE(strcmp(a, c) == 0);
}
