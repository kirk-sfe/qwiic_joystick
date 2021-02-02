/*
  This is a library written for the SparkFun Qwiic Joystick
  SparkFun sells these at its website: www.sparkfun.com
  Do you like this library? Help support SparkFun. Buy a board!
  https://www.sparkfun.com/products/15168

  Written by Nathan Seidle @ SparkFun Electronics, November 25th, 2018
  Modified by Wes Furuya @ SparkFun Electronics, February 5th, 2019

  The Qwiic Joystick is a I2C controlled analog joystick

  https://github.com/sparkfun/SparkFun_Qwiic_Joystick_Arduino_Library

  Development environment specifics:
  Arduino IDE 1.8.5

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once 

#include "pico/stdlib.h"

#define QWIIC_JOYSTICK_ADDR 0x20 //7-bit unshifted default I2C Address

//Map to the various registers on the Joystick
enum joystickRegisters {
  JOYSTICK_ID = 0x00,
  JOYSTICK_VERSION1, // 0x01
  JOYSTICK_VERSION2, // 0x02
  JOYSTICK_X_MSB, // 0x03
  JOYSTICK_X_LSB, // 0x04
  JOYSTICK_Y_MSB, // 0x05
  JOYSTICK_Y_LSB, // 0x06
  JOYSTICK_BUTTON, // 0x07
  JOYSTICK_STATUS, // 0x08 //1 - button clicked
  JOYSTICK_I2C_LOCK, // 0x09
  JOYSTICK_CHANGE_ADDRESS, // 0x0A
};

class JOYSTICK {
  public:
    JOYSTICK( uint8_t deviceAddress = QWIIC_JOYSTICK_ADDR);

    bool begin();
    bool isConnected(); //Checks if sensor ack's the I2C request
	
	uint16_t getHorizontal(); //Returns the number of indents the user has turned the knob
  uint16_t getVertical(); //Returns the number of indents the user has turned the knob
		
	uint8_t getButton(); //Returns true if knob has been twisted
	uint8_t checkButton(); //Return true if button is currently pressed.
	
	void getVersion(char* str, uint8_t len); //Returns a two byte Major/Minor version number
	
	bool setI2CAddress(uint8_t newAddress); //Change the I2C address to newAddress (Prints new address over serial)
	
  private:

  	uint8_t _deviceAddress;

};

