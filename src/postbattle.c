#include "core.h"
#include "ui.h"
#include "battle.h"
#include "rpg.h"
#include "hUGEDriver.h"

#define MESSAGE_DELAY   60

BANKREF_EXTERN(gameover)
extern hUGESong_t gameover;
BANKREF_EXTERN(victory_song)
extern hUGESong_t victory_song;

typedef struct Notification {
    const char* msg;
    const char* subject;
} Notification;

uint8_t messageTimer, messageRowIndex;
Notification notifications[8];
uint8_t notificationsSize, shownNotificationIndex;

inline void pushNotification(const char* msg, const char* subject) {
    uint8_t i = notificationsSize++;
    notifications[i].msg = msg;
    notifications[i].subject = subject;
}

void stateInitPostBattle() {
    // ASSUME WE JUST CAME FROM THE BATTLE STATE AND ALL UI ASSETS ARE LOADED
    
    HIDE_SPRITES;
    
    messageTimer = MESSAGE_DELAY;
    messageRowIndex = 8;

    notificationsSize = 0;
    shownNotificationIndex = 0;
    
    render9slice(3, 3, 14, 11);
    fill_bkg_rect(4, 4, 12, 9, 0);

    if (battleOutcome == OUTCOME_DEFEAT) {
        startMusic(&gameover, BANK(gameover));
        renderText(8, 4, "Defeat...");
        return;
    }

    if (battleOutcome == OUTCOME_ESCAPED) {
        renderText(8, 4, "Escaped!");
    } else if (battleOutcome == OUTCOME_VICTORY) {
        startMusic(&victory_song, BANK(victory_song));
        renderText(8, 4, "Victory!");
    }
    renderText(5, 6, "XP Gained:"); renderNumber(13, 6, xpGained);

    for (uint8_t i = 0; i < 4; i++) {
        if (awardXp(&party[i], xpGained)) {
            pushNotification("Level up!", party[i].name);
            for (uint8_t j = 0; j < 4; j++) {
                if (party[i].learnedSkills[j].lvlRequired == party[i].lvl) {
                    pushNotification("New skill!", skills[party[i].skills[j]].name);
                }
            }
        }
    }
}

void stateUpdatePostBattle() {
    if (shownNotificationIndex < notificationsSize) {
        if (--messageTimer == 0) {
            renderText(5, messageRowIndex, notifications[shownNotificationIndex].msg);
            renderText(11, messageRowIndex, notifications[shownNotificationIndex].subject);
            shownNotificationIndex++;
            messageRowIndex++;
            messageTimer = MESSAGE_DELAY;
        }
    } else {
        if (KEYPRESSED(J_A)) {
            if (battleOutcome == OUTCOME_DEFEAT)
                queueStateSwitch(STATE_TITLE);
            else
                queueStateSwitch(STATE_EXPLORE);
        }
    }
}

