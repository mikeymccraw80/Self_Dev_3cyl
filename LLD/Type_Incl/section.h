
#ifdef SECTION_END
#undef SECTION_END
#pragma section
#endif

#ifdef SECTION_FMPLL_REGISTER
#undef SECTION_FMPLL_REGISTER
#pragma section FMPLL_REGISTER address=0xC3F80000
#pragma use_section FMPLL_REGISTER FMPLL
#endif

#ifdef SECTION_EBI_REGISTER
#undef SECTION_EBI_REGISTER
#pragma section EBI_REGISTER address=0xC3F84000
#pragma use_section EBI_REGISTER EBI
#endif

#ifdef SECTION_SIU_REGISTER
#undef SECTION_SIU_REGISTER
#pragma section SIU_REGISTER address=0xC3F90000
#pragma use_section SIU_REGISTER SIU
#endif

#ifdef SECTION_MIOS_REGISTER
#undef SECTION_MIOS_REGISTER
#pragma section MIOS_REGISTER address=0xC3FA0000
#pragma use_section MIOS_REGISTER MIOS
#endif

#ifdef SECTION_TPU_REGISTER
#undef SECTION_TPU_REGISTER
#pragma section TPU_REGISTER address=0xC3FC0000
#pragma use_section TPU_REGISTER TPU
#endif

#ifdef SECTION_XBAR_5634_REGISTER
#undef SECTION_XBAR_5634_REGISTER
#pragma section SECTION_XBAR_5634_REGISTER address=0xFFF04000
#pragma use_section SECTION_XBAR_5634_REGISTER XBAR_5634
#endif

#ifdef SECTION_XBAR_5644_REGISTER
#undef SECTION_XBAR_5644_REGISTER
#pragma section SECTION_XBAR_5644_REGISTER address=0xFFF04000
#pragma use_section SECTION_XBAR_5644_REGISTER XBAR_5644
#endif

#ifdef SECTION_ECSM_REGISTER
#undef SECTION_ECSM_REGISTER
#pragma section ECSM_REGISTER address=0xFFF40000
#pragma use_section ECSM_REGISTER ECSM
#endif

#ifdef SECTION_DMA_A_REGISTER
#undef SECTION_DMA_A_REGISTER
#pragma section DMA_REGISTER address=0xFFF44000
#pragma use_section DMA_REGISTER DMA_A
#endif

#ifdef SECTION_INTC_REGISTER
#undef SECTION_INTC_REGISTER
#pragma section INTC_REGISTER address=0xFFF48000
#pragma use_section INTC_REGISTER INTC
#endif

#ifdef SECTION_QADC_REGISTER
#undef SECTION_QADC_REGISTER
#pragma section QADC_REGISTER address=0xFFF80000
#pragma use_section QADC_REGISTER QADC
#endif

#ifdef SECTION_DSPI_A_REGISTER
#undef SECTION_DSPI_A_REGISTER
#pragma section DSPI_A_REGISTER address=0xFFF90000
#pragma use_section DSPI_A_REGISTER DSPI_A
#endif

#ifdef SECTION_DSPI_B_REGISTER
#undef SECTION_DSPI_B_REGISTER
#pragma section DSPI_B_REGISTER address=0xFFF94000
#pragma use_section DSPI_B_REGISTER DSPI_B
#endif

#ifdef SECTION_DSPI_C_REGISTER
#undef SECTION_DSPI_C_REGISTER
#pragma section DSPI_C_REGISTER address=0xFFF98000
#pragma use_section DSPI_C_REGISTER DSPI_C
#endif

#ifdef SECTION_DSPI_D_REGISTER
#undef SECTION_DSPI_D_REGISTER
#pragma section DSPI_D_REGISTER address=0xFFF9C000
#pragma use_section DSPI_D_REGISTER DSPI_D
#endif

#ifdef SECTION_SCI_A_REGISTER
#undef SECTION_SCI_A_REGISTER
#pragma section SCI_A_REGISTER address=0xFFFB0000
#pragma use_section SCI_A_REGISTER SCI_A
#endif

#ifdef SECTION_SCI_B_REGISTER
#undef SECTION_SCI_B_REGISTER
#pragma section SCI_B_REGISTER address=0xFFFB4000
#pragma use_section SCI_B_REGISTER SCI_B
#endif

#ifdef SECTION_SCI_C_REGISTER
#undef SECTION_SCI_C_REGISTER
#pragma section SCI_C_REGISTER address=0xFFFB8000
#pragma use_section SCI_C_REGISTER SCI_C
#endif

#ifdef SECTION_FLEXCAN_A_REGISTER
#undef SECTION_FLEXCAN_A_REGISTER
#pragma section FLEXCAN_A_REGISTER address=0xFFFC0000
#pragma use_section FLEXCAN_A_REGISTER FlexCAN_A
#endif

#ifdef SECTION_FLEXCAN_B_REGISTER
#undef SECTION_FLEXCAN_B_REGISTER
#pragma section FLEXCAN_B_REGISTER address=0xFFFC4000
#pragma use_section FLEXCAN_B_REGISTER FlexCAN_B
#endif

