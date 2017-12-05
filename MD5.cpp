#include "stdafx.h"
#include "MD5.h"

CString MD5::GetMD5(BYTE* pBuf, UINT nLength)
{
	AfxIsValidAddress(pBuf,nLength,FALSE);
	MD5 MD5;
	MD5.Update( pBuf, nLength );
	return MD5.Final();
}

DWORD MD5::RotateLeft(DWORD x, int n)
{
	ASSERT( sizeof(x) == 4 );
	return (x << n) | (x >> (32-n));
}

MD5::MD5()
{
	memset(m_lpszBuffer,0,64);
	m_nCount[0]=m_nCount[1]=0;
	m_lMD5[0]=MD5_INIT_STATE_0;
	m_lMD5[1]=MD5_INIT_STATE_1;
	m_lMD5[2]=MD5_INIT_STATE_2;
	m_lMD5[3]=MD5_INIT_STATE_3;
}
void MD5::ByteToDWord(DWORD* Output,BYTE* Input,UINT nLength)
{
	ASSERT(nLength%4==0);
	ASSERT(AfxIsValidAddress(Output,nLength/4,TRUE));
	ASSERT(AfxIsValidAddress(Input,nLength,FALSE));
	UINT i=0;
	UINT j=0;
	for(;j<nLength;i++,j+=4)
	{
		Output[i]=(ULONG)Input[j]  |
			(ULONG)Input[j+1]<<8   |
			(ULONG)Input[j+2]<<16  |
			(ULONG)Input[j+3]<<24;
	}
}

void MD5::DWOrdToByte(BYTE* Output,DWORD* Input,UINT nLength)
{
	ASSERT(nLength%4==0);
	ASSERT(AfxIsValidAddress(Output,nLength,TRUE));
	ASSERT(AfxIsValidAddress(Input,nLength/4,FALSE));
	UINT i=0;
	UINT j=0;
	for(;j<nLength;i++,j+=4)
	{
		Output[j]=(UCHAR)(Input[i]&0xff);  
		Output[j+1]=(UCHAR)((Input[i]>>8)&0xff);
		Output[j+2]=(UCHAR)((Input[i]>>16)&0xff);
		Output[j+3]=(UCHAR)((Input[i]>>24)&0xff);
	}
}

void MD5::FF(DWORD &A,DWORD B,DWORD C,DWORD D,DWORD X,DWORD S,DWORD T)
{
	DWORD F=(B&C)|(~B&D);
	A+=F+X+T;
	A=RotateLeft(A,S);
	A+=B;
}

void MD5::GG(DWORD &A,DWORD B,DWORD C,DWORD D,DWORD X,DWORD S,DWORD T)
{
	DWORD G=(B&D)|(C&~D);
	A+=G+X+T;
	A=RotateLeft(A,S);
	A+=B;
}

void MD5::HH(DWORD &A,DWORD B,DWORD C,DWORD D,DWORD X,DWORD S,DWORD T)
{
	DWORD H=(B^C^D);
	A+=H+X+T;
	A=RotateLeft(A,S);
	A+=B;
}

void MD5::II(DWORD &A,DWORD B,DWORD C,DWORD D,DWORD X,DWORD S,DWORD T)
{
	DWORD I=(C^(B|~D));
	A+=I+X+T;
	A=RotateLeft(A,S);
	A+=B;
}

void MD5::Transfrom(BYTE Block[64])
{
	ULONG a=m_lMD5[0];
	ULONG b=m_lMD5[1];
	ULONG c=m_lMD5[2];
	ULONG d=m_lMD5[3];
	ULONG X[16];
	ByteToDWord(X,Block,64);
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 16; j++)
		{
			switch (i)
			{
			case 0:
				FF(a,b,c,d,X[XINDEX[i][j]],MD5_S[i][j],MD5_T[(i+1)*(j+1)]);
				break;
			case 1:
				GG(a,b,c,d,X[XINDEX[i][j]],MD5_S[i][j],MD5_T[(i+1)*(j+1)]);
				break;
			case 2:
				HH(a,b,c,d,X[XINDEX[i][j]],MD5_S[i][j],MD5_T[(i+1)*(j+1)]);
				break;
			case 3:
				II(a,b,c,d,X[XINDEX[i][j]],MD5_S[i][j],MD5_T[(i+1)*(j+1)]);
				break;
			}
		}
	}
	m_lMD5[0]+=a;
	m_lMD5[1]+=b;
	m_lMD5[2]+=c;
	m_lMD5[3]+=d;
}

void MD5::Update(BYTE *Input,ULONG nInputLen)
{
	UINT nIndex=(UINT)((m_nCount[0]>>3)&0x3F);
	if((m_nCount[0]+=nInputLen<<3)<(nInputLen<<3))
	{
		m_nCount[1]++;
	}
	m_nCount[1]+=(nInputLen>>29);
	UINT i=0;
	UINT nPartLen=64-nIndex;
	if(nInputLen>=nPartLen)
	{
		memcpy(&m_lpszBuffer[nIndex],Input,nPartLen);
		Transfrom(m_lpszBuffer);
		for(i=nPartLen;i+63<nInputLen;i+=64)
		{
			Transfrom(&Input[i]);
		}
		nIndex=0;
	}
	else
	{
		i=0;
	}
	memcpy(&m_lpszBuffer[nIndex],&Input[i],nInputLen-i);
}

CString MD5::Final()
{
	BYTE Bits[8];
	DWOrdToByte(Bits,m_nCount,8);
	UINT nIndex=(UINT)((m_nCount[0]>>3)&0x3f);
	UINT nPadLen=(nIndex<56)?(56-nIndex):(120-nIndex);
	Update(PADDING,nPadLen);
	Update(Bits,8);
	const int nMD5Size=16;
	unsigned char lpszMD5[nMD5Size];
	DWOrdToByte(lpszMD5,m_lMD5,nMD5Size);
	CString strMD5;
	for(int i=0;i<nMD5Size;i++)
	{
		CString Str;
		if(lpszMD5[i]==0)
		{
			Str=CString("00");
		}
		else if(lpszMD5[i]<=15)
		{
			Str.Format("0%x",lpszMD5[i]);
		}
		else
		{
			Str.Format("%x",lpszMD5[i]);
		}
		ASSERT(Str.GetLength()==2);
		strMD5+=Str;
	}
	ASSERT(strMD5.GetLength()==32);
	return strMD5;
}