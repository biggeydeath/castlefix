#pragma once

struct RecvProp;

struct DVariant
{
	union
	{
		float m_Float;
		long m_Int;
		char *m_pString;
		void *m_pData;
		float m_Vector[3];
		int64_t m_Int64;
	};

	int m_Type;
};

struct CRecvProxyData
{
	const RecvProp* m_pRecvProp;
	DVariant m_Value;
	int m_iElement;
	int m_ObjectID;
};

struct RecvTable
{
	RecvProp *m_pProps;
	int m_nProps;
	void *m_pDecoder;
	char *m_pNetTableName;
	bool m_bInitialized;
	bool m_bInMainList;
};

typedef void(*RecvVarProxyFn) (const CRecvProxyData *pData, void *pStruct, void *pOut);

struct RecvProp
{
	char *m_pVarName;
	int m_RecvType;
	int m_Flags;
	int m_StringBufferSize;
	bool m_bInsideArray;
	const void *m_pExtraData;
	RecvProp *m_pArrayProp;
	void *m_ArrayLengthProxy;
	RecvVarProxyFn m_ProxyFn;
	void *m_DataTableProxyFn;
	RecvTable *m_pDataTable;
	int m_Offset;
	int m_ElementStride;
	int m_nElements;
	const char *m_pParentArrayPropName;
};

class IClientNetworkable;
typedef IClientNetworkable* (*CreateClientClassFn)(int entnum, int serialNum);
typedef IClientNetworkable* (*CreateEventFn)();




class ClientClass
{
public:
	CreateClientClassFn m_pCreateFn;
	CreateEventFn *m_pCreateEventFn;
	char* m_pNetworkName;
	RecvTable *m_pRecvTable;
	ClientClass* m_pNext;
	EClassIds m_ClassID;
};

enum ClearFlags_t
{
	VIEW_CLEAR_COLOR = 0x1,
	VIEW_CLEAR_DEPTH = 0x2,
	VIEW_CLEAR_FULL_TARGET = 0x4,
	VIEW_NO_DRAW = 0x8,
	VIEW_CLEAR_OBEY_STENCIL = 0x10, // Draws a quad allowing stencil test to clear through portals
	VIEW_CLEAR_STENCIL = 0x20,
};
enum RenderViewInfo_t
{
	RENDERVIEW_UNSPECIFIED = 0,
	RENDERVIEW_DRAWVIEWMODEL = (1 << 0),
	RENDERVIEW_DRAWHUD = (1 << 1),
	RENDERVIEW_SUPPRESSMONITORRENDERING = (1 << 2),
};
class IBaseClientDLL
{
public:
	ClientClass* GetAllClasses()
	{
		typedef ClientClass* (*oGetAllClasses)(void*);
		return getvfunc<oGetAllClasses>(this, 8)(this);
	}
	bool GetPlayerView(CViewSetup &playerView)
	{
		typedef bool (__thiscall*oGetAllClasses)(void*, CViewSetup&);
		return getvfunc<oGetAllClasses>(this, 59)(this, playerView);
	}
};

