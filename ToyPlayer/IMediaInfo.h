//媒体文件（视频文件）信息查询接口(纯虚类)

#pragma once

class IMediaInfo
{
public:
	virtual ~IMediaInfo(){};

	virtual SIZE Resolution() =0;				//分辨率
	virtual LONGLONG Runtime() =0;				//时长，以100纳秒为单位
};
