/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file   openamp.h
  * @brief  Header for openamp applications
  * @author  MCD Application Team
  ******************************************************************************
   * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __openamp_H
#define __openamp_H

#include "openamp/open_amp.h"
#include "openamp_conf.h"

#ifdef __cplusplus
 extern "C" {
#endif

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Private defines -----------------------------------------------------------*/
/* USER CODE BEGIN Private defines */

/* USER CODE END  Private defines */

#define OPENAMP_send  rpmsg_send
#define OPENAMP_destroy_ept rpmsg_destroy_ept

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Initialize the openamp framework*/
int MX_OPENAMP_Init(int RPMsgRole, rpmsg_ns_bind_cb ns_bind_cb);

/* Deinitialize the openamp framework*/
void OPENAMP_DeInit(void);

/* Create and register the endpoint */
int OPENAMP_create_endpoint(struct rpmsg_endpoint *ept, const char *name,
                            uint32_t dest, rpmsg_ept_cb cb,
                            rpmsg_ns_unbind_cb unbind_cb);

/* Check for new rpmsg reception */
void OPENAMP_check_for_message(void);

/* Wait loop on endpoint ready ( message dest address is know)*/
void OPENAMP_Wait_EndPointready(struct rpmsg_endpoint *rp_ept);

#ifdef __cplusplus
}
#endif
#endif /*__openamp_H */
