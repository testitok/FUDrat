// HackerTools.cpp : implementation file
//

#include "stdafx.h"
#include "Client.h"
#include "HackerTools.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHackerTools dialog


CHackerTools::CHackerTools(CWnd* pParent /*=NULL*/)
	: CDialog(CHackerTools::IDD, pParent)
{
	//{{AFX_DATA_INIT(CHackerTools)
	m_file = _T("");
	m_rc = FALSE;
	m_imp = FALSE;
	m_bak = FALSE;
	m_key = 0x82;
	//}}AFX_DATA_INIT
}


void CHackerTools::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CHackerTools)
	DDX_Text(pDX, IDC_EDIT_FILE, m_file);
	DDX_Check(pDX, IDC_CHECK_RC, m_rc);
	DDX_Check(pDX, IDC_CHECK_IMP, m_imp);
	DDX_Check(pDX, IDC_CHECK_BAK, m_bak);
	DDX_Text(pDX, IDC_EDIT_KEY, m_key);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CHackerTools, CDialog)
	//{{AFX_MSG_MAP(CHackerTools)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_BN_CLICKED(IDC_BUTTON3, OnButton3)
	ON_BN_CLICKED(IDC_BUTTON_FILE, OnButtonFile)
	ON_BN_CLICKED(IDC_BUTTON_OK, OnButtonOk)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHackerTools message handlers

void CHackerTools::OnButton1() 
{
	// TODO: Add your control notification handler code here
	CFileDialog cfd(TRUE,_T("exe"),NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,_T("可执行文件（*.exe）|*.exe|"));
	cfd.DoModal();
	SetDlgItemText(IDC_EDIT1,cfd.GetPathName());
	
}

void CHackerTools::OnButton2() 
{
	// TODO: Add your control notification handler code here
	CFileDialog cfd(TRUE,_T("exe"),NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,_T("可执行文件（*.exe）|*.exe|"));
	cfd.DoModal();
	SetDlgItemText(IDC_EDIT2,cfd.GetPathName());
	
}


