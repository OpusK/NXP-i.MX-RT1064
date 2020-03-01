/***********************************************************************************************************************
 * This file was generated by the MCUXpresso Config Tools. Any manual edits made to this file
 * will be overwritten if the respective MCUXpresso Config Tools is used to update this file.
 **********************************************************************************************************************/

/* clang-format off */
/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
!!GlobalInfo
product: Peripherals v7.0
processor: MIMXRT1064xxxxA
package_id: MIMXRT1064DVL6A
mcu_data: ksdk2_0
processor_version: 7.0.1
functionalGroups:
- name: BOARD_InitPeripherals
  UUID: fdad6ce7-ae3e-4d4f-95b5-ddfe438aec59
  called_from_default_init: true
  selectedCore: core0
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/

/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
component:
- type: 'system'
- type_id: 'system_54b53072540eeeb8f8e9343e71f28176'
- global_system_definitions: []
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/

/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
component:
- type: 'msg'
- type_id: 'msg_6e2baaf3b97dbeef01c0043275f9a0e7'
- global_messages: []
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/
/* clang-format on */

/***********************************************************************************************************************
 * Included files
 **********************************************************************************************************************/
#include "peripherals.h"

/***********************************************************************************************************************
 * BOARD_InitPeripherals functional group
 **********************************************************************************************************************/
/***********************************************************************************************************************
 * LPUART1 initialization code
 **********************************************************************************************************************/
/* clang-format off */
/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
instance:
- name: 'LPUART1'
- type: 'lpuart'
- mode: 'interrupts'
- custom_name_enabled: 'false'
- type_id: 'lpuart_54a65a580e3462acdbacefd5299e0cac'
- functional_group: 'BOARD_InitPeripherals'
- peripheral: 'LPUART1'
- config_sets:
  - lpuartConfig_t:
    - lpuartConfig:
      - clockSource: 'LpuartClock'
      - lpuartSrcClkFreq: 'BOARD_BootClockRUN'
      - baudRate_Bps: '115200'
      - parityMode: 'kLPUART_ParityDisabled'
      - dataBitsCount: 'kLPUART_EightDataBits'
      - isMsb: 'false'
      - stopBitCount: 'kLPUART_OneStopBit'
      - txFifoWatermark: '0'
      - rxFifoWatermark: '0'
      - enableRxRTS: 'false'
      - enableTxCTS: 'false'
      - txCtsSource: 'kLPUART_CtsSourcePin'
      - txCtsConfig: 'kLPUART_CtsSampleAtStart'
      - rxIdleType: 'kLPUART_IdleTypeStartBit'
      - rxIdleConfig: 'kLPUART_IdleCharacter1'
      - enableTx: 'true'
      - enableRx: 'true'
  - interruptsCfg:
    - interrupts: 'kLPUART_RxDataRegFullInterruptEnable kLPUART_RxOverrunInterruptEnable'
    - interrupt_vectors:
      - enable_rx_tx_irq: 'true'
      - interrupt_rx_tx:
        - IRQn: 'LPUART1_IRQn'
        - enable_priority: 'false'
        - priority: '0'
        - enable_custom_name: 'false'
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/
/* clang-format on */
const lpuart_config_t LPUART1_config = {
  .baudRate_Bps = 115200,
  .parityMode = kLPUART_ParityDisabled,
  .dataBitsCount = kLPUART_EightDataBits,
  .isMsb = false,
  .stopBitCount = kLPUART_OneStopBit,
  .txFifoWatermark = 0,
  .rxFifoWatermark = 0,
  .enableRxRTS = false,
  .enableTxCTS = false,
  .txCtsSource = kLPUART_CtsSourcePin,
  .txCtsConfig = kLPUART_CtsSampleAtStart,
  .rxIdleType = kLPUART_IdleTypeStartBit,
  .rxIdleConfig = kLPUART_IdleCharacter1,
  .enableTx = true,
  .enableRx = true
};

