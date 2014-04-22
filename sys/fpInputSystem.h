/*
 * fpInputSystem.h
 *
 *  Created on: 22 февр. 2014 г.
 *      Author: gamover
 */

#ifndef FPINPUTSYSTEM_H_
#define FPINPUTSYSTEM_H_
#include "input/fpKeyboard.h"
class fpInputSystem
{
private:
    fpKeyboard* _keyboard;
public:
	fpInputSystem();
	~fpInputSystem();
    void keyBind(char keyName);
};

#endif /* FPINPUTSYSTEM_H_ */