void CHackerTools::OnButton3() 
{
	// TODO: Add your control notification handler code here
	if(!GetDS())
	{
		return;
	}
	CString strFile;
	GetDlgItemText(IDC_EDIT2,strFile);
	CFile file1(strFile,CFile::modeReadWrite);
	if (!file1.m_hFile)
	{
		SetDlgItemText(IDC_STATIC_LOG,_T("打开目标文件失败！"));
		return;
	}
	//计算数字签名大小
	int dsSize = m_size[0];
	dsSize |= ((m_size[1] << 8) & 0xFF00);
	
	DWORD dwSize = file1.GetLength();
	BYTE * pData = new BYTE[dwSize + dsSize];
	file1.Read(pData,dwSize);
	
	
	
	//判断是否是可执行文件
	if(pData[0] != 'M' || pData[1] != 'Z')
	{
		MessageBox(_T("目标文件不是一个可执行文件！"));
		return;
	}
	//计算PE偏移距离
	BYTE temp1[]={
		pData[63],
			pData[62],
			pData[61],
			pData[60]
	};
	int PE = bytesToInt(temp1);
	
	
	//判断指定位置是否有PE头
	if (pData[PE] != 'P' || pData[PE + 1] != 'E')
	{
		MessageBox(_T("没有在目标文件中找到PE头！"));
		return;
	}
	
	
	//计算数字签名位置
	byte temp2[] = {
		pData[PE + 152 + 3],
			pData[PE + 152 + 2],
			pData[PE + 152 + 1],
			pData[PE + 152 + 0]
	};
	int ds = bytesToInt(temp2);
	if(ds != 0)
	{
		MessageBox(_T("目标文件已经存在数字签名！"));
		return;
	}
	//复制数字签名到可执行文件最后位置
	for (int i = 0; i < dsSize; i++)
	{
		pData[dwSize + i] = m_byte[i];
	}
	//修复可执行文件
	BYTE addr [4];
	memset(addr,0,sizeof(byte) *  4);
    addr[0] = (byte) (0xff & dwSize);
    addr[1] = (byte) ((0xff00 & dwSize) >> 8);
    addr[2] = (byte) ((0xff0000 & dwSize) >> 16);
    addr[3] = (byte) ((0xff000000 & dwSize) >> 24);
	
	pData[PE + 152 + 3] = addr[3];
	pData[PE + 152 + 2] = addr[2];
	pData[PE + 152 + 1] = addr[1];
	pData[PE + 152 + 0] = addr[0];
	
	pData[PE + 152 + 4] = m_size[0];
	pData[PE + 152 + 5] = m_size[1];
	file1.SetLength(0);
	file1.Write(pData,dwSize + dsSize);
	file1.Close();
	delete [] m_byte;
	delete [] pData;
//	MessageBox(_T("签名复制成功！"));
	SetDlgItemText(IDC_STATIC_LOG,_T("签名复制成功！"));
	
}
int CHackerTools::bytesToInt(byte* bytes) 
{
    int addr = bytes[3] & 0xFF;
    addr |= ((bytes[2] << 8) & 0xFF00);
    addr |= ((bytes[1] << 16) & 0xFF0000);
    addr |= ((bytes[0] << 24) & 0xFF000000);
    return addr;
}
bool CHackerTools::GetDS(void)
{
	//打开文件，并获得数据
	CString strFile;
	GetDlgItemText(IDC_EDIT1,strFile);
	CFile file1(strFile,CFile::modeRead);
	if (!file1.m_hFile)
	{
		SetDlgItemText(IDC_STATIC_LOG,_T("打开原始文件失败！"));
		return FALSE;
	}
	DWORD dwSize = file1.GetLength();
	BYTE * pData = new BYTE[dwSize];
	file1.Read(pData,dwSize);
	file1.Close();
	
	
	//判断是否是可执行文件
	if(pData[0] != 'M' || pData[1] != 'Z')
	{
		MessageBox(_T("原始文件不是一个可执行文件！"));
		return FALSE;
	}
	//计算PE偏移距离
	BYTE temp1[]={
		pData[63],
			pData[62],
			pData[61],
			pData[60]
	};
	int PE = bytesToInt(temp1);
	
	
	//判断指定位置是否有PE头
	if (pData[PE] != 'P' || pData[PE + 1] != 'E')
	{
		MessageBox(_T("没有在原始文件中找到PE头！"));
		return FALSE;
	}
	
	
	//计算数字签名位置
	byte temp2[] = {
		pData[PE + 152 + 3],
			pData[PE + 152 + 2],
			pData[PE + 152 + 1],
			pData[PE + 152 + 0]
	};
	int ds = bytesToInt(temp2);
	
	//计算数字签名大小
	int dsSize = pData[PE + 152 + 4];
	dsSize |= ((pData[PE + 152 + 5] << 8) & 0xFF00);
	if(dsSize == 0)
	{
		MessageBox(_T("没有在原始文件中找到数字签名！"));
		return FALSE;
	}
	m_size[0] = pData[PE + 152 + 4];
	m_size[1] = pData[PE + 152 + 5];
	
	m_byte = new BYTE[dsSize];
	for (int i = 0; i < dsSize; i++)
	{
		m_byte[i] = pData[ds + i];
	}
	
	delete [] pData;
	return TRUE;

}

