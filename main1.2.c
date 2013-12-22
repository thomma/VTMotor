/*
 * This file is part of VTMotor (I2C motor driver)
 *
 * Copyright 2012 Vitaly Perov <vitperov@gmail.com>
 *
 * VTMotor is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with VTMotor.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <avr/io.h>

#include "motor.h"
#include "external/SMBSlave.h"

#define DRV_SW_PORT   	PORTC

#define DRV_SW0_PIN    	0b00000001
#define DRV_SW1_PIN    	0b00000010
#define DRV_SW2_PIN    	0b00000100
#define DRV_SW3_PIN    	0b00001000

#define DRV_SW_DDR     	DDRC

/* TIMER */
inline void conf_TMR0()
{
  /* set clock source f_t0 = f_io/8 = 1 MHz */
  TCCR0 = _BV(CS01);

  TIMSK |= _BV(TOIE0); /* Enable TMR0 interrupt */
}

inline void configure()
{  
  /* Set switch pins to input */
  DRV_SW_DDR  |= (DRV_SW0_PIN|DRV_SW1_PIN|DRV_SW2_PIN|DRV_SW3_PIN);  
  
  /* Set switch pins to high impedance */
  DRV_SW_PORT &= ~(DRV_SW0_PIN|DRV_SW1_PIN|DRV_SW2_PIN|DRV_SW3_PIN);
  
  uint8_t addr = 0b00001111 & DRV_SW_PORT;
  
  // Initialize SMBus
  SMBusInit(addr);
  SMBEnable();

  conf_TMR0();
  conf_motors();

  SREG |= _BV(7); /* Enable interrupts */
}

int main(void)
{
  configure();
  while (1);
  return 0;
}
