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


enum commands : uint8_t {
    FULL_GAME = 24,
    PARTIAL_GAME = 25,
    CHANGE_OK = 101,
    CHANGE_CANCEL = 102,
    CHANGE = 200,
    SETTING_PINS = 3,
    END_GAME = 100,
    GAFFE_CONFIRMED = 206,
    GAFFE_CANCELED = 205,
    CHECKSUM_NOT_MATCH = 6,
    FULL_GAME_MSG = 1,
    CHECK_GAFFE = 201,
    ACKNOWLEDGED = 203,
    REQ_REPEAT = 204

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






enum class Game: uint8_t {FULL_GAME = 1, PARTIAL_GAME = 2};

extern Game currentGameType;





#endif // GLOBAL_H
