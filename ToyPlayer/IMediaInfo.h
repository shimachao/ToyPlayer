//ý���ļ�����Ƶ�ļ�����Ϣ��ѯ�ӿ�(������)

#pragma once

class IMediaInfo
{
public:
	virtual ~IMediaInfo(){};

	virtual SIZE Resolution() =0;				//�ֱ���
	virtual LONGLONG Runtime() =0;				//ʱ������100����Ϊ��λ
};
