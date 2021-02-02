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

#include <stdio.h>
#include <string.h>
#include "qwiic_i2c.h"
#include "qwiic_joystick.h"

Qwiic_I2C qwiic;

//Constructor
JOYSTICK::JOYSTICK(uint8_t deviceAddress)
{
    _deviceAddress = deviceAddress;

}

//Initializes the I2C connection
//Returns false if board is not detected
bool JOYSTICK::begin()
{
  
    // init I2C.

    if(!qwiic.init()){
        printf("Error: I2C subsystem failed to initialize.");
        return false;
    }

    return isConnected();

}

//Returns true if I2C device ack's
bool JOYSTICK::isConnected()
{
    return  qwiic.pingDevice(_deviceAddress);

}

//Change the I2C address of this address to newAddress
bool JOYSTICK::setI2CAddress(uint8_t newAddress)
{
    if (8 > newAddress || newAddress > 119)
        return false; // out of range

    int rc;

    rc = qwiic.writeRegister(_deviceAddress, JOYSTICK_I2C_LOCK, 0x13);
    if(rc == QWIIC_ERROR_GENERIC)
        return false; // error

    rc = qwiic.writeRegister(_deviceAddress, JOYSTICK_CHANGE_ADDRESS, newAddress);
    if(rc == QWIIC_ERROR_GENERIC)
        return false; // error

    //Once the address is changed, we need to change it in the library
    uint8_t oldAddress = _deviceAddress;
    _deviceAddress = newAddress;

    if(!isConnected()){
        // failed to switch address. 
        _deviceAddress = oldAddress;
        return false;
    }
    return true;
}

//Returns the 10-bit ADC value of the joystick horizontal position
uint16_t JOYSTICK::getHorizontal()
{
    uint16_t X_MSB =  qwiic.readRegister(_deviceAddress, JOYSTICK_X_MSB);
    uint16_t X_LSB =  qwiic.readRegister(_deviceAddress, JOYSTICK_X_LSB);

    return ((X_MSB<<8) | X_LSB)>>6;
}

//Returns the 10-bit ADC value of the joystick vertical position
uint16_t JOYSTICK::getVertical()
{
    uint16_t Y_MSB =  qwiic.readRegister(_deviceAddress, JOYSTICK_Y_MSB);
    uint16_t Y_LSB =  qwiic.readRegister(_deviceAddress, JOYSTICK_Y_LSB);

    return ((Y_MSB<<8) | Y_LSB)>>6;
}

//Returns 0 button is currently being pressed
uint8_t JOYSTICK::getButton()
{
    return qwiic.readRegister(_deviceAddress, JOYSTICK_BUTTON);

}

//Returns 1 if button was pressed between reads of .getButton() or .checkButton()
//the register is then cleared after read.
uint8_t JOYSTICK::checkButton()
{
    uint8_t status =  qwiic.readRegister(_deviceAddress, JOYSTICK_STATUS);
  
    qwiic.writeRegister(_deviceAddress, JOYSTICK_STATUS, 0x00); //We've read this status bit, now clear it

    return status;
}

//Returns a string of the firmware version number
void JOYSTICK::getVersion(char *pString, uint8_t length)
{
    uint8_t Major =  qwiic.readRegister(_deviceAddress, JOYSTICK_VERSION1);
    uint8_t Minor =  qwiic.readRegister(_deviceAddress, JOYSTICK_VERSION2);

    snprintf(pString, length, "v%d.%d", Major, Minor);

}
