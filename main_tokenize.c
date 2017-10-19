/*This is all on Jed
*/

#include "value.h"
#include "talloc.h"
#include "linkedlist.h" /*Not sure if we need this*/
#include "tokenizer.h"

int main(void) {
   Value *list = tokenize();
   displayTokens(list);
   tfree();
   return 0;
}