void CHackerTools::OnButtonFile() 
{
	// TODO: Add your control notification handler code here
	CFileDialog fileDlg(TRUE,NULL,NULL,NULL,"可执行文件(*.exe)|*.exe|动态链接库文件(*.dll)|*.dll||");
	if (fileDlg.DoModal() != IDOK) return;
	
	m_file = fileDlg.GetPathName();
	UpdateData(FALSE);
	return;
	
}
bool CHackerTools::AddSection()
{
	UpdateData(TRUE);
	HANDLE	hFile = NULL;
	HANDLE	hMap = NULL;
	PVOID	pFile = NULL;

	PIMAGE_DOS_HEADER		dosheader;
	PIMAGE_NT_HEADERS		peheader;
	PIMAGE_SECTION_HEADER	sectiontable;
	PIMAGE_SECTION_HEADER	sectiontablenew;

	PVOID	pStart = NULL;
	PVOID	pEnd = NULL;

	int		secnum;

	DWORD	pos;
	DWORD	size;

	hFile = CreateFile(
				m_file.GetBuffer(0),
				GENERIC_READ|GENERIC_WRITE,
				FILE_SHARE_READ,
				NULL,
				OPEN_EXISTING,
				FILE_ATTRIBUTE_ARCHIVE,
				0
				);
	if(hFile==INVALID_HANDLE_VALUE)
	{
		MessageBox("CreateFile错误");
		return FALSE;
	}	
	
	hMap = CreateFileMapping(
				hFile,
				NULL,
				PAGE_READWRITE,
				0,
				0,
				NULL
				);
	if(hMap == NULL)
	{
		MessageBox("CreateFileMapping错误");
		CloseHandle(hFile);
		return FALSE;
	}
	
	pFile = MapViewOfFile(
				hMap,
				FILE_MAP_ALL_ACCESS,
				0,
				0,
				0
				);
	if(pFile == NULL)
	{
		MessageBox("MapViewOfFile错误");
		CloseHandle(hMap);
		CloseHandle(hFile);
		return FALSE;
	}
	
	dosheader = (PIMAGE_DOS_HEADER)pFile;
	peheader = (PIMAGE_NT_HEADERS)((DWORD)dosheader + dosheader->e_lfanew);
	secnum=peheader->FileHeader.NumberOfSections;
	sectiontable = (PIMAGE_SECTION_HEADER)((DWORD)peheader + sizeof(IMAGE_NT_HEADERS));
	sectiontable +=secnum-1;
	sectiontablenew = sectiontable+1;
	
	DWORD sectionalign=peheader->OptionalHeader.SectionAlignment;
	DWORD filealign=peheader->OptionalHeader.FileAlignment;

	memcpy(sectiontablenew->Name,".code",6);
	if((sectiontable->VirtualAddress+sectiontable->Misc.VirtualSize)%sectionalign!=0)
	{
		sectiontablenew->VirtualAddress=(DWORD)((sectiontable->VirtualAddress+sectiontable->Misc.VirtualSize)/sectionalign+1)*sectionalign;
	}
	else
	{
		sectiontablenew->VirtualAddress=(DWORD)(sectiontable->VirtualAddress+sectiontable->Misc.VirtualSize);
	}
	sectiontablenew->Misc.VirtualSize=(DWORD)sectionalign;
	if((sectiontable->PointerToRawData+sectiontable->SizeOfRawData)%filealign !=0)
	{
		sectiontablenew->PointerToRawData=(DWORD)((sectiontable->PointerToRawData+sectiontable->SizeOfRawData)/filealign+1)*filealign;
	}
	else
	{
		sectiontablenew->PointerToRawData=(DWORD)(sectiontable->PointerToRawData+sectiontable->SizeOfRawData);
	}
	sectiontablenew->SizeOfRawData=(DWORD)filealign;
	sectiontablenew->Characteristics=(DWORD)0x60000020;
	pos=sectiontablenew->PointerToRawData;
	size=sectiontablenew->SizeOfRawData;
	peheader->OptionalHeader.SizeOfImage = sectiontablenew->VirtualAddress+sectiontablenew->Misc.VirtualSize;
	peheader->FileHeader.NumberOfSections +=1;

	UnmapViewOfFile(pFile);
	CloseHandle(hMap);

	DWORD o_size;
	DWORD dFileSize = GetFileSize(hFile,NULL);
	if ((long)dFileSize<(long)pos) return FALSE;
	void * overlay=malloc(dFileSize-pos);
	SetFilePointer(hFile,pos,NULL,FILE_BEGIN);
	ReadFile(hFile,overlay,dFileSize-pos,&o_size,NULL);
	SetFilePointer(hFile,pos,NULL,FILE_BEGIN);
	void * code=malloc(size);
	memset(code,0,size);
	WriteFile(hFile,code,size,&o_size,NULL);
	WriteFile(hFile,overlay,dFileSize-pos,&o_size,NULL);
	free(code);
	free(overlay);

	CloseHandle(hFile);
	return TRUE;
}
void CHackerTools::AsmCode(char *lpBuffer,DWORD *codelen)
{
	unsigned char *p_Code = NULL;
	DWORD dwCodeLen;
	
	_asm
	{
		call __CodeExit
			PUSH EBP
			MOV EBP,ESP
			PUSH -1
			PUSH 0A8B7E3CBh			//算法
			PUSH 0AEB6BBB2h			//不懂
			MOV EAX,DWORD PTR FS:[0]
			PUSH EAX
			MOV DWORD PTR FS:[0],ESP
			POP EAX
			MOV DWORD PTR FS:[0],EAX
			POP EAX
			POP EAX
			POP EAX
			POP EAX
			MOV EBP,EAX
			PUSH 00406071h			//配置地址
			CALL __readconf
			MOV EAX,00401000h		//oep地址
			JMP EAX
__readconf:
		PUSH EDI				//读取配置并解密
			PUSH ESI
			MOV EDI,DWORD PTR DS:[ESP+0Ch]
			MOVSX ESI,BYTE PTR DS:[EDI]
			INC EDI
__readconf_start:
		CMP ESI,0
			JE __readconf_end
			MOV EAX,DWORD PTR DS:[EDI]
			MOV EBX,DWORD PTR DS:[EDI+4]
			MOV CL,BYTE PTR DS:[EDI+8]
			CALL __decode				//call解密函数
			ADD EDI,9
			DEC ESI
			JMP __readconf_start
__readconf_end:
		POP ESI
			POP EDI
			RETN 4
__decode:
		CMP EAX,EBX					//解密函数
			JGE __decode_end
			MOV DL,BYTE PTR DS:[EAX]
			XOR DL,CL
			MOV BYTE PTR DS:[EAX],DL
			INC EAX
			JMP __decode
__decode_end:
		RETN	// 返回主程序
__CodeExit:
		pop eax
			mov p_Code,eax
			lea edx,__CodeExit
			sub edx,eax
			mov dwCodeLen,edx
	}
	
	memcpy(lpBuffer,p_Code,dwCodeLen);
	*codelen = dwCodeLen;
}

