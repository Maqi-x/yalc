/*
  exit-code:
    1
  stderr:
    Assertion failed
*/

#include <assert.h>

static_assert(1, "Yay!");

int main() {
    assert(0);
}
