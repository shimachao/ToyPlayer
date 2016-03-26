#pragma once


// CNewButton

class CNewButton : public CButton
{
	DECLARE_DYNAMIC(CNewButton)

public:
	CNewButton();
	virtual ~CNewButton();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
};


