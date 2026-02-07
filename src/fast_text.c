#include "modding.h"
#include "global.h"
#include "recomputils.h"
#include "recompconfig.h"

RECOMP_HOOK("Message_Update") void message_update_hook(PlayState* play) {
    MessageContext* msgCtx = &play->msgCtx;
    if (msgCtx->msgMode == MSGMODE_TEXT_DISPLAYING) {
        msgCtx->textDrawPos = MIN(msgCtx->textDrawPos + 10, msgCtx->decodedTextLen+1);
    }
}

// RECOMP_HOOK_RETURN("Message_DrawText") void draw_text_return_hook() {
//     msgCtx->textDelayTimer = MAX(msgCtx->textDelayTimer - 3, 0);
//     msgCtx->textDrawPos = MIN(msgCtx->textDrawPos + 2, msgCtx->decodedTextLen);
// }


