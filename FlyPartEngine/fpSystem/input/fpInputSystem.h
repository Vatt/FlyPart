/*
 * fpInputSystem.h
 *
 *  Created on: 22 февр. 2014 г.
 *      Author: gamover
 */

#ifndef FPINPUTSYSTEM_H_
#define FPINPUTSYSTEM_H_
#include "fpKeyboard.hpp"
#include "../../fpCommon/fpFunction.h"
typedef enum InputType
{
    KeyboardAndMouse,
    Gamepad,
    Joystick
};
/*впилить абстракт клас для девайсов инпута, поставим его в майн и будем ждать
 * ввода бог пойми откуда
 * да и вообще впилить интерфейсы устройств
 * и интерфейсы модулей движка
*/
class fpInputSystem
{
private:
    fpKeyboard* _keyboard;
    InputType _inputType;
    void WaitInputFromController();

public:
    fpInputSystem(InputType inT);
    void setAdapter(fpCallbackInterface<void, void>* adapter);
	~fpInputSystem();
    void keyBind();
};

#endif /* FPINPUTSYSTEM_H_ */