void LPUART1_init(void) {
  LPUART_Init(LPUART1_PERIPHERAL, &LPUART1_config, LPUART1_CLOCK_SOURCE);
  LPUART_EnableInterrupts(LPUART1_PERIPHERAL, kLPUART_RxDataRegFullInterruptEnable | kLPUART_RxOverrunInterruptEnable);
  /* Enable interrupt LPUART1_IRQn request in the NVIC */
  EnableIRQ(LPUART1_SERIAL_RX_TX_IRQN);
}

/***********************************************************************************************************************
 * USB1 initialization code
 **********************************************************************************************************************/
/* clang-format off */
/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
instance:
- name: 'USB1'
- type: 'usb'
- mode: 'device'
- custom_name_enabled: 'false'
- type_id: 'usb_f20ee74266c7aae05b4d32d0517001b5'
- functional_group: 'BOARD_InitPeripherals'
- peripheral: 'USB1'
- config_sets:
  - deviceSetting:
    - vendor_id: '0x1FC9'
    - product_id: '0x0094'
    - manufacturer_string: 'NXP'
    - product_string: 'VCOM'
    - self_powered: 'true'
    - max_power: '100'
    - interfaces:
      - 0:
        - interface_class: 'kClassCic'
        - setting_cic:
          - interface_name: 'CIC VCOM'
          - implementation: 'kImplementationCicVcom'
          - subclass: 'kSubclassAcm'
          - protocol: 'kProtocolNone'
          - endpoints_settings:
            - 0:
              - setting_name: 'Default'
              - endpoints:
                - 0:
                  - direction: 'kIn'
                  - transfer_type: 'kInterrupt'
                  - synchronization: 'kNoSynchronization'
                  - usage: 'kData'
                  - max_packet_size_fs: 'k16'
                  - polling_interval_fs: '8'
                  - max_packet_size_hs: 'k16'
                  - polling_interval_hs: '7'
                  - bRefresh: '0'
                  - bSynchAddress: 'NoSynchronization'
          - data_interface_count: '1'
          - quick_selection: 'QS_INTERFACE_CIC_VCOM'
      - 1:
        - interface_class: 'kClassDic'
        - setting_dic:
          - interface_name: 'DIC VCOM'
          - implementation: 'kImplementationDicVcom'
          - subclass: 'kSubclassNone'
          - protocol: 'kProtocolNone'
          - endpoints_settings:
            - 0:
              - setting_name: 'Default'
              - endpoints:
                - 0:
                  - direction: 'kIn'
                  - transfer_type: 'kBulk'
                  - synchronization: 'kNoSynchronization'
                  - usage: 'kData'
                  - max_packet_size_fs: 'k64'
                  - polling_interval_fs: '0'
                  - max_packet_size_hs: 'k512'
                  - polling_interval_hs: '0'
                  - bRefresh: '0'
                  - bSynchAddress: 'NoSynchronization'
                - 1:
                  - direction: 'kOut'
                  - transfer_type: 'kBulk'
                  - synchronization: 'kNoSynchronization'
                  - usage: 'kData'
                  - max_packet_size_fs: 'k64'
                  - polling_interval_fs: '0'
                  - max_packet_size_hs: 'k512'
                  - polling_interval_hs: '0'
                  - bRefresh: '0'
                  - bSynchAddress: 'NoSynchronization'
          - quick_selection: 'QS_INTERFACE_DIC_VCOM'
    - quick_selection: 'QS_DEVICE_CDC_VCOM'
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/
/* clang-format on */

void USB1_init(void) {
  USB_DeviceApplicationInit();
}

/***********************************************************************************************************************
 * Initialization functions
 **********************************************************************************************************************/
void BOARD_InitPeripherals(void)
{
  /* Initialize components */
  LPUART1_init();
  USB1_init();
}

/***********************************************************************************************************************
 * BOARD_InitBootPeripherals function
 **********************************************************************************************************************/
void BOARD_InitBootPeripherals(void)
{
  BOARD_InitPeripherals();
}
