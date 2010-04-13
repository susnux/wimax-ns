/**************************************************************************
 Copyright (c) 2007-2008, Intel Corporation. All rights reserved.

 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions are met:

  1. Redistributions of source code must retain the above copyright notice,
     this list of conditions and the following disclaimer.

  2. Redistributions in binary form must reproduce the above copyright
     notice, this list of conditions and the following disclaimer in the
     documentation and/or other materials provided with the distribution.

  3. Neither the name of the Intel Corporation nor the names of its
     contributors may be used to endorse or promote products derived from
     this software without specific prior written permission.

 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 POSSIBILITY OF SUCH DAMAGE.

***************************************************************************/
#ifndef _WMX_SDK_NDS_L5_H
#define _WMX_SDK_NDS_L5_H


#include "CommonServices.h"
#include "WrappersCommon.h"
extern OSAL_critical_section cs_apdo_funcs;


typedef enum _NDNS_AGENT_L4_OPCODE
{
	//Commands OPCODES
	NDNS_OPCODE_START_SCAN = 0,
	NDNS_OPCODE_START_SCAN_DIRECT,
	NDNS_OPCODE_STOP_SCAN,
	//NDNS_OPCODE_SCAN,
	NDNS_OPCODE_CONNECT,
	NDNS_OPCODE_DISCONNECT,
	NDNS_OPCODE_RF_ON,
	NDNS_OPCODE_RF_OFF,

	//Indication Types OPCODES
	NDNS_OPCODE_IND_SCAN_COMPLETED,
	NDNS_OPCODE_IND_CONNECT_COMPLETED,
	NDNS_OPCODE_IND_SCAN_UPDATE,
	NDNS_OPCODE_IND_SYSTEM_STATE_UPDATE,
	NDNS_OPCODE_IND_DEVICE_STATUS_UPDATE,
	NDNS_OPCODE_IND_CURRENT_PREFERRED_NSP,
	NDNS_OPCODE_IND_PNM_NOTIFICATION,
	NDNS_OPCODE_IND_MEDIA_STATUS,

	// CU indications
	NDNS_OPCODE_IND_PROVISIONING_OPERATION,
	NDNS_OPCODE_IND_ALERT_NOTIFICATION,

	NDNS_OPCODE_IND_COEX_UPDATE,
	NDNS_OPCODE_IND_PACKAGE_UPDATE,
	NDNS_OPCODE_IND_CONNECTION_MODE_UPDATE,
	NDNS_OPCODE_IND_FAST_RECONNECT_MODE_UPDATE,
	NDNS_OPCODE_IND_ROAMING_MODE_UPDATE,
	NDNS_OPCODE_IND_CONNECTED_AS_CURRENT_PREFERRED_CAPABILITY_STATUS_UPDATE,
	NDNS_OPCODE_IND_PACKAGE_DOWNLOAD_PROGRESS,

	// OMA client indications
	NDNS_OPCODE_IND_APDO_LINK_STATUS,
	NDNS_OPCODE_IND_APDO_ALERT_RESPONSE,
	NDNS_OPCODE_IND_APDO_SESSION_STATUS,
	NDNS_OPCODE_IND_APDO_OOB_NOTIFICATION,
	NDNS_OPCODE_IND_APDO_FUMO_DL_APPROVAL_STATUS,
	NDNS_OPCODE_IND_APDO_DELETE_DM_ACCOUNT,

	//Data Getters
	NDNS_OPCODE_GET_CONNECTED_NSP,
	NDNS_OPCODE_GET_LAST_KNOWN_NSP_IDS,
	NDNS_OPCODE_GET_SLA,
	NDNS_OPCODE_GET_LINK_STATUS,
	NDNS_OPCODE_GET_STATISTICS,
	NDNS_OPCODE_GET_DEVICE_STATUS,
	NDNS_OPCODE_GET_PACKAGE_INFO,
	NDNS_OPCODE_GET_INSTALLATION_INFO,
	NDNS_OPCODE_GET_WMF_COMPLIANCE_VER,
	NDNS_OPCODE_GET_PNM_REQUESTED_CHANNEL,
	NDNS_OPCODE_GET_IS_PNM_COMM_DEV_USING_CHANNEL,
	
	// current preferred NSP
	NDNS_OPCODE_GET_CURRENT_PREFERRED_NSP,
	NDNS_OPCODE_SET_CURRENT_PREFERRED_NSP,

	//User Connection Mode
	NDNS_OPCODE_GET_CONNECTION_MODE,
	NDNS_OPCODE_SET_CONNECTION_MODE,

	//User Roaming Mode
	NDNS_OPCODE_GET_ROAMING_MODE,
	NDNS_OPCODE_SET_ROAMING_MODE,

	//coexistence mode
	NDNS_OPCODE_SET_COEXISTANCE_MODE,
	NDNS_OPCODE_GET_COEXISTANCE_MODE,
	NDNS_OPCODE_IND_RF_TAKEN,

	// fast reconnect status
	NDNS_OPCODE_GET_FAST_RECONNECT_STATUS,
	NDNS_OPCODE_SET_FAST_RECONNECT_STATUS,

	//APDO opcodes 
	NDNS_OPCODE_GET_APDO_INFO,
	NDNS_OPCODE_ADD_APDO_INFO,
	NDNS_OPCODE_UPDATE_APDO_INFO,
	NDNS_OPCODE_DELETE_APDO_INFO,
	NDNS_OPCODE_EXECUTE_APDO_INFO,
	NDNS_OPCODE_GET_CONTACT_INFORMATION,
	NDNS_OPCODE_GET_NSP_CONTACT_INFO_BY_NAME,
	NDNS_OPCODE_APDO_SET_PACKAGE_PATH,
	NDNS_OPCODE_GET_BEK,
	NDNS_OPCODE_GET_APDO_LINK_STATUS, 
	NDNS_OPCODE_FUMO_UPDATE,
	NDNS_OPCODE_GET_APDO_OPERATOR_CONFIGURATIONS,
	NDNS_OPCODE_GET_CONNECTED_NSP_FOR_APDO, // we allow call to this API during provisioining...
	NDNS_OPCODE_GET_POLLING_SUPPORTED,
	NDNS_OPCODE_GET_APDO_DHCP_HOST_NAME,


	NDNS_OPCODE_APDO_TYPE, // The same opcode is used for few functions

	NDNS_OPCODE_GET_UNPROVISIONED_NSP_IDS,
	NDNS_OPCODE_GET_PROVISIONED_NSP_IDS,
	NDNS_OPCODE_DEPROVISION_NSP,
	NDNS_OPCODE_GET_NSP_INFO,
	NDNS_OPCODE_RESTORE_BACKUP_PROVISIONING_DATABASE,
	NDNS_OPCODE_RESTORE_FACTORY_SETTINGS,
	NDNS_OPCODE_APDO_APPROVE_ACTION_REQUEST,

	// FUMO
	NDNS_OPCODE_SET_PACKAGE_UPDATE_STATE,
	NDNS_OPCODE_SET_MSCHAP_V2_CRD,

	// SP Lock
	NDNS_OPCODE_SET_SERVICE_PROVIDER_UNLOCK,
	NDNS_OPCODE_GET_SERVICE_PROVIDER_LOCK_STATUS,	

	//Supplicant

	//ConnectedAsCurrentPreferredCapabilityStatus
	NDNS_OPCODE_GET_CONNECTED_AS_CURRENT_PREFERRED_CAPABILITY_STATUS,
	NDNS_OPCODE_SET_CONNECTED_AS_CURRENT_PREFERRED_CAPABILITY_STATUS,

	//Error
	NDNS_OPCODE_ERROR
} NDNS_AGENT_L4_OPCODE;


typedef struct _NDNS_MESSAGE
{
	UINT32 opcode;
	UINT32 bufferLength;
	BYTE buf[1];
} NDNS_MESSAGE, *pNDNS_MESSAGE;

//
wmx_Status_t wmxNds_InitL5();
void wmxNds_FinalizeL5();

void wmxNds_MessagesHandler(L5_CONNECTION Conn,
											L5_TARGET_ID nOriginID,

											UINT32  dwSentMessageID,
											void  *pvSentBuffer,
											UINT32  cbSentBufferSize,

											UINT32  *pdwResponseMessageID,
											void  *pvResponseBuffer,
											UINT32  *cbResponseBufferSize,

											void *pvUserContext,
											void *pvReserved );

void wmxNds_EventHandler( L5_CONNECTION Conn, L5_EVENT eEvent, void *pvEventData, void *pvUserContext);

#endif // _WMX_SDK_NDS_L5_H