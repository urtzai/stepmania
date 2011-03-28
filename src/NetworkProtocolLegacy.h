/* NetworkProtocolLegacy - Legacy SMOnline networking protocol */
// todo: strip this file down to the relevant stuff.

#ifndef NetworkProtocolLegacy_H
#define NetworkProtocolLegacy_H

#include "NetworkPacket.h"

class EzSockets;

class NetworkProtocolLegacy: public NetworkProtocol
{
public:
	NetworkProtocolLegacy();
	~NetworkProtocolLegacy();

	const int ProtocolVersion = 3;

	EzSockets *NetPlayerClient;
	EzSockets *BroadcastReception;	// only used for SMLAN servers?

	bool m_bIsSMOnline;	// Are we using a SMO server?
	int m_iServerVersion;	// if (>= 128) m_bIsSMOnline = true
	RString m_sServerName;
	int m_iSalt;
	int GetSMOnlineSalt(){ return m_iSalt; }
	RString MD5Hex( const RString &sInput );

	// Client-side commands:
	enum Command
	{
		Ping = 0,				// [ 0/NSCPing] nop
		PingReply,				// [ 1/NSCPingR] nop response
		Hello,					// [ 2/NSCHello]
		GameStartRequest,		// [ 3/NSCGSR]
		GameOverNotice,			// [ 4/NSCGON]
		GameStatusUpdate,		// [ 5/NSCGSU]
		StyleUpdate,			// [ 6/NSCSU]
		ChatMessage,			// [ 7/NSCCM]
		RequestStartGame,		// [ 8/NSCRSG]
		UpdateUserList,			// [ 9/NSCUUL] "reserved"
		ScreenChange,			// [10/NSCSMS]
		ChangePlayerOptions,	// [11/NSCUPOpts]
		SMOnline,				// [12/NSCSMOnline]
		Formatted,				// [13/NSCFormatted] Reserved client-side
		Attack,					// [14/NSCAttack] undocumented
		XML,					// [15] not really used
		NUM_SMO_COMMANDS
	};
	const Command ServerOffset = (Command)128;
	NetworkPacket m_Packet;
	NetworkPacket m_NetworkPacket;		// was m_SMOnlinePacket

	// Server Packet Handlers
	void SMOPing();
	void SMOGameOverNotice();
	void SMOScoreboardUpdate();
	void SMOSystemMessage();
	void SMOChatMessage();
	void SMOChangeSong();
	void SMOUpdateUserList();
	void SMOSelectMusic();
	void SMOnlinePacket();
	void SMOAttack();

	// Client Packet Handlers
	void SMOHello();
	void SendSMOnline();
	void ReportStyle();	// "Report style, players, and names"

	// Lobby
	void SendChat(const RString& sMessage);
	void RequestRoomInfo(const RString& sName); // formerly in RoomInfoDisplay

	// SelMusic
	void ChangeScreen(int i);	// "Report song selection screen on/off" (was ReportNSSOnOff)
	void ReportPlayerOptions();
	void StartRequest(short iPosition);	// Request a start; Block until granted.
	void SelectUserSong();

	// Gameplay
	void ReportScore(int playerID, int step, int score, int combo, float offset);
	SMOStepType TranslateStepType(int score);
	void ReportSongOver();
};

#endif

/*
 * (c) 2010 AJ Kelly
 * All rights reserved.
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, and/or sell copies of the Software, and to permit persons to
 * whom the Software is furnished to do so, provided that the above
 * copyright notice(s) and this permission notice appear in all copies of
 * the Software and that both the above copyright notice(s) and this
 * permission notice appear in supporting documentation.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT OF
 * THIRD PARTY RIGHTS. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR HOLDERS
 * INCLUDED IN THIS NOTICE BE LIABLE FOR ANY CLAIM, OR ANY SPECIAL INDIRECT
 * OR CONSEQUENTIAL DAMAGES, OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS
 * OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR
 * OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 * PERFORMANCE OF THIS SOFTWARE.
 */