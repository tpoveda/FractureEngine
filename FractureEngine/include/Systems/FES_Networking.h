#ifndef FES_Networking_H
#define FES_Networking_H


#include "../Interfaces/FE_System.h"
/*
#include "RakPeerInterface.h"
#include "MessageIdentifiers.h"
#include "BitStream.h"
#include "RakNetTypes.h"*/

#define SERVER_PORT 60000
#define MAX_ALIAS_LEN 32
/*
enum GameMessages
{
	ID_GAME_MESSAGE_1 = ID_USER_PACKET_ENUM + 1,
	CM_INIT,
	CM_POS,
	CM_ST,
	CM_OBJ,
	CM_NP,
	CM_RR,
	CM_FU,
	SM_CID,
	SM_AR,
	SM_DR,
	SM_AB,
	SM_DB,
	SM_ATR,
	SM_DTR,
	SM_POS,
	SM_ST,
	SM_EST,
	SM_EPOS,
	SM_OLE,
	SM_BAS,
	SM_MI,
	SM_MF,
	SM_NP,
	SM_DP
};
*/
class FES_Networking : public FE_System
{

public:

	FES_Networking();
	~FES_Networking();

	void init();
	void processEntities(std::vector<F3D_Entity*>);

	void processReceiver();
	void processSender();

	void getMSG();
	void sendMSG();

};

#endif