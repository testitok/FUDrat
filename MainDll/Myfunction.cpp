// Myfunction.cpp: implementation of the Myfunction class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Myfunction.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Myfunction:: Myfunction()
{

}

Myfunction:: ~Myfunction()
{

}

//strstr����Դ��
//////////////////////////////////////////////////////////////////////////////////////////////////
char * Myfunction:: my_strstr(const char * str1,const char * str2)
{
        char *cp = (char *) str1;
        char *s1, *s2;
        if ( !*str2 )
            return((char *)str1);
        while (*cp)
        {
                s1 = cp;
                s2 = (char *) str2;

                while ( *s1 && *s2 && !(*s1-*s2) )
                        s1++, s2++;
                if (!*s2)
                        return(cp);
                cp++;
        }
        return(NULL);
}

//�Զ��庯�� stricmp(�ַ����Ƚ� �����ִ�Сд)
////////////////////////////////////////////////////////////////////////////////////////
int Myfunction:: my_stricmp(const char *dst, const char *src)
{
   int ch1, ch2;
   do 
   {
      if ( ((ch1 = (unsigned char)(*(dst++))) >= 'A') &&(ch1 <= 'Z') )
        ch1 += 0x20;
      if ( ((ch2 = (unsigned char)(*(src++))) >= 'A') &&(ch2 <= 'Z') )
        ch2 += 0x20;
   } while ( ch1 && (ch1 == ch2) );
   return(ch1 - ch2);
}

//strchr����Դ��
//////////////////////////////////////////////////////////////////////////////////////////////////
char * Myfunction:: my_strchr(const char *str, int ch)
{
   while (*str && *str != (char)ch)
        str++;
   if (*str == (char)ch)
        return((char *)str);
   return(NULL);
}

//Դ��strnicmp
/////////////////////////////////////////////////////////////////////////////
int Myfunction:: my_strnicmp(const char *dst,const char *src,int count)
{
   int ch1, ch2;
   do
   {
      if ( ((ch1 = (unsigned char)(*(dst++))) >= 'A') &&(ch1 <= 'Z') )
        ch1 += 0x20;
      if ( ((ch2 = (unsigned char)(*(src++))) >= 'A') &&(ch2 <= 'Z') )
        ch2 += 0x20;
   } while ( --count && ch1 && (ch1 == ch2) );
   return (ch1 - ch2);
}

//ȥ���ַ�������ǰ��Ŀո�
/////////////////////////////////////////////////////////////////////////////
char * Myfunction:: DelSpace(char *szData)
{
	int i=0 ;
	while(1)
	{
		if(my_strnicmp(szData+i," ",1))
			break;
		i++;			
	}
	return (szData+i);
} 
 

//ceil����Դ��
//////////////////////////////////////////////////////////////////////////////////////////////////
double Myfunction:: my_ceil(double x)
{
    double y=x;
     if( (*( ( (int *) &y)+1) & 0x80000000) != 0)//����if(x<0)
         return (float)((int)x);
     else                  //���۷Ǹ��������
    {
         if(x == 0)
         return (float)((int)x);
         else
         return (float)((int)x) + 1;
    }
}

//memcpy����Դ��
/////////////////////////////////////////////////////////////////////////////////////////////////
void * Myfunction:: my_memcpy(void * dst, const void * src, size_t count)
{
         void * ret = dst;
         while (count--) {
                 *(char *)dst = *(char *)src;
                 dst = (char *)dst + 1;
                 src = (char *)src + 1;
         }
         return(ret);
}

//strncmp����Դ��
//////////////////////////////////////////////////////////////////////////////////////////////////
int Myfunction:: my_strncmp(const char *first,const char *last,int count)
{
   if (!count)
      return(0);
   while (--count && *first && *first == *last)first++,last++;
   return( *(unsigned char *)first - *(unsigned char *)last );
}

//substr����Դ��
//////////////////////////////////////////////////////////////////////////////////////////////////
char * Myfunction:: my_substr(char   *str,int   istar,int   iend) 
{ 
	char   *p; 
	char   p1[100]={0}; 
	int   ip=0; 

    p=str; 
    ip=my_strlen(p); 
    if(istar> ip) 
		return   NULL; 
    else 
    { 
		p+=istar-1; 
    } 
    int   ipp=my_strlen(p); 
    if(ipp <iend) 
		my_strcpy(p1,p); 
    else 
    { 
        //p1+=iend; 
		my_memcpy(p1,p,iend); 
    }
	my_strcpy(str,p1);
    return   str; 
} 

//Դ��strncpy
/////////////////////////////////////////////////////////////////////////////
char * Myfunction:: my_strncpy( char * dest, const char * source, int count )
{
   char *p = dest;
   while (count && (*p++ = *source++)) count--;
   while(count--)
      *p++ = '\0';
   return(dest);
} 

