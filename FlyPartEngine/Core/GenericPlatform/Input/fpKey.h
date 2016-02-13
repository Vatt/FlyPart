#ifndef FPKEY_H
#define FPKEY_H

typedef enum struct keyState
{
    UP,
    DOWN
};
typedef enum struct keyMode
{
    SHIFT,
    ALT,
    CTRL
};


struct fpKey
{

     char _keyName;
    /*system key code*/
    unsigned int _scanCode;
    keyMode  _mode;
    keyState _state;
    fpKey(unsigned int code,  keyState state)
        :_scanCode(code), _state(state){}
};

#endif // FPKEY_H
