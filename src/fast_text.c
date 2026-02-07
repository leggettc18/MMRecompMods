#include "modding.h"
#include "global.h"
#include "recomputils.h"
#include "recompconfig.h"

MessageContext* msgCtx;

RECOMP_HOOK("Message_DrawTextNES") void draw_text_nes_hook(PlayState* play, Gfx** gfxP, u16 textDrawPos) {
    msgCtx = &play->msgCtx;
}

RECOMP_HOOK_RETURN("Message_DrawTextNES") void draw_text_nes_return_hook() {
    msgCtx->textDelay = msgCtx->textDelay / 2;
}


