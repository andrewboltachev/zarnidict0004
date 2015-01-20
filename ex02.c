#include <wchar.h>
#include <string.h>

int main() {
  mbstate_t mbs;
  memset(&mbs, 0, sizeof(mbs)); // initialize 

  mbrlen (NULL,0,&mbs);
}
