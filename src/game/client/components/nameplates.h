/* (c) Magnus Auvinen. See licence.txt in the root of the distribution for more information. */
/* If you are missing that file, acquire a complete release at teeworlds.com.                */
#ifndef GAME_CLIENT_COMPONENTS_NAMEPLATES_H
#define GAME_CLIENT_COMPONENTS_NAMEPLATES_H
#include <base/vmath.h>

#include <engine/shared/protocol.h>
#include <engine/textrender.h>

#include <game/client/component.h>

struct CNetObj_Character;
struct CNetObj_PlayerInfo;

class CNamePlates;

class CNamePlate
{
public:
	class CNamePlateName
	{
	public:
		CNamePlateName()
		{
			Reset();
		}
		void Reset()
		{
			m_TextContainerIndex.Reset();
			m_Id = -1;
			m_aName[0] = '\0';
			m_FriendMark = false;
			m_FontSize = -INFINITY;
		}
		void Update(CNamePlates &This, int Id, const char *pName, bool FriendMark, float FontSize, int RealId = -1);
		STextContainerIndex m_TextContainerIndex;
		char m_aName[MAX_NAME_LENGTH];
		int m_Id;
		bool m_FriendMark;
		float m_FontSize;

		bool m_NameWar = false;
	};
	class CNamePlateClan
	{
	public:
		CNamePlateClan()
		{
			Reset();
		}
		void Reset()
		{
			m_TextContainerIndex.Reset();
			m_aClan[0] = '\0';
			m_FontSize = -INFINITY;
		}
		void Update(CNamePlates &This, const char *pClan, float FontSize);
		STextContainerIndex m_TextContainerIndex;
		char m_aClan[MAX_CLAN_LENGTH];
		float m_FontSize;
	};
	class CNamePlateHookWeakStrongId
	{
	public:
		CNamePlateHookWeakStrongId()
		{
			Reset();
		}
		void Reset()
		{
			m_TextContainerIndex.Reset();
			m_Id = -1;
			m_FontSize = -INFINITY;
		}
		void Update(CNamePlates &This, int Id, float FontSize);
		STextContainerIndex m_TextContainerIndex;
		int m_Id;
		float m_FontSize;
	};
	CNamePlate()
	{
		Reset();
	}
	void Reset()
	{
		m_Name.Reset();
		m_Clan.Reset();
		m_WeakStrongId.Reset();

		// TClient
		m_SkinName.Reset();
		m_Reason.Reset();
	}
	void DeleteTextContainers(ITextRender &TextRender)
	{
		TextRender.DeleteTextContainer(m_Name.m_TextContainerIndex);
		TextRender.DeleteTextContainer(m_Clan.m_TextContainerIndex);
		TextRender.DeleteTextContainer(m_WeakStrongId.m_TextContainerIndex);
		TextRender.DeleteTextContainer(m_SkinName.m_TextContainerIndex);
		TextRender.DeleteTextContainer(m_Reason.m_TextContainerIndex);
	}
	CNamePlateName m_Name;
	CNamePlateClan m_Clan;
	CNamePlateHookWeakStrongId m_WeakStrongId;

	// TClient
	class CNamePlateSkin
	{
	public:
		CNamePlateSkin()
		{
			Reset();
		}
		void Reset()
		{
			m_TextContainerIndex.Reset();
			m_aSkin[0] = '\0';
			m_FontSize = -INFINITY;
		}
		void Update(CNamePlates &This, const char *pSkin, float FontSize);
		STextContainerIndex m_TextContainerIndex;
		char m_aSkin[MAX_SKIN_LENGTH];
		float m_FontSize;
	};
	class CNamePlateReason
	{
	public:
		CNamePlateReason()
		{
			Reset();
		}
		void Reset()
		{
			m_TextContainerIndex.Reset();
			m_aReason[0] = '\0';
			m_FontSize = -INFINITY;
		}
		void Update(CNamePlates &This, const char *pReason, float FontSize);
		STextContainerIndex m_TextContainerIndex;
		char m_aReason[MAX_WARLIST_REASON_LENGTH];
		float m_FontSize;
	};
	CNamePlateSkin m_SkinName;
	CNamePlateReason m_Reason;
};

class CNamePlates : public CComponent
{
	friend class CNamePlate::CNamePlateName;
	friend class CNamePlate::CNamePlateClan;
	friend class CNamePlate::CNamePlateHookWeakStrongId;

	// TClient
	friend class CNamePlate::CNamePlateSkin;
	friend class CNamePlate::CNamePlateReason;

	CNamePlate m_aNamePlates[MAX_CLIENTS];

	void ResetNamePlates();

	int m_DirectionQuadContainerIndex;
	class CRenderNamePlateData
	{
	public:
		vec2 m_Position;
		ColorRGBA m_Color;
		ColorRGBA m_OutlineColor;
		float m_Alpha;
		const char *m_pName;
		bool m_ShowFriendMark;
		int m_ClientId;
		float m_FontSize;
		const char *m_pClan;
		float m_FontSizeClan;
		bool m_ShowDirection;
		bool m_DirLeft;
		bool m_DirJump;
		bool m_DirRight;
		float m_FontSizeDirection;
		bool m_ShowHookWeakStrong;
		TRISTATE m_HookWeakStrong;
		bool m_ShowHookWeakStrongId;
		int m_HookWeakStrongId;
		float m_FontSizeHookWeakStrong;

		// TClient
		int m_RealClientId;
		bool m_IsGame = false;
		bool m_ShowClanWarInName = false;
		bool m_IsLocal = false;
	};
	void RenderNamePlate(CNamePlate &NamePlate, const CRenderNamePlateData &Data);

public:
	void RenderNamePlateGame(vec2 Position, const CNetObj_PlayerInfo *pPlayerInfo, float Alpha, bool ForceAlpha);
	void RenderNamePlatePreview(vec2 Position);
	virtual int Sizeof() const override { return sizeof(*this); }
	virtual void OnWindowResize() override;
	virtual void OnInit() override;
	virtual void OnRender() override;
};

#endif
