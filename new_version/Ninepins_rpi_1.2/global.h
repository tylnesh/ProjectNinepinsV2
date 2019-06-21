#ifndef GLOBAL_H
#define GLOBAL_H

#define SERIALTIMER 1000
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
    CHANGE_OK = 41,
    CHANGE_CANCEL = 42,
    CHANGE = 40,
    SETTING_PINS = 3,
    END_GAME = 50,
    GAFFE_CONFIRMED = 66,
    GAFFE_CANCELED = 65,
    CHECKSUM_NOT_MATCH = 6,
    FULL_GAME_MSG = 1,
    CHECK_GAFFE = 61,
    ACKNOWLEDGED = 43,
    REQ_REPEAT = 44,
    KNOT_CMD = 70

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

    uint16_t calculateChecksum() {
        return wire + cmd + getPoints() + rounds + score;
    }

};

enum class Game: uint8_t {FULL_GAME = 1, PARTIAL_GAME = 2};

extern Game currentGameType;





#endif // GLOBAL_H
