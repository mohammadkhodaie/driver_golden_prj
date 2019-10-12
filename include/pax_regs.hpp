//
// Copyright 2010-2012 Ettus Research LLC
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//

#ifndef INCLUDED_USRP2_REGS_HPP
#define INCLUDED_USRP2_REGS_HPP

////////////////////////////////////////////////////////////////////////
// Define slave bases
////////////////////////////////////////////////////////////////////////
#define ROUTER_RAM_BASE     0x04000
#define SPI_BASE            0x05000
#define I2C_BASE            0x05400
#define GPIO_BASE           0x05800
#define READBACK_BASE       0x05C00
#define ETH_BASE            0x06000
#define SETTING_REGS_BASE   0x07000
#define PIC_BASE            0x08000
#define UART_BASE           0x08800
#define ATR_BASE            0x08C00
#define AD9361_BASE(x) (0x40000+x<<16)
////////////////////////////////////////////////////////////////////////
// Setting register offsets
////////////////////////////////////////////////////////////////////////
#define SR_MISC       0   // 7 regs
#define SR_SIMTIMER   8   // 2
#define SR_TIME64    10   // 6
#define SR_BUF_POOL  16   // 4

#define SR_ADC_CLK_EN  24   // 1
#define SR_SYNC_CHECK_LEN 25 //1
#define SR_RX_DELAY  26   // 1



#define SR_MISC       0   // 7 regs
#define SR_SIMTIMER   8   // 2
#define SR_TIME64    10   // 6
#define SR_BUF_POOL  16   // 4
#define SR_TX_DSP_PORT 64
#define SR_RX_FRONT  24   // 5
#define SR_RX_CTRL0  512   // 9
#define SR_RX_CTRL(x) (SR_RX_CTRL0+(x*24))
#define SR_RX_DSP0   528   // 7
#define SR_RX_DSP(x) (SR_RX_DSP0+(x*24))

#define SR_TX_FRONT 128   // ?
#define SR_TX_CTRL0  256   // 6
#define SR_TX_CTRL(x) (SR_TX_CTRL0+(x*16))

#define SR_TX_DSP0   264   // 5
#define SR_TX_DSP(x) (SR_TX_DSP0+(x*16))



#define SR_UDP_SM   0   // 64



#define SR_GPIO     104
#define SR_SPI_CORE  20   // 3

#define SR_CAL_SEL 964
#define SR_COR_CONFIG 26
#define SR_COR_LEN 25


#define U2_REG_SR_ADDR(sr) (SETTING_REGS_BASE + (4 * (sr)))

#define U2_REG_GPIO_ADDR(addr) (GPIO_BASE + ( 4 * addr))
#define U2_REG_ROUTER_CTRL_PORTS U2_REG_SR_ADDR(SR_BUF_POOL) + 8


#define U2_REG_ROUTER_TX_PORT(x) (U2_REG_SR_ADDR(64) + 4*x)
#define SR_MCS 127

#define SR_RX_SW 961
#define SR_LO_SEL 963
#define SR_LO_EN 968

#define PAX8_SR_RX_CNT_PORT_BASE 970
#define PAX8_SR_RX_PORT_ADDR_WHICH_IC(x) PAX8_SR_RX_CNT_PORT_BASE + x


#define SR_RX_PORT_B 971
#define SR_RX_PORT_C 972
#define SR_RX_PORT_D 973

#define SR_SNAPSHOT_CALIBRATION 1010
#define SR_REG_PHASE_DELAY_BASE 1011
#define SR_PHASE_DELAY_VALUE(x) (SR_REG_PHASE_DELAY_BASE + x)
#define SR_CALIBRATION_RST_FIFO 1019



#define SR_TX_SW 962
#define SR_FILT_SW 1021


/////////////////////////////////////////////////
// SPI Slave Constants
////////////////////////////////////////////////
// Masks for controlling different peripherals
#define SPI_SS_AD9510    1
#define SPI_SS_AD9777    2
#define SPI_SS_RX_DAC    4
#define SPI_SS_RX_ADC    8
#define SPI_SS_RX_DB    16
#define SPI_SS_TX_DAC   32
#define SPI_SS_TX_ADC   64
#define SPI_SS_TX_DB   128
#define SPI_SS_ADS62P44 256 //for usrp2p

/////////////////////////////////////////////////
// Misc Control
////////////////////////////////////////////////
#define U2_REG_MISC_CTRL_CLOCK U2_REG_SR_ADDR(0)
#define U2_REG_MISC_CTRL_SERDES U2_REG_SR_ADDR(1)
#define U2_REG_MISC_CTRL_ADC U2_REG_SR_ADDR(2)
#define U2_REG_MISC_CTRL_LEDS U2_REG_SR_ADDR(3)
#define U2_REG_MISC_CTRL_PHY U2_REG_SR_ADDR(4)
#define U2_REG_MISC_CTRL_DBG_MUX U2_REG_SR_ADDR(5)
#define U2_REG_MISC_CTRL_RAM_PAGE U2_REG_SR_ADDR(6)
#define U2_REG_MISC_CTRL_FLUSH_ICACHE U2_REG_SR_ADDR(7)
#define U2_REG_MISC_CTRL_LED_SRC U2_REG_SR_ADDR(8)

#define U2_FLAG_MISC_CTRL_SERDES_ENABLE 8
#define U2_FLAG_MISC_CTRL_SERDES_PRBSEN 4
#define U2_FLAG_MISC_CTRL_SERDES_LOOPEN 2
#define U2_FLAG_MISC_CTRL_SERDES_RXEN   1

#define U2_FLAG_MISC_CTRL_ADC_ON  0x0F
#define U2_FLAG_MISC_CTRL_ADC_OFF 0x00

/////////////////////////////////////////////////
// Readback regs
////////////////////////////////////////////////
#define U2_PHASE_DELAY_Q_VALUE READBACK_BASE + 4*1
#define U2_PHASE_DELAY_I_VALUE READBACK_BASE + 4*2

#define U2_COR_I_LO READBACK_BASE + 4*4
#define U2_COR_I_HI READBACK_BASE + 4*5
#define U2_COR_Q_LO READBACK_BASE + 4*6
#define U2_COR_Q_HI READBACK_BASE + 4*7

#define U2_REG_STATUS READBACK_BASE + 4*8
#define U2_REG_GPIO_RB READBACK_BASE + 4*9
#define U2_REG_TIME64_HI_RB_IMM READBACK_BASE + 4*10
#define U2_REG_TIME64_LO_RB_IMM READBACK_BASE + 4*11
#define U2_REG_COMPAT_NUM_RB READBACK_BASE + 4*12
#define U2_REG_IRQ_RB READBACK_BASE + 4*13
#define U2_REG_TIME64_HI_RB_PPS READBACK_BASE + 4*14
#define U2_REG_TIME64_LO_RB_PPS READBACK_BASE + 4*15


#endif /* INCLUDED_USRP2_REGS_HPP */
