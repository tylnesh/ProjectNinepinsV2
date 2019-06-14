#ifndef GLOBAL_H
#define GLOBAL_H

#define SERIALTIMER 3000
#define DUEWIRE 1
#define DISPLAYWIRE 3

extern bool gaffeSwitch;
extern bool gaffeConfirmed;
extern bool gaffeRunning;
extern bool changer;
extern bool changerRunning;

extern bool ardListening;

extern int currentRound;

extern int lastPoints;

extern int cmdGF;
extern int cmdOutGF;

extern int pointsGF;
extern int pointsOutGF;
extern int pointsTmp;

extern int roundsGF;
extern int roundsOutGF;


extern int scoreGF;
extern int scoreOutGF;
extern int scoreTmp;


extern bool pinsGF[9];
extern bool pinsOutGF[9];
extern bool pinsTmp[9];

extern bool isPartial;

enum commands : int {
    FULLGAME = 24,
    PARTIALGAME = 25,
    CHANGEOK = 101,
    CHANGECANCEL = 102,
    CHANGE = 200,
    SETTINGPINS = 3,
    ENDGAME = 100
};





#endif // GLOBAL_H
