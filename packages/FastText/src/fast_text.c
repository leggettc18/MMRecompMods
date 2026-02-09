#include "modding.h"
#include "global.h"
#include "recomputils.h"
#include "recompconfig.h"

typedef enum {
    TEXT_SPEED_2X,
    TEXT_SPEED_4X,
    TEXT_SPEED_8X,
    TEXT_SPEED_16X,
} TextSpeed;

RECOMP_HOOK("Message_Update") void message_update_hook(PlayState* play) {
    MessageContext* msgCtx = &play->msgCtx;
    unsigned int textSpeedMod = 0;
    switch(recomp_get_config_u32("text_scroll_mult")) {
        case TEXT_SPEED_2X:
            textSpeedMod = 1;
            break;
        case TEXT_SPEED_4X:
            textSpeedMod = 3;
            break;
        case TEXT_SPEED_8X:
            textSpeedMod = 7;
            break;
        case TEXT_SPEED_16X:
            textSpeedMod = 15;
            break;
    }
    if (msgCtx->msgMode == MSGMODE_TEXT_DISPLAYING) {
        msgCtx->textDrawPos = MIN(msgCtx->textDrawPos + textSpeedMod, msgCtx->decodedTextLen+1);
    }
}

// RECOMP_HOOK_RETURN("Message_DrawText") void draw_text_return_hook() {
//     msgCtx->textDelayTimer = MAX(msgCtx->textDelayTimer - 3, 0);
//     msgCtx->textDrawPos = MIN(msgCtx->textDrawPos + 2, msgCtx->decodedTextLen);
// }


