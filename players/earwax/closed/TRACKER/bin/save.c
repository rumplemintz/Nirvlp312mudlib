/* *************************************************************************
 * Save
 *
 * - Earwax 09/14/03
 *
 *
 * *************************************************************************
*/

#include "../defs.h"

status main(string arg) {

  present(TRACKER_ID,this_player())->save_info(1);
  return 0;
}