bool CHackerTools::CheckSec(PIMAGE_SECTION_HEADER sectiontable,PIMAGE_NT_HEADERS peheader,int num)
{
	if((long)(sectiontable->VirtualAddress)<=(long)(peheader->OptionalHeader.DataDirectory[num].VirtualAddress))
		if((long)(sectiontable->VirtualAddress+sectiontable->Misc.VirtualSize)>=(long)(peheader->OptionalHeader.DataDirectory[num].VirtualAddress+peheader->OptionalHeader.DataDirectory[num].Size)) return TRUE;
		return FALSE;
}
void CHackerTools::OnButtonOk() 
{
		// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if(m_file.GetLength()==0){MessageBox("请指定要加壳的文件");return;};
	CString m_file_new=m_file+".bak";
	if(m_bak){CopyFile(m_file.GetBuffer(0),m_file_new.GetBuffer(0),TRUE);}
	
	if(!AddSection()){MessageBox("添加新区段失败");return;} //添加一个新区段
	HANDLE	hFile = NULL;
	HANDLE	hMap = NULL;
	PVOID	pFile = NULL;

	PIMAGE_DOS_HEADER		dosheader;
	PIMAGE_NT_HEADERS		peheader;
	PIMAGE_SECTION_HEADER	sectiontable;

	PVOID	pStart = NULL;
	PVOID	pEnd = NULL;

	DWORD	dwEntryPoint = 0;
	BYTE    key=m_key%256;

	unsigned char lpCodeBuf[512]={0};
	DWORD	dwCodeLen=0;
	AsmCode((char *)lpCodeBuf,&dwCodeLen);

	hFile = CreateFile(
				m_file.GetBuffer(0),
				GENERIC_READ|GENERIC_WRITE,
				FILE_SHARE_READ,
				NULL,
				OPEN_EXISTING,
				FILE_ATTRIBUTE_ARCHIVE,
				0
				);
	if(hFile==INVALID_HANDLE_VALUE)
	{
		MessageBox("CreateFile错误");
		return;
	}	
	DWORD dFileSize = GetFileSize(hFile,NULL);
	hMap = CreateFileMapping(
				hFile,
				NULL,
				PAGE_READWRITE,
				0,
				0,
				NULL
				);
	if(hMap == NULL)
	{
		MessageBox("CreateFileMapping错误");
		CloseHandle(hFile);
		return;
	}
	
	pFile = MapViewOfFile(
				hMap,
				FILE_MAP_ALL_ACCESS,
				0,
				0,
				0
				);
	if(pFile == NULL)
	{
		MessageBox("MapViewOfFile错误");
		CloseHandle(hMap);
		CloseHandle(hFile);
		return;
	}
	
	dosheader = (PIMAGE_DOS_HEADER)pFile;
	peheader = (PIMAGE_NT_HEADERS)((DWORD)dosheader + dosheader->e_lfanew);
	int secnum = peheader->FileHeader.NumberOfSections;
	dwEntryPoint = (DWORD)(peheader->OptionalHeader.ImageBase + peheader->OptionalHeader.AddressOfEntryPoint);
	sectiontable = (PIMAGE_SECTION_HEADER)((DWORD)peheader + sizeof(IMAGE_NT_HEADERS));
	byte ennum=0;
	for(int i=0;i<secnum-1;i++)
	{
		if(CheckSec(sectiontable,peheader,1)||CheckSec(sectiontable,peheader,12))
		{
			char a[200]={0};
			wsprintf(a,"%s\t%s\t%08X","导入表段",sectiontable->Name,sectiontable->VirtualAddress);
			MessageBox(a);
		}
		else if(CheckSec(sectiontable,peheader,2))
		{
			char a[200]={0};
			wsprintf(a,"%s\t%s\t%08X","资源段",sectiontable->Name,sectiontable->VirtualAddress);
			MessageBox(a);
		}
		else
		{

			pStart = (PVOID)((DWORD)pFile + (DWORD)sectiontable->PointerToRawData);
			DWORD minSize;
			if((long)sectiontable->SizeOfRawData < (long)sectiontable->Misc.VirtualSize)
			{
				minSize=sectiontable->SizeOfRawData;
			}
			else
			{
				minSize=sectiontable->Misc.VirtualSize;
			}

			pEnd = (PVOID)((DWORD)pFile + (DWORD)sectiontable->PointerToRawData + minSize);

			_asm{
					mov eax,pStart
			loop1:
					cmp eax,pEnd
					jge loop2
					mov dl,byte ptr ds:[eax]
					xor dl,key
					mov byte ptr ds:[eax],dl
					inc eax
					jmp loop1
			loop2:
				}
			
			*(DWORD *) (lpCodeBuf+dwCodeLen+1+ennum*9) = (DWORD) (peheader->OptionalHeader.ImageBase +sectiontable->VirtualAddress);
			*(DWORD *) (lpCodeBuf+dwCodeLen+5+ennum*9) = (DWORD) (peheader->OptionalHeader.ImageBase +sectiontable->VirtualAddress+minSize);
			*(BYTE *)  (lpCodeBuf+dwCodeLen+9+ennum*9) = (BYTE) key;
			ennum++;
			sectiontable->Characteristics  |= 0x80000000;
		}

		sectiontable++;
	}

	*(BYTE *) (lpCodeBuf+dwCodeLen)=ennum;
	*(DWORD *) (lpCodeBuf + 0x2B) = (DWORD)(peheader->OptionalHeader.ImageBase + sectiontable->VirtualAddress +dwCodeLen);
	*(DWORD *) (lpCodeBuf + 0x35) = (DWORD)dwEntryPoint;

	pStart = (PVOID)((DWORD)pFile + (DWORD)sectiontable->PointerToRawData);
	//pEnd = (PVOID)((DWORD)pFile + (DWORD)sectiontable->PointerToRawData + (DWORD)sectiontable->SizeOfRawData);
	memcpy(pStart,lpCodeBuf,512);
	peheader->OptionalHeader.AddressOfEntryPoint = sectiontable->VirtualAddress;

	peheader->OptionalHeader.MajorLinkerVersion = 6;
	peheader->OptionalHeader.MinorLinkerVersion = 0;

	MessageBox("加壳成功,请严格测试后使用");

	UnmapViewOfFile(pFile);
	CloseHandle(hMap);
	CloseHandle(hFile);

	return;
	
}
