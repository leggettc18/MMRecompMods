#include "modding.h"
#include "global.h"
#include "recomputils.h"
#include "recompconfig.h"

s32 Message_BombersNotebookProcessEventQueue(PlayState* play);

typedef enum {
    TEXT_SPEED_1x,
    TEXT_SPEED_2X,
    TEXT_SPEED_4X,
    TEXT_SPEED_8X,
    TEXT_SPEED_16X,
} TextSpeed;

typedef enum {
    AUTO_ADV_ON,
    AUTO_ADV_OFF,
} AutoAdvanceState;

RECOMP_HOOK("Message_Update") void message_update_hook(PlayState* play) {
    MessageContext* msgCtx = &play->msgCtx;
    Input* input = CONTROLLER1(&play->state);
    PauseContext* pauseCtx = &play->pauseCtx;
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
        default:
            break;
    }

    if (msgCtx->msgMode == MSGMODE_TEXT_DISPLAYING) {
        msgCtx->textDrawPos = MIN(msgCtx->textDrawPos + textSpeedMod, msgCtx->decodedTextLen+1);
        if (CHECK_BTN_ALL(input->cur.button, BTN_B)) {
            msgCtx->textDrawPos = msgCtx->decodedTextLen+1;
        }
    }
}

RECOMP_PATCH bool Message_ShouldAdvance(PlayState* play) {
    MessageContext* msgCtx = &play->msgCtx;
    Input* controller = CONTROLLER1(&play->state);

    if ((msgCtx->textboxEndType == TEXTBOX_ENDTYPE_TWO_CHOICE) ||
        (msgCtx->textboxEndType == TEXTBOX_ENDTYPE_THREE_CHOICE)) {
        if (CHECK_BTN_ALL(controller->press.button, BTN_A)) {
            Audio_PlaySfx(NA_SE_SY_MESSAGE_PASS);
        }
        return CHECK_BTN_ALL(controller->press.button, BTN_A);
    } else {
        if (CHECK_BTN_ALL(controller->press.button, BTN_A) || CHECK_BTN_ALL(controller->press.button, BTN_B) ||
            CHECK_BTN_ALL(controller->press.button, BTN_CUP) || 
            (recomp_get_config_u32("auto_advance_text") == AUTO_ADV_ON && CHECK_BTN_ALL(controller->cur.button, BTN_B))) {
            Audio_PlaySfx(NA_SE_SY_MESSAGE_PASS);
        }
        return CHECK_BTN_ALL(controller->press.button, BTN_A) || CHECK_BTN_ALL(controller->press.button, BTN_B) ||
               CHECK_BTN_ALL(controller->press.button, BTN_CUP) ||  
                (recomp_get_config_u32("auto_advance_text") == AUTO_ADV_ON && CHECK_BTN_ALL(controller->cur.button, BTN_B));
    }
}

RECOMP_PATCH bool Message_ShouldAdvanceSilent(PlayState* play) {
    MessageContext* msgCtx = &play->msgCtx;
    Input* controller = CONTROLLER1(&play->state);

    if ((msgCtx->textboxEndType == TEXTBOX_ENDTYPE_TWO_CHOICE) ||
        (msgCtx->textboxEndType == TEXTBOX_ENDTYPE_THREE_CHOICE)) {
        return CHECK_BTN_ALL(controller->press.button, BTN_A);
    } else {
        return CHECK_BTN_ALL(controller->press.button, BTN_A) || CHECK_BTN_ALL(controller->press.button, BTN_B) ||
               CHECK_BTN_ALL(controller->press.button, BTN_CUP) ||  
                (recomp_get_config_u32("auto_advance_text") == AUTO_ADV_ON && CHECK_BTN_ALL(controller->cur.button, BTN_B));
    }
}


