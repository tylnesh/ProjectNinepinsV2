#ifndef GLOBAL_H
#define GLOBAL_H

#define SERIALTIMER 3000
#define DUEWIRE 1
#define DISPLAYWIRE 3

#include <stdint.h>
#include <array>

extern bool gaffeSwitch;
extern bool gaffeConfirmed;
extern bool gaffeRunning;
extern bool changer;
extern bool changerRunning;

extern bool ardListening;

extern int currentRound;

extern uint8_t lastPoints;

extern int cmdGF;
//extern int cmdOutGF;

//extern int pointsGF;
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

enum commands : uint8_t {
    FULLGAME = 24,
    PARTIALGAME = 25,
    CHANGEOK = 101,
    CHANGECANCEL = 102,
    CHANGE = 200,
    SETTINGPINS = 3,
    ENDGAME = 100,
    GAFFECONFIRMED = 206,
    GAFFECANCELED = 205,
    CHECKSUMNOTMATCH = 6,
    FULLGAMEMSG = 1,
    CHECKGAFFE = 201,
    ACKNOWLEDGED = 203,
    REQREPEAT = 204

};


static constexpr size_t PINS = 9;

static constexpr int statusLength = PINS + 7;


union Status {
    struct {
        uint8_t wire;
        uint8_t cmd;
        std::array<uint8_t, PINS> pins;
        uint8_t rounds;
        uint16_t score;
        uint16_t checksum;
    };
    std::array<uint8_t, statusLength> bytes;
    uint8_t getPoints()
    {
        uint8_t points = 0;
        for (size_t i = 0; i < PINS; i++) if (pins[i]) points++;
        return points;
    }
};






enum class Game: uint8_t {FULLGAME = 1, PARTIALGAME = 2};

Game currentGameType;





#endif // GLOBAL_H