//Դ��strcat
/////////////////////////////////////////////////////////////////////////////
char* Myfunction:: my_strcat( char * dst , const char * src )  
{  
    char * cp = dst;  
    while( *cp )  
        cp++;                       
    while( *cp++ = *src++ ) ;       
    return( dst );                  
}

//Դ��strlen
/////////////////////////////////////////////////////////////////////////////
typedef unsigned long  ulong;  
size_t Myfunction:: my_strlen(const char * str)
 {

const char * char_ptr;
     const ulong * longword_ptr;
     register ulong longword, magic_bits;
  
     for (char_ptr =  str; ((ulong)char_ptr 
         & (sizeof(ulong) - 1)) != 0 ;
         ++ char_ptr) {
         if ((char *)char_ptr == "\0" )
             return char_ptr -  str;
      }
  
     longword_ptr = (ulong* )char_ptr;
  
     magic_bits = 0x7efefeffL ;
  
     while (1 ) {
  
         longword = *longword_ptr++ ;
  
         if ((((longword + magic_bits) ^ ~longword) & ~magic_bits) != 0 ) {
  
             const char *cp = (const char*)(longword_ptr - 1 );
              
             if (cp[0] == 0 )
                 return cp -  str;
             if (cp[1] == 0 )
                 return cp - str + 1 ;
             if (cp[2] == 0 )
                 return cp - str + 2 ;
             if (cp[3] == 0 )
                 return cp - str + 3 ;
          }
      }
 } 

//Դ��strcpy
/////////////////////////////////////////////////////////////////////////////
char * Myfunction:: my_strcpy (char * dst, char * src)
{
    char * cp = dst;

    while( *cp++ = *src++ );               
    return( dst );
}

//Դ��memfind
/////////////////////////////////////////////////////////////////////////////
int Myfunction:: my_memfind(const char *mem, const char *str, int sizem, int sizes)   
{   
	int   da,i,j;   
	if (sizes == 0) da = my_strlen(str);   
	else da = sizes;   
	for (i = 0; i < sizem; i++)   
	{   
		for (j = 0; j < da; j ++)   
			if (mem[i+j] != str[j])	break;   
			if (j == da) return i;   
	}   
	return -1;   
}

//Դ��strcmp
/////////////////////////////////////////////////////////////////////////////
int Myfunction:: my_strcmp ( const char* src, const char* dst )  
{  
    int ret = 0 ;  
    while( !(ret = *(unsigned char *)src - *(unsigned char *)dst) && *dst)  
        ++src, ++dst;  
    if ( ret < 0 )  
        ret = -1 ;  
    else if ( ret > 0 )  
        ret = 1 ;  
    return( ret );  
}  

//Դ��strncat
/////////////////////////////////////////////////////////////////////////////
char * Myfunction:: my_strncat(char *dest,const char *source,int count)
{
   char *p = dest;
   while (*p) p++;
   while (count-- && (*p++ = *source++));
   *p = (char)'/0';
   return(dest);
}

//Դ��rand
/////////////////////////////////////////////////////////////////////////////
#define RANDOM_MAX 0x7FFFFFFF
static unsigned long next = 1;
static long my_do_rand(unsigned long *value)
{
   long quotient, remainder, t;
 
   quotient = *value / 127773L;
   remainder = *value % 127773L;
   t = 16807L * remainder - 2836L * quotient;
 
   if (t <= 0)
      t += 0x7FFFFFFFL;
  return ((*value = t) % ((unsigned long)RANDOM_MAX + 1));
}

int Myfunction:: my_rand(void)
{
   return my_do_rand(&next);
}

//Դ��strrchr
/////////////////////////////////////////////////////////////////////////////
char * Myfunction:: my_strrchr(const char * str,int ch)
{

	char *p = (char *)str;
	while (*str) str++;
	while (str-- != p && *str != (char)ch);
	if (*str == (char)ch) 
        return( (char *)str );

	return(NULL);
}

// RC4 ��ʼ��
void Myfunction:: rc4_init(unsigned char *s, unsigned char *key, unsigned long Len)
{
	int i =0, j = 0, k[256] = {0};
	unsigned char tmp = 0;
	for(i=0;i<256;i++)
	{
		s[i]=i;
		k[i]=key[i%Len];
	}
	for (i=0; i<256; i++)
	{
		j=(j+s[i]+k[i])%256;
		tmp = s[i];
		s[i] = s[j];     //����s[i]��s[j]
		s[j] = tmp;
	}
}

// RC4 ���ܽ��ܺ���
void Myfunction:: rc4_crypt(unsigned char *s, unsigned char *Data, unsigned long Len)
{
	int x = 0, y = 0, t = 0;
	unsigned char tmp;
	unsigned long i;
	for(i=0;i<Len;i++)
	{
		x=(x+1)%256;
		y=(y+s[x])%256;
		tmp = s[x];
		s[x] = s[y];     //����s[x]��s[y]
		s[y] = tmp;
		t=(s[x]+s[y])%256;
		Data[i] ^= s[t];
	} 
}

/////////////////////////////////////////////////////////////////////////////////////////