#ifdef SECTION_FLEXCAN_C_REGISTER
#undef SECTION_FLEXCAN_C_REGISTER
#pragma section FLEXCAN_C_REGISTER address=0xFFFC8000
#pragma use_section FLEXCAN_C_REGISTER FlexCAN_C
#endif

#ifdef SECTION_FLEXCAN_D_REGISTER
#undef SECTION_FLEXCAN_D_REGISTER
#pragma section FLEXCAN_D_REGISTER address=0xFFFCC000
#pragma use_section FLEXCAN_D_REGISTER FlexCAN_D
#endif
#ifdef SECTION_FLEXRAY_REGISTER
#undef SECTION_FLEXRAY_REGISTER
#pragma section FLEXRAY_REGISTER address=0xFFFE0000
#pragma use_section FLEXRAY_REGISTER FlexRay
#endif

#ifdef SECTION_FLASH_A0_REGISTER
#undef SECTION_FLASH_A0_REGISTER
#pragma section FLASH_A0_REGISTER address=0xC3F88000
#pragma use_section FLASH_A0_REGISTER FLASH_A0
#endif

#ifdef SECTION_FLASH_A1_REGISTER
#undef SECTION_FLASH_A1_REGISTER
#pragma section FLASH_A1_REGISTER address=0xC3FB0000
#pragma use_section FLASH_A1_REGISTER FLASH_A1
#endif

#ifdef SECTION_FLASH_A2_REGISTER
#undef SECTION_FLASH_A2_REGISTER
#pragma section FLASH_A2_REGISTER address=0xC3FB4000
#pragma use_section FLASH_A2_REGISTER FLASH_A2
#endif

#ifdef SECTION_FLASH_B0_REGISTER
#undef SECTION_FLASH_B0_REGISTER
#pragma section FLASH_B0_REGISTER far-absolute RW address=0xC3F88000
#pragma use_section FLASH_B0_REGISTER FLASH_B0
#endif

#ifdef SECTION_FLASH_B1A1_REGISTER
#undef SECTION_FLASH_B1A1_REGISTER
#pragma section FLASH_B1A1_REGISTER far-absolute RW address=0xC3FB0000
#pragma use_section FLASH_B1A1_REGISTER FLASH_B1A1
#endif

#ifdef SECTION_FLASH_B1A2_REGISTER
#undef SECTION_FLASH_B1A2_REGISTER
#pragma section FLASH_B1A2_REGISTER far-absolute RW address=0xC3FB4000
#pragma use_section FLASH_B1A2_REGISTER FLASH_B1A2
#endif


#ifdef SECTION_FLASH_A_REGISTER
#undef SECTION_FLASH_A_REGISTER
#pragma section FLASH_A_REGISTER address=0xC3F88000
#pragma use_section FLASH_A_REGISTER FLASH_A
#endif

#ifdef SECTION_FLASH_B_REGISTER
#undef SECTION_FLASH_B_REGISTER
#pragma section FLASH_B_REGISTER address=0xC3F8C000
#pragma use_section FLASH_B_REGISTER FLASH_B
#endif

#ifdef SECTION_PIT_REGISTER
#undef SECTION_PIT_REGISTER
#pragma section PIT_REGISTER address=0xC3FF0000
#pragma use_section PIT_REGISTER PIT
#endif

#ifdef SECTION_CRC_REGISTER
#undef SECTION_CRC_REGISTER
#pragma section CRC_REGISTER address=0xFFE68000
#pragma use_section CRC_REGISTER CRC
#endif

#ifdef SECTION_PMC_REGISTER
#undef SECTION_PMC_REGISTER
#pragma section PMC_REGISTER address=0xC3FBC000
#pragma use_section PMC_REGISTER PMC
#endif

#ifdef SECTION_STM_REGISTER
#undef SECTION_STM_REGISTER
#pragma section STM_REGISTER address=0xFFF3C000
#pragma use_section STM_REGISTER STM
#endif

#ifdef SECTION_MPU_REGISTER
#undef SECTION_MPU_REGISTER
#pragma section MPU_REGISTER address=0xFFF10000
#pragma use_section MPU_REGISTER MPU
#endif

#ifdef SECTION_SWT_REGISTER
#undef SECTION_SWT_REGISTER
#pragma section SWT_REGISTER address=0xFFF38000
#pragma use_section SWT_REGISTER SWT
#endif

#ifdef SECTION_DEC_FILTER_REGISTER
#undef SECTION_DEC_FILTER_REGISTER
#pragma section DEC_FILTER_REGISTER address=0xFFF88000
#pragma use_section DEC_FILTER_REGISTER DEC_FILTER
#endif

#ifdef SECTION_SIM_REGISTER
#undef SECTION_SIM_REGISTER
#pragma section SIM_REGISTER address=0xFFFEC000
#pragma use_section SIM_REGISTER SIM
#endif

#ifdef SECTION_DTS_REGISTER
#undef SECTION_DTS_REGISTER
#pragma section DTS_REGISTER address=0xC3F9C000
#pragma use_section DTS_REGISTER DTS
#endif
