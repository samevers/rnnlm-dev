/*******************************************************

* �ļ����� gary_common.h
* ��  �ܣ� ��Գ��ú����ķ�װ
* ��  ���� version 1.0 2010-4-18
* ��  �ģ�

********************************************************/

#ifndef __GARY_COMMON_H_
#define __GARY_COMMON_H_
#include "twsetypedef.h"
#include <string>
#include <fstream>
#include <iostream>
#include <dirent.h>  
#include "../service_log.hpp"
namespace spaceGary
{

//�Ƿ���GBK����
 /**
        *���Ĳ���:
        *[A1A0 - A1FF]  	ȫ�Ǳ�����   			���˵�
        *[A2A0 - A2FF]     ���ֱ�����   			���˵�
        *[A3A0 - A3FF]   	�����ASCII�ַ���Ӧ     	ת������Ӧ��ASCII�ַ�,Ӣ�ķִʴ���
        *[A4-A5,A0-FF]     ����Ƭ����				���ķִʴ���
        *[A6-A9,A0-FF]   	���ַ���					���˵�
        *[A8-A9,40-9F]   	���ַ���					���˵�
        *[B0-F7,A0-FF]   	GB2312����				���ķִʴ���
        *[81-A0,40-FF]   	��չ���ֵ�һ����			���ķִʴ������˵�
        *[AA-FE,40-AF]  	��չ���ֵڶ�����			���ķִʴ������˵�     
*/
inline 
TBOOL IsStrictGBKChar(const TCHAR* szWord)
{
    const TUCHAR c1 = (const TUCHAR)*szWord;
    const TUCHAR c2 = (const TUCHAR)*(szWord+1);

    if (
                ((c1 >= 0xA1 && c1 <= 0xA9) && (c2 >= 0xA0 && c2 <= 0xFF)) ||
                ((c1 >= 0xA8 && c1 <= 0xA9) && (c2 >= 0x40 && c2 <= 0xFF)) ||
                ((c1 >= 0xB0 && c1 <= 0xF7) && (c2 >= 0xA0 && c2 <= 0xFF)) ||
                ((c1 >= 0x81 && c1 <= 0xA0) && (c2 >= 0x40 && c2 <= 0xFF)) ||
                ((c1 >= 0xAA && c1 <= 0xFE) && (c2 >= 0x40 && c2 <= 0xAF)) 
         )
     {
		 return TRUE;
     }

     return FALSE;
}


//�Ƿ��������GBK
inline
TBOOL IsIncludeChnGBK(const TCHAR* szText, TUINT32 udwTextLen)
{
	const TCHAR* pCur = szText;

	while (pCur < szText+udwTextLen)
	{
		if (*pCur < 0)
		{
			if ((pCur+1) < (szText + udwTextLen))
			{
				if (IsStrictGBKChar(pCur))
				{
					pCur += 2;
					return TRUE;
				}
				else
				{
					return FALSE;
				}
			}
		}

		pCur++;
	}
	return FALSE;
}
/****************************************/
/*	Open a input file					*/
/****************************************/
inline
int open_f(std::string filename, std::ifstream& infile)
{
	if(filename.length() == 0)
	{
		std::cerr << "ERROR: input file name is NULL....... FALSE !" << std::endl;
		return -1;
	}

	infile.open(filename.c_str(), std::ios::in);
	if(!infile)
	{
		std::cerr << "ERROR: fail to open input file, please check the file is real !" << std::endl;
		return -1;
	}

	return 0;
}

/****************************************/
/*	Build a new file					*/
/****************************************/
inline
int Build_f(std::string filename, std::ofstream& outfile)
{
	if(filename.length() == 0)
	{
		std::cerr << "ERROR: output file name is NULL !" << std::endl;
		return -1;
	}

	outfile.open(filename.c_str(), std::ios::out);
	if(!outfile)
	{
		std::cerr << "ERROR: fail to build output file, please check !" << std::endl;
		return -1;
	}

	return 0;
}


int allFiles(std::string& PATH, std::vector<std::string>& files)  
{  
    struct dirent *ptr;      
    DIR *dir;  
    dir=opendir(PATH.c_str());   
	if(dir == NULL)
	{
		_ERROR("Fail to open dir %s", PATH.c_str());
		return -1;
	}
    while((ptr=readdir(dir))!=NULL)  
    {  
        //����'.'��'..'����Ŀ¼  
        if(ptr->d_name[0] == '.')  
            continue;  
        //cout << ptr->d_name << endl;  
        files.push_back(ptr->d_name);  
    }  
      
    //for (int i = 0; i < files.size(); ++i)  
    //{  
    //    cout << files[i] << endl;  
    //}  
  
    closedir(dir);  
    return 0;  
}  

}; //end space

#endif
